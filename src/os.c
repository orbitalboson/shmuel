/*
 * os.c
 *
 *  Created on: 11 june 2018
 *      Author: OrbitalBoson
 */

#include "os.h"

uint32_t
shmuGetOSPageSize()
{
  uint32_t res;
  res = sysconf(_SC_PAGESIZE);

  if (res == -1){
    res = DEFAULT_OS_PAGE_SIZE;
#ifdef DEBUG
    printf("%s:%d (%s) Uses DEFAULT_OS_PAGE_SIZE \n", __FILE__, __LINE__, __FUNCTION__);
#endif
  }

  return res;
}
