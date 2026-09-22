#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
void move_last_n_char_to_first(char *str,int n){
    if (n<0 || n>strlen(str)) return;
    int i=strlen(str)-n;
    int j=0;
    char temp[MAXREP];
    while (i<strlen(str)){
        temp[j]=str[i];
        j++;
        i++;
    }
    i=0;
    while (j<strlen(str)){
        temp[j]=str[i];
        j++;
        i++;
    }
    temp[j]='\0';
    strcpy(str,temp);
}
void add_first_char_to_beginning(char *str,char c){
    int len=strlen(str);
    for (int i=len;i>0;i--){
        str[i]=str[i-1];
    }
    str[0]=c;
    str[len+1]='\0';
}
void decrypter(char *reponse){
    int len = strlen(reponse);
    int i = 0;
    while (reponse[i]!='\0'){ {
        char c = reponse[i];
        int x=c%8;
        move_last_n_char_to_first(reponse,x);
        add_first_char_to_beginning(reponse,c);
        i++;
    }
}
int main() {

    // Affiche les échanges avec le serveur (false pour désactiver)
    show_messages(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr");
    char reponse[MAXREP];

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer("login 12518371 RAHMANI");
    envoyer("load BayOfPigs");
    envoyer_recevoir("depart", reponse);

    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}
