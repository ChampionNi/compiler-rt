//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// x86_64/x87 FP handling of rounding and exceptions
//===----------------------------------------------------------------------===//

#include <stdint.h>
#include "fpstatus.h"

int __fpgetround(void)
{
  unsigned short control;
  __asm__ __volatile__ ("fnstcw %0" : "=m" (control));
  return (control & _ROUND_MASK);
}

#define FLT_MIN 0x1p-95
#define FLT_MAX 0x1p+97

volatile float __r;
int __fpraiseexcept(int excepts)
{
    if (excepts & FE_INVALID)
        __r = 0.0f/0.0f;
    if (excepts & FE_DIVBYZERO)
        __r = 1.0f/0.0f;
    if (excepts & FE_OVERFLOW)
        __r = FLT_MAX* FLT_MAX;
    if (excepts & FE_UNDERFLOW)
        __r = FLT_MIN*FLT_MIN;
    if (excepts & FE_INEXACT)
        __r = FLT_MAX -1.0f;
    return 0;
}
