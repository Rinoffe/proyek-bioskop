#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

const int maxFilm = 20, maxCurrent = 5, maxStudio = 3, maxStaff = 50, maxShowtimes = 10;
const int rows = 6, cols = 8;

struct {
    string nama, usn, pass;
} staff[maxStaff];

struct film{
    string judul, rating, genre;
    int durasi;
};

film dataFilm[maxFilm] = {
    {"bFilm 1", "Umum", "Action", 180},
    {"eFilm 2", "Umum", "Action", 150},
    {"aFilm 3", "Umum", "Action", 120},
    {"cFilm 4", "Umum", "Action", 90},
    {"dFilm 5", "Umum", "Action", 60}
};
int jmlFilm = 4;

film currentFilm[maxCurrent];

struct seats{
    string seatsDisplay[10][10];
};

struct jadwal{
    string judul, startTime[maxShowtimes];
    seats seats[maxShowtimes];
};

struct studio {
    string nama;
    int harga;
    jadwal dataJadwal[maxCurrent];
};

studio dataStudio[maxStudio] = {
    {"Dolby Atmos", 55000},
    {"Premium", 45000},
    {"Standar", 35000}
};

struct penonton{
    string baris[rows * cols], kolom[rows * cols];
} dataPenonton[100];

int seatSold = 0, jmlPenonton = 0;
bool jadwalChange;

string countTime(int index, int &hour, int &minute){
    int durasiBreak = 30;    
    string time = to_string(hour) + ":" + (minute < 10 ? "0" : "") + to_string(minute);

    minute += currentFilm[index].durasi + durasiBreak;
    while (minute >= 60){
        minute -= 60;
        hour++;
    }
    return time;
}

void updateJadwal(){
    for (int i = 0; i < maxCurrent; i++){
        currentFilm[i] = dataFilm[jmlFilm - i];
    }

    for (int i = 0; i < maxStudio; i++){
        int hour = 10, minute = 0;
        int filmIndex = i, cycle = 0;

        while (true){
            int index = filmIndex % maxCurrent;
            jadwal *ptrStudio = &dataStudio[i].dataJadwal[index];

            ptrStudio->judul = currentFilm[index].judul;
            ptrStudio->startTime[cycle] = countTime(index, hour, minute);

            filmIndex++;
            if (index == maxCurrent - 1) cycle++;
            if (hour > 21) break;
        }
    }
}

void hapusFilm(){
    int kodeHapus;
    bool ulangHapus = 1;
    film *ptrFilm = dataFilm;

    while (ulangHapus){
        system("cls");
        cout << "Hapus Film\n\n";

        for (int i = 0; i < jmlFilm + 1; i++){
            cout << i + 1 << ". " << (ptrFilm + i)->judul << endl;
        }
        cout << jmlFilm + 2 << ". Keluar\n";
        cout << "\nPilih menu : "; cin >> kodeHapus;

        if (kodeHapus < 0 || kodeHapus > jmlFilm + 2){
            cout << "\nKode tidak valid" << endl;
            system("pause"); system("cls");
        }else if (kodeHapus == jmlFilm + 2){
            ulangHapus = 0;
        }else{
            film *start = &dataFilm[kodeHapus - 1];
            for (int i = 0; i < jmlFilm - kodeHapus + 1; i++){
                *(start + i) = *(start + i + 1);
            }
            jmlFilm--;
            cout << "\nFilm telah dihapus\n"; system("pause");
            if (kodeHapus > 5) jadwalChange = 1;
        }
    }
}

void tambahFilm(){
    jmlFilm++;
    film *ptrFilm = &dataFilm[jmlFilm];

    if (jmlFilm >= maxFilm) {
        cout << "\nKapasitas film penuh!\n";
        system("pause");
        return;
    }
    
    system("cls");
    cout << "Tambah Film\n\n";
    cout << "Judul Film     : "; cin.ignore(); getline(cin, ptrFilm->judul);
    cout << "Rating         : "; cin >> ptrFilm->rating;
    cout << "Genre          : "; cin.ignore(); getline(cin, ptrFilm->genre);
    cout << "Durasi (menit) : "; cin >> ptrFilm->durasi;
    cout << "\nFilm berhasil ditambahkan\n";
    system("pause"); jadwalChange = 1;
}

