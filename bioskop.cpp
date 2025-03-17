#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int maksfilm = 6, maksstudio = 3;

struct {
    string judul, rating, genre, durasi, sutradara, pemain, sinopsis;
} judulFilm[] = {
    {"Film 1", "8.5", "Action", "2 jam", "Sutradara 1", "Pemain 1, Pemain 2", "Sinopsis 1"},
    {"Film 2", "8.5", "Action", "2 jam", "Sutradara 2", "Pemain 1, Pemain 2", "Sinopsis 2"},
    {"Film 3", "8.5", "Action", "2 jam", "Sutradara 3", "Pemain 1, Pemain 2", "Sinopsis 3"},
    {"Film 4", "8.5", "Action", "2 jam", "Sutradara 4", "Pemain 1, Pemain 2", "Sinopsis 4"},
    {"Film 5", "8.5", "Action", "2 jam", "Sutradara 5", "Pemain 1, Pemain 2", "Sinopsis 5"}
};
int n = 4;

string currentFilm[5];

struct {
    string nama, usn, pass;
} staff[100];

struct Studio {
    string nama;
    int harga;
};

Studio studio[maksstudio] = {
    {"Studio 1", 40000},
    {"Studio 2", 50000},
    {"Studio 3", 60000}
};

struct JadwalFilm {
    string waktu;
    string film[maksstudio];
};

JadwalFilm jadwal[maksfilm] = {
    {"08:00 - 10:00"},
    {"10:30 - 12:30"},
    {"13:00 - 15:00"},
    {"15:30 - 17:30"},
    {"18:00 - 20:00"},
    {"20:30 - 22:30"}
};

int cekN(int &j, int k){
    switch (k){
        case 0:
            return j;
        break;
        case 1:
            if (j + 1 > 4) return j = 0;
            else return j = j + 1;
        break;
        case 2:
            if (j + 1 > 4) return 0;
            else return j + 1;
    }
}

void updateJadwal(){
    int jmlFilm = n;
    for (int i = 0; i < 5; i++){
        currentFilm[i] = judulFilm[jmlFilm].judul;
        jmlFilm--;
    }

    int j = 0;
    for (int i = 0; i < maksfilm; i++){
        jadwal[i].film[0] = currentFilm[cekN(j, 0)];
        jadwal[i].film[1] = currentFilm[cekN(j, 1)];
        jadwal[i].film[2] = currentFilm[cekN(j, 2)];
    }
}

void editFilm(){
    int kodeEdit;
    bool ulangEdit;
    system("cls");

    do{
        ulangEdit = 0;
        cout << "Edit Film\n\n";
        for (int i = 0; i < 5; i++){
            cout << i+1 << " ." << currentFilm[i] << endl;
        }
        cout << "Pilih film yang di edit: "; cin >> kodeEdit;
        
        if (kodeEdit < 0 && kodeEdit > 5){
            cout << "Kode tidak valid" << endl;
            ulangEdit = 1;
            system("pause"); system("cls");
        }else{
            int pilihEdit;
            bool ulangPilih = 1;

            while (ulangPilih){
                system("cls");
                cout << "\nJudul : " << judulFilm[(n+1) - kodeEdit].judul << endl << endl;
                cout << "[1] Edit Judul\n"
                     << "[2] Keluar\n";
                cout << "Pilih Edit : "; cin >> pilihEdit;
                switch (pilihEdit){
                    case 1:
                        cout << "\nJudul baru : "; cin.ignore(); getline(cin, judulFilm[(n+1) - kodeEdit].judul);
                    break;
                    case 2:
                        ulangPilih = 0;
                    break;
                    default:
                        cout << "Kode tidak valid" << endl;
                        system("pause");
                }
            }
        }
    }while (ulangEdit);
}

void tambahFilm(){
    string judul;
    n++;
    system("cls");
    cout << "Tambah Film\n\n";
    cout << "Judul Film : "; cin.ignore(); getline(cin, judulFilm[n].judul);
    cout << "Rating     : "; cin >> judulFilm[n].rating;
    cout << "Genre      : "; cin.ignore(); getline(cin, judulFilm[n].genre);
    cout << "Durasi     : "; cin.ignore(); getline(cin, judulFilm[n].durasi);
    cout << "Sutradara  : "; cin.ignore(); getline(cin, judulFilm[n].sutradara);
    cout << "Pemain     : "; cin.ignore(); getline(cin, judulFilm[n].pemain);
    cout << "Sinopsis   : "; cin.ignore(); getline(cin, judulFilm[n].sinopsis);
    cout << "\nFilm berhasil ditambahkan\n";
    system("pause");
}

