#include "ballot.h"

ballot *creer_ballot(int nb_candidats, int nb_votants){
    ballot *b = malloc(sizeof(ballot));
    b->nb_candidats = nb_candidats;
    b->nb_votants = nb_votants;
    b->candidats_nom = malloc(sizeof(char*) * nb_candidats);
    b->classement = list_create();
    return b;
}

/**
 * @brief Crée un ensemble de préférence
 * @param rang Le rang de préférence
 * @return Pref* L'ensemble de préférence créé
 */
Pref *creer_ensemble_preference(int rang){
    Pref *pref = malloc(sizeof(Pref));
    pref->values = rang;
    pref->list = list_create();
    return pref;
}

/**
 * @brief Remplit la liste des noms de candidats à partir du fichier csv
 * @param b Le ballot à remplir
 * @param classement_csv La matrice de classement à partir du fichier csv
 * @return ballot* Le ballot rempli
 */
ballot *remplir_liste_candidats(ballot *b, t_mat_char_star_dyn *classement_csv){
    int i = 0;
    char ***matrice_csv = classement_csv->tab;
    // Remplissage de la liste de candidats
    for (int i = 0; i < b->nb_candidats; i++){
        char *nom = malloc(sizeof(char) * strlen(matrice_csv[0][i + 4]) + 1);
        strcpy(nom, matrice_csv[0][i + 4]);
        b->candidats_nom[i] = nom;
    }
    return b;
}

/**
 * @brief Recherche le rang de préférence dans une liste.
 *
 * Cette fonction permet de rechercher le rang de préférence spécifié
 * dans une liste de préférences. Elle peut être utilisée pour vérifier
 * la présence du rang de préférence ou pour obtenir l'indice du premier
 * élément correspondant.
 *
 * @param list La liste dans laquelle effectuer la recherche.
 * @param rang_preference Le rang de préférence à rechercher.
 * @param find_index Si vrai, retourne l'indice du premier élément correspondant.
 *                   Si faux, retourne simplement vrai si le rang est présent.
 * @return Si find_index est vrai, retourne l'indice du premier élément correspondant,
 *         sinon, retourne vrai si le rang de préférence est présent, sinon faux.
 */
int rechercher_preference(List *list, int rang_preference, bool find_index) {
    Iterator *it = iterator_create(list);
    int indice = 0;

    while (iterator_has_next(it)) {
        Pref *current = (Pref *)iterator_current(it);

        if (current->values == rang_preference) {
            int result = (find_index) ? indice : 1;
            iterator_delete(it);
            return result;
        }
        indice++;
        iterator_next(it);
    }
    iterator_delete(it);
    return (find_index) ? -1 : 0;
}

// Fonction de comparaison pour les préférences
int compare_pref(const void *a, const void *b) {
    return ((Pref *)a)->values - ((Pref *)b)->values;
}

/**
 * @brief Ajoute un ensemble de préférence à la liste d'ensemble de préférence
 * @param liste_preferences La liste d'ensemble de préférence
 * @param candidat_ptr Le pointeur vers le candidat à ajouter
 * @param rang_preference Le rang de préférence du candidat
 */
void ajout_ensemble_preference(List *liste_preferences, int * candidat_ptr, int rang_preference){
    // CAS 1 : Aucun ensemble de candidat n'existe pour le rang trouvé
    if(rechercher_preference(liste_preferences,rang_preference,false) == false){
        // Création d'un ensemble de préférence
        Pref *new_ens_pref = creer_ensemble_preference(rang_preference);
        list_push_back(new_ens_pref->list, candidat_ptr);
        // Cas particulier : liste vide
        if(list_is_empty(liste_preferences)){
            list_push_back(liste_preferences, (void *)new_ens_pref);
        }else{ // Cas général : liste non vide
            insert_sorted(liste_preferences, new_ens_pref, compare_pref);
        }
    }else{ // CAS 2 : Un ensemble de candidat existe pour le rang trouvé
        int indice = rechercher_preference(liste_preferences,rang_preference,true);
        Pref *ens_pref_existant = (Pref *)list_at(liste_preferences, indice);
        list_push_back(ens_pref_existant->list, candidat_ptr);
    }
}

