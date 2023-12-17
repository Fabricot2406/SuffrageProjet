/**
 * @file utils_main.h
 * @brief Fichier de fonctions utilitaires nécessaires au main.
 * @authors Marco, Anthony et Fabio
 * @date 2023-12-17
 */

#ifndef UTILS_MAIN_H
#define UTILS_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>
#include "lecture_csv.h"
#include "utils_sd.h"
#include "./dataStructure/ballot.h"
#include "./dataStructure/duel.h"
#include "./dataStructure/matrice_int_dyn.h"
#include "./dataStructure/matrice_string_dyn.h"
#include "./dataStructure/listegen.h"
#include "./dataStructure/arc.h"

#define BUFFER_SIZE 1024

/******************* STRUCTURE *********************/

/**
 * @brief Structure représentant les données d'une élection.
 *        Contient les TAD nécessaires à l'application de l'ensemble des méthodes de scrutin.
 */
typedef struct s_data {
    char **candidats_nom;
    t_mat_char_star_dyn *matrice_csv;
    t_mat_int_dyn *matrice_duel;
    ballot *matrice_ballot;
} Data;

/**
 * @brief Fonction permettant de créer un chemin complet à partir d'un nom de fichier, d'un répertoire et d'une extension.
 * 
 * @param chemin_complet Buffer dans lequel on stocke le chemin complet.
 * @param nomFichier Nom du fichier.
 * @param repertoire Répertoire dans lequel se trouve le fichier.
 * @param extension Extension du fichier.
 */
void creer_chemin_complet(char *chemin_complet, const char *nomFichier, const char *repertoire, const char *extension);

/**
 * Vérifie l'existence d'un fichier en utilisant un chemin complet.
 *
 * @param nomFichier Le nom du fichier que l'on souhaite vérifier.
 * @param repertoire Le répertoire dans lequel le fichier est censé se trouver.
 * @param extension L'extension du fichier à chercher
 * @return 1 si le fichier existe, 0 s'il n'existe pas ou en cas d'erreur d'ouverture.
 */
int fichier_existe(const char *nomFichier, const char *repertoire, const char *extension, char *cheminComplet);

/**
 * Vérifie si la chaîne de caractères 'cle' est constituée uniquement de caractères alphanumériques.
 * Si la chaîne contient d'autres caractères, affiche un message d'erreur et renvoie 1.
 *
 * @param cle La chaîne de caractères à vérifier.
 * @return 0 si 'cle' est valide, 1 en cas d'erreur.
 */
int control_cle(char *cle);


/**
 * Vérifie la validité d'une chaîne de caractères représentant un nom ou un prénom.
 * La fonction contrôle que la chaîne passée en paramètre est valide
 *
 * @param chaine La chaîne de caractères à vérifier.
 * @param prenom 1 si la chaine saisie est un prénom. 0 si c'est un nom de famille
 * @return 0 si 'chaine' est valide, 1 en cas d'erreur.
 */
int control_nom_prenom(char *chaine, int prenom);


/**
 * @brief Fonction permettant de remplir un fichier log avec les données d'une élection.
 * @param log_file Le fichier log à remplir.
 * @param data Les données de l'élection.
 */
void remplir_log(FILE *log_file, Data data);

#endif