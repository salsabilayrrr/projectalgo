#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;

struct User {
    char username[50];
    char password[50];
};

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

struct Film {
    string judul;
    Kursi* headKursi; // setiap film punya kursinya sendiri
    Film* next;
};

struct DataPesananFile {
    TiketBioskop data;
    char no_kursi[10]; // cukup buat kursi seperti "A1", "C5"
};

string usernameAktif;
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

void simpanUserKeFile() {
    User newUser;
    cout << "============== Membuat Akun ==============\n";
    cout << "\nMasukkan username : ";
    cin >> newUser.username;
    cout << "Masukkan password : ";
    cin >> newUser.password;

    FILE* file = fopen("DataUser.dat", "ab"); // append binary
    if (!file) {
        cout << "Gagal membuka file.\n";
        return;
    }

    fwrite(&newUser, sizeof(User), 1, file);
    fclose(file);

    cout << "\n====== Selamat! Berhasil Membuat Akun======\n";
}

void menu(int &pilihanMenu){
        cout << "\n================= Menu =================\n";
        cout << "| 1. Tampilkan Daftar Film             |" << endl;
        cout << "| 2. Cari Film                         |"<< endl;
        cout << "| 3. Pesan Tiket                       |"<< endl;
        cout << "| 4. Tampilkan Invoice                 |" << endl;
        cout << "| 5. Batalkan Pemesanan                |"<< endl;
        cout << "| 6. Exit                              |"<< endl;
        cout << "========================================" << endl;
        cout << "Pilih Menu[1-6]: ";
        cin >> pilihanMenu;
        cin.ignore();
}
bool login() {
    string uname, pass;

    cout << "\n================ Login ================\n";
    cout << "\nMasukkan username : ";
    cin >> uname;
    cout << "Masukkan password : ";
    cin >> pass;

    FILE* file = fopen("DataUser.dat", "rb");
    if (!file) {
        cout << "File data belum ada.\n";
        return false;
    }

    User userData;
    bool ditemukan = false;

    while (fread(&userData, sizeof(User), 1, file)) {
        string fileUser(userData.username);
        string filePass(userData.password);

        if (uname == fileUser && pass == filePass) {
            ditemukan = true;
            usernameAktif = fileUser;
            break;
        }
    }

    fclose(file);
    
    if (ditemukan) {
        cout << "\nLogin berhasil.\n" << "Selamat datang, " << uname << "!\n";
        return true;
    } else {
        cout << "Login gagal. Username atau password salah.\n";
    }
    return false;
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

    berhenti();
    system("cls");
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

    berhenti();
    system("cls");
}

void posisiKursi(Film* film){
    // char baris[] = {'A', 'B', 'C'};
    // int kolom = 5;

    // for (int i = 0; i < 3; i++) {
    //     for (int j = 1; j <= kolom; j++) {
    //         Kursi* baru = new Kursi;
    //         baru->nomor = string(1, baris[i]) + to_string(j);            
    //         baru->terisi = false;
    //         baru->next = nullptr;

    //         if (headKursi == nullptr) {
    //             headKursi = baru;
    //         } else {
    //             Kursi* temp = headKursi;
    //             while (temp->next != nullptr) temp = temp->next;
    //             temp->next = baru;
    //         }
    //     }
    // }
    char baris[] = {'A', 'B', 'C'};
    int kolom = 5;

    film->headKursi = nullptr; // inisialisasi head kursi untuk film ini

    for (int i = 0; i < 3; i++) {
        for (int j = 1; j <= kolom; j++) {
            Kursi* baru = new Kursi;
            baru->nomor = string(1, baris[i]) + to_string(j);            
            baru->terisi = false;
            baru->next = nullptr;

            if (film->headKursi == nullptr) {
                film->headKursi = baru;
            } else {
                Kursi* temp = film->headKursi;
                while (temp->next != nullptr) temp = temp->next;
                temp->next = baru;
            }
        }
    }
}

