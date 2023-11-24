/**
 * @file ballot.h
 * @author Anthony
 * @brief Structure de données pour les bulletins de vote, permettant de stocker les votes de chaque électeur.
 *   Permet d'accèder directement au candidat préféré d'un votant
 *   Exemple : 
 *       "2 5 1 3 4 0" : entiers correspondants aux indices des candidat dans la liste *candidats_nom
 *       si candidats_nom = ["A", "B", "C", "D", "E", "F"]
 *       alors classement = C > F > B > D > E > A
 *       alors classement[0] = 2 -> C
 *       alors classement[1] = 5 -> F
 *       alors classement[2] = 1 -> B
 *       alors classement[3] = 3 -> D
 *       alors classement[4] = 4 -> E
 *       alors classement[5] = 0 -> A
 * 
 *  -> Structure de données non adaptée pour Condorcet et Majo.
 *  -> Non prise en compte des préférences égales.
 * 
 *  -> Remplacement à terme par une liste d'ensembles de candidats :
 *      Exemple : {{C, F} , {B, D, E, A} , {F}}
 *                -> {C, F} préféré à {B, D, E, A} préféré à {F} 
 *                -> (C = F) > (B = D = E = A) > F
 * 
 * @details Utilisation d'une matrice dynamique contenant des entiens non signés
 * @version beta
 * @date 2021-11-24
 */

#ifndef __BALLOT_H__
#define __BALLOT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "matrice_int_dyn.h"
#include "matrice_string_dyn.h"

/**
 * @struct ballot_s
 * @brief Structure de données pour les bulletins de vote, permettant de stocker les votes de chaque électeur.
 * @details Utilisation d'une matrice dynamique contenant des entiens non signés
 */
typedef struct ballot_s ballot;

/**
 * @brief Crée un nouveau ballot vide.
 * @param nb_candidats Nombre de candidats.
 * @param nb_votants Nombre de votants.
 * @return Pointeur vers le nouveau ballot.
 */
ballot *creer_ballot(char **candidats_nom, int nb_candidats, int nb_votants);


/**
 * @brief Fonction permettant de remplir un ballot à partir d'un classement CSV.
 * @param b Pointeur vers le ballot à remplir.
 * @param classement_csv Pointeur vers la matrice contenant le classement CSV.
 * @return Pointeur vers le ballot rempli.
 * @details Exemple :
 *      "2 5 1 3 4 0" : entiers correspondants aux indices des candidat dans la liste *candidats_nom
 *      si candidats_nom = ["A", "B", "C", "D", "E", "F"]
 *      alors classement = C > F > B > D > E > A
 */
ballot *remplir_ballot(ballot *b, t_mat_char_star_dyn *classement_csv);

#endif