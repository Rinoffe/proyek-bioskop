#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int maksfilm = 6, maksstudio = 3;

struct film{
    string judul, rating, genre;
    float durasi;
    string sutradara, pemain, sinopsis;
};

film dataFilm[] = {
    {"bFilm 1", "Umum", "Action", 2, "Sutradara 1", "Pemain 1, Pemain 2", "Sinopsis 1"},
    {"eFilm 2", "Umum", "Action", 1, "Sutradara 2", "Pemain 1, Pemain 2", "Sinopsis 2"},
    {"aFilm 3", "Umum", "Action", 1.3, "Sutradara 3", "Pemain 1, Pemain 2", "Sinopsis 3"},
    {"cFilm 4", "Umum", "Action", 1.5, "Sutradara 4", "Pemain 1, Pemain 2", "Sinopsis 4"},
    {"dFilm 5", "Umum", "Action", 3, "Sutradara 5", "Pemain 1, Pemain 2", "Sinopsis 5"}
};
int jmlFilm = 4; //film tersimpan, dpt berubah

film currentFilm[5];

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
    for (int i = 0; i < 5; i++){
        for (int j = 4 - i; j == jmlFilm - i; j--){
            currentFilm[i] = dataFilm[jmlFilm];
        }
    }

    int j = 0;
    for (int i = 0; i < maksfilm; i++){
        jadwal[i].film[0] = currentFilm[cekN(j, 0)].judul;
        jadwal[i].film[1] = currentFilm[cekN(j, 1)].judul;
        jadwal[i].film[2] = currentFilm[cekN(j, 2)].judul;
    }
}

void hapusFilm(){
    system("cls");
    int kodeHapus;
    bool ulangHapus;

    do{
        ulangHapus = 0;
        cout << "Hapus Film\n\n";
        for (int i = 0; i < jmlFilm + 1; i++){
            cout << i + 1 << ". " << dataFilm[i].judul << endl;
        }
        cout << "\nPilih film yang di hapus: "; cin >> kodeHapus;

        if (kodeHapus < 0 || kodeHapus > jmlFilm + 1){
            cout << "Kode tidak valid" << endl;
            ulangHapus = 1;
            system("pause"); system("cls");
        }else{
            jmlFilm--;
            for (int i = kodeHapus - 1; i < jmlFilm + 1; i++){
                dataFilm[i] = dataFilm[i + 1];
            }
        }

    }while (ulangHapus);
}

void tambahFilm(){
    string judul;
    jmlFilm++;
    system("cls");
    cout << "Tambah Film\n\n";
    cout << "Judul Film : "; cin.ignore(); getline(cin, dataFilm[jmlFilm].judul);
    cout << "Rating     : "; cin >> dataFilm[jmlFilm].rating;
    cout << "Genre      : "; cin.ignore(); getline(cin, dataFilm[jmlFilm].genre);
    cout << "Durasi     : "; cin >> dataFilm[jmlFilm].durasi;
    cout << "Sutradara  : "; cin.ignore(); getline(cin, dataFilm[jmlFilm].sutradara);
    cout << "Pemain     : "; cin.ignore(); getline(cin, dataFilm[jmlFilm].pemain);
    cout << "Sinopsis   : "; cin.ignore(); getline(cin, dataFilm[jmlFilm].sinopsis);
    cout << "\nFilm berhasil ditambahkan\n";
    system("pause");
}

