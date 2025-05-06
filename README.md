# Création d'un langage générateur de musique

## Fichiers

- **musique.c** (et son header **musique.h**) : méthodes de création de fichier .wav et écriture d'une onde dans un fichier.
- **main.c** : écriture de la mélodie
- **Makefile** : deux commandes diponibles
  - ``make`` : crée un executable musique qui génère un .wav
  - ``make test_lexeme`` : crée l'éxecutable "test_lexeme" qui prend un argument de type ".melo" et qui analyse le lexique
  - ``make test_syntaxe`` : crée l'éxecutable "test_syntaxe" qui prend un argument de type ".melo" et qui analyse la syntaxe en s'aidant du lexeme
  - ``make clean`` : retire tout les fichiers générés (même le .wav)

## Format WAV

On a choisi de générer un fichier WAV pour gagner en fluidité et en maniabilité : pas besoin de lancer une commande ou d'installer des packages externes supplémentaires.

[Documentation de l'en-tête WAV](https://docs.fileformat.com/audio/wav/#wav-file-header)

## Autres liens

- [Nyquist (langage)](https://fr.wikipedia.org/wiki/Nyquist_(langage)#:~:text=Nyquist%20est%20un%20langage%20de,la%20famille%20XLISP%20de%20Lisp.)
- [Le langage de programmation Faust](https://www.amstramgrame.fr/faust/about/)
- [Les langages & environnements de programmation audio](http://linuxmao.org/Cat%C3%A9gorie+langages+de+programmation+audio)
- [ABC (notation)](https://fr.wikipedia.org/wiki/ABC_(notation)) - Langage de prog de musique !

## Format de fichier

`my_file.melo`, notation anglo-saxone

```melo
Signature : 4/4
BPM : 120
(C4, C4, C4, D4) (E4, D4) (C4, E4, D4, D4) (C4)

```

## Interpreteur

L'idee de base est de lire un fichier avec une syntaxe arbitraire afin de generer un "fichier.wav".

## Exemple 1 : Au clair de la lune

**Suite de notes**:

```melo
{
    n(C4, C4-D5-E#4, C4, D4) | b(E4, D4) |
    n(C4, E4, D4, D4) | r(C4) |
}
```
