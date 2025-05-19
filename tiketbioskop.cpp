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

struct Kursi {
    string nomor;
    bool terisi;
    Kursi* next;
};

struct Pesanan {
    TiketBioskop data;
    string no_kursi;
    Pesanan* next;
};

TiketBioskop* head = nullptr;
Kursi* headKursi = nullptr;
Pesanan* headPesanan = nullptr;

void opsilain() {
    cout << "========================================  " << endl;
    cout << " Pilihan tidak valid, silakan coba lagi  " << endl;
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
        {"003", "Batman", "2025-11-14", "20:30", "55000", "2.5 jam"},
        {"004", "Transformers", "2025-11-15", "21:45", "60000", "2.5 jam"},
        {"005", "Jumbo", "2025-11-16", "18:45", "65000", "2.3 jam"}
    };

    for (int i = 0; i < 5; i++) {
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

int binarySearch(TiketBioskop arr[], int left, int right, const char namafilm[]) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = 0, i = 0;
        while (arr[mid].namafilm[i] != '\0' && namafilm[i] != '\0' && arr[mid].namafilm[i] == namafilm[i]) {
            i++;
        }
        cmp = arr[mid].namafilm[i] - namafilm[i];
        
        if (cmp == 0) return mid;
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void cariFilm(){
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
        cout << "---Tidak ada Film yang dicari---\n\n";
        return;
    }

    quickSort(film, 0, jmlfilm -1);

    char filmCari[100];
    cout << "\nMasukkan Judul Film yang dicari: ";
    cin.getline(filmCari,100);

    int i = binarySearch(film, 0, jmlfilm - 1, filmCari);

    if (i != -1) {
        // Menampilkan data Film jika ditemukan
        cout << "\n========================================  " << endl;
        cout << "|    Pencarian Berdasarkan Judul Film   |" << endl;
        cout << "========================================  " << endl;
        cout << "\n----------- FILM Ditemukan -----------\n";
        cout << "ID Tiket     : " << film[i].id_tiket << endl;
        cout << "Film         : " << film[i].namafilm << endl;
        cout << "Tanggal      : " << film[i].tanggal << endl;
        cout << "Jam          : " << film[i].jam << endl;
        cout << "Harga        : " << film[i].harga << endl;
        cout << "Durasi       : " << film[i].durasi << endl;
        cout << "----------------------------------------" << endl;
    } else {
        cout << "Film dengan judul " << filmCari << " tidak ditemukan!\n";
    }
}

void posisiKursi() {
    char baris[] = {'A', 'B', 'C'};
    int kolom = 5;

    for (int i = 0; i < 3; i++) {
        for (int j = 1; j <= kolom; j++) {
            Kursi* baru = new Kursi;
            baru->nomor = string(1, baris[i]) + to_string(j);            
            baru->terisi = false;
            baru->next = nullptr;

            if (headKursi == nullptr) {
                headKursi = baru;
            } else {
                Kursi* temp = headKursi;
                while (temp->next != nullptr) temp = temp->next;
                temp->next = baru;
            }
        }
    }
}

void tampilkanKursi() {
    cout << "\nDaftar Kursi: \n";
    Kursi* temp = headKursi;
    int count = 0;
    while (temp != nullptr) {
        if (temp->terisi) {
            cout << "[XX] ";
        } else {
            cout << "[" << temp->nomor << "] ";
        }
        count++;
        if (count % 5 == 0) cout << endl;
        temp = temp->next;
    }
}

string pilihKursi() {
    string input;
    tampilkanKursi();
    cout << "\nPilih nomor kursi yang ingin dipesan: ";
    cin >> input;

    Kursi* temp = headKursi;
    while (temp != nullptr) {
        if (temp->nomor == input) {
            if (!temp->terisi) {
                temp->terisi = true;
                cout << "Kursi " << input << " berhasil dipesan.\n";
                return input;
            } else {
                cout << "Kursi sudah terisi, pilih yang lain!\n";
                return pilihKursi();
            }
        }
        temp = temp->next;
    }

    cout << "Nomor kursi tidak valid!\n";
    return pilihKursi();
}

