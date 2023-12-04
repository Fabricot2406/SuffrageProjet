/** \\file */
/**
 * @file methode_schulze.h
 * @author Fabio
 * @brief Fichier pour le calcul du vainqueur avec Schulze
 * @date 2023-11-29
 */

#ifndef __METHODE_SCHULZE_H__
#define __METHODE_SCHULZE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils_sd.h"
#include "../utils/dataStructure/arc.h"
#include "../utils/dataStructure/listegen.h"

void condorcet_schulze(t_mat_int_dyn *matrice_duel, char **candidats_nom);

#endif