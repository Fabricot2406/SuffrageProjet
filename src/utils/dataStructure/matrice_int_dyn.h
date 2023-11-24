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


/******************* UTILS *********************/

/**
 * @brief Applique une fonction donnée à chaque élément de la matrice.
 * @param matrice Un pointeur vers la matrice dynamique.
 * @param f Un pointeur de fonction prenant un entier en paramètre et ne retournant rien.
 */
void map_matrice(t_mat_int_dyn *matrice, void (*f)(int));

/**
 * @brief Affiche une matrice dynamique d'entiers.
 * @param matrice Un pointeur vers la matrice dynamique.
 * @param not_displayed_value Valeur à ne pas afficher.
 */
void afficher_matrice(t_mat_int_dyn *matrice, int not_displayed_value);

#endif