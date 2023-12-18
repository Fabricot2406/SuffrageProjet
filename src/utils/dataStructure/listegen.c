/**
 * @file listegen.c
 * @author Anthony
 * @brief Structure de donnée correspondant à une liste générique.
 * @date 2023-11-28
 */
#include "listegen.h"

List* list_create() {
	List* l = malloc(sizeof(struct s_List));
    if (l == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire\n");
        exit(EXIT_FAILURE);
    }
	l->sentinel = malloc(sizeof(LinkedElement));
    if (l->sentinel == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire\n");
        exit(EXIT_FAILURE);
    }
	l->sentinel->previous=l->sentinel->next=l->sentinel;
	l->size = 0;
	return l;
}

List* list_push_back(List* list, void *data) {
	LinkedElement* element = malloc(sizeof(LinkedElement));
    if (element == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire\n");
        exit(EXIT_FAILURE);
    }
	LinkedElement* sentinel = list->sentinel;
	element->value = data;
	element->next = sentinel;
	element->previous = sentinel->previous;
	element->previous->next = element;
	element->next->previous = element;
	(list->size)++;
	return list;
}

List* list_push_front(List* list, void *data, size_t date_size) {
	LinkedElement *element = malloc(sizeof(LinkedElement));
    if (element == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire\n");
        exit(EXIT_FAILURE);
    }
	LinkedElement *sentinel = list->sentinel;
    element->value = data;
	element->previous = sentinel;
	element->next = sentinel->next;
	sentinel->next->previous = element;
	sentinel->next=element;
	(list->size)++;
	(void)date_size;
	return list;
}

void vide(void *elem){
    (void)elem;
}

void list_delete(List *l, SimpleFunctor f) {
	assert(f!=NULL);
	List *list = l;
	struct s_LinkedElement *current = list->sentinel->next;
	struct s_LinkedElement *next;
	while (current != list->sentinel) {
        next = current->next;
		f(current->value);
        free(current);
        current = next;
    }
	free(list->sentinel);
    free(list);
}

void list_pop_back(List* list, SimpleFunctor f) {
	assert(!list_is_empty(list));
	LinkedElement *sentinel = list->sentinel;
	LinkedElement *element = sentinel->previous;
	element->previous->next = sentinel;
	sentinel->previous = element->previous;
	f(element->value);
	free(element);
	(list->size)--;
}

void *list_front(const List* l) {
	assert(!list_is_empty(l));
	return l->sentinel->next->value;
}

void *list_back(const List* l) {
	assert(!list_is_empty(l));
	return l->sentinel->previous->value;
}

bool list_is_empty(const List* l) {
	return l->size==0;
}

int list_size(const List* l) {
	return l->size;
}
List* list_remove_at(List* l, int p,SimpleFunctor f) {
	assert((p>=0) && (p<l->size));
	LinkedElement *curseur = l->sentinel->next;
	for (int i = 0; i < p; i++)
	{
		curseur = curseur->next;
	}

	LinkedElement *curseurBefore = curseur->previous;
	curseurBefore->next = curseur->next;
	curseur->next->previous = curseurBefore;
	f(curseur->value);
	free(curseur);
	(l->size)--;
	return l;
}

void *list_at(const List* l, int p) {
	assert((p>=0) && (p<l->size));
	LinkedElement *element = l->sentinel->next;
	for (int i = 0; i < p; i++) element = element->next;
	return element->value;
}

List* list_map(List* l, SimpleFunctor f) {
	LinkedElement * sentinel = l->sentinel;
	for (LinkedElement * element = sentinel->next; element!=sentinel; element=element->next)
		f(element->value);
	return l;
}

List* list_reduce(List* list, void (*f)(void *, void*), void *userData) {
	LinkedElement * sentinel = list->sentinel;
	// on parcourt la liste
	for (LinkedElement * element = sentinel->next; element!=sentinel; element=element->next)
		// on applique la fonction de traitement à la donnée
		f(element->value, userData);
	return list;
}

