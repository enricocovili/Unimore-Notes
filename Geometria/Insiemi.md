## Relazione
### definizione
sottoinsieme del prodotto cartesiano tra due insiemi
$AxB = \{(a,b), \forall a \in A, \forall b \in B\}$ -> coppie di elementi in cui il primo appartiene ad A e il secondo a B

## Applicazione o funzione
### definizione
particolare relazione che dice:
$\forall x \in A, \exists ! y \in B, (x;y) \in f$ -> esiste solo una coppia di valori x,y tali che
$f:A \to B$ 
$x \to y = (f(x))$
dove A è il **dominio** e B è il **codominio** dell'applicazione
y = **trasformato** o **immagine** di x

## Immagine
### definizione
$f(X) = \{b \in B | \exists x \in X, f(x)=b\}$
immagine di f: $f = \{y \in D / \exists x \in C, f(x)=y\}$
dove D = dominio e C = codominio

### controimmagine
insieme di $a\forall A$ che hanno corrispondente $b \forall B$
esempio:
$f:R \to R$
$x \to x^2$
controimmagini:
$f^{-1} (9) = \{-3;+3\}$
$f^{-1} (0) = \{0\}$
$f^{-1} (-5) = \emptyset$ (insieme vuoto, perchè -5 non è nell'immagine)



### Postulati / assiomi
definizioni fondamentali della matematica da prendere senza dimostrazione
#### esempi di assiomi:
- numeri $R$ -> proprietà commutativa, associativa...
- ordinamento ($<,>,=$)
- #### assioma di completezza
	- se A e B, insiemi non vuoti di numeri $R$, tali che A $\le$ B $\forall$a $\in$ A, $\forall$b $\in$ B, allora esiste almeno un numero reale c tale che a $\le$ c $\le$ b


### Teoremi / proposizioni / lemmi
definizioni secondarie derivate dagli assiomi tramite procedimenti logici (dimostrazioni)

## Teoria degli insiemi
x -> elemento, S -> insieme
x $\in$ S -> x appartiene a S
x $\notin$ S -> x non appartiene a S
A $\subseteq$ S -> l'insieme A è completamente contenuto nell'insieme S (sottoinsieme di S)
A $\cap$ S = {$x$: $x\in A \land x\in S$} -> appartiene ad A and B
A $\cup$ S = {$x$: $x\in A \lor x\in S$} -> appartiene o ad A or B
A - B = {$x:x\in A \land x\notin B$} -> appartiene ad A e non B
$A^c$ = {$x\in S: x\notin A$} -> A complementare
AxB = {$(a,b): a\in A, b\in B$} -> coppie di elementi tra A e B

### Sottoinsiemi di $R$
- $N$
- $Z$
- $Q$
$N \subseteq Z \subseteq Q \subseteq R \subseteq C$
### proposizione esercizio:
#### Non esiste alcun numero razionale che $c^2 = 2$
_dimostrazione_:
**per assurdo** supponiamo che $c = m/n$; $m,n \in Z$, dove n e m non sono pari
$c^2 = {n\over m}^2 = 2 = {m^2\over n^2}$ => $m^2 = 2n^2$ => $m$ è quindi pari. poniamo $m = 2k$
$m = 2k => m^2 = 4k^2 = 2n^2 => n^2 = 2k^2$
quindi $n$ è pari e abbiamo una contrapposizione (assurdo). $c$ non è razionale.