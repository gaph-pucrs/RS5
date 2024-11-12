#   Example: 
#       1 - load 16-bit values
#       2 - widen multiply to 32b
#       3 - shift 32b result right by 3 (reason?) 
#       4 - store 32b values
#
#   a0: total number of elements to process
#   a1: holds the address of the source array (e16b) 
#   a2: holds the address of the destination array (e32b) 

loop:
    vsetvli     a3, a0, e16, m4, ta, ma     # vl = a3 = 8 
    vle16.v     v4, (a1)        # load a1[i] 
    slli        t1, a3, 1       # t1 = 2*vl 
    add         a1, a1, t1      # i += 16   (i++)
    vwmul.vx    v8, v4, x10     # res is 2*SEW (32b)
                                # res = 2*v4 
    
    vsetvli     x0, x0, e32, m8, ta, ma     # same vl, but elements
                                            # are 32b now
    vsrl.vi     v8, v8, 3       # res >> 3  
    vse32.v     v8, (a2)        # store res in rd 
    slli        t1, a3, 2       # t1 = 4vl  
    add         a2, a2, t1      # i += 32    (i++) 
    sub         a0, a0, a3      # decrement count by vl 
    bnez        a0, loop        # loop
