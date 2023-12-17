/**
 * @file lecture_csv.h
 * @brief Fichier de déclaration pour la lecture d'un fichier CSV.
 * @author Marco
 * @date 2023-10-17
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
 * @fn t_mat_char_star_dyn *remplirMatrice(char *fichier)
 * @brief Fonction pour remplir la matrice avec les données du fichier CSV.
 * Procédé : 1) On vérifie que le fichier est bien un ".csv".
 *           2) On ouvre le fichier en lecture.
 *           3) On crée la matrice de chaînes de caractères.
 *           4) On lit le fichier caractère par caractère.
 *           5) Si on rencontre une virgule, on termine le mot correspondant à la cellule et on alloue de l'espace pour une colonne supplémentaire.
 *           6) Si on rencontre un saut de ligne, on termine le mot correspondant à la dernière cellule de la ligne, on rajoute le nombre de colonnes total à la structure, on alloue de l'espace pour une ligne supplémentaire et on réinitialise l'indice de colonne.
 *           7) Si on rencontre un caractère autre qu'une virgule ou un saut de ligne, on l'ajoute à la cellule.
 *           8) On retourne la matrice remplie après avoir libéré l'espace alloué en trop et fermé le fichier.
 * @param fichier Le nom du fichier CSV.
 * @return Pointeur vers la matrice remplie.
 */
t_mat_char_star_dyn *remplirMatrice(char *fichier);

#endif // LECTURE_CSV_H