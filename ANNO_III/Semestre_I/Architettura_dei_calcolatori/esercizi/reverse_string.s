# reverse a string
# x10 contains pointer
# x11 reverse pointer

addi x10, x0, 4
addi x5, x0, 'H'
sb x5, 0(x10)
addi x5, x0, 'e'
sb x5, 1(x10)
addi x5, x0, 'l'
sb x5, 2(x10)
addi x5, x0, 'l'
sb x5, 3(x10)
addi x5, x0, 'o'
sb x5, 4(x10)

add x11, x10, x04

get_str_len:
    lb x5, 0(x11)
    beq x5, x0, end_str_len
    addi x11, x11, 1
    j get_str_len

end_str_len:
    addi x11, x11, -1 # go back 1 char from terminator

loop:
    bge x10, x11, done

    #swap
    lb x5, 0(x10) # temp var
    # Store the value at x11 into a temporary register
    lb x6, 0(x11) # Load the value pointed by x11 into x6
    sb x5, 0(x11) # Store the byte from x5 into the address pointed by x10
    sb x6, 0(x10) # Store the byte from x6 into the address pointed by x11

    # increment shit
    addi x10, x10, 1
    addi x11, x11, -1

    j loop

done:
    ret