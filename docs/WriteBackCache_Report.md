# Direct-Mapped Write-Back Cache (`DMWBCtrl`) — Design Report

**Author:** Lucas Motta Damo
**Date:** 2026-06-21
**Branch:** `cached`
**Module:** `CacheControllers/rtl/DMWBCtrl.sv`

---

## 1. Goal

The `cached` branch already shipped a direct-mapped **write-through** cache
controller (`DMWTCtrl`). The task was to add the **write-back** counterpart,
following the RS5 coding style, and validate it against the `riscv-tests` suite.

The result is `DMWBCtrl`: a direct-mapped, **write-back / write-allocate** cache
controller that is pin-compatible with `DMWTCtrl`, so it drops into the existing
testbench without any wrapper changes.

---

## 2. Architecture overview

The controller sits between the core and two synchronous SRAM-style memories,
exactly like `DMWTCtrl`:

```
        core (ce/we/addr/data)
                │
                ▼
        ┌───────────────┐   cache_*   ┌──────────────┐
        │   DMWBCtrl     │◀───────────▶│  cache SRAM  │  (data store, 1 cycle)
        │ (tags+dirty,   │             └──────────────┘
        │  burst FSM)    │   mem_*     ┌──────────────┐
        │                │◀───────────▶│  main memory │  (backing store, may stall)
        └───────────────┘             └──────────────┘
```

* The **cache SRAM** (`cache_*`) only stores data words. All metadata
  (valid, dirty, tag) lives in flip-flops inside the controller.
* The **main memory** (`mem_*`) carries the variable-latency handshake through
  `mem_busy_i`.

### Address decode

The address layout is identical to `DMWTCtrl` and fully parameterizable:

```
addr = { tag | index | offset }
         TAG   INDEX    OFFSET
```

| Parameter      | Default | Meaning                                  |
|----------------|---------|------------------------------------------|
| `ADDR_WIDTH`   | 20      | Main-memory address width                |
| `CACHE_WIDTH`  | 12      | log2(cache data store size in bytes)     |
| `OFFSET_WIDTH` | 6       | log2(line size in bytes) → 64-byte lines |

Derived: `TAG_WIDTH = ADDR-CACHE`, `INDEX_WIDTH = CACHE-OFFSET`,
`FILL_WORDS = 2^(OFFSET-2)` words per line, `NB_BLOCKS = 2^INDEX` lines.
With the testbench defaults (`ADDR=28`, `CACHE=12`, `OFFSET=6`): 64 lines of
64 bytes (16 words) each, 4 KiB data store, 16-bit tags.

---

## 3. Cache policy and protocol

| Event          | `DMWTCtrl` (write-through) | `DMWBCtrl` (write-back, this work) |
|----------------|---------------------------|------------------------------------|
| Read hit       | serve from SRAM           | serve from SRAM                    |
| Read miss      | fill, then serve          | **evict if dirty → fill → serve**  |
| Write hit      | write SRAM **and** memory | write SRAM, **set dirty** (no mem) |
| Write miss     | write memory only (no allocate) | **evict if dirty → fill → write SRAM → set dirty** (write-allocate) |
| Memory writes  | every store               | only on dirty-line eviction        |

The two defining choices for `DMWBCtrl`:

1. **Write-back** — a store updates only the cache and marks the line dirty.
   Main memory is touched only when a dirty line must be evicted.
2. **Write-allocate** — a write miss first brings the line into the cache, then
   performs the store. This is the natural pairing for write-back and is
   *required* for correctness with sub-word stores (`sb`/`sh`): the rest of the
   word/line must be resident and valid before a partial write, otherwise the
   un-written bytes of the line would later be flushed as garbage.

### Per-line metadata

```systemverilog
typedef struct packed {
    logic valid;
    logic dirty;   // <-- added vs. DMWTCtrl
    tag_t tag;
} entry_t;
```

---

## 4. Miss handling FSM

A write-back miss can require moving an entire line **out** (eviction) and an
entire line **in** (fill). Each word transfer needs one cycle for the SRAM/memory
to answer, so the burst is expressed as an explicit 5-state machine instead of
the single `filling` flag used by the write-through controller:

