/**
 * @file duel.h
 * @author Anthony
 * @brief Création de la matrice de duel, qui contient les duels entre les candidats. 
 * La diagonale est remplie de 0, car un candidat ne peut pas se battre contre lui-même.
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
 */
t_mat_int_dyn *creer_matrice_duel(ballot *b);

/**
 * @brief Fonction permettant de créer la matrice de duel à partir d'une matrice de chaines de caractères.
 * @details Cette fonction est utilisée dans le cadre de l'option -d du programme.
 * @param matrice_string La matrice de chaines de caractères.
 * @return t_mat_int_dyn* La matrice de duel.
 */
t_mat_int_dyn *creer_matrice_duel_f_char(t_mat_char_star_dyn *matrice_string);

/******************* UTILS *********************/

/**
 * @brief Fonction permettant de remplir un fichier de log avec la matrice de duel.
 * 
 * @param matrice_duel La matrice de duel.
 * @param log_file Le fichier de log.
 */
void log_duel(t_mat_int_dyn *matrice_duel, FILE *log_file);

#endif // __DUEL_H__