

### Amplificatori TriState
con X in input l'uscita Z è ad alta impedenza, che corrisponde a un circuito chiuso.
![[Pasted image 20251020113125.png]]
In elettronica sono noti come _pass transistors_.
Ci permettono di costruire dei multiplexer distribuiti senza l'uso di un multiplexer. Il vantaggio è di usare due transistor al posto di una classica rete multiplexer. E' necessaria la certezza che solo uno dei transistor sei attivo. 
Si usa in quasi tutti i collegamenti per i bus: scrittura, lettura oppure non fare niente. (riduce consumo)

### Comparatore
![[Pasted image 20251020114542.png]]
I vari ingressi Ai e Bi sono i bit
### Half adder

### ALU
L'alu lavora in parallelo: in realtà è solo il multiplexer che dice "attiva questo" e poi noi ricaviamo dall'operazione solo il risultato interessato.
Negli esempi abbiamo visto ALU cablate, cioè con tutte le reti logiche hardware.
SI è poi passato ad usare le ALU microprogrammate (microcode). Attualmente il trend è però tornato all'hard wiring.
### Full adder

#### N bit adder
Inserisco in cascata gli adder, i CarryOut di quello precedente diventano il CarryIn di quello successivo.
Il problema è il **ritardo**: diventa ritardo * 3 (livelli in un full hadder per arrivare al carryOut) * n.
Nella realtà il circuito è fatto ad albero per trovare un punto di incontro tra ritardo e complessità del circuito.ls

### Sottrazione
B negato e A in un full-hadder, con carryIn forzato a 1 (per effettuare il +1 del complemento a 2 nella sottrazione).