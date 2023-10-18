### Potenza
$f(x) = x^n, n \in Z$
- strettamente crescente se n >= 0
esempio con n=2
$x_1 < x_2 <=> x_1^2<x_2^2$
moltiplico entrambe le parti per $x_1$
$x_1^2<x_2*x_1$
moltiplico entrambe le parti per $x_2$
$x_1*x_2<x_2^2$
unisco le espressioni
$x_1^2<x_2*x_1<x_2^2$
verificato
- strettamente monotona -> invertibile
$f^{-1}(x) = x^{1\over n} = \sqrt[n]{x}$

### Esponenziale
- strett. crescente $a > 1$
- strett. descrescente $0<a<1$
$f(x) = a^x$
importante $f(x) = e^x$

### Logaritmo
$f$ inversa dell'esponenziale
$y= \log_{a}x \iff a^y=x$ (RICORDA: quale esponente devo mettere alla base per avere x?)
#### proprietà
![[Pasted image 20230921111435.png]]
![[Pasted image 20230921111505.png]]
### Composta
se $g: X \to Y$ e $f:Y \to Z$
allora $f \circ g: X \to Z$ è $f \circ g (x) = f(g(x))$

### Lineare
$f(x) = mx+q$, m=coefficente angolare e q=termine noto
- invertibile

### Valore assoluto
$$
|x| =
\begin{cases}
x & x\ge 0\\
-x & x<0
\end{cases}
$$
#### proprietà (valgono per $x \in R$)
- $|x|>0$
- $|x| = 0 \iff x=0$
- |-x| = |x|
- $|x_1*x_2| = |x_1|*|x_2|$
- $|x_1/x_2| = |x_1|/|x_2|$
- $|x|< o < r \iff -r < x < r$ (vale anche con $\le$)
![[Pasted image 20230921110551.png]] esempio con r=2

### Disuguaglianza triangolare
$\forall (x_1,x_2), x_1,x_2 \in R$
vale $|x_1+x_2| \le |x_1|+|x_2|$
**dimostrazione:**
$|x|\le|x|$
$-|x|\le x \le |x|$
$-(|x_1|+|x_2|) \le x_1+x_2 \le |x_1|+ |x_2| \to |x_1+x_2| \le |x_1|+|x_2|$

## Funzioni trigonometriche

![[Pasted image 20230921111606.png]]
$x^°:x^{rad} = 360^°:2\pi_{rad}$
$-1 \le sen(x),cos(x) \le +1$
$sen(x)^2 + cos(x)^2 = 1$