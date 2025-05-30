#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

typedef struct salle {
    int capacite;
    char  position[25], disponibilite_machines[5], code_unique[25];
}salle ;

// Fonction utilitaire pour vider le tampon
void vider_tempon(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// Retirer le saut de ligne
void retirer_le_saut_de_ligne(char * var_lu){
    var_lu[strcspn(var_lu, "\n")] = '\0';
}

// Vérifie si une chaîne est vide ou ne contient que des espaces
int chaine_vide_ou_espace(const char *str) {
    while (*str) {
        if (*str != ' ' && *str != '\t' && *str != '\n' && *str != '\r')
            return 0;
        str++;
    }
    return 1;
}

void effacer_ecran(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void attendreUtilisateur(){
    printf("\nAppuyez sur Entrée pour continuer...\n");
    getchar();
}

// Vérifie si le code existe déjà dans salle.txt
int est_ce_que_le_code_existe(const char* code){
    FILE * flux_fichier_salle;
    salle s;
    flux_fichier_salle = fopen("salle.txt", "r");
    if(flux_fichier_salle == NULL){
        return 2;
    }
    while (fscanf(flux_fichier_salle,"%[^\t]\t%[^\t]\t%d\t%[^\n]\n", s.code_unique, s.position, &s.capacite, s.disponibilite_machines) == 4){
        if(strcmp(code, s.code_unique) == 0){
            fclose(flux_fichier_salle);
            return 1;
        }
    }
    fclose(flux_fichier_salle);
    return 0;
}

void Ajouter_une_nouvelle_salle(){
    FILE * flux_fichier_salle;
    salle s;
    int dispo_machine;
    effacer_ecran();
    flux_fichier_salle = fopen("salle.txt", "a");
    if(flux_fichier_salle == NULL){
        printf("Echec de l'Ouverture du fichier !!\n");
        return;
    }
    printf("________________________________________________\n");
    printf("     === AJOUT D'UNE NOUVELLE SALLE ===\n");
    printf("------------------------------------------------\n");

    // Pour le code
    do {
        printf("Entrer le code : ");
        fgets(s.code_unique, sizeof(s.code_unique), stdin);
        retirer_le_saut_de_ligne(s.code_unique);
        if (chaine_vide_ou_espace(s.code_unique)) {
            printf("Le code ne doit pas être vide ou composé uniquement d'espaces !\n");
            continue;
        }
        if(est_ce_que_le_code_existe(s.code_unique) == 2){
            printf("Echec de l'Ouverture du fichier !!\n");
            continue;
        }
        if(est_ce_que_le_code_existe(s.code_unique) == 1){
            printf("Le code existe déjà !\n");
        }
    }while(est_ce_que_le_code_existe(s.code_unique) != 0 || chaine_vide_ou_espace(s.code_unique));

    // Pour la position
    do {
        printf("Position: ");
        fgets(s.position, sizeof(s.position), stdin);
        retirer_le_saut_de_ligne(s.position);
        if (chaine_vide_ou_espace(s.position)) {
            printf("La position ne doit pas être vide ou composée uniquement d'espaces !\n");
        }
    } while (chaine_vide_ou_espace(s.position));

    // Pour la capacité
    do{
        printf("Capacite : ");
        scanf("%d", &s.capacite);
        vider_tempon();
        if(s.capacite < 0){
            printf("La capacité ne peut pas être négative !!\n");
        }
    }while(s.capacite < 0);

    // Pour la disponibilité des machines
    do{
        printf("Disponibilite machines:\n1:Oui\n2:Non\n");
        printf("Entrer votre choix: ");
        scanf("%d", &dispo_machine);
        vider_tempon();
    }while(dispo_machine != 1 && dispo_machine != 2);

    if (dispo_machine == 1)
        strcpy(s.disponibilite_machines, "Oui");
    else
        strcpy(s.disponibilite_machines, "Non");

    fprintf(flux_fichier_salle,"%s\t%s\t%d\t%s\n", s.code_unique, s.position, s.capacite, s.disponibilite_machines);
    fclose(flux_fichier_salle);

    printf("Salle ajoutée avec succès ! \n");
    attendreUtilisateur();
}

void Afficher_la_liste_des_salles_connues(){
    FILE * flux_fichier_salle;
    salle s;
    int compteur = 0;
    effacer_ecran();
    flux_fichier_salle = fopen("salle.txt", "r");
    if(flux_fichier_salle == NULL){
        printf("Echec de l'Ouverture du fichier !!\n");
        return;
    }
    printf("_______________________________________________________________\n");
    printf("     === AFFICHAGE DE LA LISTE DES SALLES CONNUES ===\n");
    printf("---------------------------------------------------------------\n");
    while (fscanf(flux_fichier_salle,"%[^\t]\t%[^\t]\t%d\t%[^\n]\n", s.code_unique, s.position, &s.capacite, s.disponibilite_machines) == 4){
        compteur++;
        printf("=== SALLE ===\n");
        printf("Code                   : %s\n", s.code_unique);
        printf("Position               : %s\n", s.position);
        printf("Capacité               : %d\n", s.capacite);
        printf("Disponibilité machines : %s\n\n", s.disponibilite_machines);
    }
    if (compteur == 0) {
        printf("Aucune salle n'est connue pour le moment !!\n");
    }
    fclose(flux_fichier_salle);
    attendreUtilisateur();
}

void Rechercher_une_salle_a_partir_de_son_code(){
    FILE * flux_fichier_salle;
    salle s;
    char code[25];
    int trouve = 0;
    effacer_ecran();
    flux_fichier_salle = fopen("salle.txt", "r");
    if(flux_fichier_salle == NULL){
        printf("Echec de l'Ouverture du fichier !!\n");
        attendreUtilisateur();
        return;
    }
    printf("_______________________________________________________________\n");
    printf("     === RECHERCHE D'UNE SALLE A PARTIR DE SON CODE  ===\n");
    printf("---------------------------------------------------------------\n");
    printf("Donner le code de la salle à rechercher: ");
    fgets(code, sizeof(code), stdin);
    retirer_le_saut_de_ligne(code);

    while (fscanf(flux_fichier_salle,"%[^\t]\t%[^\t]\t%d\t%[^\n]\n", s.code_unique, s.position, &s.capacite, s.disponibilite_machines) == 4){
        if(strcmp(code, s.code_unique) == 0 ){
            printf("=== SALLE ===\n");
            printf("Code                   : %s\n", s.code_unique);
            printf("Position               : %s\n", s.position);
            printf("Capacité               : %d\n", s.capacite);
            printf("Disponibilité machines : %s\n\n", s.disponibilite_machines);
            trouve = 1;
            break;
        }
    }
    if(!trouve){
        printf("Salle non trouvée !! \n");
    }
    attendreUtilisateur();
    fclose(flux_fichier_salle);
}

void Modifier_une_salle_connue(){
    FILE * flux_fichier_salle, *fichierTmp;
    int dispo_machine, confirmation;
    char code[25];
    salle new_salle, salle_tmp;

    effacer_ecran();
    printf("________________________________________________\n");
    printf("     === MODIFICATION D'UNE SALLE ===\n");
    printf("------------------------------------------------\n");
    printf("Donner le code de la salle à modifier: ");
    fgets(code, sizeof(code), stdin);
    retirer_le_saut_de_ligne(code);

    if (est_ce_que_le_code_existe(code) == 1){
        // Saisir les nouvelles données
        strcpy(new_salle.code_unique, code);

        // Pour la position
        do {
            printf("Position: ");
            fgets(new_salle.position, sizeof(new_salle.position), stdin);
            retirer_le_saut_de_ligne(new_salle.position);
            if (chaine_vide_ou_espace(new_salle.position)) {
                printf("La position ne doit pas être vide ou composée uniquement d'espaces !\n");
            }
        } while (chaine_vide_ou_espace(new_salle.position));

        // Pour la capacité
        do{
            printf("Capacite : ");
            scanf("%d", &new_salle.capacite);
            vider_tempon();
            if(new_salle.capacite < 0){
                printf("La capacité ne peut pas être négative !!\n");
            }
        }while(new_salle.capacite < 0);

        // Pour la disponibilité des machines
        do{
            printf("Disponibilite machines:\n1:Oui\n2:Non\n");
            printf("Entrer votre choix: ");
            scanf("%d", &dispo_machine);
            vider_tempon();
        }while(dispo_machine != 1 && dispo_machine != 2);

        if (dispo_machine == 1)
            strcpy(new_salle.disponibilite_machines, "Oui");
        else
            strcpy(new_salle.disponibilite_machines, "Non");

        // Demande de confirmation dans une boucle
        do {
            printf("Confirmer la modification ?\n1: Oui\n2: Non\nVotre choix : ");
            scanf("%d", &confirmation);
            vider_tempon();
        } while (confirmation != 1 && confirmation != 2);

        if (confirmation != 1) {
            printf("Modification annulée.\n");
            attendreUtilisateur();
            return;
        }

        fichierTmp = fopen ("new_file.txt", "wt");
        if(fichierTmp == NULL){
            printf("Echec de l'ouverture du fichier temporaire !!\n");
            return;
        }

        flux_fichier_salle = fopen("salle.txt", "r");
        if(flux_fichier_salle == NULL){
            printf("Echec de l'Ouverture du fichier !!\n");
            fclose(fichierTmp);
            return;
        }

        while (fscanf(flux_fichier_salle,"%[^\t]\t%[^\t]\t%d\t%[^\n]\n", salle_tmp.code_unique, salle_tmp.position, &salle_tmp.capacite, salle_tmp.disponibilite_machines) == 4){
            if(strcmp(code, salle_tmp.code_unique) == 0){
                fprintf(fichierTmp,"%s\t%s\t%d\t%s\n", new_salle.code_unique, new_salle.position, new_salle.capacite, new_salle.disponibilite_machines);
            } else {
                fprintf(fichierTmp,"%s\t%s\t%d\t%s\n", salle_tmp.code_unique, salle_tmp.position, salle_tmp.capacite, salle_tmp.disponibilite_machines);
            }
        }
        fclose(flux_fichier_salle);
        fclose(fichierTmp);

        if (remove("salle.txt") != 0) {
            perror("Erreur de suppression");
            return;
        } else {
            printf("Salle modifiée avec succès !\n");
        }

        if (rename("new_file.txt", "salle.txt") != 0) {
            perror("Erreur de renommage");
        }
    } else {
        printf("La salle avec le code %s n'existe pas !\n", code);
    }
    attendreUtilisateur();
}

void Supprimer_une_salle_connue(){
    FILE * flux_fichier_salle, *fichierTmp;
    char code[25];
    int confirmation;
    salle s;

    effacer_ecran();
    printf("________________________________________________\n");
    printf("     === SUPPRESSION D'UNE SALLE ===\n");
    printf("------------------------------------------------\n");
    printf("Donner le code de la salle à supprimer: ");
    fgets(code, sizeof(code), stdin);
    retirer_le_saut_de_ligne(code);

    if (est_ce_que_le_code_existe(code) == 1){
        // Demande de confirmation dans une boucle
        do {
            printf("Confirmer la suppression ?\n1: Oui\n2: Non\nVotre choix : ");
            scanf("%d", &confirmation);
            vider_tempon();
        } while (confirmation != 1 && confirmation != 2);

        if (confirmation != 1) {
            printf("Suppression annulée.\n");
            attendreUtilisateur();
            return;
        }

        flux_fichier_salle = fopen("salle.txt", "r");
        if(flux_fichier_salle == NULL){
            printf("Echec de l'Ouverture du fichier !!\n");
            return;
        }

        fichierTmp = fopen ("new_file.txt", "wt");
        if(fichierTmp == NULL){
            printf("Echec de l'ouverture du fichier !!\n");
            fclose(flux_fichier_salle);
            return;
        }
        while (fscanf(flux_fichier_salle, "%[^\t]\t%[^\t]\t%d\t%[^\n]\n", s.code_unique, s.position, &s.capacite, s.disponibilite_machines) == 4){
            if(strcmp(s.code_unique, code) != 0){
                fprintf(fichierTmp,"%s\t%s\t%d\t%s\n", s.code_unique, s.position, s.capacite, s.disponibilite_machines);
            }
        }
        fclose(flux_fichier_salle);
        fclose(fichierTmp);

        if (remove("salle.txt") != 0) {
            perror("Erreur de suppression");
        } else {
            printf("Salle supprimée avec succès !\n");
        }

        if (rename("new_file.txt", "salle.txt") != 0) {
            perror("Erreur de renommage");
        }
    } else {
        printf("La salle avec le code %s n'existe pas !\n", code);
    }
    attendreUtilisateur();
}

void menu_Gestion_des_salles(){
    int choix;
    do {
        effacer_ecran();
        printf("1:Ajouter une nouvelle salle\n");
        printf("2:Afficher la liste des salles connues\n");
        printf("3:Rechercher une salle a partir de son code\n");
        printf("4:Modifier une salle connue\n");
        printf("5:Supprimer une salle connue\n");
        printf("6:Retour au menu principal\n");
        printf("Entrer votre choix: ");
        scanf("%d", &choix);
        vider_tempon();

        switch (choix) {
            case 1:
                Ajouter_une_nouvelle_salle();
                break;
            case 2:
                Afficher_la_liste_des_salles_connues();
                break;
            case 3:
                Rechercher_une_salle_a_partir_de_son_code();
                break;
            case 4:
                Modifier_une_salle_connue();
                break;
            case 5:
                Supprimer_une_salle_connue();
                break;
            case 6:
                break;
            default:
                printf("Choix invalide\a\n");
                attendreUtilisateur();
        }
    } while (choix != 6);
}