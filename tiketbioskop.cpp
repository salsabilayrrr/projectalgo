#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;

struct TiketBioskop {
    char id_tiket[10];
    char namafilm[100];
    char tanggal[20];
    char jam[10];
    char harga[20];
    char durasi[20];
};

TiketBioskop* head = nullptr;

void opsilain() {
    cout << "========================================  " << endl;
    cout << "  Pilihan tidak Valid, silakan coba lagi  " << endl;
    cout << "========================================  " << endl;
}

void berhenti() {
    char pilihan;
    cout << "Apakah Anda Ingin Kembali ke Menu Awal? (y/n): ";
    cin >> pilihan;
    if (pilihan == 'y' || pilihan == 'Y'){
        system("cls");
    } else if (pilihan == 'n' || pilihan == 'N') {
        cout << "Program selesai.\n";
        exit(0);
    } else {
        opsilain();
        berhenti();
    }
}

void login(){
    string username,password;
    cout << setw(51) << setfill ('=' )<< endl;
    cout << "\n||" << setw(40) << setfill (' ') << "  Selamat Datang di Pemesanan Tiket Bioskop" << setw(3) << setfill (' ') << "||";
    cout << setw(70) << setfill ('=' )<< endl;

    cout << "\nMasukkan username  = "; cin >> username;
    cout << "Masukkan password  = "; cin >> password;
    cout << "\n----------Selamat Anda Berhasil Login------------\n";

}
void menu(int &pilihan){
        cout << "\n================= Menu =================\n";
        cout << "| 1. Tampilkan Daftar Film             |" << endl;
        cout << "| 2. Cari Film                         |"<< endl;
        cout << "| 3. Pesan Tiket                       |"<< endl;
        cout << "| 4. Tampilkan Invoice                 |" << endl;
        cout << "| 5. Batalkan Pemesanan                |"<< endl;
        cout << "| 6. Exit                              |"<< endl;
        cout << "========================================" << endl;
        cout << "Pilih Menu[1-6]: ";
        cin >> pilihan;
        cin.ignore();
}

void isiDataAwal() {
    FILE* file = fopen("DataFilm.dat", "wb"); // overwrite semua
    if (!file) {
        cout << "Gagal membuat file data.\n";
        return;
    }

    TiketBioskop data[] = {
        {"001", "Avengers", "2025-11-12", "17:00", "50000", "2 jam"},
        {"002", "Spider-Man", "2025-11-13", "19:00", "45000", "2.5 jam"},
        {"003", "Batman", "2025-11-14", "20:30", "55000", "2.5 jam"}
    };

    for (int i = 0; i < 3; i++) {
        fwrite(&data[i], sizeof(TiketBioskop), 1, file);
    }

    fclose(file);
}

void quickSort(TiketBioskop arr[], int low, int high) {
    if (low < high) {
        int pivot = low;
        int i = low, j = high;
        TiketBioskop temp;
        while (i < j) {
            while (arr[i].namafilm[0] <= arr[pivot].namafilm[0] && i < high) i++;
            while (arr[j].namafilm[0] > arr[pivot].namafilm[0]) j--;
            if (i < j) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        temp = arr[pivot];
        arr[pivot] = arr[j];
        arr[j] = temp;
        quickSort(arr, low, j - 1);
        quickSort(arr, j + 1, high);
    }
}

void tampilFilm() {
    FILE* file = fopen("DataFilm.dat", "rb");
    if (!file) {
        cout << "\nTidak ada data film yang tersedia.\n";
        return;
    }

    TiketBioskop film[100];
    int jmlfilm = 0;

    while (fread(&film[jmlfilm], sizeof(TiketBioskop), 1, file)){
        jmlfilm ++;
    }
    fclose(file);

    if (jmlfilm == 0) {
        cout << "---Tidak ada Film yang terdaftar---\n\n";
        return;
    }

    quickSort(film, 0, jmlfilm -1);

    cout << "\n========================================  " << endl;
    cout << "|            Daftar Film               |" << endl;
    cout << "========================================  " << endl;

    for (int i = 0; i < jmlfilm; i++) {
        cout << "ID Tiket     : " << film[i].id_tiket << endl;
        cout << "Film         : " << film[i].namafilm << endl;
        cout << "Tanggal      : " << film[i].tanggal << endl;
        cout << "Jam          : " << film[i].jam << endl;
        cout << "Harga        : " << film[i].harga << endl;
        cout << "Durasi       : " << film[i].durasi << endl;
        cout << "----------------------------------------" << endl;
    }

}

int main(){
    int pilihan;
    isiDataAwal();
    login();
    do {
        menu(pilihan);
        switch (pilihan) {
            case 1: tampilFilm(); break;
            // case 2: ; break;
            // case 3: ; break;
            // case 4: ; break;
            // case 5: ; break;
            case 6: 
                    cout << "\nTerima kasih telah menggunakan Layanan Kami! \n";
                    cout <<"Selamat Menonton!\n";
                    break;
            default: 
                    opsilain();
                    berhenti();
        }
        berhenti();
    } while (pilihan != 6);
    return 0;
}