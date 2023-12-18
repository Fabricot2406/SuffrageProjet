/**
 * @file methode_schulze.c
 * @brief Fichier pour le calcul du vainqueur avec Schulze
 * @author Fabio
 * @date 2023-11-29
 */

 #include "methode_schulze.h"

 /**
 * @brief Compare les scores des arcs a et b.
 * 
 * @param a Un arc.
 * @param b Un arc.
 * @return true : si le score de a est inférieur ou égal à b.
 * @return false : si le score de a est supérieur à b.
 */
 bool comparer_scores(void *a, void *b) {
    arc * elem1 = a;
    arc * elem2 = b;
    return elem1->score <= elem2->score;
}

 /**
 * @brief Fonction permettant de déterminer si un candidat est vainqueur de condorcet.
 * Processus : 1) On cherche pour chaque candidats si il est vainqueur, dans ce cas on retourne son indice.
 *             2) Dans le cas contraire, on retourne -1.
 * 
 * @param list_arc Liste d'arcs triée par ordre croissant.
 * @param nb_candidats Nombre de candidats.
 * @param candidats_nom Liste des noms des candidats.
 * @return i : l'indice du candidat vainqueur si il y a un vainqueur.
 * @return -1 : si il n'y a pas de vainqueur à ce stade.
 */
 int trouver_vainqueur_schulze(List *list_arc, int nb_candidats, char **candidats_nom) {
    // Pour chaque candidat, on vérifie si il est vainqueur
    for (int candidat = 0; candidat < nb_candidats; candidat++) {
        if (est_vainqueur(list_arc, candidat)) {
            // Le vainqueur est à l'indice désigné par la variable candidat
            return candidat;
        }
    }
    (void)candidats_nom;
    // Pas de vainqueur, on retourne -1
    return -1;
}

/**
 * @brief Fonction permettant de déterminer si un candidat est vainqueur de condorcet.
 * Processus : 1) Tant qu'on ne trouve pas de vainqueur dans la liste d'arcs, on retire le premier arc.
 *             2) Une fois le vainqueur trouvé, on l'affiche.
 * 
 * @param list_arc Liste d'arcs triée par ordre croissant.
 * @param nb_candidats Nombre de candidats.
 * @param candidats_nom Liste des noms des candidats.
 * @param output Le fichier de sortie dans lequel on écrit le résultat.
 */
 void reduire_arcs(List *list_arc, int nb_candidats, char **candidats_nom, FILE *output) {
    int vainqueur;

    // On continue de retirer l'arc tant qu'on n'a pas de vainqueur
    while ((vainqueur = trouver_vainqueur_schulze(list_arc, nb_candidats, candidats_nom)) == -1)
        list_remove_at(list_arc, 0, free);

    // A COMPLETER AVEC NBCANDIDATS ET NBVOTANTS
    retourner_vainqueur("Condorcet Schulze", nb_candidats, nb_candidats, candidats_nom[vainqueur], 0, output);
}

void condorcet_schulze(t_mat_int_dyn *matrice_duel, char **candidats_nom, FILE *output) {
    // Création de la liste d'arcs
    larc *list_arc = larc_init(matrice_duel);
    // Tri de la liste d'arcs
    list_arc -> larc = list_sort(list_arc -> larc, comparer_scores);
    // Détermination du vainqueur
    reduire_arcs(list_arc -> larc, list_arc -> nb_candidats, candidats_nom, output);
    // Destruction de la liste d'arcs
    larc_delete(list_arc);
}