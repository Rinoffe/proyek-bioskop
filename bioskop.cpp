#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

const int maxCurrent = 5, maxStudio = 3, maxShowtimes = 3;
const int rows = 6, cols = 8;
string fileFilm = "data_film.csv",
       fileStaff = "data_staff.csv",
       fileJadwal = "data_jadwal.csv";

int jmlStaff = 0, jmlFilm = 0;
bool jadwalChange;

struct staff{
    string nama, usn, pass;
} dataStaff;

struct film{
    string judul, rating, genre;
    int durasi;
};
film dataFilm, currentFilm[maxCurrent];

struct seats{
    string seatsDisplay[rows][cols];
};

struct jadwal{
    string judul, jamTayang[maxShowtimes];
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

struct temp{
    string nama, judul, tayang, display, baris, kolom;
}tempDataStudio;

struct penonton{
    string baris[rows * cols], kolom[rows * cols];
} dataPenonton;

void splitFileDataJadwal(string line){
    string nama, judul, tayang, display, baris, kolom;
    stringstream ss(line);

    getline(ss, nama, ',');
    getline(ss, judul, ',');
    getline(ss, tayang, ',');
    getline(ss, display, ',');
    getline(ss, baris, ',');
    getline(ss, kolom);

    tempDataStudio.nama = nama;
    tempDataStudio.judul = judul;
    tempDataStudio.tayang = tayang;
    tempDataStudio.display = display;
    tempDataStudio.baris = baris;
    tempDataStudio.kolom = kolom;
}

void splitFileDataFilm(string line){
    string judul, rating, genre, durasi;
    stringstream ss(line);

    getline(ss, judul, ',');
    getline(ss, rating, ',');
    getline(ss, genre, ',');
    getline(ss, durasi);

    dataFilm.judul = judul;
    dataFilm.rating = rating;
    dataFilm.genre = genre;
    dataFilm.durasi = stoi(durasi);
}

void splitFileDataStaff(string line){
    string nama, usn, pass;
    stringstream ss(line);

    getline(ss, nama, ',');
    getline(ss, usn, ',');
    getline(ss, pass);

    dataStaff.nama = nama;
    dataStaff.usn = usn;
    dataStaff.pass = pass;
}

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

void updateJadwal(bool display){
    string line;

    if (display){
        system("cls");
        cout << "Jadwal Film\n\n";
    }

    ifstream file(fileFilm);
    if (file.is_open()){
        for (int i = 0; i < maxCurrent; i++){
            file.seekg(0, ios::beg);
            for (int j = 0; j < jmlFilm - i; j++){
                getline(file, line);
            }
            splitFileDataFilm(line);
            currentFilm[i] = dataFilm;
        }
    }
    file.close();

    for (int i = 0; i < maxStudio; i++){
        int hour = 10, minute = 0;
        int filmIndex = i, cycle = 0;

        if (display){
            cout << "+" << setfill('-') << setw(60) << "" << "+" << endl;
            cout << left << setfill(' ');
            cout << "| " << dataStudio[i].nama << " (Rp. " << dataStudio[i].harga
                 << setw(47 - dataStudio[i].nama.length()) << ")" << " |" << endl;
            cout << "+" << setfill('-') << setw(60) << "" << "+" << endl;
        }

        while (true){
            int index = filmIndex % maxCurrent;
            jadwal *ptrStudio = &dataStudio[i].dataJadwal[index];

                ptrStudio->judul = currentFilm[index].judul;
                ptrStudio->jamTayang[cycle] = countTime(index, hour, minute);

                if (display){
                    cout << setfill(' ');
                    cout << "| " << ptrStudio->jamTayang[cycle] << " - "
                     << setw(50) << ptrStudio->judul << " |\n";
                }

            filmIndex++;
            if (index == maxCurrent - 1) cycle++;
            if (hour > 21) break;
        }
        if (display)
            cout << "+" << setfill('-') << setw(60) << "" << "+\n";
    }
}

void editFilm(){
    int kodeEdit;
    string line, lineKeep;
    bool ulangEdit = 1;

    while (ulangEdit){
        int i = 1;
        system("cls");
        cout << "EDIT FILM\n\n";

        ifstream file(fileFilm);
        if (file.is_open()){
            while(getline(file, line)){
                splitFileDataFilm(line);
                cout << i << ". " << dataFilm.judul << endl; i++;
            }
        }        
        file.close();
        cout << jmlFilm + 1 << ". Keluar\n";
        cout << "\nPilih judul : "; cin >> kodeEdit;

        if (kodeEdit < 0 || kodeEdit > jmlFilm + 1){
            cout << "\nKode tidak valid" << endl;
            system("pause"); system("cls");
        }else if (kodeEdit == jmlFilm + 1){
            ulangEdit = 0;
        }else{
            string judul, rating, genre, temp[jmlFilm];
            int durasi, pilihEdit, count = 0;
            bool ulangPilih = 1;

            ifstream file(fileFilm);
            if (file.is_open()){
                for (int i = 0; i < kodeEdit; i++){
                    getline(file, line);
                    splitFileDataFilm(line);
                }
            }
            file.close();

            while (ulangPilih){
                system("cls");
                cout << "[1] Judul  : " << dataFilm.judul << endl
                     << "[2] Rating : " << dataFilm.rating << endl
                     << "[3] Genre  : " << dataFilm.genre << endl
                     << "[4] Durasi : " << dataFilm.durasi << endl
                     << "[5] Keluar\n\n";
                cout << "Pilih Edit : "; cin >> pilihEdit; cin.ignore();

                switch (pilihEdit){
                    case 1: cout << "\nJudul baru : "; getline(cin, judul); dataFilm.judul = judul; break;
                    case 2: cout << "\nRating baru : "; getline(cin, rating); dataFilm.rating = rating; break;
                    case 3: cout << "\nGenre baru : "; getline(cin, genre); dataFilm.genre = genre; break;
                    case 4: cout << "\nDurasi baru (menit) : "; cin >> durasi; dataFilm.durasi = durasi; break;
                    case 5: ulangPilih = 0; break;
                    default:
                        cout << "Kode tidak valid" << endl;
                        system("pause");
                }
            }

            ifstream fileUpdate(fileFilm);
            if (fileUpdate.is_open()){
                while (getline(fileUpdate, lineKeep)){
                    if (lineKeep != line){
                        temp[count] = lineKeep; count++;
                    }else{
                        temp[count] = dataFilm.judul + "," +
                                      dataFilm.rating + "," +
                                      dataFilm.genre + "," +
                                      to_string(dataFilm.durasi);
                        count++;
                    }
                }
            }
            fileUpdate.close();

            ofstream fileWrite(fileFilm);
            if (fileWrite.is_open()){
                for (int i = 0; i < count; i++){
                    fileWrite << temp[i] << endl;
                }
            }
            fileWrite.close();
        }
    }
}

void hapusFilm(){
    int kodeHapus, count = 0;
    string line, lineDelete, linesTemp[jmlFilm];
    bool ulangHapus = 1;

    if (jmlFilm <= maxCurrent){
        cout << "\nHarus ada lebih dari " << maxCurrent << " film untuk hapus film";
        if (jmlFilm > 0) cout << "\nHanya ada " << jmlFilm << " terdaftar\n";
        else cout << "Belum ada film terdata\n";
        system("pause");
        return;
    }

    while (ulangHapus){
        int i = 1;
        system("cls");
        cout << "HAPUS FILM\n\n";

        ifstream file(fileFilm);
        if (file.is_open()){
            while(getline(file, line)){
                splitFileDataFilm(line);
                cout << i << ". " << dataFilm.judul << endl; i++;
            }
        }        
        file.close();
        cout << jmlFilm + 1 << ". Keluar\n";
        cout << "\nPilih judul : "; cin >> kodeHapus;

        if (kodeHapus < 0 || kodeHapus > jmlFilm + 1){
            cout << "\nKode tidak valid" << endl;
            system("pause"); system("cls");
        }else if (kodeHapus == jmlFilm + 1){
            ulangHapus = 0;
        }else{
            ifstream fileDelete(fileFilm);
                if (fileDelete.is_open()){
                    for (int i = 0; i < kodeHapus; i++){
                        getline(fileDelete, lineDelete);
                    }
                    fileDelete.seekg(0, ios::beg);
                    while(getline(fileDelete, line)){
                        if (line != lineDelete){
                            linesTemp[count] = line; count++;
                        }
                    } 
                }
            fileDelete.close();

            ofstream fileUpdate(fileFilm);
            if (fileUpdate.is_open()){
                for (int i = 0; i < count; i++){
                    fileUpdate << linesTemp[i] << endl;
                }
                cout << "\nFilm telah dihapus\n"; system("pause");
                jmlFilm--;
                if (kodeHapus > (jmlFilm - maxCurrent)) jadwalChange = 1;
            }
            fileUpdate.close();            
        }
    }
}

void tambahFilm(){
    system("cls");
    
    cout << "TAMBAH FILM\n\n";
    cout << "Judul Film     : "; cin.ignore(); getline(cin, dataFilm.judul);
    cout << "Rating         : "; cin >> dataFilm.rating;
    cout << "Genre          : "; cin.ignore(); getline(cin, dataFilm.genre);
    cout << "Durasi (menit) : "; cin >> dataFilm.durasi;    

    ofstream file(fileFilm, ios::app);
    if (file.is_open()){
        cout << setfill(' ');
        file << dataFilm.judul << ","
             << dataFilm.rating << ","
             << dataFilm.genre << ","
             << to_string(dataFilm.durasi) << endl;

        cout << "\nFilm berhasil ditambahkan\n";
        jmlFilm++; jadwalChange = 1;
        system("pause");
    }
    file.close();
}

void menuEdit(){
    int kodeEdit;
    bool ulangEdit = 1;
        
    while (ulangEdit){
        system("cls");

        if (jadwalChange){
            ofstream fileReset(fileJadwal);
            fileReset.close();
            jadwalChange = 0;
        }

        updateJadwal(0);
        cout << "EDIT INFORMASI JADWAL\n\n";
        cout << "PERHATIAN!\n"
             << "# Bioskop hanya menampilkan " << maxCurrent << " film terbaru\n"
             << "# Jika tambah film baru maka film terlama tidak akan ditayangkan\n"
             << "# Data film lama masih disimpan kecuali dihapus\n\n";
             
        cout << "[1] Tambah Film\n"
             << "[2] Hapus Film\n"
             << "[3] Edit Film\n"
             << "[4] Keluar\n\n";
        cout << "Pilih kode : "; cin >> kodeEdit;
        
        switch (kodeEdit){
            case 1: tambahFilm(); break;
            case 2: hapusFilm(); break;
            case 3: editFilm(); break;
            case 4: ulangEdit = 0; break;
            default:
                cout << "Kode menu tidak valid" << endl;
                system("pause");
        }
    }
}

void sortJadwal(int kodeSort, bool kondisi){
    system("cls");
    bool tukar;    
        
    for (int i = 0; i < maxCurrent - 1; i++){
        for (int j = 0; j < maxCurrent - 1 - i; j++){
            if (kodeSort == 1) tukar = kondisi ?
                (currentFilm[j].judul > currentFilm[j + 1].judul) :
                (currentFilm[j].judul < currentFilm[j + 1].judul);
            else tukar = kondisi ?
                (currentFilm[j].durasi > currentFilm[j + 1].durasi) :
                (currentFilm[j].durasi < currentFilm[j + 1].durasi);

            if (tukar) swap(currentFilm[j], currentFilm[j + 1]);
        }
    }    
    for (int i = 0; i < maxCurrent; i++) {
        cout << i + 1 << ". " << currentFilm[i].judul;
        if (kodeSort == 2) cout << " - " << currentFilm[i].durasi << " menit";
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
        updateJadwal(0);
        cout << "SORT FILM\n\n";
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
    bool found = 0, currentFilm;
    string keyword, line;

    system("cls");
    cout << "Cari Film\n\n";
    cout << "Cari : "; cin.ignore(); getline(cin, keyword);

    ifstream file(fileFilm);
    if (file.is_open()){
        for (int i = 0; i < jmlFilm; i++){
            file.seekg(0, ios::beg);
            for (int j = 0; j < jmlFilm - i; j++){
                getline(file, line);
            }
            splitFileDataFilm(line);
            currentFilm = 0;
            if (dataFilm.judul.find(keyword) != string::npos){
                cout << "\nJudul      : " << dataFilm.judul;
                cout << "\nRating     : " << dataFilm.rating;
                cout << "\nGenre      : " << dataFilm.genre << endl;
                found = 1;

                if (i >= 0 && i < maxCurrent) currentFilm = 1;
                if (currentFilm){
                    cout << "Jam Tayang : ";
                    for (int i = 0; i < maxStudio; i++){
                        for (int j = 0; j < maxCurrent; j++){
                            if (dataFilm.judul == dataStudio[i].dataJadwal[j].judul){
                                for (int k = 0; k < maxShowtimes; k++){
                                    if (!dataStudio[i].dataJadwal[j].jamTayang[k].empty()){
                                        cout << dataStudio[i].dataJadwal[j].jamTayang[k] << " ";
                                    }
                                }
                            }
                        }
                    }
                    cout << endl;
                }
            }
        }

        if (!found) {
            cout << "\nFilm tidak ditemukan";
        }
        cout << endl;
        system("pause");
    }    
}

void viewCurrentFilm(){
    system("cls");
    cout << "NOW PLAYING\n\n";

    for (int i = 0; i < maxCurrent; i++){
        cout << "+" << setfill('-') << setw(52) << "" << "+" << endl;
        cout << left << setfill(' ');
        cout << "| " << setw(50) << currentFilm[i].judul << " |\n"
             << "| Durasi: " << setw(5) << currentFilm[i].durasi
             << "Rating: " << setw(10) << currentFilm[i].rating
             << "Genre: " << setw(12) << currentFilm[i].genre << " |\n";
        cout << "+" << setfill('-') << setw(52) << "" << "+" << endl;
    }
    system("pause");
}

void cetakTiket(int studio, int film, int tayang){
    system ("cls");
    int baris, kolom;
    penonton *ptrPenonton = &dataPenonton;

    cout << "Selamat menikmati film!\n\n";
    for (int i = 0; i < rows * cols; i++){
        if (!ptrPenonton->baris[i].empty()){

            cout << "+" << setfill('-') << setw(65) << "" << "+" << endl;
            cout << left << setfill(' ');
            cout << setw(65) << "| Bioskop X " << " |";
            cout << "\n| Film       : " << setw(50) << dataStudio[studio].dataJadwal[film].judul << " |"
                 << "\n| Jam Tayang : " << setw(50) << dataStudio[studio].dataJadwal[film].jamTayang[tayang] << " |"
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

void deleteAllSeat(int studio, int film, int tayang, int &seatSold){
    string temp[27 * (rows * cols)], line;
    int count = 0;
    seatSold = 0;

    ifstream fileDelete(fileJadwal);
        if (fileDelete.is_open()){
            while(getline(fileDelete, line)){
                splitFileDataJadwal(line);
                if (!(tempDataStudio.nama == dataStudio[studio].nama &&
                    tempDataStudio.judul == dataStudio[studio].dataJadwal[film].judul &&
                    tempDataStudio.tayang == dataStudio[studio].dataJadwal[film].jamTayang[tayang])){
                    temp[count] = line; count++;
                }
            } 
        }
    fileDelete.close();

    ofstream fileUpdate(fileJadwal);
    if (fileUpdate.is_open()){
        for (int i = 0; i < count; i++){
            fileUpdate << temp[i] << endl;
        }
    }
    fileUpdate.close();
}

void deleteSeat(int studio, int film, int tayang, int &indexSeat, int &seatSold){
    int baris, kolom, count = 0;
    seats *ptrSeats = &dataStudio[studio].dataJadwal[film].seats[tayang];
    penonton *ptrPenonton = &dataPenonton;
    string temp[27 * (rows * cols)], line;

    displaySeats(studio, film, tayang);
    cout << "\nInput baris & kolom (contoh: 5 7)\n";
    cout << "Pilih kursi : "; cin >> baris >> kolom;

    if (ptrSeats->seatsDisplay[baris - 1][kolom - 1] == "|   "){
        cout << "\nKursi sudah kosong\n";
        system("pause");
        return;
    }

    ptrSeats->seatsDisplay[baris - 1][kolom - 1] = "|   ";
    for (int i = 0; i < rows * cols; i++){
        if (ptrPenonton->baris[i] == to_string(baris) && ptrPenonton->kolom[i] == to_string(kolom))
            ptrPenonton->baris[i] = "";
            ptrPenonton->kolom[i] = "";
    }
    seatSold--; indexSeat--;

    ifstream fileDelete(fileJadwal);
    if (fileDelete.is_open()){
        while(getline(fileDelete, line)){
            splitFileDataJadwal(line);
            if (!(tempDataStudio.nama == dataStudio[studio].nama &&
                  tempDataStudio.judul == dataStudio[studio].dataJadwal[film].judul &&
                  tempDataStudio.tayang == dataStudio[studio].dataJadwal[film].jamTayang[tayang] &&
                  tempDataStudio.baris == to_string(baris - 1) &&
                  tempDataStudio.kolom == to_string(kolom - 1))){
                temp[count] = line; count++;
            }
        } 
    }
    fileDelete.close();

    ofstream fileUpdate(fileJadwal);
    if (fileUpdate.is_open()){
        for (int i = 0; i < count; i++){
            fileUpdate << temp[i] << endl;
        }
    }
    fileUpdate.close();
}

void addSeat(int studio, int film, int tayang, int &indexSeat, int &seatSold){
    int baris, kolom;
    seats *ptrSeats = &dataStudio[studio].dataJadwal[film].seats[tayang];
    penonton *ptrPenonton = &dataPenonton;

    displaySeats(studio, film, tayang);
    cout << "\nInput baris & kolom (contoh: 5 7)\n";
    cout << "Pilih kursi : "; cin >> baris >> kolom;

    if (ptrSeats->seatsDisplay[baris - 1][kolom - 1] == "| X "){
        cout << "\nKursi sudah terpakai\n\n";
        system("pause");
        return;
    }
    
    ptrSeats->seatsDisplay[baris - 1][kolom - 1] = "| X ";
    ptrPenonton->baris[indexSeat] = to_string(baris);
    ptrPenonton->kolom[indexSeat] = to_string(kolom);
    seatSold++; indexSeat++;

    ofstream file(fileJadwal, ios::app);
    if (file.is_open()){
        file << dataStudio[studio].nama << ","
             << dataStudio[studio].dataJadwal[film].judul << ","
             << dataStudio[studio].dataJadwal[film].jamTayang[tayang] << ","
             << dataStudio[studio].dataJadwal[film].seats[tayang].seatsDisplay[baris - 1][kolom - 1] << ","
             << to_string(baris - 1) << ","
             << to_string(kolom - 1) << endl;
    }
    file.close();

}

void updateSeats(){
    string line;
    seats *ptrSeats;

    for (int i = 0; i < maxStudio; i++){
        for (int j = 0; j < maxCurrent; j++){
            for (int k = 0; k < maxShowtimes; k++){
                ptrSeats = &dataStudio[i].dataJadwal[j].seats[k];
                for (int i = 0; i < rows; i++){
                    for (int j = 0; j < cols; j++){
                        ptrSeats->seatsDisplay[i][j] = "|   ";
                    }
                }
            }
        }
    }

    ifstream file(fileJadwal);
    if (file.is_open()){
        while (getline(file, line)){
            splitFileDataJadwal(line);            

            for (int i = 0; i < maxStudio; i++){
                if (dataStudio[i].nama == tempDataStudio.nama){
                    for (int j = 0; j < maxCurrent; j++){
                        if (dataStudio[i].dataJadwal[j].judul == tempDataStudio.judul){
                            for (int k = 0; k < maxShowtimes; k++){
                                if (dataStudio[i].dataJadwal[j].jamTayang[k] == tempDataStudio.tayang){
                                    ptrSeats = &dataStudio[i].dataJadwal[j].seats[k];
                                    ptrSeats->seatsDisplay[stoi(tempDataStudio.baris)][stoi(tempDataStudio.kolom)] = "| X ";
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    file.close();
}

void menuSeats(int studio, int film, int tayang){
    int indexSeat = 0, kodeSeats, seatSold = 0, temp = seatSold;
    bool ulangSeats = 1;
    seats *ptrSeats = &dataStudio[studio].dataJadwal[film].seats[tayang];
    penonton *ptrPenonton = &dataPenonton;

    while (ulangSeats){
        updateSeats();
        displaySeats(studio, film, tayang);
        cout << "\n[1] Tambah kursi"
             << "\n[2] Hapus kursi"
             << "\n[3] Hapus semua"
             << "\n[4] Keluar\n\n";
        cout << "Pilih menu: "; cin >> kodeSeats;

        switch (kodeSeats){
            case 1: addSeat(studio, film, tayang, indexSeat, seatSold); break;
            case 2: deleteSeat(studio, film, tayang, indexSeat, seatSold); break;
            case 3: deleteAllSeat(studio, film, tayang, seatSold); break;
            case 4: ulangSeats = 0; break;
            default:
                cout << "Kode menu tidak valid" << endl;
                system("pause");
        }
    }
    if (seatSold > temp){
        cetakTiket(studio, film, tayang);
    }
}

void pilihJadwal() {
    system("cls");
    int studio, film, tayang, count = 1;
    updateSeats();

    cout << "Studio\n";
    for (int i = 0; i < maxStudio; i++){
        cout << i + 1 << ". " << dataStudio[i].nama << endl;
    }
    cout << maxStudio + 1 << ". Keluar" << endl;
    cout << "\nPilih Studio : "; cin >> studio;
    if (studio == maxStudio + 1) return;

    system("cls"); cout << "Film\n";
    for (int i = 0; i < maxCurrent; i++){
        cout << i + 1 << ". " << dataStudio[studio - 1].dataJadwal[i].judul << endl;
    }
    cout << maxCurrent + 1 << ". Keluar" << endl;
    cout << "\nPilih Film : "; cin >> film;
    if (film == maxCurrent + 1) return;

    system("cls"); cout << "Jam Tayang\n";    
    for (int i = 0; i < maxShowtimes; i++){
        if (!dataStudio[studio - 1].dataJadwal[film - 1].jamTayang[i].empty()){
            cout << count << ". " << dataStudio[studio - 1].dataJadwal[film - 1].jamTayang[i] << endl;
            count++;
        }
    }
    cout << count << ". Keluar" << endl;
    cout << "\nKode Jam Tayang : "; cin >> tayang;
    if (tayang == count) return;
    
    menuSeats(studio - 1, film - 1, tayang - 1);    
}

void menuUtama() {
    int kodeMenu;
    bool ulangUtama = 1;

    while (ulangUtama){
        system("cls");
        updateJadwal(0);
        cout << "MENU UTAMA\n";
        cout << "\n[1] Lihat Jadwal"
             << "\n[2] Cetak Tiket"
             << "\n[3] Now Playing"
             << "\n[4] Cari Film"
             << "\n[5] Sort Film"
             << "\n[6] Manage Film"
             << "\n[7] Keluar\n";
        cout << "\nPilih menu : "; cin >> kodeMenu;

        switch (kodeMenu) {
            case 1: updateJadwal(1); system("pause"); break;
            case 2: pilihJadwal(); break;
            case 3: viewCurrentFilm(); break;
            case 4: cariFilm(); break;
            case 5: menuSort(); break;
            case 6: menuEdit(); break;
            case 7: ulangUtama = 0; break;
            default:
                cout << "Kode menu tidak valid" << endl;
                system("pause");
        }
    }
}

void login(bool &ulangMasuk, int limitLogin){
    string usn, pass, line;
    bool ulangLogin = 1, terdaftar = 0;

    if (jmlStaff == 0) {
        cout << "\nBelum ada pengguna yang terdaftar, mohon daftar terlebih dahulu\n";
        system("pause");
        return;
    }

    if (limitLogin == 0){
        ulangMasuk = 0;
        return;
    }

    system("cls");
    cout << "MASUK\n\n";
    cout << "Username : "; cin >> usn;
    cout << "Password : "; cin >> pass;

    ifstream file(fileStaff);
    if (file.is_open()){
        for (int i = 0; i <= jmlStaff; i++){
            getline(file, line);
            splitFileDataStaff(line);
            if (usn == dataStaff.usn && pass == dataStaff.pass){
                cout << "\nBerhasil masuk\n";
                ulangLogin = 0;
                system("pause");
                menuUtama();
            }        
            if (usn == dataStaff.usn) terdaftar = 1;
        }    

        if (ulangLogin){
            if (!terdaftar){
                cout << "\nUsername Anda belum terdaftar, mohon daftar terlebih dahulu\n";
                system("pause");
                return;
            }
            cout << "\nLogin gagal, kesempatan Anda tersisa " << limitLogin - 1 << endl;
            system("pause");
            login(ulangMasuk, limitLogin - 1);
        }
    }
}

void signup() {
    string line;
    string nama, usn, pass;

    system("cls");
    cout << "DAFTAR\n\n";
    cout << "Nama     : "; cin.ignore(); getline(cin, nama);
    cout << "Username : "; cin >> usn;
    cout << "Password : "; cin >> pass;

    ifstream fileRead(fileStaff);
    if (fileRead.is_open()){
        for (int i = 0; i < jmlStaff; i++){
            getline(fileRead, line);
            splitFileDataStaff(line);
            if (usn == dataStaff.usn) {
                cout << "\nUsername tidak tersedia. Silakan coba username lain.\n";
                system("pause");
                return;
            }
        }
    }
    fileRead.close();

    ofstream fileWrite(fileStaff, ios::app);
    if (fileWrite.is_open()){
        fileWrite << nama << "," << usn << "," << pass << endl;
        cout << "\nBerhasil daftar\n";
        jmlStaff++;
        system("pause");
    }
    fileWrite.close();
}

void menuMasuk() {
    int kodeMasuk, limitLogin = 5;
    bool ulangMasuk = 1;

    while (ulangMasuk) {
        system("cls");
        cout << "SISTEM BIOSKOP X\n";
        cout << "\n[1] Masuk";
        cout << "\n[2] Daftar";
        cout << "\n[3] Keluar\n";
        cout << "\nPilih menu: "; cin >> kodeMasuk;

        switch (kodeMasuk) {
            case 1: login(ulangMasuk, limitLogin); break;
            case 2: signup(); break;
            case 3: ulangMasuk = 0; break;
            default:
                cout << "Kode tidak valid\n";
                system("pause");
        }
    }
}

main() {
    string line;

    ifstream fileF(fileFilm);
    if (fileF.is_open()){
        while (getline(fileF, line)){
            jmlFilm++;
        }
    }
    fileF.close();

    ifstream fileS(fileStaff);
    if (fileS.is_open()){
        while (getline(fileS, line)){
            jmlStaff++;
        }
    }
    fileS.close();

    menuMasuk();
}