#include "header.h"

int nMaxCabang = 10;
const int nMaxNasabah = 10;
list_Teller FAM;
int MaxDummy = 0;

void createList_teller(list_Teller &LP){
    /*
    I.S : LP adalah list teller yang kosong.
    F.S : LP terdefinisi dengan first dan last bernilai NULL.
    */
    first(LP) = NULL;
    last(LP) = NULL;
};

address_teller alokasi_teller(infotypeTeller P){
    /*
    I.S : Tidak ada elemen baru untuk teller.
    F.S : Elemen baru bertipe address_teller terbentuk, dengan info(A) diisi
          nilai P, dan next(A), prev(A), nextC(A) diinisialisasi NULL.
          Elemen baru dikembalikan.
    */
    address_teller A = new element_list_Teller;
    info(A) = P;
    next(A) = NULL;
    prev(A) = NULL;
    nextC(A) = NULL;
    return A;
};

address_nasabah alokasi_nasabah(infotypeNasabah C){
    /*
    I.S : Tidak ada elemen baru yang dialokasikan untuk nasabah.
    F.S : Terbentuk elemen baru bertipe address_nasabah dengan infoN(B) diisi
          dengan nilai C, nextN(B) diinisialisasi dengan NULL, elemen baru
          dikembalikan sebagai nilai fungsi.
    */
    address_nasabah B = new element_Nasabah;
    infoN(B) = C;
    nextN(B) = NULL;
    return B;
};

void insertFirst_teller(list_Teller &LP, address_teller P) {
    /*
    I.S : LP mungkin kosong atau sudah berisi elemen, P adalah elemen baru.
    F.S : P disisipkan di awal list LP. Jika kosong, P menjadi pertama dan terakhir.
          Jika tidak, P menjadi pertama dengan elemen sebelumnya tetap terhubung.
          Jika cabang penuh, fungsi_Menu_Tambah(LP) dipanggil.
    */
    if (!isCabangPenuh(LP)){
        if (first(LP) == NULL) {
            first(LP) = P;
            last(LP) = P;
        } else {
            next(P) = first(LP);
            prev(first(LP)) = P;
            first(LP) = P;
        }
    }else {
        cout<<"Cabang Penuh"<<endl;
        fungsi_Menu_Tambah(LP);
    }
}

void insertLast_teller(list_Teller &LP, address_teller P) {
    /*
    I.S : LP mungkin kosong atau berisi elemen, P adalah elemen baru.
    F.S : P disisipkan di akhir LP. Jika kosong, P jadi pertama dan terakhir.
          Jika tidak, P jadi terakhir dengan elemen sebelumnya terhubung.
          Jika cabang penuh, fungsi_Menu_Tambah(LP) dipanggil.
    */
    if (!isCabangPenuh(LP)){
        if (first(LP) == NULL) {
            first(LP) = P;
            last(LP) = P;
        } else {
            prev(P) = last(LP);
            next(last(LP)) = P;
            last(LP) = P;
        }
    }else {
        cout<<"Teller pada cabang ini penuh"<<endl;
    }
}

void dealokasi_teller(address_teller P) {
    /*
    I.S : P adalah elemen address_teller yang tidak diperlukan.
    F.S : Memori elemen P dilepas kembali ke sistem.
    */
    delete P;
}

void dealokasi_nasabah(address_nasabah C) {
    /*
    I.S : C adalah elemen bertipe address_nasabah yang telah digunakan
          dan tidak diperlukan lagi.
    F.S : Memori yang dialokasikan untuk elemen C dilepas kembali ke sistem.
    */
    delete C;
}

void show_teller(list_Teller LP) {
     /*
    I.S : LP adalah list teller yang mungkin kosong atau berisi elemen.
    F.S : Menampilkan data setiap teller dalam list LP, termasuk ID, nama,
          jabatan, bidang, umur, dan jumlah nasabah dari setiap teller,
          jika list kosong maka tidak ada yang ditampilkan.
    */
    address_teller P = first(LP);
    while (P != NULL) {
        cout << "ID Teller: " << info(P).idTeller << endl;
        cout << "Nama: " << info(P).nama << endl;
        cout << "Jabatan: " << info(P).jabatan << endl;
        cout << "Bidang: " << info(P).bidang << endl;
        cout << "Umur: " << info(P).umur << endl;
        cout << "Jumlah Nasabah: " << info(P).jumlahNasabah << endl;
        cout<<endl;
        P = next(P);
    }
}

