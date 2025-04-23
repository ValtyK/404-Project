# Documentation générale

---

## Fonctions principales de la lib musique

### note_to_frequency

```h
double note_to_frequency(const char *note_name, int octave);
```

**Description :**  
Convertit un nom de note musicale et une octave en sa fréquence en Hz, selon le système tempéré égal basé sur A4 = 440 Hz.

Cette fonction est utile pour générer des notes précises dans des buffers audio ou construire des accords.

#### Paramètres

| Nom | Type | Description |
|-|-|-|
| `note_name` | `const char *` | Nom de la note parmi : `"C"`, `"C#"`, `"D"`, `"D#"`, `"E"`, `"F"`, `"F#"`, `"G"`, `"G#"`, `"A"`, `"A#"`, `"B"` |
| `octave` | `int` | Numéro de l’octave (ex : 4 pour A4 = 440 Hz) |

#### Valeur de retour

- Retourne la fréquence de la note en Hz si la note est valide.
- Retourne `-1.0` si la note n’est pas reconnue.

#### Exemple

```c
double a = note_to_frequency("A", 4);    // 440.0
double cs = note_to_frequency("C#", 4);  // 277.18
double err = note_to_frequency("H", 4);  // -1.0
```

---

### generate_chord

```h
void generate_chord(double t1, double t2, const double *frequencies, int count, double amp, int sample_rate);
```

**Description :**  
Génère un accord à partir d’un tableau de fréquences représentant les notes. Chaque note est enrichie par synthèse additive avec plusieurs harmoniques, et les signaux sont additionnés dans les buffers audio gauche et droit.

Cette fonction permet de créer des accords riches et complexes entre deux instants donnés.

#### Paramètres de generate_chord

| Nom | Type | Description |
|-|-|-|
| `t1` | `double` | Temps de début de l'accord, en secondes |
| `t2` | `double` | Temps de fin de l'accord, en secondes |
| `frequencies` | `const double *` | Tableau des frequences (en Hz) des notes à superposer |
| `count` | `int` | Nombre de freq. dans le tableau (nb de notes de l'accord) |
| `amp` | `double` | Amplitude globale (répartie sur les notes de l'accord) |
| `sample_rate` | `int` | Taux d'échantillonage en Hz (ex: 44100) |

#### Retour (generate_chord)

- Aucun retour. Les signaux sont ajoutés dans les buffers audio globaux.

#### Exemple d'accord

```c
double freqs[] = {261.63, 329.63, 392.00}; // Do, Mi, Sol
generate_chord(0.0, 2.0, freqs, 3, 3000.0, 44100);
```

---

### generate_envelope

```h
void generate_envelope(double t1, double t2, double attack, double decay, double sustain, double release, int sample_rate);
```

**Description :**  
Applique une enveloppe ADSR (Attack, Decay, Sustain, Release) sur la plage temporelle donnée dans les buffers audio. Cette enveloppe module progressivement l’amplitude du signal, rendant le son plus naturel.

#### Paramètres de generate_envelope

| Nom | Type | Description |
|-|-|-|
| `t1` | `double` | Temps de début de l'enveloppe, en secondes |
| `t2` | `double` | Temps de fin de l'enveloppe, en secondes |
| `attack` | `double` | Pourcentage de la durée affecté à l'attaque |
| `decay` | `double` | Pourcentage de la durée affecté à la dércoissance |
| `sustain` | `double` | Niveau de maintien (pourcentage de l'amplitude max) |
| `release` | `double` | Pourcentage de la durée affecté au relâchement |
| `sample_rate` | `int` | Taux d'échantillonage en Hz (ex: 44100) |

#### Retour (generate_envelope)

- Aucun retour. L'amplitude des échantillons est modifiée directeent dans les buffers audio.

#### Exemple ADSR

```c
generate_envelope(0.0, 3.0, 10.0, 20.0, 70.0, 10.0, 44100);
```

Valeurs typiques :

- Attack (durée %) : 0-30
- Decay (durée %) : 0-40
- Sustain (niveau %) : 30-100
- Release (durée %) : 0-40

![representation_ADSR](./Envelopes-ADSR.png)

---
