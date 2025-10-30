## Pipeline
![[Pasted image 20251021112228.png]]
IF = instruction fetch
- MAR 🡐 PC
- MDR  🡐 M\[MAR\]
- IR  🡐 MDR; PC  🡐 PC+1
ID = instruction decode
- Decode(IR)  # il decoder "capisce" il codice operativo
- ALU(A)  🡐 R\[IR.S1\]; ALU(B)  🡐 R\[IR.S2\]
EX = execute95
- ALUout 🡐 A (IR_opcode) B # IR_opcode è il codice operativo dell'operazione
MEM = memory access
- MAR 🡐 ALUout
- MDR 🡐 M\[MAR\]
WB = registers write back (salvare il risultato in un registro)
- R\[IR_dest\] 🡐 MDR
#### Circuit pipeline
![[Pasted image 20251021112325.png]]