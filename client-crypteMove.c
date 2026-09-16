#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void remove_first_char(char *str) {
    if (str == NULL || str[0] == '\0') {
        return;
    }

    memmove(str, str + 1, strlen(str));
}

void move_n_first_char_to_end(char *str, int n) {
    size_t len;
    if (str == NULL || str[0] == '\0' || n <= 0) {
        return;
    }
    len = strlen(str);
    n=n%len;
    char new[n+1];
    memmove(new, str, n);
    for (int i=0;i<n;i++){
    remove_first_char(str);}
    strcat(str,new);
}



int main(){
    // Affiche les échanges avec le serveur (false pour désactiver)
    show_messages(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr");
    char reponse[MAXREP];
    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer("login 12518371 RAHMANI");
    envoyer("load crypteMove");
    envoyer_recevoir("help",reponse);
    char enc[MAXREP] = "";
    while (strlen(reponse)>0){
        
        //step 1 ///////
        

        char c= reponse[0];
        char temp[2];
        temp[0]=c;
        temp[1]='\0';
        strcat(enc,temp);

        //step 2 //////////////////////


        remove_first_char(reponse);
        printf("Message après suppression du premier caractère : %s\n",reponse);
        int x=c%8;
        move_n_first_char_to_end(reponse,x);
        printf("Message après transformation : %s\n",reponse);
        }
    envoyer(enc);

    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}
