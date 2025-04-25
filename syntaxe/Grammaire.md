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

> melo &rarr; ACCO seq_mesure ACCF \
seq_mesure &rarr; mesure SEPMESURE suite_seq_mesure \
suite_seq_mesure &rarr; seq_mesure \
suite_seq_mesure &rarr; ε \
mesure &rarr; dr PARO seq_note PARF suite_mesure \
suite_mesure &rarr; mesure \
suite_mesure &rarr; ε \
seq_note &rarr; note ENTIER suite_seq_note \
suite_seq_note &rarr; SEPNOTE seq_note \
suite_seq_note &rarr; ACCORD seq_note \
suite_seq_note &rarr; ε \
note &rarr; C/C#, D/D#, E, F/F#, C, G/G#, A/A#, B \
dr &rarr; dc, c, n, b, r
## 3. Affectation / Fonctions

```
melo_piano = { c(D4, D4, D4, D4, D4, D4, D4, D4) | r(C4) | }
x = 10
PLAY(melo_piano)
```

> pgm &rarr; seq_inst \
seq_inst &rarr; inst suite_seq_inst \
suite_seq_inst &rarr; SEPINST seq_inst \
suite_seq_inst &rarr; SEPINST \
inst &rarr; IDF AFF variable \
inst &rarr; PLAY PARO IDF SEPNOTE GUIO IDF GUIF PARF \
inst &rarr; COMMENTAIRE
inst &rarr; autres instructions.. \
variable &rarr; melo \
variable &rarr; ENTIER 


