#ifndef GYM_H
#define GYM_H
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;


// Tipe alias untuk menunjuk struct
typedef struct member* adrMember;
typedef struct jenisGerakan* adrGerakan;
typedef struct paketLatihan* adrPaket;
typedef struct relasi* adrRelasi;


// Tree
struct infoMember {
    string nama_member;
    float target_berat;
    float tinggi_badan;
    float progress_berat[12];
};

struct member {
    infoMember info_member;
    adrMember left;
    adrMember right;
};


// Multi Linked List
struct jenisGerakan {
    string nama_gerakan;
    bool isBerbasisWaktu;  
    int frekuensi;         
    int sets;              
    adrGerakan next;
};

struct paketLatihan {
    string nama_paket;
    string kesulitan;
    adrGerakan first;
    adrPaket next;
};

// Relasi Member-Paket
struct relasi {
    string nama_member;
    string nama_paket;
    string kesulitan_paket;
    adrRelasi next;
};

// Fungsi traversal
void inorder(adrMember root);
void preorder(adrMember root);
void postorder(adrMember root);
void levelOrder(adrMember root);

// Fungsi Pengolahan BST
int countTotalMember(adrMember root);
adrMember findMemberMaxWeight(adrMember root);
adrMember findMemberMinWeight(adrMember root);
float averageTargetWeight(adrMember root, int &count);

// Helper functions untuk deletion
adrMember findMin(adrMember root);
adrMember deleteNode(adrMember root, string nama);

// Fungsi Member
void lihatAllMember(adrMember root);
adrMember createNode(infoMember info);
void insertNode(adrMember &root, adrMember newNode);
adrMember findNode(adrMember root, string nama);
void updateProgMember(adrMember &root);
void detailMember(adrMember root);

// Menu Member
void menuMember(adrMember &root);
void lihatSemuaMember(adrMember root);
void hapusMember(adrMember &root);
void menuStatistikMember(adrMember root);

// Fungsi Multi Linked List - Paket Latihan
adrPaket createPaket(string nama, string kesulitan);
adrGerakan createGerakan(string nama, bool isBerbasisWaktu, int frekuensi, int sets);
void insertPaket(adrPaket &head, adrPaket newPaket);
void insertGerakan(adrPaket paket, adrGerakan newGerakan);
adrPaket findPaket(adrPaket head, string nama, string kesulitan);
int countPaketByName(adrPaket head, string nama);
adrPaket findPaketByName(adrPaket head, string nama);
bool isGerakanExists(adrPaket paket, string namaGerakan);
void deletePaket(adrPaket &head, string nama, string kesulitan);
void deleteGerakan(adrPaket paket, string namaGerakan);

// Menu Latihan
void menuLatihan(adrPaket &headPaket);
void tambahPaket(adrPaket &headPaket);
void tambahGerakan(adrPaket headPaket);
void hapusPaket(adrPaket &headPaket);
void hapusGerakan(adrPaket headPaket);
void updatePaket(adrPaket headPaket);
void updateGerakan(adrPaket headPaket);
void lihatSemuaPaket(adrPaket headPaket);
void detailPaket(adrPaket headPaket);

// Fungsi Pengolahan MLL
int countTotalPaket(adrPaket head);
int countGerakanInPaket(adrPaket paket);
adrPaket findPaketMostExercises(adrPaket head);
adrPaket findPaketLeastExercises(adrPaket head);
void viewPaketByKesulitan(adrPaket head, string kesulitan);
void menuStatistikPaket(adrPaket headPaket);

// Fungsi Relasi Member-Paket
adrRelasi createRelasi(string namaMember, string namaPaket, string kesulitanPaket);
void insertRelasi(adrRelasi &head, adrRelasi newRelasi);
bool isRelasiExists(adrRelasi head, string namaMember, string namaPaket, string kesulitan);
void deleteRelasi(adrRelasi &head, string namaMember, string namaPaket, string kesulitan);
adrRelasi findRelasiByMember(adrRelasi head, string namaMember);

// Menu Relasi
void menuRelasi(adrRelasi &headRelasi, adrMember rootMember, adrPaket headPaket);
void assignPaketToMember(adrRelasi &headRelasi, adrMember rootMember, adrPaket headPaket);
void lihatPaketMember(adrRelasi headRelasi);
void hapusAssignment(adrRelasi &headRelasi);
void lihatAllAssignments(adrRelasi headRelasi);

#endif