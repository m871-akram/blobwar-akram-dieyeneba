# Blob War - Projet d'algorithmique avancee

Projet autour du jeu Blob War. Le but est d'implementer et comparer
plusieurs strategies de recherche pour une IA de jeu : glouton, Minimax,
Alpha-Beta parallele intermediaire et Alpha-Beta parallele optimise.

## Strategies

- `strategy_glouton.cc` : strategie gloutonne, evalue tous les coups possibles a profondeur 1.
- `strategy_minimax.cc` : Minimax a profondeur fixe.
- `strategy_alphabeta0.cc` : Alpha-Beta parallele intermediaire avec OpenMP au niveau racine.
- `strategy.cc` : version finale avec heuristique avancee, tri des coups, approfondissement iteratif et parallelisation
  OpenMP.

## Compilation

Depuis la racine du projet :

```bash
make
```

Pour forcer une recompilation complete :

```bash
make -B
```

Pour nettoyer les binaires et fichiers objets :

```bash
make clean
```

Pour lancer le jeu : 

```bash
./blobwar
```

## Lancer le benchmark

Le script `benchmark_blobwar.py` fait jouer les strategies entre elles et produit les CSV plus les graphes.

```bash
python3 benchmark_blobwar.py --timeout 2 --games-per-pair 1
```

- Le timeout du benchmark est fixe a 2 secondes par coup.
- La version finale `strategy.cc` utilise l'approfondissement iteratif et tourne donc jusqu'au timeout.
- Les parties avec `alphabeta_final` peuvent prendre plusieurs minutes, car il utilise presque tout le temps disponible
  a chaque coup.

## Rapport

Le rapport est dans :

- `rapport_blobwar.pdf`
