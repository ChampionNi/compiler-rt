//===-- aeabi_cfcmpeq.c - Test __aeabi_cfcmpeq ----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file tests __aeabi_cfcmpeq for the compiler_rt library.
//
//===----------------------------------------------------------------------===//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#if __arm__
#include "call_apsr.h"

extern __attribute__((pcs("aapcs"))) void __aeabi_cfcmpeq(float a, float b);

int test__aeabi_cfcmpeq(float a, float b)
{
    uint32_t cpsr_value = call_apsr_f(a, b, __aeabi_cfcmpeq);
    int expected = a == b;
    union cpsr cpsr = { .value = cpsr_value };
    if (expected != cpsr.flags.z) {
        printf("error in __aeabi_cfcmpeq(%f, %f) => Z = %d, expected %d\n",
               a, b, cpsr.flags.z, expected);
        return 0;
    }
    return 0;
}
#endif

int main()
{
#if __arm__
    if (test__aeabi_cfcmpeq(1.0, 1.0))
        return 1;
    if (test__aeabi_cfcmpeq(1234.567, 765.4321))
        return 1;
    if (test__aeabi_cfcmpeq(-123.0, -678.0))
        return 1;
    if (test__aeabi_cfcmpeq(0.0, -0.0))
        return 1;
    if (test__aeabi_cfcmpeq(1.0, NAN))
        return 1;
    if (test__aeabi_cfcmpeq(NAN, 1.0))
        return 1;
#else
    printf("skipped\n");
#endif
    return 0;
}
