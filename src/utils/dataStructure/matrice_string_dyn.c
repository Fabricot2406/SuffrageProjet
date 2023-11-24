#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "matrice_string_dyn.h"

#define TAILLE_MAX 65

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

/******************* UTILS *********************/

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