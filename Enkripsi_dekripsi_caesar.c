#include <stdio.h>
#include <string.h>

// Fungsi untuk membaca isi file dan menyimpannya dalam array konten
void baca(const char *namaFile, char *konten) {
    FILE *fileInput;
    fileInput = fopen(namaFile, "r"); // Membuka file untuk dibaca
    int i = 0;

    if (fileInput == NULL) {
        printf("Gagal membuka file\n");
        return;
    }

    char character;
    while ((character = fgetc(fileInput)) != EOF) {
        konten[i++] = character;
    }
    konten[i] = '\0'; // Menambahkan null terminator
    fclose(fileInput); // Menutup file
}

// Fungsi untuk enkripsi karakter dengan Caesar cipher
char enkripsi(char teks, int kunci) {
    int ASCII = (int)teks;
    int en = (ASCII + kunci) % 256;
    return (char)en;
    } // Menggunakan modulo 256 untuk menjaga dalam rentang ASCII


// Fungsi untuk dekripsi karakter dengan Caesar cipher
char dekripsi(char teks, int kunci) {
    int ASCII = (int)teks;
    int de = (ASCII - kunci) % 256; // Menggunakan modulo 256 untuk menjaga dalam rentang ASCII
    return (char)de;
}

// Fungsi untuk menulis konten ke dalam file
void tulis(const char *namaFile, char *konten) {
    FILE *fileOutput;
    fileOutput = fopen(namaFile, "w"); // Membuka file untuk ditulis
    if (fileOutput == NULL) {
        printf("Gagal membuka file output\n");
        return;
    }

    fputs(konten, fileOutput); // Menulis konten ke dalam file
    fclose(fileOutput); // Menutup file
}

int main() {
    char teksFile[4000];
    int pilihan;
    char namaFile[100];
    char fileEnkripsi[100];
    char fileDekripsi[100];
    char kunci[100];
    int key;

    printf("Pilih enkripsi atau dekripsi (1/2): "); // Meminta pengguna memilih antara enkripsi atau dekripsi
    scanf("%d", &pilihan);
    getchar(); // Menghilangkan newline, agar karakter dapat terbaca

    switch (pilihan) {
        case 1: // Kasus pertama, enkripsi
            printf("Masukkan nama dokumen yang ingin anda enkripsi: "); // Dokumen harus berupa file .txt
            scanf("%s", namaFile); // File harus berada di dalam direktori yang sama dengan program ini
            printf("Masukkan kunci: "); // Kunci untuk Caesar cipher, kunci ini bisa berupa string 
            scanf("%s", kunci);
            printf("Input nama file baru (tambahkan .txt): ");
            scanf("%s", fileEnkripsi);

            key = 0;
            for (int i = 0; kunci[i] != '\0'; i++) {
                key += kunci[i];
                printf("%d ", key);
            }     

            key = key % 256;

            baca(namaFile, teksFile); // Membaca isi file
            for (int i = 0; i < strlen(teksFile); i++) {
                teksFile[i] = enkripsi(teksFile[i], key); // Enkripsi setiap karakter
            }
            tulis(fileEnkripsi, teksFile); // Menulis hasil enkripsi ke file baru
            printf("Enkripsi berhasil\n %d", key);
            break;

        case 2: // Kasus kedua, dekripsi
            printf("Masukkan nama dokumen yang ingin anda dekripsi: ");
            scanf("%s", namaFile);
            printf("Masukkan kunci: ");
            scanf("%s", kunci);
            printf("Nama file dekripsi (tambahkan .txt): ");
            scanf("%s", fileDekripsi);

            key = 0;
            for (int i = 0; kunci[i] != '\0'; i++) {
                key += kunci[i];
            }

            key = key % 256;

            baca(namaFile, teksFile); // Membaca isi file

            for (int i = 0; i < strlen(teksFile); i++) {
                teksFile[i] = dekripsi(teksFile[i], key); // Dekripsi setiap karakter
            }

            tulis(fileDekripsi, teksFile); // Menulis hasil dekripsi ke file baru
            printf("Dekripsi berhasil\n %d", key);
            break;

        default:
            printf("Pilihan salah\n");
            break;
    }
    return 0;
}
