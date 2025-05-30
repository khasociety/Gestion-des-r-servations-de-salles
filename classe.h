#include <stdio.h>
#include <string.h>
//#include <stdlib.h>
#include <windows.h>

typedef struct {
    char nom[25];
	char niveau[25];
	char code_unique[25];
    int effectif;
}classe;
//fonction pour vider le tempon
void vider_tempon(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
	
}
 // retirer le saut de ligne
 void  retirer_le_saut_de_ligne(char * var_lu){
 	 var_lu[strcspn(var_lu, "\n")] = '\0';
 }

//Gestion des classe

void effacer_ecran(){
	#ifdef _WIN32
	        system("cls");
	    #else
	        system("clear");
	    #endif  //pour la portablite du programme
}

int est_ce_que_la_classe_existe(char* code){
   FILE * flux_fichier_classe;
   classe c;
   flux_fichier_classe = fopen ("classe.txt", "r");
   if(flux_fichier_classe == NULL){
      // printf("Echec de l'Ouverture du fichier !!\n");
      return 2;
   }
   while ( fscanf(flux_fichier_classe,"%[^\t]\t%[^\t]\t%d\t%[^\n]\n", c.code_unique, c.nom, &c.effectif, c.niveau) == 4)
   {
     if(strcmp(code, c.code_unique) == 0 ){
        return 1;
     }
   }
   fclose(flux_fichier_classe);
   return 0;
}
void attendreUtilisateur(){
	printf("\nAppuyez sur Entrée pour continuer...\n");
	getchar(); // pour attendre l'utilisateur
}

int chaine_vide_ou_espace(const char *str) {
    while (*str) {
        if (*str != ' ' && *str != '\t' && *str != '\n' && *str != '\r')
            return 0; // Il y a un caractère non espace
        str++;
    }
    return 1; // Que des espaces ou vide
}

void Ajouter_une_nouvelle_classe(){
    FILE * flux_fichier_classe;
    classe c;
    effacer_ecran(); // Ajout ici
    flux_fichier_classe = fopen("classe.txt", "a");
    if(flux_fichier_classe == NULL){
        printf("Echec de l'Ouverture du fichier !!\n");
        return;
    }
    printf("________________________________________________\n");
    printf("     === AJOUT D'UNE NOUVELLE CLASSE ===\n");    
    printf("------------------------------------------------\n");

    // Pour le code
    do {
        printf("Entrer le code de la classe : ");
        fgets(c.code_unique, sizeof(c.code_unique), stdin);
        retirer_le_saut_de_ligne(c.code_unique);
        if (chaine_vide_ou_espace(c.code_unique)) {
            printf("Le code ne doit pas être vide ou composé uniquement d'espaces !\n");
            continue;
        }
        if(est_ce_que_la_classe_existe(c.code_unique) == 2){
            printf("Echec de l'Ouverture du fichier !!\n");
            continue;
        }
        if(est_ce_que_la_classe_existe(c.code_unique) == 1){
            printf("La classe avec le code %s existe deja !!\n", c.code_unique);
        }
    }while(est_ce_que_la_classe_existe(c.code_unique) != 0 || chaine_vide_ou_espace(c.code_unique));

    // Pour le nom
    do {
        printf("Nom: ");
        fgets(c.nom, sizeof(c.nom), stdin);
        retirer_le_saut_de_ligne(c.nom);
        if (chaine_vide_ou_espace(c.nom)) {
            printf("Le nom ne doit pas être vide ou composé uniquement d'espaces !\n");
        }
    } while (chaine_vide_ou_espace(c.nom));

	 do{
        printf("Effectif : ");
        scanf("%d", &c.effectif);
        vider_tempon(); // vider le tampon pour eviter les problemes de saisie
        if(c.effectif < 0){
            printf("L'effectif ne peut pas etre negatif !!\n");
        }
    }while( c.effectif < 0);

    // Pour le niveau
    do {
        printf("Niveau : ");
        fgets(c.niveau, sizeof(c.niveau), stdin);
        retirer_le_saut_de_ligne(c.niveau);
        if (chaine_vide_ou_espace(c.niveau)) {
            printf("Le niveau ne doit pas être vide ou composé uniquement d'espaces !\n");
        }
    } while (chaine_vide_ou_espace(c.niveau));
	// Ecriture dans le fichier
    fprintf(flux_fichier_classe,"%s\t%s\t%d\t%s\n", c.code_unique, c.nom, c.effectif, c.niveau);
    fclose(flux_fichier_classe);
    
    printf("Classe ajoutée avec succès ! \n");
    attendreUtilisateur();
}

