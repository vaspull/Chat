#include <iostream>
#include <ctype.h>

void shifr (char *res, char *key)
{
    int reslen = 0, keylen = 0, keydigit = 0, trashlen = 0, itoglen = 0;
    char trash[5000]="", itog[5000]="";
    while(res[reslen]) reslen++;
    for(int i = 0; i <= (reslen*2); i++){
        trash[i] = rand() % 127;
        if(isalnum(trash[i]) == 0) {
            trash[i] = 63;
        }
        i++;
        trash[i] = rand() % 127;
        if(isalnum(trash[i]) == 0) {
            trash[i] = 63;
        }
    }
    trashlen = 0;
    while(trash[trashlen]) trashlen++;
    for(int i = 0, a = 0, j = 0; a < reslen; ){
        itog[i++] = trash[j++];
        itog[i++] = trash[j++];
        itog[i++] = res[a++];
    }
    while(itog[itoglen]) itoglen++;
    for(int i = 0; i < reslen; i++) res[i] = 0;
    for(int i = 0; i < itoglen; i++) res[i] = itog[i];
    while(key[keylen]) keylen++;
    reslen = 0;
    while(res[reslen]) reslen++;
    keydigit = reslen % 4;
    for (int i = 0; i < reslen;){
        for (int a = 0; a < keylen;a++){
            if(i<reslen){
                res[i] = res[i]+key[a]+keydigit;
                i++;
            }
            else{
                break;
            }
        }
    }
}

void deshifr (char *res, char *key)
{
    int reslen = 0, keylen = 0, keydigit = 0, itoglen = 0;
    char itog[5000]="";
    while(res[reslen]) reslen++;
    keydigit = reslen % 4;
    while(key[keylen]) keylen++;
    for (int i = 0; i < reslen;){
        for (int a = 0; a < keylen;a++){
            if(i<reslen){
                res[i] = res[i]-key[a]-keydigit;
                i++;
            }
            else{
                break;
            }
        }
    }
    for(int i = 0, a = 2; i < reslen; i++){
        itog[i] = res[a];
        a += 3;
    }
    while(itog[itoglen]) itoglen++;
    for(int i = 0; i < reslen; i++) res[i] = 0;
    for(int i = 0; i < itoglen; i++) res[i] = itog[i];
}
