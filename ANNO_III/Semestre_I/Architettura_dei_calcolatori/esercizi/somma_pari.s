addi    x11, x0, 5 # lunghezza array

# sezione somme
addi    x5, x0, 1
sw      x5, 0(x10)
addi    x5, x0, 2
sw      x5, 4(x10)
addi    x5, x0, 7
sw      x5, 8(x10)
addi    x5, x0, 4
sw      x5, 12(x10)
addi    x5, x0, 5
sw      x5, 16(x10)
https://vikunja.enricocovili.com/projects/1/4
beq     x11, x0, zero_len     # se length == 0  🡒 return 0
addi    x12, x0, 0            # x12 = somma = 0
addi    x13, x0, 0            # x13 = i (iteratore) = 0
add     x14, x10, x0          # x14 = indirizzo corrente (iteratore indirizzo)

loop:
    beq     x13, x11, done        # fine se i == length

    lw      x15, 0(x14)           # x15 = elemento corrente
    andi    x16, x15, 1           # x16 = bit meno significativo
    bne     x16, x0, skip         # se dispari  🡒 salta

    add     x12, x12, x15         # somma += elemento

skip:
    addi    x13, x13, 1           # i++
    addi    x14, x14, 4           # prossimo indirizzo
    j       loop

done:
    add     x10, x12, x0          # risultato in x10

zero_len:
    addi    x10, x0, 0
