#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "matrice_string_dyn.h"

#define TAILLE_MAX 65

typedef struct s_matriceVote{
    int nbLignes;
    int nbColonnes;
    char ***tab;
}t_mat_char_star_dyn;

t_mat_char_star_dyn *creerMatrice (){
    //initialisation de la structure
    t_mat_char_star_dyn *matrice;
    if ((matrice=malloc(sizeof(t_mat_char_star_dyn)))==NULL){
        fprintf(stderr,"Erreur lors de l'allocation de la strcture.\n");
        return NULL;
    }
    matrice->nbLignes=0;
    matrice->nbColonnes=0;
    //initialisation de la matrice
    if ((matrice->tab=malloc(sizeof(char**)))==NULL){
        fprintf(stderr,"Erreur lors de l'allocation du tableau de lignes.\n");
        return NULL;
    }
    if ((matrice->tab[0]=malloc(sizeof(char*)))==NULL){
        fprintf(stderr,"Erreur lors de l'allocation du tableau de colonnes.\n");
        return NULL;
    }
    if ((matrice->tab[0][0]=malloc(TAILLE_MAX*sizeof(char)))==NULL){
        fprintf(stderr,"Erreur lors de l'allocation des cellules.\n");
        return NULL;
    }
    return matrice;   
}

int trouverElem(t_mat_char_star_dyn *matrice, char *elem, int *ligne, int *colonne){
    //Si la matrice est nulle on renvoie une erreur
    if (matrice==NULL){
        fprintf(stderr,"Matrice non valide.\n");
        return 0;
    }
    //On initialise les indices de ligne et de colonne à -1
    *ligne=-1;
    *colonne=-1;
    //On parcourt la matrice
    for (int i=0;i<matrice->nbLignes;i++){
        for (int j=0;j<matrice->nbColonnes;j++){
            //On compare chaque cellule à l'element recherché
            if (!strcmp(elem,matrice->tab[i][j])){
                //Si on trouve l'element on met à jour les indices de ligne et de colonne
                *ligne=i;
                *colonne=j;
            }
        }
        //On passe à la ligne suivante
    }
    return *ligne!=1 && *colonne!=-1;
}

void libererMatrice(t_mat_char_star_dyn *matrice){
    //Si la matrice est nulle on renvoie une erreur
    if (matrice==NULL){
        return;
    }
    for (int i=0;i<matrice->nbLignes;i++){
        for (int j=0;j<matrice->nbColonnes;j++){
            //On libère chaque cellule de la matrice
            free(matrice->tab[i][j]);
        }
        //On libère chaque ligne de la matrice
        free(matrice->tab[i]);
    }
    //On libère la matrice
    free(matrice->tab);
    //On réinitialise la structure
    matrice->nbLignes=0;
    matrice->nbColonnes=0;
    //On libère la structure
    free(matrice);
    return ; 
}

/******************* ITERATEUR *********************/

typedef enum {
    ROW,
    COLUMN
} TraverseType;

typedef enum {
    FORWARD,
    BACKWARD
} IteratorDirection;

typedef struct {
    t_mat_char_star_dyn *matrix; // Matrice sur laquelle on itère
    int current_row; // Ligne courante
    int current_col; // Colonne courante
    TraverseType traverse_type; // Type de parcours
    IteratorDirection direction; // Direction de l'itérateur
} MatrixIterator;


MatrixIterator createMatrixIterator(t_mat_char_star_dyn *matrix, TraverseType traverse_type, IteratorDirection direction) {
    MatrixIterator *iterator = malloc(sizeof(iterator));
    iterator->matrix = matrix;
    iterator->traverse_type = traverse_type;
    iterator->direction = direction;
    iterator->current_row = 0;
    iterator->current_col = 0;
    return *iterator;
}

char *currentValue(const MatrixIterator *iterator) {
    return iterator->matrix->tab[iterator->current_row][iterator->current_col];
}

