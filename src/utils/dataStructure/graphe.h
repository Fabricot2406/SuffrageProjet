/** \\file */
/**
 * @file graphe.h
 * @author Anthony
 * @brief Structure de données pour structurer un graphe
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

typedef struct s_sommet {
	int indice; // Indice globale du candidat
	List *successeur; // Liste de pointeur de sommet (ensemble des arcs)
}sommet;

typedef struct s_graphe {
    sommet **graphe; // Tableau de pointeur de sommet
    int *status; // Tableau d'état pour chaque candidat
    int nb_candidat; // Nombre de candidat dans le graphe
}graphe;

/******************* CONSTRUCTEURS *********************/

graphe *creation_graphe(int nb_candidat);

sommet *creer_sommet(int indice);

/******************* OPERATEURS *********************/

void ajout_succession(sommet *s_current, sommet *s_successor);

void delete_succession(sommet *s_current);

void detruire_sommet(void *elem);

void detruire_graphe(graphe *g);

bool circuits(graphe *G,sommet *s_current);

void initialiser_status(graphe *g, int sommet_depart);

#endif //__GRAPHE_H__