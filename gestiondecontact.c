#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"
#define WHT "\e[0;37m"
#define GRN "\e[0;32m"
#define CR "\e[0m"

#define MAX 100
#define MAX_NAME 50
#define MAX_NB 50
#define MAX_EMAIL 50

typedef struct {char nom[MAX_NAME];char num[MAX_NB];char email[MAX_EMAIL];int id;}contacts;

contacts contact[MAX];
int contactcount = 3;
int id = 4;

void menu(){ //menu

    printf(BMAG"\n\t\t***** MENU *****\n"CR);
    printf(BYEL"\t1. Ajouter un Contact\n");
    printf("\t2. Modifier un Contact\n");
    printf("\t3. Supprimer un Contact\n");
    printf("\t4. Afficher Tous les Contacts\n");
    printf("\t5. Rechercher un Contact\n"CR);
    printf(BRED"\t6. Quitter\n"CR);

}

void fgt(char *var, size_t se) {//fgets
    fgets(var, se, stdin);
    var[strcspn(var, "\n")] = 0; // Remove '\n'
}

int checkname(char *nom) { //check le nom
    for (int i = 0; nom[i] != '\0'; i++) {
        if (!isalpha(nom[i]) && !isspace(nom[i])) { //ila makanch name 7rf et espace kitl3 error
            printf(BRED"Erreur, Entrer un nom valide.\n"CR);
            return 0;}}
    return 1;
}

int checknum(char *num, int idx) { //check le numero
    for (int i = 0; i <= contactcount; i++) {
        if (i != idx && strcmp(contact[i].num, num) == 0) {
            printf(BRED"Erreur, ce numero existe deja\n"CR);
            return 0;
        }  
    }
        
    if (strlen(num) != 10 || strspn(num, "0123456789") != 10 ) {
        printf(BRED"Erreur, Entrez un numero de telephone valide\n"CR);
        return 0; // return false
    }

    if (strncmp(num, "06", 2) != 0 && strncmp(num, "07", 2) != 0) {
        printf(BRED "Erreur, le numero doit commencer par 06 ou 07\n" CR);
        return 0; // return false
    }

    return 1; // return true
}

int checkemail(char *email, int idx){//check le email
    for (int i = 0; i < contactcount; i++) {
        if (i != idx && strcmp(email, contact[i].email) == 0){
           printf(BRED"Erreur, ce Email existe deja\n"CR);
           return 0;}  
    }

    if (strncmp(email, "@", MAX_EMAIL) != 0 && strncmp(email, ".", MAX_EMAIL) != 0){
        printf(BRED"Erreur, Entrez un Email valide\n"CR);
        return 0;
    }
    return 1;
}

int getchoice() { //nakhdo choix correcte
    char input[50]; //bnsba fgets andiro conversion mn char int 1\n\0

    while (1) {
        printf(BYEL"\nEntrez un nombre (1-6): "CR);
        fgets(input, sizeof(input), stdin);

        //correction dyal kola caractere wach s7i7a
        if (strlen(input) == 2  && input[0] >= '1' && input[0] <= '6' && input[1] == '\n') {
            return input[0] - '0'; // conversion dyal caracter to int avec le valeur ascii
            //ascii dyal 0 hoa 48
        } else {
            printf(BRED"Erreur, entrez un nombre valide.\n"CR);
        }
    }
}

void add(){ //ajouter le contact
    if (contactcount >= MAX){ //si le carnet est plain knrj3o false
        printf(BRED"Le carnet est plein.\n"CR);
        return;}

    contacts new; //structer pour les new contacts

    do{
        printf(BYEL"Entrez le Nom de cette contact: "CR);
        fgt(new.nom,sizeof(new.nom));
    } while (!checkname(new.nom));
    
    do{
        printf(BYEL"Entrez le Numero de contact(10 chiffres): "CR);
        fgt(new.num,sizeof(new.num));
    } while (!checknum(new.num, contactcount));    

    do
    {
        printf(BYEL"Entrez le Email de contact: "CR);
        fgt(new.email,sizeof(new.email));
    } while (!checkemail(new.email, contactcount));

    new.id = id++; //kndiro id jdid

    contact[contactcount++] = new; //ajouter le new contact dans le structure de contacts
    printf(BGRN"Cet operation est succes!"CR);
}

