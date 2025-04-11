# Melo Language Support for VSCode

Coloration syntaxique officielle pour le langage de programmation musical **Melo** 🎵

---

## ✨ Fonctions incluses

- 🎨 Coloration syntaxique `.melo`
- ✅ Support des entêtes : `Name`, `Authors`, `Date`, `Signature`, `BPM`
- 🎶 Mise en évidence des fonctions musicales : `n()`, `b()`, `c()`, `r()`, `play(...)`
- 🧠 Coloration différente pour les notes, variables, nombres, structures de contrôle

---

## 📂 Utilisation

1. Installez l’extension depuis le Marketplace ou en `.vsix`
2. Créez un fichier `monchef.melo`
3. Écrivez vos mélodies, puis interprétez-les avec votre moteur `melo`

---

## 🛠️ Exemple de code

```melo
---
Name: Ma musique de ZINZIN
Authors: Tavib & MaTttThéEau & Vlnaeitn
Date: aozidgyauzdhg 12 caca

Signature: 4/4
BPM: 120
---
/* commentaire qque part dans le code */
// commentaire sur une ligne...

melo_piano = {
    n(C4, C4-D5-E#4, C4, D4) | b(E4, D4) | // C4-D5-E#4 est un accord
    n(C4, E4, D4, D4) | r(C4) |
}

melo_piano_2 = { c(D4 D4 D4 D4 D4 D4 D4 D4) | r(C4) | }

// Construction de "Au Clair de la Lune"
ami_pierrot = {n(C4, C4, C4, D4) | b(E4, D4) | n(C4, E4, D4, D4) | r(C4) |}
interlude = {n(D4, D4, D4, D4) | b(A4, A4) | n(D4, C4, B4, A4) | r(G3) |}
au_clair_de_la_lune = (2 * ami_pierrot) + interlude + ami_pierrot

play(au_clair_de_la_lune, 1:, "clair_lune.wav") // Ecris toute la melodie a partir de la mesure 1

/*
    La fonction play ecrit une melodie dans le .wav
    param. 1 = melodie a jouer
    param. 2 = mesures jouees dans la melodie
*/

play(melo_piano, 1:3, "file_1.wav") // Ecris les mesures 1 à 3
play(melo_piano, 4, "file_1.wav") // Ecris la mesure 4 à la suite du fichier 1

n = 0
while (n < 4) {
    play(melo_piano_2, 1-2)

    if (n = 3) {
        play(melo_piano, 1)
    }

    n = n + 1
}

/* Idée : afficher la melo finale apres interpretation dans le terminal */
```
