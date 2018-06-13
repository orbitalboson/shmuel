/*
 * hello_world.c
 *
 *  Created on: 13 June 2018
 *      Author: OrbitalBoson
 */

#include <stdio.h>

#include "os.h"

int main(int argc, char * argv[])
{
  uint32_t page_size = shmuGetOSPageSize();
  printf("OS page size: %d \r\n", page_size);

  return 0;
}