void show() {//afficher les contacts
    if (contactcount == 0) {
        printf(BRED"Le carnet est vide.\n"CR);} 
    else {
        printf(BYEL"+--+--------------+-------------------+-----------------------+\n");
        printf(BYEL"%-4s%-12s%-20s%-50s\n","#  |","Nom           |","Telephone          |","Email                  |");
        printf(BYEL"+--+--------------+-------------------+-----------------------+\n");
        for (int i = 0; i < contactcount; i++) {
            printf(GRN"%-4d%-15s%-20s%-50s\n"WHT,contact[i].id, contact[i].nom,contact[i].num,contact[i].email);
        }
    }
}

void edit() { //modifier les contact
    char nom[MAX_NAME];
    do{
        printf(BYEL"EEntrez le nom du contact a modifier: "CR);
        fgt(nom,sizeof(nom));
    } while (!checkname(nom));

    for (int i = 0; i <= contactcount; i++) {
        if (strcmp(contact[i].nom, nom) == 0) {
            do{
                printf(BYEL"Entrez le nouveau numero: "CR);
                fgt(contact[i].num,sizeof(contact[i].num));
            } while (!checknum(contact[i].num, i));    

            do{
                printf(BYEL"Entrez le nouveau Email: "CR);
                fgt(contact[i].email,sizeof(contact[i].email));
            } while (!checkemail(contact[i].email, i)); 

            printf(BGRN"Contact modifie avec succes!\n"CR);
            return;
        }
    }
    printf(BRED"Le contact nexiste pas.\n"CR);
}

void search() {//recherce
    char search[MAX_NAME];
    do{
        printf(BYEL"Entrez le nom du contact a rechercher:: "CR);
        fgt(search,sizeof(search));
    } while (!checkname(search));

    for (int i = 0; i < contactcount; i++) {
        if (strcmp(contact[i].nom, search) == 0) {
            printf(BGRN"Contact existe:\n"CR);
            printf("Nom: %s\n", contact[i].nom);
            printf("Telephone: %s\n", contact[i].num);
            printf("Email: %s\n", contact[i].email);
            return;
        }
    }
    printf(BRED"Le contact nexiste pas.\n"CR);
}

void delete(){//supprimer
    char nom[MAX_NAME];
    do{
        printf(BYEL"Entrez le nom du contact a supprimer: "CR);
        fgt(nom,sizeof(nom));
    } while (!checkname(nom));

    for (int i = 0; i <= contactcount; i++) { //boucle pour recherche
        if (strcmp(contact[i].nom, nom) == 0) { //stecmp pour confirmation

            for (int j = i; j < contactcount - 1; j++) { // supression et iza7a 3la liser
                contact[j] = contact[j + 1];
            }
            contactcount--;
            printf(BRED"Contact supprime avec succes!\n"CR);
            return;
        }
    }
    printf(BRED"Le contact nexiste pas.\n"CR);

}

void def(){//default
    strcpy(contact[0].nom, "taha");
    strcpy(contact[0].num, "0682226573");
    strcpy(contact[0].email, "taha@gmail.com");
    contact[0].id = 1;
    strcpy(contact[1].nom, "jaiti");
    strcpy(contact[1].num, "0682426573");
    strcpy(contact[1].email, "tahaj@gmail.com");
    contact[1].id = 2;
    strcpy(contact[2].nom, "ka");
    strcpy(contact[2].num, "0654657643");
    strcpy(contact[2].email, "ka@gmail.com");
    contact[2].id = 3;
}

int main(){
    def();

    while (1) {
        menu();
        int choice = getchoice();
        switch (choice) {
            case 1:add();sleep(2);break;
            case 2:edit();sleep(2);break;
            case 3:delete();sleep(2);break;
            case 4:show();sleep(2);break;
            case 5:search();sleep(2);break;
            case 6:printf(BYEL"Passe une bonne journee!\n"CR); return 0;
            default:printf(BRED"Choix invalide.\n"CR);sleep(1);
        }
    }

    return 0;
}