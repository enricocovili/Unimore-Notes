# Fondamenti del Livello Host-to-Network (H2N)

Il livello Host-to-Network (H2N) costituisce il substrato materiale del modello TCP/IP, definendo le modalità di interconnessione e trasmissione dati tra host direttamente adiacenti. Sotto il profilo architettonico, la scelta tecnologica a questo livello non è neutrale: essa impone vincoli deterministici o non-deterministici che ricadono sugli strati superiori. Se il livello H2N adotta un approccio "best-effort" e non-deterministico (come l'Ethernet classico), l'onere della garanzia di affidabilità deve necessariamente traslare verso l'alto, obbligando il livello Transport (TCP) a implementare robusti meccanismi di Error Control. Al contrario, un H2N deterministico permetterebbe protocolli superiori più snelli, ma a costi di infrastruttura e complessità gestionale sensibilmente più elevati.

Le finalità del livello H2N si articolano in due domini distinti:

* **Livello 1 (Fisico)**: Definisce le specifiche dell'hardware, inclusi i mezzi trasmissivi (doppino, fibra, radio), il layout dei connettori, i voltaggi per i segnali elettrici, le lunghezze d'onda per l'ottica e le frequenze di modulazione.
* **Livello 2 (Data Link)**: Gestisce l'incapsulamento dei pacchetti in frame, il controllo dell'accesso al mezzo (gestione della resource contention), il controllo di flusso e la rilevazione/correzione degli errori.

| Tipologia di Rete | Esempi di Tecnologie |
|---|---|
| LAN Cablate | Ethernet (IEEE 802.3), Token-ring, FDDI, Frame Relay |
| LAN Wireless | Standard IEEE 802.11x (a, b, g, n, ac, ax) |
| Linee Seriali | SLIP, PPP |

Mentre il livello IP garantisce la consegna globale, il livello H2N opera esclusivamente sul singolo link (host-router, router-router), isolando le specificità tecnologiche locali dai protocolli di rete e trasporto.

# Ethernet: Lo Standard De Facto della Connettività LAN

Ethernet si è imposta come standard dominante non per una superiorità teorica assoluta, ma per la sua natura economica e l'eccezionale adattabilità al modello TCP/IP. Originariamente concepita per canali di tipo broadcast, Ethernet delega la gestione della comunicazione all'indirizzo MAC (Media Access Control) a 48 bit, memorizzato stabilmente nella ROM delle Network Interface Card (NIC).

L'indirizzo MAC è suddiviso in 3 byte di OUI (identificativo del produttore assegnato dall'IEEE) e 3 byte di NIC ID univoco. Dal punto di vista sistemistico, l'indirizzo IP da solo non è sufficiente a livello hardware: l'uso del MAC permette alla NIC di filtrare i pacchetti in transito in modo autonomo. Senza questa distinzione, ogni frame sulla LAN genererebbe un interrupt alla CPU dell'host per verificare la corrispondenza dell'indirizzo IP, causando un overhead di sistema insostenibile.

## Frame ethernet

1. **Preambolo** (8 byte): I primi 7 byte (sequenza 10101010) servono a stabilizzare il clock dei ricevitori; l'8° byte (SFD, sequenza 10101011) segnala l'inizio effettivo del frame.
2. **Indirizzi MAC** (Destinazione/Sorgente): 6 byte ciascuno.
3. **Type** (2 byte): Identifica il protocollo superiore (es. IP=0x0800, ARP=0x0806).
4. **Payload** (Data): Compreso tra 46 e 1500 byte (MTU). Se i dati sono inferiori a 46 byte, viene applicato un padding per garantire la rilevazione delle collisioni.
5. **CRC** (4 byte): Controllo di ridondanza ciclico per garantire l'integrità dei dati.

## ARP e RARP per l'indirizzamento

La coesistenza tra indirizzamento logico (IP) e fisico (MAC) richiede un'interfaccia dinamica. Il protocollo ARP (Address Resolution Protocol) mappa queste due entità all'interno di una LAN. Quando un host conosce l'IP target ma non il MAC, invia una ARP Query in broadcast (FF:FF:FF:FF:FF:FF); l'host corrispondente risponde in unicast con una ARP Response.

