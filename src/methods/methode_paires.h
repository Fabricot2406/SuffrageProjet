/**
 * @file methode_paires.h
 * @author Anthony
 * @brief 
 * @date 2023-11-28
 */

#ifndef __METHODE_PAIRES_H__
#define __METHODE_PAIRES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils_sd.h"
#include "../utils/dataStructure/ballot.h"
#include "../utils/dataStructure/graphe.h"
#include "../utils/dataStructure/listegen.h"
#include "../utils/dataStructure/arc.h"
#include "../utils/dataStructure/duel.h"


/**
 * @brief Fonction principale de la méthode de Condorcet par le classement des paires.
 * Processus : 1) Créer la liste d'arc.
 *             2) Filtrer la liste d'arc.
 *             3) Déterminer le classement des candidats.
 * 
 * @param matrice_duel Matrice de duel.
 * @param candidats_nom Tableau de nom des candidats.
 * @param output Le fichier de sortie dans lequel on écrit le résultat.
 * @pre La matrice de duel est initialisé et remplie.
 * @pre Les noms sont rangés dans l'ordre de la matrice de duel.
 */
void condorcet_paires(t_mat_int_dyn *matrice_duel,char **candidats_nom, FILE *output);

#endif // __METHODE_PAIRE_H__