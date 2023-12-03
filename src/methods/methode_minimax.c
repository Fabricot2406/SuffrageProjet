#include "methode_minimax.h"

/**
 * @file methode_minimax.c
 * @brief Implémentation de la méthode Minimax.
 * @author Marco
 * @version 1.0
*/


/**
 * @brief Remplit le tableau des pires scores.
 *
 * Cette fonction compare le score de l'arc avec le score du candidat perdant (initialisé à 0).
 * Si le score de l'arc est supérieur au pire score actuel du candidat perdant, il le remplace par le score de l'arc.
 *
 * @param elem L'élément à traiter (un arc).
 * @param tab Le tableau à remplir (tableau des pires scores).
 */
void remplirTabPireScore(void *elem, void *tab){
    //On cast l'élément au type arc et tab au type int*
    arc *a = (arc *)elem;
    int *tab_pire_score = (int *)tab;
    //On compare le score de l'arc avec le score du candidat perdant (initialisé à 0)
    if (a->score > tab_pire_score[a->candidat_perdant]){
        //Le score de l'arc représente la différence de voix entre les deux candidats
        //Le pire score d'un canidat est donc le plus grand score de l'arc où il est perdant
        //Si le score de l'arc est supérieur au pire score actuel du candidat perdant, on le remplace par le score de l'arc
        tab_pire_score[a->candidat_perdant] = a->score;
    }
}

/**
 * @brief Implémente la méthode Minimax.
 *
 * Cette fonction implémente la méthode Minimax pour déterminer le gagnant d'une élection.
 * Elle crée d'abord une matrice de duels à partir des bulletins de vote. Ensuite, elle initialise
 * une liste d'arcs à partir de cette matrice. Elle alloue ensuite un tableau pour stocker le pire score
 * de chaque candidat et initialise tous les scores à zéro. Elle utilise ensuite la fonction remplirTabPireScore
 * pour remplir ce tableau avec les pires scores de chaque candidat. Enfin, elle détermine le candidat gagnant
 * comme étant celui dont le pire score est le plus bas et affiche le nom du gagnant.
 *
 * @param matrice_ballot La matrice des bulletins de vote.
 */
void methodeMinimax(ballot *matrice_ballot){
    t_mat_int_dyn *matrice_duel = creer_matrice_duel(matrice_ballot);
    //afficher_matrice_duels(matrice_duel);
    larc *list_arc = larc_init(matrice_duel);
    //afficher_larc(list_arc);
    int *pireScore = malloc(sizeof(int)*matrice_ballot->nb_candidats);
    for (int i = 0; i<matrice_ballot->nb_candidats; i++){
        pireScore[i] = 0;
    }
    list_reduce(list_arc->larc,remplirTabPireScore,pireScore);
    int candidat_gagnant = 0;
    for (int i = 0; i<matrice_ballot->nb_candidats; i++){
        if (pireScore[i] < pireScore[candidat_gagnant]){
            candidat_gagnant = i;
        }
    }
    afficherVainqueur("Condorcet minimax",matrice_ballot->nb_candidats,matrice_ballot->nb_votants,nom_candidat(matrice_ballot,candidat_gagnant),0);
}

/**
 * @brief Utilisée pour afficher le tableau du pire score de chaque candidats.
 *
 * @param tab Le tableau à afficher.
 * @param taille La taille du tableau.
 */
void afficherTab(int *tab, int taille){
    for (int i = 0; i<taille; i++){
        printf("%d ",tab[i]);
    }
    printf("\n");
}