Per minimizzare il traffico broadcast, gli host implementano una ARP Cache con un meccanismo di self-learning: ogni volta che viene ricevuta una risposta o osservata una query, l'host aggiorna la propria tabella locale. In scenari specifici (sistemi diskless), il protocollo RARP permette a un host di ottenere il proprio IP partendo dal MAC address tramite un server dedicato.

Il pacchetto ARP/RARP (28 byte) presenta campi tecnici precisi:

### Frame ARP/RARP

* **Hardware Type** (HT): Valore 1 per Ethernet.
* **Protocol Type** (PT): Valore 0x0800 per il protocollo IP.
* **Hardware Size** (HS) / **Protocol Size** (PS): Rispettivamente 6 e 4 byte.
* **Operation** (OP): 1 (Request), 2 (Response), 3 (RARP Req), 4 (RARP Resp).

# Dispositivi di Interconnessione: Hub, Bridge e Switch

L'evoluzione dei dispositivi di interconnessione risponde alla necessità di isolare i domini di collisione per scalare le prestazioni.

* **Hub** (Livello 1): Semplice ripetitore; propaga i segnali elettrici su tutte le porte, massimizzando la probabilità di collisione e limitando il throughput totale.
* **Bridge** (Livello 2): Dispositivo intelligente che opera sui frame. Il suo funzionamento si basa sul self-learning: quando riceve un frame sulla Porta A, il bridge analizza il MAC sorgente e lo associa a tale porta in una filtering table con un relativo TTL. Successivamente, ispeziona il MAC destinazione: se è presente in tabella, inoltra il frame solo sulla porta corretta; altrimenti, effettua il flooding su tutte le porte tranne quella di ingresso.
* **Switch**: Bridge hardware ad alte prestazioni che supporta interfacce multiple. Implementa lo switching Store-and-forward (verifica il CRC prima dell'inoltro, maggiore latenza) o Cut-through (inoltro immediato dopo la lettura del MAC destinazione, minore latenza ma rischio di propagazione di frame corrotti).

Per evitare loop infiniti in topologie ridondanti, i bridge implementano il protocollo Spanning Tree, che disabilita logicamente i percorsi ciclici.

### Bridge in Linux

In ambiente Linux, è possibile configurare un bridge software per interconnettere interfacce fisiche o virtuali (fondamentale per VM e Container):

#### Comandi operativi:

Creazione del bridge

```brctl addbr br0```

In alternativa con iproute2:

```ip link add br0 type bridge```

Aggiunta di interfacce fisiche

``` brctl addif br0 eth0 ```

``` brctl addif br0 eth1 ```

Verifica delle tabelle MAC apprese

```brctl showmacs br0```


Configurazione persistente (Debian-style /etc/network/interfaces):

```
auto br0
iface br0 inet static
    bridge_ports eth0 eth1
    address 192.168.1.10
    netmask 255.255.255.0
```


# Virtual LAN (VLAN) e lo Standard 802.1Q

La segmentazione fisica tramite switch ha raggiunto col tempo un limite di efficienza ("port waste"), portando all'astrazione logica delle VLAN. Lo standard IEEE 802.1Q permette la coesistenza di più reti logiche sulla stessa infrastruttura fisica, garantendo sicurezza e confinamento del traffico broadcast.

Il frame 802.1Q introduce un tag di 4 byte che include:

* **TPI** (Tag Protocol Identifier): Valore 0x8100 per identificare lo standard.
* **TCI** (Tag Control Information): Suddiviso in User Priority (3 bit per il QoS), CFI (1 bit per compatibilità Token Ring) e VID (VLAN ID, 12 bit).
* **VID** (VLAN ID): Supporta fino a 4094 identificativi (i valori 0 e 4095 sono riservati).

Le porte si distinguono in Access (untagged, per host finali) e Trunk (tagged, per collegamenti tra switch). Gli ISP utilizzano spesso il Double Tagging (802.1AD), inserendo un S-Tag (Service Tag) sopra il C-Tag del cliente per gestire infrastrutture multi-tenant. La sicurezza degli apparati è garantita dalla Management VLAN, isolata dal traffico dati ordinario.


## IP Datagram e Servizi di Rete

L'header IP (minimo 20 byte) agisce come una "busta intelligente". Tra i campi principali:

* Version: IPv4.
* **TOS** (Type of Service): Evolutosi nel moderno DSCP (Differentiated Services Code Point, 6 bit per la priorità) e ECN (Explicit Congestion Notification, 2 bit per segnalare saturazione senza scartare pacchetti).
* **Identification/Flags/Fragment Offset**: Gestiscono la frammentazione quando un datagramma supera l'MTU del link fisico.
* **TTL** (Time To Live): Non è una misura temporale, ma un contatore di hop. Ogni router decrementa il valore di 1; a zero, il pacchetto viene scartato, prevenendo loop infiniti a livello 3.
* **Checksum**: Verifica l'integrità del solo header.

I servizi IP sono rigorosamente connectionless e inaffidabili: la rete non garantisce né l'ordine né la consegna, lasciando tali compiti agli strati superiori.

# Indirizzamento IP: Classi, Gerarchie e Gestione

L'indirizzamento IP a 32 bit segue una logica gerarchica <NetID, HostID>. Storicamente, l'allocazione era basata su classi rigide, gestite da IANA e ICANN sotto la supervisione storica di Jon Postel (il "Tsar dei numeri").

| Classe | Bit Iniziali | NetID | Host ID Supportati (2^n - 2) | Range IP |
|---|---|---|---|---|
| A | 0 | 1 byte | 16.777.214 | 0.0.0.0 - 127.255.255.255 |
| B | 10 | 2 byte | 65.534 | 128.0.0.0 - 191.255.255.255 |
| C | 110 | 3 byte | 254 | 192.0.0.0 - 223.255.255.255 |

La rigidità di questo sistema è evidente guardando ai possessori storici di interi blocchi di Classe A, come IBM, Apple, Ford e il DoD (Department of Defense). 
È essenziale notare che l'indirizzo IP è assegnato all'interfaccia (NIC) e non all'host fisico. Esistono indirizzi speciali: Loopback (127.0.0.1), indirizzo di Rete (HostID = 0) e indirizzo di Broadcast (HostID = 1).

## Ottimizzazione della Rete: Subnetting e Supernetting

Per superare la rigidità delle classi e l'esaurimento degli indirizzi, si è passati da una divisione a byte a una divisione logica a bit.

* **Subnetting**: Permette di frammentare un NetID in sottoreti più piccole tramite la Network Mask. Un'operazione logica AND tra l'indirizzo IP e la maschera permette di estrarre il Subnet ID. Questo abilita il routing gerarchico: i router esterni ignorano la struttura interna delle sottoreti, mentre i router locali utilizzano la maschera per l'instradamento granulare.
* **Supernetting** (CIDR): Approccio opposto, utilizzato dagli ISP per aggregare blocchi contigui di Classe C in un'unica entità logica, riducendo drasticamente la dimensione delle tabelle di routing globali. Ad esempio, una maschera /26 indica che 26 bit sono riservati alla rete, lasciandone 6 per gli host (62 indirizzi utili).


# Livello 4: Trasporto

Il livello di trasporto costituisce il baricentro dell'architettura TCP/IP, operando una trasformazione fondamentale: eleva il servizio di consegna "host-to-host" offerto dal protocollo IP (Layer 3) a una comunicazione "process-to-process". Da un punto di vista architetturale, il Layer 4 risiede nel Kernel del Sistema Operativo, fungendo da interfaccia critica tra lo User Space (dove operano le applicazioni) e i driver di basso livello e l'hardware (Layer 1 e 2). Questa posizione strategica permette di astrarre la complessità della rete sottostante, offrendo ai processi applicativi un canale di comunicazione logico indipendente dalla topologia fisica.

È un errore concettuale comune identificare il livello di trasporto esclusivamente con il protocollo TCP. La suite TCP/IP include necessariamente anche l'UDP (User Datagram Protocol). Sebbene IP fornisca l'instradamento, il Layer 4 introduce servizi essenziali comuni a entrambi i protocolli, quali il multiplexing/demultiplexing dei messaggi e il rilevamento degli errori tramite checksum. Questi meccanismi garantiscono l'integrità minima necessaria affinché i dati siano recapitati al socket corretto e non risultino palesemente corrotti.

Tuttavia, per applicazioni che richiedono garanzie superiori al "best effort", TCP implementa una suite di servizi aggiuntivi:

* **Trasferimento dati affidabile**: garantisce la consegna di ogni singolo byte.
* **Controllo di flusso**: regola la velocità di invio per non saturare il ricevitore.
* **Sequenziamento**: garantisce l'ordine corretto dei byte tramite numeri di sequenza.
* **Controllo della congestione**: adatta il throughput allo stato di carico della rete globale.

Questa distinzione poggia sulla capacità del trasporto di identificare i processi mediante l'architettura delle porte.

## Multiplexing, Demultiplexing e l'Architettura delle Porte

Il multiplexing permette a molteplici applicazioni di condividere un unico indirizzo IP. Il "punto di accesso" logico è la porta, un identificativo a 16 bit (range 0-65535). Tecnicamente, il multiplexing avviene lato mittente, raccogliendo i dati dai vari socket e incapsulandoli in segmenti con header specifici; il demultiplexing avviene lato ricevente, dove il sistema operativo esamina i campi delle porte per smistare il segmento al processo corretto.

Le porte sono classificate secondo tre categorie IANA:

1. **Well Known Ports** (0-1023): riservate a servizi standard (es. HTTP, SSH), utilizzabili tipicamente solo con privilegi di root.
2. **Registered Ports** (1024-49151): destinate a servizi specifici previa registrazione.
3. **Dynamic/Private Ports** (49152-65535): utilizzate dai client per connessioni effimere.

Per distinguere processi identici in esecuzione simultanea o più client che accedono allo stesso servizio, non basta la porta di destinazione. È necessaria l'intera tupla di identificazione: (IP sorgente, porta sorgente, IP destinazione, porta destinazione).

Esempi:
| Protocollo Standard | Porta | Descrizione |
|---|---|---|
| SSH | 22 | Accesso remoto sicuro |
| SMTP | 25 | Trasferimento email |
| DNS | 53 | Risoluzione nomi (Query via UDP) |
| HTTP | 80 | Navigazione Web |

Il protocollo più snello che utilizza questa architettura è l'UDP.

## Il Protocollo UDP (User Datagram Protocol)

Definito nella RFC 768, l'UDP è un protocollo "connectionless" e "lightweight". È la scelta d'elezione quando la latenza ridotta è preferibile alla garanzia di consegna, poiché non introduce ritardi dovuti all'handshaking o al mantenimento di uno stato della connessione (permettendo a un server di supportare un numero maggiore di sessioni attive). UDP tratta ogni segmento in modo indipendente, operando secondo una filosofia "best effort": i dati possono essere persi, duplicati o giungere fuori ordine.

L'header UDP è di soli 8 byte, contenente porte, lunghezza e checksum.

### Rilevamento errori e pseudo-header

UDP garantisce l'integrità end-to-end tramite il checksum. Per il calcolo, viene creato uno pseudo-header (non trasmesso) che include indirizzi IP sorgente/destinazione e il campo protocollo. Questa è una violazione intenzionale del principio di indipendenza tra livelli: il Layer 4 deve "conoscere" i dettagli del Layer 3 per assicurarsi che il datagramma sia giunto all'host corretto.

L'algoritmo utilizza la somma in complemento a 1 dei campi a 16 bit. Il destinatario esegue la somma totale (inclusi i dati e il checksum stesso): se il risultato è una sequenza di soli '1' (1111111111111111), il segmento è considerato integro.

## Teoria del Trasferimento Dati Affidabile

Costruire un canale affidabile su un supporto intrinsecamente inaffidabile richiede la gestione di tre scenari critici tramite protocolli di tipo Stop-and-Wait.

### Scenari di Errore e Risposte

1. **Corruzione del Messaggio**. Gestito tramite checksum e riscontri (ACK per conferma, NAK per errore).
2. **Corruzione del Riscontro (ACK)**. Per evitare duplicati, si introducono i numeri di sequenza. Se l'ACK è corrotto, il mittente ritrasmette; il ricevitore, riconoscendo il numero di sequenza, scarta il duplicato e invia nuovamente l'ACK.
3. **Perdita del Messaggio**. Si introduce un timer (timeout). Se l'ACK non arriva entro l'intervallo stabilito, il mittente presume la perdita e re-invia.

### Inefficienza dello Stop-and-Wait e Pipelining


Nonostante sia affidabile, lo Stop-and-Wait è inefficiente. Con un link a 1 Gbps, RTT di 30ms e pacchetti da 1KB, l'utilizzazione U è:

```
T = (8000 bit) / (10^9 bps) = 0.008 ms
U = T / (RTT + T) = 0.008 / 30.008 ≈ 0.027%
```

Per ovviare a questo spreco (0.027% di banda utilizzata), si introduce il Pipelining, dove il mittente invia molteplici segmenti prima di attendere un ACK. Questo richiede due modelli teorici principali:

1. **Go-Back-N (GBN)**: Utilizza ACK cumulativi. Se un pacchetto i va in timeout, il mittente ritrasmette i e tutti i successivi. Il ricevitore scarta i pacchetti fuori ordine.
2. **Selective Retransmission (SR)**: Il ricevitore bufferizza i pacchetti fuori ordine e invia ACK singoli. Il mittente ritrasmette solo i segmenti mancanti.

##  Il Protocollo TCP: Architettura e Ciclo di Vita

TCP (RFC 793) realizza un'astrazione di byte-stream full-duplex. Per le applicazioni, la comunicazione è un flusso continuo di byte, gestito dal TCP tramite buffering e segmentazione. Un meccanismo fondamentale è il Piggybacking, che permette di includere informazioni di controllo (ACK) all'interno di segmenti contenenti dati utente nella direzione opposta.

### Header TCP

* **Sequence Number**: Posizione del primo byte del segmento nel flusso.
* **Acknowledgment Number**: Il numero del prossimo byte atteso (ACK cumulativo).
* **Flags**: SYN, FIN, ACK, RST, PSH, URG.
* **Urgent Pointer**: Utilizzato per i dati urgenti (out-of-band); il puntatore indica la fine del blocco urgente, che viene consegnato immediatamente bypassando il buffer di stream regolare.

### Connessione e Three-way Handshake

La sincronizzazione avviene tramite il Three-way Handshake:

1. **SYN**: Il client invia il proprio Initial Sequence Number (ISN), scelto pseudo-casualmente per sicurezza.
2. **SYN-ACK**: Il server risponde con il proprio ISN e ACK = ISN_{client} + 1.
3. **ACK**: Il client conferma ACK = ISN_{server} + 1.

La chiusura è "polite" (educata) tramite flag FIN. Dopo l'ultimo ACK, il client entra in stato TIME_WAIT (tipicamente 30-120s) per gestire eventuali segmenti ritardati o la perdita dell'ultimo ACK, evitando che vecchi dati interferiscano con nuove connessioni.

## Gestione dei Buffer e Controllo di Flusso

Il buffering è essenziale per gestire l'asincronia tra la velocità dell'applicazione e quella della rete. Per evitare che un mittente rapido sovraccarichi un ricevitore lento, TCP implementa il Controllo di Flusso tramite il meccanismo della finestra scorrevole.

### Sliding Window e Advertised Window


Il ricevitore comunica la **Advertised Window** (AW), lo spazio libero nel buffer:

```
AW = MaxRcvBuffer - ((NextByteExpected - 1) - LastByteRead)
```

Il mittente calcola la **Effective Window** (EW) per limitare l'invio:

```
EW = AW - (LastByteSent - LastByteAcked)
```

**Invarianti di correttezza:**

- **Lato Mittente:** `LastSegmentSent - LastAckReceived ≤ SenderWindowSize`
- **Lato Ricevente:** `LargestAcceptableSegment - LastSegmentReceived ≤ ReceiverWindowSize`


In caso di AW=0, il mittente invia periodicamente segmenti da 1 byte per sollecitare aggiornamenti. Per prevenire la Sindrome della Finestra Sciocca, il ricevitore attende che si liberi almeno il 50% del buffer prima di annunciare una nuova finestra.

### Controllo della Congestione: Algoritmi e Strategie

Il controllo della congestione protegge la rete tramite l'approccio AIMD (Additive Increase, Multiplicative Decrease). TCP regola la velocità tramite la Congestion Window (CW), inviando un quantitativo di dati pari a `min(AW, CW)`.

#### Algoritmi Reattivi: Tahoe e Reno

- **TCP Tahoe**: In caso di perdita (timeout), dimezza la soglia (Threshold) e resetta `CW=1`, ripartendo con lo Slow Start (crescita esponenziale).
- **TCP Reno**: Introduce la Fast Recovery. Se riceve tre ACK duplicati (segno che la rete trasmette ma un pacchetto è perso), non azzera la finestra ma la dimezza (`CW = CW/2`), proseguendo con una crescita lineare (Congestion Avoidance).


### Algoritmo Proattivo: TCP Vegas

TCP Vegas è un algoritmo proattivo che cerca di prevenire la congestione osservando le variazioni del RTT. Utilizza la logica della derivata del throughput:

```
X(t) = (WndSize(t) - WndSize(t-1)) / (RTT(t) - RTT(t-1))
```

Se `X(t) > 0`, l'aumento della finestra causa un aumento proporzionale del RTT, segno che i buffer dei router si stanno riempiendo. Vegas riduce quindi la finestra preventivamente. Nonostante la sua efficienza teorica, Vegas è poco diffuso poiché "soccombe" in competizione con Reno, che è più aggressivo nell'occupare banda.


## Evoluzione per Reti Moderne: LFN e CUBIC

Le Long Fat Networks (LFN) (alta banda e alta latenza) rendono i protocolli tradizionali troppo lenti nel recuperare la capacità dopo una perdita.

### Bic e CUBIC

#### TCP BIC

Utilizza un meccanismo di Binary Search in 4 fasi:

1. Additive Increase: Crescita lineare se la finestra è lontana dal target.
2. Binary Search: Salto al punto medio (midpoint) tra la finestra attuale e il massimo precedente (W_{max}).
3. Max Probing: Esplorazione cauta oltre W_{max}.
4. Slow Start: Se viene superato drasticamente il vecchio massimo.

#### TCP CUBIC

TCP CUBIC (default in Linux) semplifica BIC utilizzando una funzione cubica del tempo trascorso dall'ultima congestione:

```
CW = f(t_now - t_last_loss)³
```

Questo rende la crescita della finestra indipendente dal RTT, garantendo stabilità vicino a W_max e aggressività lontano da esso. CUBIC è particolarmente efficace su LFN poiché recupera rapidamente la capacità disponibile dopo una perdita, mantenendo equità con i flussi Reno su reti non congestionate.


### Buffer Bloating

Il Buffer Bloating, studiato estensivamente da David Täht, è l'eccessivo accodamento di pacchetti in router con buffer sovradimensionati. Questo nasconde la congestione al TCP (niente pacchetti persi), ma esplode il RTT, rendendo le applicazioni interattive inutilizzabili. La soluzione risiede in algoritmi di gestione code come CoDel (Controlled Delay).

## Esempi e scelte di protocolli

La scelta del protocollo di trasporto è una decisione architetturale basata sul trade-off tra affidabilità e tempo reale. TCP garantisce la Fairness: se N sessioni condividono un link, l'algoritmo AIMD le porta naturalmente a convergere verso una divisione equa (1/N) della banda.

Esempi:

Applicazione	Protocollo	Giustificazione
| Applicazione | Protocollo | Giustificazione |
|---|---|---|
| Email (SMTP) | TCP | Richiede trasferimento affidabile dei dati. |
| Web (HTTP) | TCP | Necessita di integrità per il rendering dei contenuti. |
| DNS Query | UDP | Overhead minimo; evita i ritardi del 3-way handshake. |
| VoIP / Streaming | UDP | Tollera perdite ma richiede rate costante (no congestion control). |
| NFS | UDP/TCP | Storicamente UDP per velocità; TCP per reti geografiche. |

In sintesi, mentre UDP rimane insostituibile per l'efficienza pura, l'evoluzione di TCP (da Tahoe a CUBIC) dimostra la capacità del Layer 4 di adattarsi a infrastrutture globali sempre più veloci e complesse.
