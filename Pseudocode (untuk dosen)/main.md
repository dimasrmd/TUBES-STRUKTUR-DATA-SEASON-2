# PSEUDOCODE - main.cpp
## Gym & Fitness Tracker System - Main Program

---

### PROGRAM GymFitnessTracker

#### DEKLARASI
```
root: adrMember ← nullptr
headPaket: adrPaket ← nullptr
headRelasi: adrRelasi ← nullptr
pilihanMenu: integer
```

#### ALGORITMA
```
BEGIN
    REPEAT
        // Tampilkan UI Menu Utama
        CLS
        OUTPUT "========== GYM =========="
        OUTPUT "1. Info member"
        OUTPUT "2. Info latihan"
        OUTPUT "3. Relasi Member-Latihan"
        OUTPUT "4. Keluar"
        OUTPUT "-------------------------"
        OUTPUT "Pilih: "
        INPUT pilihanMenu
        
        // Proses pilihan menu
        CASE pilihanMenu OF
            1: 
                menuMember(root)
            2: 
                menuLatihan(headPaket)
            3: 
                menuRelasi(headRelasi, root, headPaket)
            DEFAULT:
                // Tidak melakukan apa-apa
        ENDCASE
        
    UNTIL pilihanMenu = 4
    
    RETURN 0
END
```

---

### PENJELASAN PROGRAM

**Tujuan:**
Program utama untuk sistem manajemen gym dan fitness tracker yang mengelola data member, paket latihan, dan relasi antara member dengan paket latihan mereka.

**Struktur Data yang Digunakan:**
1. **Binary Search Tree (BST)** - `adrMember root`
   - Menyimpan data member dalam struktur tree terurut berdasarkan nama
   
2. **Multi Linked List (MLL)** - `adrPaket headPaket`
   - Menyimpan daftar paket latihan
   - Setiap paket memiliki linked list gerakan-gerakan latihan
   
3. **Single Linked List** - `adrRelasi headRelasi`
   - Menyimpan relasi/assignment antara member dengan paket latihan

**Alur Program:**
1. Inisialisasi semua struktur data dengan nullptr
2. Tampilkan menu utama dengan 4 pilihan
3. Proses pilihan user:
   - Pilihan 1: Buka menu pengelolaan member (BST)
   - Pilihan 2: Buka menu pengelolaan paket latihan (MLL)
   - Pilihan 3: Buka menu relasi member-paket (SLL)
   - Pilihan 4: Keluar dari program
4. Ulangi sampai user memilih keluar (pilihan 4)

**Catatan:**
- Program menggunakan referencing (`&`) untuk melewatkan struktur data ke fungsi menu agar perubahan data dapat tersimpan
- Menggunakan `system("cls")` untuk membersihkan layar sebelum menampilkan menu
- Input validation tidak dilakukan di level main, diserahkan ke masing-masing fungsi menu
