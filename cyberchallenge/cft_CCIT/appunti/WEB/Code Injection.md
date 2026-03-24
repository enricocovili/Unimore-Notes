Generalmente cerchi, come nelle command injection, caratteri di escape per eseguire funzioni del linguaggio specifico

### PHP

#### Local file inclusion
Esecuzione di file locali (o anche remoti, se abilitato) direttamente dal costrutto `include` di PHP.

Se i tag `<? php >` non sono sanificati possiamo provare il **file poisoning**, caricando codice infetto in file normalmente innoqui (come input testuali o file caricati in un eventuale database)

**tips**
trova subito le funzioni abilitate
`<?php eval($_GET['c']); ?>`
KISS (keep it simple and stupid)