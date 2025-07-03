#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Kisi{
  char ad[100];
  char soyad[100];
  unsigned long long telefon;

};

int main(){

  FILE *fptr;
  struct Kisi kisi;
  fptr = fopen("rehber.txt", "a+");

   printf("Isim, soyisim, telefon numarasi girin:\n");
   gets(kisi.ad);
   gets(kisi.soyad);
   scanf("%llu", &kisi.telefon);
   fprintf(fptr, "Isim: %s,\n Soyisim: %s,\n Telefon Numarasi:%llu;\n", kisi.ad, kisi.soyad, kisi.telefon);

  fclose(fptr);
  return 0;

}