void Afficher_la_liste_des_classes_connues() {
    FILE * flux_fichier_classe;
    classe c;
	int compteur = 0;
    effacer_ecran(); // Ajout ici
    flux_fichier_classe = fopen("classe.txt", "r");
    if(flux_fichier_classe == NULL){
        printf("Echec de l'Ouverture du fichier !!\n");
        return;
    }
    printf("_______________________________________________________________\n");
    printf("     === AFFICHAGE DE LA LISTES DES CLASSES CONNUES ===\n");    
    printf("---------------------------------------------------------------\n");
    while (fscanf(flux_fichier_classe,"%[^\t]\t%[^\t]\t%d\t%[^\n]\n", c.code_unique, c.nom, &c.effectif , c.niveau )== 4){
			compteur++;
			if (compteur = 0){
				printf("Aucune classe n'est connue pour le moment !!\n");
			    fclose(flux_fichier_classe);
			    attendreUtilisateur();
			    return;
		}
		else{
			    printf("=== CLASSE ===\n");
				printf("Code     : %s\n", c.code_unique);
				printf("Nom      : %s\n", c.nom);
				printf("Effectif : %d\n", c.effectif);
				printf("Niveau   : %s\n", c.niveau);
	    }
   }
    fclose(flux_fichier_classe);
	attendreUtilisateur();
}


void Rechercher_une_classe_a_partir_de_son_code() {
    FILE * flux_fichier_classe;
    classe c;
    char code[25];
    int trouve = 0;
    effacer_ecran(); 
    flux_fichier_classe = fopen("classe.txt", "r");
    if(flux_fichier_classe == NULL){
        printf("Echec de l'Ouverture du fichier !!\n");
        attendreUtilisateur();
        return;
    }
    printf("_______________________________________________________________\n");
    printf("     === RECHERCHE D'UNE CLASSE A PARTIR DE SON CODE  ===\n");    
    printf("---------------------------------------------------------------\n");

    printf("Entrer le code de la classe a rechercher: ");
    fgets(code, sizeof(code), stdin);
    retirer_le_saut_de_ligne(code);

    while (fscanf(flux_fichier_classe,"%[^\t]\t%[^\t]\t%d\t%[^\n]\n", c.code_unique, c.nom, &c.effectif , c.niveau )== 4){
        if(strcmp(code, c.code_unique) == 0 ){
            printf("=== CLASSE ===\n");
            printf("Code     : %s\n", c.code_unique);
            printf("Nom      : %s\n", c.nom);
			printf("Effectif : %d\n", c.effectif); 
            printf("Niveau   : %s\n", c.niveau);
            trouve = 1;
            break;
        }
    }
    if(!trouve){
        printf("classe non trouvee !! \n");
    }
    attendreUtilisateur();
    fclose(flux_fichier_classe);
}

