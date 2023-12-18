/**
 * @file arc.c
 * @author Anthony
 * @brief Structure de données pour les arcs du graphe.
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

/**
 * @brief Fonction de comparaison de deux arcs.
 * @details Fonction utilisée pour le tri de la liste d'arcs.
 * @param a Un arc.
 * @param b Un arc.
 * @return int 1 si a > b, -1 si a < b, 0 si a = b.
 */
int compare_arc(const void *a, const void *b) {
    return ((arc *)b)->score - ((arc *)a)->score;
}

/**
 * @brief Complète une liste d'arcs avec des pourcentages de victoire entre les candidats.
 * @param tab_arc Un tableau d'arcs à compléter.
 * @param matrice_duel Une matrice représentant les résultats des duels entre candidats.
 * @pre La liste d'arcs est initialisée.
 * @pre La matrice de duel est initialisée. 
 *      La matrice est carrée et de taille nb_candidats x nb_candidats.
 *      La diagonale de la matrice est nulle.
 * @post La liste d'arcs est complétée avec les arcs de la matrice de duel.
 */
void larc_complete(larc *tab_arc, t_mat_int_dyn *matrice_duel){
    List *list = tab_arc->larc;
    int nb_candidats = tab_arc->nb_candidats;
    int nb_votes, nb_votes_a, nb_votes_b, cand_a, cand_b = 0;
    // On parcourt l'ensemble des duels possibles
    // Les duels entre un candidat et lui-même ne sont pas pris en compte
    for (int candidat_1 = 0; candidat_1 < nb_candidats; candidat_1++) {
        for (int candidat_2 = candidat_1 + 1; candidat_2 < nb_candidats; candidat_2++) {
            nb_votes_a = matrice_duel->mat[candidat_1][candidat_2];
            nb_votes_b = matrice_duel->mat[candidat_2][candidat_1];
            // On calcule le nombre de voix entre les deux candidats
            nb_votes = (nb_votes_a >= nb_votes_b) ? nb_votes_a - nb_votes_b : nb_votes_b - nb_votes_a;
            // On détermine le candidat gagnant et perdant : a > b
            cand_a = (nb_votes_a >= nb_votes_b) ? candidat_1 : candidat_2;
            cand_b = (nb_votes_a >= nb_votes_b) ? candidat_2 : candidat_1;
            // On ajoute l'arc dans la liste
            if (nb_votes) {
                arc *a = arc_create(cand_a, cand_b, nb_votes);
                insert_sorted(list, a, compare_arc);
            }
        }
    }
}

larc* larc_init(t_mat_int_dyn *matrice_duel){
    assert(matrice_duel != NULL);
    larc *l_arc = malloc(sizeof(larc));
    if (l_arc == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire\n");
        exit(EXIT_FAILURE);
    }
    l_arc->larc = list_create();
    l_arc->nb_candidats = matrice_duel->cols;
    // On complète la liste d'arcs avec les arcs de la matrice de duel
    larc_complete(l_arc, matrice_duel);
    return l_arc;
}

/**
 * @brief Operateur de suppression d'un arc.
 * @param elem l'arc à supprimer
 */
void arc_delete(void *elem){
    assert(elem != NULL);
    arc *a = (arc *)elem;
    free(a);
}

void larc_delete(larc *tab_arc){
    assert(tab_arc != NULL);
    List *list = tab_arc->larc;
    list_delete(list,arc_delete);
    free(tab_arc);
}

void candidat_delete(List *list_arc,int candidat){
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
 * @brief Affiche un arc dans le fichier de log.
 * @param input l'arc à afficher
 * @param log_file le fichier de log
 */
void arc_log(void* input, FILE *log_file){
    arc *a = (arc *)input;
    fprintf(log_file, "(%d > %d: %d)\n",a->candidat_gagnant, a->candidat_perdant, a->score);
}

void larc_log(larc *tab_arc, FILE *log_file){
    fprintf(log_file ,"Liste des arcs : ");
    fprintf(log_file ,"(indice_gagnant > indice_perdant: score)\n");
    List *list = tab_arc->larc;
    // On parcourt la liste des arcs
    // Creer un iterateur
    Iterator *it_larc = iterator_create(list);
    // On parcourt la liste des arcs
    while (iterator_has_next(it_larc)){
        arc *arc_courrant = iterator_current(it_larc);
        arc_log(arc_courrant, log_file);
        iterator_next(it_larc);
    }
    iterator_delete(it_larc);
    fprintf(log_file, "\n");
}