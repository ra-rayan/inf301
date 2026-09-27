#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

void remove_first_char(char *str) {
    if (str==NULL||str[0]=='\0') {
        return;
    }
    memmove(str, str+1,strlen(str));
}
int find_char_index(char *str,char c){
    int i=0;
    while (str[i]!='\0'){
        if (str[i]==c) return i;
        i++;
    }
    return -1;
}
void move_nth_char_to_end(char *str, int n){
    if (str==NULL||n<0)
        return;
    int len=strlen(str);
    if (n>=len)
        return;
    char c=str[n];
    int i=n;
    while (i<len-1){
        str[i]=str[i+1];
        i++;
    }
    str[len-1]=c;
}
void crypteSeq(char *reponse){
    char seq[MAXREP]="";
    char enc[MAXREP]="";
    while (reponse[0] != '\0'){
        char c = reponse[0];
        int x=find_char_index(seq,c);
        if (x==-1){
            seq[strlen(seq)]=c;
            seq[strlen(seq)]='\0';
            enc[strlen(enc)]=c;
            enc[strlen(enc)]='\0';
        } else {
            if (x==0){
                char d =seq[strlen(seq)-1];
                enc[strlen(enc)]=d;
                enc[strlen(enc)]='\0';
                move_nth_char_to_end(seq,x);
            } else {
                char d=seq[x-1];
                enc[strlen(enc)]=d;
                enc[strlen(enc)]='\0';
                move_nth_char_to_end(seq,x);
            }
        }
        remove_first_char(reponse);
    }
    strcpy(reponse, enc);
}
void decrypteseq(char *message) {
    char seq[MAXREP]="";
    char dec[MAXREP]="";
    while (message[0]!='\0') {
        char d=message[0];
        int pos=find_char_index(seq,d);
        char c;
        if (pos==-1) {
            c=d;
            seq[strlen(seq)]=c;
            seq[strlen(seq)]='\0';
        } else {
            int x=(pos+1)%strlen(seq);
            c=seq[x];
            move_nth_char_to_end(seq, x);
        }
        dec[strlen(dec)]=c;
        dec[strlen(dec)]='\0';
        remove_first_char(message);
    }
    strcpy(message, dec);
}
void crypteAssoc(char *reponse){
    char seq[MAXREP] = "";
    char assoc[256];
    char enc[MAXREP] = "";
    while (reponse[0]!='\0'){
        char c = reponse[0];
        int x = find_char_index(seq,c);
        if (x==-1){
            seq[strlen(seq)]=c;
            seq[strlen(seq)]='\0';
            assoc[(unsigned char)c] = c;
        } else {
            char p;
        if (x == 0) {
                p = seq[strlen(seq)-1];
            } else {
                p = seq[x-1];
            }
            char tmp = assoc[(unsigned char)c];
            assoc[(unsigned char)c] = assoc[(unsigned char)p];
            assoc[(unsigned char)p] = tmp;
            move_nth_char_to_end(seq,x);
        }
        enc[strlen(enc)] = assoc[(unsigned char)c];
        enc[strlen(enc)] = '\0';
        remove_first_char(reponse);
    }
    strcpy(reponse,enc);
}
char find_assoc_key(char *seq, char *assoc, char o){
    for (int i = 0; seq[i] != '\0'; i++){
        if (assoc[(unsigned char)seq[i]] == o) return seq[i];
    }
    return '\0';
}

void decrypteAssoc(char *message){
    char seq[MAXREP] = "";
    char assoc[256];
    char dec[MAXREP] = "";
    while (message[0] != '\0'){
        char o = message[0];
        int inSeq = (find_char_index(seq, o) != -1);
        char c;
        if (!inSeq){
            c = o;
            seq[strlen(seq)] = c;
            seq[strlen(seq)] = '\0';
            assoc[(unsigned char)c] = c;
        } else {
            char p = find_assoc_key(seq, assoc, o);
            int p_pos = find_char_index(seq, p);
            int x = (p_pos + 1) % strlen(seq);
            c = seq[x];
            char tmp = assoc[(unsigned char)c];
            assoc[(unsigned char)c] = assoc[(unsigned char)p];
            assoc[(unsigned char)p] = tmp;
            move_nth_char_to_end(seq, x);
        }
        dec[strlen(dec)] = c;
        dec[strlen(dec)] = '\0';
        remove_first_char(message);
    }
    strcpy(message, dec);
}

int main(){
    char reponse[MAXREP];
    show_messages(true);
    connexion("im2ag-appolab.u-ga.fr");
    envoyer("login 12518371 RAHMANI");
    envoyer("load LostCause");
    envoyer_recevoir("help", reponse);
    decrypteseq(reponse);
    printf("Reponse du serveur : %s\n", reponse);
    envoyer_recevoir("depart", reponse);
    decrypteAssoc(reponse);
    printf("Reponse du serveur : %s\n", reponse);
    envoyer("tout va bien");
    printf ("Fin d'envoi des messages.\n");
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}