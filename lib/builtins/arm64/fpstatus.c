//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// AARCH64 Float-Point Status & Control register partial handling
//   Similar to fegetround and feraiseexcept without the libm dependency
//===----------------------------------------------------------------------===//

#include <stdint.h>
#include "fpstatus.h"

#define FPCR_RMODE_SHIFT 22


int __fpgetround(void)
{
  uint32_t _fpsr;
  __asm__ __volatile__("mrs  %0, fpsr" : "=r" (_fpsr));
  return (_fpsr >> FPCR_RMODE_SHIFT) & _ROUND_MASK;
}

int __fpraiseexcept(int excepts)
{
  uint32_t _fpsr;
  const uint32_t exceptMask = excepts & FE_ALL_EXCEPT;
  __asm__ __volatile__("mrs  %0, fpsr" : "=r" (_fpsr));
  if ((_fpsr & exceptMask) != exceptMask) {
    _fpsr |= exceptMask;
    __asm__ __volatile__("msr  fpsr, %0" : : "ri" (_fpsr));
  }
  return 0;
}
