// TERBARU
#include<iostream>
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

struct dataOrder {
    int id;
    string nama;
    string supir;
    string platNomor;
    string tujuan;
    dataOrder* next;
};

dataOrder* antrianPesanan = NULL;
int nomorPesanan = 1;


struct dataMobil {
    string platNomor;
    string jenisMobil;
    string brandMobil;
    dataMobil* prev;
    dataMobil* next;
};

dataMobil* top = NULL;

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
                cout<<"5. Proses Pesanan"       <<endl;
                cout<<"6. Tambah Unit Mobil"    <<endl;
                cout<<"7. Cek Unit Mobil"    <<endl;
                cout<<"0. Exit"                 <<endl;
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
                        cout << "4. Exit" << endl;

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
                        } else if(inputUser == 4) {
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

                    if (current == NULL) {
                        cout << "Supir dengan Id " << idHapus << " tidak ditemukan." << endl;
                        break;
                    }

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
                                // Perubahan dua digit pertama jika yang diubah adalah nama
                                int digitHurufPertamaBaru = supir->nama[0] - 'a' + 1;
                                int digitHurufTerakhirBaru = supir->nama[supir->nama.length() - 1] - 'a' + 1;
                                int duaDigitPertamaTempBaru = abs(digitHurufPertamaBaru - digitHurufTerakhirBaru);
                                string duaDigitPertamaBaru;
                                if(duaDigitPertamaTempBaru < 10) {
                                    duaDigitPertamaBaru = "0" + to_string(duaDigitPertamaTempBaru);
                                } else {
                                    duaDigitPertamaBaru = to_string(duaDigitPertamaTempBaru);
                                }

                                // Update dua digit pertama pada ID
                                string duaDigitBaru = duaDigitPertamaBaru + to_string(supir->id).substr(1);
                                supir->id = stoi(duaDigitBaru);
                                break;

                            } else if(inputUbah == 2) {
                                cout << "Masukkan Kelamin yang baru (l/p) > ";
                                cin >> supir->kelamin;

                                // Perubahan digit ketiga jika yang diubah adalah kelamin
                                int digitKetigaTempBaru = 0;
                                if(supir->kelamin == 'l') {
                                    digitKetigaTempBaru += 1;
                                } else if (supir->kelamin == 'p') {
                                    digitKetigaTempBaru += 0;
                                }

                                // Update digit ketiga pada ID
                                string duaDigitPertama = to_string(supir->id).substr(0, 1);
                                string digitTiga = to_string(digitKetigaTempBaru);
                                string digitSelanjutnya = to_string(supir->id).substr(2);
                                supir->id = stoi(duaDigitPertama + digitTiga + digitSelanjutnya);
                                break;
                            } else if(inputUbah == 3) {
                                cout << "Masukkan Alamat yang baru > ";
                                cin.ignore();
                                getline(cin, supir->alamat);
                                break;
                            } else if(inputUbah == 4) {
                                cout << "Masukkan Tgl Lahir yang baru (dd-mm-yy) > ";
                                cin >> supir->tglLahir;

                                // Perubahan digit keempat jika yang diubah adalah tanggal lahir
                                int tanggalBaru = stoi(supir->tglLahir.substr(1));
                                int bulanBaru = stoi(supir->tglLahir.substr(4));
                                int tahunBaru = stoi(supir->tglLahir.substr(supir->tglLahir.length() - 1));

                                int digitKeEmpatTempBaru = (tanggalBaru + bulanBaru + tahunBaru) % 9;

                                // Update digit keempat pada ID
                                string tigaDigitPertama = to_string(supir->id).substr(0, 2);
                                string digitKeEmpatBaru = to_string(digitKeEmpatTempBaru);
                                string digitSelanjutnya = to_string(supir->id).substr(3);
                                supir->id = stoi(tigaDigitPertama + digitKeEmpatBaru + digitSelanjutnya);
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

                    // tambahDataSupir(nama, tglLahir, kelamin, alamat);
                    dataSupir* newSupir = new dataSupir;
                    newSupir->nama = nama;
                    newSupir->tglLahir = tglLahir;
                    newSupir->kelamin = kelamin;
                    newSupir->alamat = alamat;

                    // Generate Id
                    // dua digit pertama
                    int digitHurufPertama = nama[0] - 'a' + 1;
                    int digitHurufTerakhir = nama[nama.length() - 1] - 'a' + 1;
                    int duaDigitPertamaTemp = abs(digitHurufPertama - digitHurufTerakhir);
                    string duaDigitPertama;
                    if(duaDigitPertamaTemp < 10) {
                        duaDigitPertama = "0" + to_string(duaDigitPertamaTemp);
                    } else {
                        duaDigitPertama = to_string(duaDigitPertamaTemp);
                    }

                    // digit ke-tiga
                    int digitKetigaTemp = 0;
                    if(kelamin == 'l') {
                        digitKetigaTemp += 1;
                    } else if (kelamin == 'p') {
                        digitKetigaTemp += 0;
                    }
                    string digitKetigaString = to_string(digitKetigaTemp);

                    // digit ke-empat
                    int tanggal = stoi(tglLahir.substr(1));
                    int bulan = stoi(tglLahir.substr(4));
                    int tahun = stoi(tglLahir.substr(tglLahir.length() - 1));

                    int digitKeEmpatTemp = (tanggal + bulan + tahun) % 9;
                    string digitKeEmpat = to_string(digitKeEmpatTemp);

                    // gabungan empat digit
                    string digitEmpat = duaDigitPertama + digitKetigaString + digitKeEmpat;

                    // digit ke lima
                    int digitKelima = 0;
                    unordered_map<string, int> idMap;
                    while (idMap.find(digitEmpat + to_string(digitKelima)) != idMap.end()) {
                        digitKelima++;
                        if (digitKelima == 9) {
                        // Menambah digit jika mencapai 9
                        digitEmpat += to_string(digitKelima);
                        digitKelima = 0;
                        }
                    }
                    string idString = digitEmpat + to_string(digitKelima);
                    int id = stoi(idString);

                    newSupir->id = id;

                    // Tambahkan ke linked list
                    newSupir->next = head;
                    head = newSupir;

                    cout << "Data berhasil ditambahkan !" << endl;
                    
                } else if (inputDasboard == 5) {
                    if(antrianPesanan != NULL) {
                        dataOrder* pesananSaatIni = antrianPesanan;
                        int nomorPesanan = 1;
                    
                        while(pesananSaatIni != NULL) {
                            cout<<"---Pesanan ke-"<<nomorPesanan<<"---"<<endl;
                            cout<<"Id         :"<<to_string(pesananSaatIni->id)<<endl;
                            cout<<"Nama       :"<<pesananSaatIni->nama<<endl;
                            cout<<"Supir      :"<<pesananSaatIni->supir<<endl;
                            cout<<"Plat nomor :"<<pesananSaatIni->platNomor<<endl;
                            cout<<"Tujuan     :"<<pesananSaatIni->tujuan<<endl;
                            cout<<endl;
                            cout<<"1. Accept"<<endl;
                            cout<<"2. Reject"<<endl;
                            cout<<"0. Exit"<<endl;

                            int inputPesanan;
                            cin>>inputPesanan;

                            if(inputPesanan == 1) {
                                cout<<"Pesanan dengan Id "<<pesananSaatIni->id<<" telah diproses !!"<<endl;
                                dataOrder* temp = pesananSaatIni;
                                pesananSaatIni = pesananSaatIni->next;
                                delete temp;
                                nomorPesanan++;
                            } else if(inputPesanan == 2) {
                                cout<<"Pesanan dengan Id "<<pesananSaatIni->id<<" telah ditolak !!"<<endl;
                                dataOrder* temp = pesananSaatIni;
                                pesananSaatIni = pesananSaatIni->next;
                                delete temp;
                                nomorPesanan++;
                            } else if(inputPesanan == 0) {
                                break;
                            } else {
                                cout<<"Input yang anda masukkan salah"<<endl;
                                break;
                            }
                        }
                        antrianPesanan = NULL;
                    } else {
                        cout<<"Tidak Ada Pesanan"<<endl;
                    }


                } else if (inputDasboard == 6){
                    bool exitTambahUnit = false;
                    while (!exitTambahUnit) {
                        string platNomor, jenisMobil, brandMobil;
                        cout << "Masukkan plat nomor mobil > ";
                        cin.ignore();
                        getline(cin, platNomor);
                        cout << "Masukkan jenis mobil > ";
                        getline(cin, jenisMobil);
                        cout << "Masukkan brand mobil > ";
                        getline(cin, brandMobil);

                        dataMobil* newNode = new dataMobil;
                        newNode->platNomor = platNomor;
                        newNode->jenisMobil = jenisMobil;
                        newNode->brandMobil = brandMobil;
                        newNode->next = top;
                        top = newNode;
                        
                        cout << "Data berhasil dimasukkan !!" << endl;
                        cout << "Ingin menambahkan unit lain? (y/n) > ";
                        char pilihan;
                        cin >> pilihan;
                        if (pilihan == 'n') {
                            exitTambahUnit = true;
                        }
                    }
                } else if (inputDasboard == 7) {
                    dataMobil* current = top;

                    bool exitUserMenu = false;
                    while (!exitUserMenu) {
                        if (current == NULL) {
                            cout << "Mobil kosong" << endl;
                            break;
                        }

                        cout << "Plat Nomor  : "<<current->platNomor << endl;
                        cout << "Jenis Mobil : "<<current->jenisMobil << endl;
                        cout << "Brand Mobil : "<<current->brandMobil << endl;
                        cout << "1. Next" << endl;
                        cout << "2. Previous" << endl;
                        cout << "0. Exit" << endl;

                        int inputUser;
                        cin >> inputUser;

                        if(inputUser == 1) {
                            // Pindah ke supir berikutnya
                            if (current->next != NULL) {
                                current = current->next;
                            } else {
                                cout << "Anda sudah berada di data mobil terakhir." << endl;
                            }
                        } else if(inputUser == 2) {
                            // Pindah ke supir sebelumnya
                            if (current != top) {
                                dataMobil* temp = top;
                                while (temp->next != current) {
                                    temp = temp->next;
                                }
                                current = temp;
                            } else {
                                cout << "Anda sudah berada di data mobil pertama." << endl;
                            }
                        } else if(inputUser == 0) {
                            exitUserMenu = true;
                        } else {
                            cout << "Pilihan tidak valid!" << endl;
                            break;
                        }
                    }
                } else if (inputDasboard == 0) {
                    exitDasboarMenu = true;
                } else {
                    cout << "Pilihan tidak valid!" << endl;
                    break;
                }
            } 
            //End Input Awal 1
            
        } else if(inputAwal == 2) {
            dataSupir* current = head;
            // 
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
                cout << "4. Exit" << endl;

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
                    dataMobil* curr = top;

                    bool exitOrder = false;
                    while(!exitOrder) {
                        string platNomor; 
                        if (curr == NULL) {
                            cout << "Unit Mobil kosong" << endl;
                            break;
                        } else {
                            platNomor = curr->platNomor;
                            curr = curr->next;
                        }

                        cout<<"Masukkan nama pelanggan : ";
                        string namaPelanggan;
                        cin.ignore();
                        getline(cin, namaPelanggan);

                        cout<<"Tujuan pelanggan : ";
                        string tujuanPelanggan;
                        cin.ignore();
                        getline(cin, tujuanPelanggan);

                        int digitDuaPertama = platNomor[0] - 'A' + 1;
                        int digitLimaSelanjutnya = current->id;
                        int digitDuaSelanjutnya = (tujuanPelanggan[tujuanPelanggan.length() - 1] - 'a' + 1) + (tujuanPelanggan[tujuanPelanggan.length() - 2] - 'a' + 1);

                        int total = 0;
                        for(int i = 0; i < namaPelanggan.length(); i++) {
                            total += namaPelanggan[i] - 'a' + 1;
                        };
                        
                        string digitTerakhirString;
                        string totalString = to_string(total);
                        if (totalString.length() > 1) {
                            digitTerakhirString = totalString.substr(totalString.length() - 1);
                        } else {
                            digitTerakhirString = totalString;
                        }

                        string idString = to_string(digitDuaPertama) + to_string(digitLimaSelanjutnya) + to_string(digitDuaSelanjutnya) + digitTerakhirString;

                        int id = stoi(idString);

                        dataOrder* pesananBaru = new dataOrder;
                        pesananBaru->id = id;
                        pesananBaru->nama = namaPelanggan;
                        pesananBaru->supir = current->nama;
                        pesananBaru->platNomor = platNomor;
                        pesananBaru->tujuan = tujuanPelanggan;
                        pesananBaru->next = NULL;

                        if(antrianPesanan == NULL) {
                            antrianPesanan = pesananBaru;
                        } else {
                            dataOrder* temp = antrianPesanan;
                            while(temp->next != NULL) {
                                temp = temp->next;
                            }
                            temp->next = pesananBaru;
                        }

                        cout<<"Order telah dilakukan !!!"<<endl;
                        cout<<"Id         : "<<pesananBaru->id<<endl;
                        cout<<"Nama       : "<<pesananBaru->nama<<endl;
                        cout<<"Supir      : "<<pesananBaru->supir<<endl;
                        cout<<"Plat nomor : "<<pesananBaru->platNomor<<endl;
                        cout<<"tujuan     : "<<pesananBaru->tujuan<<endl;
                        cout<<"Ingin melakukan order lagi ? (y/n) ";
                        char inputPilihan;
                        cin>>inputPilihan;
                        if(inputPilihan == 'n') {
                            exitOrder = true;
                        }
                    }


                } else if(inputUser == 4) {
                    exitUserMenu = true;
                } else {
                    cout << "Pilihan tidak valid!" << endl;
                    break;
                }
            }
            // End Input 2

        } else if (inputAwal == 3) {
            break;
        } else {
            cout<<"Input tidak valid!"<<endl;
            break;
        }
    }  
}