```
        ┌──────┐  ce & miss & dirty victim   ┌────────────┐ ──┐
        │ IDLE │ ───────────────────────────▶│ EVICT_READ │   │ read word from
        │      │                             └────────────┘   │ cache SRAM
        │ hits │  ce & miss & clean victim          │         │
        │served│ ─────────────┐                     ▼         │
        └──────┘              │              ┌────────────┐   │ write word to
           ▲                  │              │EVICT_WRITE │◀──┘ main memory
           │                  │              └────────────┘
           │                  │            last word │ (when !mem_busy)
           │                  ▼                     ▼
           │           ┌────────────┐        (loop until line flushed)
           │           │  FILL_REQ  │◀──────────────┘
           │           └────────────┘ ──┐
           │                  │          │ request word from main memory
           │                  ▼          │
           │           ┌────────────┐    │
           └───────────│ FILL_WRITE │◀───┘ store word into cache SRAM
            last word  └────────────┘
```

* **`EVICT_READ` → `EVICT_WRITE`** pair: read a victim word out of the cache SRAM
  (1-cycle latency), then drive it onto `mem_*` as a write. `cache_ce_o` is
  de-asserted during `EVICT_WRITE` so the SRAM output holds the word stable while
  main memory completes the write (important when `mem_busy_i` stretches).
* **`FILL_REQ` → `FILL_WRITE`** pair: request a word from main memory, then write
  the returned data into the cache SRAM.
* A shared `word_idx` counter walks the line for both phases. The eviction reuses
  the *old* tag (`evict_tag_r`, captured at miss time) to address the write-back;
  the fill uses the *new* tag (`tag_r`, derived from the captured request).
* `busy_o` is held for the whole burst. When the FSM returns to `IDLE`, the line
  is resident, so the still-stalled access **replays as an ordinary hit** through
  the exact same datapath as the write-through controller. For a write miss this
  is what performs the actual store and sets the dirty bit.

### Why an FSM instead of the `filling` flag

The write-through controller only ever moves data **in**, so one flag plus a
couple of counters suffice. Write-back adds a second, opposite-direction transfer
(data **out**) that must complete *before* the fill and that reuses the same
single cache/memory ports. An explicit, named-state FSM makes the ordering
(evict → fill → replay) and the port ownership in each phase unambiguous and
easy to review.

---

## 5. Memory handshake correctness

The controller is **address-stable and request-toggling**: in the request states
(`EVICT_WRITE`, `FILL_REQ`) it asserts `mem_ce_o`, and it advances only when
`mem_busy_i` is low. This matches the testbench memory model
(`sim/testbench.sv`), whose negedge handshake re-arms on each `mem_ce` pulse, and
it was validated across a range of memory latencies (see §6). The cache SRAM is
assumed to have a fixed 1-cycle latency and never stalls — the same assumption
documented in `DMWTCtrl` (`@todo: add cache_busy_i ...`).

---

## 6. Verification

### Method

* Suite: `app/riscv-tests` (65 tests — RV32 UI/UM/UC/UA/MI/SI: ALU, branches,
  loads/stores, `mul`/`div`, compressed, **A-extension atomics**, CSR, traps).
* Built with `riscv64-elf-gcc 14.2.0`, simulated with `Verilator 5.028`.
* The data cache uses `DMWBCtrl`; the instruction cache keeps `DMWTCtrl`
  (read-only, so write-back vs write-through is indistinguishable there — no
  stores means no dirty lines and no eviction traffic). This isolates the change
  to the path that actually exercises the write-back policy.
* Pass criterion: every test prints `..OK` and the run reaches `DONE`
  (a failing `riscv-test` traps to a fail loop and never reaches `DONE`).

### Results — all configurations pass 65/65

| Configuration                              | Result   |
|--------------------------------------------|----------|
| Write-back, single-port, `RAM_DELAY=0`     | 65/65 ✅ |
| Write-back, single-port, `RAM_DELAY=2`     | 65/65 ✅ |
| Write-back, single-port, `RAM_DELAY=5`     | 65/65 ✅ |
| Write-back, dual-port,   `RAM_DELAY=0`     | 65/65 ✅ |
| Write-through baseline (reference)         | 65/65 ✅ |

### Memory write traffic (the whole point of write-back)

Counting writes to main memory over the full suite (`RAM_DELAY=0`):

