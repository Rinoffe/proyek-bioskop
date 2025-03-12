#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int maksfilm = 3;
int percobaan = 3;

struct {
    string nama, usn, pass;
} staff[100];

struct JadwalFilm {
    string judul;
    string jamTayang[3];
    char studio[3];
    int harga;
};

JadwalFilm jadwal[maksfilm] = {
    {"Perayaan Mati Rasa", {"09.00 - 11.00", "12.30 - 13.30", "11.15 - 12.15"}, {'A', 'B', 'C'}, 50000},
    {"Petaka Gunung Gede", {"09.00 - 11.00", "11.15 - 12.15", "12.30 - 13.30"}, {'B', 'C', 'A'}, 50000},
    {"Main America: Brave New", {"09.00 - 11.00", "11.15 - 12.15", "12.30 - 13.30"}, {'C', 'B', 'A'}, 50000}
};

void tampilkanJadwal() {
    system("cls");
    cout << "========================================================================================\n";
    cout << "| " << setw(6) << left << "Kode" 
         << "| " << setw(30) << left << "Judul"
         << "| " << setw(15) << left << "Jam Tayang"
         << "| " << setw(7) << left << "Studio"
         << "| " << setw(10) << left << "Harga" << "|\n";
    cout << "========================================================================================\n";

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == 0)
                cout << "| " << setw(6) << left << i + 1
                     << "| " << setw(30) << left << jadwal[i].judul;
            else
                cout << "| " << setw(6) << " "
                     << "| " << setw(30) << " ";
            
            cout << "| " << setw(15) << left << jadwal[i].jamTayang[j]
                 << "| " << setw(7) << left << jadwal[i].studio[j]
                 << "| " << setw(10) << left << jadwal[i].harga << "|\n";
        }
        cout << "----------------------------------------------------------------------------------------\n";
    }
    system("pause");
}

void pesanTiket() {
    cout << "\nFitur Pesan Tiket Belum Tersedia\n";
    system("pause");
}



void cariFilm(JadwalFilm jadwal[], int size, const string &keyword) {
    bool found = false;

    for (int i = 0; i < size; i++) {
        if (jadwal[i].judul.find(keyword) != string::npos) {
            cout << "\nFilm ditemukan: \n";
            cout << "Judul : " << jadwal[i].judul << endl;
            cout << "Harga : " << jadwal[i].harga << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "\nFilm tidak ditemukan\n";
    }
}

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

        cout << "1. Lihat Jadwal Film" << endl;
        cout << "2. Pesan Tiket" << endl;
        cout << "3. Cari Film" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih menu (1-3): ";
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
