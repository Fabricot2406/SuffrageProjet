/**
 * @file methode_minimax.h
 * @brief Implémentation de la méthode Minimax.
 * @author Marco
 * @date 2023-12-03
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
 * @brief Implémente la méthode Minimax.
 * Procédé : 1) On initialise la liste d'arc résultant de la matrice de duel. 
 *           2) On initialise un tableau répertoriant tous les candidats du scrutin à 0.
 *           3) Pour chaque candidat perdant d'un duel, le score de l'arc ou il est perdant est supérieur à la valeur du tableau à l'indice correspondant on remplace la valeur du tableau par le score de l'arc.
 *           4) Une fois tous les arcs traités on parcourt le tableau et on récupère l'indice du candidat ayant le score le plus faible.
 *           5) On affiche le nom du candidat correspondant à l'indice récupéré.
 * @param matrice_ballot La matrice des bulletins de vote.
 * @param output Fichier de sortie.
 */
void condorcet_minimax(t_mat_int_dyn *matrice_duel,char **candidats_nom, FILE *output);


#endif /* METHODE_MINMAX_H */