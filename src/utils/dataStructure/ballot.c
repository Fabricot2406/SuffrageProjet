/**
 * @file ballot.c
 * @author Anthony
 * @brief Structure de données représentant un ballot de vote.
 * @date 2023-11-15
 */
#include "ballot.h"

// Constantes d'incrémentation permettant d'ignorer les colonnes inutiles du CSV
#define INCREMENT_COLONNE 4
#define INCREMENT_LIGNE 1

ballot *ballot_create(int nb_candidats, int nb_votants){
    assert(nb_candidats > 0);
    assert(nb_votants > 0);
    nb_candidats -= INCREMENT_COLONNE;
    nb_votants -= INCREMENT_LIGNE;
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
Pref *ens_pref_create(int rang){
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
ballot *list_candidat_init(ballot *b, t_mat_char_star_dyn *classement_csv){
    char ***matrice_csv = classement_csv->tab;
    // Remplissage de la liste de candidats
    for (int i = 0; i < b->nb_candidats; i++){
        char *nom = malloc(sizeof(char) * strlen(matrice_csv[0][i + INCREMENT_COLONNE]) + INCREMENT_LIGNE);
        strcpy(nom, matrice_csv[0][i + INCREMENT_COLONNE]);
        b->candidats_nom[i] = nom;
    }
    return b;
}

/**
 * @brief Recherche le rang de préférence dans une liste.
 *
 * @details Cette fonction permet de rechercher le rang de préférence spécifié
 * dans une liste de préférences. Elle peut être utilisée pour vérifier
 * la présence du rang de préférence ou pour obtenir l'indice du premier
 * élément correspondant.
 *
 * @param list La liste de préférence dans laquelle effectuer la recherche.
 * @param rang_preference Le rang de préférence à rechercher.
 * @param find_index
 * @return Si find_index = true : indice du premier élément correspondant.
 * @return Si find_index = false : 1 si le rang de préférence est présent, sinon 0.
 */
int ens_pref_search(List *list, int rang_preference, bool find_index) {
    Iterator *it = iterator_create(list);
    int indice = 0;

    while (iterator_has_next(it)) {
        Pref *current = (Pref *)iterator_current(it);

        if (current->values == rang_preference) {
            iterator_delete(it);
            return (find_index) ? indice : 1;
        }
        indice++;
        iterator_next(it);
    }
    iterator_delete(it);
    return find_index;
}

/**
 * @brief Fonction de comparaison pour le tri de la liste d'ensemble de préférence
 * @param a Pointeur vers le premier ensemble de préférence
 * @param b Pointeur vers le second ensemble de préférence
 * @return int Résultat de la comparaison
 */
int ens_pref_comp(const void *a, const void *b) {
    return ((Pref *)a)->values - ((Pref *)b)->values;
}

/**
 * @brief Ajoute une liste de préférence à la liste d'ensemble de préférence
 * @details Si l'ensemble de préférence n'existe pas, il est créé et ajouté à la liste
 *        - Si l'ensemble de préférence existe, le candidat est ajouté à l'ensemble
 *        - L'ensemble de préférence est trié par ordre croissant de rang de préférence
 * @param liste_preferences La liste d'ensemble de préférence
 * @param candidat_ptr Le pointeur vers le candidat à ajouter
 * @param rang_preference Le rang de préférence du candidat
 */
void ens_pref_add(List *liste_preferences, int * candidat_ptr, int rang_preference){

    // CAS 1 : Aucun ensemble de candidat n'existe pour le rang trouvé
    if(!ens_pref_search(liste_preferences,rang_preference,false)){

        // Création d'un ensemble de préférence
        Pref *new_ens_pref = ens_pref_create(rang_preference);
        list_push_back(new_ens_pref->list, candidat_ptr);

        // Cas particulier : liste vide
        if(list_is_empty(liste_preferences))
            list_push_back(liste_preferences, (void *)new_ens_pref);

        // Cas général : liste non vide
        else insert_sorted(liste_preferences, new_ens_pref, ens_pref_comp);

    // CAS 2 : Un ensemble de candidat existe pour le rang trouvé
    }else{
        int indice = ens_pref_search(liste_preferences,rang_preference,true);
        Pref *ens_pref_existant = (Pref *)list_at(liste_preferences, indice);
        list_push_back(ens_pref_existant->list, candidat_ptr);
    }
}

/**
 * @brief Remplit la structure de données de classement avec les données du fichier CSV.
 *
 * @details Cette fonction prend une structure de données de type ballot et remplit sa liste
 * de classement avec les informations provenant d'une matrice CSV représentant les
 * préférences des votants. Chaque ligne de la matrice CSV représente les préférences
 * d'un votant, et chaque colonne à partir de la 5ème contient le rang de préférence
 * d'un candidat pour ce votant.
 *
 * @param b La structure de données de type ballot à remplir.
 * @param classement_csv La matrice CSV contenant les préférences des votants.
 * @return Un pointeur vers la structure de données ballot remplie.
 */
ballot *classement_init(ballot *b, t_mat_char_star_dyn *classement_csv){
    char ***matrice_csv = classement_csv->tab;
    int nb_candidats = b->nb_candidats;
    int nb_votants = b->nb_votants;

    // Pour chaque votant dans le fichier csv
    for(int votant = 0; votant < nb_votants; votant++){

        // Création d'une liste d'ensemble de préférence
        List *liste_preferences = list_create();

        // Remplissage de la liste d'ensemble de préférence
        for(int candidat = 0; candidat < nb_candidats; candidat++){
            // Récupération du rang de préférence pour un candidat
            int rang_preference = atoi(matrice_csv[votant + INCREMENT_LIGNE][candidat + INCREMENT_COLONNE]);
            if (rang_preference == -1) rang_preference = nb_candidats + 1;
            int *candidat_ptr = malloc(sizeof(int));
            *candidat_ptr = candidat;

            // Ajout du candidat à la liste d'ensemble de préférence
            ens_pref_add(liste_preferences, candidat_ptr, rang_preference);
        }
        // Ajout de la liste d'ensemble de préférence à la liste de votant
        list_push_back(b->classement, liste_preferences);
    }
    return b;
}

ballot *ballot_init(ballot *b, t_mat_char_star_dyn *classement_csv){
    assert(b != NULL);
    assert(classement_csv != NULL);
    // Remplissage de la liste des noms de candidats
    b = list_candidat_init(b, classement_csv);
    // Remplissage de la matrice de classement
    b = classement_init(b, classement_csv);
    return b;
}

/**
 * @brief Détruit un ensemble de préférence
 * @param elem Pointeur vers l'ensemble de préférence à détruire
 * @pre elem != NULL
 */
void ens_pref_delete(void *elem){
    assert(elem != NULL);
    Pref *pref = (Pref *)elem;
    // Libération de la mémoire allouée pour la liste de candidat
    list_delete(pref->list,free);
    free(pref);
}

/**
 * @brief Détruit une liste d'ensemble de préférence
 * @param elem Pointeur vers la liste d'ensemble de préférence à détruire
 * @pre elem != NULL
 */
void list_ens_pref_delete(void *elem){
    assert(elem != NULL);
    List *list = (List *)elem;
    // Libération de la mémoire allouée pour la liste de préférence
    list_delete(list,ens_pref_delete);
}

void ballot_delete(ballot *b){
    assert(b != NULL);
    // Libération de la mémoire allouée pour les noms des candidats
    for (int i = 0; i < b->nb_candidats; i++) free(b->candidats_nom[i]);
    free(b->candidats_nom);

    // Libération de la mémoire allouée pour les listes de préférence
    list_delete(b->classement,list_ens_pref_delete);
    // Libération de la mémoire allouée pour le ballot
    free(b);
}

/******************* UTILS *********************/

char *get_candidat_nom(ballot *b, int indice_candidat){
    return b->candidats_nom[indice_candidat];
}

List *get_liste_pref(ballot *b, int num_votant){
    assert(num_votant < b->nb_votants && num_votant >= 0);
    List *list = b->classement;
    List *classement_courant = (List *)list_at(list,num_votant);
    return classement_courant;
}

int get_fav_candidat(ballot *b,int num_votant){
    List *list = b->classement;
    List *classement_courant = (List *)list_at(list,num_votant);
    Pref *pref_courant = (Pref *)list_at(classement_courant,0);
    int *indice_candidat = (int *)list_at(pref_courant->list,0);
    return *indice_candidat;
}

void ballot_log(ballot *b, FILE *log_file) {
    fprintf(log_file,"Nombre de candidats : %d\n", b->nb_candidats);
    fprintf(log_file,"Nombre de votants : %d\n\n", b->nb_votants);
    fprintf(log_file,"Liste des candidats : \n");
    for (int i = 0; i < b->nb_candidats; i++) {
        fprintf(log_file,"[%d] : %s\n",i,b->candidats_nom[i]);
    }
    fprintf(log_file,"\n");
    fprintf(log_file,"Liste des ballots : (nombre occurence : indice_candidat > indice_candidat ...)\n");
    fprintf(log_file,"(à saisir dans le simulateur \"https://jorisdeguet.github.io/PrefVote/tideman.html\")\n");

    // Créer un iterateur sur la liste de votant
    Iterator *it = iterator_create(b->classement);
    // Parcourir la liste de votant
    while (iterator_has_next(it)) {
        fprintf(log_file,"1 : ");
        List *list_pref = (List *)iterator_current(it);
        Iterator *it_pref = iterator_create(list_pref);
        // Parcourir la liste d'ensemble de préférence
        while (iterator_has_next(it_pref)) {

            Pref *pref = (Pref *)iterator_current(it_pref);
            Iterator *it_candidat = iterator_create(pref->list);
            // Parcourir la liste de candidat
            while (iterator_has_next(it_candidat)) {
                int *candidat = (int *)iterator_current(it_candidat);
                fprintf(log_file,"%d",*candidat);
                iterator_next(it_candidat);
                if (iterator_has_next(it_candidat)) fprintf(log_file," = ");
            }
            iterator_delete(it_candidat);
            iterator_next(it_pref);
            if (iterator_has_next(it_pref)) fprintf(log_file," > ");
        }
        iterator_delete(it_pref);
        iterator_next(it);
        if (iterator_has_next(it)) fprintf(log_file,"\n");
    }
    iterator_delete(it);
    fprintf(log_file,"\n\n");
}