/**
 * @file listegen.h
 * @author Anthony
 * @brief Structure de donnée correspondant à une liste générique.
 * @date 2021-11-26
 */

#ifndef __LISTE_GEN_H__
#define __LISTE_GEN_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/******************* TYPEDEF FONCTION *********************/

typedef void(*SimpleFunctor)(void *);

typedef int (*ReduceFunctor)(void *, int);

typedef int (*Functor)(void *, void *);

typedef bool(*OrderFunctor)(void *, void *);

/******************* STRUCTURE *********************/

/**
 * @brief Structure de données représentant un élément de la liste.
 */
typedef struct s_LinkedElement {
	void *value;
	struct s_LinkedElement* previous;
	struct s_LinkedElement* next;
} LinkedElement;


typedef struct s_List {
	LinkedElement* sentinel;
	int size;
}List;

/******************* CONSTRUCTEURS *********************/

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
 * @brief Fonction permettant d'inserer un élément à une position donnée.
 * @param l La liste dans laquelle on veut insérer l'élément
 * @param p La position à laquelle on veut insérer l'élément
 * @param v Le pointeur vers les données de l'élément à insérer
 * @return List* La liste modifiée
 */
List* list_insert_at(List* l, int p, void *v);

/**
 * @brief Insère un nouvel élément dans une liste triée.
 * @param list La liste dans laquelle insérer l'élément.
 * @param newElement Un pointeur vers la nouvelle valeur à insérer.
 * @param list_comp La fonction de comparaison pour déterminer l'ordre des éléments.
 * Cette fonction doit retourner un entier négatif si le premier élément est inférieur au deuxième, 
 * 0 s'ils sont égaux, 
 * et un entier positif si le premier élément est supérieur au deuxième.
 */
void insert_sorted(List *list, void *newElement, int (*list_comp)(const void *, const void *));

/******************* OPERATEURS *********************/

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
 * @brief Fonction permettant d'accéder à l'élément à une position donnée.
 * @param l La liste dans laquelle on veut accéder à l'élément
 * @param p La position à laquelle on veut accéder à l'élément
 * @return void* Le pointeur vers les données de l'élément à la position p
 */
void *list_at(const List* l, int p);

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
 * @brief Utiliser cette fonction dans le paramètre f de list_delete 
 *        afin de ne pas libérer la mémoire des éléments de la liste.
 */
void vide(void *elem);

/**
 * @brief Libère la mémoire allouée pour la liste.
 * @param l : pointeur vers la liste à libérer.
 * @param f : fonction permettant de libérer la mémoire allouée pour les données de la liste.
 * 			  Si vide est utilisé, la fonction ne libère pas la mémoire allouée pour les données.
 **/
void list_delete(List *l, SimpleFunctor f);

/**
 * @brief Supprime l'élément à la position spécifiée dans la liste.
 * @param l : La liste dont on veut supprimer un élément.
 * @param p : La position de l'élément à supprimer.
 * @param f : Une fonction pour libérer la mémoire allouée pour la valeur de l'élément.
 * @return List* : La liste modifiée sans l'élément supprimé.
 */
List* list_remove_at(List* l, int p,SimpleFunctor f);

/**
 * @brief Supprime le dernier élément de la liste et libère la mémoire associée.
 * @param list La liste à modifier.
 * @param f Foncteur simple pour libérer la mémoire du contenu de l'élément.
 * Si NULL, la fonction se contente de libérer l'élément sans libérer son contenu.
 * @pre La liste ne doit pas être vide.
 */
void list_pop_back(List* list, SimpleFunctor f);

/******************* UTILS *********************/

/**
 * @brief Fonction permettant d'appliquer une fonction sur tous les éléments d'une liste.
 * 
 * @param l Liste sur laquelle on veut appliquer la fonction
 * @param f Fonction à appliquer
 * @return List* La liste modifiée
 */
List* list_map(List* l, SimpleFunctor f);

/**
 * @brief Fonction de réduction.
 * @details Cette fonction permet d'appliquer un traitement à une donnée passée en paramètre pour chaque élément de la liste.
 * 
 * @param list La liste à parcourir
 * @param f La fonction de traitement
 * @param userData La donnée à traiter
 * @return List* La liste passé en paramètre
 * @pre La fonction f est de type void (*f)(int, void*)
 * @post La liste est inchangée
 */
List* list_reduce(List* list, void (*f)(void *, void*), void *userData);

/**
 * @brief Trie les éléments de la liste dans l'ordre croissant.
 * @param l : La liste à trier.
 * @param comp : Une fonction de comparaison qui renvoie vrai si le premier argument doit venir avant le second dans la liste triée.
 * @return List* : La liste triée selon la fonction de comparaison f.
 */
List* list_sort(List* l, OrderFunctor f);

/******************* ITERATOR *********************/

/**
 * @brief Structure de l'iterateur utilisée pour la liste générique
 * Définition opaque de la structure
*/
typedef struct s_Iterator Iterator;

/**
 * @brief Fonction permettant de construire un iterateur
 * 
 * @param l Liste que l'on souhaite parcourir
 * @return Iterator* pointeur vers l'iterateur créé
 */
Iterator* iterator_create(const List* l);

/**
 * @brief Fonction permettant de supprimer un iterateur
 * @param it Iterateur que l'on souhaite supprimer
*/
void iterator_delete(Iterator* it);

/**
 * @brief Fonction indiquant la fin du liste à la prochaine itération
 * @param it L'itérateur utilisé
 * @return true si il y a encore des éléments à parcourir et false sinon
*/
bool iterator_has_next(const Iterator* it);

/**
 * @brief Fonction renvoyant la valeur courrante pointée par l'itérateur
 * @param it L'itérateur utilisé
 * @return La valeur courrante
*/
void *iterator_current(const Iterator* it);

/**
 * @brief Fonction permettant de passer à l'élément suivant
 * @param it L'itérateur utilisé
*/
void iterator_next(Iterator* it);

/**
 * @brief Fonction permettant de passer à l'élément précédent
 * @param it L'itérateur utilisé
*/
void iterator_prev(Iterator* it);

/**
 * @brief Fonction permettant de mettre l'itérateur à position donnée
 * @param it L'itérateur utilisé
 * @param p La position souhaitée
*/
void set_position(Iterator* it, int p);

/**
 * @brief Fonction permettant de récupérer la position courrante de l'itérateur
 * @param it L'itérateur utilisé
 * @return La position courrante
*/
int iterator_index(const Iterator *it);
 
#endif // __LISTE_GEN_H__