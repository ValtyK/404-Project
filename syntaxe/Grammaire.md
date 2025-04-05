# Grammaire d'un fichier melo
---
## 1. Rythme
On définit la grammaire pour la signature rythmique.

```
Signature: 4/4
BPM: 120
```


## 2. Séquence de notes
Nous définissons la grammaire pour une **séquence de notes** que nous appelons une "_**melodie**_".



```
{
    n(C4, C4-D5-E#4, C4, D4) | b(E4, D4) |
    n(C4, E4, D4, D4) | r(C4) |
}
```
---

> melo &rarr; emea FIN_SEQUENCE
emea &rarr; ACCO seqmelo ACCF
seqmelo &rarr; seqnote SEPMESURE suite_seqmelo
seqnote &rarr; DR PARO notes PARF
notes &rarr; NOTE ENTIER VIRGULE notes
notes &rarr; NOTE ENTIER
suite_seqmelo &rarr; seqmelo
suite_seqmelo &rarr; \(\epsilon\)
