#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrice_duel.h"

typedef struct t_mat_int_dyn{
    int** mat;
    int rows;
    int cols;
}t_mat_int_dyn;

t_mat_int_dyn *creer_matrice(int rows,int col){
    t_mat_int_dyn *matrice = malloc(sizeof(t_mat_int_dyn));
    matrice->mat = (int**)malloc(rows * sizeof(int*));
    if (matrice->mat == NULL){
        printf("Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }

    // Allocation de la mémoire pour chaque ligne
    for(int i = 0; i < rows; i++){
        matrice->mat[i] = (int*)malloc(col * sizeof(int));
        if (matrice->mat[i] == NULL){
            printf("Erreur d'allocation de mémoire\n");
            exit(EXIT_FAILURE);
        }
    }

    // Initialisation de la diagonale à 0
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < col; j++){
            if(i == j){
                matrice->mat[i][j] = 0;
            }
        }
    }
    matrice->rows = rows;
    matrice->cols = col;
    return matrice;
}

void incrementer_matrice(t_mat_int_dyn *matrice, int i, int j){
    assert(i >= 0 && i < matrice->rows && j >= 0 && j < matrice->cols);
    assert(i != j);
    matrice->mat[i][j]++;
}

void detruire_matrice(t_mat_int_dyn *matrice){
    for(int i = 0; i < matrice->rows; i++){
        free(matrice->mat[i]);
    }
    free(matrice->mat);
    free(matrice);
}

void map_matrice(t_mat_int_dyn *matrice, void (*f)(int)){
    for(int i = 0; i < matrice->rows; i++){
        for(int j = 0; j < matrice->cols; j++){
            f(matrice->mat[i][j]);
        }
    }
}