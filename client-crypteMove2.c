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

void move_n_first_char_to_end(char *str, int n){
    if (str == NULL)
        return;
    int len = strlen(str);
    if (len == 0)
        return;
    if (n >= len)
    return;
    char temp[len + 1];
    int i = n;
    while (i < len){
        temp[i - n] = str[i];
        i++;
    }
    while (i < len + n){
        temp[i - n] = str[i - len];
        i++;
    }
    temp[len] = '\0';
    strcpy(str, temp);
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
    envoyer("depart");
    char enc[MAXREP] = "";
    while (strlen(reponse)>0){
        
        //step 1 ///////
        

        char c= reponse[0];
        char temp[2];
        temp[0]=c;
        temp[1]='\0';
        strcat(enc,temp);

        //step 2 ////////////////


        remove_first_char(reponse);
        int x=c%8;
        move_n_first_char_to_end(reponse,x);
        }
    envoyer(enc);

    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}