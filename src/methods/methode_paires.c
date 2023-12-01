/** \\file */
/**
 * @file methode_paires.c
 * @author Anthony
 * @date 2023-11-28
 */
#include "methode_paires.h"


/**
 * @brief Parcour de la liste d'arc pour déterminer les potentiels arcs à supprimer.
 * Les arcs à supprimer sont ceux qui lors de l'ajout d'un arc dans le graphe, créent un circuit.
 * Processus : 1) Pour chaque arc de la liste, on ajoute une succession dans le graphe.
 *             2) On vérifie si il y a un circuit dans le graphe.
 *             3) Si il y a un circuit, on supprime l'arc de la liste et on supprime la succession dans le graphe.
 * 
 * @param list_arc Liste d'arc trié par ordre décroissant de différence de voix (score).
 * @return int Le nombre d'arc supprimé.
 * @pre La liste d'arc est initialisé et trié par ordre décroissant de différence de voix (score).
 * @post La liste d'arc est modifié. Les arcs supprimés sont ceux qui créent un circuit dans le graphe.
 */
int filtrer_larc(larc *list_arc){
    int nb_circuit = 0;
    int nb_candidats = list_arc->nb_candidats;
    graphe *g = creation_graphe(nb_candidats);
    Iterator *it = iterator_create(list_arc->larc);

    // Pour chaque arc de la liste
    while (iterator_has_next(it)){
        arc *a = iterator_current(it);
        // On ajoute une succession dans le graphe
        ajout_succession(g->graphe[a->candidat_gagnant], g->graphe[a->candidat_perdant]);
        sommet *s_current = g->graphe[a->candidat_gagnant];
        // Tableau de status initialisé à chaque ajout de succession
        initialiser_status(g, s_current->indice);

        // Si un circuit est détecté dans le graphe après l'ajout de l'arc
        if (circuits(g, s_current)){
            nb_circuit++;
            // On supprime l'arc de la liste et on supprime la succession dans le graphe
            delete_succession(g->graphe[a->candidat_gagnant]);
            int index = iterator_index(it);
            iterator_prev(it);
            // Arc supprimé de la liste
            list_remove_at(list_arc->larc, index, free);
        }

        iterator_next(it);
    }
    // Libération de la mémoire
    iterator_delete(it);
    detruire_graphe(g);
    return nb_circuit;
}

/**
 * @brief Fonction permettant de déterminer si un candidat est vainqueur.
 * Processus à suivre : 1) On parcourt la liste d'arc.
 *                          - Si le candidat est impliqué dans un arc où il est perdant, alors il n'est pas vainqueur.
 *                          - Si le candidat n'est impliqué dans aucun arc où il est perdant, alors il est vainqueur.
 * 
 * @param list_arc Liste d'arc trié par ordre décroissant de différence de voix (score).
 * @param candidat Candidat dont on veut savoir si il est vainqueur.
 * @return true Si le candidat est vainqueur.
 * @return false Si le candidat n'est pas vainqueur.
 */
bool est_vainqueur(List *list_arc, int candidat){
    Iterator *it_larc = iterator_create(list_arc);
    // On parcourt la liste d'arc
    while (iterator_has_next(it_larc)){
        arc *arc_courant = iterator_current(it_larc);
        // Si le candidat est impliqué dans un arc où il est perdant
        if (arc_courant->candidat_perdant == candidat){
            // Il n'est pas vainqueur
            iterator_delete(it_larc);
            return false;
        }
        iterator_next(it_larc);
    }
    iterator_delete(it_larc);
    // Sinon il est vainqueur
    return true;
}

/**
 * @brief Fonction utilisé pour déterminer quel candidat est vainqueur parmi les candidats restant à classer.
 * Processus à suivre : 1) Pour chaque candidat restant, on vérifie si il est vainqueur (voir fonction est_vainqueur).
 *                      2) Si il est vainqueur :
 *                          - on l'ajoute dans le classement.
 *                          - on le supprime de la liste des candidats restant.
 *                          - supression des arcs pour lesquels le candidat est impliqué.
 * 
 * @param list_arc Liste d'arc trié par ordre décroissant de différence de voix (score).
 * @param classement Liste de candidat classé
 * @param candidats_restant Liste de candidat restant à classer
 * @param candidats_nom Tableau de nom des candidats.
 */
void determiner_vainqueur(List *list_arc,List *classement,List *candidats_restant,char **candidats_nom){
    Iterator *it_candidat_restant = iterator_create(candidats_restant);
    // On parcourt la liste des candidats restant
    while(iterator_has_next(it_candidat_restant)){
        int *cand_courrant = iterator_current(it_candidat_restant);
        // Si le candidat est vainqueur
        if (est_vainqueur(list_arc,*cand_courrant)){
            int candidat_gagnant = *cand_courrant;
            char *nom_candidat = candidats_nom[candidat_gagnant];
            // On l'ajoute dans le classement
            list_push_back(classement,nom_candidat);
            // On le supprime de la liste des candidats restant
            list_remove_at(candidats_restant,iterator_index(it_candidat_restant),free);
            // Supression des arcs pour lesquels le candidat est impliqué
            supprimer_candidat(list_arc,candidat_gagnant);
            break;
        }
        iterator_next(it_candidat_restant);
    }
    // Libération de la mémoire
    iterator_delete(it_candidat_restant);
}

/**
 * @brief Fonction permettant de créer un classement des candidats selon la méthode de Condorcet.
 * Processus : Application de la fonction determiner_vainqueur jusqu'à ce qu'il ne reste plus de candidats à classer.
 * 
 * @param list_arc Liste d'arc trié par ordre décroissant de différence de voix (score).
 * @param candidats_nom Tableau de nom des candidats.
 * @return List* Liste de candidat trié par ordre décroissant de score (le premier candidat est le vainqueur).
 */
List *determiner_classement(larc *list_arc,char **candidats_nom){
    List *larc = list_arc->larc;
    int nb_candidats = list_arc->nb_candidats;
    // Utilisation d'une liste pour stocker les candidats restant à classer
    List *candidats_restant = list_create();
    // Initialisation de la liste des candidats restant
    for (int i_candidat = 0; i_candidat < nb_candidats; i_candidat++){
        int *elem = malloc(sizeof(int));
        *elem = i_candidat;
        list_push_back(candidats_restant,elem);
    }
    // Création d'une liste de candidat classé
    List *classement = list_create();
    
    // Tant qu'il reste des candidats à classer
    while(!list_is_empty(candidats_restant)){
        // Détermination du vainqueur parmi les candidats restant
        determiner_vainqueur(larc,classement,candidats_restant,candidats_nom);
    }

    // Libération de la mémoire
    list_delete(candidats_restant,free);
    return classement;
}

void condorcet_paires(t_mat_int_dyn *matrice_duel,char **candidats_nom) {
    // Création de la liste d'arc
    larc *list_arc = larc_init(matrice_duel);
    afficher_larc(list_arc);

    // Filtrage de la liste d'arc
    int nb_circuit = filtrer_larc(list_arc);
    printf("Nombre de circuit détecté : %d\n\n",nb_circuit);
    //afficher_larc(list_arc);

    // Détermination du classement des candidats
    List *classement = (List *)determiner_classement(list_arc,candidats_nom);
    afficher_classement(classement);

    // Libération de la mémoire
    detruire_larc(list_arc);
    list_delete(classement,vide);
}