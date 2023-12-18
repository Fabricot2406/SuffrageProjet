/**
 * @file graphe.h
 * @author Anthony
 * @brief Structure de données représentant un graphe.
 * @details Un graphe est une structure composée d'un tableau de pointeur de sommet et d'un tableau d'état.
 * @date 2023-11-27
*/

#ifndef __GRAPHE_H__
#define __GRAPHE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "listegen.h"


/******************* STRUCTURE *********************/

/**
 * @brief Structure de données représentant un sommet du graphe.
 * @details Un sommet est une structure composée d'un indice et d'une liste de pointeur de sommet.
 */
typedef struct s_sommet {
	int indice; // Indice du candidat
	List *successeur; // Liste de pointeur de sommet (ensemble des arcs)
}sommet;

/**
 * @brief Structure de données représentant un graphe.
 */
typedef struct s_graphe {
    sommet **graphe; // Tableau de pointeur de sommet
    int *status; // Tableau d'état pour chaque candidat
    int nb_candidat; // Nombre de candidat dans le graphe
}graphe;

/******************* CONSTRUCTEURS *********************/

/**
 * @brief Fonction permettant de créer un graphe.
 * @param nb_candidat le nombre de candidat
 * @return graphe* le graphe créé
 */
graphe *graphe_create(int nb_candidat);

/**
 * @brief Fonction permettant de créer un sommet.
 * @param indice l'indice du sommet
 * @return sommet* le sommet créé
 */
sommet *sommet_create(int indice);

/******************* OPERATEURS *********************/

/**
 * @brief Fonction permettant de savoir si un circuit est présent dans le graphe.
 * @details Cette fonction est utilisée dans le cadre de la méthode de classement par les paires.
 * @param G le graphe
 * @param s_current le sommet courant
 * @return true si un circuit est présent dans le graphe
 * @return false si aucun circuit est présent dans le graphe
 */
bool contain_circuit(graphe *G,sommet *s_current);

/**
 * @brief Fonction permettant d'ajouter une succession à un sommet.
 * @param s_current le sommet courant
 * @param s_successor le sommet successeur
 */
void succ_add(sommet *s_current, sommet *s_successor);

/**
 * @brief Fonction permettant d'initialiser le tableau d'état.
 * @param g le graphe
 * @param sommet_depart le sommet de départ
 */
void status_init(graphe *g, int sommet_depart);

/**
 * @brief Fonction permettant de supprimer la dernière succession d'un sommet.
 * @param s_current le sommet courant
 */
void last_succ_delete(sommet *s_current);

/**
 * @brief Fonction permettant de supprimer un sommet.
 * @param elem le pointeur générique vers le sommet à supprimer
 */
void sommet_delete(void *elem);

/**
 * @brief Fonction permettant de supprimer un graphe.
 * @param g le graphe à supprimer
 */
void graphe_delete(graphe *g);


#endif //__GRAPHE_H__