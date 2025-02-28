 # MoveOn - Moteur de Rendu 3D OpenGL

## Description
MoveOn est un moteur de rendu 3D utilisant OpenGL, permettant d'afficher et manipuler des objets en temps réel. Il repose sur une architecture modulaire avec des composants dédiés à la gestion des caméras, des lumières, des shaders et des maillages (meshes). L'objectif principal est d'offrir un environnement graphique interactif où des objets peuvent être affichés, déplacés et rendus avec différents styles d'éclairage et d'ombrage.

## Fonctionnalités principales
- **Rendu 3D en OpenGL** avec gestion complète d'une scène.
- **Création et manipulation d'objets 3D** (quadrilatères, sphères, pyramides).
- **Utilisation de shaders GLSL** (Phong, Cartoon, Basic).
- **Éclairage dynamique** avec gestion de sources lumineuses.
- **Caméra interactive** avec navigation libre.
- **Affichage des FPS** et mise à jour en temps réel.

## Technologies utilisées
- C++
- OpenGL
- GLFW (gestion de la fenêtre et des entrées utilisateur)
- GLEW (gestion des extensions OpenGL)
- GLM (mathématiques 3D)

## Installation et exécution
### Prérequis
Assurez-vous d'avoir installé :
- **GLFW** : `sudo apt install libglfw3-dev` (Linux) ou via vcpkg sous Windows.
- **GLEW** : `sudo apt install libglew-dev` (Linux) ou vcpkg.
- **GLM** : `sudo apt install libglm-dev` (Linux) ou vcpkg.

### Compilation du projet

Utilisant l'outil d'exécution de Visual Studio et ne m'étant pas encore interessé à la création de l'exécutéble, un fichier Make sera écrit dans le futur.

## Contrôles
| Touche | Action |
|--------|--------|
| Flèches directionnelles | Déplacement latéral et avant/arrière |
| W / S | Rotation verticale de la caméra (pitch) |
| A / D | Rotation horizontale de la caméra (yaw) |
| Échap | Quitter l'application |

## Structure du projet
- `src/` : Contient le code source du moteur
- `shaders/` : Contient les shaders GLSL
- `resources/` : Contient les éventuels modèles ou textures
- `include/` : Contient les fichiers d'en-tête

## Améliorations futures
- Ajout de lumières directionnelles.
- Application de textures sur les objets.
- Implémentation d’un moteur physique.
- Importation de modèles 3D externes (OBJ, FBX).

## Auteurs
- Florient Artu
