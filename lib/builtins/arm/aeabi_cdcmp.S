//===-- aeabi_cdcmp.S - EABI cdcmp* implementation ---------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "../assembly.h"

#define APSR_Z (1 << 30)
#define APSR_C (1 << 29)

// void __aeabi_cdcmpeq(double a, double b) {
//   Z = dcmpeq(a, b);
// }

// FIXME: doesn't specially handle signalling NaN
        .syntax unified
        .p2align 2
DEFINE_COMPILERRT_FUNCTION(__aeabi_cdcmpeq)
        push {r0, r1, r2, r3, lr}
        bl __aeabi_dcmpeq
        cmp r0, #1
        pop {r0, r1, r2, r3, pc}
END_COMPILERRT_FUNCTION(__aeabi_cdcmpeq)


// void __aeabi_cdcmple(double a, double b) {
//   if (__aeabi_dcmplt(a, b)) {
//     Z = 1; C = 0;
//   } else if (__aeabi_dcmpeq(a, b)) {
//     Z = 0; C = 1;
//   } else {
//     Z = 0; C = 0;
//   }
// }

        .syntax unified
        .p2align 2
DEFINE_COMPILERRT_FUNCTION(__aeabi_cdcmple)
        push {r0, r1, r2, r3, lr}
        bl __aeabi_dcmplt
        cmp r0, #1
        bne 1f
        msr CPSR_f, #0
        pop {r0, r1, r2, r3, pc}

1:
        ldm sp, {r0, r1, r2, r3}
        bl __aeabi_dcmpeq
        cmp r0, #1
        bne 2f
        msr CPSR_f, #(APSR_Z | APSR_C)
        pop {r0, r1, r2, r3, pc}

2:
        msr CPSR_f, #APSR_C
        pop {r0, r1, r2, r3, pc}
END_COMPILERRT_FUNCTION(__aeabi_cdcmple)

// int __aeabi_cdrcmple(double a, double b) {
//   return __aeabi_cdcmple(b, a);
// }

        .syntax unified
        .p2align 2
DEFINE_COMPILERRT_FUNCTION(__aeabi_cdrcmple)
        // Swap r0 and r2
        mov ip, r0
        mov r0, r2
        mov r2, ip

        // Swap r1 and r3
        mov ip, r1
        mov r1, r3
        mov r3, ip
        b __aeabi_cdcmple
END_COMPILERRT_FUNCTION(__aeabi_cdrcmple)

