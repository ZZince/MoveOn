# MoveOn — Moteur 3D modulaire en C++

## Description

**MoveOn** est un projet de moteur 3D développé en C++17, utilisant actuellement OpenGL pour le rendu graphique en temps réel.

L'objectif est de concevoir un moteur modulaire, extensible et indépendant, à terme, de l'API graphique utilisée. MoveOn repose sur une architecture orientée objets et composants, permettant de construire des scènes 3D, de manipuler des objets et de leur associer différents comportements.

Le projet constitue également un environnement d'expérimentation et d'apprentissage autour de la programmation graphique, de l'architecture logicielle et de l'optimisation des performances.

Il est actuellement en cours de développement.

## Fonctionnalités

### Fonctionnalités implémentées

- **Rendu 3D avec OpenGL 3.3 Core Profile**.
- **Gestion des scènes** contenant plusieurs objets 3D.
- **Architecture à composants** permettant d'associer des fonctionnalités à chaque objet.
- **Transformations 3D** : translation, rotation par quaternions et mise à l'échelle.
- **Hiérarchie parent-enfant** avec calcul des matrices de transformation mondiales.
- **Partage des maillages** entre plusieurs objets pour éviter la duplication des données géométriques.
- **Gestion individuelle de la visibilité et de la couleur** des objets rendables.
- **Génération de primitives géométriques** : cubes, sphères et pyramides.
- **Shaders GLSL** avec gestion des uniforms.
- **Caméra interactive** avec déplacements et rotations.
- **Gestion des entrées clavier**.
- **Compteur FPS** et mesure du temps de rendu des frames.

### Fonctionnalités en développement ou prévues

- Transformation des caméras et des lumières en composants.
- Séparation des ressources graphiques et des API de rendu.
- Implémentation de différents backends graphiques, notamment Vulkan.
- Gestion des matériaux et des textures.
- Amélioration du système de scène et de la hiérarchie des objets.
- Gestion avancée de l'éclairage et des ombres.
- Importation de modèles 3D externes.
- Optimisation du rendu et de l'utilisation des ressources GPU.
- Intégration éventuelle d'un moteur physique.

## Architecture

MoveOn s'appuie sur plusieurs classes ayant des responsabilités distinctes.

| Classe | Responsabilité |
|---|---|
| `Scene` | Stockage et mise à jour des objets d'une scène |
| `MoveOnObject` | Représentation d'un objet 3D, de sa transformation et de ses composants |
| `Component` | Classe de base des composants |
| `RenderableComponent` | Gestion du maillage, de la visibilité et de la couleur d'un objet |
| `Transform` | Position, rotation, échelle et matrices de transformation |
| `Renderer` | Interface générale destinée à abstraire le rendu graphique |
| `OpenGLRenderer` | Implémentation du rendu avec OpenGL |
| `Mesh` | Gestion de la géométrie et des buffers graphiques |
| `Shader` | Chargement, compilation et utilisation des shaders GLSL |
| `Camera` | Gestion de la vue et de la projection |
| `InputProcessor` | Traitement des entrées utilisateur |
| `FPSCounter` | Mesure des performances d'affichage |

L'architecture distingue les données des objets, leurs fonctionnalités et le processus de rendu.

Un même `Mesh` peut notamment être utilisé par plusieurs `MoveOnObject`, chacun conservant ses propres transformations et propriétés visuelles.

À terme, cette séparation doit permettre de prendre en charge plusieurs API graphiques sans modifier la logique fondamentale du moteur.

## Technologies utilisées

| Technologie | Utilisation |
|---|---|
| **C++17** | Langage principal |
| **OpenGL 3.3** | API de rendu graphique actuelle |
| **GLFW 3.4** | Création de fenêtres, contexte OpenGL et entrées |
| **GLEW 2.1** | Chargement des fonctions OpenGL |
| **GLM** | Vecteurs, matrices, quaternions et transformations 3D |
| **GLSL** | Programmation des shaders |
| **CMake** | Configuration du projet |
| **Ninja** | Compilation du projet |

Les dépendances graphiques sont conservées localement dans le dossier `OpenGL/` afin de faciliter la compilation du projet sur plusieurs machines.

