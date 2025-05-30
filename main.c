#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "classe.h"
//#include "reservations.h"

int main() {
	SetConsoleOutputCP(CP_UTF8);
    int choix;
    do {	
        printf("Gestion des réservations de salles de la section informatique\n");
        printf("------------------------------------------------------------------\n");
        printf("1: Gestion des salles\n");
        printf("2: Gestion des classes\n");
        printf("3: Gestion des réservations \n");
        printf("4: Quitter\n");
        printf("Entrer votre choix: ");
        scanf("%d", &choix);
        printf("__________________________________________________________________\n");
        switch (choix) {
            case 1:
                //menu_Gestion_des_salles();
                break;
            case 2:
                menu_Gestion_des_classes();
                break;
            case 3:
               // menu_Gestion_des_reservations();
                break;
            case 4:
                printf("\nAu revoir!\n");
                break;
            default:
                printf("\nChoix invalide\n");
        } 
           printf("\nAppuyez sur Entrée pour continuer...\n");
           getchar(); getchar();
    } while (choix != 4);
    return 0;
}
