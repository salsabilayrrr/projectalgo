#include <iostream>

using namespace std;

struct TiketKereta {
    string id_tiket;
    string nama_penumpang;
    string asal;
    string tujuan;
    string tanggal;
    string jam;
    string kelas;
    int kursi;
    TiketKereta* next;
};

TiketKereta* head = nullptr;

