/**
 * @file methode_minimax.h
 * @brief Fichier d'en-tête pour les fonctions de la méthode Minimax.
 * @author Marco
 * @version 1.0
 */

#ifndef METHODE_MINMAX_H
#define METHODE_MINMAX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils_sd.h"
#include "../utils/dataStructure/ballot.h"
#include "../utils/dataStructure/duel.h"
#include "../utils/dataStructure/listegen.h"
#include "../utils/dataStructure/arc.h"

/**
 * @brief Remplit le tableau des pires scores.
 *
 * @param elem L'élément à traiter.
 * @param tab Le tableau à remplir.
 */
void remplirTabPireScore(void *elem, void *tab);

/**
 * @brief Implémente la méthode Minimax.
 *
 * @param matrice_ballot La matrice des bulletins de vote.
 */
void methodeMinimax(ballot *matrice_ballot);

/**
 * @brief Affiche un tableau.
 *
 * @param tab Le tableau à afficher.
 * @param taille La taille du tableau.
 */
void afficherTab(int *tab, int taille);

#endif /* METHODE_MINMAX_H */