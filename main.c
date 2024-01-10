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

#include <stdbool.h>

// [TODO] Add munmap at some point
// [NOTE] Should I only allocate "page aligned" values of requested size?

struct heapNode_t {
    void *head;
    int size;
};

struct heapinfo_t {
    bool success;
    void *head;

    struct heapNode_t *nodes;
};

struct heapinfo_t heapAlloc(int heapSize) {
    printf("Attempting to allocate a heap of size %d\n", heapSize);

    struct heapinfo_t retVal;
    retVal.success = false;
    retVal.head = NULL;
    retVal.nodes = NULL;

    void *address = NULL;
    int prot = PROT_EXEC | PROT_READ | PROT_WRITE;    // ALL THE PERMISSIONS!!!
    int flags = MAP_PRIVATE | MAP_ANONYMOUS;    // Get a errno of EPERM if I try MAP_SHARED lol
    int fd = 0;
    int offset = 0;

    retVal.head = mmap(address, heapSize * sizeof(int), prot, flags, fd, offset);

    if (retVal.head == MAP_FAILED) {
        printf("Mapping failed with error %d\n", errno);
        return retVal;
    }

    // I hate that this isn't cpp... I want classes not structure management nonsense...

    retVal.success = true;

    return retVal;
}

void heapPrint(void *heap) {
    //
}

int main() {
    int heapSize;
    printf("How many bytes do you want your heap to be?\n");
    scanf("%d", &heapSize);

    struct heapinfo_t heap = heapAlloc(heapSize);
    printf("Your heap is located at %p\n", heap.head);

    return 0;
}
