#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;

struct TiketBioskop {
    char id_tiket[10];
    char namafilm[100];
    char tanggal[10];
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

void tampilFilm() {
    FILE* file = fopen("DataFilm.dat", "rb");
    if (!file) {
        cout << "\nTidak ada data film yang tersedia.\n";
        return;
    }

    TiketBioskop film;

    cout << "\n========================================  " << endl;
    cout << "|            Daftar Film               |" << endl;
    cout << "========================================  " << endl;

    while (fread(&film, sizeof(TiketBioskop), 1, file)) {
        cout << "ID Tiket     : " << film.id_tiket << endl;
        cout << "Film         : " << film.namafilm << endl;
        cout << "Tanggal      : " << film.tanggal << endl;
        cout << "Jam          : " << film.jam << endl;
        cout << "Harga        : " << film.harga << endl;
        cout << "Durasi       : " << film.durasi << endl;
        cout << "----------------------------------------" << endl;
    }
    fclose(file);
}

int main(){
    int pilihan;
    do {
        login();
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