bool isCabangPenuh(list_Teller LP){
     /*
    I.S : LP adalah list teller yang mungkin kosong atau berisi elemen.
    F.S : Mengembalikan nilai true jika jumlah elemen dalam list LP sama
          dengan nilai nMaxCabang, false jika jumlah elemen kurang dari
          nMaxCabang.
    */
    address_teller P = first(LP);
    int total = 0;
    while (P != NULL){
        total = total+1;
        P = next(P);
    }
    return nMaxCabang == total;
};

void delete_teller(list_Teller &LP, address_teller &P){
    /*
    I.S : P adalah elemen bertipe address_teller yang ada dalam list LP,
          dan elemen P terhubung dengan list LP (bisa di awal, tengah, atau akhir).
    F.S : Elemen P dihapus dari list LP, memori yang dialokasikan untuk elemen P dilepas,
          dan pointer P diset menjadi NULL. List LP diperbarui sesuai dengan posisi P di list.
    */
    if (P != NULL) {
        if (P == first(LP) && P == last(LP)) {
            first(LP) = NULL;
            last(LP) = NULL;
        } else if (P == first(LP)) {
            first(LP) = next(P);
            prev(first(LP)) = NULL;
            next(P) = NULL;
        } else if (P == last(LP)) {
            last(LP) = prev(P);
            next(last(LP)) = NULL;
            prev(P) = NULL;
        } else {
            next(prev(P)) = next(P);
            prev(next(P)) = prev(P);
            next(P) = NULL;
            prev(P) = NULL;

        }
        dealokasi_teller(P);
    }
};

void insertlast_nasabah(list_Teller &LP, address_nasabah C){
     /*
    I.S : LP berisi list teller, C adalah elemen nasabah baru.
    F.S : C ditambahkan ke akhir daftar nasabah teller yang sesuai
          jika teller ditemukan dan belum penuh, jumlah nasabah teller bertambah.
    */
    address_teller P = checkTellerNasabah(LP, C);
    if (P != NULL && info(P).jumlahNasabah < nMaxNasabah){
         if (nextC(P) == NULL) {
            nextC(P) = C;
        } else {
            address_nasabah Q = nextC(P);
            while (nextN(Q) != NULL) {
                Q = nextN(Q);
            }
                nextN(Q) = C;
        }
        info(P).jumlahNasabah = info(P).jumlahNasabah + 1;
    }else {
        cout << "Nasabah sudah lebih dari 10"<<endl;
    }
};

void ubahData_teller(list_Teller &LP){
    /*
    I.S : LP adalah list teller yang sudah terdefinisi, dan ID teller yang akan diubah sudah dimasukkan.
    F.S : nama teller yang sesuai dengan ID yang dimasukkan diperbarui dengan nama baru yang diberikan oleh pengguna.
          Jika ID teller tidak ditemukan, maka menampilkan pesan bahwa teller tidak ditemukan.
    */
    string idTeller;
    cout << "Masukkan ID Teller yang akan diubah: ";
    cin >> idTeller;
    address_teller P = searchTeller(LP, idTeller);
    if (P != NULL) {
        cout << "Masukkan nama baru untuk Teller: " << endl;
        cout << "Nama: ";
        cin >> info(P).nama;
        cout << "Data berhasil diubah." << endl;
    } else {
        cout << "Teller dengan ID tersebut tidak ditemukan." << endl;
    }
};

void ubahData_nasabah(address_teller P){
    /*
    I.S : P adalah elemen bertipe address_teller yang valid, dan nomor rekening nasabah yang akan diubah sudah dimasukkan.
    F.S : Jika nasabah dengan nomor rekening yang dimasukkan ditemukan, maka data nama nasabah diperbarui sesuai input pengguna.
          Jika nasabah dengan nomor rekening tersebut tidak ditemukan, maka akan menampilkan pesan bahwa nasabah tidak ditemukan.
    */
    int noRek;
    cout << "Masukkan noRek Nasabah yang akan diubah: ";
    cin >> noRek;
    address_nasabah Q = search_nasabah_berdasarkan_teller(noRek, P);
    if (Q !=NULL){
        cout << "Masukkan nama baru untuk Nasabah: " << endl;
        cout << "Nama: ";
        cin >> infoN(Q).nama;
        cout << "Data berhasil diubah." << endl;
    }else {
        cout << "Nasabah dengan noRek tersebut tidak ditemukan." << endl;
    }
};

