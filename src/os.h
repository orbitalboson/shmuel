/*
 * os.h
 *
 *  Created on: 11 june 2018
 *      Author: OrbitalBoson
 */

#ifndef OS_H_
#define OS_H_

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define DEFAULT_OS_PAGE_SIZE	4096;

uint32_t shmuGetOSPageSize();

#endif /* OS_H_ */
