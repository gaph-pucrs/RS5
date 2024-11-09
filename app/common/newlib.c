#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>

#undef errno
extern int errno;

#define HALT (*((volatile unsigned int*)0x80000000))
#define UART (*((volatile unsigned int*)0x80001000))

int _close (int file) {
	errno = EBADF;
	return -1;
}

void _exit (int  rc)
{
	while (true) {
		HALT = 0;
	}
}

int _fstat(int file, struct stat *st)
{
	if(file != STDOUT_FILENO && file != STDERR_FILENO){
		errno = EBADF;
		return -1;
    }

	st->st_mode = S_IFCHR;
	return 0;
}

int _lseek(int file, int offset, int whence)
{
	if((STDOUT_FILENO != file) && (STDERR_FILENO != file)){
		errno = EBADF;
		return -1;
	} 
	return 0;
}

int _read (int file, char *ptr, int len)
{
	return  0;
}

caddr_t _sbrk(int incr)
{
	extern char _end;		/* Defined by the linker */
	static char *heap_end = 0;
	char *prev_heap_end;

	/* Initialize heap_end on first call */
	if (heap_end == 0) {
		heap_end = &_end;
	}
	prev_heap_end = heap_end;

	/* Little trick to get the stack pointer */
	void* stack_ptr = NULL;

	if ((heap_end + incr) > (char*)&stack_ptr) {
		write(1, "Heap and stack collision\n", 25);
		return NULL;
	}

	heap_end += incr;
	return (caddr_t) prev_heap_end;
}

int _write (int file, char *buf, int nbytes)
{
	/* We only handle stdout and stderr */
	if ((file != STDOUT_FILENO) && (file != STDERR_FILENO)) {
		errno = EBADF;
		return -1;
	}

	/* Output character at at time */
	for (int i = 0; i < nbytes; i++) {
		UART = buf[i];
	}

	return nbytes;
}
