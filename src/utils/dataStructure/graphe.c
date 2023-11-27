#include "graphe.h"

typedef struct s_sommet {
	int indice; // Indice globale du candidat
	List *sommets; // Liste de pointeur de sommet (ensemble des arcs)
}sommet;

/**
 * Initialise un graphe avec un tableau de sommets et un tableau d'états pour chaque candidat.
 *
 * @param nb_candidat   Le nombre de candidats dans le graphe.
 * @param status Un tableau d'états initialisé pour chaque candidat.
 * Les valeurs possible : -1 = libre | 0 = ouvert | 1 = fermé, intialisé à -1.
 * @return Un tableau de pointeurs de sommets initialisés.
 */
sommet **init_graphe(int nb_candidat,int *status){
    status = malloc(nb_candidat * sizeof(int));
    for (int candidat = 0; candidat < nb_candidat; candidat++){
        status[candidat] = -1;
    }
    sommet **graphe = malloc(nb_candidat * sizeof(sommet *));
    return graphe;
}

/*
PSEUDO CODE : Détecter les circuits dans un graphe orienté

Entier circuit(graphe G, tableau statut, sommet x){
    int r;
    Pour tout successeur y de x faire {
        si y est libre :
            statut[y]=0
            r=circuit(G,statut,y) 
        si r=1 
            retourner 1
        sinon si statut[y]=0 
            retourner 1
    }
    statut[x]=1
    retourner 0
} 
*/
bool circuits(sommet **graphe,int *status,sommet *s_current);