/**
 * @brief Remplit la structure de données de classement avec les données du fichier CSV.
 *
 * Cette fonction prend une structure de données de type ballot et remplit sa liste
 * de classement avec les informations provenant d'une matrice CSV représentant les
 * préférences des votants. Chaque ligne de la matrice CSV représente les préférences
 * d'un votant, et chaque colonne à partir de la 5ème contient le rang de préférence
 * d'un candidat pour ce votant.
 *
 * @param b La structure de données de type ballot à remplir.
 * @param classement_csv La matrice CSV contenant les préférences des votants.
 * @return Un pointeur vers la structure de données ballot remplie.
 */
ballot *remplir_classement(ballot *b, t_mat_char_star_dyn *classement_csv){
    char ***matrice_csv = classement_csv->tab;
    int nb_candidats = b->nb_candidats;
    int nb_votants = b->nb_votants;
    for(int votant = 0; votant < nb_votants; votant++){
        // Création d'une liste d'ensemble de préférence pour un votant
        List *liste_preferences = list_create();
        for(int candidat = 0; candidat < nb_candidats; candidat++){
            // 4 colonnes et 1 ligne de plus pour ne pas prendre en compte les infos de l'élection
            int rang_preference = atoi(matrice_csv[votant + 1][candidat + 4]);
            if (rang_preference == -1) rang_preference = nb_candidats + 1;
            int *candidat_ptr = malloc(sizeof(int));
            *candidat_ptr = candidat;
            ajout_ensemble_preference(liste_preferences, candidat_ptr, rang_preference);
        }
        // Ajout de la liste d'ensemble de préférence à la liste de votant
        list_push_back(b->classement, liste_preferences);
    }
    return b;
}

ballot *remplir_ballot(ballot *b, t_mat_char_star_dyn *classement_csv){
    // Remplissage de la liste des noms de candidats
    b = remplir_liste_candidats(b, classement_csv);
    // Remplissage de la matrice de classement
    b = remplir_classement(b, classement_csv);
    libererMatrice(classement_csv);
    return b;
}

/**
 * @brief Détruit un ensemble de préférence
 * @param elem Pointeur vers l'ensemble de préférence à détruire
 */
void detruire_ensemble_preference(void *elem){
    Pref *pref = (Pref *)elem;
    list_delete((ptrList *)pref->list,free);
    free(pref);
}

/**
 * @brief Détruit une liste d'ensemble de préférence
 * @param elem Pointeur vers la liste d'ensemble de préférence à détruire
 */
void detruire_liste_ensemble_preference(void *elem){
    List *list = (List *)elem;
    list_delete((ptrList *)list,detruire_ensemble_preference);
}

void detruire_ballot(ballot *b){
    for (int i = 0; i < b->nb_candidats; i++){
        free(b->candidats_nom[i]);
    }
    free(b->candidats_nom);
    list_delete((ptrList *)b->classement,detruire_liste_ensemble_preference);
    free(b);
}

/******************* UTILS *********************/

char *nom_candidat(ballot *b, int indice_candidat){
    return b->candidats_nom[indice_candidat];
}

List *acces_liste_preference(ballot *b, int num_votant){
    assert(num_votant < b->nb_votants && num_votant >= 0);
    List *list = b->classement;
    List *classement_courant = (List *)list_at(list,num_votant);
    return classement_courant;
}

int fav_candidat(ballot *b,int num_votant){
    List *list = b->classement;
    List *classement_courant = (List *)list_at(list,num_votant);
    Pref *pref_courant = (Pref *)list_at(classement_courant,0);
    int *indice_candidat = (int *)list_at(pref_courant->list,0);
    return *indice_candidat;
}

void afficher_liste_candidat(void *data) {
    printf(" %d ", *(int *)data);
}

void afficher_ensemble_preference(void *data) {
    Pref *pref = (Pref *)data;
    int rang = pref->values;
    printf("(%d)", rang);
    list_map(pref->list, afficher_liste_candidat);
    printf("\t");
}

void afficher_liste_votant(void *data) {
    List *list_pref = (List *)data;
    list_map(list_pref, afficher_ensemble_preference);
    printf("\n");
}

void afficher_ballot(ballot *b) {
    printf("\nNombre de candidats : %d\n", b->nb_candidats);
    printf("Nombre de votants : %d\n\n", b->nb_votants);
    printf("Liste des candidats : \n");
    for (int i = 0; i < b->nb_candidats; i++) {
        printf("[%d] : %s\n",i,b->candidats_nom[i]);
    }
    printf("\n");
    printf("Liste des ballots : \n\n");
    list_map(b->classement, afficher_liste_votant);
}