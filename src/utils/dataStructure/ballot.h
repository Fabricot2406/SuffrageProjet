/**
 * @file ballot.h
 * @author Anthony
 * @brief Structure de données représentant un ballot de vote.
 * @details Un ballot est une structure composée d'une liste de candidats, d'une matrice de classement et d'un nombre de votants.
 * 
 *        - Chaque élément de la matrice de classement est un ensemble de préférence.
 *             - Chaque ligne de la matrice de classement correspond une liste d'ensemble de préférence.
 *             - Il y a autant de lignes que de votants.
 *             - Il peut y avoir (nb_candidats + 1) colonnes dans la matrice de classement.
 *             - Chaque colonne de la matrice de classement correspond à un rang de préférence.
 *             - La liste d'ensemble de préférence est triée par ordre croissant de rang.
 * 
 *        - Chaque ensemble de préférence est composée d'un rang et d'une liste d'indice de candidat.
 *        - Le pire rang est -1. Le meilleur rang est 1.
 * 
 * @example ensemble de préférence : {rang : [indice_candidat_1, indice_candidat_2, ...]}
 * @example liste d'ensemble préférence : [{1 : [2 , 3]} , {3 : 4} , {4 : [0 , 1]}]
 * @example ballot : 5 candidats, 10 votants
 * 
 *          [0] :  Charlotte aux poires
 *          [1] :  Clafouti
 *          [2] :  Quatre quart
 *          [3] :  Baba au ruhm
 *          [4] :  Tarte à la fraise
 *          
 *          Matrice de classement :
 * 
 *          votant n°0 : [{1 : 4} , {2 : [0 , 3]} , {4 : 2} , {-1 : 1}]
 *          votant n°1 : [{1 : [2 , 3]} , {3 : 4} , {4 : [0 , 1]}]
 *          votant n°2 : [...]
 *          votant n°3 : [...]
 *          votant n°4 : [...]
 *          votant n°5 : [...]
 *          votant n°6 : [...]
 *          votant n°7 : [...]
 *          votant n°8 : [{2 : 0} , {3 : 1} , {4 : [2 , 4]} , {-1 : 3}]
 *          votant n°9 : [{1 : 4} , {2 : [0 , 2]} , {4 : [1 , 3]}]
 * 
 * @date 2023-11-15
 */

#ifndef __BALLOT_H__
#define __BALLOT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "matrice_string_dyn.h"
#include "matrice_int_dyn.h"
#include "listegen.h"

/******************* STRUCTURE *********************/

/**
 * @struct s_ensemble_preference
 * @brief Structure de données représentant un ensemble de préférence.
 * @details Au moins un candidat est présent dans l'ensemble de préférence.
 */
typedef struct s_ensemble_preference{
    int values; // Rang de préférence
    List *list; // Liste de candidat
} Pref;

/**
 * @struct ballot_s
 * @brief Structure de données représentant un ballot de vote.
 * @details Utilisation d'une liste générique contenant des listes d'ensemble de préférence.
 */
typedef struct ballot_s{
    char **candidats_nom; // Liste des candidats (noms des candidats)
    int nb_candidats;
    int nb_votants;
    List *classement; // Matrice d'ensemble de préférence
} ballot;

/******************* CONSTRUCTEURS *********************/

/**
 * @brief Crée un nouveau ballot vide.
 * @param nb_candidats Nombre de candidats
 * @param nb_votants Nombre de votants
 * @return Pointeur vers le nouveau ballot.
 * @pre nb_candidats > 0
 * @pre nb_votants > 0
 */
ballot *ballot_create(int nb_candidats, int nb_votants);

/**
 * @brief Fonction permettant de remplir un ballot à partir d'un classement CSV.
 * @param b Pointeur vers le ballot à remplir.
 * @param classement_csv Pointeur vers la matrice contenant le classement CSV.
 * @return Pointeur vers le ballot rempli.
 * @pre b != NULL
 * @pre classement_csv != NULL
 */
ballot *ballot_init(ballot *b, t_mat_char_star_dyn *classement_csv);

/**
 * @brief Détruit un ballot, libérant la mémoire allouée.
 * @param b Pointeur vers le ballot à détruire.
 * @pre b != NULL
 */
void ballot_delete(ballot *b);

/******************* UTILS *********************/

/**
 * @brief Fonction permettant d'accéder au nom d'un candidat.
 * @param b Pointeur vers le ballot.
 * @param indice_candidat correspond à l'indice du candidat dans la liste des noms des candidats : (numéro de colonne - 1)
 * @return Pointeur vers le nom du candidat.
 */
char *get_candidat_nom(ballot *b, int indice_candidat);

/**
 * @brief Fonction permettant d'accéder à la liste de préférence d'un votant.
 * @param b Pointeur vers le ballot.
 * @param num_votant correspond à l'indice du votant dans la matrice de classement : (numéro de ligne - 1)
 * @return Pointeur vers la liste de préférence du votant.
 */
List *get_liste_pref(ballot *b, int num_votant);

/**
 * @brief Affiche le premier candidat favori d'un votant.
 * 
 * @param b Pointeur vers le ballot.
 * @param votant correspond à l'indice du votant dans la matrice de classement : (numéro de ligne - 1)
 * @return int l'indice du candidat favori dans la liste des noms des candidats
 */
int get_fav_candidat(ballot *b,int num_votant);

/**
 * @brief Fonction permettant de remplir le fichier log avec le ballot
 * @param b ballot à afficher
 * @param log_file le fichier de log à remplir
 */
void ballot_log(ballot *b, FILE *log_file);

#endif //__BALLOT_H__