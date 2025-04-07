## Definizione di determinante

![placeholder](./imgs/Pasted_image_20231008102821.png)
Sommatoria di tutte le permutazioni di A, in modo che in ciascuna di essi risulti un solo elemento per riga e per colonna

### Sottomatrice
Data una matrice A $\in M_{mxn}(\mathbb K)$, si dice sottomatrice di tipo h x k (con h $\le$ m e k $\le$ n) estratta da A ogni matrice avente per elementi gli elementi di A appartenenti contemporaneamente a h righe fissate e a k colonne fissate.

### Minore complementare
Si dice minore complementare dell'elemento $a^i_j$ la matrice $M^i_j$ di ordine n -1 ottenuta da A cancellandone la i-esima riga e la j-esima colonna.

### Complemento Algebrico
![placeholder](./imgs/Pasted_image_20231008113102.png)
dove $M^i_j$ è il minore complementare dell'elemento della riga i e colonna j
## Calcolo del determinante
### Ordine 2
Effettuare la sottrazione tra la diagonale principale e la diagonale secondaria
![placeholder](./imgs/Pasted_image_20231008103326.png)

### Ordine 3
**Regola di Sarrus**
![placeholder](./imgs/Pasted_image_20231008103437.png)

### Ordine 4+
Utilizzo il [[#Teorema di Laplace]]

## Proprietà del determinante
![placeholder](./imgs/Pasted_image_20231008103627.png)
![placeholder](./imgs/Pasted_image_20231008103716.png)
![placeholder](./imgs/Pasted_image_20231008103650.png)
Multi linearità (IV' e IV''):
![placeholder](./imgs/Pasted_image_20231008103700.png)
![placeholder](./imgs/Pasted_image_20231008103735.png)
![placeholder](./imgs/Pasted_image_20231008103749.png)
![placeholder](./imgs/Pasted_image_20231008103802.png)

## Teorema di Laplace
![placeholder](./imgs/Pasted_image_20231008104415.png)
### Dimostrazione
![placeholder](./imgs/Pasted_image_20231008113316.png)

## Teorema di Binet
![placeholder](./imgs/Pasted_image_20231008161935.png)
## Teorema matrici inverse
![placeholder](./imgs/Pasted_image_20231008161831.png)
