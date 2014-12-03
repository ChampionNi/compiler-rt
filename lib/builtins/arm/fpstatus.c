//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// ARM v7/Aarch32 Float-Point Status & Control register partial handling
//   Similar to fegetround and feraiseexcept without the libm dependency
//===----------------------------------------------------------------------===//

#include <stdint.h>
#include "fpstatus.h"

#define FPSCR_RMODE_SHIFT 22

int __fpgetround(void)
{
  uint32_t _fpscr;
  __asm__ __volatile__("vmrs %0,fpscr" : "=r" (_fpscr));
  return ((_fpscr >> FPSCR_RMODE_SHIFT) & _ROUND_MASK);
}

int __fpraiseexcept(int excepts)
{
  uint32_t _fpscr;
  const uint32_t exceptMask = (excepts & FE_ALL_EXCEPT);
  __asm__ __volatile__("vmrs %0,fpscr" : "=r" (_fpscr));
  if ((_fpscr &  exceptMask) != exceptMask) {
    _fpscr |= exceptMask;
    __asm__ __volatile__("vmsr fpscr,%0" : :"ri" (_fpscr));
  }
  return 0;
}
