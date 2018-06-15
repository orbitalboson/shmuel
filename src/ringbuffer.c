/*
 * ringbuffer.c
 *
 *  Created on: 13 June 2018
 *      Author: OrbitalBoson
 */


#include "ringbuffer.h"

int
RingBuffer_init(RingBuffer * rb, SharedMemoryBlock * shmb, size_t block_size)
{
  if (block_size > shmb->size)
  {
    return -1;
  }

  if ( !(shmb->status & SHMB_SUCCESS) )
  {
#ifdef DEBUG
    printf("%s:%d (%s) shmb->status is not SUCCESS \n", __FILE__, __LINE__, __FUNCTION__);
#endif
      return -1;
  }

  size_t count_of_blocks = shmb->size / (block_size + sizeof(RBFrameHeader));
#ifdef DEBUG
    printf("%s:%d (%s) count_of_blocks: %d \n", __FILE__, __LINE__, __FUNCTION__, (int)count_of_blocks);
#endif

  rb->shmb = shmb;
  rb->block_size = block_size;
  rb->block_count = count_of_blocks;
  rb->start = shmb->buf;
  rb->tail = shmb->buf;
  rb->id = 0;
}

int
RingBuffer_put(RingBuffer * rb, void * buf, size_t size)
{
  if (size > rb->block_size)
  {
#ifdef DEBUG
    printf("%s:%d (%s) Put failed. Size of buffer (%d) is more than max size of RB block (%d)! \n", __FILE__, __LINE__, __FUNCTION__, (int)size, (int)rb->block_size);
#endif

    return -1;
  }

  if (RingBuffer_isFull(rb)){
      rb->tail = rb->start;
  }

  RBFrameHeader rbf_header = {0};
  rbf_header.main.id = rb->id;
  rbf_header.main.payload_size = size;

  uint8_t crc8res = Crc8((void *)&rbf_header, 0xFF, sizeof(RBFrameHeaderMain));
  crc8res = Crc8(buf, crc8res, size);

  rbf_header.crc8 = crc8res;

  memcpy(rb->tail, (uint8_t*)&rbf_header, sizeof(RBFrameHeader));
  memcpy(rb->tail+sizeof(RBFrameHeader), buf, size);

  rb->tail += rb->block_size + sizeof(RBFrameHeader);
#ifdef DEBUG
    printf("%s:%d (%s) ID: #%d. Start and Tail address %p %p \n", __FILE__, __LINE__, __FUNCTION__, (int)rb->id, (void *)rb->start, (void *)rb->tail);
    printf("%s:%d (%s) CRC8: %02x \n", __FILE__, __LINE__, __FUNCTION__, rbf_header.crc8);
#endif

  if (rb->id == UINT32_MAX){
    rb->id = 0;
#ifdef DEBUG
    printf("%s:%d (%s) Maximum value of rb->id is reached. ID reset. \n", __FILE__, __LINE__, __FUNCTION__);
#endif
  } else {
    rb->id += 1;
  }
}

int
RingBuffer_isFull(RingBuffer * rb)
{
  if ((rb->tail - rb->start) / (rb->block_size + sizeof(RBFrameHeader)) >= rb->block_count){
#ifdef DEBUG
    printf("%s:%d (%s) RingBuffer_isFull \n", __FILE__, __LINE__, __FUNCTION__);
#endif
      return 1;
  } else {
      return 0;
  }
}

