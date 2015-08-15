.syntax unified
// __attribute__((pcs("aapcs"))) int32_t call_apsr_d(double a, double b, void(*fn)(double, double)) {
//   fn(a, b);
//   return apsr;
// }

.globl call_apsr_d
.type call_apsr_d,%function
call_apsr_d:
    push {lr}
    ldr ip, [sp, #4]
	blx ip
	mrs r0, apsr
    pop {pc}

// __attribute__((pcs("aapcs"))) int32_t call_apsr_f(float a, float b, void(*fn)(float, float)) {
//   fn(a, b);
//   return apsr;
// }

.globl call_apsr_f
.type call_apsr_f,%function
call_apsr_f:
	push {lr}
	blx r2
	mrs r0, apsr
	pop {pc}
