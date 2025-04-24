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

> melo &rarr; ACCO seqmelo ACCF \
seqmelo &rarr; mesure SEPMESURE suite_seqmelo \
mesure &rarr; dr PARO notes PARF suite_mesure\
notes &rarr; note ENTIER suite_notes \
suite_notes &rarr; SEPNOTE notes
suite_notes &rarr; ACCORD notes
suite_notes &rarr; ε
note &rarr; C \
note &rarr; C# \
note &rarr; D \
note &rarr; D# \
note &rarr; E \
note &rarr; F \
note &rarr; F# \
note &rarr; C \
note &rarr; G \
note &rarr; G# \
note &rarr; A \
note &rarr; A# \
note &rarr; B \
dr &rarr; dc \
dr &rarr; c \
dr &rarr; n \
dr &rarr; b \
dr &rarr; r \
suite_mesure &rarr; mesure \
suite_mesure &rarr; ε \
suite_seqmelo &rarr; seqmelo \
suite_seqmelo &rarr; ε

## 3. Affectation

```
melo_piano_2 = { c(D4, D4, D4, D4, D4, D4, D4, D4) | r(C4) | }
x = 10
```

> pgm &rarr; seq_inst \
seq_inst &rarr; inst suite_seq_inst \
suite_seq_inst &rarr; SEPINT seq_inst \
suite_seq_inst &rarr; ε \
inst &rarr; IDF AFF melo \
inst &rarr; PLAY PARO IDF PARF \
inst &rarr; autres instructions.. \ 

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

