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
void remplir_tab_pire_score(void *elem, void *tab);

/**
 * @brief Implémente la méthode Minimax.
 * @param matrice_duel Matrice de duel avec les résultats du vote.
 * @param candidats_nom Liste des noms des candidats.
 * @param output Le fichier de sortie dans lequel on écrit le résultat.
 */
void condorcet_minimax(t_mat_int_dyn *matrice_duel,char **candidats_nom, FILE *output);

/**
 * @brief Affiche un tableau.
 *
 * @param tab Le tableau à afficher.
 * @param taille La taille du tableau.
 */
void afficher_tab(int *tab, int taille);

#endif /* METHODE_MINMAX_H */