bool hasMoreElements(const MatrixIterator *iterator) {
    if (iterator->traverse_type == ROW) {
        if (iterator->direction == FORWARD) {
            // valeur de retour : vrai si on est pas à la dernière ligne
            return iterator->current_row < iterator->matrix->nbLignes - 1;
        } else { // direction == BACKWARD
            // valeur de retour : vrai si on est pas à la première ligne
            return iterator->current_row >= 1;
        }
    } else { // traverse_type == COLUMN
        if (iterator->direction == FORWARD) {
            // valeur de retour : vrai si on est pas à la dernière colonne
            return iterator->current_col < iterator->matrix->nbColonnes - 1;
        } else { // direction == BACKWARD
            // valeur de retour : vrai si on est pas à la première colonne
            return iterator->current_col >= 1;
        }
    }
}

void moveToNextElement(MatrixIterator *iterator) {
    switch (iterator->traverse_type) {
        // CAS DU PARCOURS EN LIGNE
        case ROW:
            switch (iterator->direction) {
                // CAS DU PARCOURS EN LIGNE VERS L'AVANT
                case FORWARD:
                    iterator->current_col++;
                    // Si on est à la dernière colonne, on passe à la ligne suivante
                    if (iterator->current_col >= iterator->matrix->nbColonnes) {
                        iterator->current_col = 0;
                        if (iterator->current_row < iterator->matrix->nbLignes - 1){
                            iterator->current_row++;
                        }
                    }break;
                // CAS DU PARCOURS EN LIGNE VERS L'ARRIERE
                case BACKWARD:
                    iterator->current_col--;
                    // Si on est à la première colonne, on passe à la ligne précédente
                    if (iterator->current_col < 0) {
                        iterator->current_col = iterator->matrix->nbColonnes - 1;
                        if (iterator->current_row >= 1)
                            iterator->current_row--;
                    }break;
            }break;
        // CAS DU PARCOURS EN COLONNE
        case COLUMN:
            switch (iterator->direction) {
                // CAS DU PARCOURS EN COLONNE VERS L'AVANT
                case FORWARD:
                    iterator->current_row++;
                    // Si on est à la dernière ligne, on passe à la colonne suivante
                    if (iterator->current_row >= iterator->matrix->nbLignes) {
                        iterator->current_row = 0;
                        if (iterator->current_col < iterator->matrix->nbColonnes - 1)
                            iterator->current_col++;
                    }break;
                // CAS DU PARCOURS EN COLONNE VERS L'ARRIERE
                case BACKWARD:
                    iterator->current_row--;
                    // Si on est à la première ligne, on passe à la colonne précédente
                    if (iterator->current_row < 0) {
                        iterator->current_row = iterator->matrix->nbLignes - 1;
                        if (iterator->current_col >= 1)
                            iterator->current_col--;
                    }break;
            }break;
    }
}

void setPosition(MatrixIterator *iterator, int position) {
    switch (iterator->traverse_type) {
        // CAS DU PARCOURS EN LIGNE
        case ROW:
            assert(position >= 0 && position < iterator->matrix->nbLignes);
            iterator->current_row = position;
            break;
        // CAS DU PARCOURS EN COLONNE
        case COLUMN:
            assert(position >= 0 && position < iterator->matrix->nbColonnes);
            iterator->current_col = position;
            break;
    }
}

void libererIterateur(MatrixIterator *iterator) {
    free(iterator);
}


/******************* UTILITAIRE *********************/

void afficherMatrice(t_mat_char_star_dyn *matrice){
    //Si la matrice est nulle on renvoie une erreur
    if (matrice==NULL){
        fprintf(stderr,"Matice non valide.\n");
        return;
    }
    for (int i=0;i<matrice->nbLignes;i++){
        for (int j=0;j<matrice->nbColonnes;j++){
            //On affiche chaque cellule de la matrice
            printf("%s\t",matrice->tab[i][j]);
        }
        //On passe à la ligne suivante
        printf("\n");
    }
}

void afficherLigne(t_mat_char_star_dyn *matrice, int ligne){
    //Si la matrice est nulle on renvoie une erreur
    if (matrice==NULL){
        fprintf(stderr,"Matice non valide.\n");
        return;
    }
    //On affiche chaque cellule de la ligne
    for (int j=0;j<matrice->nbColonnes;j++){

        int longueurChaine = strlen(matrice->tab[0][j]);
        int largeurChamp = 40 - longueurChaine;

        printf("%s: %*s \n",matrice->tab[0][j], largeurChamp, matrice->tab[ligne][j]);
    }
}