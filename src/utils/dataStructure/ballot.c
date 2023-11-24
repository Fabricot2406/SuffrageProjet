#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "matrice_int_dyn.h"
#include "matrice_string_dyn.h"

typedef struct ballot_s{
    char **candidats_nom;
    int nb_candidats;
    int nb_votants;
    t_mat_int_dyn *classement;
} ballot;

ballot *creer_ballot(int nb_candidats, int nb_votants){
    ballot *b = malloc(sizeof(ballot));
    b->nb_candidats = nb_candidats;
    b->nb_votants = nb_votants;
    b->candidats_nom = malloc(sizeof(char*) * nb_candidats);
    b->classement = creer_matrice(nb_votants, nb_candidats+1);
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

/**
 * @brief Remplit la matrice de classement à partir du fichier csv
 * @param b Le ballot à remplir
 * @param classement_csv La matrice de classement à partir du fichier csv
 * @return ballot* Le ballot rempli
 */
ballot *remplir_classement(ballot *b, t_mat_char_star_dyn *classement_csv){
    int i = 0;
    int j = 0;

    int **matrice_classement = b->classement->mat;
    char ***matrice_csv = classement_csv->tab;

    // Initialisation de la matrice de classement à -1 :
    for(i = 0; i < b->nb_votants; i++){
        for(j = 0; j < b->nb_candidats + 1; j++){
            matrice_classement[i][j] = -1;
        }
    }

    // Remplissage du classement
    for(i = 0; i < b->nb_votants; i++){
        for(j = 0; j < b->nb_candidats; j++){
            // Récupération de l'indice du candidat
            // i + 1 : 1 ligne pour les infos de l'élection
            // j + 4 : 4 colonnes pour les infos de l'élection
            int index_candidat = atoi(matrice_csv[i + 1][j + 4]);
            
            // Enlever 1 si l'indice est supérieur à 0
            if (index_candidat > 0){
                index_candidat--;
            }else if (index_candidat == -1){
                index_candidat = b->nb_candidats;
            }
            // Ajouter le candidat à la matrice si la case est vide
            // Case considérée comme vide si elle contient -1
            if(matrice_classement[i][index_candidat] < 0 ){
                matrice_classement[i][index_candidat] = j;
            }
        }
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

void detruire_ballot(ballot *b){
    for (int i = 0; i < b->nb_candidats; i++){
        free(b->candidats_nom[i]);
    }
    free(b->candidats_nom);
    detruire_matrice(b->classement);
    free(b);
}

/******************* UTILS *********************/

int fav_candidat(ballot *b,int num_votant){
    int i = 0;
    int *ligne_votant = b->classement->mat[num_votant];
    while (ligne_votant[i] == -1) i++;
    return ligne_votant[i];
}


