#include "arc.h"

arc* arc_create(int candidat_gagnant, int candidat_perdant, int nb_votes){
    arc *a = malloc(sizeof(arc));
    if (a == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire\n");
        exit(EXIT_FAILURE);
    }
    a->candidat_gagnant = candidat_gagnant;
    a->candidat_perdant = candidat_perdant;
    a->nb_votes = nb_votes;
    return a;
}


/**
 * @brief Fonction qui permet de completer la liste des arcs à partir de la matrice de duel.
 * @param tab_arc La liste des arcs à compléter
 * @param matrice_duel La matrice de duel
 */
void larc_complete(larc *tab_arc, t_mat_int_dyn *matrice_duel){
    List *list = tab_arc->larc;
    int nb_candidats = tab_arc->nb_candidats;
    int nb_votes = 0;
    int cand_a = 0;
    int cand_b = 0;
    for (int candidat_1 = 0; candidat_1 < nb_candidats; candidat_1++) {
        for (int candidat_2 = candidat_1 + 1; candidat_2 < nb_candidats; candidat_2++) {
            int nb_votes_a = matrice_duel->mat[candidat_1][candidat_2];
            int nb_votes_b = matrice_duel->mat[candidat_2][candidat_1];
            
            int nb_votes = (nb_votes_a >= nb_votes_b) ? nb_votes_a : nb_votes_b;
            int cand_a = (nb_votes_a >= nb_votes_b) ? candidat_1 : candidat_2;
            int cand_b = (nb_votes_a >= nb_votes_b) ? candidat_2 : candidat_1;
            if (nb_votes != 0) {
                arc *a = arc_create(cand_a, cand_b, nb_votes);
                list_push_back(list, (void *)a);
            }
        }
    }
}

larc* larc_init(t_mat_int_dyn *matrice_duel){
    larc *l_arc = malloc(sizeof(larc));
    if (l_arc == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire\n");
        exit(EXIT_FAILURE);
    }
    l_arc->larc = list_create();
    List *list = l_arc->larc;
    l_arc->nb_candidats = matrice_duel->cols;
    larc_complete(l_arc, matrice_duel);
    return l_arc;
}

void detruire_arc(void *elem){
    arc *a = (arc *)elem;
    free(a);
}

void detruire_larc(larc *tab_arc){
    List *list = tab_arc->larc;
    list_delete((ptrList *)list,detruire_arc);
    free(tab_arc);
}

/******************* UTILS *********************/

/**
 * @brief Fonction qui permet d'afficher la liste des arcs.
 * @param list La liste des arcs à afficher
 */
void afficher_arc(void* input){
    arc *a = (arc *)input;
    printf("(%d > %d: %d)\n",a->candidat_gagnant, a->candidat_perdant, a->nb_votes);
}

void afficher_larc(larc *tab_arc){
    printf("Liste des arcs :\n\n");
    List *list = tab_arc->larc;
    list_map(list, afficher_arc);
    printf("\n");
}