void editFilm(){
    int kodeEdit;
    bool ulangEdit;
    system("cls");

    do{
        ulangEdit = 0;
        cout << "Edit Film\n\n";
        for (int i = 0; i < 5; i++){
            cout << i + 1 << ". " << currentFilm[i].judul << endl;
        }
        cout << "\nPilih film yang di edit: "; cin >> kodeEdit;
        
        if (kodeEdit < 0 || kodeEdit > 5){
            cout << "Kode tidak valid" << endl;
            ulangEdit = 1;
            system("pause"); system("cls");
        }else{
            int pilihEdit;
            bool ulangPilih = 1;

            while (ulangPilih){
                system("cls");
                cout << "\nJudul : " << dataFilm[(jmlFilm+1) - kodeEdit].judul << endl << endl;
                cout << "[1] Edit Judul\n"
                     << "[2] Keluar\n";
                cout << "Pilih Edit : "; cin >> pilihEdit;
                switch (pilihEdit){
                    case 1:
                        cout << "\nJudul baru : "; cin.ignore(); getline(cin, dataFilm[(jmlFilm+1) - kodeEdit].judul);
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

void menuEdit(){
    int kodeEdit;
    bool ulangEdit = 1;
    
    system("cls");
    do{
        updateJadwal();
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
                if (jmlFilm < 5){
                    cout << "\nHarus ada lebih dari 5 film untuk hapus film\n"; system("pause");
                }else{
                    hapusFilm();
                }
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

void sortDurasi(int kodeSort){
    system("cls");
    if (kodeSort == 3){
        cout << "Durasi Ascending\n\n";
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4 - i; j++){
                if (currentFilm[j].durasi > currentFilm[j + 1].durasi){
                    swap(currentFilm[j], currentFilm[j + 1]);
                }
            }
        }
    }else{
        cout << "Durasi Descending\n\n";
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4 - i; j++){
                if (currentFilm[j].durasi < currentFilm[j + 1].durasi){
                    swap(currentFilm[j], currentFilm[j + 1]);
                }
            }
        }
    }
    
    for (int i = 0; i < 5; i++){
        cout << i + 1 << ". " << currentFilm[i].judul << endl;
        cout << "   Durasi : " << currentFilm[i].durasi << " jam" << endl;
    }
    system("pause");
}

void sortNama(int kodeSort){
    system("cls");
    if (kodeSort == 1){
        cout << "Nama Ascending\n\n";
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4 - i; j++){
                if (currentFilm[j].judul[0] > currentFilm[j + 1].judul[0]){
                    swap(currentFilm[j], currentFilm[j + 1]);
                }
            }
        }
    }else{
        cout << "Nama Descending\n\n";
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4 - i; j++){
                if (currentFilm[j].judul[0] < currentFilm[j + 1].judul[0]){
                    swap(currentFilm[j], currentFilm[j + 1]);
                }
            }
        }
    }
    
    for (int i = 0; i < 5; i++){
        cout << i + 1 << ". " << currentFilm[i].judul << endl;
    }
    system("pause");
}

void menuSort(){
    int kodeSort;
    bool ulangSort = 1;

    do{
        system("cls");
        updateJadwal();
        cout << "Sort Film\n\n";
        cout << "[1] Nama Ascending\n"
             << "[2] Nama Descending\n"
             << "[3] Durasi Ascending\n"
             << "[4] Durasi Descending\n"
             << "[5] Keluar\n";
        cout << "Pilih menu : "; cin >> kodeSort;

        switch(kodeSort){
            case 1:
                sortNama(kodeSort);
            break;
            case 2:
                sortNama(kodeSort);
            break;
            case 3:
                sortDurasi(kodeSort);
            break;
            case 4:
                sortDurasi(kodeSort);
            break;
            case 5:
                ulangSort = 0;
            break;
            default:
                cout << "Kode menu tidak valid" << endl;
                system("pause");
        }
        system("cls");

    } while(ulangSort);
}

void cariFilm() {
    bool found = false;
    string keyword;
    
    system("cls");
    cout << "Cari Film\n\n";
    cout << "Cari : "; cin.ignore(); getline(cin, keyword);

    for (int i = 0; i < 5; i++){
        if (currentFilm[i].judul.find(keyword) != string::npos){
                        cout << "\nJudul      : " << currentFilm[i].judul << endl;
                        cout << "Rating     : " << currentFilm[i].rating << endl;
                        cout << "Genre      : " << currentFilm[i].genre << endl;
                        cout << "Durasi     : " << currentFilm[i].durasi << " jam" << endl;
                        cout << "Sutradara  : " << currentFilm[i].sutradara << endl;
                        cout << "Pemain     : " << currentFilm[i].pemain << endl;
                        cout << "Sinopsis   : " << currentFilm[i].sinopsis << endl;
                        cout << "Jam Tayang : "  << endl;
            for (int j = 0; j < maksfilm; j++) {
                for (int k = 0; k < maksstudio; k++) {
                    if (jadwal[j].film[k] == currentFilm[i].judul) {
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
        cout << "4. Sort Film" << endl;
        cout << "5. Edit Film" << endl;
        cout << "6. Keluar" << endl;
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
                menuSort();
            break;
            case 5:
                menuEdit();
            break;
            case 6:
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
        cout << "Pilih menu: "; cin >> kodeMasuk;

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
