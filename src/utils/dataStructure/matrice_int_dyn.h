/**
 * @file matrice_int_dyn.h
 * @author Anthony
 * @brief Structure de donnée correspondant à une matrice dynamique contenant des entiers.
 * @date 2021-11-23
 */

#ifndef __MATRICE_INT_DYN_H__
#define __MATRICE_INT_DYN_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

/******************* STRUCTURE *********************/

/**
 * @struct t_mat_int_dyn
 * @brief Structure représentant une matrice dynamique d'entiers.
 *        Contient un tableau bidimensionnel, le nombre de lignes et le nombre de colonnes.
 */
typedef struct t_mat_int_dyn{
    int** mat; // Tableau bidimensionnel représentant la matrice
    int rows; // Nombre de lignes de la matrice
    int cols; // Nombre de colonnes de la matrice
} t_mat_int_dyn;

/******************* CONSTRUCTEUR *********************/

/**
 * @brief Crée une nouvelle matrice dynamique d'entiers.
 * @param rows Le nombre de lignes de la matrice.
 * @param col Le nombre de colonnes de la matrice.
 * @return Un pointeur vers la nouvelle matrice dynamique.
 */
t_mat_int_dyn* mat_int_create(int rows, int col);


/**
 * @brief Détruit une matrice dynamique d'entiers, libérant la mémoire allouée.
 * @param matrice Un pointeur vers la matrice dynamique à détruire.
 */
void mat_int_delete(t_mat_int_dyn* matrice);


/******************* UTILS *********************/

/**
 * @brief Applique une fonction donnée à chaque élément de la matrice.
 * @param matrice Un pointeur vers la matrice dynamique.
 * @param f Un pointeur de fonction prenant un entier en paramètre et ne retournant rien.
 */
void mat_int_map(t_mat_int_dyn *matrice, void (*f)(int));

/**
 * @brief Remplit un fichier de log avec la matrice dynamique.
 * @param matrice la matrice que l'on souhaite saisir dans le fichier de log
 * @param not_displayed_value la valeur que l'on ne souhaite pas afficher dans le fichier de log
 * @param log_file le fichier de log
 */
void mat_int_log(t_mat_int_dyn *matrice, int not_displayed_value, FILE *log_file);

#endif