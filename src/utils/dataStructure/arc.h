/**
 * @file arc.h
 * @autor Anthony
 * @brief Structure de données pour les arcs du graphe.
 * @version 1.0
 * @date 2023-11-27
*/

#ifndef __ARC_H__
#define __ARC_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "listegen.h"
#include "matrice_int_dyn.h"

typedef struct t_arc_p{
    int candidat_gagnant;
    int candidat_perdant;
    float score;
}arc;

typedef struct s_arc{
    List *larc; // liste des arcs
    int nb_candidats;
}larc;

/**
 * @brief Constructeur de la structure de donnée arc.
 * @param candidat_gagnant
 * @param candidat_perdant 
 * @param score
 * @return arc* l'arc créé
 */
arc* arc_create(int candidat_gagnant, int candidat_perdant, float score);

/**
 * @brief Fonction qui permet d'initialiser et de completer la liste des arcs à partir de la matrice de duel.
 * @param matrice_duel La matrice de duel
 * @return larc* La liste des arcs
 */
larc* larc_init(t_mat_int_dyn *matrice_duel);


/**
 * @brief Libérer la mémoire allouée à une liste d'arcs.
 * @param tab_arc Liste des arcs à détruire
 */
void detruire_larc(larc *tab_arc);

/**
 * @brief Afficher la liste des arcs.
 * @param tab_arc Liste des arcs à afficher
 */
void afficher_larc(larc *tab_arc);

#endif // __ARC_H__