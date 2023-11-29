/** \\file */
/**
 * @file uninominale.c
 * @author Fabio
 * @date 2023-11-28
 * 
 */
#include "uninominale.h"

int nbCandidats, nbVotants;
int * votes;

void initialiserTableauVotes(ballot * matrice) {
    nbCandidats = matrice -> nb_candidats;
    nbVotants = matrice -> nb_votants; 

    // Création d'un tableau de votes avec le résultat de chaque candidat
    if ((votes = malloc(nbCandidats * sizeof(int))) == NULL) {
        fprintf(stderr,"Erreur lors de l'allocation de la mémoire.\n");
        exit(-1);
    }

    // Init du tableau de votes
    for (int i = 0; i < nbCandidats; i++) {
        votes[i] = 0;
    }
    
    // Entrée des scores de chaque candidats
    for (int i = 0; i < nbVotants; i++) {
        votes[fav_candidat(matrice, i)] ++;
    }
}

void calculerUninominaleUnTour(ballot * matrice) {
    initialiserTableauVotes(matrice);

    // Recherche du vainqueur
    int vainqueur = 0;
    for (int i = 0; i < nbCandidats; i++) {
        if (votes[i] > votes[vainqueur]) {
            vainqueur = i;
        }
    }
    char * nomVainqueur = nom_candidat(matrice, vainqueur);
    double score = calculerScore(nbVotants, votes[vainqueur]);
    afficherVainqueur("uninominale à un tour", nbCandidats, nbVotants, nomVainqueur, score);

    free(votes);
}

void calculerUninominaleDeuxTours(ballot * matrice) {
    initialiserTableauVotes(matrice);
    // Recherche des deux vainqueurs
    int vainqueurUn = 1, vainqueurDeux = 0;
    for (int i = 0; i < nbCandidats; i++) {
        if (votes[i] > votes[vainqueurUn]) {
            vainqueurDeux = vainqueurUn;
            vainqueurUn = i;
        } else if (votes[i] > votes[vainqueurDeux]) {
            vainqueurDeux = i;
        }
    }

    char * nomVainqueur1 = nom_candidat(matrice, vainqueurUn);
    double score1 = calculerScore(nbVotants, votes[vainqueurUn]);
    char * nomVainqueur2 = nom_candidat(matrice, vainqueurDeux);
    double score2 = calculerScore(nbVotants, votes[vainqueurDeux]);

    // Vérification de la présence de majorité absolue
    if (votes[vainqueurUn] > (nbVotants) / 2) {
        afficherVainqueur("uninominale à deux tours, tour 1", nbCandidats, nbVotants, nomVainqueur1, score1);
    } else {
        afficherVainqueur("uninominale à deux tours, tour 1", nbCandidats, nbVotants, nomVainqueur1, score1);
        afficherVainqueur("uninominale à deux tours, tour 1", nbCandidats, nbVotants, nomVainqueur2, score2);
        votes[vainqueurUn] = 0;
        votes[vainqueurDeux] = 0;

        uni_data *data = creer_uni_data(&vainqueurUn, &vainqueurDeux, votes);
        // Recherche du vainqueur au second tour
        for (int i_votant = 0; i_votant < nbVotants; i_votant++) {
            List * liste_preference = acces_liste_preference(matrice, i_votant);
            list_reduce(liste_preference, uni_reduce, (void *)data);
        }
        // Affichage du vainqueur au second tour
        if (votes[vainqueurUn] < votes[vainqueurDeux]) {
            char * nomVainqueur = nom_candidat(matrice, vainqueurDeux);
            double score = calculerScore(nbVotants, votes[vainqueurDeux]);
            afficherVainqueur("uninominale à deux tours, tour 2", nbCandidats, nbVotants, nomVainqueur, score);
        } else {
            char * nomVainqueur = nom_candidat(matrice, vainqueurUn);
            double score = calculerScore(nbVotants, votes[vainqueurUn]);
            afficherVainqueur("uninominale à deux tours, tour 2", nbCandidats, nbVotants, nomVainqueur, score);
        }
        free(data);
    }
    free(votes);
}