List* list_insert_at(List* l, int p, void *v) {
	assert((p <= l->size) && (p >= 0));
	LinkedElement *element = malloc(sizeof(LinkedElement));
	element->value = v;
	LinkedElement *curseur = l->sentinel->next;
	while (p--) curseur = curseur->next;
	LinkedElement *curseurBefore = curseur->previous;
	element->next = curseur;
	element->previous = curseurBefore;
	curseurBefore->next = element;
	curseur->previous = element;
	(l->size)++;
	return l;
}

void insert_sorted(List *list, void *newElement, int (*compare)(const void *, const void *)) {
    int indice_insert = 0;
    Iterator *it = iterator_create(list);
    
    while (iterator_has_next(it)) {
        void *current = iterator_current(it);
        if (compare(current, newElement) > 0) break;
        iterator_next(it);
        indice_insert = iterator_index(it);
    }
    list_insert_at(list, indice_insert, newElement);
    iterator_delete(it);
}

/******************* FONCTION DE TRI *********************/

/**
 * @brief Structure de sous-liste
 */
typedef struct subList{
	LinkedElement *head;
	LinkedElement *queue;
}subList;

/**
 * @brief Fonction de séparation d'une liste en deux sous-listes
 * @param l liste à séparer
 * @return subList la sous-liste
 */
subList list_split(subList l){
	LinkedElement *leftPtr = l.head;
	LinkedElement *rightPtr = l.queue;
	// tant que les deux pointeurs ne se sont pas croisés
	while (leftPtr != rightPtr)
	{	
		// on s'arrête si les deux pointeurs sont voisins
		if (leftPtr->next == rightPtr) break;
		// on s'arrêtre si les deux pointeurs se croiseront au prochain tour
		if (leftPtr->next == rightPtr->previous) {
			leftPtr = leftPtr->next;
			break;
		}
		// on avance le pointeur de gauche
		// on recule le pointeur de droite
		leftPtr = leftPtr->next;
		rightPtr= rightPtr->previous;
	}
	l.head = leftPtr;
	l.queue = rightPtr;
	return l;
}

/**
 * @brief Fonction de transformation d'une liste en sous-liste
 * @param l liste à transformer
 * @return subList la sous-liste
 */
subList subListTransform(List *l){
	subList sList;
	sList.head = l->sentinel->next;
	sList.queue = l->sentinel->previous;
	//on libère la liste et la sentinel
	free(l->sentinel);
	free(l);
	return sList;
}

/**
 * @brief Fonction de fusion de deux sous-listes triées
 * @param leftlist liste gauche
 * @param rightlist liste droite
 * @param f fonction de comparaison
 * @return subList la liste fusionnée
 */
subList list_merge(subList leftlist, subList rightlist,OrderFunctor f){
	List *listTotal = list_create();
	LinkedElement *Lptr = leftlist.head;
	LinkedElement *endLptr = leftlist.queue;
	LinkedElement *Rptr = rightlist.head;
	LinkedElement *endRptr = rightlist.queue;
	while (1){
		if (f(Lptr->value,Rptr->value)){
			// on ajoute l'élément de la liste gauche
			list_push_back(listTotal,Lptr->value);
			// on est à la fin de la liste gauche
			if (Lptr == endLptr) {
				free(Lptr);
				// on ajoute le reste de la liste droite
				while (Rptr != endRptr)
				{
					list_push_back(listTotal,Rptr->value);
					Rptr = Rptr->next;
					free(Rptr->previous);
				}
				// on ajoute le dernier élément de la liste droite
				list_push_back(listTotal,Rptr->value);
				free(Rptr);
				break;
			}
			// on passe à l'élément suivant de la liste gauche
			Lptr = Lptr->next;
			free(Lptr->previous);
		}else if (f(Rptr->value,Lptr->value)){
			// on ajoute l'élément de la liste droite
			list_push_back(listTotal,Rptr->value);
			// Cas où on est à la fin de la liste droite
			if (Rptr == endRptr) {
				free(Rptr);
				// on ajoute le reste de la liste gauche
				while (Lptr != endLptr)
				{
					list_push_back(listTotal,Lptr->value);
					Lptr = Lptr->next;
					free(Lptr->previous);
				}
				// on ajoute le dernier élément de la liste gauche
				list_push_back(listTotal,Lptr->value);
				free(Lptr);
				break;
			}
			// on passe à l'élément suivant de la liste droite
			Rptr = Rptr->next;
			free(Rptr->previous);
		}
	}
	return subListTransform(listTotal);
}


