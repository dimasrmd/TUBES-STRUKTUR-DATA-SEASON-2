#include "gym.h"

adrMember createNode(infoMember info) {
    adrMember p = new member;
    p->info_member.nama_member  = info.nama_member;
    p->info_member.target_berat  = info.target_berat;
    p->info_member.tinggi_badan = info.tinggi_badan;
    for (int i = 0; i < 12; i++) p->info_member.progress_berat[i] = 0;
    p->left = nullptr;
    p->right = nullptr;
    return p;
}

void insertNode(adrMember &root, adrMember node) {
    // konsep inputnya
    if (root == nullptr) {
        root = node;
        cout << "Member dengan nama " << node->info_member.nama_member << " berhasil terdaftar.\n";
    } else if (node->info_member.nama_member < root->info_member.nama_member) {
        insertNode(root->left, node);
    } else if (node->info_member.nama_member > root->info_member.nama_member) {
        insertNode(root->right, node);
    } else {
        cout << "Member dengan nama " << node->info_member.nama_member << " sudah terdaftar.\n";
        delete node;
    }
}

void tambahMember(adrMember &root) {
    // variabel data
    adrMember p;
    infoMember info;

    // UI MENU TAMBAH MEMBER
    system("cls");
    cout << setfill('=') << setw(10) << "" << " Tambah Member " << setfill('=') << setw(10) << "" << endl; cout << setfill(' ');
    cin.ignore();
    
    // Validasi: nama tidak boleh kosong
    do {
        cout << "Nama                  : "; getline(cin, info.nama_member);
        if (info.nama_member.empty()) {
            cout << "Nama tidak boleh kosong!\n";
        }
    } while (info.nama_member.empty());
    
    // Validasi: target berat (1-300 kg)
    do {
        cout << "Target Berat Badan    : "; cin >> info.target_berat;
        if (info.target_berat <= 0 || info.target_berat > 300) {
            cout << "Target berat harus antara 1-300 kg!\n";
        }
    } while (info.target_berat <= 0 || info.target_berat > 300);
    
    // Validasi: tinggi badan (50-250 cm)
    do {
        cout << "Tinggi Badan          : "; cin >> info.tinggi_badan;
        if (info.tinggi_badan <= 50 || info.tinggi_badan > 250) {
            cout << "Tinggi badan harus antara 50-250 cm!\n";
        }
    } while (info.tinggi_badan <= 50 || info.tinggi_badan > 250);
    cout << setfill('-') << setw(35) << "" << endl; cout << setfill(' ');
    
    // insert data ke tree sekaligus membuat node
    p = createNode(info);
    insertNode(root, p);
}

adrMember findNode(adrMember root, string nama) {
    // cek apakah tree kosong
    if (root == nullptr) return nullptr;
    
    // cek nama
    if (root->info_member.nama_member == nama) return root;

    // bagian pencarian
    if (nama < root->info_member.nama_member) return findNode(root->left, nama);
    else if (nama > root->info_member.nama_member) return findNode(root->right, nama);

    return nullptr;
}

void updateProgMember(adrMember &root) {
    // Variabel Data
    adrMember p;
    infoMember data;
    int bulan;

    // UI UPDATE MEMBER
    system("cls");
    cout << setfill('=') << setw(10) << "" << " UPDATE PROGRESS MEMBER " << setfill('=') << setw(10) << "" << endl; cout << setfill(' ');
    cin.ignore();
    
    // Validasi: nama tidak boleh kosong
    do {
        cout << "Nama: "; getline(cin, data.nama_member);
        if (data.nama_member.empty()) {
            cout << "Nama tidak boleh kosong!\n";
        }
    } while (data.nama_member.empty());
    
    p = findNode(root, data.nama_member);
    if (p == nullptr) {
        cout << "Nama " << data.nama_member << " belum terdaftar";
        cin.ignore(); cin.get();
        return;
    }

    // Validasi: bulan (1-12)
    do {
        cout << "Bulan ke-(1 s.d 12): "; cin >> bulan;
        if (bulan < 1 || bulan > 12) {
            cout << "Bulan harus antara 1-12!\n";
        }
    } while (bulan < 1 || bulan > 12);
    cin.ignore();
    
    // Validasi: berat badan (1-300 kg)
    do {
        cout << "Berat Badan: "; cin >> data.target_berat;
        if (data.target_berat <= 0 || data.target_berat > 300) {
            cout << "Berat harus antara 1-300 kg!\n";
        }
    } while (data.target_berat <= 0 || data.target_berat > 300);
    cout << setfill('-') << setw(43) << "" << endl; cout << setfill(' ');

    // update data progress perbulan
    p->info_member.progress_berat[bulan-1] = data.target_berat;
    cout << "Update! " << data.nama_member << " pada bulan ke-" << bulan << " dengan berat badan " << data.target_berat;
}

