#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100
#define MAX_NAME 50
#define MAX_NB 11
#define MAX_EMAIL 50

typedef struct {char nom[MAX_NAME];char num[MAX_NB];char email[MAX_EMAIL];}contacts;

contacts contact[MAX];
int contactcount = 0;

int getchoice(){
    int choice;
    char input[7];

    while (1) {
        printf("Entrer une nombre (1-6): ");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &choice) == 1 && choice >= 1 && choice <= 6) {
            return choice;
        }
        printf("Erreur: Entrer un nombre valide entre 1 et 6.\n");
    }

}


void menu(){
    printf("\n\t***** MENU *****\n");
    printf("1. Ajouter un Contact\n");
    printf("2. Modifier un Contact\n");
    printf("3. Supprimer un Contact\n");
    printf("4. Afficher Tous les Contacts\n");
    printf("5. Rechercher un Contact\n");
    printf("6.Quitter\n");
    printf("Entrer un nombre: ");

}



int main(){

    while (1) {
        menu();
        int choice = getchoice();
        switch (choice) {
            case 1: ; break;
            
        }
    }

    return 0;
}