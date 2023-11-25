/**
 * @file listegen.c
 * @author Anthony
 * @brief Structure de donnée correspondant à une liste générique.
 * @version 1.0
 * @date 2021-11-25
 */

#ifndef __LISTE_GEN_H__
#define __LISTE_GEN_H__

/**
 * @brief Structure de donnée correspondant à une liste générique.
 * Définition opaque du type List.
 */
typedef struct s_List List;

/**
 * @brief Définition du type ptrList : pointeur vers une liste générique.
 */
typedef List* ptrList;

/**
 * @brief Constructeur de la structure de donnée List.
 * @return List* : pointeur vers la liste créée.
 */
List* list_create();

/**
 * @brief Ajoute un élément en fin de liste.
 * @param list : liste à laquelle on veut ajouter un élément.
 * @param data : pointeur vers les données à ajouter.
 * @param data_size : la taille de data
 * @return List* : pointeur vers la liste modifiée.
 */
List* list_push_back(List* list, void *data, size_t date_size);

/**
 * @brief Ajoute un élément en début de liste.
 * @param list : liste à laquelle on veut ajouter un élément.
 * @param data : pointeur vers les données à ajouter.
 * @param data_size : la taille de data
 * @return List* : pointeur vers la liste modifiée.
 */
List* list_push_front(List* list, void *data, size_t date_size);

/**
 * @brief Libaire la mémoire allouée pour la liste.
 * @param list : liste à laquelle on veut libérer la mémoire
 */
void list_delete(ptrList *l);

/**
 * @brief Accède à l'élément en tête de liste.
 * @param l : liste à laquelle on veut accéder à l'élément en tête.
 * @return void* : pointeur vers les données de l'élément en tête de liste.
 */
void *list_front(const List* l);

/**
 * @brief Accède à l'élément en fin de liste.
 * @param l : liste à laquelle on veut accéder à l'élément en fin.
 * @return void* : pointeur vers les données de l'élément en fin de liste.
 */
void *list_back(const List* l);

/**
 * @brief Fonction indiquant si la liste est vide ou non.
 * @param l : liste à laquelle on veut savoir si elle est vide ou non.
 * @return true : si la liste est vide.
 * @return false : si la liste n'est pas vide.
 */
bool list_is_empty(const List* l);

/**
 * @brief Fonction indiquant la taille de la liste.
 * @param l : liste à laquelle on veut connaître la taille.
 * @return int : taille de la liste.
 */
int list_size(const List* l);

#endif // __LISTE_GEN_H__