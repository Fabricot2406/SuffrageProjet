/**
 * @file verify_my_vote.h
 * @brief Fichier d'en-tête pour la vérification des votes.
 */

#ifndef VERIFY_MY_VOTE_H
#define VERIFY_MY_VOTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"
#include "sha256_utils.h"
#include "lecture_csv.h"

#define TAILLE_NOM_MAX 50 ///< Taille maximale du nom.
#define TAILLE_CLE_MAX 17 ///< Taille maximale de la clé.
#define TAILLE_NOM_FICHIER_MAX 100 ///< Taille maximale du nom de fichier.

/**
 * @brief Convertit une clé hexadécimale en octets.
 * 
 * @param cle La clé hexadécimale à convertir.
 * @return Un pointeur vers le tableau d'octets résultant.
 */
unsigned char *hexaToByte(char *cle);

/**
 * @brief Hash deux chaînes de caractères ensemble.
 * 
 * @param nom Le nom à hacher.
 * @param cle La clé à hacher avec le nom.
 * @return Un pointeur vers la chaîne de caractères résultante.
 */
char *hasherChaines (char *nom, char *cle);

/**
 * @brief Recherche un hash dans un fichier CSV.
 * 
 * @param hash Le hash à rechercher.
 * @param fichier Le nom du fichier CSV dans lequel rechercher.
 */
void trouverHashDansCsv(char *hash, char *fichier);

#endif // VERIFY_MY_VOTE_H
