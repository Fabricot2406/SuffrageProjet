/** \\file */
/**
 * @file verify_my_vote.h
 * @author Marco
 * @brief Fichier de déclaration pour la vérification du vote de l'utilisateur.
 * @date 2023-11-26
 */
#ifndef VERIFY_MY_VOTE_H
#define VERIFY_MY_VOTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"
#include "sha256_utils.h"
#include "../utils/lecture_csv.h"

#define TAILLE_NOM_MAX 50 ///< Taille maximale du nom.
#define TAILLE_CLE_MAX 17 ///< Taille maximale de la clé.
#define TAILLE_NOM_FICHIER_MAX 100 ///< Taille maximale du nom de fichier.

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
