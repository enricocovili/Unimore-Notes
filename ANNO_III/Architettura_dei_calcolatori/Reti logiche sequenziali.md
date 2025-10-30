### Definizione
Il risultato dipende da ingressi e dagli stati precedenti
La funzione di commutazione z non dipende solo dalla struttura ma anche dal tempo
Sono l'elemento di base per il funzionamento della memoria.
I registri ne sono un esempio: memorizzano i risultati di un'altra rete combinatoria (l'ALU)
![[Pasted image 20251014114838.png]]
### Clock
Serve per trasformare una rete asincrona in una sincrona (il clock funge da "master" per la sincronizzazione)
Serve anche per ridurre il problema del transitorio: leggo un valore solo quando so che è valido (ritardo). "Risolve" il problema delle [[Reti logiche sequenziali#Alee]] dinamiche.
![[Pasted image 20251014114939.png]]

### Tempo di propagazione
E' il tempo impiegato per la propagazione di un input nell'output. Essenziali per capire qual'è la massima frequenza di lavoro di una rete logica, specialmente se sequenziale.
![[Pasted image 20251014120143.png]]

### Alee
Anche detto glitch, è un impulso indesiderato. L'effetto è un risultato diverso da quello posseduto a regime.
Una rete logica affetta da glitch è caratterizzata da un'alea (hazard).
Alcune volte sono eliminabili tramite sintesi opportune, altre no.
- **STATICHE**  🡒 ad un cambiamento dell'ingresso c'è un cambio nell'uscita, anche se doveva rimanere costante
- **DINAMICHE**  🡒 cambi di valore multipli durante il transitorio

### Elementi di memoria
Di base sono bistabili, capaci di mantenere 0 o 1.

#### Bistabile asincrono (SET-RESET)
Contiene una variabile in stato binario e commuta in presenza di un opportuno ingresso.
![[Pasted image 20251014120558.png]]
1,1 è una combinazione proibita (non so cosa succede se SET e RESET sono attivati assieme)
La prima riga descrive il comportamento di memoria: **l'output è quello dell'istante precedente.**

![[Pasted image 20251014121209.png]]
![[Pasted image 20251014121255.png]]
Ma solitamente si usa la sintesi a NOR o NAND, per pareggiare i tempi di risposta.
![[Pasted image 20251014121347.png]]
#### LATCH SET RESET con CLOCK
![[Pasted image 20251014121833.png]]
Rete sincrona (comandata dal clock). Rimane il problema della combinazione proibita SET 1 RESET 1. Nel caso succeda, c'è una divergenza (loop 1-0).

#### D-LATCH
![[Pasted image 20251014122115.png]]
**E' risolto il problema della combinazione proibita**: l'input è uno solo.
E' effettivamente l'elemento di base delle memorie statiche.

#### FLIP-FLOP
La transizione avviene soltanto quando il clock transita dallo stato 0 allo stato 1: lavoriamo con il **fronte** e non più con il **livello**.
![[Pasted image 20251014122735.png]]
Il comportamento, rispetto al D LATCH, è diverso: l'**uscita è molto più regolare**.
La produzione di un FLIP-FLOP è più **costosa**.
![[Pasted image 20251014123037.png]]
### Register file
![[Pasted image 20251014123808.png]]

### SRAM
Esempio con RAM 4 parole di 3 bit l'una

![[Drawing 2025-10-20 12.50.03.excalidraw]]

### Sintesi di reti logiche sequenziali
**FSM**  🡒 automi a stati finiti (Finite State Machine)
è una quintupla {X,Z,S,G,F}
X = ingressi
Z = uscite
S = stati interni
G = funzione combinatoria per il passaggio allo stato futuro
F = funzione combinatoria per il valore delle uscite in base allo stato interno

#### Modello di Mealy
F complessa ma meno stati
![[Pasted image 20251020130927.png]]

#### Modello di Moore
F più semplice, ma ho più stati
![[Pasted image 20251020131132.png]]

I due modelli sono intercambiabili.

#### Metodo di sintesi
1. Descrivere il comportamento del sistema (specifiche).
2. Definire il diagramma degli stati e le transizioni.
3. Tradurre in tabella di flusso per definire stati e transizioni interne.
4. Minimizzare gli stati manualmente o con algoritmi.
5. Codificare gli stati per ottenere le tabelle di transizione e di uscita.
6. Realizzare la rete logica con bistabili e porte logiche scelte.

#### Esempio: distributore di bibite (Tramite mealy)
4 stati, 3 monete accettate (0c, 10c, 20c). 2 output possibili (0 bibite, 1 bibita).
Inizio allo stato S0.
a 30c da in output una bibita.
![[Pasted image 20251020132941.png]]
Qui S3 è _inutile_. si composta come S0, quindi può essere eliminato e il numero totale di stati può essere ridotto (minimizzazione degli stati). S3 è **equivalente** a S0.

#### Tabella di flusso
![[Pasted image 20251020133709.png]]
ha corrispondenza 1 a 1 con il diagramma a stati

#### Codifica
##### Tabella delle transizioni
In realtà sono tabelle di verità, solo scritte sotto forma di mappe di karnaough per comodità (salto di un passaggio)s
##### Tabella delle uscite
Si usano anche le mappe di karnaough, come per le reti logiche combinatorie

Raccolgo gli 1 o gli 0 in base alla codifica interessata. la scelta è lasciata a chi disegna la rete.

#### Esempio: orologio countdown 5 - 0
