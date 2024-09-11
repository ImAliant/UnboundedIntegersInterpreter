# UnboundedIntegersInterpreter

## Prérequis

Il vous faut installer la librairie `readline`.  
Debian: `sudo apt-get install libreadline8t64 libreadline-dev`

## Compilation et execution (dans la racine)

Pour la compilation: `make` \
Puis pour l'execution: `./test` pour les tests et `./interpreter` pour lancer l'interpréteur.

## Utilisation

L'interpréteur contient trois types d'instructions:  
1. `variable = entier_ou_variable op entier_ou_variable`
2. `variable = entier`
3. `print variable`

L'ensemble des opérations classiques sont implémentées: `+`, `-`, `*`, `/`, `%` et `^`. 

Pour quitter le programme, il vous suffit d'écrire `exit`.

## Historique

Projet rendu lors de ma première année de L2 (2021/2022).  
Projet réécrit en 2024.
