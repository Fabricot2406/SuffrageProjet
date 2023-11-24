/**
 * @file ballot.h
 * @author Anthony
 * @brief Structure de données pour les bulletins de vote, permettant de stocker les votes de chaque électeur.
 *   Permet d'accèder directement au candidat préféré d'un votant
 *   Exemple : 
 *       "2 5 2 3 4 4" : entiers correspondants aux indices des candidat dans la liste *candidats_nom
 *       si candidats_nom = ["A", "B", "C", "D", "E", "F"]
 *       alors classement = C > F > B > D > E > A
 *       alors classement[0] = -1
 *       alors classement[1] = -1
 *       alors classement[2] = A
 *       alors classement[3] = D
 *       alors classement[4] = E
 *       alors classement[5] = -1
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
typedef struct ballot_s{
    char **candidats_nom; // Liste des noms des candidats
    int nb_candidats; // Nombre de candidats
    int nb_votants; // Nombre de votants
    t_mat_int_dyn *classement; // Matrice contenant le classement de chaque votant
} ballot;

/**
 * @brief Crée un nouveau ballot vide.
 * @param nb_candidats Nombre de candidats.
 * @param nb_votants Nombre de votants.
 * @return Pointeur vers le nouveau ballot.
 */
ballot *creer_ballot(int nb_candidats, int nb_votants);


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

/**
 * @brief Remplit la liste des noms de candidats à partir du fichier csv
 * @param b Le ballot à remplir
 * @param classement_csv La matrice de classement à partir du fichier csv
 * @return ballot* Le ballot rempli
 */
ballot *remplir_liste_candidats(ballot *b, t_mat_char_star_dyn *classement_csv);

/**
 * @brief Remplit la matrice de classement à partir du fichier csv
 * @param b Le ballot à remplir
 * @param classement_csv La matrice de classement à partir du fichier csv
 * @return ballot* Le ballot rempli
 */
ballot *remplir_classement(ballot *b, t_mat_char_star_dyn *classement_csv);


/**
 * @brief Détruit un ballot, libérant la mémoire allouée.
 * @param b Pointeur vers le ballot à détruire.
 */
void detruire_ballot(ballot *b);

/******************* UTILS *********************/

/**
 * @brief Affiche le premier candidat favori d'un votant.
 * 
 * @param b 
 * @param votant correspond à l'indice du votant dans la matrice de classement : numéro de ligne -1
 * @return int l'indice du candidat favori dans la liste des candidats
 */
int fav_candidat(ballot *b,int num_votant);

#endif