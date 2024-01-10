/*
    Insipration for this taken from https://www.youtube.com/watch?v=CulF4YQt6zA

    Can use WSL linux for gcc
    gcc main.c && ./a.out
*/

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// erno codes: https://stackoverflow.com/questions/46013418/how-to-check-the-value-of-errno
#include <errno.h>

void *heapAlloc(int heapSize) {
    printf("Attempting to allocate a heap of size %d\n", heapSize);

    void *address = NULL;
    int prot = PROT_EXEC | PROT_READ | PROT_WRITE;    // ALL THE PERMISSIONS!!!
    int flags = MAP_PRIVATE | MAP_ANONYMOUS;    // Get a errno of EPERM if I try MAP_SHARED lol
    int fd = 0;
    int offset = 0;

    void *ptr = mmap(address, heapSize * sizeof(int), prot, flags, fd, offset);
    printf("debug: %p\n", ptr);

    if (ptr == MAP_FAILED) {
        printf("Mapping failed with error %d\n", errno);
        return NULL;
    }

    return ptr;
}

int main() {
    int heapSize;
    printf("How many bytes do you want your heap to be?\n");
    scanf("%d", &heapSize);

    void *heapPtr = heapAlloc(heapSize);
    printf("Your heap is located at %p\n", heapPtr);

    return 0;
}
