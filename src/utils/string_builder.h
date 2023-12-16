/**
 * @file string_builder.h
 * @author anthony
 * @brief Implémentation d'un StringBuilder
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * @brief Structure représentant un StringBuilder
 */
typedef struct s_string_builder{
    char *data; // Données
    size_t length; // Longueur
    size_t capacity; // Capacité
} StringBuilder;

/**
 * @brief Initialise un StringBuilder
 * @param sb Le StringBuilder à initialiser
 * @param initialCapacity La capacité initiale du StringBuilder
 */
StringBuilder *init_string_builder(size_t initialCapacity);

/**
 * @brief Ajoute une chaîne de caractères à la fin du StringBuilder
 * @param sb Le StringBuilder
 * @param str La chaîne de caractères à ajouter
 */
void append_string(StringBuilder *sb, const char *str);

/**
 * @brief Ajoute un caractère à la fin du StringBuilder
 * @param sb Le StringBuilder
 * @param c Le caractère à ajouter
 */
void free_string_builder(StringBuilder *sb);