| Cache policy   | Main-memory writes | Notes                              |
|----------------|--------------------|------------------------------------|
| Write-through  | **1172**           | one per store, every store         |
| Write-back     | **32**             | only dirty-line evictions          |

That is a **~97% reduction** in write traffic to main memory — exactly the
behavior expected from a write-back cache, and direct evidence that the dirty-bit
/ eviction path is actually being exercised (not just bypassed).

### Performance note

At `RAM_DELAY=0` the write-back run finishes in 473,685 ns vs 471,605 ns for
write-through (~0.4% slower, ≈208 cycles). With zero memory latency, avoided
writes are nearly free, so the simpler write-through fill wins marginally. The
write-back advantage grows as memory latency increases, because each eliminated
write would otherwise cost `RAM_DELAY` cycles. A latency sweep on a
store-heavy benchmark would make the crossover explicit (see §8).

### Reproducing

```sh
module load verilator riscv64-elf/14.2.0
source /opt/rh/gcc-toolset-14/enable      # newer g++ for Verilator coroutines
cd app/riscv-tests && make                # build test.bin
cd ../../sim       && make run            # verilate + simulate
```

---

## 7. Coding-style notes

`DMWBCtrl` deliberately mirrors `DMWTCtrl` so the two read as siblings:

* Same GAPH/PUCRS header block, same `////`-delimited section banners, same
  parameter/`localparam`/`typedef` ordering and naming (`tag_t`, `line_idx_t`,
  `word_idx_t`, `entry_t`).
* Same interface block layout and comment phrasing for the core / cache / memory
  ports — it is a drop-in replacement.
* `always_ff @(posedge clk or negedge rst_n)` with active-low async reset
  throughout (the new code consistently uses `negedge rst_n`, including the
  metadata-reset block where `DMWTCtrl` has a likely `posedge rst_n` typo).
* Combinational output decoders written as `always_comb`/`unique case` over the
  FSM state — clearer than nested ternaries for a 5-state machine, while the
  trivial one-liners (`data_o`, `mem_data_o`) stay as `assign`.
* Verilator-clean under `-Wall` (lint-only and full build), reusing the existing
  `lint_off UNUSEDSIGNAL` idiom for the partially-used `address_r`.

---

## 8. Possible improvements

1. **Pipeline the fill (and eviction).** Today each word costs a
   request/answer pair (≈2 cycles/word at zero latency). `DMWTCtrl` streams its
   fill at ~1 word/cycle by keeping `mem_ce` high and using a 2-pointer
   issue/commit scheme (`fetch_idx`/`fill_idx` + registered `mem_valid`). The
   same technique — plus a 1-deep skid register for the eviction read — would
   roughly halve burst time. It was traded away here for an obviously-correct,
   easy-to-review FSM.

2. **Critical-word-first + early restart.** Fetch the requested word first and
   release the core as soon as it arrives, filling the rest of the line in the
   background. This hides most of the miss latency for the common case.

3. **Write/eviction buffer.** Stream the dirty victim into a small buffer and
   start the fill immediately, draining the write-back to memory in parallel.
   This removes the serial "evict-then-fill" penalty entirely for dirty misses.

4. **Sub-block / partial dirty tracking.** A dirty bit per word (instead of per
   line) lets eviction write back only the words that actually changed, cutting
   write traffic further on lines that are only lightly modified.

5. **`cache_busy_i` support.** The current design assumes a fixed-latency cache
   SRAM. Supporting a stallable SRAM (as the `@todo` in both controllers notes)
   would need output buffering with bypass.

6. **Associativity.** Moving from direct-mapped to set-associative (with a
   replacement policy such as LRU/PLRU) would cut conflict misses, which on a
   direct-mapped cache also directly cause extra dirty evictions.

7. **Coherence / fence support.** There is currently no flush/`fence.i`
   mechanism to force dirty lines back to memory. A self-test (`fence_i`) is
   already commented out in `app/riscv-tests/test.S`; a cache-flush path would be
   needed before DMA or instruction-memory modification can be relied upon.

8. **Assertions & directed tests.** Add SVA for the invariants
   (e.g. "a line is never evicted without writing back when dirty",
   "`word_idx` never exceeds `FILL_WORDS-1`") and a directed store/evict
   micro-benchmark that deliberately thrashes one index to stress the
   evict→fill→replay sequence under high `RAM_DELAY`.
