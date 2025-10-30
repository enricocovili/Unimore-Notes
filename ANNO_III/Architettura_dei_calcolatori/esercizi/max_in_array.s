.text

addi x11, x0, 5
.data
array:
.word 1, 2, 7, 4, 5
.text
la x10, array

find_max:
    # x10 = base, x11 = length
    beq     x11, x0, zero_len    # if length == 0  🡒 return 0

    lw      x12, 0(x10)          # x12 = max = a[0]
    addi    x13, x0, 1           # i = 1
    addi    x15, x10, 4          # addr = base + 4

loop:
    beq     x13, x11, done       # if i == length  🡒 done
    lw      x14, 0(x15)          # x14 = current element
    blt     x12, x14, set_max    # if max < cur  🡒 update max
    # else
    addi    x13, x13, 1
    addi    x15, x15, 4
    j       loop

set_max:
    add     x12, x14, x0         # x12 = x14
    addi    x13, x13, 1
    addi    x15, x15, 4
    j       loop

done:
    ret

zero_len:
    addi    x10, x0, 0
    ret
