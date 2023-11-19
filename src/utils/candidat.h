/**
 * @file matrice_duel.h
 * @brief A DEFINIR
 */

#ifndef CANDIDAT_H
#define CANDIDAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct candidat candidat;

typedef struct double_linked liste_duel;

typedef struct duel duel;

candidat *creer_candidat(char *nom);

candidat *ajouter_association_duel(candidat *sujet,candidat *opposant);

void supprimer_candidat(struct candidat *candidat);


#endif