void menuMember(adrMember &root) {
    // variabel utilitas
    int pilihanMenu;

    do {
        // UI MENU MEMBER
        system("cls");
        cout << setfill('=') << setw(10) << "" << " Member " << setfill('=') << setw(10) << "" << endl; cout << setfill(' ');
        cout << "1. Tambah member\n";
        cout << "2. Update progress member\n";
        cout << "3. Lihat detail member\n";
        cout << "4. Lihat semua member\n";
        cout << "5. Hapus member\n";
        cout << "6. Statistik Member\n";
        cout << "7. Kembali\n";
        cout << setfill('-') << setw(32) << "" << endl; cout << setfill(' ');
        cout << "Pilihan: "; cin >> pilihanMenu;

        // Pilihan
        switch (pilihanMenu)
        {
        case 1:
            tambahMember(root);
            break;
        case 2:
            updateProgMember(root);
            break;
        case 3:
            detailMember(root);
            break;
        case 4:
            lihatSemuaMember(root);
            break;
        case 5:
            hapusMember(root);
            break;
        case 6:
            menuStatistikMember(root);
            break;
        
        default:
            break;
        }

    } while (pilihanMenu != 7);
}

// Fungsi Inorder Traversal (Left -> Root -> Right)
void inorder(adrMember root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << "- " << root->info_member.nama_member 
             << " (Target BB: " << root->info_member.target_berat << " kg, "
             << "TB: " << root->info_member.tinggi_badan << " cm)\n";
        inorder(root->right);
    }
}

// Fungsi Preorder Traversal (Root -> Left -> Right)
void preorder(adrMember root) {
    if (root != nullptr) {
        cout << "- " << root->info_member.nama_member 
             << " (Target BB: " << root->info_member.target_berat << " kg, "
             << "TB: " << root->info_member.tinggi_badan << " cm)\n";
        preorder(root->left);
        preorder(root->right);
    }
}

// Fungsi Postorder Traversal (Left -> Right -> Root)
void postorder(adrMember root) {
    if (root != nullptr) {
        postorder(root->left);
        postorder(root->right);
        cout << "- " << root->info_member.nama_member 
             << " (Target BB: " << root->info_member.target_berat << " kg, "
             << "TB: " << root->info_member.tinggi_badan << " cm)\n";
    }
}

// Menu Lihat Semua Member
void lihatSemuaMember(adrMember root) {
    int pilihan;
    
    system("cls");
    cout << setfill('=') << setw(10) << "" << " LIHAT SEMUA MEMBER " << setfill('=') << setw(10) << "" << endl;
    cout << setfill(' ');
    
    if (root == nullptr) {
        cout << "Belum ada member yang terdaftar.\n";
        cin.ignore(); cin.get();
        return;
    }
    
    cout << "1. Inorder (Alfabetis)\n";
    cout << "2. Preorder\n";
    cout << "3. Postorder\n";
    cout << setfill('-') << setw(40) << "" << endl;
    cout << setfill(' ');
    cout << "Pilihan: "; cin >> pilihan;
    
    cout << "\nDaftar Member:\n";
    switch(pilihan) {
        case 1: inorder(root); break;
        case 2: preorder(root); break;
        case 3: postorder(root); break;
        default: cout << "Pilihan tidak valid\n";
    }
    
    cin.ignore(); cin.get();
}

