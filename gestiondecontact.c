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
int checkname(char *nom) {
    for (int i = 0; nom[i] != '\0'; i++) {
        if (!isalpha(nom[i]) && !isspace(nom[i])) {
            printf("Erreur, Entrer un nombre valide.\n");
            return 0;}}
    return 1;
}
int checknum(char *num) {
    return strlen(num) == 10 && 
    (strncmp(num, "05", 2) == 0 ||
    strncmp(num, "06", 2) == 0 ||
    strncmp(num, "07", 2) == 0) &&
    strspn(num, "0123456789") == 10;
}

int getchoice(){
    int choice;
    char input[10];

    while (1) {
        printf("Entrer une nombre (1-6): ");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &choice) == 1) {
            if (input[0] != '\n' && (input[1] == '\n' || input[1] == '\0')) {
                if (choice >= 1 && choice <= 6) {
                    return choice;}
            }
        }
        printf("Erreur, Entrer un nombre (1-6).\n");}
}
void add(){
    if (contactcount >= MAX){
        printf("Le carnet est plein.\n");
        return;}

    contacts new;

    do{
        printf("Entrez le Nom de cette contact: ");
        fgets(new.nom, sizeof(new.nom), stdin);
        new.nom[strcspn(new.nom, "\n")] = 0;
    } while (!checkname(new.nom));
    
    do{
        printf("Entrez le Numero de contact: ");
        fgets(new.num, sizeof(new.num), stdin);
        new.num[strcspn(new.num, "\n")] = 0;
    } while (!checknum(new.num));
    
    

    printf("Entrez le Email de contact: ");
    fgets(new.email, sizeof(new.email), stdin);
    new.email[strcspn(new.email, "\n")] = 0;

    contact[contactcount++] = new;
    printf("Cet operation est succes!");
}





int main(){

    while (1) {
        menu();
        int choice = getchoice();
        switch (choice) {
            case 1:add(); break;
            
        }
    }

    return 0;
}