void Modifier_une_classe_connue() {
    FILE * flux_fichier_classe , *fichierTmp;
    char code[25];
    int confirmation;
    classe c, ctemp;

    effacer_ecran();
    printf("________________________________________________\n");
    printf("     === MODIFICATION D'UNE CLASSE ===\n");    
    printf("------------------------------------------------\n");
    printf("Donner le code de la classe a modifier: ");
    fgets(code, sizeof(code), stdin);
    retirer_le_saut_de_ligne(code);

    if (est_ce_que_la_classe_existe(code) == 1){
        strcpy(ctemp.code_unique, code);

        // Pour le nom
        do {
            printf("Nom: ");
            fgets(ctemp.nom, sizeof(ctemp.nom), stdin);
            retirer_le_saut_de_ligne(ctemp.nom);
            if (chaine_vide_ou_espace(ctemp.nom)) {
                printf("Le nom ne doit pas être vide ou composé uniquement d'espaces !\n");
            }
        } while (chaine_vide_ou_espace(ctemp.nom));

        // Pour l'effectif
        do{
            printf("Effectif : ");
            scanf("%d", &ctemp.effectif);
            vider_tempon();
            if(ctemp.effectif < 0){
                printf("L'effectif ne peut pas etre negatif !!\n");
            }
        }while( ctemp.effectif < 0);

        // Pour le niveau
        do {
            printf("Niveau : ");
            fgets(ctemp.niveau, sizeof(ctemp.niveau), stdin);
            retirer_le_saut_de_ligne(ctemp.niveau);
            if (chaine_vide_ou_espace(ctemp.niveau)) {
                printf("Le niveau ne doit pas être vide ou composé uniquement d'espaces !\n");
            }
        } while (chaine_vide_ou_espace(ctemp.niveau));

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
        flux_fichier_classe = fopen("classe.txt", "r");
        if(flux_fichier_classe == NULL|| fichierTmp == NULL){
            printf("Echec de l'Ouverture du fichier !!\n");
            attendreUtilisateur();
            return;
        }

        while (fscanf(flux_fichier_classe,"%[^\t]\t%[^\t]\t%d\t%[^\n]\n", c.code_unique, c.nom, &c.effectif , c.niveau )== 4){
            if(strcmp(code, c.code_unique) != 0){
                fprintf(fichierTmp,"%s\t%s\t%d\t%s\n", c.code_unique, c.nom, c.effectif, c.niveau);
            }
            else {
                fprintf(fichierTmp,"%s\t%s\t%d\t%s\n", ctemp.code_unique, ctemp.nom, ctemp.effectif, ctemp.niveau);
            }
        }
        fclose(flux_fichier_classe);
        fclose(fichierTmp);
        _fcloseall();

        if (remove("classe.txt") != 0) {
            perror("Erreur de suppression");
        }
        else printf("Classe modifiée avec succès !\n");

        if (rename("new_file.txt", "classe.txt") != 0) {
            perror("Erreur de renommage");
        }
    }
    else{
        printf("La classe avec le code %s n'existe pas !\n", code);
    }

    attendreUtilisateur();
}

void Supprimer_une_classe_connue() {
    FILE * flux_fichier_classe , *fichierTmp;
    char code[25];
    int confirmation;
    classe c;

    effacer_ecran();
    printf("________________________________________________\n");
    printf("     === SUPPRESSION D'UNE CLASSE ===\n");    
    printf("------------------------------------------------\n");
    printf("Donner le code de la classe a supprimer: ");
    fgets(code, sizeof(code), stdin);
    retirer_le_saut_de_ligne(code);

    if (est_ce_que_la_classe_existe(code) == 1){
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

        flux_fichier_classe = fopen("classe.txt", "r");
        fichierTmp = fopen ("new_file.txt", "wt");
        if(fichierTmp == NULL|| flux_fichier_classe == NULL){
            effacer_ecran();
            printf("Echec de l'ouverture du fichier !!\n");
            attendreUtilisateur();
            return;
        }

        while (fscanf(flux_fichier_classe,"%[^\t]\t%[^\t]\t%d\t%[^\n]\n", c.code_unique, c.nom, &c.effectif , c.niveau )== 4){
            if(strcmp(c.code_unique, code) != 0 ){
                fprintf(fichierTmp, "%s\t%s\t%d\t%s\n", c.code_unique, c.nom, c.effectif,c.niveau );
            }
        }
        fclose(flux_fichier_classe);
        fclose(fichierTmp);
        _fcloseall();

        if (remove("classe.txt") != 0) {
            perror("Erreur de suppression");
        }
        else printf("Classe supprimee avec succès !\n");

        if (rename("new_file.txt", "classe.txt") != 0) {
            perror("Erreur de renommage");
        }
    }
    else{
        printf("La classe avec le code %s n'existe pas !\n", code);
    }

    attendreUtilisateur();
}

void menu_Gestion_des_classes(){
    int choix;  
    do {    
        effacer_ecran(); 
        printf("1:Ajouter une nouvelle classe\n");
        printf("2:Afficher la liste des classes connues\n");
        printf("3:Rechercher une classe a partir de son code\n");
        printf("4:Modifier une classe connue\n");
        printf("5:Supprimer une classe connue\n");
        printf("0:Retour au menu principal\n");
        printf("Entrer votre choix: ");
        scanf("%d", &choix);
		getchar(); // pour vider le tampon d'entrée

        switch (choix) {
            case 1:
                Ajouter_une_nouvelle_classe();
                break;
            case 2:
                Afficher_la_liste_des_classes_connues();
                break;
            case 3:
                Rechercher_une_classe_a_partir_de_son_code();
                break;
            case 4:
                Modifier_une_classe_connue();
                break;	
            case 5:
                Supprimer_une_classe_connue();
                break;
            case 0:
                break;
            default:
                printf("Choix invalide\a");
        }
    } while (choix != 0);
}