void tampilkanKursi(Film* film) {
    // cout << "\nDaftar Kursi: \n";
    // Kursi* temp = headKursi;
    // int count = 0;
    // while (temp != nullptr) {
    //     if (temp->terisi) {
    //         cout << "[XX] ";
    //     } else {
    //         cout << "[" << temp->nomor << "] ";
    //     }
    //     count++;
    //     if (count % 5 == 0) cout << endl;
    //     temp = temp->next;
    // }
    cout << "\nDaftar Kursi untuk film " << film->judul << ":\n";
    Kursi* temp = film->headKursi;
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

string pilihKursi(Film* film) {
    string input;
    tampilkanKursi(film);
    cout << "\nPilih nomor kursi yang ingin dipesan: ";
    cin >> input;

    Kursi* temp = film->headKursi;
    while (temp != nullptr) {
        if (temp->nomor == input) {
            if (!temp->terisi) {
                temp->terisi = true;
                cout << "Kursi " << input << " berhasil dipesan.\n";
                return input;
            } else {
                cout << "Kursi sudah terisi, pilih yang lain!\n";
                return pilihKursi(film);
            }
        }
        temp = temp->next;
    }

    cout << "Nomor kursi tidak valid!\n";
    return pilihKursi(film);
}

void tambahPesanan(TiketBioskop tiket, Film* film) {
    if (usernameAktif.empty()) {
        cout << "Anda harus login dulu sebelum pesan tiket.\n";
        return;
    }    
    
    int jml;
    cout << "Berapa tiket yang ingin dipesan? ";
    cin >> jml;

    string namaFile = "pesanan_" + usernameAktif + ".dat";

    FILE* file = fopen("DataPesanan.dat", "ab");
    if (!file) {
        cout << "Gagal membuka file.\n";
        return;
    }

    for (int i = 0; i < jml; i++){
        string kursi = pilihKursi(film);
        DataPesananFile dp;
        dp.data = tiket;
        strcpy(dp.no_kursi, kursi.c_str());  // perbaikan penyalinan kursi

        fwrite(&dp, sizeof(DataPesananFile), 1, file);
        Pesanan* baru = new Pesanan;
        baru->data = tiket;
        baru->no_kursi = kursi;
        baru->next = nullptr;

        if (headPesanan == nullptr) {
            headPesanan = baru;
        } else {
            Pesanan* temp = headPesanan;
            while (temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = baru;
    }
    fclose(file);
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

    berhenti();
    system("cls");
}

void tampilkanInvoice() {
    if (usernameAktif.empty()) {
        cout << "Anda belum login.\n";
        return;
    }

    if (headPesanan == nullptr) {
        // Load dari file pesanan_[username].dat
        string namaFile = "pesanan_" + usernameAktif + ".dat";
        FILE* file = fopen(namaFile.c_str(), "rb");
            if (!file) {
                cout << "Belum ada pesanan yang dilakukan.\n";
                return;
            }

        DataPesananFile dp;
        while (fread(&dp, sizeof(DataPesananFile), 1, file)) {
            Pesanan* node = new Pesanan;
            node->data = dp.data;
            node->no_kursi = dp.no_kursi;
            node->next = nullptr;

            if (headPesanan == nullptr) {
                headPesanan = node;
            } else {
                Pesanan* temp = headPesanan;
                while (temp->next != nullptr)
                    temp = temp->next;
                temp->next = node;
            }
        }
        fclose(file);
    }

    if (headPesanan == nullptr) {
        cout << "\nBelum ada pesanan yang dilakukan.\n";
        return;
    }

    Pesanan* temp = headPesanan;
    int nomorPesanan = 1;

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

        temp = temp->next;
    }

    berhenti();
    system("cls");
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
            if (temp->data.id_tiket == id && temp->no_kursi == kursi) {
            if (bantu == nullptr) {
                headPesanan = temp->next;
            } else {
                bantu->next = temp->next;
            }

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

    berhenti();
    system("cls");
}

void menulogin(){
    int pil;
    bool berhasilLogin = false;
    do {
        cout << "\n================= Menu =================\n";
        cout << "| 1. Registrasi                        |" << endl;
        cout << "| 2. Login                             |"<< endl;
        cout << "| 3. Exit                              |"<< endl;
        cout << "========================================" << endl;
        cout << "Pilih Menu[1-3]: ";
        cin >> pil;
        system("cls");

        switch (pil) {
            case 1:
                simpanUserKeFile();
                break;
            case 2:
                berhasilLogin=login();
                if(berhasilLogin){
                    int pilihanMenu;
                    do {
                        menu(pilihanMenu);
                        if (pilihanMenu == 1) tampilFilm();
                        else if (pilihanMenu == 2) cariFilm();
                        else if (pilihanMenu == 3) pesanTiket();
                        else if (pilihanMenu == 4) tampilkanInvoice();
                        else if (pilihanMenu == 5) batalPesan();
                        else if (pilihanMenu == 6){
                            cout << "\nTerima kasih telah menggunakan Layanan Kami! \n";
                            cout <<"Selamat Menonton!\n";
                        }
                        else opsilain();
                    }while (pilihanMenu != 6);
                } 
                break;
            case 3:
                exit(0);
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (true);
}

int main(){
    system("cls");
    isiDataAwal();
    //posisiKursi(film);
    menulogin();
    return 0;
}