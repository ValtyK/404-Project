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
    n(C4, C4@D5@E#4, C4, D4) | b(E4, D4) |
    n(C4, E4, D4, D4) | r(C4) |
}

{ b(C4) n(C4, D4) | }
```
---

> melo &rarr; mea FIN_SEQUENCE \
mea &rarr; ACCO seqmelo ACCF \
seqmelo &rarr; mesure SEPMESURE suite_seqmelo \
mesure &rarr; DUREE_RYTHMIQUE PARO notes PARF suite_seqmelo\
notes &rarr; NOTE ENTIER SEPNOTE notes \
notes &rarr; NOTE DIESE ENTIER SEPNOTE notes \
notes &rarr; NOTE ENTIER ACCORD notes
notes &rarr; NOTE DIESE ENTIER ACCORD notes
notes &rarr; NOTE DIESE ENTIER \
notes &rarr; NOTE ENTIER \
suite_seqmelo &rarr; seqmelo \
suite_seqmelo &rarr; ε

## 3. Affectation

```
melo_piano_2 = { c(D4, D4, D4, D4, D4, D4, D4, D4) | r(C4) | }
x = 10
```

> identifiant &rarr; IDF AFF melo \
identifiant &rarr; IDF AFF ENTIER

## 4. Fonctions

```
play(melo_piano, 1:3)
play(melo_piano, 4)
```

> fonc &rarr; mc PARO zic SEPNOTE mesure PARF FINSEQ \
mc &rarr; PLAY \
zic &rarr; IDF \
zic &rarr; melo \
mesure &rarr; ENTIER \
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