void menuEdit(){
    int kodeEdit;
    bool ulangEdit = 1;
    
    system("cls");
    do{
        cout << "Edit Informasi Jadwal\n\n";
        cout << "PERHATIAN!\n"
             << "1. Bioskop hanya bisa menampilkan 5 film dalam 1 hari\n"
             << "2. Jika film baru ditambahkan maka film lama tidak akan ditayangkan lagi\n"
             << "3. Data film yang sudah tidak ditayangkan masih tersimpan kecuali dihapus\n"
             << "4. Hapus dan edit film dengan seksama\n\n";
             
        cout << "[1] Edit Film\n"
             << "[2] Tambah Film\n"
             << "[3] Hapus Film\n"
             << "[4] Keluar\n\n";
        cout << "Pilih kode : "; cin >> kodeEdit;
        
        switch (kodeEdit){
            case 1:
                editFilm();
            break;
            case 2:
                tambahFilm();
            break;
            case 3:
                
            break;
            case 4:
                ulangEdit = 0;
            break;
            default:
                cout << "Kode menu tidak valid" << endl;
                system("pause");
        }
        system("cls");
    }while (ulangEdit);
}

void cariFilm() {
    bool found = false;
    string keyword;
    
    system("cls");
    cout << "Cari Film\n\n";
    cout << "Cari : "; cin.ignore(); getline(cin, keyword);

    for (int i = 0; i < 5; i++){
        if (currentFilm[i].find(keyword) != string::npos){
                        cout << "\nJudul      : " << currentFilm[i] << endl;
                        // cout << "Rating     : " << judulFilm[i].rating << endl;
                        // cout << "Genre      : " << judulFilm[i].genre << endl;
                        // cout << "Durasi     : " << judulFilm[i].durasi << endl;
                        // cout << "Sutradara  : " << judulFilm[i].sutradara << endl;
                        // cout << "Pemain     : " << judulFilm[i].pemain << endl;
                        // cout << "Sinopsis   : " << judulFilm[i].sinopsis << endl;
                        cout << "Jam Tayang : "  << endl;
            for (int j = 0; j < maksfilm; j++) {
                for (int k = 0; k < maksstudio; k++) {
                    if (jadwal[j].film[k] == currentFilm[i]) {
                        cout << studio[k].nama << " (Rp. " << studio[k].harga << ") : " << jadwal[j].waktu << endl;
                        found = true;
                    }
                }
            }
        }
    }

    if (!found) {
        cout << "\nFilm tidak ditemukan";
    }
    cout <<  endl;
    system("pause");
}

void pesanTiket() {
    cout << "\nFitur Pesan Tiket Belum Tersedia\n";
    system("pause");
}

void tampilkanJadwal() {
    system("cls");
    
    cout << "Jadwal Film\n\n";
    cout << left;
    cout << setw(20) << "Waktu"
         << setw(20) << studio[0].nama
         << setw(20) << studio[1].nama 
         << setw(20) << studio[2].nama << endl;
    cout << setfill('-') << setw(80) << "" << endl;
    
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

void menuUtama() {
    int kodeMenu;
    bool ulangUtama = 1;

    system("cls");
    do {
        updateJadwal();
        cout << "\nMenu Utama\n\n";

        cout << "1. Lihat Jadwal" << endl;
        cout << "2. Pesan Tiket" << endl;
        cout << "3. Cari Film" << endl;
        cout << "4. Edit Jadwal" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih menu : "; cin >> kodeMenu;

        switch (kodeMenu) {
            case 1:
                tampilkanJadwal();
            break;
            case 2:
                pesanTiket();
            break;
            case 3:
                cariFilm();
            break;
            case 4:
                menuEdit();
            break;
            case 5:
                ulangUtama = 0;
            break;
            default:
                cout << "Kode menu tidak valid" << endl;
                system("pause");
        }
        system("cls");
    } while (ulangUtama);
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
                break;
            default:
                cout << "Kode tidak valid\n";
                system("pause");
        }
        system("cls");
    }
}

main() {
    int daftar = 0;
    masuk(daftar);
}
