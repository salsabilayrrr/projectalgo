#include <iostream>

using namespace std;

struct TiketBioskop {
    string id_tiket;
    string nama_pemesan;
    string namafilm;
    string tanggal;
    string jam;
    string harga;
    int jmltiket;
    int kursi;
    TiketBioskop* next;
};

TiketBioskop* head = nullptr;

int main(){
    
}