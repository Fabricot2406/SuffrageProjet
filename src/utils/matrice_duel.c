#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "matrice_duel.h"

//******************* MATRICE *********************//

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

// Fonction pour positionner un entier à une position donnée
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

//******************* ITERATEUR *********************//

// Direction de l'itérateur
typedef enum {
    FORWARD,
    BACKWARD
} IteratorDirection;

// Type de parcours (LIGNE ou COLONNE)
typedef enum {
    ROW,
    COLUMN,
    DIAGONAL
} TraverseType;

// Votre structure d'itérateur
typedef struct {
    t_mat_int_dyn* matrix;
    int current_row;
    int current_col;
    IteratorDirection direction;
    TraverseType traverse_type;
} MatrixIterator;

// Fonction pour initialiser un itérateur
MatrixIterator *createMatrixIterator(t_mat_int_dyn* matrix, IteratorDirection direction, TraverseType traverse_type) {
    MatrixIterator *iterator = malloc(sizeof(MatrixIterator));
    iterator->matrix = matrix;
    iterator->direction = direction;
    iterator->traverse_type = traverse_type;

    if (direction == FORWARD) {
        iterator->current_row = 0;
        iterator->current_col = 0;
    } else {
        iterator->current_row = matrix->rows - 1;
        iterator->current_col = matrix->cols - 1;
    }

    return iterator;
}

// Fonction pour vérifier si l'itérateur a encore des éléments
bool hasMoreElements(const MatrixIterator* iterator) {
    if (iterator->direction == FORWARD) {
        return iterator->current_row < iterator->matrix->rows;
    } else {
        return iterator->current_row >= 0;
    }
}

// Fonction pour obtenir la valeur courante de la matrice
int getCurrentValue(const MatrixIterator* iterator) {
    return iterator->matrix->mat[iterator->current_row][iterator->current_col];
}

// Fonction pour déplacer l'itérateur vers l'élément suivant
void moveToNextElement(MatrixIterator* iterator) {
    if (iterator->direction == FORWARD) {
        iterator->current_col++;
        if (iterator->current_col >= iterator->matrix->cols) {
            iterator->current_col = 0;
            iterator->current_row++;
        }
    } else {
        iterator->current_col--;
        if (iterator->current_col < 0) {
            iterator->current_col = iterator->matrix->cols - 1;
            iterator->current_row--;
        }
    }
}


//******************* UTILS *********************//

void map_matrice(t_mat_int_dyn *matrice, void (*f)(int)){
    for(int i = 0; i < matrice->rows; i++){
        for(int j = 0; j < matrice->cols; j++){
            f(matrice->mat[i][j]);
        }
    }
}