void editFilm(){
    int kodeEdit;
    bool ulangEdit = 1;
    film *ptrCurrent = currentFilm;

    while (ulangEdit){
        system("cls");
        cout << "Edit Film\n\n";

        for (int i = 0; i < maxCurrent; i++){
            cout << i + 1 << ". " << (ptrCurrent + i)->judul << endl;
        }
        cout << maxCurrent + 1 << ". Keluar\n";
        cout << "\nPilih film yang di edit: "; cin >> kodeEdit;
        
        if (kodeEdit < 0 || kodeEdit > 6){
            cout << "\nKode tidak valid" << endl;
            system("pause"); system("cls");
        }else if (kodeEdit == 6){
            ulangEdit = 0;
        }else{
            
            int pilihEdit;
            bool ulangPilih = 1;

            while (ulangPilih){
                system("cls");
                film* ptrEdit = &dataFilm[(jmlFilm + 1) - kodeEdit];

                cout << "[1] Judul  : " << ptrEdit->judul
                     << "\n[2] Rating : " << ptrEdit->rating
                     << "\n[3] Genre  : " << ptrEdit->genre
                     << "\n[4] Durasi : " << ptrEdit->durasi
                     << "\n[5] Keluar\n\n";
                cout << "Pilih Edit : "; cin >> pilihEdit; cin.ignore();
                
                switch (pilihEdit){
                    case 1: cout << "\nJudul baru : "; getline(cin, ptrEdit->judul); break;
                    case 2: cout << "\nRating baru : "; getline(cin, ptrEdit->rating); break;
                    case 3: cout << "\nGenre baru : "; getline(cin, ptrEdit->genre); break;
                    case 4: cout << "\nDurasi baru (menit) : "; cin >> ptrEdit->durasi; break;
                    case 5: ulangPilih = 0; break;
                    default:
                        cout << "Kode tidak valid" << endl;
                        system("pause");
                }
            }
        }
    }
}

void menuEdit(){
    int kodeEdit;
    bool ulangEdit = 1;
        
    while (ulangEdit){
        system("cls");
        updateJadwal();
        cout << "Edit Informasi Jadwal\n\n";
        cout << "PERHATIAN!\n"
             << "# Bioskop hanya menampilkan " << maxCurrent << " film terbaru\n"
             << "# Jika tambah film baru maka film terlama tidak akan ditayangkan\n"
             << "# Data film lama masih disimpan kecuali dihapus\n\n";
             
        cout << "[1] Edit Film\n"
             << "[2] Tambah Film\n"
             << "[3] Hapus Film\n"
             << "[4] Keluar\n\n";
        cout << "Pilih kode : "; cin >> kodeEdit;
        
        switch (kodeEdit){
            case 1: editFilm(); break;
            case 2: tambahFilm(); break;
            case 3:
                if (jmlFilm < maxCurrent){
                    cout << "\nHarus ada lebih dari " << maxCurrent << " film untuk hapus film\n";
                    system("pause");
                }else{
                    hapusFilm();
                }
            break;
            case 4: ulangEdit = 0; break;
            default:
                cout << "Kode menu tidak valid" << endl;
                system("pause");
        }
    }
}

void sortJadwal(int kodeSort, int kondisi){
    system("cls");
    film *ptrSort = currentFilm;
    bool tukar;    
        
    for (int i = 0; i < maxCurrent - 1; i++){
        for (int j = 0; j < maxCurrent - 1 - i; j++){
            if (kodeSort == 1) tukar = kondisi ?
                ((ptrSort + j)->judul > (ptrSort + j + 1)->judul) :
                ((ptrSort + j)->judul < (ptrSort + j + 1)->judul);
            else tukar = kondisi ?
                ((ptrSort + j)->durasi > (ptrSort + j + 1)->durasi) :
                ((ptrSort + j)->durasi < (ptrSort + j + 1)->durasi);

            if (tukar) swap(*(ptrSort + j), *(ptrSort + j + 1));
        }
    }    
    for (int i = 0; i < maxCurrent; i++) {
        cout << i + 1 << ". " << (ptrSort + i)->judul;
        if (kodeSort == 2) cout << " - " << (ptrSort + i)->durasi << " menit";
        cout << endl;
    }    
    cout << endl;
    system("pause");
}

void menuSort(){
    int kodeSort;
    bool ulangSort = 1;

    while (ulangSort){
        system("cls");
        updateJadwal();
        cout << "Sort Film\n\n";
        cout << "[1] Nama Ascending\n"
             << "[2] Nama Descending\n"
             << "[3] Durasi Ascending\n"
             << "[4] Durasi Descending\n"
             << "[5] Keluar\n";
        cout << "\nPilih menu : "; cin >> kodeSort;

        switch(kodeSort){
            case 1: sortJadwal(1, 1); break;
            case 2: sortJadwal(1, 0); break;
            case 3: sortJadwal(2, 1); break;
            case 4: sortJadwal(2, 0); break;
            case 5: ulangSort = 0; break;
            default:
                cout << "Kode menu tidak valid" << endl;
                system("pause");
        }
    }
}

