li x10, 0x0f0f

# Function count_bits
# Arguments:
#   x10: a 32-bit number
# Outputs:
#   x10: Number of 0-bits
#   x11: Number of 1-bits

count_bits:
    addi x11, x0, 0      # Initialize counter for 1-bits
    addi x12, x0, 0      # Initialize counter for 0-bits
    addi x5, x0, 32      # 32 iterations for a 32-bit number

loop:
    beq x5, zero, end_loop  # End loop if all bits processed

    andi x6, x10, 1     # Check the least significant bit
    beq x6, x0, zero_bit  # Jump to zero_bit if the bit is 0

    addi x11, x11, 1     # Increment 1-bit counter (if not jumped)
    j next_bit

zero_bit:
    addi x12, x12, 1     # Increment 0-bit counter

next_bit:
    srli x10, x10, 1      # Shift bits right by 1
    addi x5, x5, -1    # Decrement bit counter
    j loop

end_loop:
    add x10, x0, x12   # Set x10 to number of 0-bits
    add x11, x0, x11   # Set x11 to number of 1-bits
    ret