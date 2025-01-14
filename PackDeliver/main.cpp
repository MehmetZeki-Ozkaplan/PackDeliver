#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

// The package structure is defined, and the properties of the packages are specified
struct Paket {
    int id;  // Stores the package ID
    char teslimatNoktasi[50];  // Stores the delivery point in the teslimatNoktasi[] array
    int hacim;  // Stores the package volume in the hacim variable
    int bozulmaPuani;  // Stores the spoilage score in the bozulmaPuani variable
    int beklenenGun;  // Stores the expected delivery day in the beklenenGun variable
    int deger;  // Stores the calculated package value in the deger variable
};

// A list is created to store the packages
struct PaketListesi {
    Paket* paketler;  // Stores the array of packages in the paketler pointer
    int kapasite;  // Stores the maximum capacity of the list in the kapasite variable
    int sayi;  // Stores the current number of packages in the sayi variable
};

// Function declarations
bool dosyaOku(const char* dosyaAdi, char satirlar[][100], int& satirSayisi);  // Reads the file and stores its content
void paketDegeriHesapla(char satirlar[][100], int satirSayisi, PaketListesi& paketler);  // Calculates the package values
void paketYukle(const PaketListesi& paketler, PaketListesi& yuklenenPaketler, int aracKapasite);  // Loads the packages into the vehicle
void teslimatSonucunuYazdir(const PaketListesi& yuklenenPaketler);  // Prints the delivery results to the screen
int hesaplaTeslimSure(int mesafe, int sira);  // Calculates the delivery time
bool compareByDeger(const Paket& a, const Paket& b);  // Compares packages based on their values for sorting

int main() {
    // Packages and vehicle capacity are set
    PaketListesi paketler = { new Paket[100], 100, 0 };
    PaketListesi yuklenenPaketler = { new Paket[100], 100, 0 };
    const int aracKapasite = 150;  // The vehicle capacity is checked with aracKapasite variable
    char satirlar[100][100];  // The satirlar[] two-dimensional array is used to store the lines read from the file
    int satirSayisi = 0;

    // The file is read, and errors are checked
    if (!dosyaOku("YardimPaketleri.txt", satirlar, satirSayisi)) {
        cerr << "File read error!\n";
        delete[] paketler.paketler;
        delete[] yuklenenPaketler.paketler;
        return 1;
    }

    // Package values are calculated
    paketDegeriHesapla(satirlar, satirSayisi, paketler);

    // Packages are loaded into the vehicle
    paketYukle(paketler, yuklenenPaketler, aracKapasite);

    // Delivery results are printed to the screen
    teslimatSonucunuYazdir(yuklenenPaketler);

    // Dynamic memory is cleaned up
    delete[] paketler.paketler;
    delete[] yuklenenPaketler.paketler;

    return 0;
}

// The file is opened, and its content is read
bool dosyaOku(const char* dosyaAdi, char satirlar[][100], int& satirSayisi) {
    FILE* dosya = fopen(dosyaAdi, "r");
    if (!dosya) {
        cerr << dosyaAdi << " could not be opened!\n";
        return false;
    }

    satirSayisi = 0;
    while (fgets(satirlar[satirSayisi], 100, dosya)) {
        // Trailing spaces are removed from the line
        char* newline = strchr(satirlar[satirSayisi], '\n');
        if (newline) *newline = '\0';

        if (strlen(satirlar[satirSayisi]) > 0) {
            satirSayisi++;
        }
    }

    fclose(dosya);
    return true;
}

// Package values are calculated
void paketDegeriHesapla(char satirlar[][100], int satirSayisi, PaketListesi& paketler) {
    for (int i = 0; i < satirSayisi; ++i) {
        Paket paket;
        char tamSatir[100];
        strncpy(tamSatir, satirlar[i], sizeof(tamSatir) - 1);
        tamSatir[sizeof(tamSatir) - 1] = '\0';

        // Data is read and checked
        if (sscanf(tamSatir, "%*[^,],%49[^,],%d,%*d,%*d,%d,%d",
                   paket.teslimatNoktasi, &paket.hacim, &paket.bozulmaPuani, &paket.beklenenGun) < 4) {
            cerr << "Incomplete or incorrect data: " << satirlar[i] << "\n";
            continue;
        }

        // Package ID is obtained and value calculation is done
        string idStr = string(satirlar[i]).substr(2, string(satirlar[i]).find(',') - 2);
        paket.id = stoi(idStr);
        paket.deger = paket.bozulmaPuani + (paket.beklenenGun * 5);

        if (paketler.sayi < paketler.kapasite) {
            paketler.paketler[paketler.sayi++] = paket;
        }
    }
}

// Packages are loaded into the vehicle
void paketYukle(const PaketListesi& paketler, PaketListesi& yuklenenPaketler, int aracKapasite) {
    int mevcutHacim = 0;
    for (int i = 0; i < paketler.sayi; ++i) {
        if (mevcutHacim + paketler.paketler[i].hacim <= aracKapasite) {
            if (yuklenenPaketler.sayi < yuklenenPaketler.kapasite) {
                yuklenenPaketler.paketler[yuklenenPaketler.sayi++] = paketler.paketler[i];
                mevcutHacim += paketler.paketler[i].hacim;
            }
        }
    }

    // Loaded packages are sorted based on their values
    sort(yuklenenPaketler.paketler, yuklenenPaketler.paketler + yuklenenPaketler.sayi, compareByDeger);
}

// Packages are sorted by their values
bool compareByDeger(const Paket& a, const Paket& b) {
    return a.deger > b.deger;
}

// Delivery time is calculated
int hesaplaTeslimSure(int mesafe, int sira) {
    const int hiz = 60; // km/h
    int yolculukSuresi = ceil((double)mesafe / hiz * 60);  // Time is calculated in minutes
    int teslimatSuresi = yolculukSuresi + (sira * 23 / 17);  // Extra time is added
    return teslimatSuresi;
}

// Delivery results are printed to the screen
void teslimatSonucunuYazdir(const PaketListesi& yuklenenPaketler) {
    cout << "The delivery of the aid packages is complete.\n\n";
    cout << "Order\tPackageID\tDelivery Point\tPackage Value\tPackage Delivery Time\n";
    cout << "-------------------------------------------------------------\n";

    for (int i = 0; i < yuklenenPaketler.sayi; ++i) {
        int mesafe = (i + 1) * 10;  // The distance is determined
        int teslimSure = hesaplaTeslimSure(mesafe, i + 1);
        cout << (i + 1) << "\t"
             << "YP" << yuklenenPaketler.paketler[i].id << "\t"
             << yuklenenPaketler.paketler[i].teslimatNoktasi << "\t\t"
             << yuklenenPaketler.paketler[i].deger << "\t\t"
             << teslimSure << " min\n";
    }
}

