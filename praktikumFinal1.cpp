// TERBARU
#include<iostream>
#include<ctime>
#include <vector>
#include <sstream>
#include <unordered_map>
using namespace std;

struct dataSupir {
    int id;
    string nama;
    string tglLahir;
    char kelamin;
    string alamat;
    dataSupir* next;
};

dataSupir* head = NULL;

dataSupir* cariSupirById(int id) {
    dataSupir* current = head;

    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

string generateId(string nama, char kelamin, string tglLahir, unordered_map<string, int>& idMap) {
    // Menghitung nilai 2 digit pertama
    int hurufPertama = nama.front();
    int hurufTerakhir = nama.back();
    int duaDigitPertama = abs(hurufPertama - hurufTerakhir);

    // Menghitung nilai digit ketiga
    int digitKetiga = (kelamin == 'l') ? 1 : 0;

    // Menghitung nilai digit keempat
    vector<string> splitTglLahir;
    stringstream ss(tglLahir);
    string token;

    while (getline(ss, token, '-')) {
        splitTglLahir.push_back(token);
    }

    // Mengambil hanya angka terakhir dari setiap bagian
    char day = splitTglLahir[0].back();
    char month = splitTglLahir[1].back();
    char year = splitTglLahir[2].back();

    int digitKeempat = (day - '0' + month - '0' + year - '0') % 9;

    // Menghitung nilai digit kelima dengan menangani duplikasi
    int digitKelima = 0;
    string idAwal = (duaDigitPertama < 10 ? "0" : "") + to_string(duaDigitPertama) + to_string(digitKetiga) + to_string(digitKeempat);
    while (idMap.find(idAwal + to_string(digitKelima)) != idMap.end()) {
        digitKelima++;
        if (digitKelima == 9) {
        // Menambah digit jika mencapai 9
        idAwal += to_string(digitKelima);
        digitKelima = 0;
        }
    }

    // Menggabungkan nilai-nilai menjadi sebuah string
    string id = idAwal + to_string(digitKelima);

    // Menambahkan ID ke dalam map
    idMap[id] = 1;
    
    return id;
}

int main() {
    bool ulang = false;

    cout<<"=============================="<<endl;   
    cout<<"     Selamat Datang!"<<endl;
    cout<<"=============================="<<endl;   
    while(ulang == false) {
        cout<<"1. Masuk Sebagai Admin"<<endl;
        cout<<"2. Masuk Sebagai User"<<endl;
        cout<<"3. Exit"<<endl;
        int inputAwal;
        cin>>inputAwal;

        if(inputAwal == 1) {
            bool exitDasboarMenu = false;
            while (!exitDasboarMenu) {
                cout<<"==== Dashboard Admin ===="<<endl<<endl;
                cout<<"1. Mencari Data Supir"   <<endl;
                cout<<"2. Menghapus Dasboard"   <<endl;
                cout<<"3. Mengubah Data Supir"  <<endl;
                cout<<"4. Menambah Data Supir"  <<endl;
                cout<<"0. Kembali ke-Dasboard"<<endl;
                int inputDasboard;
                cin>>inputDasboard;

                if(inputDasboard == 1) {
                    // Implementasikan pencarian data supir
                    dataSupir* current = head;


                    bool exitUserMenu = false;
                    while (!exitUserMenu) {
                        if (current == NULL) {
                            cout << "Data supir kosong." << endl;
                            break;
                        }

                        cout << "|-------------------------|" << endl;
                        cout << "|Nama     : " << current->nama << endl;
                        cout << "|Id       : " << current->id << endl;
                        cout << "|Tgl Lahir: " << current->tglLahir << endl;
                        cout << "|Kelamin  : " << ((current->kelamin == 'l') ? "Laki-Laki" : "Perempuan") << endl;
                        cout << "|Alamat   : " << current->alamat << endl;
                        cout << "|-------------------------|" << endl;
                        cout << "1. Next" << endl;
                        cout << "2. Previous" << endl;
                        cout << "3. Order" << endl;
                        cout << "0. Exit" << endl;

                        int inputUser;
                        cin >> inputUser;

                        if(inputUser == 1) {
                            // Pindah ke supir berikutnya
                            if (current->next != NULL) {
                                current = current->next;
                            } else {
                                cout << "Anda sudah berada di supir terakhir." << endl;
                            }
                        } else if(inputUser == 2) {
                            // Pindah ke supir sebelumnya
                            if (current != head) {
                                dataSupir* temp = head;
                                while (temp->next != current) {
                                    temp = temp->next;
                                }
                                current = temp;
                            } else {
                                cout << "Anda sudah berada di supir pertama." << endl;
                            }
                        } else if(inputUser == 3) {
                            // Implementasi order (sementara tidak melakukan apa-apa)
                            cout << "Ini Order" << endl;
                        } else if(inputUser == 0) {
                            exitUserMenu = true;
                        } else {
                            cout << "Pilihan tidak valid!" << endl;
                            break;
                        }
                    }

                } else if(inputDasboard == 2) {
                    // Implementasikan penghapusan dashboard
                    cout << "Masukkan Id Supir yang ingin dihapus > ";
                    int idHapus;
                    cin >> idHapus;

                    dataSupir* current = head;
                    dataSupir* previous = NULL;

                    while (current != NULL) {
                        if (current->id == idHapus) {
                            if (previous == NULL) {
                                // Jika data yang dihapus adalah data pertama
                                head = current->next;
                            } else {
                                previous->next = current->next;
                            }

                            cout << "Supir dengan Id " << idHapus << " berhasil dihapus!" << endl;
                            delete current;
                            current = NULL;
                            break;
                        }

                        previous = current;
                        current = current->next;
                        break;
                    }

                    if (current == NULL) {
                        cout << "Supir dengan Id " << idHapus << " tidak ditemukan." << endl;
                    }

                } else if(inputDasboard == 3) {
                    // Implementasikan pengubahan data supir
                    cout << "Masukkan Id Supir yang ingin diubah > ";
                    int idUbah;
                    cin >> idUbah;
                    // ubahDataSupir(idUbah);
                    dataSupir* supir = cariSupirById(idUbah);

                    if (supir != NULL) {
                        cout<<"1. Ubah Nama"        <<endl;
                        cout<<"2. Ubah Kelamin"     <<endl;
                        cout<<"3. Ubah Alamat"      <<endl;
                        cout<<"4. Ubah Tgl Lahir"   <<endl;
                        cout<<"0. Kembali ke menu Dasboard Admin"<<endl;
                        int inputUbah;
                        cin >> inputUbah;

                        bool exitUbah = false;
                        while(!exitUbah) {
                            if(inputUbah == 1) {
                                cout << "Masukkan Nama yang baru > ";
                                cin.ignore();
                                getline(cin, supir->nama);
                                break;
                            } else if(inputUbah == 2) {
                                cout << "Masukkan Kelamin yang baru (l/p) > ";
                                cin >> supir->kelamin;
                                break;
                            } else if(inputUbah == 3) {
                                cout << "Masukkan Alamat yang baru > ";
                                cin.ignore();
                                getline(cin, supir->alamat);
                                break;
                            } else if(inputUbah == 4) {
                                cout << "Masukkan Tgl Lahir yang baru (dd-mm-yy) > ";
                                cin >> supir->tglLahir;
                                break;
                            } else if(inputUbah == 0) {
                                break;
                            } else {
                                cout << "Pilihan tidak valid!" << endl;
                                break;
                            }
                        cout << "Data Id " <<idUbah<< " telah berubah!" << endl;

                        // tampilkanDataSupir
                        }
                    } else {
                        cout<<"Data Id "<<idUbah<<" tidak ditemukan!"<<endl;
                    }

                } else if (inputDasboard == 4) {
                    // Penambahan data supir
                    cout << "Masukkan Nama > ";
                    string nama;
                    cin.ignore();
                    getline(cin, nama);
                    cout << "Masukkan Tgl Lahir (dd-mm-yy) > ";
                    string tglLahir;
                    cin >> tglLahir;
                    cout << "Masukkan Kelamin (l/p) > ";
                    char kelamin;
                    cin >> kelamin;
                    cout << "Masukkan Alamat > ";
                    string alamat;
                    cin.ignore();
                    getline(cin, alamat);

                   // Generate Id
                    unordered_map<string, int> idMap;
                    string id = generateId(nama, kelamin, tglLahir, idMap);

                    dataSupir* newSupir = new dataSupir;
                    newSupir->nama = nama;
                    newSupir->tglLahir = tglLahir;
                    newSupir->kelamin = kelamin;
                    newSupir->alamat = alamat;
                    newSupir->id = stoi(id, nullptr, 10);

                    // Tambahkan ke linked list
                    newSupir->next = head;
                    head = newSupir;

                    cout << "Data berhasil ditambahkan !" << endl;
                    
                } else if(inputDasboard == 0) {
                    exitDasboarMenu = true;
                } else {
                    cout << "Pilihan tidak valid!" << endl;
                    break;
                }
            } 
            //End Input Awal 1
            
        } else if(inputAwal == 2) {
            cout<<"|-----------------------------|"<<endl;
            cout<<"| Nama       : Kim Jatim Park |"<<endl;
            cout<<"| Id         : 01234          |"<<endl;
            cout<<"| Tgl Lahir  : 12-02-2001     |"<<endl;
            cout<<"| Kelamin    : Laki-Laki      |"<<endl;
            cout<<"| Alamat     : Surabaya       |"<<endl;
            cout<<"|-----------------------------|"<<endl;
            cout<<"1. Next"     <<endl;
            cout<<"2. Previous" <<endl;
            cout<<"3. Order"    <<endl;
            cout<<"4. Exit"     <<endl;
            int inputUser;
            cin>>inputUser;
            
            bool exitUserInput = false;
            while(!exitUserInput) {
                if(inputUser == 1) {
                    cout<<"Ini Next"<<endl;
                    break;
                } else if(inputUser == 2) {
                    cout<<"Ini Previous"<<endl;
                    break;
                } else if(inputUser == 3) {
                    cout<<"Ini Order"<<endl;
                    break;
                } else if(inputUser == 4) {
                    exitUserInput = true;
                } else {
                    cout<<"Input yang anda masukkan tidak valid!"<<endl;
                    break;
                }
            }
            // End input 2

        } else if (inputAwal == 3) {
            break;
        } else {
            cout<<"Input tidak valid!"<<endl;
            break;
        }
    }  
}