// Helper: Mencari node dengan nilai minimum (paling kiri)
adrMember findMin(adrMember root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// Fungsi Delete Node dari BST
adrMember deleteNode(adrMember root, string nama) {
    if (root == nullptr) return nullptr;
    
    // Cari node yang akan dihapus
    if (nama < root->info_member.nama_member) {
        root->left = deleteNode(root->left, nama);
    } else if (nama > root->info_member.nama_member) {
        root->right = deleteNode(root->right, nama);
    } else {
        // Node ditemukan, 3 kasus:
        
        // Kasus 1 & 2: Node leaf atau hanya punya 1 child
        if (root->left == nullptr) {
            adrMember temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            adrMember temp = root->left;
            delete root;
            return temp;
        }
        
        // Kasus 3: Node punya 2 children
        // Cari inorder successor (smallest in right subtree)
        adrMember temp = findMin(root->right);
        
        // Copy data successor ke node ini
        root->info_member = temp->info_member;
        
        // Hapus successor
        root->right = deleteNode(root->right, temp->info_member.nama_member);
    }
    
    return root;
}

// Menu Hapus Member
void hapusMember(adrMember &root) {
    string nama;
    
    system("cls");
    cout << setfill('=') << setw(10) << "" << " HAPUS MEMBER " << setfill('=') << setw(10) << "" << endl;
    cout << setfill(' ');
    
    if (root == nullptr) {
        cout << "Belum ada member yang terdaftar.\n";
        cin.ignore(); cin.get();
        return;
    }
    
    cin.ignore();
    
    // Validasi: nama tidak boleh kosong
    do {
        cout << "Nama member yang akan dihapus: "; getline(cin, nama);
        if (nama.empty()) {
            cout << "Nama tidak boleh kosong!\n";
        }
    } while (nama.empty());
    cout << setfill('-') << setw(34) << "" << endl;
    cout << setfill(' ');
    
    // Cek apakah member ada
    adrMember found = findNode(root, nama);
    if (found == nullptr) {
        cout << "Member dengan nama " << nama << " tidak ditemukan.\n";
    } else {
        root = deleteNode(root, nama);
        cout << "Member dengan nama " << nama << " berhasil dihapus.\n";
    }
    
    cin.get();
}

// Menu Lihat Detail Member
void detailMember(adrMember root) {
    string nama;
    
    system("cls");
    cout << setfill('=') << setw(10) << "" << " DETAIL MEMBER " << setfill('=') << setw(10) << "" << endl;
    cout << setfill(' ');
    
    if (root == nullptr) {
        cout << "Belum ada member yang terdaftar.\n";
        cin.ignore(); cin.get();
        return;
    }
    
    cin.ignore();
    
    // Validasi: nama tidak boleh kosong
    do {
        cout << "Nama member: "; getline(cin, nama);
        if (nama.empty()) {
            cout << "Nama tidak boleh kosong!\n";
        }
    } while (nama.empty());
    cout << setfill('-') << setw(34) << "" << endl;
    cout << setfill(' ');
    
    // Cari member
    adrMember found = findNode(root, nama);
    if (found == nullptr) {
        cout << "Member dengan nama " << nama << " tidak ditemukan.\n";
    } else {
        cout << "\nInformasi Member:\n";
        cout << "Nama                  : " << found->info_member.nama_member << endl;
        cout << "Target Berat Badan    : " << found->info_member.target_berat << " kg\n";
        cout << "Tinggi Badan          : " << found->info_member.tinggi_badan << " cm\n";
        
        cout << "\nProgress Berat Badan per Bulan:\n";
        bool hasProgress = false;
        for (int i = 0; i < 12; i++) {
            if (found->info_member.progress_berat[i] != 0) {
                cout << "Bulan " << (i+1) << "  : " << found->info_member.progress_berat[i] << " kg\n";
                hasProgress = true;
            }
        }
        
        if (!hasProgress) {
            cout << "(Belum ada data progress)\n";
        }
    }
    
    cin.get();
}

// ==================== FUNGSI MULTI LINKED LIST - PAKET LATIHAN ====================

// Membuat node paket latihan baru
adrPaket createPaket(string nama, string kesulitan) {
    adrPaket p = new paketLatihan;
    p->nama_paket = nama;
    p->kesulitan = kesulitan;
    p->next = nullptr;
    p->first = nullptr;
    return p;
}

// Membuat node gerakan baru
adrGerakan createGerakan(string nama, bool isBerbasisWaktu, int frekuensi, int sets) {
    adrGerakan p = new jenisGerakan;
    p->nama_gerakan = nama;
    p->isBerbasisWaktu = isBerbasisWaktu;
    p->frekuensi = frekuensi;
    p->sets = sets;
    p->next = nullptr;
    return p;
}

// Insert paket latihan ke list (di awal)
void insertPaket(adrPaket &head, adrPaket newPaket) {
    if (head == nullptr) {
        head = newPaket;
    } else {
        newPaket->next = head;
        head = newPaket;
    }
}

// Insert gerakan ke paket latihan tertentu (di akhir)
void insertGerakan(adrPaket paket, adrGerakan newGerakan) {
    if (paket->first == nullptr) {
        paket->first = newGerakan;
    } else {
        adrGerakan temp = paket->first;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newGerakan;
    }
}

// Mencari paket latihan berdasarkan nama dan kesulitan
adrPaket findPaket(adrPaket head, string nama, string kesulitan) {
    adrPaket temp = head;
    while (temp != nullptr) {
        if (temp->nama_paket == nama && temp->kesulitan == kesulitan) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Menghitung jumlah paket dengan nama tertentu
int countPaketByName(adrPaket head, string nama) {
    adrPaket temp = head;
    int count = 0;
    while (temp != nullptr) {
        if (temp->nama_paket == nama) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}

// Mencari paket hanya berdasarkan nama (tanpa kesulitan)
adrPaket findPaketByName(adrPaket head, string nama) {
    adrPaket temp = head;
    while (temp != nullptr) {
        if (temp->nama_paket == nama) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Mengecek apakah gerakan dengan nama tertentu sudah ada dalam paket
bool isGerakanExists(adrPaket paket, string namaGerakan) {
    adrGerakan temp = paket->first;
    while (temp != nullptr) {
        if (temp->nama_gerakan == namaGerakan) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Hapus paket latihan
void deletePaket(adrPaket &head, string nama, string kesulitan) {
    if (head == nullptr) return;
    
    adrPaket temp = head;
    adrPaket prev = nullptr;
    
    // Cari paket yang akan dihapus
    while (temp != nullptr && !(temp->nama_paket == nama && temp->kesulitan == kesulitan)) {
        prev = temp;
        temp = temp->next;
    }
    
    // Jika tidak ditemukan
    if (temp == nullptr) {
        cout << "Paket tidak ditemukan.\n";
        return;
    }
    
    // Hapus semua gerakan di paket
    adrGerakan gerakan = temp->first;
    while (gerakan != nullptr) {
        adrGerakan toDelete = gerakan;
        gerakan = gerakan->next;
        delete toDelete;
    }
    
    // Hapus paket dari list
    if (prev == nullptr) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    
    delete temp;
    cout << "Paket " << nama << " (" << kesulitan << ") berhasil dihapus.\n";
}

// Hapus gerakan dari paket
void deleteGerakan(adrPaket paket, string namaGerakan) {
    if (paket->first == nullptr) {
        cout << "Paket tidak memiliki gerakan.\n";
        return;
    }
    
    adrGerakan temp = paket->first;
    adrGerakan prev = nullptr;
    
    // Cari gerakan yang akan dihapus
    while (temp != nullptr && temp->nama_gerakan != namaGerakan) {
        prev = temp;
        temp = temp->next;
    }
    
    // Jika tidak ditemukan
    if (temp == nullptr) {
        cout << "Gerakan tidak ditemukan.\n";
        return;
    }
    
    // Hapus gerakan dari list
    if (prev == nullptr) {
        paket->first = temp->next;
    } else {
        prev->next = temp->next;
    }
    
    delete temp;
    cout << "Gerakan " << namaGerakan << " berhasil dihapus.\n";
}

// ==================== MENU LATIHAN ====================

void tambahPaket(adrPaket &headPaket) {
    string nama, kesulitan;
    
    system("cls");
    cout << setfill('=') << setw(10) << "" << " TAMBAH PAKET LATIHAN " << setfill('=') << setw(10) << "" << endl;
    cout << setfill(' ');
    
    cin.ignore();
    
    // Validasi: nama paket tidak boleh kosong
    do {
        cout << "Nama Paket         : "; getline(cin, nama);
        if (nama.empty()) {
            cout << "Nama paket tidak boleh kosong!\n";
        }
    } while (nama.empty());
    
    // Input kesulitan dengan menu pilihan
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
    
    cout << setfill('-') << setw(41) << "" << endl;
    cout << setfill(' ');
    
    // Cek apakah paket sudah ada
    adrPaket found = findPaket(headPaket, nama, kesulitan);
    if (found != nullptr) {
        cout << "Paket " << nama << " (" << kesulitan << ") sudah ada.\n";
    } else {
        adrPaket newPaket = createPaket(nama, kesulitan);
        insertPaket(headPaket, newPaket);
        cout << "Paket " << nama << " (" << kesulitan << ") berhasil ditambahkan.\n";
    }
    
    cin.ignore(); cin.get();
}

void tambahGerakan(adrPaket headPaket) {
    string namaPaket, kesulitan, namaGerakan, jenisInput;
    int frekuensi, sets;
    bool isBerbasisWaktu;
    
    system("cls");
    cout << setfill('=') << setw(10) << "" << " TAMBAH GERAKAN KE PAKET " << setfill('=') << setw(10) << "" << endl;
    cout << setfill(' ');
    
    if (headPaket == nullptr) {
        cout << "Belum ada paket latihan. Tambahkan paket terlebih dahulu.\n";
        cin.ignore(); cin.get();
        return;
    }
    
    cin.ignore();
    cout << "Nama Paket         : "; getline(cin, namaPaket);
    
    // Smart search: hitung jumlah paket dengan nama tersebut
    int count = countPaketByName(headPaket, namaPaket);
    adrPaket paket = nullptr;
    
    if (count == 0) {
        cout << "Paket tidak ditemukan.\n";
        cin.ignore(); cin.get();
        return;
    } else if (count == 1) {
        // Jika hanya 1 paket, langsung gunakan
        paket = findPaketByName(headPaket, namaPaket);
    } else {
        // Jika lebih dari 1, tanyakan kesulitan
        cout << "Kesulitan          : "; getline(cin, kesulitan);
        paket = findPaket(headPaket, namaPaket, kesulitan);
        if (paket == nullptr) {
            cout << "Paket tidak ditemukan.\n";
            cin.ignore(); cin.get();
            return;
        }
    }
    
    // Validasi: nama gerakan tidak boleh kosong
    do {
        cout << "Nama Gerakan       : "; getline(cin, namaGerakan);
        if (namaGerakan.empty()) {
            cout << "Nama gerakan tidak boleh kosong!\n";
        }
    } while (namaGerakan.empty());
    
    // Validasi: cek apakah gerakan sudah ada
    if (isGerakanExists(paket, namaGerakan)) {
        cout << "Gerakan dengan nama \"" << namaGerakan << "\" sudah ada dalam paket ini.\n";
        cin.ignore(); cin.get();
        return;
    }
    
    // Validasi: berbasis waktu (y/n) - tidak boleh kosong dan harus y atau n
    do {
        cout << "Berbasis waktu? (y/n): "; getline(cin, jenisInput);
        if (jenisInput.empty()) {
            cout << "Input tidak boleh kosong!\n";
        } else if (jenisInput != "y" && jenisInput != "Y" && jenisInput != "n" && jenisInput != "N") {
            cout << "Input harus 'y' atau 'n'!\n";
            jenisInput = ""; // Reset agar loop lanjut
        }
    } while (jenisInput.empty());
    
    if (jenisInput == "y" || jenisInput == "Y") {
        // Berbasis waktu - validasi durasi
        isBerbasisWaktu = true;
        do {
            cout << "Durasi (detik)     : "; cin >> frekuensi;
            if (frekuensi <= 0) {
                cout << "Durasi harus lebih dari 0!\n";
            }
        } while (frekuensi <= 0);
        sets = 0; // Tidak ada sets untuk berbasis waktu
    } else {
        // Berbasis reps - validasi reps dan sets
        isBerbasisWaktu = false;
        do {
            cout << "Reps               : "; cin >> frekuensi;
            if (frekuensi <= 0) {
                cout << "Reps harus lebih dari 0!\n";
            }
        } while (frekuensi <= 0);
        
        do {
            cout << "Sets               : "; cin >> sets;
            if (sets <= 0) {
                cout << "Sets harus lebih dari 0!\n";
            }
        } while (sets <= 0);
    }
    
    cout << setfill('-') << setw(44) << "" << endl;
    cout << setfill(' ');
    
    adrGerakan newGerakan = createGerakan(namaGerakan, isBerbasisWaktu, frekuensi, sets);
    insertGerakan(paket, newGerakan);
    cout << "Gerakan " << namaGerakan << " berhasil ditambahkan ke paket " << namaPaket << ".\n";
    
    cin.ignore();
}

void hapusPaket(adrPaket &headPaket) {
    string nama, kesulitan;
    
    system("cls");
    cout << setfill('=') << setw(10) << "" << " HAPUS PAKET LATIHAN " << setfill('=') << setw(10) << "" << endl;
    cout << setfill(' ');
    
    if (headPaket == nullptr) {
        cout << "Belum ada paket latihan.\n";
        cin.ignore(); cin.get();
        return;
    }
    
    cin.ignore();
    cout << "Nama Paket         : "; getline(cin, nama);
    cout << "Kesulitan          : "; getline(cin, kesulitan);
    cout << setfill('-') << setw(40) << "" << endl;
    cout << setfill(' ');
    
    deletePaket(headPaket, nama, kesulitan);
    
    cin.ignore();
}

void hapusGerakan(adrPaket headPaket) {
    string namaPaket, kesulitan, namaGerakan;
    
    system("cls");
    cout << setfill('=') << setw(10) << "" << " HAPUS GERAKAN DARI PAKET " << setfill('=') << setw(10) << "" << endl;
    cout << setfill(' ');
    
    if (headPaket == nullptr) {
        cout << "Belum ada paket latihan.\n";
        cin.ignore(); cin.get();
        return;
    }
    
    cin.ignore();
    cout << "Nama Paket         : "; getline(cin, namaPaket);
    
    // Smart search: hitung jumlah paket dengan nama tersebut
    int count = countPaketByName(headPaket, namaPaket);
    adrPaket paket = nullptr;
    
    if (count == 0) {
        cout << "Paket tidak ditemukan.\n";
        cin.ignore(); cin.get();
        return;
    } else if (count == 1) {
        // Jika hanya 1 paket, langsung gunakan
        paket = findPaketByName(headPaket, namaPaket);
    } else {
        // Jika lebih dari 1, tanyakan kesulitan
        cout << "Kesulitan          : "; getline(cin, kesulitan);
        paket = findPaket(headPaket, namaPaket, kesulitan);
        if (paket == nullptr) {
            cout << "Paket tidak ditemukan.\n";
            cin.ignore(); cin.get();
            return;
        }
    }
    
    cout << "Nama Gerakan       : "; getline(cin, namaGerakan);
    cout << setfill('-') << setw(45) << "" << endl;
    cout << setfill(' ');
    
    deleteGerakan(paket, namaGerakan);
    
    cin.ignore();
}

void updatePaket(adrPaket headPaket) {
    string nama, kesulitan, namaBaru, kesulitanBaru;
    
    system("cls");
    cout << setfill('=') << setw(10) << "" << " UPDATE PAKET LATIHAN " << setfill('=') << setw(10) << "" << endl;
    cout << setfill(' ');
    
    if (headPaket == nullptr) {
        cout << "Belum ada paket latihan.\n";
        cin.ignore(); cin.get();
        return;
    }
    
    cin.ignore();
    cout << "Nama Paket Lama    : "; getline(cin, nama);
    
    // Input kesulitan lama dengan menu
    int pilihanKesulitanLama;
    cout << "\nKesulitan Lama:\n";
    cout << "1. Beginner\n";
    cout << "2. Intermediate\n";
    cout << "3. Advanced\n";
    cout << "Pilihan (1-3)      : "; cin >> pilihanKesulitanLama;
    
    switch(pilihanKesulitanLama) {
        case 1: kesulitan = "Beginner"; break;
        case 2: kesulitan = "Intermediate"; break;
        case 3: kesulitan = "Advanced"; break;
        default: 
            kesulitan = "Beginner";
            cout << "Pilihan tidak valid, default ke Beginner.\n";
            break;
    }
    
    adrPaket paket = findPaket(headPaket, nama, kesulitan);
    if (paket == nullptr) {
        cout << "Paket tidak ditemukan.\n";
        cin.ignore(); cin.get();
        return;
    }
    
    cin.ignore();
    cout << "\n--- Data Baru ---\n";
    cout << "Nama Paket Baru    : "; getline(cin, namaBaru);
    
    // Input kesulitan baru dengan menu
    int pilihanKesulitanBaru;
    cout << "\nKesulitan Baru:\n";
    cout << "1. Beginner\n";
    cout << "2. Intermediate\n";
    cout << "3. Advanced\n";
    cout << "Pilihan (1-3)      : "; cin >> pilihanKesulitanBaru;
    
    switch(pilihanKesulitanBaru) {
        case 1: kesulitanBaru = "Beginner"; break;
        case 2: kesulitanBaru = "Intermediate"; break;
        case 3: kesulitanBaru = "Advanced"; break;
        default: 
            kesulitanBaru = "Beginner";
            cout << "Pilihan tidak valid, default ke Beginner.\n";
            break;
    }
    cout << setfill('-') << setw(41) << "" << endl;
    cout << setfill(' ');
    
    paket->nama_paket = namaBaru;
    paket->kesulitan = kesulitanBaru;
    cout << "Paket berhasil diupdate.\n";
    
    cin.ignore();
}

void updateGerakan(adrPaket headPaket) {
    string namaPaket, kesulitan, namaGerakan, namaGerakanBaru, jenisInput;
    int frekuensiBaru, setsBaru;
    bool isBerbasisWaktu;
    
    system("cls");
    cout << setfill('=') << setw(10) << "" << " UPDATE GERAKAN " << setfill('=') << setw(10) << "" << endl;
    cout << setfill(' ');
    
    if (headPaket == nullptr) {
        cout << "Belum ada paket latihan.\n";
        cin.ignore(); cin.get();
        return;
    }
    
    cin.ignore();
    cout << "Nama Paket         : "; getline(cin, namaPaket);
    
    // Smart search: hitung jumlah paket dengan nama tersebut
    int count = countPaketByName(headPaket, namaPaket);
    adrPaket paket = nullptr;
    
    if (count == 0) {
        cout << "Paket tidak ditemukan.\n";
        cin.ignore(); cin.get();
        return;
    } else if (count == 1) {
        // Jika hanya 1 paket, langsung gunakan
        paket = findPaketByName(headPaket, namaPaket);
    } else {
        // Jika lebih dari 1, tanyakan kesulitan
        cout << "Kesulitan          : "; getline(cin, kesulitan);
        paket = findPaket(headPaket, namaPaket, kesulitan);
        if (paket == nullptr) {
            cout << "Paket tidak ditemukan.\n";
            cin.ignore(); cin.get();
            return;
        }
    }
    
    cout << "Nama Gerakan Lama  : "; getline(cin, namaGerakan);
    
    // Cari gerakan
    adrGerakan gerakan = paket->first;
    while (gerakan != nullptr && gerakan->nama_gerakan != namaGerakan) {
        gerakan = gerakan->next;
    }
    
    if (gerakan == nullptr) {
        cout << "Gerakan tidak ditemukan.\n";
        cin.ignore(); cin.get();
        return;
    }
    
    cout << "\n--- Data Baru ---\n";
    cout << "Nama Gerakan Baru  : "; getline(cin, namaGerakanBaru);
    cout << "Berbasis waktu? (y/n): "; getline(cin, jenisInput);
    
    if (jenisInput == "y" || jenisInput == "Y") {
        // Berbasis waktu
        isBerbasisWaktu = true;
        cout << "Durasi (detik)     : "; cin >> frekuensiBaru;
        setsBaru = 0; // Tidak ada sets untuk berbasis waktu
    } else {
        // Berbasis reps
        isBerbasisWaktu = false;
        cout << "Reps               : "; cin >> frekuensiBaru;
        cout << "Sets               : "; cin >> setsBaru;
    }
    
    cout << setfill('-') << setw(34) << "" << endl;
    cout << setfill(' ');
    
    gerakan->nama_gerakan = namaGerakanBaru;
    gerakan->isBerbasisWaktu = isBerbasisWaktu;
    gerakan->frekuensi = frekuensiBaru;
    gerakan->sets = setsBaru;
    cout << "Gerakan berhasil diupdate.\n";
    
    cin.ignore();
}

void lihatSemuaPaket(adrPaket headPaket) {
    system("cls");
    cout << setfill('=') << setw(10) << "" << " DAFTAR PAKET LATIHAN " << setfill('=') << setw(10) << "" << endl;
    cout << setfill(' ');
    
    if (headPaket == nullptr) {
        cout << "Belum ada paket latihan.\n";
        cin.ignore(); cin.get();
        return;
    }
    
    // Membersihkan newline dari input menu
    cin.ignore();
    
    adrPaket temp = headPaket;
    int no = 1;
    while (temp != nullptr) {
        cout << "\n" << no++ << ". " << temp->nama_paket << " (" << temp->kesulitan << ")\n";
        
        if (temp->first != nullptr) {
            cout << "   Gerakan:\n";
            adrGerakan gerakan = temp->first;
            while (gerakan != nullptr) {
                cout << "   - " << gerakan->nama_gerakan << " : ";
                if (gerakan->isBerbasisWaktu) {
                    cout << gerakan->frekuensi << " detik\n";
                } else {
                    cout << gerakan->frekuensi << " reps x " << gerakan->sets << " sets\n";
                }
                gerakan = gerakan->next;
            }
        } else {
            cout << "   (Belum ada gerakan)\n";
        }
        
        temp = temp->next;
    }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.get();
}

void detailPaket(adrPaket headPaket) {
    string nama, kesulitan;
    
    system("cls");
    cout << setfill('=') << setw(10) << "" << " DETAIL PAKET LATIHAN " << setfill('=') << setw(10) << "" << endl;
    cout << setfill(' ');
    
    if (headPaket == nullptr) {
        cout << "Belum ada paket latihan.\n";
        cin.ignore(); cin.get();
        return;
    }
    
    cin.ignore();
    cout << "Nama Paket         : "; getline(cin, nama);
    
    // Smart search: hitung jumlah paket dengan nama tersebut
    int count = countPaketByName(headPaket, nama);
    adrPaket paket = nullptr;
    
    if (count == 0) {
        cout << "Paket tidak ditemukan.\n";
        cin.ignore(); cin.get();
        return;
    } else if (count == 1) {
        // Jika hanya 1 paket, langsung gunakan
        paket = findPaketByName(headPaket, nama);
    } else {
        // Jika lebih dari 1, tanyakan kesulitan
        cout << "Kesulitan          : "; getline(cin, kesulitan);
        paket = findPaket(headPaket, nama, kesulitan);
        if (paket == nullptr) {
            cout << "Paket tidak ditemukan.\n";
            cin.ignore(); cin.get();
            return;
        }
    }
    
    cout << setfill('-') << setw(41) << "" << endl;
    cout << setfill(' ');
    
    cout << "\nInformasi Paket:\n";
    cout << "Nama Paket         : " << paket->nama_paket << endl;
    cout << "Kesulitan          : " << paket->kesulitan << endl;
    
    if (paket->first != nullptr) {
        cout << "\nDaftar Gerakan:\n";
        adrGerakan gerakan = paket->first;
        int no = 1;
        while (gerakan != nullptr) {
            cout << no++ << ". " << gerakan->nama_gerakan << " : ";
            if (gerakan->isBerbasisWaktu) {
                cout << gerakan->frekuensi << " detik\n";
            } else {
                cout << gerakan->frekuensi << " reps x " << gerakan->sets << " sets\n";
            }
            gerakan = gerakan->next;
        }
    } else {
        cout << "\n(Belum ada gerakan dalam paket ini)\n";
    }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.get();
}

void menuLatihan(adrPaket &headPaket) {
    int pilihanMenu;
    
    do {
        system("cls");
        cout << setfill('=') << setw(10) << "" << " MENU LATIHAN " << setfill('=') << setw(10) << "" << endl;
        cout << setfill(' ');
        cout << "1. Tambah paket latihan\n";
        cout << "2. Tambah gerakan ke paket\n";
        cout << "3. Hapus paket latihan\n";
        cout << "4. Hapus gerakan dari paket\n";
        cout << "5. Update paket latihan\n";
        cout << "6. Update gerakan\n";
        cout << "7. Lihat semua paket\n";
        cout << "8. Lihat detail paket\n";
        cout << "9. Statistik Paket\n";
        cout << "10. Kembali\n";
        cout << setfill('-') << setw(34) << "" << endl;
        cout << setfill(' ');
        cout << "Pilihan: "; cin >> pilihanMenu;
        
        switch (pilihanMenu) {
            case 1: tambahPaket(headPaket); break;
            case 2: tambahGerakan(headPaket); break;
            case 3: hapusPaket(headPaket); break;
            case 4: hapusGerakan(headPaket); break;
            case 5: updatePaket(headPaket); break;
            case 6: updateGerakan(headPaket); break;
            case 7: lihatSemuaPaket(headPaket); break;
            case 8: detailPaket(headPaket); break;
            case 9: menuStatistikPaket(headPaket); break;
            default: break;
        }
    } while (pilihanMenu != 10);
}

// ==================== FUNGSI PENGOLAHAN BST ====================
// Level Order Traversal (BFS)
void levelOrder(adrMember root) {
    if (root == nullptr) return;
    
    adrMember queue[100];
    int front = 0, rear = 0;
    
    queue[rear++] = root;
    
    while (front < rear) {
        adrMember current = queue[front++];
        cout << "- " << current->info_member.nama_member 
             << " (Target BB: " << current->info_member.target_berat << " kg, "
             << "TB: " << current->info_member.tinggi_badan << " cm)\n";
        
        if (current->left != nullptr) {
            queue[rear++] = current->left;
        }
        if (current->right != nullptr) {
            queue[rear++] = current->right;
        }
    }
}
// Count total member
int countTotalMember(adrMember root) {
    if (root == nullptr) return 0;
    return 1 + countTotalMember(root->left) + countTotalMember(root->right);
}
// Find member dengan target berat tertinggi
adrMember findMemberMaxWeight(adrMember root) {
    if (root == nullptr) return nullptr;
    
    adrMember maxNode = root;
    adrMember leftMax = findMemberMaxWeight(root->left);
    adrMember rightMax = findMemberMaxWeight(root->right);
    
    if (leftMax != nullptr && leftMax->info_member.target_berat > maxNode->info_member.target_berat) {
        maxNode = leftMax;
    }
    if (rightMax != nullptr && rightMax->info_member.target_berat > maxNode->info_member.target_berat) {
        maxNode = rightMax;
    }
    
    return maxNode;
}
// Find member dengan target berat terendah
adrMember findMemberMinWeight(adrMember root) {
    if (root == nullptr) return nullptr;
    
    adrMember minNode = root;
    adrMember leftMin = findMemberMinWeight(root->left);
    adrMember rightMin = findMemberMinWeight(root->right);
    
    if (leftMin != nullptr && leftMin->info_member.target_berat < minNode->info_member.target_berat) {
        minNode = leftMin;
    }
    if (rightMin != nullptr && rightMin->info_member.target_berat < minNode->info_member.target_berat) {
        minNode = rightMin;
    }
    
    return minNode;
}
// Hitung rata-rata target berat
float averageTargetWeight(adrMember root, int &count) {
    if (root == nullptr) {
        count = 0;
        return 0.0;
    }
    
    int leftCount = 0, rightCount = 0;
    float leftSum = averageTargetWeight(root->left, leftCount) * leftCount;
    float rightSum = averageTargetWeight(root->right, rightCount) * rightCount;
    
    count = 1 + leftCount + rightCount;
    return (root->info_member.target_berat + leftSum + rightSum) / count;
}
// ==================== FUNGSI PENGOLAHAN MLL ====================
// Count total paket
int countTotalPaket(adrPaket head) {
    int count = 0;
    adrPaket temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}
// Count gerakan dalam paket
int countGerakanInPaket(adrPaket paket) {
    int count = 0;
    adrGerakan temp = paket->first;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}
// Find paket dengan gerakan terbanyak
adrPaket findPaketMostExercises(adrPaket head) {
    if (head == nullptr) return nullptr;
    
    adrPaket maxPaket = head;
    int maxCount = countGerakanInPaket(head);
    
    adrPaket temp = head->next;
    while (temp != nullptr) {
        int currentCount = countGerakanInPaket(temp);
        if (currentCount > maxCount) {
            maxCount = currentCount;
            maxPaket = temp;
        }
        temp = temp->next;
    }
    
    return maxPaket;
}
// Find paket dengan gerakan tersedikit
adrPaket findPaketLeastExercises(adrPaket head) {
    if (head == nullptr) return nullptr;
    
    adrPaket minPaket = head;
    int minCount = countGerakanInPaket(head);
    
    adrPaket temp = head->next;
    while (temp != nullptr) {
        int currentCount = countGerakanInPaket(temp);
        if (currentCount < minCount) {
            minCount = currentCount;
            minPaket = temp;
        }
        temp = temp->next;
    }
    
    return minPaket;
}
// View paket berdasarkan kesulitan
void viewPaketByKesulitan(adrPaket head, string kesulitan) {
    int count = 0;
    adrPaket temp = head;
    
    cout << "\nPaket dengan kesulitan \"" << kesulitan << "\":\n";
    while (temp != nullptr) {
        if (temp->kesulitan == kesulitan) {
            count++;
            cout << count << ". " << temp->nama_paket 
                 << " (" << countGerakanInPaket(temp) << " gerakan)\n";
        }
        temp = temp->next;
    }
    
    if (count == 0) {
        cout << "(Tidak ada paket dengan kesulitan ini)\n";
    } else {
        cout << "\nTotal: " << count << " paket\n";
    }
}
// ==================== MENU STATISTIK ====================
void menuStatistikMember(adrMember root) {
    system("cls");
    cout << setfill('=') << setw(10) << "" << " STATISTIK MEMBER " << setfill('=') << setw(10) << "" << endl;
    cout << setfill(' ');
    
    if (root == nullptr) {
        cout << "Belum ada member.\n";
        cin.ignore(); cin.get();
        return;
    }
    
    int totalMember = countTotalMember(root);
    adrMember maxMember = findMemberMaxWeight(root);
    adrMember minMember = findMemberMinWeight(root);
    
    int count = 0;
    float avgWeight = averageTargetWeight(root, count);
    
    cout << "\n=== STATISTIK MEMBER ===\n";
    cout << "Total Member           : " << totalMember << " orang\n";
    cout << "Rata-rata Target Berat : " << fixed << setprecision(2) << avgWeight << " kg\n";
    cout << "\nTarget Berat Tertinggi : " << maxMember->info_member.nama_member 
         << " (" << maxMember->info_member.target_berat << " kg)\n";
    cout << "Target Berat Terendah  : " << minMember->info_member.nama_member 
         << " (" << minMember->info_member.target_berat << " kg)\n";
    
    cout << "\nTekan Enter untuk kembali...";
    cin.ignore(); cin.get();
}
void menuStatistikPaket(adrPaket headPaket) {
    system("cls");
    cout << setfill('=') << setw(10) << "" << " STATISTIK PAKET " << setfill('=') << setw(10) << "" << endl;
    cout << setfill(' ');
    
    if (headPaket == nullptr) {
        cout << "Belum ada paket latihan.\n";
        cin.ignore(); cin.get();
        return;
    }
    
    int totalPaket = countTotalPaket(headPaket);
    adrPaket mostEx = findPaketMostExercises(headPaket);
    adrPaket leastEx = findPaketLeastExercises(headPaket);
    
    cout << "\n=== STATISTIK PAKET LATIHAN ===\n";
    cout << "Total Paket : " << totalPaket << " paket\n";
    cout << "\nPaket dengan Gerakan Terbanyak : " << mostEx->nama_paket 
         << " (" << countGerakanInPaket(mostEx) << " gerakan)\n";
    cout << "Paket dengan Gerakan Tersedikit: " << leastEx->nama_paket 
         << " (" << countGerakanInPaket(leastEx) << " gerakan)\n";
    
    cout << "\n=== PAKET PER KESULITAN ===\n";
    viewPaketByKesulitan(headPaket, "Beginner");
    viewPaketByKesulitan(headPaket, "Intermediate");
    viewPaketByKesulitan(headPaket, "Advanced");
    
    cout << "\nTekan Enter untuk kembali...";
    cin.ignore(); cin.get();
}