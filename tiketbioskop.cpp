#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct TiketBioskop {
    string id_tiket;
    string nama_pemesan;
    string namafilm;
    string tanggal;
    string jam;
    string harga;
    string durasi;
    int jmltiket;
    int kursi;
    TiketBioskop* next;
};

TiketBioskop* head = nullptr;

void menu(int pilihan){
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
int main(){
    int pilihan;
    do {
        menu(pilihan);
        switch (pilihan) {
            // case 1: ; break;
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