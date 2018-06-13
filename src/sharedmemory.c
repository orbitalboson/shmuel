/*
 * sharedmemory.c
 *
 *  Created on: 13 June 2018
 *      Author: OrbitalBoson
 */

#include "sharedmemory.h"

SharedMemoryBlock *
shmuCreateSharedMemory(const char * name, size_t size)
{
  uint8_t r;
  SharedMemoryBlock * shmb = malloc(sizeof(SharedMemoryBlock));
  if (!shmb){
#ifdef DEBUG
    printf("%s:%d (%s) Malloc failed \n", __FILE__, __LINE__, __FUNCTION__);
#endif
    return NULL;
  }

  SharedMemoryBlock_init(shmb);

  strncpy((char *)shmb->name, name, sizeof(shmb->name));
  shmb->size = size;

#ifdef DEBUG
    printf("%s:%d (%s) SharedMemoryBlock name: %s \n", __FILE__, __LINE__, __FUNCTION__, shmb->name);
    printf("%s:%d (%s) SharedMemoryBlock size: %d \n", __FILE__, __LINE__, __FUNCTION__, (int)shmb->size);
#endif

  int oflags = O_RDWR | O_CREAT;

  int fd = shm_open(shmb->name, oflags, 0777);
  if (fd == -1){
    shmb->status |= SHMB_ERROR;
#ifdef DEBUG
    printf("%s:%d (%s) shm_open failed \n", __FILE__, __LINE__, __FUNCTION__);
#endif
    return shmb;
  }

  r = ftruncate(fd, shmb->size);
  if (r == -1){
    shmb->status |= SHMB_ERROR;
    close(fd);
#ifdef DEBUG
    printf("%s:%d (%s) ftruncate failed \n", __FILE__, __LINE__, __FUNCTION__);
#endif
    return shmb;
  }

  uint8_t * ptr = (uint8_t *) mmap(NULL, shmb->size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  if (ptr == (void *)-1){
    shmb->status |= SHMB_ERROR;
    close(fd);
#ifdef DEBUG
    printf("%s:%d (%s) mmap failed \n", __FILE__, __LINE__, __FUNCTION__);
#endif
    return shmb;
  }

  shmb->buf = ptr;
  shmb->status |= SHMB_SUCCESS;

  close(fd);

  return shmb;
}

void
SharedMemoryBlock_init(SharedMemoryBlock * shmb){
  memset(shmb->name, 0, sizeof(shmb->name));
  shmb->size = 0;
  shmb->buf = NULL;
  shmb->status = 0;
}

void
SharedMemoryBlock_destroy(SharedMemoryBlock * shmb){
  shm_unlink(shmb->name);
  free(shmb);
}

void
SharedMemoryBlock_printStatus(SharedMemoryBlock * shmb){
  printf("SharedMemoryBlock status SUCCESS: %s \n", (shmb->status & SHMB_SUCCESS) ? "yes" : "no");
  printf("SharedMemoryBlock status ERROR: %s \n", (shmb->status & SHMB_ERROR) ? "yes" : "no");
}

