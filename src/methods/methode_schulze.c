/** \\file */
/**
 * @file methode_schulze.c
 * @author Fabio
 * @date 2023-11-29
 */

 #include "methode_schulze.h"

 /**

    Schulze algo :

    On prend les arcs dans l'ordre croissant.
    On retire petit à petit les arcs, à chaque itération, on vérifie si on a un vainqueur, si ce n'est pas le cas,
    on continue.
    On s'arrête lorsqu'un vainqueur est trouvé.
 
 */

bool comparer_scores(void *a, void *b) {
    arc * elem1 = a;
    arc * elem2 = b;
    return elem1->score >= elem2->score;
}

// COMMUN ENTRE TOUT (util_sd)
bool est_vainqueur(List *list_arc, int candidat){
    Iterator *it_larc = iterator_create(list_arc);
    // On parcourt la liste d'arc
    while (iterator_has_next(it_larc)){
        arc *arc_courant = iterator_current(it_larc);
        // Si le candidat est impliqué dans un arc où il est perdant
        if (arc_courant->candidat_perdant == candidat){
            // Il n'est pas vainqueur
            iterator_delete(it_larc);
            return false;
        }
        iterator_next(it_larc);
    }
    iterator_delete(it_larc);
    // Sinon il est vainqueur
    return true;
}

int trouver_vainqueur_schulze(List *list_arc, int nb_candidats, char **candidats_nom) {
    
    // Pour chaque candidat, on vérifie si il est vainqueur
    for (int candidat = 0; candidat < nb_candidats; candidat++) {
        if (est_vainqueur(list_arc, candidat)) {
            // Le vainqueur est à l'indice désigné par la variable candidat
            return candidat;
        }
    }

    // Pas de vainqueur, on retourne -1
    return -1;
}

void reduire_arcs(List *list_arc, int nb_candidats, char **candidats_nom) {
    int vainqueur;

    // On continue de retirer l'arc tant qu'on n'a pas de vainqueur
    while ((vainqueur = trouver_vainqueur_schulze(list_arc, nb_candidats, candidats_nom)) == -1) {
        list_remove_at(list_arc, 0, free);
    }

    afficherVainqueur("condorcet - méthode de Schulze", 1, 1, candidats_nom[vainqueur], 0);
}

void condorcet_schulze(t_mat_int_dyn *matrice_duel, char **candidats_nom) {
    larc *list_arc = larc_init(matrice_duel);
    
    list_arc -> larc = list_sort(list_arc -> larc, comparer_scores);

    reduire_arcs(list_arc -> larc, list_arc -> nb_candidats, candidats_nom);
    
    detruire_larc(list_arc);
}