void showALL_Data(list_Teller LP){
    /*
    I.S : LP berisi list teller dengan data nasabah.
    F.S : Menampilkan informasi teller dan nasabah terkait, termasuk ID, nama, jabatan, bidang, umur, jumlah nasabah, serta data nasabah.
    */
    address_teller P = first(LP);
    while (P != NULL) {
        cout << "ID Teller: " << info(P).idTeller << endl;
        cout << "Nama: " << info(P).nama << endl;
        cout << "Jabatan: " << info(P).jabatan << endl;
        cout << "Bidang: " << info(P).bidang << endl;
        cout << "Umur: " << info(P).umur << endl;
        cout << "Jumlah Nasabah: " << info(P).jumlahNasabah << endl;
        address_nasabah C = nextC(P);
        cout<<endl;
        while (C != NULL) {
            cout << "  - Nasabah: " << infoN(C).nama << endl;
            cout << "    Jenis Nasabah: " << infoN(C).jenisNasabah << endl;
            cout << "    Jenis Transaksi: " << infoN(C).jenisTransaksi << endl;
            cout << "    No. Rekening: " << infoN(C).noRek << endl;
            cout << "    Besar Transaksi: " << infoN(C).besarTransaksi << endl;
            C = nextN(C);
            cout<<endl;
        }
        P = next(P);
    }
};

address_teller checkTellerNasabah(list_Teller LP, address_nasabah C){
    /*
    I.S : LP berisi list teller dan C adalah elemen nasabah.
    F.S : Mengembalikan alamat teller yang sesuai berdasarkan kriteria jenis transaksi
          dan besar transaksi nasabah, jika tidak ditemukan maka mengembalikan Nil.
    */
    address_teller temp = NULL;
    address_teller P = first(LP);
    while (P != NULL) {
        if (info(P).bidang == infoN(C).jenisTransaksi) {
            if (infoN(C).besarTransaksi > 25000000 && info(P).jabatan == "senior") {
                if (temp == NULL || info(P).jumlahNasabah < info(temp).jumlahNasabah) {
                    temp = P;
                }
            } else if (infoN(C).besarTransaksi <= 25000000 && info(P).jabatan == "junior") {
                if (temp == NULL || info(P).jumlahNasabah < info(temp).jumlahNasabah) {
                    temp = P;
                }
            }
        }
        P = next(P);
    }
    return temp;
};

address_nasabah search_nasabah_berdasarkan_teller(int noRek, address_teller P) {
     /*
    I.S : P adalah address_teller yang valid dan berisi daftar nasabah.
    F.S : Mengembalikan alamat nasabah yang memiliki noRek sesuai jika ditemukan,
          atau NULL jika tidak ada nasabah dengan noRek tersebut.
    */
    if (P != NULL) {
        address_nasabah Q = P->nextC;
        while (Q != NULL) {
            if (infoN(Q).noRek == noRek) {
                return Q;
            }
            Q = nextN(Q);
        }
    }
    return NULL;
}

void deletefirst_nasabah_berdasarkan_teller(address_teller &P){
    /*
    I.S : P adalah address_teller yang memiliki nasabah terhubung.
    F.S : Menghapus nasabah pertama pada daftar nasabah teller P dan
          melepaskan memori yang digunakan.
    */
    if (nextC(P) != NULL){
        address_nasabah Q = nextC(P);
        if (nextN(Q) != NULL){
            address_nasabah R = nextN(Q);
            nextC(P) = R;
            nextN(Q) = NULL;
            dealokasi_nasabah(Q);
        }else{
            nextC(P) = NULL;
            dealokasi_nasabah(Q);
        }
        cout<<"Penghapusan berhasil"<<endl;
    }else {
        cout<<"Teller ini tidak memiliki nasabah"<<endl;
    }
};

address_teller searchTeller(list_Teller LP, string idTeller) {
    /*
    I.S : LP adalah list teller dengan data teller yang mungkin kosong.
    F.S : Mengembalikan alamat teller dengan idTeller yang sesuai, atau NULL jika tidak ditemukan.
    */
    address_teller P = first(LP);
    while (P != NULL) {
        if (info(P).idTeller == idTeller) {
            return P;
        }
        P = next(P);
    }
    return NULL;
}

int total_transaksi(list_Teller LP){
    /*
    I.S : LP adalah list teller yang mungkin berisi data nasabah.
    F.S : Menghitung dan menampilkan total transaksi nasabah di semua teller dalam LP.
    */
    address_teller P = first(LP);
    int total = 0;
    while (P != NULL) {
        address_nasabah C = nextC(P);
        while (C != NULL) {
            total = total + 1;
            C = nextN(C);
        }
        P = next(P);
    }
    cout << "========================================" << endl;
    cout << "Total Transaksi: "<< total<<endl;
    cout << "========================================" << endl;
};

