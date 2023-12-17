/**
 * @file ballot.h
 * @author Anthony
 * @brief Structure de données pour les bulletins de vote, permettant de stocker les votes de chaque électeur.
 * @date 2021-11-26
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

#define INCREMENT_COLONNE 4
#define INCREMENT_LIGNE 1

/******************* STRUCTURE *********************/

/**
 * @struct s_ensemble_preference
 * @brief Structure de données pour les ensembles de préférences, permettant de stocker les votes de chaque électeur.
 * @details Définition opaque de la structure
 */
typedef struct s_ensemble_preference{
    int values; // Rang de préférence
    List *list; // List d'indice de candidat
} Pref;

/**
 * @struct ballot_s
 * @brief Structure de données pour les bulletins de vote, permettant de stocker les votes de chaque électeur.
 * @details Utilisation d'une matrice dynamique contenant des entiens non signés
 */
typedef struct ballot_s{
    char **candidats_nom; // Liste des noms des candidats
    int nb_candidats; // Nombre de candidats
    int nb_votants; // Nombre de votants
    List *classement; // Matrice de classement
} ballot;

/******************* CONSTRUCTEURS *********************/

/**
 * @brief Crée un nouveau ballot vide.
 * @param nb_candidats Nombre de candidats
 * @param nb_votants Nombre de votants
 * @return Pointeur vers le nouveau ballot.
 */
ballot *creer_ballot(int nb_candidats, int nb_votants);

/**
 * @brief Fonction permettant de remplir un ballot à partir d'un classement CSV.
 * @param b Pointeur vers le ballot à remplir.
 * @param classement_csv Pointeur vers la matrice contenant le classement CSV.
 * @return Pointeur vers le ballot rempli.
 */
ballot *remplir_ballot(ballot *b, t_mat_char_star_dyn *classement_csv);

/**
 * @brief Détruit un ballot, libérant la mémoire allouée.
 * @param b Pointeur vers le ballot à détruire.
 */
void detruire_ballot(ballot *b);

/******************* UTILS *********************/

/**
 * @brief Fonction permettant d'accéder au nom d'un candidat.
 * @param b Pointeur vers le ballot.
 * @param indice_candidat correspond à l'indice du candidat dans la liste des noms des candidats : (numéro de colonne - 1)
 * @return Pointeur vers le nom du candidat.
 */
char *nom_candidat(ballot *b, int indice_candidat);

/**
 * @brief Fonction permettant d'accéder à la liste de préférence d'un votant.
 * @param b Pointeur vers le ballot.
 * @param num_votant correspond à l'indice du votant dans la matrice de classement : (numéro de ligne - 1)
 * @return Pointeur vers la liste de préférence du votant.
 */
List *acces_liste_preference(ballot *b, int num_votant);

/**
 * @brief Affiche le premier candidat favori d'un votant.
 * 
 * @param b Pointeur vers le ballot.
 * @param votant correspond à l'indice du votant dans la matrice de classement : (numéro de ligne - 1)
 * @return int l'indice du candidat favori dans la liste des noms des candidats
 */
int fav_candidat(ballot *b,int num_votant);

/**
 * @brief Fonction permettant de remplir le fichier log avec le ballot
 * @param b ballot à afficher
 * @param log_file le fichier de log à remplir
 */
void log_ballot(ballot *b, FILE *log_file);

#endif //__BALLOT_H__