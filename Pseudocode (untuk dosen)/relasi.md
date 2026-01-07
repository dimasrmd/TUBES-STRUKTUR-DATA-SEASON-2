# PSEUDOCODE - relasi.cpp
## Gym & Fitness Tracker System - Modul Relasi Member-Paket

---

## BAGIAN 1: FUNGSI DASAR RELASI

### FUNCTION createRelasi(namaMember: string, namaPaket: string, kesulitanPaket: string) → adrRelasi
#### ALGORITMA
```
BEGIN
    p ← alokasi memori untuk struct relasi baru
    p.nama_member ← namaMember
    p.nama_paket ← namaPaket
    p.kesulitan_paket ← kesulitanPaket
    p.next ← nullptr
    RETURN p
END
```

---

### PROCEDURE insertRelasi(head: adrRelasi [by reference], newRelasi: adrRelasi)
#### ALGORITMA
```
BEGIN
    IF head = nullptr THEN
        head ← newRelasi
    ELSE
        newRelasi.next ← head
        head ← newRelasi
    ENDIF
END
```
**Catatan:** Menggunakan head insertion untuk efisiensi O(1)

---

### FUNCTION isRelasiExists(head: adrRelasi, namaMember: string, namaPaket: string, kesulitan: string) → boolean
#### ALGORITMA
```
BEGIN
    temp ← head
    
    WHILE temp ≠ nullptr DO
        IF temp.nama_member = namaMember AND 
           temp.nama_paket = namaPaket AND 
           temp.kesulitan_paket = kesulitan THEN
            RETURN true
        ENDIF
        temp ← temp.next
    ENDWHILE
    
    RETURN false
END
```

---

### PROCEDURE deleteRelasi(head: adrRelasi [by reference], namaMember: string, namaPaket: string, kesulitan: string)
#### ALGORITMA
```
BEGIN
    IF head = nullptr THEN
        RETURN
    ENDIF
    
    temp ← head
    prev ← nullptr
    
    // Cari node yang akan dihapus
    WHILE temp ≠ nullptr AND NOT (temp.nama_member = namaMember AND 
          temp.nama_paket = namaPaket AND temp.kesulitan_paket = kesulitan) DO
        prev ← temp
        temp ← temp.next
    ENDWHILE
    
    // Jika tidak ditemukan
    IF temp = nullptr THEN
        OUTPUT "Relasi tidak ditemukan."
        RETURN
    ENDIF
    
    // Hapus node
    IF prev = nullptr THEN
        // Node ada di head
        head ← temp.next
    ELSE
        prev.next ← temp.next
    ENDIF
    
    dealokasi temp
    OUTPUT "Assignment berhasil dihapus."
END
```

---

## BAGIAN 2: MENU DAN FITUR RELASI

### PROCEDURE assignPaketToMember(headRelasi: adrRelasi [by reference], rootMember: adrMember, headPaket: adrPaket)
#### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== ASSIGN PAKET KE MEMBER =========="
    
    CLEAR INPUT BUFFER
    
    // Input dan validasi nama member
    REPEAT
        OUTPUT "Nama Member        : "
        INPUT namaMember (getline)
        IF namaMember kosong THEN
            OUTPUT "Nama member tidak boleh kosong!"
        ENDIF
    UNTIL namaMember tidak kosong
    
    // Validasi member exists
    member ← findNode(rootMember, namaMember)
    IF member = nullptr THEN
        OUTPUT "Member dengan nama \"", namaMember, "\" tidak ditemukan."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    // Input dan validasi nama paket
    REPEAT
        OUTPUT "Nama Paket         : "
        INPUT namaPaket (getline)
        IF namaPaket kosong THEN
            OUTPUT "Nama paket tidak boleh kosong!"
        ENDIF
    UNTIL namaPaket tidak kosong
    
    // Smart search untuk paket
    count ← countPaketByName(headPaket, namaPaket)
    
    IF count = 0 THEN
        OUTPUT "Paket \"", namaPaket, "\" tidak ditemukan."
        WAIT FOR ENTER
        RETURN
    ELSE IF count = 1 THEN
        // Hanya ada 1 paket dengan nama ini, langsung ambil
        paket ← findPaketByName(headPaket, namaPaket)
        kesulitan ← paket.kesulitan
    ELSE
        // Ada multiple paket dengan nama sama, minta kesulitan
        REPEAT
            OUTPUT "Kesulitan          : "
            INPUT kesulitan (getline)
            IF kesulitan kosong THEN
                OUTPUT "Kesulitan tidak boleh kosong!"
            ENDIF
        UNTIL kesulitan tidak kosong
        
        paket ← findPaket(headPaket, namaPaket, kesulitan)
        IF paket = nullptr THEN
            OUTPUT "Paket dengan kesulitan \"", kesulitan, "\" tidak ditemukan."
            WAIT FOR ENTER
            RETURN
        ENDIF
    ENDIF
    
    // Cek duplikasi
    IF isRelasiExists(headRelasi, namaMember, namaPaket, kesulitan) THEN
        OUTPUT "Member \"", namaMember, "\" sudah memiliki paket \"", namaPaket, " (", kesulitan, ")\"."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    // Buat dan insert relasi
    newRelasi ← createRelasi(namaMember, namaPaket, kesulitan)
    insertRelasi(headRelasi, newRelasi)
    
    OUTPUT "--------------------------------------------"
    OUTPUT "Paket \"", namaPaket, " (", kesulitan, ")\" berhasil di-assign ke ", namaMember, "."
    
    WAIT FOR ENTER
