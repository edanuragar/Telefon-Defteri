#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *dosya = fopen("rehber.txt", "r");
    FILE *gecici = fopen("temp.txt", "w");
    char satir[150];
    char silinecek[100];
    int atla = 0;

    if (!dosya || !gecici) {
        printf("Dosya açılamadı.\n");
        return 1;
    }

    printf("Silinecek ismi girin: ");
    scanf("%s", silinecek);

    while (fgets(satir, sizeof(satir), dosya)) { //Isim bir kişinin ilk kaydının başladığı yer ve Isimde silmek için başlangıçtan
        if (strncmp(satir, "Isim:", 5) == 0) { // strncmp eşit olup olmadığını kontrol eder verilen karakter sayısı kadar
            char isim[100];
            sscanf(satir, "Isim: %99[^,],", isim); // Isimden sonra gelen gerçek ismi alır.
            if (strcmp(isim, silinecek) == 0) { // bu isim silinmek istenenle eşleşiyorsa
                atla = 2; // diğer 2 satırı da atla
                continue; // simdiki satir yazılmasın diğerine gec demek yani yazma bu satırları demek
            }
        }

        if (atla > 0) { // eğer atla = 2 olduysa silinecek satırın 2. ya da 3. satırındasın demek
            atla--; // atla = 0 olana kadar eksilt yani bu satırları da es geç soyisim ve telefon numrası
            continue; // ve onları atlayarak devam et
        }

        fputs(satir, gecici); // eğer yukarıdaki hiçbir continue çalışmadıysa bu satır silinmeyecek demek. Geçici dosyaya yaz
    }

    fclose(dosya);
    fclose(gecici);

    remove("rehber.txt");
    rename("temp.txt", "rehber.txt");

    printf("Silme işlemi tamamlandı.\n");
    return 0;
}
