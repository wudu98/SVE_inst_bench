.globl cpu_fp32_lat_kernel_aarch64

cpu_fp32_lat_kernel_aarch64:
    eor    v0.16b, v0.16b, v0.16b 
.cpufp.aarch64.fp32.L1:
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    fmla    v0.4s, v0.4s, v0.4s
    subs    x0, x0, #1
    bne     .cpufp.aarch64.fp32.L1
    ret

