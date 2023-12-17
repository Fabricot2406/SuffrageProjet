#include "methode_minimax.h"

/**
 * @file methode_minimax.c
 * @brief Implémentation de la méthode Minimax.
 * @author Marco
 * @date 2023-12-03
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
void remplir_tab_pire_score(void *elem, void *tab){
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
 * de chaque candidat et initialise tous les scores à zéro. Elle utilise ensuite la fonction remplirTabpire_score
 * pour remplir ce tableau avec les pires scores de chaque candidat. Enfin, elle détermine le candidat gagnant
 * comme étant celui dont le pire score est le plus bas et affiche le nom du gagnant.
 * 
 * @param matrice_duel La matrice de duel.
 * @param candidats_nom La liste des noms des candidats.
 * @param output Le fichier de sortie dans lequel on écrit le résultat.
 */
void condorcet_minimax(t_mat_int_dyn *matrice_duel,char **candidats_nom, FILE *output){
    larc *list_arc = larc_init(matrice_duel);
    //afficher_larc(list_arc);
    int pire_score[matrice_duel->cols];
    for (int i = 0; i<matrice_duel->cols; i++){
        pire_score[i] = 0;
    }
    list_reduce(list_arc->larc,remplir_tab_pire_score,pire_score);
    int candidat_gagnant = 0;
    for (int i = 0; i<matrice_duel->cols; i++){
        if (pire_score[i] < pire_score[candidat_gagnant]){
            candidat_gagnant = i;
        }
    }
    detruire_larc(list_arc);
    retourner_vainqueur("Condorcet minimax",matrice_duel->cols,matrice_duel->rows,candidats_nom[candidat_gagnant],0, output);
}

/**
 * @brief Utilisée pour afficher le tableau du pire score de chaque candidats.
 *
 * @param tab Le tableau à afficher.
 * @param taille La taille du tableau.
 */
void afficher_tab(int *tab, int taille){
    for (int i = 0; i<taille; i++){
        printf("%d ",tab[i]);
    }
    printf("\n");
}