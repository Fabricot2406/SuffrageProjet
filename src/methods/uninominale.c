/**
 * @file uninominale.c
 * @author Fabio
 * @date 2023-11-28
 * 
 */
#include "uninominale.h"

int nb_candidats, nb_votants;
int * votes;

void initialiser_tableau_votes(ballot * matrice) {
    nb_candidats = matrice -> nb_candidats;
    nb_votants = matrice -> nb_votants; 

    // Création d'un tableau de votes avec le résultat de chaque candidat
    if ((votes = malloc(nb_candidats * sizeof(int))) == NULL) {
        fprintf(stderr,"Erreur lors de l'allocation de la mémoire.\n");
        exit(-1);
    }

    // Init du tableau de votes
    for (int i = 0; i < nb_candidats; i++) {
        votes[i] = 0;
    }
    
    // Entrée des scores de chaque candidats
    for (int i = 0; i < nb_votants; i++) {
        votes[fav_candidat(matrice, i)] ++;
    }
}

void calculer_uninominale_un_tour(ballot * matrice, FILE *output) {
    // Chaîne de caractères à retourner, contenant le résultat de la méthode
    initialiser_tableau_votes(matrice);

    // Recherche du vainqueur
    int vainqueur = 0;
    for (int i = 0; i < nb_candidats; i++) {
        if (votes[i] > votes[vainqueur]) {
            vainqueur = i;
        }
    }
    char * nom_vainqueur = nom_candidat(matrice, vainqueur);
    double score = calculer_score(nb_votants, votes[vainqueur]);
    retourner_vainqueur("uninominale à un tour", nb_candidats, nb_votants, nom_vainqueur, score, output);

    free(votes);
}

void calculer_uninominale_deux_tours(ballot * matrice, FILE *output) {
    initialiser_tableau_votes(matrice);
    // Recherche des deux vainqueurs
    int vainqueur_un = 0, vainqueur_deux = 1;
    for (int i = 0; i < nb_candidats; i++) {
        if (votes[i] > votes[vainqueur_un]) {
            vainqueur_deux = vainqueur_un;
            vainqueur_un = i;
        } else if (votes[i] > votes[vainqueur_deux] && i != vainqueur_un) {
            vainqueur_deux = i;
        }
    }

    char * nom_vainqueur1 = nom_candidat(matrice, vainqueur_un);
    double score1 = calculer_score(nb_votants, votes[vainqueur_un]);
    char * nom_vainqueur2 = nom_candidat(matrice, vainqueur_deux);
    double score2 = calculer_score(nb_votants, votes[vainqueur_deux]);

    // Vérification de la présence de majorité absolue
    if (votes[vainqueur_un] > (nb_votants) / 2) {
        retourner_vainqueur("uninominale à deux tours, tour 1", nb_candidats, nb_votants, nom_vainqueur1, score1, output);
    } else {
        retourner_vainqueur("uninominale à deux tours, tour 1", nb_candidats, nb_votants, nom_vainqueur1, score1, output);
        retourner_vainqueur("uninominale à deux tours, tour 1", nb_candidats, nb_votants, nom_vainqueur2, score2, output);
        votes[vainqueur_un] = 0;
        votes[vainqueur_deux] = 0;

        uni_data *data = creer_uni_data(&vainqueur_un, &vainqueur_deux, votes);
        // Recherche du vainqueur au second tour
        for (int i_votant = 0; i_votant < nb_votants; i_votant++) {
            List * liste_preference = acces_liste_preference(matrice, i_votant);
            Iterator * it = iterator_create(liste_preference);
            while (iterator_has_next(it)){
                Pref *pref = (Pref *)iterator_current(it);
                if(uni_reduce(pref, data)) break;
                iterator_next(it);
            }
            iterator_delete(it);
        }
        // Affichage du vainqueur au second tour
        if (votes[vainqueur_un] < votes[vainqueur_deux]) {
            char * nom_vainqueur = nom_candidat(matrice, vainqueur_deux);
            double score = calculer_score(nb_votants, votes[vainqueur_deux]);
            retourner_vainqueur("uninominale à deux tours, tour 2", nb_candidats, nb_votants, nom_vainqueur, score, output);
        } else {
            char * nom_vainqueur = nom_candidat(matrice, vainqueur_un);
            double score = calculer_score(nb_votants, votes[vainqueur_un]);
            retourner_vainqueur("uninominale à deux tours, tour 2", nb_candidats, nb_votants, nom_vainqueur, score, output);
        }
        free(data);
    }
    free(votes);
}