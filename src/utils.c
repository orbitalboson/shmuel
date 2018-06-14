/*
 * utils.c
 *
 *  Created on: Jun 12, 2018
 *      Author: OrbitalBoson
 */

#include "utils.h"

uint8_t Crc8(uint8_t *pcBlock, uint8_t init, size_t len)
{
  uint8_t crc = init;
  unsigned int i;

  while (len--)
  {
    crc ^= *pcBlock++;
    for (i = 0; i < 8; i++)
      crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;
  }

  return crc;
}