END
```

---

### PROCEDURE lihatPaketMember(headRelasi: adrRelasi)
#### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== PAKET MEMBER =========="
    
    IF headRelasi = nullptr THEN
        OUTPUT "Belum ada assignment paket."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    CLEAR INPUT BUFFER
    
    // Input nama member
    REPEAT
        OUTPUT "Nama Member        : "
        INPUT namaMember (getline)
        IF namaMember kosong THEN
            OUTPUT "Nama member tidak boleh kosong!"
        ENDIF
    UNTIL namaMember tidak kosong
    
    OUTPUT "---------------------------------"
    
    // Cari semua paket untuk member ini
    temp ← headRelasi
    count ← 0
    
    OUTPUT "Paket untuk ", namaMember, ":"
    WHILE temp ≠ nullptr DO
        IF temp.nama_member = namaMember THEN
            count ← count + 1
            OUTPUT count, ". ", temp.nama_paket, " (", temp.kesulitan_paket, ")"
        ENDIF
        temp ← temp.next
    ENDWHILE
    
    IF count = 0 THEN
        OUTPUT "(Belum ada paket yang di-assign)"
    ENDIF
    
    WAIT FOR ENTER
END
```

---

### PROCEDURE hapusAssignment(headRelasi: adrRelasi [by reference])
#### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== HAPUS ASSIGNMENT =========="
    
    IF headRelasi = nullptr THEN
        OUTPUT "Belum ada assignment paket."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    CLEAR INPUT BUFFER
    
    // Input nama member
    REPEAT
        OUTPUT "Nama Member        : "
        INPUT namaMember (getline)
        IF namaMember kosong THEN
            OUTPUT "Nama member tidak boleh kosong!"
        ENDIF
    UNTIL namaMember tidak kosong
    
    // Input nama paket
    REPEAT
        OUTPUT "Nama Paket         : "
        INPUT namaPaket (getline)
        IF namaPaket kosong THEN
            OUTPUT "Nama paket tidak boleh kosong!"
        ENDIF
    UNTIL namaPaket tidak kosong
    
    // Input kesulitan dengan menu
    OUTPUT ""
    OUTPUT "Pilih Kesulitan:"
    OUTPUT "1. Beginner"
    OUTPUT "2. Intermediate"
    OUTPUT "3. Advanced"
    OUTPUT "Pilihan (1-3)      : "
    INPUT pilihanKesulitan
    
    CASE pilihanKesulitan OF
        1: kesulitan ← "Beginner"
        2: kesulitan ← "Intermediate"
        3: kesulitan ← "Advanced"
        DEFAULT:
            kesulitan ← "Beginner"
            OUTPUT "Pilihan tidak valid, default ke Beginner."
    ENDCASE
    
    OUTPUT "-------------------------------------"
    
    deleteRelasi(headRelasi, namaMember, namaPaket, kesulitan)
    
    WAIT FOR ENTER
END
```

---

### PROCEDURE lihatAllAssignments(headRelasi: adrRelasi)
#### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== SEMUA ASSIGNMENT =========="
    
    IF headRelasi = nullptr THEN
        OUTPUT "Belum ada assignment paket."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    CLEAR INPUT BUFFER
    
    temp ← headRelasi
    no ← 1
    
    OUTPUT ""
    OUTPUT "Daftar Assignment:"
    WHILE temp ≠ nullptr DO
        OUTPUT no, ". ", temp.nama_member, " -> ", temp.nama_paket, " (", temp.kesulitan_paket, ")"
        no ← no + 1
        temp ← temp.next
    ENDWHILE
    
    WAIT FOR ENTER
END
```

---

### PROCEDURE menuRelasi(headRelasi: adrRelasi [by reference], rootMember: adrMember, headPaket: adrPaket)
#### ALGORITMA
```
BEGIN
    REPEAT
        CLS
        OUTPUT "========== MENU RELASI =========="
        OUTPUT "1. Assign paket ke member"
        OUTPUT "2. Lihat paket member"
        OUTPUT "3. Hapus assignment"
        OUTPUT "4. Lihat semua assignment"
        OUTPUT "5. Kembali"
        OUTPUT "---------------------------------"
        OUTPUT "Pilihan: "
        INPUT pilihanMenu
        
        CASE pilihanMenu OF
            1: assignPaketToMember(headRelasi, rootMember, headPaket)
            2: lihatPaketMember(headRelasi)
            3: hapusAssignment(headRelasi)
            4: lihatAllAssignments(headRelasi)
            DEFAULT: // Tidak melakukan apa-apa
        ENDCASE
        
    UNTIL pilihanMenu = 5
END
```

---

## PENJELASAN MODUL

**Tujuan:**
Modul ini mengelola relasi/assignment antara member dengan paket latihan mereka menggunakan Single Linked List.

**Struktur Data:**
- **Single Linked List (SLL)** untuk menyimpan relasi
- Setiap node berisi: nama_member, nama_paket, kesulitan_paket, next

**Fitur Utama:**
1. **Create Relasi:** Membuat assignment baru antara member dan paket
2. **Insert Relasi:** Menambahkan relasi ke list (head insertion)
3. **Check Exists:** Mencegah duplikasi assignment
4. **Delete Relasi:** Menghapus assignment tertentu
5. **View by Member:** Menampilkan semua paket yang dimiliki satu member
6. **View All:** Menampilkan semua assignment yang ada

**Smart Search Logic:**
- Jika hanya ada 1 paket dengan nama tertentu, sistem langsung menggunakannya
- Jika ada multiple paket dengan nama sama (beda kesulitan), sistem meminta user memilih kesulitan

**Kompleksitas Waktu:**
- Insert: O(1) karena head insertion
- Search/Check exists: O(n) dimana n = jumlah relasi
- Delete: O(n) untuk mencari, O(1) untuk menghapus