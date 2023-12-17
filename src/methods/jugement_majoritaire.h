/**
 * @file jugement_majoritaire.h
 * @author Marco
 * @brief Fichier de la méthode de scrutin du jugement majoritaire
 * @date 2023-11-28
 */

#ifndef __JUGEMENT_MAJORITAIRE_H__
#define __JUGEMENT_MAJORITAIRE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/lecture_csv.h"
#include "../utils/dataStructure/listegen.h"
#include "../utils/utils_sd.h"

/******************* STRUCTURE *********************/

/**
 * @brief Structure représentant un candidat dans le scrutin du jugement majoritaire.
 */
typedef struct s_candidat Candidat;

/**
 * @brief Détermine le vainqueur du jugement en fonction des mentions de chaque candidat et affiche le nom du vainqueur.
 * Procédé : 1) On initialise chaque candidat avec son nom, les votes des électeurs à son égard triés par ordre croissant et la mention majoritaire correspondante.
 *           2) On initialise un tableau répertoriant tous les candidats du scrutin.
 *           3) On calcule le vainqueur du jugement en fonction des mentions de chaque candidat.
 *           4) Si il y a égalité, on supprime le vote correspondant à la mention majoritaire et on réitère l'étape 3.
 *           5) On affiche le nom du vainqueur.
 * @param matrice Matrice de mentions.
 * @param output Fichier de sortie.
 */
void determiner_vainqueur_jugement(t_mat_char_star_dyn *matrice,FILE *output);


#endif //__JUGEMENT_MAJORITAIRE_H__