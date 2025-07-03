#include <stdio.h>
#include <stdlib.h>

struct Okuma {
    char isim[100][100];
    char soyisim[100][100];
    unsigned long long numara[100];
};

int main(){

    FILE *fptr;
    int i=0;
    char satir[150];
    struct Okuma oku;

    fptr = fopen("rehber.txt", "r");
    if(fptr == NULL){
        printf("Dosya bulumadi.\n");
        return 1;
    }

    while(fgets(satir, sizeof(satir), fptr)){
        if(sscanf(satir, "Isim: %99[^,],", oku.isim[i])!=1)continue;

        if(!fgets(satir, sizeof(satir), fptr))break;
        if(sscanf(satir, " Soyisim: %99[^,],", oku.soyisim[i])!=1)continue;

        if(!fgets(satir, sizeof(satir), fptr))break;
        if(sscanf(satir, " Telefon Numarasi:%llu;", &oku.numara[i])!=1)continue;

        i++;


    }
    fclose(fptr);

      printf("\n--- REHBER ---\n");
    for(int j=0;j<i; j++){
        printf("Isim:  %s,\n", oku.isim[j]);
        printf("Soyisim: %s,\n", oku.soyisim[j]);
        printf("Telefon Numarasi: %llu;\n\n", oku.numara[j]);
    }


    return 0;
}