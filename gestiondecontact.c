#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100
#define MAX_NAME 50
#define MAX_NB 19
#define MAX_EMAIL 50

typedef struct {char nom[MAX_NAME];char num[MAX_NB];char email[MAX_EMAIL];}contacts;

contacts contact[MAX];
int contactcount = 0;

void menu(){ //menu

    printf("\n\t***** MENU *****\n");
    printf("1. Ajouter un Contact\n");
    printf("2. Modifier un Contact\n");
    printf("3. Supprimer un Contact\n");
    printf("4. Afficher Tous les Contacts\n");
    printf("5. Rechercher un Contact\n");
    printf("6.Quitter\n");

}

int checkname(char *nom) { //check le nom
    for (int i = 0; nom[i] != '\0'; i++) {
        if (!isalpha(nom[i]) && !isspace(nom[i])) { //ila makanch name 7rf et espace kitl3 error
            printf("Erreur, Entrer un nombre valide.\n");
            return 0;}}
    return 1;
}

int checknum(char *num) { //check le numero
    if (strlen(num) != 10 || strspn(num, "0123456789") != 10) {
        printf("Erreur, Entrez un numéro de téléphone valide\n");
        return 0; // return false
    }

    return 1; // return true
}

int getchoice() { //nakhdo choix correcte
    char input[50]; //bsba fgets andiro conversion mn char int

    while (1) {
        printf("\nEntrez un nombre (1-6): ");
        fgets(input, sizeof(input), stdin);

        //correction dyal kola caractere wach s7i7a
        if (strlen(input) == 2  && input[0] >= '1' && input[0] <= '6' && input[1] == '\n') {
            return input[0] - '0'; // conversion dyal caracter to int avec le valeur ascii
            //ascii dyal 0 hoa 48
        } else {
            printf("Erreur, entrez un nombre valide.\n");
        }
    }
}

void add(){ //ajouter le contact
    if (contactcount >= MAX){ //si le carnet est plain knrj3o false
        printf("Le carnet est plein.\n");
        return;}

    contacts new; //structer pour les new contacts

    do{
        printf("Entrez le Nom de cette contact: ");
        fgets(new.nom, sizeof(new.nom), stdin);
        new.nom[strcspn(new.nom, "\n")] = 0; //remove \n
    } while (!checkname(new.nom));
    
    do{
        printf("Entrez le Numero de contact: ");
        fgets(new.num, sizeof(new.num), stdin);
        new.num[strcspn(new.num, "\n")] = 0;
    } while (!checknum(new.num));    

    printf("Entrez le Email de contact: ");
    fgets(new.email, sizeof(new.email), stdin);
    new.email[strcspn(new.email, "\n")] = 0;

    contact[contactcount++] = new; //ajouter le new contact dans le structure de contacts
    printf("Cet operation est succes!");
}

void show() {//afficher les contacts
    if (contactcount == 0) {
        printf("Le carnet est vide.\n");} 
    else {
        for (int i = 0; i < contactcount; i++) {
            printf("\nContact %d:\n", i + 1);
            printf("Nom: %s\n", contact[i].nom);
            printf("Telephone: %s\n", contact[i].num);
            printf("Email: %s\n", contact[i].email);}
        }
}

void edit() { //modifier les contact
    char nom[MAX_NAME];
    do{
        printf("EEntrez le nom du contact a modifier: ");
        fgets(nom, sizeof(nom), stdin);
        nom[strcspn(nom, "\n")] = 0; //remove \n
    } while (!checkname(nom));

    for (int i = 0; i < contactcount; i++) {
        if (strcmp(contact[i].nom, nom) == 0) {
            do{
                printf("Entrez le nouveau numero: ");
                fgets(contact[i].num, sizeof(contact[i].num), stdin);
                contact[i].num[strcspn(contact[i].num, "\n")] = 0;
            } while (!checknum(contact[i].num));    

            printf("Entrez le nouvel email: ");
            fgets(contact[i].email, sizeof(contact[i].email), stdin);
            contact[i].email[strcspn(contact[i].email, "\n")] = 0;

            printf("Contact modifie avec succes!\n");
            return;
        }
    }
    printf("Le contact nexiste pas.\n");
}

void search() {//recherce
    char search[MAX_NAME];
    do{
        printf("Entrez le nom du contact a rechercher:: ");
        fgets(search, sizeof(search), stdin);
        search[strcspn(search, "\n")] = 0; //remove \n
    } while (!checkname(search));

    for (int i = 0; i < contactcount; i++) {
        if (strcmp(contact[i].nom, search) == 0) {
            printf("Contact existe:\n");
            printf("Nom: %s\n", contact[i].nom);
            printf("Telephone: %s\n", contact[i].num);
            printf("Email: %s\n", contact[i].email);
            return;
        }
    }
    printf("Le contact nexiste pas.\n");
}

void delete(){//supprimer
    char nom[MAX_NAME];
    do{
        printf("Entrez le nom du contact a supprimer: ");
        fgets(nom, sizeof(nom), stdin);
        nom[strcspn(nom, "\n")] = 0; //remove \n
    } while (!checkname(nom));

    for (int i = 0; i < contactcount; i++) { //boucle pour recherche
        if (strcmp(contact[i].nom, nom) == 0) { //stecmp pour confirmation
            for (int j = i; j < contactcount - 1; j++) { // supression et iza7a 3la liser
                contact[j] = contact[j + 1];
            }
            contactcount--;
            printf("Contact supprime avec succes!\n");
            return;
        }
    }
    printf("Le contact nexiste pas.\n");

}

int main(){

    while (1) {
        menu();
        int choice = getchoice();
        switch (choice) {
            case 1:add();break;
            case 2:edit();break;
            case 3:delete();break;
            case 4:show();break;
            case 5:search();break;
            case 6: printf("Passe une bonne journée!\n"); return 0;
            default: printf("Choix invalide.\n");
        }
    }

    return 0;
}