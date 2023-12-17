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

 /**
 * @brief Fonction permettant de déterminer si un candidat est vainqueur de condorcet.
 * Processus : 1) On initialise une liste d'arcs à partir de la matrice de duels.
 *             2) On trie la liste d'arcs dans l'ordre croissant.
 *             3) On réduit la liste d'arcs jusqu'à obtenir un vainqueur.
 * 
 * @param matrice_duel Matrice de duel avec les résultats du vote.
 * @param candidats_nom Liste des noms des candidats.
 * @param output Le fichier de sortie dans lequel on écrit le résultat.
 */
 void condorcet_schulze(t_mat_int_dyn *matrice_duel, char **candidats_nom, FILE *output);

#endif