void input_Nasabah(list_Teller &LP, int pilihan) {
    /*
    I.S : LP adalah list teller yang mungkin kosong.
    F.S : Menambah satu atau beberapa nasabah ke dalam list LP sesuai pilihan,
          memeriksa keunikan nomor rekening nasabah sebelum ditambahkan.
    */
    infotypeNasabah Q;
    int jumlah = 0;

    if (pilihan == 1) {
        cout << "Masukan nama nasabah: ";
        cin >> Q.nama;

        cout << "Masukan jenis nasabah(Individu/Bisnis): ";
        cin >> Q.jenisNasabah;

        cout << "Masukan jenis transaksi(tarik_uang/setor): ";
        cin >> Q.jenisTransaksi;

        cout << "Masukan nomor rekening: ";
        cin >> Q.noRek;

        cout << "Masukan besar transaksi: ";
        cin >> Q.besarTransaksi;
        if (checkUnikNasabah(LP, Q)){
            address_nasabah P = alokasi_nasabah(Q);
            insertlast_nasabah(LP, P);
        }else {
            cout<<"Maaf nomor rekening sudah digunakan"<<endl;
        };

    } else if (pilihan == 2) {
        cout << "Masukan jumlah nasabah yang akan ditambahkan: ";
        cin >> jumlah;

        for (int i = 0; i < jumlah; i++) {
            cout << "\nData Nasabah ke-" << i + 1 << ":" << endl;

            cout << "Masukan nama nasabah: ";
            cin >> Q.nama;

            cout << "Masukan jenis nasabah(Individu/Bisnis): ";
            cin >> Q.jenisNasabah;

            cout << "Masukan jenis transaksi(tarik_uang/setor): ";
            cin >> Q.jenisTransaksi;

            cout << "Masukan nomor rekening: ";
            cin >> Q.noRek;

            cout << "Masukan besar transaksi: ";
            cin >> Q.besarTransaksi;
            if (checkUnikNasabah(LP, Q)){
                address_nasabah P = alokasi_nasabah(Q);
                insertlast_nasabah(LP, P);
            }else {
                cout<<"Maaf nomor rekening sudah digunakan"<<endl;
            }
        }
    }
}

void input_Teller(list_Teller &LP, int pilihan) {
    /*
    I.S : LP adalah list teller yang mungkin kosong.
    F.S : Menambah satu teller ke dalam list LP sesuai pilihan,
          memeriksa keunikan ID teller sebelum ditambahkan.
    */
    infotypeTeller Q;
    int jumlah = 0;

    if (pilihan == 1) {
        cout << "Masukan ID Teller: ";
        cin >> Q.idTeller;

        cout << "Masukan nama Teller: ";
        cin >> Q.nama;

        cout << "Masukan jabatan Teller(senior/junior): ";
        cin >> Q.jabatan;

        cout << "Masukan bidang Teller(tarik_uang/setor): ";
        cin >> Q.bidang;

        cout << "Masukan umur Teller: ";
        cin >> Q.umur;

        Q.jumlahNasabah=0;

        if (checkUnikTeller(LP, Q)) {
            address_teller P = alokasi_teller(Q);
            insertFirst_teller(LP, P);
        } else {
            cout << "Maaf, ID Teller sudah digunakan." << endl;
        }
    } else {
        cout << "Masukan ID Teller: ";
        cin >> Q.idTeller;

        cout << "Masukan nama Teller: ";
        cin >> Q.nama;

        cout << "Masukan jabatan Teller(senior/junior): ";
        cin >> Q.jabatan;

        cout << "Masukan bidang Teller(tarik_uang/setor): ";
        cin >> Q.bidang;

        cout << "Masukan umur Teller: ";
        cin >> Q.umur;

        Q.jumlahNasabah=0;

        if (checkUnikTeller(LP, Q)) {
            address_teller P = alokasi_teller(Q);
            insertLast_teller(LP, P);
        } else {
            cout << "Maaf, ID Teller sudah digunakan." << endl;
        }
    }
}


bool checkUnikNasabah(list_Teller LP, infotypeNasabah Q){
    /*
    I.S : LP berisi list teller dengan nasabah terkait.
    F.S : Mengembalikan true jika nomor rekening nasabah (noRek) belum ada di list,
          false jika nomor rekening sudah ada di salah satu nasabah dalam LP.
    */
    address_teller P = first(LP);
    while (P != NULL){
        address_nasabah C = nextC(P);
        while (C != NULL){
            if (infoN(C).noRek == Q.noRek){
                return false;
            }
            C = nextN(C);
        }
        P = next(P);
    }
    return true;
}

