/*
 * ringbuffer.h
 *
 *  Created on: 13 June 2018
 *      Author: OrbitalBoson
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>

#include "sharedmemory.h"
#include "utils.h"

typedef struct
{
  SharedMemoryBlock * shmb;
  uint8_t *start, *tail;
  size_t block_size;
  size_t block_count;
  uint32_t id;
} RingBuffer;

typedef struct {
  uint32_t id;
  size_t payload_size;
} RBFrameHeaderMain;

typedef struct {
  RBFrameHeaderMain main;
  uint8_t crc8;
} RBFrameHeader;

int RingBuffer_init(RingBuffer * rb, SharedMemoryBlock * shmb, size_t block_size);
int RingBuffer_put(RingBuffer * rb, void * buf, size_t size);
int RingBuffer_isFull(RingBuffer * rb);

#endif /* RINGBUFFER_H_ */
