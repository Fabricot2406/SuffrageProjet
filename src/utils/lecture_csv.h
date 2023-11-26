/**
 * @file lecture_csv.h
 * @author Marco
 * @brief Fichier de déclaration pour la lecture d'un fichier CSV.
 * @version 1.0
 */

#ifndef LECTURE_CSV_H
#define LECTURE_CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "./dataStructure/matrice_string_dyn.h"

#define TAILLE_MAX 65

/**
 * @fn int estMauvaiseExtension(char *fichier)
 * @brief Fonction qui confirme si le fichier est un ".csv".
 * @param fichier Le nom du fichier à vérifier.
 * @return 1 si le fichier n'est pas un ".csv", 0 sinon.
 */
int estMauvaiseExtension(char *fichier);

/**
 * @fn t_mat_char_star_dyn *remplirMatrice(char *fichier)
 * @brief Fonction pour remplir la matrice avec les données du fichier CSV.
 * @param fichier Le nom du fichier CSV.
 * @return Pointeur vers la matrice remplie.
 */
t_mat_char_star_dyn *remplirMatrice(char *fichier);

#endif // LECTURE_CSV_H
