/**
 * @file jugement_majoritaire.h
 * @author Marco Regragui Martins
 * @brief Fichier de la méthode de scrutin du jugement majoritaire
 * @version 1.0
 * @date Date de création
 */

#ifndef __METHODE_PAIRE_H__
#define __METHODE_PAIRE_H__

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