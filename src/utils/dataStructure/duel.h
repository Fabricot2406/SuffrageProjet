/**
 * @file duel.h
 * @author Anthony
 * @brief Structure de données représentant une matrice de duel.
 * @details La diagonale est remplie de 0, car un candidat ne peut pas se battre contre lui-même.
 * 
 * @example matrice de duel : 5 candidats
 * 
 *           [[0  5  6  7  6], 
 *            [1  0  4  6  6], 
 *            [2  3  0  5  5], 
 *            [2  3  3  0  3],
 *            [3  3  3  5  0]]
 * 
 * @date 2023-11-26
 */

#ifndef __DUEL_H__
#define __DUEL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "matrice_int_dyn.h"
#include "listegen.h"
#include "ballot.h"

/**
 * @brief Fonction permettant de créer la matrice de duel à partir d'un ballot.
 * @param b Le ballot qui contient les préférences des électeurs.
 * @return t_mat_int_dyn* La matrice de duel.
 * @pre Le ballot est initialisé.
 */
t_mat_int_dyn *mat_duel_create(ballot *b);

/**
 * @brief Fonction permettant de créer la matrice de duel à partir d'une matrice de chaines de caractères.
 * @details Cette fonction est utilisée dans le cadre de l'option -d du programme.
 * @param matrice_string La matrice de chaines de caractères.
 * @return t_mat_int_dyn* La matrice de duel.
 */
t_mat_int_dyn *mat_duel_create_from_str(t_mat_char_star_dyn *matrice_string);

/******************* UTILS *********************/

/**
 * @brief Fonction permettant de remplir un fichier de log avec la matrice de duel.
 * 
 * @param matrice_duel La matrice de duel.
 * @param log_file Le fichier de log.
 */
void mat_duel_log(t_mat_int_dyn *matrice_duel, FILE *log_file);

#endif // __DUEL_H__