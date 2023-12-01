/** \\file */
/**
 * @file arc.c
 * @author Anthony
 * @date 2023-11-28
 */
#include "arc.h"

arc* arc_create(int candidat_gagnant, int candidat_perdant, int score){
    arc *a = malloc(sizeof(arc));
    if (a == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire\n");
        exit(EXIT_FAILURE);
    }
    a->candidat_gagnant = candidat_gagnant;
    a->candidat_perdant = candidat_perdant;
    a->score = score;
    return a;
}


double calculerPourcentage(int score1, int score2) {
    int totalScores = score1 + score2;
    if (totalScores == 0) {
        // Éviter une division par zéro
        return 0.0;
    }
    double pourcentage = ((double)score1 / totalScores) * 100.0;
    return pourcentage;
}

int compare_arc(const void *a, const void *b) {
    return ((arc *)b)->score - ((arc *)a)->score;
}

/**
 * @brief Complète une liste d'arcs avec des pourcentages de victoire entre les candidats.
 * @param tab_arc Un tableau d'arcs à compléter.
 * @param matrice_duel Une matrice représentant les résultats des duels entre candidats.
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
            
            int nb_votes = (nb_votes_a >= nb_votes_b) ? nb_votes_a - nb_votes_b : nb_votes_b - nb_votes_a;
            int cand_a = (nb_votes_a >= nb_votes_b) ? candidat_1 : candidat_2;
            int cand_b = (nb_votes_a >= nb_votes_b) ? candidat_2 : candidat_1;
            if (nb_votes != 0) {
                arc *a = arc_create(cand_a, cand_b, nb_votes);
                insert_sorted(list, a, compare_arc);
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
    list_delete(list,detruire_arc);
    free(tab_arc);
}

void supprimer_candidat(List *list_arc,int candidat){
    Iterator *it_larc = iterator_create(list_arc);
    // On parcourt la liste des arcs
    while (iterator_has_next(it_larc)){
        arc *arc_courrant = iterator_current(it_larc);
        int indice_courrant = iterator_index(it_larc);
        // Si l'arc contient le candidat, on le supprime de la liste
        // Candidat gagnant
        if (arc_courrant->candidat_gagnant == candidat){
            // On se place sur l'élément précédent pour ne pas sauter d'élément
            iterator_prev(it_larc);
            list_remove_at(list_arc,indice_courrant,free);
        }
        // Candidat perdant
        else if(arc_courrant->candidat_perdant == candidat){
            iterator_prev(it_larc);
            list_remove_at(list_arc,indice_courrant,free);
        }
        iterator_next(it_larc);
    }
    // Libération de la mémoire
    iterator_delete(it_larc);
}

/******************* UTILS *********************/

/**
 * @brief Fonction qui permet d'afficher la liste des arcs.
 * @param list La liste des arcs à afficher
 */
void afficher_arc(void* input){
    arc *a = (arc *)input;
    printf("(%d > %d: %d)\n",a->candidat_gagnant, a->candidat_perdant, a->score);
}

void afficher_larc(larc *tab_arc){
    printf("Liste des arcs :\n\n");
    List *list = tab_arc->larc;
    list_map(list, afficher_arc);
    printf("\n");
}