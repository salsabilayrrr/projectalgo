#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

struct Movie {
    int id;
    char film_name[50];
    int available_seats[5][10];  // Array 2D untuk kursi (5 baris, 10 kolom)
    double price;
};

struct Reservation {
    int movie_id;
    int seats_reserved;
    char customer_name[50];
    char customer_nik[20];  // NIK untuk mencari pesanan
    Reservation* next;  // Linked List untuk riwayat pemesanan
};

// Function prototypes
void loadMovies(vector<Movie>& movies);
void displayMovies(const vector<Movie>& movies);
void makeReservation(vector<Movie>& movies, Reservation*& history);
void saveReservation(Reservation* history);
void searchReservation(Reservation* history);
void searchMovieByName(const vector<Movie>& movies);
void searchMovieByID(const vector<Movie>& movies);
void sortMoviesByName(vector<Movie>& movies);
void displaySeatingPlan(Movie& movie);
bool isSeatAvailable(Movie& movie, int row, int col);
void reserveSeat(Movie& movie, int row, int col);

int main() {
    vector<Movie> movies;
    Reservation* history = nullptr;  // Linked list untuk riwayat pemesanan

    loadMovies(movies);

    while (true) {
        int choice;
        cout << "\n==== Pemesanan Tiket Bioskop ====\n";
        cout << "1. Tampilkan Jadwal Film\n";
        cout << "2. Pesan Tiket\n";
        cout << "3. Cari Pemesanan berdasarkan NIK\n";
        cout << "4. Cari Film berdasarkan Nama\n";
        cout << "5. Cari Film berdasarkan ID\n";
        cout << "6. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> choice;

        switch (choice) {
            case 1:
                sortMoviesByName(movies);
                displayMovies(movies);
                break;
            case 2:
                makeReservation(movies, history);
                break;
            case 3:
                searchReservation(history);
                break;
            case 4:
                searchMovieByName(movies);
                break;
            case 5:
                searchMovieByID(movies);
                break;
            case 6:
                saveReservation(history);
                cout << "Terima kasih! Program selesai.\n";
                return 0;
            default:
                cout << "Pilihan tidak valid, coba lagi.\n";
        }
    }

    return 0;
}

void loadMovies(vector<Movie>& movies) {
    ifstream file("movies.txt");
    if (!file) {
        cout << "File film tidak ditemukan, membuat file baru.\n";
    } else {
        Movie movie;
        while (file >> movie.id) {
            file.ignore();
            file.getline(movie.film_name, 50);
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 10; ++j) {
                    movie.available_seats[i][j] = 1;  // Kursi kosong (1 berarti tersedia)
                }
            }
            file >> movie.price;
            movies.push_back(movie);
        }
        file.close();
    }

    if (movies.empty()) {
        movies.push_back({1, "Avatar 2", {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}, 120.0});
        movies.push_back({2, "Spiderman: No Way Home", {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}, 100.0});
        movies.push_back({3, "Black Panther: Wakanda Forever", {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}, 110.0});
    }
}

void displayMovies(const vector<Movie>& movies) {
    cout << "\nJadwal Film Tersedia:\n";
    for (const auto& movie : movies) {
        cout << movie.id << ". " << movie.film_name << " - Harga: Rp " << movie.price << endl;
    }
}

void makeReservation(vector<Movie>& movies, Reservation*& history) {
    int movie_id;
    cout << "Masukkan ID Film yang ingin dipesan: ";
    cin >> movie_id;

    if (movie_id < 1 || movie_id > movies.size()) {
        cout << "Film tidak ditemukan.\n";
        return;
    }

    Movie& selected_movie = movies[movie_id - 1];
    displaySeatingPlan(selected_movie);

    int row, col;
    cout << "Masukkan baris dan kolom kursi yang ingin dipesan (1-5 untuk baris, 1-10 untuk kolom): ";
    cin >> row >> col;

    if (!isSeatAvailable(selected_movie, row - 1, col - 1)) {
        cout << "Kursi tidak tersedia, pilih kursi lain.\n";
        return;
    }

    char customer_name[50], customer_nik[20];
    cout << "Masukkan nama pemesan: ";
    cin.ignore();
    cin.getline(customer_name, 50);
    cout << "Masukkan NIK pemesan: ";
    cin >> customer_nik;

    reserveSeat(selected_movie, row - 1, col - 1);

    Reservation* new_reservation = new Reservation{movie_id, 1, "", "", nullptr};
    strcpy(new_reservation->customer_name, customer_name);
    strcpy(new_reservation->customer_nik, customer_nik);

    // Menambah ke linked list riwayat pemesanan
    new_reservation->next = history;
    history = new_reservation;

    cout << "Pemesanan berhasil! Kursi (" << row << ", " << col << ") telah dipesan untuk " << customer_name << ".\n";
}

void saveReservation(Reservation* history) {
    ofstream file("reservations.txt");
    if (!file) {
        cout << "Gagal menyimpan pemesanan.\n";
        return;
    }

    Reservation* current = history;
    while (current != nullptr) {
        file << current->movie_id << " " << current->seats_reserved << " "
             << current->customer_name << " " << current->customer_nik << endl;
        current = current->next;
    }

    file.close();
}

void searchReservation(Reservation* history) {
    char nik[20];
    cout << "Masukkan NIK untuk mencari pemesanan: ";
    cin >> nik;

    Reservation* current = history;
    bool found = false;
    while (current != nullptr) {
        if (strcmp(current->customer_nik, nik) == 0) {
            cout << "Pemesan: " << current->customer_name << ", Film ID: " << current->movie_id << ", Kursi yang dipesan: " << current->seats_reserved << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Pemesan dengan NIK tersebut tidak ditemukan.\n";
    }
}

void searchMovieByName(const vector<Movie>& movies) {
    char search_term[50];
    cout << "Masukkan nama film yang ingin dicari: ";
    cin.ignore();
    cin.getline(search_term, 50);

    bool found = false;
    for (const auto& movie : movies) {
        if (strstr(movie.film_name, search_term)) {
            cout << "Film ditemukan: " << movie.film_name << " dengan ID: " << movie.id << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Film tidak ditemukan.\n";
    }
}

void searchMovieByID(const vector<Movie>& movies) {
    int id;
    cout << "Masukkan ID film yang ingin dicari: ";
    cin >> id;

    if (id < 1 || id > movies.size()) {
        cout << "Film dengan ID tersebut tidak ditemukan.\n";
        return;
    }

    cout << "Film ditemukan: " << movies[id - 1].film_name << " dengan harga Rp " << movies[id - 1].price << endl;
}

void sortMoviesByName(vector<Movie>& movies) {
    // Sorting menggunakan bubble sort berdasarkan nama film
    for (size_t i = 0; i < movies.size() - 1; ++i) {
        for (size_t j = 0; j < movies.size() - 1 - i; ++j) {
            if (strcmp(movies[j].film_name, movies[j + 1].film_name) > 0) {
                swap(movies[j], movies[j + 1]);
            }
        }
    }
}

void displaySeatingPlan(Movie& movie) {
    cout << "\nPeta Kursi untuk film: " << movie.film_name << endl;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout << (movie.available_seats[i][j] == 1 ? "[ ]" : "[X]");
        }
        cout << endl;
    }
}

bool isSeatAvailable(Movie& movie, int row, int col) {
    return movie.available_seats[row][col] == 1;
}

void reserveSeat(Movie& movie, int row, int col) {
    movie.available_seats[row][col] = 0;  // Tandai kursi sebagai terpesan (0)
}
