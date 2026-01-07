#include "gym.h"

// ==================== RELASI MEMBER-PAKET ====================

// Membuat node relasi baru
adrRelasi createRelasi(string namaMember, string namaPaket, string kesulitanPaket) {
    adrRelasi p = new relasi;
    p->nama_member = namaMember;
    p->nama_paket = namaPaket;
    p->kesulitan_paket = kesulitanPaket;
    p->next = nullptr;
    return p;
}

// Insert relasi ke list (head insertion)
void insertRelasi(adrRelasi &head, adrRelasi newRelasi) {
    if (head == nullptr) {
        head = newRelasi;
    } else {
        newRelasi->next = head;
        head = newRelasi;
    }
}

// Cek apakah relasi sudah ada
bool isRelasiExists(adrRelasi head, string namaMember, string namaPaket, string kesulitan) {
    adrRelasi temp = head;
    while (temp !=nullptr) {
        if (temp->nama_member == namaMember && 
            temp->nama_paket == namaPaket && 
            temp->kesulitan_paket == kesulitan) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Hapus relasi tertentu
void deleteRelasi(adrRelasi &head, string namaMember, string namaPaket, string kesulitan) {
    if (head == nullptr) return;
    
    adrRelasi temp = head;
    adrRelasi prev = nullptr;
    
    while (temp != nullptr && !(temp->nama_member == namaMember && 
           temp->nama_paket == namaPaket && temp->kesulitan_paket == kesulitan)) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == nullptr) {
        cout << "Relasi tidak ditemukan.\n";
        return;
    }
    
    if (prev == nullptr) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    
    delete temp;
    cout << "Assignment berhasil dihapus.\n";
}

// ==================== MENU RELASI ====================

void assignPaketToMember(adrRelasi &headRelasi, adrMember rootMember, adrPaket headPaket) {
    string namaMember, namaPaket, kesulitan;
    
    system("cls");
    cout << setfill('=') << setw(10) << "" << " ASSIGN PAKET KE MEMBER " << setfill('=') << setw(10) << "" << endl;
    cout << setfill(' ');
    
    cin.ignore();
    
    // Input dan validasi nama member
    do {
        cout << "Nama Member        : "; getline(cin, namaMember);
        if (namaMember.empty()) {
            cout << "Nama member tidak boleh kosong!\n";
        }
    } while (namaMember.empty());
    
    // Validasi member exists
    adrMember member = findNode(rootMember, namaMember);
    if (member == nullptr) {
        cout << "Member dengan nama \"" << namaMember << "\" tidak ditemukan.\n";
        cout << "\nTekan Enter untuk kembali...";
        cin.get();
        return;
    }
    
    // Input dan validasi nama paket
    do {
        cout << "Nama Paket         : "; getline(cin, namaPaket);
        if (namaPaket.empty()) {
            cout << "Nama paket tidak boleh kosong!\n";
        }
    } while (namaPaket.empty());
    
    // Smart search untuk paket
    int count = countPaketByName(headPaket, namaPaket);
    adrPaket paket = nullptr;
    
    if (count == 0) {
        cout << "Paket \"" << namaPaket << "\" tidak ditemukan.\n";
        cout << "\nTekan Enter untuk kembali...";
        cin.get();
        return;
    } else if (count == 1) {
        paket = findPaketByName(headPaket, namaPaket);
        kesulitan = paket->kesulitan;
    } else {
        do {
            cout << "Kesulitan          : "; getline(cin, kesulitan);
            if (kesulitan.empty()) {
                cout << "Kesulitan tidak boleh kosong!\n";
            }
        } while (kesulitan.empty());
        
        paket = findPaket(headPaket, namaPaket, kesulitan);
        if (paket == nullptr) {
            cout << "Paket dengan kesulitan \"" << kesulitan << "\" tidak ditemukan.\n";
            cout << "\nTekan Enter untuk kembali...";
            cin.get();
            return;
        }
    }
    
    // Cek duplikasi
    if (isRelasiExists(headRelasi, namaMember, namaPaket, kesulitan)) {
        cout << "Member \"" << namaMember << "\" sudah memiliki paket \"" << namaPaket << " (" << kesulitan << ")\".\n";
        cout << "\nTekan Enter untuk kembali...";
        cin.get();
        return;
    }
    
    // Buat dan insert relasi
    adrRelasi newRelasi = createRelasi(namaMember, namaPaket, kesulitan);
    insertRelasi(headRelasi, newRelasi);
    
    cout << setfill('-') << setw(46) << "" << endl;
    cout << setfill(' ');
    cout << "Paket \"" << namaPaket << " (" << kesulitan << ")\" berhasil di-assign ke " << namaMember << ".\n";
    
    cout << "\nTekan Enter untuk kembali...";
    cin.get();
}

void lihatPaketMember(adrRelasi headRelasi) {
    string namaMember;
    
    system("cls");
    cout << setfill('=') << setw(10) << "" << " PAKET MEMBER " << setfill('=') << setw(10) << "" << endl;
    cout << setfill(' ');
    
    if (headRelasi == nullptr) {
        cout << "Belum ada assignment paket.\n";
        cout << "\nTekan Enter untuk kembali...";
        cin.ignore(); cin.get();
        return;
    }
    
    cin.ignore();
    
    do {
        cout << "Nama Member        : "; getline(cin, namaMember);
        if (namaMember.empty()) {
            cout << "Nama member tidak boleh kosong!\n";
        }
    } while (namaMember.empty());
    
    cout << setfill('-') << setw(33) << "" << endl;
    cout << setfill(' ');
    
    // Cari semua paket untuk member ini
    adrRelasi temp = headRelasi;
    int count = 0;
    
    cout << "\nPaket untuk " << namaMember << ":\n";
    while (temp != nullptr) {
        if (temp->nama_member == namaMember) {
            count++;
            cout << count << ". " << temp->nama_paket << " (" << temp->kesulitan_paket << ")\n";
        }
        temp = temp->next;
    }
    
    if (count == 0) {
        cout << "(Belum ada paket yang di-assign)\n";
    }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.get();
}

void hapusAssignment(adrRelasi &headRelasi) {
    string namaMember, namaPaket, kesulitan;
    
    system("cls");
    cout << setfill('=') << setw(10) << "" << " HAPUS ASSIGNMENT " << setfill('=') << setw(10) << "" << endl;
    cout << setfill(' ');
    
    if (headRelasi == nullptr) {
        cout << "Belum ada assignment paket.\n";
        cout << "\nTekan Enter untuk kembali...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); cin.get();
        return;
    }
    
    cin.ignore();
    
    do {
        cout << "Nama Member        : "; getline(cin, namaMember);
        if (namaMember.empty()) {
            cout << "Nama member tidak boleh kosong!\n";
        }
    } while (namaMember.empty());
    
    do {
        cout << "Nama Paket         : "; getline(cin, namaPaket);
        if (namaPaket.empty()) {
            cout << "Nama paket tidak boleh kosong!\n";
        }
    } while (namaPaket.empty());
    
    // Input kesulitan dengan menu
    int pilihanKesulitan;
    cout << "\nPilih Kesulitan:\n";
    cout << "1. Beginner\n";
    cout << "2. Intermediate\n";
    cout << "3. Advanced\n";
    cout << "Pilihan (1-3)      : "; cin >> pilihanKesulitan;
    
    switch(pilihanKesulitan) {
        case 1: kesulitan = "Beginner"; break;
        case 2: kesulitan = "Intermediate"; break;
        case 3: kesulitan = "Advanced"; break;
        default: 
            kesulitan = "Beginner";
            cout << "Pilihan tidak valid, default ke Beginner.\n";
            break;
    }
    
    cout << setfill('-') << setw(37) << "" << endl;
    cout << setfill(' ');
    
    deleteRelasi(headRelasi, namaMember, namaPaket, kesulitan);
    
    cout << "\nTekan Enter untuk kembali...";
    cin.get();
}

void lihatAllAssignments(adrRelasi headRelasi) {
    system("cls");
    cout << setfill('=') << setw(10) << "" << " SEMUA ASSIGNMENT " << setfill('=') << setw(10) << "" << endl;
    cout << setfill(' ');
    
    if (headRelasi == nullptr) {
        cout << "Belum ada assignment paket.\n";
        cout << "\nTekan Enter untuk kembali...";
        cin.ignore(); cin.get();
        return;
    }
    
    cin.ignore();
    
    adrRelasi temp = headRelasi;
    int no = 1;
    
    cout << "\nDaftar Assignment:\n";
    while (temp != nullptr) {
        cout << no++ << ". " << temp->nama_member << " -> " 
             << temp->nama_paket << " (" << temp->kesulitan_paket << ")\n";
        temp = temp->next;
 }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.get();
}

void menuRelasi(adrRelasi &headRelasi, adrMember rootMember, adrPaket headPaket) {
    int pilihanMenu;
    
    do {
        system("cls");
        cout << setfill('=') << setw(10) << "" << " MENU RELASI " << setfill('=') << setw(10) << "" << endl;
        cout << setfill(' ');
        cout << "1. Assign paket ke member\n";
        cout << "2. Lihat paket member\n";
        cout << "3. Hapus assignment\n";
        cout << "4. Lihat semua assignment\n";
        cout << "5. Kembali\n";
        cout << setfill('-') << setw(33) << "" << endl;
        cout << setfill(' ');
        cout << "Pilihan: "; cin >> pilihanMenu;
        
        switch (pilihanMenu) {
            case 1: assignPaketToMember(headRelasi, rootMember, headPaket); break;
            case 2: lihatPaketMember(headRelasi); break;
            case 3: hapusAssignment(headRelasi); break;
            case 4: lihatAllAssignments(headRelasi); break;
            default: break;
        }
    } while (pilihanMenu != 5);
}
