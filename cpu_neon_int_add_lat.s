.globl cpu_neon_int_add_lat

cpu_neon_int_add_lat:
    eor     x1, x1, x1
.L1:
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    add     x1, x1, x1
    subs    x0, x0, #1
    bne     .L1
    ret

