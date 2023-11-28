#include "methode_paire.h"

void resoudre_paradoxe(larc *list_arc, int *vainqueur){
    int nb_candidats = list_arc->nb_candidats;
    graphe *g = creation_graphe(nb_candidats);
    Iterator *it = iterator_create(list_arc->larc);
    while (iterator_has_next(it)){
        arc *a = iterator_current(it);
        ajout_succession(g->graphe[a->candidat_gagnant], g->graphe[a->candidat_perdant]);
        if (circuits(g, g->graphe[a->candidat_gagnant])){
            printf("Il y a un paradoxe de Condorcet\n");
            delete_succession(g->graphe[a->candidat_gagnant]);
            list_remove_at(list_arc->larc, iterator_index(it), free);
        }
        iterator_next(it);
    }
    iterator_delete(it);
    detruire_graphe(g);
    vainqueur_condorcet(list_arc, vainqueur);
}

void condorcet_paires(ballot *matrice_ballot) {
    t_mat_int_dyn *matrice_duel = creer_matrice_duel(matrice_ballot);
    afficher_matrice_duels(matrice_duel);
    larc *list_arc = larc_init(matrice_duel);
    afficher_larc(list_arc);
    int vainqueur;
    if (vainqueur_condorcet(list_arc, &vainqueur)){
        printf("Le vainqueur de Condorcet est le candidat %d\n\n", vainqueur);
    }else{
        printf("Il n'y a pas de vainqueur de Condorcet dans cette election.\n\n");
        resoudre_paradoxe(list_arc,&vainqueur);
        printf("Après résolution du paradoxe, le vainqueur de Condorcet est le candidat %d\n\n", vainqueur);
    }
    detruire_larc(list_arc);
    detruire_matrice(matrice_duel);
}