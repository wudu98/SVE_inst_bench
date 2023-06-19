.globl cpu_fp32_cpi_kernel_aarch64

cpu_fp32_cpi_kernel_aarch64:
    eor    v0.16b, v0.16b, v0.16b 
    eor    v1.16b, v1.16b, v1.16b 
    eor    v2.16b, v2.16b, v2.16b
    eor    v3.16b, v3.16b, v3.16b
    eor    v4.16b, v4.16b, v4.16b
    eor    v5.16b, v5.16b, v5.16b
    eor    v6.16b, v6.16b, v6.16b
    eor    v7.16b, v7.16b, v7.16b
    eor    v8.16b, v8.16b, v8.16b 
    eor    v9.16b, v9.16b, v9.16b 
.cpufp.aarch64.fp32.L1:
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v1.4s, v1.4s, v1.4s
    fmla    v2.4s, v2.4s, v2.4s
    fmla    v3.4s, v3.4s, v3.4s
    fmla    v4.4s, v4.4s, v4.4s
    fmla    v5.4s, v5.4s, v5.4s
    fmla    v6.4s, v6.4s, v6.4s
    fmla    v7.4s, v7.4s, v7.4s
    fmla    v8.4s, v8.4s, v8.4s
    fmla    v9.4s, v9.4s, v9.4s
    subs    x0, x0, #1
    bne     .cpufp.aarch64.fp32.L1
    ret

