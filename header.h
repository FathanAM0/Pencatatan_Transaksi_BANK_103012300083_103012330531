#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <iostream>
using namespace std;
#define Nil NULL
#define info(P) (P)->info
#define next(P) (P)->next
#define nextC(P) (P)->nextC
#define prev(P) (P)->prev
#define first(L) ((L).first)
#define last(L) ((L).last)
#define nextN(C) (C)->nextN
#define infoN(C) (C)->infoN

struct nasabah{
    string nama, jenisNasabah, jenisTransaksi;
    int noRek, besarTransaksi;
};

struct teller{
    string idTeller, jabatan, bidang, nama;
    int umur, jumlahNasabah;
};

typedef nasabah infotypeNasabah;
typedef struct element_Nasabah *address_nasabah;
typedef teller infotypeTeller;
typedef struct element_list_Teller *address_teller;

struct element_Nasabah{
    infotypeNasabah infoN;
    address_nasabah nextN;
};

struct element_list_Teller{
    infotypeTeller info;
    address_nasabah nextC;
    address_teller next, prev;
};

struct list_Teller{
    address_teller first;
    address_teller last;
};

void createList_teller(list_Teller &LP);
address_teller alokasi_teller(infotypeTeller P);
address_nasabah alokasi_nasabah(infotypeNasabah C);
void insertFirst_teller(list_Teller &LP, address_teller P);
void insertLast_teller(list_Teller &LP, address_teller P);
void dealokasi_teller(address_teller P);
void dealokasi_nasabah(address_nasabah C);
void show_teller(list_Teller LP);
void delete_teller(list_Teller &LP, address_teller &P);
void insertlast_nasabah(list_Teller &LP, address_nasabah C);
void ubahData_teller();
void ubahData_nasabah();
void showALL_Data(list_Teller LP);
address_nasabah search_nasabah_berdasarkan_teller(int noRek, address_teller P);
void deletefirst_nasabah_berdasarkan_teller(list_Teller &LP, string idTeller);
int total_transaksi(list_Teller LP);
bool isCabangPenuh(list_Teller LP);
void printNasabah(address_nasabah Q);
address_teller searchTeller(list_Teller LP, string idTeller);
address_teller checkTellerNasabah(list_Teller LP, address_nasabah C);
void input_Nasabah(list_Teller &LP,int pilihan);
void input_Teller(list_Teller &LP,int pilihan);
bool checkUnikTeller(list_Teller LP, infotypeTeller Q);
bool checkUnikNasabah(list_Teller LP, infotypeNasabah Q);

// function Fungsi Menu
void fungsi_Menu_Tambah(list_Teller &LP);
void Dummy(list_Teller &LP);
void Fungsi_Menu_Utama();
void fungsi_Menu_Hapus(list_Teller &LP);
void fungsi_Menu_Ubah(list_Teller &LP);
void fungsi_Menu_Show(list_Teller LP);
void fungsi_Menu_Cari(list_Teller LP);
void menu_tambah_teller(list_Teller &LP);
void menu_tambah_nasabah(list_Teller &LP);


#endif // HEADER_H_INCLUDED
