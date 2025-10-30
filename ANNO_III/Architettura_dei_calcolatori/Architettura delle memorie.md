## Architettura standard
![[Pasted image 20251027112220.png]]
### BUS RDY # signal
Molte volte la memoria non riesce a rispondere in tempo alla richiesta di un dato (la CPU è molto più veloce).
C'è un segnale BUS RDY # (bus ready) di controllo che dice alla CPU di aspettare la risposta della memoria (esempio: la memoria ha bisogno di 6 cicli di clock per rispondere).
Il segnal BUS RDY (Wait nell'immagine) viene controllato dalla rete logica della CU, che sa quanto è veloce la RAM.
![[Pasted image 20251027113126.png]]
### Tipi di memoria
- centrale
- di massa
#### Classificazione
- Capacità
- caratteristiche fisiche
- modalità di accesso
- Organizzazione
- Prestazioni

##### Capacità
**CxM**, dove M è il numero di parole, N la dimensione delle parole. Solitamente N=8 (byte-wide)
Spesso la word è maggiore a causa dei bit di ridondanza.
Esistono codici di rilevazione di errori: bit di parità, oppure di correzione tramite il codice di Hamming. Per questo sono necessari bit aggiuntivi alla parola.
##### Caratteristiche fisiche
- magnetiche
- semiconduttori
- ottiche
- ...
Ma anche _affidabilità_ (MTBF, mean time between failure)
_Alterabilità_, cioè se può essere scritta o no (es ROM)
Durevolezza o _volatilità_, indicano il tempo definito o indefinito di permanenza in memoria (es la RAM è volabile perchè si perde al mancare dell'alimentazione)

##### Modalità di accesso
- sequenziale
	per accedere a un dato **devo** leggere tutti i precedenti
	esempio: nastro
- diretto
	indirizzo una cella e non passo dalle precedenti
	Tacc = Treq + Tstartup + N * Tdato
	esempio: hard disk
- casuale
	Il tempo di accesso è costante
	Solitamente a un indirizzo corrisponde un dato 1:1
	Tacc = Tadd + Tdato (Tdato è il ritardo della memoria)
	esempio: RAM
- associativo
	Controllo nella zona degli indirizzi e da lì passo ai dati, se lo trovo.
	C'è un' associazione tra indirizzo della cpu e zona degli indirizzi. Se non c'è, il dato manca. Sono memorie veloci ma piccolissime. Solitamente usate per i dati frequenti.
	Esempio: Cache
	![[Pasted image 20251028121507.png]]
	L'indirizzo che esce dalla CPU contiene il TAG (primi Nadd-log2(B)) e l'OFFSET (log2(B)).
	La prima parte va a cercare nella cache dir, l'offset va a pescare il dato nella linea corrispondente. (ricorda che c'è una corrispondenza per linea tra cache dir e cache data).
	Ci sono due bit di stato: H/M (Hit or miss, un comparatore con un or e il bit valido della cache) e dirty: quest'ultimo indica se si sta leggendo o scrivendo, per capire se bisogna fare una copia aggiuntiva in memoria centrale (in scrittura).
	Inoltre c'è un bit status (nell'immagine) per capire se è valido o no (esempio: inizialmente tutto è a 0 e non è valido)
	Quando devo scrivere in cache, se è vuota, vado nel primo libero (Miss). Se devo sovrascrivere uso LRU (complicata in HW, elimina il più vecchio) oppure Random.
	E' usata solo nelle cache molto piccole a causa del costo hardware.

#### Memorie non gerarchiche
Classico accesso in serie

#### Memorie gerarchiche
From fast to slow (generalmente proporzionali alla distanza dalla CPU)
![[Pasted image 20251027130720.png]]
La Cache finisce in mezzo: fa da intermediario tra memoria di massa e la CPU.
La cache viene popolata seguendo l'algoritmo LastRecentlyUsed, cioè mantengo i dati più recenti sovrascrivendo quelli di utilizzo meno recente.
Uno dei modelli usati è il **WriteBack**, dove salvo alcuni dati sulla cache. Il lato negativo è che bisogna occuparsi della scrittura sulla memoria centrale quando la cache viene cancellata o rimpiazzata. (Ci saranno discrepanze tra cache e memoria centrale in alcuni momenti).
Un altro è il **WriteThrough**, è più lento ma consente la consistenza di tutte le memoria (scrivo in tutta la gerarchia).
#### Principio di località
- **Temporale**: accedendo ad un dato è assai probabile che si debba accedere nuovamente ad esso in un breve intervallo di tempo ossia in un tempo “localmente vicino”
- **Spaziale**: accedendo ad un dato è assai probabile che si debba accedere ad un dato allocato in uno spazio in memoria localmente vicino.
	Esempio: copio tutta una linea di word al posto di una sola. Questo accelera il processo nel caso io usi questi dati vicini, ma è dannoso in caso contrario (pollution).
	Questo è effettuato in Hardware.
**Località nel codice**: 
Il codice non vede la gerarchia: _considera tutto come memoria centrale_.
Subentra il concetto di **memoria virtuale**: la memoria di massa è usata come cache / centrale.
Questo viene descritto come **paginazione**. Il sistema operativo decide quali blocchi vengono spostati in base alle operazioni richieste dal software.
Le vecchie gerarchie avevano registri, cache L1 e MMU internamente alla CPU.
Cache L2 e memoria centrale erano esterno.
Ora, coi sistemi multi core, le cache sono distribuite con la L3 condivisa.

### Tipi di cache associative
- **Fully associative**
	Quella vista fino ad ora
- **N-way associative**
	
	Clusterizzo le Linee in Set = L / N-way. Indirizzo i cluster con Log2(S).
	Diventa fully associative dentro il set e direct mapped fuori.
	In questo modo trovo un bilancio di prestazioni e hardware (ho un numero S di comparatori)
- **Direct mapped**
	Non sovrascrivere a caso: c'è un'indicizzazione.
	Organizzo i dati in cache in modo che siano ordinabili tramite una funzione di hash.
	Contiene dei bit di index per indirizzare, che sono Log2(L) (categorizzo per Linea).
	L'hit rate è più alto perché è meno general purpose, ma è più lenta causa categorizzazione.
	Si mettono i bit di index come i meno significativi prima dell'offsett per una questione di intervalli (vengono spalmati meglio sulla cache).

### Prestazioni
Blocco: unità di informazione minima scambiata fra livelli (es: 32 bytes) 
**Hit**: un accesso alla memoria che trova l'informazione cercata nel livello superiore. 
**Hit Rate**: frequenza di accessi trovati nel livello superiore (h). 
**Miss Rate**: (1 - h). 
**Hit Time**: tempo di accesso al livello superiore Th. 
**Miss Penalty**: tempo per rimpiazzare un blocco nel livello superiore più il tempo per fornirlo alla CPU. 
Il "miss penalty“ (Tmp) può anche essere scomposto nei tempi per reperire il primo dato di un blocco più il tempo per trasferire gli altri. 
Comprende certamente un Th e un “overhead” nel caso di miss (Tmiss). 
Tacc = h Th + (1-h)Tmp 
**Tacc** = Th + (1-h)Tmiss 
Questo perche’ Tacc= hTh+(1-h)(Th+tmiss) = hTh+Th –hTh+(1-h)Tmiss

Occhio ad avere pagine troppo ampie: si palesa il fenomeno del **pollution**, e il missrate ricomincia ad aumentare
![[Pasted image 20251028125128.png]]
Oggi si usa la **Split cache**, una per i dati e una per le istruzioni.