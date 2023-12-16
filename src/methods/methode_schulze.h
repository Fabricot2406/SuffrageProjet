/**
 * @file methode_schulze.h
 * @author Fabio
 * @brief Fichier pour le calcul du vainqueur avec Schulze
 * @date 2023-11-29
 */

#ifndef __METHODE_SCHULZE_H__
#define __METHODE_SCHULZE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils_sd.h"
#include "../utils/dataStructure/arc.h"
#include "../utils/dataStructure/listegen.h"

/******************* FONCTIONS OPERATRICES *********************/

bool comparer_scores(void *a, void *b);

/******************* METHODE *********************/

/**
 * @brief Fonction permettant de déterminer si un candidat est vainqueur de condorcet.
 * @param list_arc Liste d'arcs triée par ordre croissant.
 * @param nb_candidats Nombre de candidats.
 * @param candidats_nom Liste des noms des candidats.
 * @return i : l'indice du candidat vainqueur si il y a un vainqueur.
 * @return -1 : si il n'y a pas de vainqueur à ce stade.
 */
int trouver_vainqueur_schulze(List *list_arc, int nb_candidats, char **candidats_nom);

/**
 * @brief Fonction permettant de déterminer si un candidat est vainqueur de condorcet.
 * @param list_arc Liste d'arcs triée par ordre croissant.
 * @param nb_candidats Nombre de candidats.
 * @param candidats_nom Liste des noms des candidats.
 * @param output Le fichier de sortie dans lequel on écrit le résultat.
 */
void reduire_arcs(List *list_arc, int nb_candidats, char **candidats_nom, FILE *output);

/**
 * @brief Fonction permettant de déterminer si un candidat est vainqueur de condorcet.
 * @param matrice_duel Matrice de duel avec les résultats du vote.
 * @param candidats_nom Liste des noms des candidats.
 * @param output Le fichier de sortie dans lequel on écrit le résultat.
 */
void condorcet_schulze(t_mat_int_dyn *matrice_duel, char **candidats_nom, FILE *output);

#endif