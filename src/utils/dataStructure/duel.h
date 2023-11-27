/**
 * @file duel.h
 * @author Anthony
 * @brief Création de la matrice de duel, qui contient les duels entre les candidats. 
 * La diagonale est remplie de 0, car un candidat ne peut pas se battre contre lui-même.
 * @version beta
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
 * @brief Fonction permettant de créer la matrice de duel.
 * @param b Le ballot qui contient les préférences des électeurs.
 * @return t_mat_int_dyn* La matrice de duel.
 */
t_mat_int_dyn *creer_matrice_duel(ballot *b);

/******************* UTILS *********************/

/**
 * @brief Affiche la matrice de duel.
 * @param matrice_duel La matrice de duel à afficher.
 */
void afficher_matrice_duels(t_mat_int_dyn *matrice_duel);

#endif // __DUEL_H__