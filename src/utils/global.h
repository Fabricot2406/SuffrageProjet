/** \\file */
/**
 * @file global.h
 * @author Anthony
 * @brief Fichier global qui contient tous les headers des fichiers .c
 * @date 2023-11-28
 */
#include "lecture_csv.h"
#include "utils_main.h"
#include "utils_sd.h"
#include "./dataStructure/matrice_int_dyn.h"
#include "./dataStructure/matrice_string_dyn.h"
#include "./dataStructure/listegen.h"
#include "./dataStructure/ballot.h"
#include "./dataStructure/duel.h"
#include "./dataStructure/arc.h"
#include "./dataStructure/graphe.h"
#include "../methods/uninominale.h"
#include "../methods/jugement_majoritaire.h"
#include "../methods/methode_paires.h"
#include "../methods/methode_schulze.h"
#include "../verify/verify_my_vote.h"