void tambahPesanan(TiketBioskop tiket) {
    Pesanan* baru = new Pesanan;
    baru->data = tiket;
    baru->no_kursi = pilihKursi();
    baru->next = nullptr;

    if (headPesanan == nullptr) {
        headPesanan = baru;
    } else {
        Pesanan* temp = headPesanan;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = baru;
    }
    cout << "\nTiket berhasil dipesan!\n";
}

void pesanTiket() {
    FILE* file = fopen("DataFilm.dat", "rb");
    if (!file) {
        cout << "Tidak ada data film yang tersedia.\n";
        return;
    }

    TiketBioskop film[100];
    int jmlfilm = 0;

    while (fread(&film[jmlfilm], sizeof(TiketBioskop), 1, file)) jmlfilm++;
    fclose(file);

    cout << "\nDaftar Film:\n";
    for (int i = 0; i < jmlfilm; i++) {
        cout << i + 1 << ". " << film[i].namafilm << endl;
    }

    int pilih;
    cout << "Pilih film (1-" << jmlfilm << "): ";
    cin >> pilih;
    if (pilih >= 1 && pilih <= jmlfilm) {
        tambahPesanan(film[pilih - 1]);
    } else {
        cout << "Pilihan tidak valid.\n";
    }
}

void tampilkanInvoice() {
    if (headPesanan == nullptr) {
        cout << "\nBelum ada pesanan yang dilakukan.\n";
        return;
    }

    Pesanan* temp = headPesanan;  // Mulai dari pesanan pertama
    int nomorPesanan = 1;         // Untuk memberi nomor pada invoice

    cout << "\n=========== INVOICE PESANAN ===========\n";
    while (temp != nullptr) {
        cout << "Pesanan #" << nomorPesanan++ << endl;
        cout << "----------------------------------------\n";
        cout << "ID Tiket     : " << temp->data.id_tiket << endl;
        cout << "Judul Film   : " << temp->data.namafilm << endl;
        cout << "Tanggal      : " << temp->data.tanggal << endl;
        cout << "Jam Tayang   : " << temp->data.jam << endl;
        cout << "Harga Tiket  : Rp " << temp->data.harga << endl;
        cout << "Durasi Film  : " << temp->data.durasi << endl;
        cout << "No Kursi     : " << temp->no_kursi << endl;
        cout << "----------------------------------------\n\n";

        // Lanjut ke pesanan berikutnya
        temp = temp->next;
    }
}

void batalPesan(){
    if (headPesanan == nullptr) {
        cout << "\nBelum ada pesanan untuk dibatalkan.\n";
        return;
    }

    string id, kursi;
    cout << "\nMasukkan ID Tiket yang ingin dibatalkan: ";
    cin >> id;
    cout << "Masukkan No Kursi yang ingin dibatalkan: ";
    cin >> kursi;

    Pesanan* temp = headPesanan;
    Pesanan* bantu = nullptr;

    while (temp != nullptr) {
        if (temp->data.id_tiket == id && temp->no_kursi == kursi) {
            // Bebaskan kursi
            Kursi* k = headKursi;
            while (k != nullptr) {
                if (k->nomor == kursi) {
                    k->terisi = false;
                    break;
                }
                k = k->next;
            }

            // Hapus node pesanan
            if (bantu == nullptr) {
                headPesanan = temp->next;
            } else {
                bantu->next = temp->next;
            }
            delete temp;
            cout << "Pesanan berhasil dibatalkan!\n";
            return;
        }
        bantu = temp;
        temp = temp->next;
    }
    cout << "Pesanan tidak ditemukan. Pastikan ID Tiket dan No Kursi benar.\n";
}

int main(){
    system("cls");
    int pilihan;
    isiDataAwal();
    posisiKursi();
    login();
    do {
        menu(pilihan);
        system("cls");
        switch (pilihan) {
            case 1: tampilFilm(); break;
            case 2: cariFilm(); break;
            case 3: pesanTiket(); break;
            case 4: tampilkanInvoice(); break;
            case 5: batalPesan(); break;
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