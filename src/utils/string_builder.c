/**
 * @file string_builder.c
 * @author Anthony
 * @brief Implémentation d'un string builder.
 */
#include "string_builder.h"

StringBuilder *init_string_builder(size_t initialCapacity) {
    StringBuilder *sb = (StringBuilder *)malloc(sizeof(StringBuilder));
    sb->data = (char *)malloc(initialCapacity * sizeof(char));
    if (sb->data == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }
    sb->data[0] = '\0';
    sb->length = 0;
    sb->capacity = initialCapacity;
    return sb;
}

void append_string(StringBuilder *sb, const char *str) {
    size_t strLength = strlen(str);
    size_t newLength = sb->length + strLength + 1; // +1 pour le caractère nul
    printf("newLength = %zu\n", newLength);
    assert(newLength < sb->capacity); // Vérifier qu'il n'y a pas eu de débordement
    // Ajouter la nouvelle chaîne à la fin du tableau
    strcat(sb->data, str);
    sb->length = newLength - 1; // Exclure le caractère nul ajouté par strcat
}

void free_string_builder(StringBuilder *sb) {
    free(sb->data);
    sb->data = NULL;
    sb->length = 0;
    sb->capacity = 0;
    free(sb);
}
