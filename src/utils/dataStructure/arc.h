/**
 * @file arc.h
 * @author Anthony
 * @brief Structure de données representant un arc et une liste d'arcs.
 * @details Un arc est une structure composée d'un candidat gagnant, perdant et du score du duel entre ces deux candidats.
 *        - La liste d'arc est utilisée dans le cadre des méthodes de Condorcet.
 *        - Elle permet de stocker les arcs du graphe et de les trier par ordre croissant ou décroissant de score.
 * @example arc : {candidat_gagnant : 1, candidat_perdant : 2, score : 5}
 * @example liste d'arc : [{1, 2, 5} , {2, 3, 4} , {1, 3, 3}]
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

/******************* STRUCTURE *********************/

/**
 * @brief Structure de données représentant un arc du graphe.
 * @details Couple de candidats et score de l'arc.
 */
typedef struct t_arc_p{
    int candidat_gagnant;
    int candidat_perdant;
    int score;
}arc;

/**
 * @brief Liste d'arcs.
 * @details Liste d'arcs triée par ordre décroissant de score.
 * Utilisation d'une liste générique.
 */
typedef struct s_arc{
    List *larc; // liste des arcs
    int nb_candidats;
}larc;

/******************* OPERATEURS *********************/

/**
 * @brief Constructeur de la structure de donnée arc.
 * @param candidat_gagnant
 * @param candidat_perdant
 * @param score le score du duel entre les deux candidats
 * @return arc* l'arc créé
 */
arc* arc_create(int candidat_gagnant, int candidat_perdant, int score);

/**
 * @brief Fonction permettant d'initialiser et de completer la liste des arcs à partir d'une matrice de duel.
 * @param matrice_duel La matrice de duel
 * @return larc* La liste des arcs
 * @pre La matrice de duel est initialisé.
 * @post La liste des arcs est initialisé et complété avec les arcs de la matrice de duel.
 *     - La liste des arcs est triée par ordre décroissant de score.
 */
larc* larc_init(t_mat_int_dyn *matrice_duel);

/**
 * @brief Libérer la mémoire allouée à une liste d'arcs.
 * @param tab_arc Liste des arcs à détruire
 * @pre La liste d'arc est initialisé.
 * @post La liste d'arc est détruite.
 */
void larc_delete(larc *tab_arc);

/**
 * @brief Fonction permettant de remplir un fichier de log avec la description des arcs.
 * @param tab_arc La liste d'arc à saisir dans le fichier de log.
 * @param log_file Le fichier de log.
 */
void larc_log(larc *tab_arc, FILE *log_file);

/**
 * @brief Fonction qui permetettant de supprimer les arcs d'un candidat donné.
 * @details - La méthode parcourt la liste des arcs.
 *          - Si l'arc de la liste contient le candidat donné, il est supprimé de la liste.
 * @param list_arc La liste des arcs à parcourir.
 * @param candidat Le candidat à supprimer.
 * @pre La liste des arcs est non vide, triée par ordre décroissant de score.
 *      Le candidat donné est présent dans la liste des arcs.
 * @post La liste des arcs ne contient plus d'arc avec le candidat donné.
 */
void candidat_delete(List *list_arc,int candidat);

#endif // __ARC_H__