/* Fast pseudo-random bits based on clock_gettime.
   Copyright (C) 2019-2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#ifndef _RANDOM_BITS_H
# define _RANDOM_BITS_H

#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/* LOCAL RANDOM-BITS: Provides fast pseudo-random bits through clock_gettime.  It has unspecified
   starting time, nano-second accuracy, its randomness is significantly better
   than gettimeofday, and for mostly architectures it is implemented through
   vDSO instead of a syscall.  Since the source is a system clock, the upper
   bits will have less entropy. */
static inline uint32_t
random_bits (void)
{
  struct timespec tv;
  clock_gettime (CLOCK_MONOTONIC, &tv);
  printf("\n random_bits: Time data: %lld | . | %.9ld \n", (long long)tv.tv_sec, tv.tv_nsec);
  /* Shuffle the lower bits to minimize the clock bias.  */
  uint32_t ret = tv.tv_nsec ^ tv.tv_sec;
  ret ^= (ret << 24) | (ret >> 8);
  return ret;
}

uint32_t
random_bits_from_seed (time_t tv_sec, long tv_nsec)
{
  // printf("\n from seed: Time data: %lld.%.9ld \n", (long long)tv_sec, tv_nsec);

  /* Shuffle the lower bits to minimize the clock bias.  */
  uint32_t ret = tv_nsec ^ tv_sec;
  ret ^= (ret << 24) | (ret >> 8);
  return ret;
}

#endif
