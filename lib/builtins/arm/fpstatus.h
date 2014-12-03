/* ===-----------------------------------------------------------------------===
 *
 *                     The LLVM Compiler Infrastructure
 *
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 * ===-----------------------------------------------------------------------===
 *
 * This file is not part of the interface of this library.
 *
 * This file defines substitutes for the libm functions used in some of the
 * compiler-rt implementations, defined in such a way that there is not a direct
 * dependency on libm or fenv.h.
 *
 * ===-----------------------------------------------------------------------===
 */

#ifndef FPSTATUS_H
#define FPSTATUS_H

/* Exception flags */
#define FE_INVALID   0x0001
#define FE_DIVBYZERO 0x0002
#define FE_OVERFLOW  0x0004
#define FE_UNDERFLOW 0x0008
#define FE_INEXACT   0x0010
#define FE_ALL_EXCEPT    (FE_DIVBYZERO | FE_INEXACT | \
                          FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW)

/* Rounding modes */
#define FE_TONEAREST  0x0000
#define FE_TOWARDZERO 0x0001
#define FE_UPWARD     0x0002
#define FE_DOWNWARD   0x0003
#define _ROUND_MASK   (FE_TONEAREST | FE_DOWNWARD | \
                       FE_UPWARD | FE_TOWARDZERO)

// Get the current rounding mode (as in fegetround)
int __fpgetround();
// Raise the supported exceptions (as in feraiseexcept)
int __fpraiseexcept(int);

#endif // FPSTATUS_H
