#include "gym.h"

int main() {
    // variabel data
    adrMember root = nullptr;
    adrPaket headPaket = nullptr;
    adrRelasi headRelasi = nullptr;

    // variabel utilitas
    int pilihanMenu;

    do {
        // UI MENU
        system("cls");
        cout << setfill('=') << setw(10) << "" << " GYM " << setfill('=') << setw(10) << "" << endl; cout << setfill(' ');
        cout << "1. Info member\n";
        cout << "2. Info latihan\n";
        cout << "3. Relasi Member-Latihan\n";
        cout << "4. Keluar\n";
        cout << setfill('-') << setw(25) << "" << endl; cout << setfill(' ');
        cout << "Pilih: "; cin >> pilihanMenu;

        // Pilihan
        switch (pilihanMenu)
        {
        case 1:
            menuMember(root);
            break;
        case 2:
            menuLatihan(headPaket);
            break;
        case 3:
            menuRelasi(headRelasi, root, headPaket);
            break;
        default:
            break;
        }
    } while (pilihanMenu != 4);
    return 0;
}