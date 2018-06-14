/*
 * utils.h
 *
 *  Created on: 14 June 2018
 *      Author: OrbitalBoson
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdint.h>
#include <sys/types.h>

uint8_t Crc8(uint8_t *pcBlock, uint8_t init, size_t len);

#endif /* UTILS_H_ */