## Installation et compilation

### Prérequis

La configuration actuelle du projet cible **Windows x64**.

Les outils suivants sont nécessaires :

- Un compilateur compatible C++17, tel que MinGW-w64 ou MSVC.
- CMake 3.20 ou supérieur.
- Ninja, pour les commandes de compilation ci-dessous.
- Des pilotes graphiques compatibles avec OpenGL 3.3.

GLFW, GLEW et GLM sont déjà fournis dans le dépôt. Il n'est donc pas nécessaire de les installer séparément.

### Cloner le dépôt

```bash
git clone https://github.com/ZZince/MoveOn.git
cd MoveOn
```

### Compiler en mode Debug

Depuis un terminal PowerShell, à la racine du projet :

```powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
```

### Exécuter MoveOn

```powershell
.\build\MoveOn.exe
```

### Compiler en mode Release

Pour activer les optimisations du compilateur :

```powershell
cmake -S . -B build-release -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build-release --parallel
```

Puis :

```powershell
.\build-release\MoveOn.exe
```

Les bibliothèques dynamiques nécessaires et les shaders sont copiés automatiquement vers le dossier de compilation par CMake.

**Remarque :** les bibliothèques précompilées fournies dans le dépôt sont destinées à Windows x64. La compatibilité avec d'autres systèmes d'exploitation fait partie des évolutions possibles du projet.

## Contrôles

| Touche | Action |
|---|---|
| Flèche haut | Avancer dans la direction de la caméra |
| Flèche bas | Reculer |
| Flèche gauche | Déplacement vers la gauche sur l'axe X |
| Flèche droite | Déplacement vers la droite sur l'axe X |
| W / S | Rotation verticale de la caméra (*pitch*) |
| A / D | Rotation horizontale de la caméra (*yaw*) |
| Échap | Fermer l'application |

Les déplacements et les rotations utilisent le temps écoulé entre les frames (`deltaTime`) afin de conserver une vitesse indépendante des FPS.

## Organisation du projet

```text
MoveOn/
├── include/
│   ├── Core/
│   ├── Components/
│   ├── Geometry/
│   ├── Graphics/
│   ├── Maths/
│   └── Utilities/
│
├── src/
│   ├── Core/
│   ├── Components/
│   ├── Geometry/
│   ├── Graphics/
│   ├── Maths/
│   ├── Utilities/
│   └── MoveOn.cpp
│
├── OpenGL/
│   ├── GLFW/
│   ├── GLEW/
│   ├── GLM/
│   ├── bin/
│   └── lib/
│
├── shaders/
├── CMakeLists.txt
└── README.md
```

Les dossiers `include/` et `src/` sont organisés selon les responsabilités des classes.

- **Core** : objets fondamentaux et gestion des scènes.
- **Components** : composants associés aux objets.
- **Geometry** : maillages, sommets et faces.
- **Graphics** : rendu, caméras, shaders et éclairage.
- **Maths** : transformations et opérations mathématiques.
- **Utilities** : gestion des entrées, outils de mesure et fonctionnalités transversales.

## Objectifs à long terme

MoveOn vise à évoluer vers un moteur 3D polyvalent, qui ne soit pas limité au développement de jeux vidéo.

Ses applications potentielles comprennent notamment la visualisation scientifique, la simulation, la représentation de données et le développement d'interfaces graphiques 3D interactives.

Les principaux axes de développement sont :

- **Modularité** : permettre l'ajout de nouvelles fonctionnalités grâce aux composants.
- **Portabilité** : réduire les dépendances à une plateforme ou à une API graphique particulière.
- **Performance** : optimiser l'utilisation du CPU, du GPU et de la mémoire.
- **Extensibilité** : faciliter l'intégration de nouveaux systèmes sans remettre en cause l'architecture existante.
- **Réutilisabilité** : permettre le partage de ressources graphiques entre plusieurs objets.

## État du projet

MoveOn est actuellement un projet expérimental en développement actif.

L'architecture, les interfaces et les fonctionnalités peuvent évoluer au fil des expérimentations et des besoins.

## Auteur

**Florient Artu**

## Dépôt

[GitHub — MoveOn](https://github.com/ZZince/MoveOn)