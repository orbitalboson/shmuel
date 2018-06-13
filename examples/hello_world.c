/*
 * hello_world.c
 *
 *  Created on: 13 June 2018
 *      Author: OrbitalBoson
 */

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "sharedmemory.h"
#include "ringbuffer.h"

int main(int argc, char * argv[])
{
  printf("Hello world! \r\n");

  SharedMemoryBlock * r = shmuCreateSharedMemory("/test", 4096);

  SharedMemoryBlock_printStatus(r);

  RingBuffer rb;
  RingBuffer_init(&rb, r, 512);

  char buf[512];

  for (int i=0; i<10; i++){
      RingBuffer_put(&rb, buf, 512);
  }

  SharedMemoryBlock_destroy(r);

  return 0;
}