/**
	Fonction de tri par fusion
	@param list : sous-liste à trier
	@param f : fonction de comparaison
	@return : sous-liste triée
*/
subList list_mergesort(subList list, OrderFunctor f){
	subList result;
	// cas de base : liste vide ou de taille 1
	if (list.head == list.queue) result = list;
	// cas récursif
	else {
		subList leftList,rightList;
		LinkedElement *deb = list.head;
		LinkedElement *fin = list.queue;
		// cas d'une liste de taille 2
		if (deb->next == fin) {
			// initialisation des listes gauche et droite
			leftList.head = deb;
			leftList.queue = deb;
			rightList.head = fin;
			rightList.queue = fin;
		// cas d'une liste de taille 3 ou plus
		}else{
			subList splitList = list_split(list);
			// leftList  = [deb,milieu]
			leftList.head = deb;
			leftList.queue = splitList.head;
			// rightList = [milieu+1,fin]
			rightList.head = splitList.queue;
			rightList.queue = fin;
		}
		// tri des listes droites et gauches
		leftList = list_mergesort(leftList,f);
		rightList = list_mergesort(rightList,f);
		// fusion des listes droites et gauches
		result = list_merge(leftList,rightList,f);
	}
	return result;
}

List *list_sort(List *l, OrderFunctor f){
	assert(!list_is_empty(l) && f != NULL);

	// sauvegarde de la taille initiale de la liste
	int oldsize = l->size;

	// si la liste est vide ou ne contient qu'un seul élément, elle est déjà triée
	if (l->size == 0 || l->size == 1) return l;

	// transformation de la liste en sous-liste pour faciliter le tri
	subList list = subListTransform(l);
	list = list_mergesort(list,f);

	// création d'une nouvelle liste triée
	List *listResult = list_create();

	// remise en place de la taille initiale de la liste triée
	listResult->size = oldsize;

	// remise en place de la sentinel de la liste triée
	LinkedElement *sentinel = listResult->sentinel;
	sentinel->next = list.head;
	list.head->previous = sentinel;
	sentinel->previous = list.queue;
	list.queue->next = sentinel;

	return listResult;
}

/******************* ITERATOR *********************/

typedef struct s_Iterator {
	int index;
	LinkedElement *current;
	LinkedElement *sentinel;
}Iterator;

Iterator* iterator_create(const List* l) {
	Iterator *it = malloc(sizeof(Iterator));
	if (it == NULL) {
		fprintf(stderr, "Erreur lors de l'allocation de la mémoire\n");
		exit(EXIT_FAILURE);
	}
	it->index = 0;
	it->current = l->sentinel->next;
	it->sentinel = l->sentinel;
	return it;
}

void iterator_delete(Iterator* it) {
	free(it);
}

bool iterator_has_next(const Iterator* it) {
	return it->current != it->sentinel;
}

void *iterator_current(const Iterator* it) {
	return it->current->value;
}

int iterator_index(const Iterator *it){
	return it->index;
}

void iterator_next(Iterator* it) {
	it->current = it->current->next;
	it->index = it->index+1;
}

void iterator_prev(Iterator* it) {
	it->current = it->current->previous;
	it->index = it->index-1;
}

void set_position(Iterator* it, int p) {
	assert((p >= 0));
	it->current = it->sentinel->next;
	it->index = p;
	while (p--) it->current = it->current->next;
}