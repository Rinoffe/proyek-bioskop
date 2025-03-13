#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int maksfilm = 6, maksstudio = 3;

struct {
    string nama, usn, pass;
} staff[100];

struct Studio {
    string nama;
    int harga;
};

struct JadwalFilm {
    string waktu;
    string film[maksstudio];
};

Studio studio[maksstudio] = {
    {"Studio 1", 40000},
    {"Studio 2", 50000},
    {"Studio 3", 60000}
};

JadwalFilm jadwal[maksfilm] = {
    {"08:00 - 10:00", {"Film A", "Film B", "Film C"}},
    {"10:30 - 12:30", {"Film D", "Film E", "Film A"}},
    {"13:00 - 15:00", {"Film B", "Film C", "Film D"}},
    {"15:30 - 17:30", {"Film E", "Film A", "Film B"}},
    {"18:00 - 20:00", {"Film C", "Film D", "Film E"}},
    {"20:30 - 22:30", {"Film A", "Film B", "Film C"}}
};

void tampilkanJadwal() {
    system("cls");

    // Menampilkan judul
    cout << "Jadwal Film\n\n";
    cout << left;
    cout << setw(20) << "Waktu"
         << setw(20) << studio[0].nama
         << setw(20) << studio[1].nama 
         << setw(20) << studio[2].nama << endl;
    cout << setfill('-') << setw(80) << "" << endl;
    
    // Menampilkan Jadwal Film
    cout << setfill(' ');
    for (int i = 0; i < maksfilm; i++) {
        cout << setw(20) << jadwal[i].waktu;
        cout << setw(20) << jadwal[i].film[0];
        cout << setw(20) << jadwal[i].film[1];
        cout << setw(20) << jadwal[i].film[2] << endl;
    }

    cout << "\nHarga Studio:\n";
    for (int i = 0; i < maksstudio; i++) {
        cout << studio[i].nama << " Rp. " << studio[i].harga << endl;
    }

    cout << endl;
    system("pause");
}

void pesanTiket() {
    cout << "\nFitur Pesan Tiket Belum Tersedia\n";
    system("pause");
}

// void cariFilm(JadwalFilm jadwal[], int size, const string &keyword) {
//     bool found = false;

//     for (int i = 0; i < size; i++) {
//         if (jadwal[i].judul.find(keyword) != string::npos) {
//             cout << "\nFilm ditemukan: \n";
//             cout << "Judul : " << jadwal[i].judul << endl;
//             cout << "Harga : " << jadwal[i].harga << endl;
//             found = true;
//         }
//     }

//     if (!found) {
//         cout << "\nFilm tidak ditemukan\n";
//     }
// }

void menuUtama() {
    int pilihan;
    string keyword;

    do {
        system("cls");
        cout << "\n===== Menu Utama Bioskop =====" << endl << endl;
        // cout << "Cari film (masukkan judul): ";
        // cin.ignore();
        // getline(cin, keyword);
        // cariFilm(jadwal, maksfilm, keyword);

        cout << "1. Lihat Jadwal" << endl;
        cout << "2. Pesan Tiket" << endl;
        cout << "3. Cari Film" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih menu : ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanJadwal();
                break;
            case 2:
                pesanTiket();
                break;
            case 3:

            break;
            case 4:
                cout << "Terima kasih telah menggunakan layanan kami!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                system("pause");
        }
        system("cls");
    } while (pilihan != 3);
}


void login(int daftar, bool &ulangMasuk, int limitLogin){
    string usn, pass;
    bool ulangLogin = 1;

    if (limitLogin == 0){
        ulangMasuk = 0;
        cout << "\nLimit login anda habis\n";
        system("pause");
    }else{
        system("cls");
        cout << "MASUK\n\n";
        cout << "Username : "; cin >> usn;
        cout << "Password : "; cin >> pass;

        for (int i = 0; i < daftar; i++) {
            if (usn == staff[i].usn && pass == staff[i].pass) {
                cout << "\nBerhasil masuk\n";
                ulangLogin = 0;
                system("pause");
                menuUtama();
            }
        }

        if (ulangLogin){
            cout << "\nLogin gagal, kesempatan anda tersisa " << limitLogin - 1 << endl;
            system("pause");
            login(daftar, ulangMasuk, limitLogin - 1);
        }
    }
}

void signup(int &daftar) {
    system("cls");
    cout << "DAFTAR\n\n";
    cout << "Nama     : "; cin.ignore(); getline(cin, staff[daftar].nama);
    cout << "Username : "; cin >> staff[daftar].usn;

    for (int i = 0; i < daftar; i++) {
        if (staff[daftar].usn == staff[i].usn) {
            cout << "\nUsername tidak tersedia. Silakan coba username lain.\n";
            system("pause");
            return;
        }
    }

    cout << "Password : "; cin >> staff[daftar].pass;
    cout << "\nBerhasil daftar\n";
    daftar++;
    system("pause");
}

void masuk(int &daftar) {
    int kodeMasuk, limitLogin = 3;
    bool ulangMasuk = 1;

    while (ulangMasuk) {
        system("cls");
        cout << "SISTEM BIOSKOP X\n\n";
        cout << "[1] Masuk\n";
        cout << "[2] Daftar\n";
        cout << "[3] Keluar\n";
        cout << "Pilih : "; cin >> kodeMasuk;

        switch (kodeMasuk) {
            case 1:
                if (daftar == 0) {
                    cout << "\nBelum ada pengguna yang terdaftar, mohon daftar terlebih dahulu\n";
                    system("pause");
                }else{
                    login(daftar, ulangMasuk, limitLogin);
                }
            break;
            case 2:
                signup(daftar);
            break;
            case 3:
                ulangMasuk = 0;
            default:
                cout << "Kode tidak valid\n";
                system("pause");
        }
        system("cls");
    }
}

int main() {
    int daftar = 0;
    masuk(daftar);
}
