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

/* Exception flags. */
#define FE_INVALID   0x01
#define FE_DIVBYZERO 0x02
#define FE_OVERFLOW  0x04
#define FE_UNDERFLOW 0x08
#define FE_INEXACT   0x10
#define FE_DENORMAL  0x80
#define FE_ALL_EXCEPT (FE_DIVBYZERO | FE_INEXACT | FE_INVALID | \
                       FE_OVERFLOW | FE_UNDERFLOW | FE_DENORMAL)

/* Rounding modes. */
#define FE_TONEAREST  0x0
#define FE_UPWARD     0x1
#define FE_DOWNWARD   0x2
#define FE_TOWARDZERO 0x3
#define _ROUND_MASK     (FE_TONEAREST | FE_DOWNWARD | \
                         FE_UPWARD | FE_TOWARDZERO)


// Get the current rounding mode (as in fegetround)
int __fpgetround();
// Raise the supported exceptions (as in feraiseexcept)
int __fpraiseexcept(int);

#endif // FPSTATUS_H
