/**
 * @file listegen.h
 * @author Anthony
 * @brief Structure de donnée correspondant à une liste générique.
 * @version beta
 * @date 2021-11-26
 */

#ifndef __LISTE_GEN_H__
#define __LISTE_GEN_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef void(*SimpleFunctor)(void *);

typedef int (*ReduceFunctor)(void *, int);

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
 * @return List* : pointeur vers la liste modifiée.
 */
List* list_push_back(List* list, void *data);

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
 * @param l : pointeur vers la liste à libérer.
 * @param f : fonction permettant de libérer la mémoire allouée pour les données de la liste.
 **/
void list_delete(ptrList *l, SimpleFunctor f);

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

/**
 * @brief Fonction permettant d'accéder à l'élément à une position donnée.
 * @param l La liste dans laquelle on veut accéder à l'élément
 * @param p La position à laquelle on veut accéder à l'élément
 * @return void* Le pointeur vers les données de l'élément à la position p
 */
void *list_at(const List* l, int p);

/**
 * @brief Fonction permettant d'inserer un élément à une position donnée.
 * @param l La liste dans laquelle on veut insérer l'élément
 * @param p La position à laquelle on veut insérer l'élément
 * @param v Le pointeur vers les données de l'élément à insérer
 * @return List* La liste modifiée
 */
List* list_insert_at(List* l, int p, void *v);

/******************* UTILS *********************/

/**
 * @brief Fonction permettant de savoir si une liste contient un élément donné.
 * 
 * @param l Liste dans laquelle on veut chercher l'élément
 * @param f Fonction permettant de comparer l'élément avec un autre
 * @param userData L'élément à comparer, sous forme d'entier
 * @return true si la liste contient l'élément
 * @return false si la liste ne contient pas l'élément
 */
bool contient(List* l, ReduceFunctor f, int userData);

/**
 * @brief Fonction permettant d'appliquer une fonction sur tous les éléments d'une liste.
 * 
 * @param l Liste sur laquelle on veut appliquer la fonction
 * @param f Fonction à appliquer
 * @return List* La liste modifiée
 */
List* list_map(List* l, SimpleFunctor f);

/**
 * @brief Fonction permettant de trouver l'indice d'un élément dans une liste.
 * 
 * @param l Liste dans laquelle on veut chercher l'élément
 * @param f Fonction permettant de comparer l'élément avec un autre
 * @param userData L'élément à comparer, sous forme d'entier
 * @return int L'indice de l'élément dans la liste
 */
int trouver_indice(List* l, ReduceFunctor f, int userData);

#endif // __LISTE_GEN_H__