#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
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

List* list_push_back(List* list, void *data, size_t date_size) {
	LinkedElement* element = malloc(sizeof(LinkedElement));
    if (element == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire\n");
        exit(EXIT_FAILURE);
    }
	LinkedElement* sentinel = list->sentinel;
	element->value = malloc(date_size);
    if (element->value == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire\n");
        exit(EXIT_FAILURE);
    }
    memcpy(element->value, data, date_size);
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
	element->value = malloc(date_size);
    if (element->value == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire\n");
        exit(EXIT_FAILURE);
    }
    memcpy(element->value, data, date_size);
	element->previous = sentinel;
	element->next = sentinel->next;
	sentinel->next->previous = element;
	sentinel->next=element;
	(list->size)++;
	return list;
}

void list_delete(ptrList *l) {
	struct s_List *list = *l;
	struct s_LinkedElement *sentinel = list->sentinel; 
	free(sentinel);
    if (list->size == 0) {
        free(list);
        return;
    }
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