bool checkUnikTeller(list_Teller LP, infotypeTeller Q){
    /*
    I.S : LP berisi list teller.
    F.S : Mengembalikan true jika ID teller (idTeller) belum ada di list,
          false jika ID teller sudah ada di salah satu teller dalam LP.
    */
    address_teller P = first(LP);
    while (P != NULL){
        if (info(P).idTeller == Q.idTeller){
            return false;
        }
        P = next(P);
    }
    return true;
}

void Dummy(list_Teller &LP) {
    /*
    I.S : LP adalah list teller yang berisi data teller dan nasabah yang mungkin kosong atau sudah berisi beberapa data.
    F.S : Menambahkan data dummy teller dan nasabah ke dalam list LP. Teller dan nasabah tersebut memiliki data seperti ID, nama, umur, jabatan, bidang,
    serta transaksi yang sesuai. Dummy tidak dapat digunakan 2 kali.
    */
    if (MaxDummy != 1){
        infotypeTeller teller1;
        teller1.idTeller = "TLL-BDG01-12345";
        teller1.nama = "Bintang_Saputra";
        teller1.umur = 23;
        teller1.jabatan = "senior";
        teller1.bidang = "tarik_uang";
        teller1.jumlahNasabah = 0;
        address_teller P1 = alokasi_teller(teller1);
        insertFirst_teller(LP, P1);

        infotypeTeller teller2;
        teller2.idTeller = "TLL-BDG01-12364";
        teller2.nama = "Ezra_Mangansi";
        teller2.umur = 19;
        teller2.jabatan = "junior";
        teller2.bidang = "tarik_uang";
        teller2.jumlahNasabah = 0;
        address_teller P2 = alokasi_teller(teller2);
        insertFirst_teller(LP, P2);

        infotypeTeller teller3;
        teller3.idTeller = "TLL-BDG01-12347";
        teller3.nama = "Dandy";
        teller3.umur = 21;
        teller3.jabatan = "senior";
        teller3.bidang = "setor_Uang";
        teller3.jumlahNasabah = 0;
        address_teller P3 = alokasi_teller(teller3);
        insertLast_teller(LP, P3);

        infotypeTeller teller4;
        teller4.idTeller = "TLL-BDG01-12880";
        teller4.nama = "Bintang_Saputra";
        teller4.umur = 22;
        teller4.jabatan = "junior";
        teller4.bidang = "setor_Uang";
        teller4.jumlahNasabah = 0;
        address_teller P4 = alokasi_teller(teller4);
        insertFirst_teller(LP, P4);

        infotypeNasabah nasabah1;
        nasabah1.nama = "Nabila_Azhari";
        nasabah1.jenisNasabah = "Individu";
        nasabah1.noRek = 1432780087;
        nasabah1.jenisTransaksi = "tarik_uang";
        nasabah1.besarTransaksi = 10000000;
        address_nasabah C1 = alokasi_nasabah(nasabah1);
        insertlast_nasabah(LP, C1);

        infotypeNasabah nasabah2;
        nasabah2.nama = "Velisia_Nihan";
        nasabah2.jenisNasabah = "Individu";
        nasabah2.noRek = 1528500654;
        nasabah2.jenisTransaksi = "tarik_uang";
        nasabah2.besarTransaksi = 50000000;
        address_nasabah C2 = alokasi_nasabah(nasabah2);
        insertlast_nasabah(LP, C2);

        infotypeNasabah nasabah3;
        nasabah3.nama = "Jeany_Ferliza";
        nasabah3.jenisNasabah = "Bisnis";
        nasabah3.noRek = 1753927300;
        nasabah3.jenisTransaksi = "tarik_uang";
        nasabah3.besarTransaksi = 8000000;
        address_nasabah C3 = alokasi_nasabah(nasabah3);
        insertlast_nasabah(LP, C3);

        infotypeNasabah nasabah4;
        nasabah4.nama = "Yolanda_Rahmah";
        nasabah4.jenisNasabah = "Bisnis";
        nasabah4.noRek = 1538007583;
        nasabah4.jenisTransaksi = "setor_Uang";
        nasabah4.besarTransaksi = 100000000;
        address_nasabah C4 = alokasi_nasabah(nasabah4);
        insertlast_nasabah(LP, C4);

        infotypeNasabah nasabah5;
        nasabah5.nama = "Auliya_Marifah";
        nasabah5.jenisNasabah = "Individu";
        nasabah5.noRek = 1508736500;
        nasabah5.jenisTransaksi = "setor_Uang";
        nasabah5.besarTransaksi = 20000000;
        address_nasabah C5 = alokasi_nasabah(nasabah5);
        insertlast_nasabah(LP, C5);

        infotypeNasabah nasabah6;
        nasabah6.nama = "Nasywa";
        nasabah6.jenisNasabah = "Individu";
        nasabah6.noRek = 1845387006;
        nasabah6.jenisTransaksi = "setor_Uang";
        nasabah6.besarTransaksi = 400000;
        address_nasabah C6 = alokasi_nasabah(nasabah6);
        insertlast_nasabah(LP, C6);

        MaxDummy = MaxDummy + 1;
    }else {
        cout<<"Dummy Telah digunakan"<<endl;
    }
};

