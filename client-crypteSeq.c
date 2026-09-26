#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
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
void crypte(char *reponse){
    char enc[MAXREP] = ""; 
    while (strlen(reponse)>0){
        char c= reponse[0];
        char temp[2];
        temp[0]=c;
        temp[1]='\0';
        strcat(enc,temp);
        remove_first_char(reponse);
        int x=c%8;
        move_n_first_char_to_end(reponse,x);
        }
    strcpy(reponse,enc);
    }
void move_last_n_char_to_first(char *str,int n){
    if (n<0 || (unsigned long)n>strlen(str)) return;
    unsigned long i=strlen(str)-n;
    unsigned long j=0;
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
void add_char_to_beginning(char *str,char c){
    int len=strlen(str);
    for (int i=len;i>0;i--){
        str[i]=str[i-1];
    }
    str[0]=c;
    str[len+1]='\0';
}
void decrypter(char *enc){
    int i = strlen(enc)-1;
    char rep[MAXREP];
    rep[0]='\0';
    while (i>=0){ 
        char c = enc[i];
        int x=c%8;
        move_last_n_char_to_first(rep,x);
        add_first_char_to_beginning(rep,c);
        enc[i]='\0';
        i--;
    }
    strcpy(enc,rep);
}
int index(char *str, char c){
    int i=0;
    while (str[i]!='\0'){
        if (str[i]==c) return i;
        i++;
    }
    return -1;
}
void crypteSeq(char *reponse){
    char seq[MAXREP] = "";
   while (reponse[0]!='\0'){
        char c = reponse[0];
        int x = index(seq,c);
        if (x==-1){
            

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
    envoyer_recevoir("load crypteSeq", reponse);
    decrypter(reponse);
    envoyer_recevoir("depart", reponse);
    decrypter(reponse);


    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}
