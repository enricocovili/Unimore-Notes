## Massimo e Minimo

### Definizione massimo
Se A è un insieme tale che $\mathbb A \subseteq \mathbb R$, allora il massimo di A, se esiste, gode delle seguenti proprietà:
$$
\begin{flalign*}
&M = max\space A \iff
\begin{cases}
M \ge a & \forall a \in A\\
M \in A
\end{cases}
&\end{flalign*}
$$
### Definizione minimo
Vale la precedente al contrario
$$
\begin{flalign*}
&m = min\space A \iff
\begin{cases}
m \le a & \forall a \in A\\
m \in A
\end{cases}
&\end{flalign*}
$$
### Osservazioni su massimi e minimi
**esempio**
sia $\mathbb A = \{x \in \mathbb R : x > 0\} = (0,+\infty)$ 
Non c'è ne massimo ne minimo, poiché lo 0 è fuori dall'insieme e non esiste numero maggiore di $+\infty$

Diciamo quindi che: se **M** e **m** esistono, allora sono unici.
**Dimostrazione**: 
Poniamo due massimi in un insieme A, detti $M_1, M_2$. Per le proprietà del massimo, $M_1 \ge M_2$ e $M_2 \ge M_1$. Allora $M_1 = M_2$.

## Maggioranti e Minoranti
Poniamo $\mathbb A \subseteq \mathbb R$

Un numero $L$ si dice **maggiorante** se $L \ge a, \forall a \in A$
Un numero $l$ si dice **minorante** se $l \le a, \forall a \in A$

$\mathbb A$ è **limitato superiormente** se ha dei maggioranti
$\mathbb A$ è **limitato inferiormente** se ha dei minoranti
$\mathbb A$ è **limitato** se ha dei maggioranti e minoranti -> $l \le a \le L, \forall a \in A$

#### Proposizione
Un insieme $\mathbb A$ è limitato se e solo se esiste un numero positivo M tale che $|a| \le M, \forall a \in A$
**Dimostrazione in due versi**: 
prima dimostro che A è limitato, poi che esiste un M che soddisfi le condizioni dell'ipotesi
DIM$_1$ <- se $|a| \le M, \forall a \in A \to -M \le a \le M$ -> quindi A è limitato
DIM$_2$ -> A è limitato $\iff \exists \space l,L \in \mathbb R, l \le a \le L \space \forall a \in \mathbb A$. Prendo il max tra $\{|l|,|L|\}$ e quindi $-M \le l \le a \le L \le M$ -> $|a| \le M \space \forall a \in A$

### teorema dell'esistenza del limite superiore
Sia $\mathbb A \subset \mathbb R, \mathbb A \ne \emptyset$, allora esiste il minimo dei maggioranti
**dimostrazione**:
poniamo $\mathbb B = \{maggioranti\space di\space \mathbb A\}$, poichè A è limitato superiormente
Applichiamo l'**assioma di completezza** e diciamo che A<B.
Inoltre $\exists M \in \mathbb R$ t.c. $a \le M \le b \quad \forall a \in A, \forall b \in B$
se M è maggiore di A, $M \in B$
Per la regola del minimo:
$$
\begin{flalign*}
&M = min\space B \iff
\begin{cases}
m \le b & \forall b \in B\\
m \in B
\end{cases} \quad \to M \space \textrm{è l'estremo superiore di } \mathbb A 
&\end{flalign*}
$$
### altre osservazioni su estremi sup. e inf.

Quindi M è il minimo dei maggioranti ed è il limite superiore di A
$$
\begin{flalign*}
&M = \sup A \iff
\begin{cases}
m \ge a & \forall a \in A\\
\forall \epsilon \exists x \in A: \space 0 + \epsilon > x
\end{cases} \quad \to M \space \textrm{è l'estremo superiore di } \mathbb A 
&\end{flalign*}
$$
Stesso discorso per il limite inferiore
$$
\begin{flalign*}
&m = \inf A \iff
\begin{cases}
m \le a & \forall a \in A\\
\forall \epsilon \exists x \in A: \space m - \epsilon > a
\end{cases} \quad \to m \space \textrm{è l'estremo inferiore di } \mathbb A 
&\end{flalign*}
$$

Se un insieme non è limitato superiormente, si scrive
$\sup \mathbb A = + \infty$
al contrario se non è limitato inferiormente
$\inf \mathbb A = - \infty$

## Successione
Una successione è una funzione $f:\mathbb N \to \mathbb R$
**esempi**:
- $n \to n^2$
- $n \to (-1)^n$
- $n \to \frac{n}{1}$
Cosa **non è** esempio
$n \to \frac{1}{1+(-1)^n}$ perchè è definita solo sui pari ($\frac{1}{1-1}=\frac{1}{0}$) -> impossibile
