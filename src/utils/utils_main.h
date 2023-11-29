/** \\file */
/**
 * @file utils_main.h
 * @authors Marco, Anthony et Fabio
 * @brief Fichier de fonctions utilitaires nécessaires au main.c
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

/**
 * Vérifie l'existence d'un fichier en utilisant un chemin complet.
 *
 * @param nomFichier Le nom du fichier que l'on souhaite vérifier.
 * @param repertoire Le répertoire dans lequel le fichier est censé se trouver.
 * @param extension L'extension du fichier à chercher
 * @return 1 si le fichier existe, 0 s'il n'existe pas ou en cas d'erreur d'ouverture.
 */
int fichierExiste(const char *nomFichier, const char *repertoire, const char *extension, char *cheminComplet);

/**
 * Vérifie si la chaîne de caractères 'cle' est constituée uniquement de caractères alphanumériques.
 * Si la chaîne contient d'autres caractères, affiche un message d'erreur et renvoie 1.
 *
 * @param cle La chaîne de caractères à vérifier.
 * @return 0 si 'cle' est valide, 1 en cas d'erreur.
 */
int controlCle(char *cle);


/**
 * Vérifie la validité d'une chaîne de caractères représentant un nom ou un prénom.
 * La fonction contrôle que la chaîne passée en paramètre est valide
 *
 * @param chaine La chaîne de caractères à vérifier.
 * @param prenom 1 si la chaine saisie est un prénom. 0 si c'est un nom de famille
 * @return 0 si 'chaine' est valide, 1 en cas d'erreur.
 */
int controlNomPrenom(char *chaine, int prenom);


/**
 * @brief Fonction permettant de construire et d'afficher les structures de données à partir des fichiers csv.
 * Les TAD affichés sont les suivants : ballot, matrice de duel, liste des arcs.
 * Le vainqueur de Condorcet est également affiché si il existe.
 * @param fichier Le nom du fichier contenant les candidats.
 */
void construire_afficher_TAD(char *fichier);

#endif