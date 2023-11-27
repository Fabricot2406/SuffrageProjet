#include "duel.h"

/**
 * @brief Incrémente la matrice de duel en fonction des préférences passées en paramètre.
 * @details Pour chaque préférence du sujet, on incrémente tous les duels avec les préférences de l'adversaire.
 * @param matrice_duel La matrice de duel à incrémenter
 * @param pref_sujet La préférence du sujet
 * @param pref_adverse La préférence de l'adversaire
 */
void creer_duels(t_mat_int_dyn *matrice_duel,Pref *pref_sujet,Pref *pref_adverse){
    List *liste_sujet = pref_sujet->list;
    List *liste_adverse = pref_adverse->list;
    for (int i_sujet = 0; i_sujet < list_size(liste_sujet); i_sujet++)
    {
        int indice_sujet = *(int *)list_at(liste_sujet, i_sujet);
        for (int i_adverse = 0; i_adverse < list_size(liste_adverse); i_adverse++)
        {
            int indice_adverse = *(int *)list_at(liste_adverse, i_adverse);
            matrice_duel->mat[indice_sujet][indice_adverse] += 1;
        }
    }
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
            Pref *pref_adverse = (Pref *)list_at(liste_preferences, i+1);
            creer_duels(matrice_duel,pref_sujet,pref_adverse);
        }
    }
    return matrice_duel;
}

/******************* UTILS *********************/

void afficher_matrice_duels(t_mat_int_dyn *matrice_duel){
    printf("\nAffichage de la matrice de duel\n\n");
    afficher_matrice(matrice_duel, 0);
    printf("\n");
}