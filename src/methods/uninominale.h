/**
 * @file uninominale.h
 * @author Fabio
 * @brief Méthode uninominale à 1 et 2 tours
 * @date 2023-11-25
 */

#ifndef UNINOMINALE_H
#define UNINOMINALE_CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils_sd.h"
#include "../utils/dataStructure/ballot.h"

 /**
 * @brief Calcule le résultat de la méthode uninominale à un tour.
 * Processus : 1) On initialise un tableau de votes.
 *             2) On cherche dans ce tableau le vainqueur.
 *             3) On affiche le vainqueur.
 * 
 * @param matrice Une matrice de type ballot.
 * @param output Le fichier de sortie dans lequel on écrit le résultat.
 * @pre La matrice ballot est initialisée et remplie.
 * @post Le vainqueur du scrutin est affiché.
 */
 void calculer_uninominale_un_tour(ballot * matrice, FILE *output);

 /**
 * @brief Calcule le résultat de la méthode uninominale à deux tour.
 * Processus : 1) On initialise un tableau de votes.
 *             2) On cherche dans ce tableau les deux vainqueurs.
 *             3) Si le score du vainqueur un est supérieur à 50%, alors on l'affique comme vainqueur, sinon on continue.
 *             4) On cherche le vainqueur entre les deux (celui qui obtient le plus de voix en ne contant que leurs votes).
 *             5) On affiche le vainqueur dépendant de qui a le plus haut score.
 * 
 * @param matrice Une matrice de type ballot.
 * @param output Le fichier de sortie dans lequel on écrit le résultat.
 * @pre La matrice ballot est initialisée et remplie.
 * @post Le vainqueur du scrutin est affiché.
 */
 void calculer_uninominale_deux_tours(ballot * matrice, FILE *output);

#endif