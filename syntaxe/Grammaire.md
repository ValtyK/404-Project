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
seqnote &rarr; dr PARO notes PARF
notes &rarr; ACCORD SEPNOTE notes
notes &rarr; ACCORD
notes &rarr; note ENTIER SEPNOTE notes
notes &rarr; note ENTIER
suite_seqmelo &rarr; seqmelo
suite_seqmelo &rarr; \(\epsilon\)
dr &rarr; D_CROCHE
dr &rarr; CROCHE
dr &rarr; NOIR
dr &rarr; BLANCHE
dr &rarr; RONDE
note &rarr; A
note &rarr; B
note &rarr; C
note &rarr; D
note &rarr; E
note &rarr; F
note &rarr; G

## 3. Affectation

```
melo_piano_2 = { c(D4, D4, D4, D4, D4, D4, D4, D4) | r(C4) | }
```

> IDF &rarr; melo

## 4. Fonctions

```
play(melo_piano, 1-3)
play(melo_piano, 4)
```

> fonc &rarr; mc PARO zic SEPNOTE mesure PARF FINSEQ
mc &rarr; PLAY
zic &rarr; IDF
zic &rarr; melo
mesure &rarr; ENTIER
mesure &rarr; ENTIER MOINS ENTIER 

## 5. Condition
```
idf << 5
idf >> 5
idf <= 5
idf >= 5
idf == 5
idf != 5
```

## 6. Boucle

