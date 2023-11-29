/** \\file */
/**
 * @file duel.c
 * @author Anthony
 * @date 2023-11-28
 */
#include "duel.h"

/**
 * @brief Crée les duels entre le sujet et les adversaires en mettant à jour la matrice de duel.
 *
 * Cette fonction prend une matrice de duel, un sujet, et un itérateur sur la liste des préférences du sujet.
 * Elle parcourt les préférences du sujet et, pour chaque adversaire, elle parcourt les préférences de l'adversaire,
 * incrémentant la matrice de duel pour chaque paire de candidats.
 *
 * @param matrice_duel La matrice de duel à mettre à jour.
 * @param pref_sujet La préférence du sujet.
 * @param it Un itérateur sur la liste des préférences.
 */
void creer_duels(t_mat_int_dyn *matrice_duel, Pref *pref_sujet, Iterator *it) {
    // Récupération de la liste des préférences du sujet et création d'un itérateur sur celle-ci
    List *liste_sujet = pref_sujet->list;
    Iterator *it_sujet = iterator_create(liste_sujet);
    // Sauvegarde de la position initiale de l'itérateur global
    int index_init = iterator_index(it);

    // Parcours des préférences du sujet
    while (iterator_has_next(it_sujet)) {
        // Récupération de l'indice du candidat sujet
        int indice_sujet = *(int *)iterator_current(it_sujet);

        // Parcours des préférences des adversaires
        while (iterator_has_next(it)) {
            // Récupération de la préférence de l'adversaire et de sa liste de préférences
            Pref *pref_adverse = (Pref *)iterator_current(it);
            List *liste_adverse = pref_adverse->list;
            // Création d'un itérateur sur la liste de préférences de l'adversaire
            Iterator *it_adverse = iterator_create(liste_adverse);

            // Parcours des préférences de l'adversaire et mise à jour de la matrice de duel
            while (iterator_has_next(it_adverse)) {
                int indice_adverse = *(int *)iterator_current(it_adverse);
                matrice_duel->mat[indice_sujet][indice_adverse] += 1;
                iterator_next(it_adverse);
            }

            iterator_delete(it_adverse);
            iterator_next(it);
        }

        // Réinitialisation de l'itérateur global à sa position initiale
        set_position(it, index_init);
        iterator_next(it_sujet);
    }
    iterator_delete(it_sujet);
}

t_mat_int_dyn *creer_matrice_duel(ballot *b){
    int nb_candidats = b->nb_candidats;
    int nb_votants = b->nb_votants;
    t_mat_int_dyn *matrice_duel = creer_matrice(nb_candidats, nb_candidats);
    // Initialisation de la matrice à 0
    for(int i = 0; i < nb_candidats; i++){
        for(int j = 0; j < nb_candidats; j++){
            matrice_duel->mat[i][j] = 0;
        }
    }
    for(int votant = 0; votant < nb_votants; votant++){
        List *liste_preferences = (List *)list_at(b->classement, votant);
        for (int i = 0; i < list_size(liste_preferences) - 1; i++)
        {
            Pref *pref_sujet = (Pref *)list_at(liste_preferences, i);
            Iterator *it = iterator_create(liste_preferences);
            set_position(it, i+1);
            creer_duels(matrice_duel,pref_sujet,it);
            iterator_delete(it);
        }
    }
    return matrice_duel;
}

/******************* UTILS *********************/

void afficher_matrice_duels(t_mat_int_dyn *matrice_duel){
    printf("\nMatrice de duel :\n\n");
    afficher_matrice(matrice_duel, 0);
    printf("\n");
}