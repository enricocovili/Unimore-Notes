#### **Applicazioni composte**

![placeholder](./imgs/Pasted%20image%2020230921121604.png)

#### **Composizione identica**

![placeholder](./imgs/Pasted%20image%2020230921121648.png)

#### **Operazioni Binarie (interne)**

![placeholder](./imgs/Pasted%20image%2020230921121735.png)

## **Definizione di gruppo**

![placeholder](./imgs/Pasted%20image%2020230921122208.png)
dove $u$ è l'elemento neutro in questione
#### esempi
- ($Z, +$) è un gruppo abeliano (**RICORDARE**: il $+$ non vuol dire per forza somma!!!)
- $(N,*)$ non è un gruppo (non possiamo ottenere l'elemento nullo della moltiplicazione, 1)
- $(Z,*)$ non è un gruppo per lo stesso motivo
- $(Q,*)$ non è un gruppo a causa di 0 (se moltiplichiamo con 0 otteniamo 0 e non l'elemento nullo)
- $(Q-\{0\},*)$ è un gruppo abeliano

Consideriamo $S(X)=\{f:X \to X/f \space biunivoca\}$
$S(X),S(X) \to S(X)$
$f,g \to g \circ f$
$(S(X),\circ)$ è un gruppo? si, ma non abeliano
1. E' associativa perchè l'applicazione è biunivoca
2. L'elemento neutro è $Id_x$ (guardare [placeholder](Strutture Algebriche#**Composizione identica**))
3. $\forall f \in S(x) \space \exists f' \in S(x)$ tale che $f^{-1}\circ f = f\circ f^{-1} = Id_x$

In questo caso S(X) è abeliano con meno di 3 elementi

| f:x -> x | f:g -> g |
|----------|----------|
| a -> a   | a -> b   |
| b -> c   | b -> a   |
| c -> b   | c -> c   |


## Definizione di anello
Un anello è composto da:
- Un insieme (A)
- Due operazioni binarie interne

e deve avere le seguenti caratteristiche (es: $(A,+,*)$):
1. (A,+) deve essere un gruppo abeliano
2. Il prodotto (l'ultima op. binaria) deve essere associativo
3. $\forall x,y,z \in A$ il prodotto deve essere associativo ($x*(y+z) = xy+xz$)

Anello esempio: **Anello degli interi** = $(Z,+,-)$

Un anello $(A, +, ·)$ è detto **commutativo** se il prodotto è commutativo.
Un anello $(A, +, ·)$ contenente almeno due elementi è detto **unitario** o con unità se $(A, ·)$ ammette l’elemento neutro, indicato con 1.

## Definizione di campo

Un anello commutativo unitario è detto campo se ogni elemento non nullo (della prima operazione binaria) è invertibile rispetto alla seconda operazione

## Esempi di campi e anelli

$(Z,+,-)$ non è campo
$(Q,+,*)$ è campo

$n \in N$
$Z_n = \{\overline 0,\overline 1,\overline 2,... \overline {n-1}\}$ e definisco l'operazione $\triangle$ (resto divisione per n di a+b)
Con n=4:
- $\overline1 \triangle \overline 1 = \overline 2$
- $\overline 2 \triangle \overline 2 = \overline 0$

($Z_n,\triangle$) è gruppo
l'opposto di $m \in Z_n$ è n-m

Stessa cosa si può fare con il prodotto
definisco $\square$ l'operazione di divisione per n di a\*b
- $\overline2 \square \overline 3 = \overline 2$

$(Z_n,\triangle,\square)$ è un anello commutativo con unità, ed è campo solo se n è primo perchè:
$n = p*q, \overline p * \overline q = \overline 0$, ci sarà almeno una coppia di numeri che daranno resto 0.



### Algebra di Boole (le proprietà non sono da sapere)
![placeholder](./imgs/Pasted%20image%2020230921161126.png)

### Sottostrutture
Le sottostrutture sono strutture algebriche che godono delle stesse proprietà della struttura padre.
Il controllo fondamentale da effettuare è che l'operazione interna rimanga interna nella sottostruttura

### omomorfismo e isomorfismo
![placeholder](./imgs/Pasted%20image%2020230921161424.png)
In poche parole, se applico l'operazione binaria interna prima di spostare gli elementi nel sottogruppo, il risultato è uguale.

#### esempio:
funzione esponenziale è isomorfismo: $\exp_a({x+y}) = \exp{a}^{x+y} = a^x*a^y$ 

### dimostrazione della legge dell'annullamento del prodotto
$K$ è un campo
**ipotesi**: $\forall a,b \in K-\{0\}, a*b\ne 0$
**dimostrazione**: 
poniamo $a\ne0$
sa $K$ è un campo, allora $a^{-1}\in K$
moltiplico per $a^{-1}$
$a*a^{-1}*b=0*a^{-1}$, semplifico a
$b = 0*a^{-1}$
$b = 0$ verificata

### Parti di insiemi
poniamo X=insieme
definisco $P(X)=\{Y\subset X\}$ cioè **insieme delle parti** o **insieme dei sottoinsiemi** di X
$P(X):P(X)\to P(X)$
$A:B\to A \cup B$
ne $(P(X),\cup)$ ne $(P(X),\cap)$ sono gruppi

## n-ple
K è un campo
![placeholder](./imgs/Pasted%20image%2020230921163416.png)
### Permutazioni di n-ple
Si dice $S_n$ l'insieme delle permutazioni di su $\mathbb N_n$ ($n!$ elementi)

es:
$p \in S_n, I_n = \{(i,j) \in \mathbb N_m x \mathbb N_n | i<j\}$
Coppie di valori dove i è minore di j

Il **segno** di una permutazione è dipendente dal numero di spostamenti che abbiamo eseguito per trovare la permutazione stessa: $sign(p) = (-1)^{n(p)}$
Numero permutazioni dispari, segno negativo, altrimenti positivo.

E' detta trasposizione o scambio una permutazione in cui è stato effettuato un solo spostamento tra valori. Il segno è negativo $p(n) = 1$
### Combinazione lineare
![placeholder](./imgs/Pasted%20image%2020230921163745.png)

### Anello di polinomi
![placeholder](./imgs/Pasted%20image%2020230921164008.png)