void cariFilm() {
    bool found = 0;
    string keyword;

    system("cls");
    cout << "Cari Film\n\n";
    cout << "Cari : "; cin.ignore(); getline(cin, keyword);

    for (int i = 0; i < maxCurrent; i++){
        film *currentPtr = &currentFilm[i];
        if (currentPtr->judul.find(keyword) != string::npos){
            cout << "\nJudul      : " << currentPtr->judul << endl;
            cout << "Rating     : " << currentPtr->rating << endl;
            cout << "Genre      : " << currentPtr->genre << endl;
            cout << "Durasi     : " << currentPtr->durasi << " menit" << endl;
            cout << "Jam Tayang : ";

            for (int i = 0; i < maxStudio; i++){
                for (int j = 0; j < maxShowtimes; j++){
                    if (currentPtr->judul == dataStudio[i].dataJadwal[j].judul){
                        for (int k = 0; k < maxShowtimes; k++){
                            if (!dataStudio[i].dataJadwal[j].startTime[k].empty()){
                                cout << dataStudio[i].dataJadwal[j].startTime[k] << " ";
                                found = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    if (!found) {
        cout << "\nFilm tidak ditemukan";
    }
    cout << endl << endl;
    system("pause");
}

void displayJadwal(){
    system("cls");
    cout << "Jadwal Film\n\n";

    for (int i = 0; i < maxStudio; i++){
        int hour = 10, minute = 0;
        int filmIndex = i, cycle = 0;

        cout << "+" << setfill('-') << setw(60) << "" << "+" << endl;
        cout << left << setfill(' ');
        cout << "| " << dataStudio[i].nama << " (Rp. " << dataStudio[i].harga
             << setw(47 - dataStudio[i].nama.length()) << ")" << " |" << endl;
        cout << "+" << setfill('-') << setw(60) << "" << "+" << endl;

        while (true){
            int index = filmIndex % maxCurrent;
            jadwal *ptrStudio = &dataStudio[i].dataJadwal[index];
            countTime(index, hour, minute);

            cout << setfill(' ');
            cout << "| " << ptrStudio->startTime[cycle] << " - " << setw(50) << ptrStudio->judul << " |\n";

            filmIndex++;
            if (index == maxCurrent - 1) cycle++;
            if (hour > 21) break;
        }
        cout << "+" << setfill('-') << setw(60) << "" << "+\n";
    }
}

void cetakTiket(int studio, int film, int tayang){
    system ("cls");
    int baris, kolom;
    penonton *ptrPenonton = &dataPenonton[jmlPenonton - 1];

    cout << "Selamat menikmati film!\n\n";
    for (int i = 0; i < rows * cols; i++){
        if (!ptrPenonton->baris[i].empty()){

            cout << "+" << setfill('-') << setw(65) << "" << "+" << endl;
            cout << left << setfill(' ');
            cout << setw(65) << "| Bioskop X " << " |";
            cout << "\n| Film       : " << setw(50) << dataStudio[studio].dataJadwal[film].judul << " |"
                << "\n| Jam Tayang : " << setw(50) << dataStudio[studio].dataJadwal[film].startTime[tayang] << " |"
                << "\n| Studio     : " << setw(50) << dataStudio[studio].nama << " |"
                << "\n| Seat       : " << ptrPenonton->baris[i] << " " << setw(48) << ptrPenonton->kolom[i] << " |"
                << "\n| Price      : " << setw(50) << dataStudio[studio].harga << " |\n";
            cout << "+" << setfill('-') << setw(65) << "" << "+" << endl;
        }
    }
    system("pause");
}

void displaySeats(int studio, int film, int tayang){
    system("cls");
    char ulangPilih;
    bool kosong = 0;
    seats *ptrSeats = &dataStudio[studio].dataJadwal[film].seats[tayang];

    if (ptrSeats->seatsDisplay[0][0] == "" || jadwalChange) kosong = 1; jadwalChange = 0;
    if (kosong){
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                ptrSeats->seatsDisplay[i][j] = "|   ";
            }
        }
    }
    cout << "Kursi ruang " << dataStudio[studio].nama << endl << endl;

    cout << "    ";
    for (int i = 0; i < cols; i++){
        cout << "  " << i + 1 << " ";
    }
    cout << "\n\n    " << setfill('-') << setw(cols * 4 + 1) << "" << endl;
    for (int i = rows; i > 0; i--){
        cout << i << (i > 9 ? "  " : "   ");

        for (int j = 0; j < cols; j++){
            cout << ptrSeats->seatsDisplay[i - 1][j];
        }
        cout << "|" << endl;
        cout << "    " << setfill('-') << setw(cols * 4 + 1) << "" << endl;
    }
    cout << "    " << setfill(' ') << setw((cols * 4 + 1) / 2 - 4) << "" << "/ Layar /" << endl;
}

void setSeats(int studio, int film, int tayang){
    int baris, kolom, kodeSeats, indexSeat = 0, tempSeat = seatSold;
    bool ulangSeats = 1;
    seats *ptrSeats = &dataStudio[studio].dataJadwal[film].seats[tayang];
    penonton *ptrPenonton = &dataPenonton[jmlPenonton];

    while (ulangSeats){
        displaySeats(studio, film, tayang);
        cout << "\n[1] Tambah kursi"
             << "\n[2] Hapus kursi"
             << "\n[3] Hapus semua"
             << "\n[4] Keluar\n\n";
        cout << "Pilih menu: "; cin >> kodeSeats;

        switch (kodeSeats){
            case 1:
                displaySeats(studio, film, tayang);
                cout << "\nInput baris & kolom (contoh: 5 7)\n";
                cout << "Pilih kursi : "; cin >> baris >> kolom;

                if (ptrSeats->seatsDisplay[baris - 1][kolom - 1] == "| X "){
                    cout << "\nKursi sudah terpakai\n\n";
                    system("pause");
                }else{
                    ptrSeats->seatsDisplay[baris - 1][kolom - 1] = "| X ";
                    ptrPenonton->baris[indexSeat] = to_string(baris); ptrPenonton->kolom[indexSeat] = to_string(kolom);
                    seatSold++; indexSeat++;
                }
            break;
            case 2:
                displaySeats(studio, film, tayang);
                cout << "\nHapus kursi (contoh: 5 7): "; cin >> baris >> kolom;
                if (ptrSeats->seatsDisplay[baris - 1][kolom - 1] == "|   "){
                    cout << "\nKursi sudah kosong\n\n";
                    system("pause");
                }else{
                    ptrSeats->seatsDisplay[baris - 1][kolom - 1] = "|   ";
                    for (int i = 0; i < rows * cols; i++){
                        if (ptrPenonton->baris[i] == to_string(baris) && ptrPenonton->kolom[i] == to_string(kolom))
                            ptrPenonton->baris[i] = ""; ptrPenonton->kolom[i] = "";
                    }
                    seatSold--; indexSeat--;
                }
            break;
            case 3:
                for (int i = 0; i < rows; i++){
                    for (int j = 0; j < cols; j++){
                        ptrSeats->seatsDisplay[i][j] = "|   ";
                    }
                }
            break;
            case 4:
                ulangSeats = 0; system("cls");
            break;
            default:
                cout << "Kode menu tidak valid" << endl;
                system("pause");
            }
    }

    if (tempSeat < seatSold){
        jmlPenonton++;
        cetakTiket(studio, film, tayang);
    }
}

void pilihJadwal() {
    system("cls");
    int studio, film, tayang, count = 1;

    cout << "Studio\n";
    for (int i = 0; i < maxStudio; i++){
        cout << i + 1 << ". " << dataStudio[i].nama << endl;
    }
    cout << "\nPilih Studio : "; cin >> studio;

    system("cls"); cout << "Film\n";
    for (int i = 0; i < maxCurrent; i++){
        cout << i + 1 << ". " << dataStudio[studio - 1].dataJadwal[i].judul << endl;
    }
    cout << "\nPilih Film : "; cin >> film;    

    system("cls"); cout << "Jam Tayang\n";    
    for (int i = 0; i < maxShowtimes; i++){
        if (!dataStudio[studio - 1].dataJadwal[film - 1].startTime[i].empty()){
            cout << count << ". " << dataStudio[studio - 1].dataJadwal[film - 1].startTime[i] << endl;
            count++;
        }
    }
    cout << "\nKode Jam Tayang : "; cin >> tayang;
    
    setSeats(studio - 1, film - 1, tayang - 1);    
}

void menuUtama() {
    int kodeMenu;
    bool ulangUtama = 1;

    while (ulangUtama){
        system("cls");
        updateJadwal();
        cout << "\nMenu Utama\n\n";

        cout << "[1] Lihat Jadwal" << endl;
        cout << "[2] Cetak Tiket" << endl;
        cout << "[3] Cari Film" << endl;
        cout << "[4] Sort Film" << endl;
        cout << "[5] Edit Film" << endl;
        cout << "[6] Keluar" << endl;
        cout << "\nPilih menu : "; cin >> kodeMenu;

        switch (kodeMenu) {
            case 1: displayJadwal(); system("pause"); break;
            case 2: pilihJadwal(); break;
            case 3: cariFilm(); break;
            case 4: menuSort(); break;
            case 5: menuEdit(); break;
            case 6: ulangUtama = 0; break;
            default:
                cout << "Kode menu tidak valid" << endl;
                system("pause");
        }
    }
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
    int kodeMasuk, limitLogin = 5;
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
    }
}

main() {
    int daftar = 0;
    masuk(daftar);
}