#include "listegen.h"

typedef struct s_LinkedElement {
	void *value;
	struct s_LinkedElement* previous;
	struct s_LinkedElement* next;
} LinkedElement;

struct s_List {
	LinkedElement* sentinel;
	int size;
};

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
	return list;
}

void list_delete(ptrList *l, SimpleFunctor f) {
	List *list = (List *)l;
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

void *list_at(const List* l, int p) {
	assert((p>=0) && (p<l->size));
	LinkedElement *element = l->sentinel->next;
	for (int i = 0; i < p; i++)
	{
		element = element->next;
	}
	return element->value;
}

List* list_map(List* l, SimpleFunctor f) {
	LinkedElement * sentinel = l->sentinel;
	for (LinkedElement * element = sentinel->next; element!=sentinel; element=element->next)
	{
		f(element->value);
	}
	return l;
}

List* list_reduce(List* l, Functor f, void *userData) {
	LinkedElement * sentinel = l->sentinel;
	for (LinkedElement * element = sentinel->next; element!=sentinel; element=element->next)
	{
		if (f(element->value, userData)) break;
	}
	return l;
}


// Factoriser les deux fonctions suivantes

bool contient(List* l, ReduceFunctor f, int userData) {
	int elem;
	int i = 0;
	LinkedElement *sentinel = l->sentinel;
	LinkedElement *element = sentinel->next;
	while (element!=sentinel)
	{
		if(f(element->value, userData)) return true;
		element=element->next;
		i++;
	}
	return false;
}

int trouver_indice(List* l, ReduceFunctor f, int userData) {
	int elem;
	int i = 0;
	LinkedElement *sentinel = l->sentinel;
	LinkedElement *element = sentinel->next;
	while (element!=sentinel)
	{
		if(f(element->value, userData)) return i;
		element=element->next;
		i++;
	}
	return i;
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