#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "matrice_string_dyn.h"
#include "matrice_int_dyn.h"
#include "listegen.h"
#include "ballotgen.h"

typedef struct s_ensemble_preference{
    int values; // Rang de préférence
    List *list; // List d'indice de candidat
} Pref;

ballot *creer_ballot(int nb_candidats, int nb_votants){
    ballot *b = malloc(sizeof(ballot));
    b->nb_candidats = nb_candidats;
    b->nb_votants = nb_votants;
    b->candidats_nom = malloc(sizeof(char*) * nb_candidats);
    b->classement = list_create();
    return b;
}

/**
 * @brief Remplit la liste des noms de candidats à partir du fichier csv
 * @param b Le ballot à remplir
 * @param classement_csv La matrice de classement à partir du fichier csv
 * @return ballot* Le ballot rempli
 */
ballot *remplir_liste_candidats(ballot *b, t_mat_char_star_dyn *classement_csv){
    int i = 0;
    char ***matrice_csv = classement_csv->tab;
    // Remplissage de la liste de candidats
    for (int i = 0; i < b->nb_candidats; i++){
        char *nom = malloc(sizeof(char) * strlen(matrice_csv[0][i + 4]) + 1);
        strcpy(nom, matrice_csv[0][i + 4]);
        b->candidats_nom[i] = nom;
    }
    return b;
}

int elem_egaux(void *elem, int value){
    Pref *elem_pref = (Pref *)elem;
    return elem_pref->values == value;
}

int elem_plus_grand(void *elem, int value){
    Pref *elem_pref = (Pref *)elem;
    return elem_pref->values > value;
} 

/**
 * @brief Remplit la matrice de classement à partir du fichier csv
 * @param b Le ballot à remplir
 * @param classement_csv La matrice de classement à partir du fichier csv
 * @return ballot* Le ballot rempli
 */
ballot *remplir_classement(ballot *b, t_mat_char_star_dyn *classement_csv){
    char ***matrice_csv = classement_csv->tab;
    int nb_candidats = b->nb_candidats;
    int nb_votants = b->nb_votants;

    for(int votant = 0; votant < nb_votants; votant++){
        // Création d'une liste d'ensemble de préférence pour un votant
        List *liste_preferences = list_create();

        for(int candidat = 0; candidat < nb_candidats; candidat++){
            // 4 colonnes et 1 ligne de plus pour ne pas prendre en compte les infos de l'élection
            int rang_preference = atoi(matrice_csv[votant + 1][candidat + 4]);
            if (rang_preference == -1) rang_preference = nb_candidats + 1;
            
            int *candidat_ptr = malloc(sizeof(int));
            *candidat_ptr = candidat;

            // CAS 1 : Aucun ensemble de candidat n'existe pour le rang trouvé
            if(contient(liste_preferences, elem_egaux, rang_preference) == false){
                // Création d'un ensemble de préférence
                Pref *new_ens_pref = malloc(sizeof(Pref));
                new_ens_pref->values = rang_preference;
                new_ens_pref->list = list_create();
                list_push_back(new_ens_pref->list, candidat_ptr);
                
                // Si le rang de préférence est -1 (considéré comme pire) ou si la liste est vide
                if(list_is_empty(liste_preferences)){
                    // Ajout de l'ensemble de candidat en fin de liste
                    list_push_back(liste_preferences, (void *)new_ens_pref);
                }else{ // Ajout dans l'ordre croissant
                    int indice_insert = trouver_indice(liste_preferences,elem_plus_grand,rang_preference);
                    list_insert_at(liste_preferences, indice_insert, new_ens_pref);
                }
            }
            // CAS 2 : Un ensemble de candidat existe pour le rang trouvé
            else{
                int indice = trouver_indice(liste_preferences, elem_egaux, rang_preference);
                Pref *ens_pref_existant = (Pref *)list_at(liste_preferences, indice);
                list_push_back(ens_pref_existant->list, candidat_ptr);
            }
        }
        // Ajout de la liste d'ensemble de préférence à la liste de votant
        list_push_back(b->classement, liste_preferences);
    }
    return b;
}

ballot *remplir_ballot(ballot *b, t_mat_char_star_dyn *classement_csv){
    // Remplissage de la liste des noms de candidats
    b = remplir_liste_candidats(b, classement_csv);
    // Remplissage de la matrice de classement
    b = remplir_classement(b, classement_csv);
    libererMatrice(classement_csv);
    return b;
}

/******************* DESTRUCTEURS *********************/

void detruire_ensemble_preference(void *elem){
    Pref *pref = (Pref *)elem;
    list_delete((ptrList *)pref->list,free);
    free(pref);
}

void detruire_liste_ensemble_preference(void *elem){
    List *list = (List *)elem;
    list_delete((ptrList *)list,detruire_ensemble_preference);
}

void detruire_ballot(ballot *b){
    for (int i = 0; i < b->nb_candidats; i++){
        free(b->candidats_nom[i]);
    }
    free(b->candidats_nom);
    list_delete((ptrList *)b->classement,detruire_liste_ensemble_preference);
    free(b);
}


/******************* UTILS *********************/

void afficher_liste_candidat(void *data) {
    printf(" %d ", *(int *)data);
}

void afficher_ensemble_preference(void *data) {
    Pref *pref = (Pref *)data;
    int rang = pref->values;
    printf("(%d)", rang);
    list_map(pref->list, afficher_liste_candidat);
    printf("\t");
}

void afficher_liste_votant(void *data) {
    List *list_pref = (List *)data;
    list_map(list_pref, afficher_ensemble_preference);
    printf("\n");
}

void afficher_ballot(ballot *b) {
    printf("Nombre de candidats : %d\n", b->nb_candidats);
    printf("Nombre de votants : %d\n", b->nb_votants);
    printf("Liste des candidats : \n");
    for (int i = 0; i < b->nb_candidats; i++) {
        printf("[%d] : %s\n",i,b->candidats_nom[i]);
    }
    printf("\n");
    printf("Classement : \n");
    list_map(b->classement, afficher_liste_votant);
}

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
    printf("\nCréation de la matrice de duel\n\n");
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