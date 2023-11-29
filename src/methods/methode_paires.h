/** \\file */
/**
 * @file methode_paires.h
 * @author Anthony
 * @brief 
 * @date 2023-11-28
 */

#ifndef __METHODE_PAIRES_H__
#define __METHODE_PAIRES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils_sd.h"
#include "../utils/dataStructure/ballot.h"
#include "../utils/dataStructure/graphe.h"
#include "../utils/dataStructure/listegen.h"
#include "../utils/dataStructure/arc.h"
#include "../utils/dataStructure/duel.h"

void condorcet_paires(ballot *matrice_ballot);

#endif // __METHODE_PAIRE_H__