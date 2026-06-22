# C++ Module 01 — mémoire, pointeurs sur membres, références & switch

> Source : `subject.pdf` ("CPP - Module 01", v11.1), exercices 00 à 06.
> Concepts + schémas. Versions éditables des schémas dans `schemas/*.excalidraw` (ouvre-les sur excalidraw.com ou avec l'extension VS Code "Excalidraw").

## Le theme du module

Après le 00 (premières classes et methodes), le 01 c'est la **gestion mémoire** et l'**indirection** (pointeurs/références). 5 morceaux :

| Thème | Exos | La question |
|---|---|---|
| stack vs heap, `new`/`delete`, `new[]`/`delete[]` | 00, 01 | où vit l'objet, qui le détruit ? |
| pointeurs & références | 02, 03 | diff entre `T*` et `T&`, lequel quand ? |
| fichiers en C++ | 04 | lire/écrire un fichier sans `open`/`read`, avec les streams C++ |
| pointeurs sur fonctions membres | 05 | appeler une méthode sans pavé de `if/else` |
| `switch` | 06 | se servir du fall-through |

---

## Les 3 notions de base

**1. stack vs heap**
<img width="2848" height="1190" alt="image" src="https://github.com/user-attachments/assets/20a5e707-b2fc-4d66-a448-fe827aa0f126" />


Règle : objet utile **que dans cette fonction** → stack. Objet qui doit **survivre / être renvoyé** → heap.

**2. `new`/`delete` ≠ `malloc`/`free`** : `new` appelle le **constructeur**, `delete` appelle le **destructeur**. C'est toute la diff (et `malloc`/`free`/`printf` sont **interdits**, note = 0).

**3. tu matches toujours** : `new` → `delete`, et `new[]` → `delete[]`. Jamais croiser les deux (undefined behavior).

---

## ex00 — BraiiiiiiinnnzzzZ
`Makefile main.cpp Zombie.{h,hpp} Zombie.cpp newZombie.cpp randomChump.cpp`

Classe `Zombie` (attribut privé `name`), méthode `announce()` qui print `<name>: BraiiiiiiinnnzzzZ...`, et un destructeur qui print le nom. Plus deux fonctions :
- `Zombie* newZombie(std::string name)` → sur le **heap**, renvoyé, donc l'appelant fait le `delete`.
- `void randomChump(std::string name)` → sur la **stack**, s'annonce, meurt tout seul.

Tout le but de l'exo = choisir stack ou heap selon que l'objet doit survivre à la fonction ou pas. Le message dans le destructeur te montre **quand** chaque objet meurt.

**Piège** : oublier le `delete` du `newZombie` (leak), ou `delete` sur le zombie stack de `randomChump` (crash).

---

## ex01 — Moar brainz!
`Makefile main.cpp Zombie.{h,hpp} Zombie.cpp zombieHorde.cpp`

`Zombie* zombieHorde(int N, std::string name)` : alloue **N zombies en une seule alloc** (`new Zombie[N]`, pas N `new` en boucle), les nomme, renvoie le pointeur sur le premier. `delete[]` à la fin.

Le point clé : `new Zombie[N]` appelle le **constructeur par défaut** N fois, tu peux pas passer `name` dedans. Donc il te faut un constructeur par défaut **et** un moyen de set le nom après (un setter).

```
horde ─► [ Zombie#0 ][ Zombie#1 ] ... [ Zombie#N-1 ]   (bloc contigu)
delete[] horde;   // détruit les N PUIS libère
```

**Piège** : `delete` au lieu de `delete[]`.

---

## ex02 — HI THIS IS BRAIN
`Makefile main.cpp`

Une string `"HI THIS IS BRAIN"`, un pointeur `stringPTR` et une référence `stringREF` dessus. Tu print les 3 **adresses** puis les 3 **valeurs**.

Le but : démystifier la référence. C'est juste un **alias** — pas une variable à part comme le pointeur.
```
str   ───┐
         ├─ même adresse, même valeur
stringPTR ┤   &str == stringPTR == &stringREF
stringREF ┘   str == *stringPTR == stringREF
```
| | `T*` pointeur | `T&` référence |
|---|---|---|
| null possible | oui | non |
| réassignable | oui | non (collé à vie) |
| accès | `*ptr` | `ref` direct |

---

## ex03 — Unnecessary violence
`Makefile main.cpp Weapon.{h,hpp} Weapon.cpp HumanA.{h,hpp} HumanA.cpp HumanB.{h,hpp} HumanB.cpp`

`Weapon` : `type` privé, `getType()` renvoie une **réf const**, `setType()` le change. `HumanA` et `HumanB` ont un `Weapon` + un `name` + `attack()` qui print `<name> attacks with their <weapon type>`.

Le cœur : les deux humains pointent sur la **même** arme, donc un `setType()` se voit dans les deux `attack()`.
- **HumanA → référence `Weapon&`** : reçue au constructeur (init dans la **liste d'init**), jamais null → "toujours armé".
- **HumanB → pointeur `Weapon*`** : pas d'arme au départ, set après via `setWeapon()`, `NULL` = pas d'arme.

C'est ça la question du sujet : référence quand c'est garanti présent et fixé, pointeur quand ça peut manquer ou changer.

**Piège** : faire une **copie** de l'arme dans HumanA → le changement de type se voit plus, test foiré.

---

## ex04 — Sed is for losers
`Makefile main.cpp *.cpp *.{h,hpp}` — interdit : `std::string::replace` et les fonctions fichier du C (`open`/`read`/`fopen`...).

3 args : `filename s1 s2`. Tu copies `filename` dans `filename.replace` en remplaçant chaque `s1` par `s2`.

Outils : `std::ifstream` (lecture), `std::ofstream` (écriture), et pour le replace à la main `std::string::find` + `substr` :
```
pos = 0
tant que (i = texte.find(s1, pos)) != std::string::npos :
    écris [pos..i[ , puis écris s2
    pos = i + s1.length()
écris le reste [pos..fin]
```
Gère les erreurs : mauvais nb d'args, fichier introuvable, `s1` vide (sinon boucle infinie). Fournis tes tests.

---

## ex05 — Harl 2.0
`Makefile main.cpp Harl.{h,hpp} Harl.cpp`

`Harl` avec 4 méthodes **privées** (`debug/info/warning/error`) et une publique `complain(std::string level)` qui dispatche. **Imposé** : pointeurs sur fonctions membres, pas de pavé de `if/else`.

```cpp
void (Harl::*f)(void) = &Harl::debug;   // déclaration + assignation
(this->*f)();                           // appel (parenthèses obligatoires)
```
L'idée = deux tableaux parallèles (niveaux / pointeurs), tu cherches l'index du level et tu appelles via le pointeur :
```
{"DEBUG","INFO","WARNING","ERROR"}  ↔  {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error}
```
**Piège** : oublier le `&` devant `Harl::debug`, ou mal mettre les parenthèses de `(this->*f)()`.

---

## ex06 — Harl filter
`Makefile main.cpp Harl.{h,hpp} Harl.cpp` — exécutable **`harlFilter`**. *(facultatif)*

Un niveau en argument → affiche ce niveau **et tous ceux au-dessus**. Niveau inconnu → `[ Probably complaining about insignificant problems ]`. **Imposé** : `switch`.

Le truc c'est le **fall-through** : sans `break`, un `case` tombe dans le suivant.
```
WARNING → index 2 :
  switch(index) {
    case 2: warning();   // pas de break
    case 3: error();     // tombe ici → affiche WARNING + ERROR
            break;
    default: ...
  }
```
Avant le switch, convertis la string en index (en C++98 pas de `switch` sur une string).

**Piège** : mettre des `break` partout → un seul niveau affiché.
