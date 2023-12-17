/**
 * @file graphe.c
 * @author Anthony
 * @brief Structure de données pour structurer un graphe
 * @date 2023-11-28
 */
#include "graphe.h"

graphe *creation_graphe(int nb_candidat){
    graphe *g = malloc(sizeof(graphe));
    if (g == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire\n");
        exit(EXIT_FAILURE);
    }
    g->graphe = malloc(nb_candidat * sizeof(sommet *));
    if (g->graphe == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire\n");
        exit(EXIT_FAILURE);
    }
    g->status = malloc(nb_candidat * sizeof(int));
    if (g->status == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire\n");
        exit(EXIT_FAILURE);
    }
    g->nb_candidat = nb_candidat;
    for (int candidat = 0; candidat < nb_candidat; candidat++){
        g->graphe[candidat] = creer_sommet(candidat);
    }
    return g;
}

void initialiser_status(graphe *g, int sommet_depart){
    for (int candidat = 0; candidat < g->nb_candidat; candidat++){
        g->status[candidat] = -1;
    }
    g->status[sommet_depart] = 0;
}

sommet *creer_sommet(int indice){
    sommet *s = malloc(sizeof(sommet));
    if (s == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire\n");
        exit(EXIT_FAILURE);
    }
    s->indice = indice;
    s->successeur = list_create();
    return s;
}

void ajout_succession(sommet *s_current, sommet *s_successor){
    list_push_back(s_current->successeur, s_successor);
}

void delete_succession(sommet *s_current){
    list_pop_back(s_current->successeur,vide);
}

void detruire_sommet(void *elem){
    sommet *s = (sommet *)elem;
    list_delete(s->successeur, vide);
    free(s);
}

void detruire_graphe(graphe *g){
    for (int candidat = 0; candidat < g->nb_candidat; candidat++){
        detruire_sommet(g->graphe[candidat]);
    }
    free(g->graphe);
    free(g->status);
    free(g);
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
bool circuits(graphe *G,sommet *s_current){
    int r = 0;
    Iterator *it = iterator_create(s_current->successeur);
    // Pour tout successeur de s_current
    while (iterator_has_next(it)) {
        sommet *successor = (sommet *)iterator_current(it);
        // Si le sommet a été visité alors il y a un circuit
        if (G->status[successor->indice] == 0) {
            iterator_delete(it);
            return true;
        }
        // Sinon si le sommet n'a pas été visité
        else if (G->status[successor->indice] == -1) {
            G->status[successor->indice] = 0;
            // Appel récursif pour le successeur
            r = circuits(G, successor);
            if (r == 1) {
                iterator_delete(it);
                return true;
            }
        }
        iterator_next(it);
    }
    G->status[s_current->indice] = 1;
    iterator_delete(it);
    return false;
}