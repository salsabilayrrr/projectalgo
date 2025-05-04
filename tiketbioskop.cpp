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


void tampilFilm(){
    FILE *file = fopen("DataFilm.txt", "rb");
    if (!file) {
        cout << "\nTidak ada data film yang tersedia.\n";
        return;
    }

    TiketBioskop film;

    // Membaca data film dari file dan menambahkannya ke dalam linked list
    while (fread(&film, sizeof(TiketBioskop), 1, file)){
        // Membuat node baru untuk linked list
        TiketBioskop* newNode = new TiketBioskop();
        //Menggunakan Struck untuk membaca data (DataFilm) dalam film
        newNode->id_tiket = film.id_tiket;
        newNode->nama_pemesan = film.nama_pemesan;
        newNode->namafilm = film.namafilm;
        newNode->tanggal = film.tanggal;
        newNode->jam = film.jam;
        newNode->harga = film.harga;
        newNode->durasi = film.durasi;
        newNode->jmltiket = film.jmltiket;
        newNode->kursi = film.kursi;

        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;  // Jika linked list kosong, node pertama menjadi head
        } else {
            TiketBioskop* bantu = head;
            while (bantu->next != nullptr) {
                bantu = bantu->next;
            }
            bantu->next = newNode;  
        }
    }

    fclose(file);

    // Menampilkan daftar film
    if (head == nullptr) {
        cout << "\nTidak ada data film yang tersedia.\n";
        return;
    }

    cout << "\n========================================  " << endl;
    cout << "|            Daftar Film               |" << endl;
    cout << "========================================  " << endl;

    TiketBioskop* bantu = head;         
    while (bantu != nullptr) {
        cout << "ID Tiket     : " << bantu->id_tiket << endl;
        cout << "Nama Pemesan : " << bantu->nama_pemesan << endl;
        cout << "Film         : " << bantu->namafilm << endl;
        cout << "Tanggal      : " << bantu->tanggal << endl;
        cout << "Jam          : " << bantu->jam << endl;
        cout << "Harga        : " << bantu->harga << endl;
        cout << "Durasi       : " << bantu->durasi << endl;
        cout << "Jumlah Tiket : " << bantu->jmltiket << endl;
        cout << "No Kursi     : " << bantu->kursi << endl;
        cout << "------------------------------------" << endl;
        bantu = bantu->next;
    }
}

int main(){
    int pilihan;
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