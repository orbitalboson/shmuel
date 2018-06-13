/*
 * sharedmemory.h
 *
 */

#ifndef SHAREDMEMORY_H_
#define SHAREDMEMORY_H_

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SHMB_SUCCESS 	1
#define SHMB_ERROR 	2

typedef struct {
  char name[NAME_MAX];
  size_t size;
  uint8_t * buf;
  uint8_t status;
} SharedMemoryBlock;

SharedMemoryBlock * shmuCreateSharedMemory(const char * name, size_t size);
void SharedMemoryBlock_init(SharedMemoryBlock * shmb);
void SharedMemoryBlock_destroy(SharedMemoryBlock * shmb);
void SharedMemoryBlock_printStatus(SharedMemoryBlock * shmb);

#endif /* SHAREDMEMORY_H_ */
