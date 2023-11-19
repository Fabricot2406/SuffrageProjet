#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "candidat.h"

struct candidat {
    char *nom;
    int nb_duel;
    liste_duel *liste_duel;
};

typedef struct duel{
    int occurence;
    candidat *candidat;
};

/**
 * @brief A struct representing a node in a doubly linked list of duels between candidates.
 * 
 * This struct contains pointers to the previous and next nodes in the list, as well as a pointer to the
 * corresponding duel struct.
 */
typedef struct double_linked{
    liste_duel *prev;
    liste_duel *next;
    struct duel *adverse;
}liste_duel;

candidat *creer_candidat(char *nom){
    candidat *sujet = malloc(sizeof(struct candidat));
    sujet->nom = nom;
    sujet->nb_duel = 0;
    sujet->liste_duel = malloc(sizeof(liste_duel));
    liste_duel *sentinel = sujet->liste_duel;
    sentinel->adverse = NULL;
    sentinel->next=sentinel->prev = sentinel;
    return sujet;
}

duel *creer_duel(candidat *opposant){
    // Création du nouveau duel
    duel *new_duel = malloc(sizeof(struct duel));
    new_duel->candidat = opposant;
    new_duel->occurence = 0;
    return new_duel;
}

candidat *ajouter_association_duel(candidat *sujet,candidat *opposant){
    duel *new_duel = creer_duel(opposant);

    // Création du nouveau duel chaîné
    liste_duel *new_liste_duel = malloc(sizeof(liste_duel));
    new_liste_duel->adverse = new_duel;

    // Accès à la sentinel
    liste_duel *sentinel = sujet->liste_duel;
    // Accès au dernier duel chaîné ajouté pour le candidat sujet
    liste_duel *dernier_duel = sentinel->prev;

    // Ajout du nouveau duel chaîné
    dernier_duel->next = new_liste_duel;
    new_liste_duel->prev = dernier_duel;
    new_liste_duel->next = sentinel;
    sentinel->prev = new_liste_duel;

    return sujet;

}

void supprimer_candidat(struct candidat *candidat){
    free(candidat->liste_duel);
    free(candidat);
}

//candidat *associer_duel(candidat sujet, candidat adverse)

