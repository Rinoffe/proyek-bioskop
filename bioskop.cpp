#include <iostream>
using namespace std;

struct {
    string nama, usn, pass;
} staff[100];

void login(int &daftar){
    string nama, usn, pass;
    bool ulangMasuk = 1;

    system("cls");
    cout << "MASUK\n\n";
    cout << "Username : "; cin >> usn;
    cout << "Password : "; cin >> pass;

    for (int i = 0; i < daftar; i++){
        if ((usn == staff[i].usn) && (pass == staff[i].pass)){
            cout << "\nBerhasil masuk\n"; system("pause");
            ulangMasuk = 0;
            // lanjut
        }
    }

    if (ulangMasuk){
        cout << "\nGagal masuk\n";
        system("pause"); system("cls");
        login(daftar);
    }       
}

void signup(int &daftar){
    bool berhasil = 1;
    
    system("cls");
    cout << "DAFTAR\n\n";
    cout << "Nama     : "; cin.ignore(); getline(cin, staff[daftar].nama);
    cout << "Username : "; cin >> staff[daftar].usn;
    cout << "Password : "; cin >> staff[daftar].pass;

    for (int i = 0; i < daftar; i++){
        if (staff[daftar].usn == staff[i].usn){
            cout << "\nUsername tidak tersedia\n";
            berhasil = 0;
            system("pause"); system("cls");
            signup(daftar);
        }
    }

    if (berhasil){
        cout << "\nBerhasil daftar\n";
        daftar++;
        system("pause"); system("cls");
    }    
}

void masuk(int daftar){
    int kodeMasuk;

    cout << "SISTEM BIOSKOP X\n\n";
    cout << "[1] Masuk\n";
    cout << "[2] Daftar\n";
    cout << "Pilih : "; cin >> kodeMasuk;

    switch (kodeMasuk){
        case 1:
            if (daftar == 0){
                cout << "\nBelum ada pengguna yang terdaftar, mohon daftar terlebih dahulu\n";
                system("pause"); system("cls");
            }else{
                login(daftar);
            }
        break;
        case 2:
            signup(daftar);
        break;
        default:
            cout << "Kode tidak valid\n";
            system("pause"); system("cls");
        }
    masuk(daftar);
}

main (){
    int  daftar = 0;
    masuk(daftar);
}