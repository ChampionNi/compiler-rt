//===-- aeabi_cfcmp.S - EABI cfcmp* implementation ---------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "../assembly.h"

// void __aeabi_cfcmpeq(float a, float b) {
//   Z = fcmpeq(a, b);
// }

#define APSR_Z (1 << 30)
#define APSR_C (1 << 29)

// FIXME: doesn't specially handle signalling NaN
        .syntax unified
        .p2align 2
DEFINE_COMPILERRT_FUNCTION(__aeabi_cfcmpeq)
        push {r0, r1, lr}
        bl __aeabi_fcmpeq
        cmp r0, #1
        pop {r0, r1, pc}
END_COMPILERRT_FUNCTION(__aeabi_cfcmpeq)


// void __aeabi_cfcmple(float a, float b) {
//   if (__aeabi_fcmplt(a, b)) {
//     Z = 0; C = 0;
//   } else if (__aeabi_fcmpeq(a, b)) {
//     Z = 1; C = 1;
//   } else {
//     Z = 0; C = 1;
//   }
// }

        .syntax unified
        .p2align 2
DEFINE_COMPILERRT_FUNCTION(__aeabi_cfcmple)
        push {r0, r1, lr}
        bl __aeabi_fcmplt
        cmp r0, #1
        bne 1f
        msr CPSR_f, #0
        pop {r0, r1, pc}

1:
        ldm sp, {r0, r1}
        bl __aeabi_fcmpeq
        cmp r0, #1
        bne 2f
        msr CPSR_f, #(APSR_Z | APSR_C)
        pop {r0, r1, pc}

2:
        msr CPSR_f, #APSR_C
        pop {r0, r1, pc}
END_COMPILERRT_FUNCTION(__aeabi_cfcmple)

// int __aeabi_cfrcmple(float a, float b) {
//   return __aeabi_cfcmple(b, a);
// }

        .syntax unified
        .p2align 2
DEFINE_COMPILERRT_FUNCTION(__aeabi_cfrcmple)
        // Swap r0 and r1
        mov ip, r0
        mov r0, r1
        mov r1, ip
        b __aeabi_cfcmple
END_COMPILERRT_FUNCTION(__aeabi_cfrcmple)

