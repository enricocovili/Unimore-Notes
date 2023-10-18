### tipi di funzioni
- #### suriettiva
	- $\forall b \in B, \exists a \in A, f(a)=b$
	- l'immagine copre tutto l'insieme B
 ![[Pasted image 20230919100311.png]]
- #### iniettiva
	- $(f(a') = f(a^") \to (a'=a^"))$
	- $\forall a' \ne a^", \{a',a^"\} \in A, f(a') \ne f(a^")$
	- c'è un immagine unica -> a un valore dell'immagine corrisponde un valore diverso della controimmagine
 ![[Pasted image 20230919100330.png]]
- #### biettiva
	- $\forall b \in B, \exists ! a \in A, f(a)=b$
	- c'è un valore di partenza e uno di arrivo unico
 ![[Pasted image 20230919100402.png]]
esempi:
$f:R \to R_0^+$
$x \to x^2$
funzione suriettiva e non iniettiva

#### Invertibile
Se una funzione è biettiva, è anche **invertibile**, cioè posso definire $f^{-1}:B \to A$ tale che:
- $f^{-1}(f(x))=x, \forall x \in A$ -> se ad ogni immagine di x applichiamo la funzione inversa troviamo x stesso
- $f(f^{-1}(y)) = y, \forall y \in B$ -> se ad ogni valore del codominio applico la funzione inversa, trovo y stesso

#### Monotona
|proprietà|scrittura|
|---|---|
|crescente|$x_1<x_2 \to f(x_1)<f(x_2)$|
|strettamente crescente|$x_1<x_2 \to f(x_1)<=f(x_2)$|
|descrecente|$x_1<x_2 \to f(x_1)>f(x_2)$|
|strettamente descrescente|$x_1<x_2 \to f(x_1)>=f(x_2)$|
dove $\forall x_1,x_2 \in D$ (dominio)

le funzioni **strettamente monotone** sono biunivoce e quindi invertibili
$f: A \to B$, consideriamo X un sottinsieme di A ($X \subseteq A$)
$f(X) = \{y \in B: \exists x \in X : y=f(x)\}$ -> sottoinsieme del codominio (immagini di x)
$f^{-1}(Y) = \{x \in A: f(x) \in Y\}$ sottoinsieme del dominio (controimmagini)

#### Grafico di una funzione
Il grafico di una funzione è un sottoinsieme del pjano cartesiano $RxR$ tale che:
$G_f = \{(x,y): x \in D_f, y=f(x)\}$