#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Kisi {
    char ad[100];
    char soyad[100];
    unsigned long long telefon;
};

struct Okuma {
    char isim[100][100];
    char soyisim[100][100];
    unsigned long long numara[100];
};

int main() {
    struct Kisi kisi;
    struct Okuma oku;
    char islem[100];
    char satir[150];
    char silinecek[100];

    while (1) {
        printf("Islem secin: ekle, sil, listele, exit\n");
        scanf("%s", islem);

        if (strcmp(islem, "exit") == 0) {
            printf("Programdan cikiliyor.\n");
            break;
        }

        // === EKLEME ===
        if (strcmp(islem, "ekle") == 0) {
            FILE *fptr = fopen("rehber.txt", "a");
            if (!fptr) {
                printf("Dosya acilamadi.\n");
                continue;
            }

            int c;
            while ((c = getchar()) != '\n' && c != EOF); // buffer temizle

            printf("Isim, soyisim, telefon numarasi girin:\n");
            fgets(kisi.ad, sizeof(kisi.ad), stdin);
            fgets(kisi.soyad, sizeof(kisi.soyad), stdin);

            kisi.ad[strcspn(kisi.ad, "\n")] = '\0';
            kisi.soyad[strcspn(kisi.soyad, "\n")] = '\0';

            scanf("%llu", &kisi.telefon);

            fprintf(fptr, "Isim: %s,\n Soyisim: %s,\n Telefon Numarasi:%llu;\n",
                    kisi.ad, kisi.soyad, kisi.telefon);

            fclose(fptr);
        }

        // === LİSTELEME ===
        else if (strcmp(islem, "listele") == 0) {
            FILE *fptr = fopen("rehber.txt", "r");
            if (!fptr) {
                printf("Dosya bulunamadi.\n");
                continue;
            }

            int i = 0; // burada sıfırlanmalı

            while (fgets(satir, sizeof(satir), fptr)) {
                if (sscanf(satir, "Isim: %99[^,],", oku.isim[i]) != 1) continue;

                if (!fgets(satir, sizeof(satir), fptr)) break;
                if (sscanf(satir, " Soyisim: %99[^,],", oku.soyisim[i]) != 1) continue;

                if (!fgets(satir, sizeof(satir), fptr)) break;
                if (sscanf(satir, " Telefon Numarasi:%llu;", &oku.numara[i]) != 1) continue;

                i++;
            }

            fclose(fptr);

            printf("Listeleme:\n");
            for (int j = 0; j < i; j++) {
                printf("Isim: %s\n", oku.isim[j]);
                printf("Soyisim: %s\n", oku.soyisim[j]);
                printf("Telefon Numarasi: %llu\n\n", oku.numara[j]);
            }
        }

        // === SİLME ===
        else if (strcmp(islem, "sil") == 0) {
            FILE *fptr = fopen("rehber.txt", "r");
            FILE *temp = fopen("temp.txt", "w");

            if (!fptr || !temp) {
                printf("Dosyalar acilamadi.\n");
                if (fptr) fclose(fptr);
                if (temp) fclose(temp);
                continue;
            }

            printf("Silinecek ismi girin: ");
            scanf("%s", silinecek);

            int atla = 0;

            while (fgets(satir, sizeof(satir), fptr)) {
                if (strncmp(satir, "Isim: ", 6) == 0) {
                    char isim[150];
                    sscanf(satir, "Isim: %99[^,],", isim);
                    if (strcmp(isim, silinecek) == 0) {
                        atla = 2;
                        continue;
                    }
                }

                if (atla > 0) {
                    atla--;
                    continue;
                }

                fputs(satir, temp);
            }

            fclose(fptr);
            fclose(temp);

            remove("rehber.txt");
            rename("temp.txt", "rehber.txt");

            printf("Silme islemi tamamlandi.\n");
        }

        else {
            printf("Gecersiz islem. Lutfen tekrar deneyin.\n");
        }
    }

    return 0;
}
