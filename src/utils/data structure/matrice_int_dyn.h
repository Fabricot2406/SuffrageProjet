/**
 * @file matrice_int_dyn.c
 * @author Anthony
 * @brief Structure de donnée correspondant à une matrice dynamique contenant des entiers.
 * @version 1.0
 * @date 2021-11-23
 */

#ifndef __MATRICE_INT_DYN_H__
#define __MATRICE_INT_DYN_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

/**
 * @struct t_mat_int_dyn
 * @brief Structure représentant une matrice dynamique d'entiers.
 *        Contient un tableau bidimensionnel, le nombre de lignes et le nombre de colonnes.
 */
typedef struct t_mat_int_dyn{
    int** mat; /**< Tableau bidimensionnel représentant la matrice */
    int rows; /**< Nombre de lignes de la matrice */
    int cols; /**< Nombre de colonnes de la matrice */
} t_mat_int_dyn;

/**
 * @brief Crée une nouvelle matrice dynamique d'entiers.
 * @param rows Le nombre de lignes de la matrice.
 * @param col Le nombre de colonnes de la matrice.
 * @return Un pointeur vers la nouvelle matrice dynamique.
 */
t_mat_int_dyn* creer_matrice(int rows, int col);


/**
 * @brief Détruit une matrice dynamique d'entiers, libérant la mémoire allouée.
 * @param matrice Un pointeur vers la matrice dynamique à détruire.
 */
void detruire_matrice(t_mat_int_dyn* matrice);


/******************* ITERATEUR *********************/

/**
 * @enum IteratorDirection
 * @brief Direction de l'itérateur (FORWARD ou BACKWARD)
*/
typedef enum {
    FORWARD,
    BACKWARD
} IteratorDirection;

/**
 * @enum TraverseType
 * @brief Type de parcours (LIGNE, COLONNE ou DIAGONALE)
*/
typedef enum {
    ROW,
    COLUMN,
    DIAGONAL
} TraverseType;

/**
 * @struct MatrixIterator
 * @brief Structure représentant un itérateur sur une matrice dynamique.
*/
typedef struct {
    t_mat_int_dyn* matrix;
    int current_row;
    int current_col;
    IteratorDirection direction;
    TraverseType traverse_type;
} MatrixIterator;

/**
 * @brief Crée un nouvel itérateur sur une matrice dynamique.
 * @param matrix Un pointeur vers la matrice dynamique.
 * @param direction La direction de l'itérateur (FORWARD ou BACKWARD).
 * @param traverse_type Le type de parcours (ROW, COLUMN ou DIAGONAL).
 * @return Un pointeur vers le nouvel itérateur.
 */
MatrixIterator *createMatrixIterator(t_mat_int_dyn* matrix, IteratorDirection direction, TraverseType traverse_type);

/**
 * @brief Vérifie si l'itérateur a encore des éléments à parcourir.
 * @param iterator Un pointeur vers l'itérateur.
 * @return Vrai si l'itérateur a encore des éléments à parcourir, faux sinon.
 */
bool hasMoreElements(const MatrixIterator* iterator);

/**
 * @brief Obtient la valeur courante de la matrice.
 * @param iterator Un pointeur vers l'itérateur.
 * @return La valeur courante de la matrice.
 */
int getCurrentValue(const MatrixIterator* iterator);

/**
 * @brief Déplace l'itérateur vers l'élément suivant.
 * @param iterator Un pointeur vers l'itérateur.
*/
void moveToNextElement(MatrixIterator* iterator);

/******************* UTILS *********************/

/**
 * @brief Applique une fonction donnée à chaque élément de la matrice.
 * @param matrice Un pointeur vers la matrice dynamique.
 * @param f Un pointeur de fonction prenant un entier en paramètre et ne retournant rien.
 */
void map_matrice(t_mat_int_dyn *matrice, void (*f)(int));

#endif