void Fungsi_Menu_Utama(){
    /*
    I.S : FAM adalah list teller yang berisi data teller dan nasabah.
    F.S : Menampilkan menu utama untuk memilih berbagai operasi seperti menambah data, menampilkan data, mengubah, mencari, menghapus, dan menghitung total transaksi.
          Operasi yang dipilih akan dijalankan sesuai dengan pilihan pengguna. Program akan berhenti jika pengguna memilih opsi keluar.
    */
    int pilihan = 0;
    while (pilihan != 9){
        cout << "============================================" << endl;
        cout << "            === MENU UTAMA ===              " << endl;
        cout << "============================================" << endl;
        cout << "1.  Tambah Nasabah/Teller" << endl;
        cout << "2.  Tambah Data Dummy" << endl;
        cout << "3.  Tampilkan Semua Data Teller dan Nasabah" << endl;
        cout << "4.  Tampilkan Data Teller" << endl;
        cout << "5.  Ubah Nasabah/Teller" << endl;
        cout << "6.  Cari Nasabah/Teller" << endl;
        cout << "7.  Hapus Nasabah/Teller" << endl;
        cout << "8.  Total Transaksi" << endl;
        cout << "9.  Keluar" << endl;
        cout << "============================================" << endl;
        cout << "Pilih menu (1-9): ";
        cin >> pilihan;
        if (pilihan == 1){
            fungsi_Menu_Tambah(FAM);
        }else if (pilihan == 2){
            Dummy(FAM);
        }else if (pilihan == 3){
            fungsi_Menu_Show(FAM);
        }else if (pilihan == 4){
            show_teller(FAM);
        }else if (pilihan == 5){
            fungsi_Menu_Ubah(FAM);
        }else if (pilihan == 6){
            fungsi_Menu_Cari(FAM);
        }else if (pilihan == 7){
            fungsi_Menu_Hapus(FAM);
        }else if (pilihan == 8){
            total_transaksi(FAM);
        }else if (pilihan == 9){
               cout << "Keluar dari program. Terima kasih!" << endl;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
};

void fungsi_Menu_Tambah(list_Teller &LP) {
    /*
    I.S : LP adalah list teller yang berisi data teller dan nasabah.
    F.S : Menampilkan menu untuk menambah data teller atau nasabah, dan menjalankan fungsi untuk menambah data sesuai pilihan pengguna.
    */
    int pilihan = 0;
    while (pilihan != 3) {
        cout << "========================================" << endl;
        cout << "        === MENU TAMBAH DATA ===        " << endl;
        cout << "========================================" << endl;
        cout << "1. Tambah Teller" << endl;
        cout << "2. Tambah Nasabah" << endl;
        cout << "3. Kembali ke Menu Utama" << endl;
        cout << "========================================" << endl;
        cout << "Pilih menu (1-3): ";
        cin >> pilihan;
        if (pilihan == 1) {
            menu_tambah_teller(LP);
        } else if (pilihan == 2) {
            menu_tambah_nasabah(LP);
        } else if (pilihan == 3) {
            cout << "Kembali ke Menu Utama..." << endl;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

void fungsi_Menu_Hapus(list_Teller &LP) {
    /*
    I.S : LP adalah list teller yang berisi elemen-elemen teller dan nasabah yang terhubung,
    F.S : Menampilkan menu untuk menghapus teller atau nasabah, dan menjalankan logika penghapusan berdasarkan pilihan pengguna.
    */
    int pilihan = 0;
    string pilih;
    while (pilihan != 3) {
        cout << "========================================" << endl;
        cout << "        === MENU HAPUS DATA ===         " << endl;
        cout << "========================================" << endl;
        cout << "1. Hapus Teller" << endl;
        cout << "2. Hapus Nasabah Pertama dari Teller" << endl;
        cout << "3. Kembali ke Menu Utama" << endl;
        cout << "========================================" << endl;
        cout << "Pilih menu (1-3): ";
        cin >> pilihan;
        if (pilihan == 1) {
            cout << "Masukan idTeller: ";
            cin >> pilih;
            address_teller P = searchTeller(LP, pilih);
            delete_teller(LP, P);
        } else if (pilihan == 2) {
            cout << "Masukan idTeller: ";
            cin >> pilih;
            address_teller P = searchTeller(LP, pilih);
            deletefirst_nasabah_berdasarkan_teller(P);
        } else if (pilihan == 3) {
            cout << "Kembali ke Menu Utama..." << endl;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

void fungsi_Menu_Ubah(list_Teller &LP) {
    /*
    I.S : LP adalah list teller yang berisi elemen-elemen teller dan nasabah yang terhubung,
    F.S : Menampilkan menu untuk mengubah nama teller atau nasabah.
    */
    int pilihan, noRek = 0;
    string pilih;
    while (pilihan != 3) {
        cout << "========================================" << endl;
        cout << "        === MENU UBAH NAMA ===          " << endl;
        cout << "========================================" << endl;
        cout << "1. Ubah Nama Teller" << endl;
        cout << "2. Ubah Nama Nasabah" << endl;
        cout << "3. Kembali ke Menu Utama" << endl;
        cout << "========================================" << endl;
        cout << "Pilih menu (1-3): ";
        cin >> pilihan;
        if (pilihan == 1) {
            ubahData_teller(LP);
        } else if (pilihan == 2) {
            cout << "Masukan idTeller dari nasabah yang dicari: ";
            cin >> pilih;
            address_teller P = searchTeller(LP, pilih);
            if (P != NULL){
                cout << "Masukan nomor rekening nasabah: ";
                cin >> noRek;
                address_nasabah Q = search_nasabah_berdasarkan_teller(noRek, P);
                if (Q != NULL){
                    ubahData_nasabah(P);
                }else {
                    cout << "========================================" << endl;
                    cout << "Nasabah tidak ditemukan"<<endl;
                    cout << "========================================" << endl;
                }
            }else {
                cout << "========================================" << endl;
                cout << "Teller tidak ditemukan"<<endl;
                cout << "========================================" << endl;
            }
        } else if (pilihan == 3) {
            cout << "Kembali ke Menu Utama..." << endl;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

void fungsi_Menu_Cari(list_Teller LP) {
    /*
    I.S : LP adalah list teller yang berisi elemen-elemen teller dan nasabah yang terhubung,
    F.S : Menampilkan menu untuk mencari data teller atau nasabah, dan menjalankan logika pencarian berdasarkan pilihan pengguna.
    */
    int pilihan, noRek = 0;
    string pilih;
    while (pilihan != 3) {
        cout << "========================================" << endl;
        cout << "        === MENU CARI DATA ===          " << endl;
        cout << "========================================" << endl;
        cout << "1. Cari Teller" << endl;
        cout << "2. Cari Nasabah" << endl;
        cout << "3. Kembali ke Menu Utama" << endl;
        cout << "========================================" << endl;
        cout << "Pilih menu (1-3): ";
        cin >> pilihan;
        if (pilihan == 1) {
            cout << "Masukan idTeller yang akan dicari: ";
            cin >> pilih;
            address_teller P = searchTeller(LP, pilih);
            if (P != NULL){
                cout << "========================================" << endl;
                cout << "        === Teller ditemukan ===        " << endl;
                cout << "========================================" << endl;
                cout << "ID Teller: " << info(P).idTeller << endl;
                cout << "Nama: " << info(P).nama << endl;
                cout << "Jabatan: " << info(P).jabatan << endl;
                cout << "Bidang: " << info(P).bidang << endl;
                cout << "Umur: " << info(P).umur << endl;
                cout << "Jumlah Nasabah: " << info(P).jumlahNasabah << endl;
            }else {
                cout << "========================================" << endl;
                cout << "Teller tidak ditemukan"<<endl;
                cout << "========================================" << endl;
            }
        } else if (pilihan == 2) {
            cout << "Masukan idTeller dari nasabah yang dicari: ";
            cin >> pilih;
            address_teller P = searchTeller(LP, pilih);
            if (P != NULL){
                cout << "Masukan nomor rekening nasabah: ";
                cin >> noRek;
                address_nasabah Q = search_nasabah_berdasarkan_teller(noRek, P);
                if (Q != NULL){
                    cout << "========================================" << endl;
                    cout << "        === Nasabah ditemukan ===       " << endl;
                    cout << "========================================" << endl;
                    cout << "Nasabah: " << infoN(Q).nama << endl;
                    cout << "Jenis Nasabah: " << infoN(Q).jenisNasabah << endl;
                    cout << "Jenis Transaksi: " << infoN(Q).jenisTransaksi << endl;
                    cout << "No. Rekening: " << infoN(Q).noRek << endl;
                    cout << "Besar Transaksi: " << infoN(Q).besarTransaksi << endl;
                }else {
                    cout << "========================================" << endl;
                    cout << "Nasabah tidak ditemukan"<<endl;
                    cout << "========================================" << endl;
                }
            }else {
                cout << "========================================" << endl;
                cout << "Teller tidak ditemukan"<<endl;
                cout << "========================================" << endl;
            }
        } else if (pilihan == 3) {
            cout << "Kembali ke Menu Utama..." << endl;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}


void fungsi_Menu_Show(list_Teller LP){
    /*
    I.S : LP adalah list teller yang berisi elemen-elemen teller yang terhubung dengan nasabah,
    F.S : Menampilkan daftar lengkap teller dan nasabah yang ada dalam list LP.
    */
    cout << "========================================" << endl;
    cout << "    === DAFTAR TELLER DAN NASABAH ===   " << endl;
    cout << "========================================" << endl;
    showALL_Data(LP);
    cout << "\n======================================" << endl;
};

void fungsi_Menu_Show_Teller(list_Teller LP){
    /*
    I.S : LP adalah list teller yang berisi elemen-elemen teller,
    F.S : Menampilkan daftar teller yang ada dalam list LP.
    */
    cout << "========================================" << endl;
    cout << "          === DAFTAR TELLER ===         " << endl;
    cout << "========================================" << endl;
    show_teller(LP);
    cout << "\n======================================" << endl;
};

void menu_tambah_teller(list_Teller &LP){
    /*
    I.S : LP adalah list teller yang mungkin kosong atau berisi elemen teller,
    F.S : Menampilkan menu untuk menambah teller, dengan pilihan untuk
          menambah teller di depan atau di belakang list LP, atau
          kembali ke menu utama tanpa mengubah list LP.
    */
    int pilihan = 0;
    while (pilihan != 3) {
        cout << "========================================" << endl;
        cout << "       === MENU Tambah Teller ===       " << endl;
        cout << "========================================" << endl;
        cout << "1. Tambah Teller Depan" << endl;
        cout << "2. Tambah Teller Belakang" << endl;
        cout << "3. Kembali ke Menu Tambah" << endl;
        cout << "========================================" << endl;
        cout << "Pilih menu (1-3): ";
        cin >> pilihan;
        if (pilihan == 1) {
            input_Teller(LP, pilihan);
        } else if (pilihan == 2) {
            input_Teller(LP, pilihan);
        } else if (pilihan == 3) {
            cout << "Kembali ke Menu Utama..." << endl;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
};

void menu_tambah_nasabah(list_Teller &LP){
    /*
    I.S : LP adalah list teller yang valid, dengan pilihan menu yang tersedia untuk menambah nasabah.
    F.S : Berdasarkan input pengguna, fungsi ini akan memanggil fungsi input_nasabah untuk menambah satu atau banyak nasabah.
          Jika pilihan adalah 3, maka akan kembali ke menu utama.
          Jika pilihan tidak valid, program akan meminta pengguna untuk mencoba lagi.
    */
    int pilihan = 0;
    while (pilihan != 3) {
        cout << "========================================" << endl;
        cout << "      === MENU Tambah Nasabah ===       " << endl;
        cout << "========================================" << endl;
        cout << "1. Tambah Satu Nasabah" << endl;
        cout << "2. Tambah Banyak Nasabah" << endl;
        cout << "3. Kembali ke Menu Tambah" << endl;
        cout << "========================================" << endl;
        cout << "Pilih menu (1-3): ";
        cin >> pilihan;
        if (pilihan == 1) {
            input_Nasabah(LP, pilihan);
        } else if (pilihan == 2) {
            input_Nasabah(LP, pilihan);
        } else if (pilihan == 3) {
            cout << "Kembali ke Menu Utama..." << endl;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
};
