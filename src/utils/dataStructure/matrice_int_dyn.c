/** \\file */
/**
 * @file matrice_int_dyn.c
 * @author Anthony
 * @date 2023-11-28
 */
#include "matrice_int_dyn.h"

/******************* MATRICE *********************/

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
    matrice->rows = rows;
    matrice->cols = col;
    return matrice;
}

void setPosition(t_mat_int_dyn* matrix, int value, int col, int row) {
    assert(col >= 0 && col < matrix->cols && row >= 0 && row < matrix->rows);
    matrix->mat[row][col] = value;
}

void detruire_matrice(t_mat_int_dyn *matrice){
    for(int i = 0; i < matrice->rows; i++){
        free(matrice->mat[i]);
    }
    free(matrice->mat);
    free(matrice);
}

/******************* UTILS *********************/

void log_matrice(t_mat_int_dyn *matrice, int not_displayed_value, FILE *log_file){
    for(int i = 0; i < matrice->rows; i++){
        for(int j = 0; j < matrice->cols; j++){
            if (matrice->mat[i][j] != not_displayed_value){
                fprintf(log_file, "%2d ", matrice->mat[i][j]);
            }else fprintf(log_file, "   ");
        }
        fprintf(log_file,"\n");
    }
}

void map_matrice(t_mat_int_dyn *matrice, void (*f)(int)){
    for(int i = 0; i < matrice->rows; i++){
        for(int j = 0; j < matrice->cols; j++){
            f(matrice->mat[i][j]);
        }
    }
}
