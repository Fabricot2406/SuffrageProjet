/** \\file */
/**
 * @file methode_paires.c
 * @author Anthony
 * @date 2023-11-28
 */
#include "methode_paires.h"

int resoudre_paradoxe(larc *list_arc, int *vainqueur){
    int nb_circuit = 0;
    int nb_candidats = list_arc->nb_candidats;
    graphe *g = creation_graphe(nb_candidats);
    Iterator *it = iterator_create(list_arc->larc);
    // Pour chaque arc de la liste, on ajoute une succession dans le graphe
    while (iterator_has_next(it)){
        arc *a = iterator_current(it);
        printf("Ajout de la succession %d -> %d\n", a->candidat_gagnant, a->candidat_perdant);
        ajout_succession(g->graphe[a->candidat_gagnant], g->graphe[a->candidat_perdant]);
        // Si un circuit est détecté dans le graphe après l'ajout de l'arc
        sommet *s_current = g->graphe[a->candidat_gagnant];
        initialiser_status(g, s_current->indice);
        if (circuits(g, s_current)){
            nb_circuit++;
            // On supprime l'arc de la liste et on supprime la succession dans le graphe
            delete_succession(g->graphe[a->candidat_gagnant]);
            int index = iterator_index(it);
            iterator_prev(it);
            list_remove_at(list_arc->larc, index, free);
        }
        iterator_next(it);
    }
    iterator_delete(it);
    detruire_graphe(g);
    vainqueur_condorcet(list_arc, vainqueur);
    return nb_circuit;
}

void condorcet_paires(ballot *matrice_ballot) {
    t_mat_int_dyn *matrice_duel = creer_matrice_duel(matrice_ballot);
    afficher_matrice_duels(matrice_duel);
    larc *list_arc = larc_init(matrice_duel);
    afficher_larc(list_arc);
    int vainqueur;
    int nb_circuit = resoudre_paradoxe(list_arc,&vainqueur);
    char *nom_vainqueur = matrice_ballot->candidats_nom[vainqueur];
    printf("Le vainqueur de Condorcet est %s\n\n", nom_vainqueur);
    afficher_larc(list_arc);
    detruire_larc(list_arc);
    detruire_matrice(matrice_duel);
}


List *determiner_classement(larc *list_arc){
    List *larc = list_arc->larc;
    int nb_candidats = list_arc->nb_candidats;
    List *candidat = list_create();
    for (int i_candidat = 0; i_candidat < nb_candidats; i_candidat++){
        int *elem = malloc(sizeof(int));
        *elem = i_candidat;
        list_push_back(candidat,elem);
    }
    
    List *classement = list_create();
    
    return classement;
}


int determiner_vainqueur(List *list_arc,List *classement,List *candidats){
    Iterator *it_c_restant = iterator_create(candidats);
    while(iterator_has_next(it_c_restant)){
        int *c_courrant = iterator_current(it_c_restant);
        if (est_vainqueur(list_arc,*c_courrant)){
            int *candidats_gagnant = malloc(sizeof(int));
            *candidats_gagnant = *c_courrant;
            list_push_back(classement,candidats_gagnant);
        }
    }
}


bool est_vainqueur(List *list_arc, int candidat){
    Iterator *it_larc = iterator_create(list_arc);
    while (iterator_has_next(it_larc)){
        arc *arc_courant = iterator_current(it_larc);
        if (arc_courant->candidat_perdant == candidat){
            iterator_delete(it_larc);
            return false;
        }
        iterator_next(list_arc);
    }
    return true;
}