/** \\file */
/**
 * @file uninominale.h
 * @author Fabio
 * @brief Méthode uninominale à 1 et 2 tours
 * @date 2023-11-25
 */

#ifndef UNINOMINALE_H
#define UNINOMINALE_CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils_sd.h"
#include "../utils/dataStructure/ballot.h"

/**
 * @brief Initialise un tableau contenant le score de chaque candidat
 * @param matrice Une matrice de type ballot
 */
void initialiserTableauVotes(ballot * matrice);

/**
 * @brief Calcule le résultat de la méthode uninominale à un tour
 * @param matrice Une matrice de type ballot
 */
void calculerUninominaleUnTour(ballot * matrice); // Calcule le vainqueur de la méthode uninominale à un tour.

/**
 * @brief Calcule le résultat de la méthode uninominale à deux tours
 * @param matrice Une matrice de type ballot
 */
void calculerUninominaleDeuxTours(ballot * matrice);// Calcule le vainqueur de la méthode uninominale à deux tours.

#endif