# GROUPE 14 - TDA1

* Anthony CHAIGNEAU (Responsable Utilitaires)
* Fabio YABAR (Responsable Méthodes)
* Marco REGRAGUI MARTINS (Responsable Sécurité / Documentation)

# Présentation du logiciel

Ce logiciel a deux buts principaux : **calculer les résultats d'un scrutin à l'aide d'une méthode et consulter ses propres votes.**

La liste des méthodes accessibles dans ce logiciel sont les suivants :
* Méthode Uninominale (à un et deux tours)
* Méthode de Jugement Majoritaire
* Méthode de Condorcet (Minimax, Schulze et paires)

# Avant de démarrer

Pour utiliser le logiciel, vous devez prendre compte des commandes de compilation. Pour entrer celles-ci, ouvrez donc le terminal de votre choix (sous un système d'exploitation Unix) dans le dossier où le makefile se situe et :
* **Pour compiler le programme**, utilisez la commande `make`.
* **Pour générer la documentation**, utilisez la commande `make doc`.
* **Pour effectuer des tests automatiques**, utilisez la commande `make TEST=<methode>`.
 > *avec [methode] étant choisi parmi : uni, cm, cp, cs, jm, all.*
* **Pour supprimer les fichiers locaux de compilation**, utilisez la commande `make clean`.

# Exécution du programme

Pour exécuter le programme, utilisez la commande suivante :

```
./scrutin [-i <ballot>] [-d <duel>] [-o <output>] [-m <methode>]
```

Les balises doivent être utilisées comme ceci :
* **-i <ballot>** : ouvre un fichier de scrutin (au format csv, de type ballot).
 > *avec [fichier] le nom du fichier, sans chemins ni extensions, placé dans le dossier `test/input`.*
* **-d <duel>** : ouvre un fichier de scrutin (au format csv, de type duel).
 > *avec [fichier] le nom du fichier, sans chemins ni extensions, placé dans le dossier `test/input`.*
* **-o <output>** : permet d'écrire la sortie du programme dans un fichier au choix.
 > *avec [output] le nom du fichier, sans chemins ni extensions, placé dans le dossier `test/output`.*
* **-m <methode>** : la méthode au choix que vous souhaitez utiliser pour déterminer le vainqueur du scrutin.
 > *avec [methode] étant choisi parmi : uni1, uni2, cm, cp, cs, jm, all.*

**ATTENTION :**
- Il est au minimum **nécessaire** d'utilisé une option d'input (-i ou -d) et l'option -m.
- Les options -i et -d sont **incompatibles**.
- L'option -d **ne peut pas** être utilisée avec les méthodes uni1, uni2, jm et all.

## Exemples d'exécution

```
./scrutin -i vote10 -m uni2
```

```
./scrutin -d wiki_paires -o test_wiki_paire -m cp
```

# Utilisation du programme

Le programme vous propose deux options :
* **Entrez 1** si vous souhaitez utiliser la méthode choisie sur le fichier demandé, le résultat du vote sera affiché en sortie.
* **Entrez 2** si vous souhaitez consulter vos votes.

## Consultation des votes

Vous pouvez uniquement consulter vos votes dans le cas où vous utilisez l'option -i avec les fichiers `voteJugement` et  `voteCondorcet`.

Les étapes de consultation sont les suivantes :
- Entrez votre nom.
- Entrez votre prénom.
- Entrez votre clé, celle-ci est trouvable dans les fichiers txt (respectivement `test/reference/codeJugement` et `test/reference/codeCondorcet`) suivant votre numéro étudiant.

## Fichiers de log

Vous pouvez consulter le fichier de log une fois le programme exécuté dans `test/output/log`.
