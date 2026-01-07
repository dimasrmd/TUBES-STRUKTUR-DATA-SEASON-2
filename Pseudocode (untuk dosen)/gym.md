# PSEUDOCODE - gym.cpp
## Gym & Fitness Tracker System - Modul Member & Paket Latihan

---

# DAFTAR ISI

1. [BAGIAN A: FUNGSI MEMBER (BST)](#bagian-a-fungsi-member-bst)
2. [BAGIAN B: FUNGSI TRAVERSAL BST](#bagian-b-fungsi-traversal-bst)
3. [BAGIAN C: MENU MEMBER](#bagian-c-menu-member)
4. [BAGIAN D: FUNGSI MULTI LINKED LIST - PAKET](#bagian-d-fungsi-multi-linked-list-paket)
5. [BAGIAN E: MENU PAKET LATIHAN](#bagian-e-menu-paket-latihan)
6. [BAGIAN F: FUNGSI PENGOLAHAN BST](#bagian-f-fungsi-pengolahan-bst)
7. [BAGIAN G: FUNGSI PENGOLAHAN MLL](#bagian-g-fungsi-pengolahan-mll)
8. [BAGIAN H: MENU STATISTIK](#bagian-h-menu-statistik)

---

# BAGIAN A: FUNGSI MEMBER (BST)

## FUNCTION createNode(info: infoMember) → adrMember
### ALGORITMA
```
BEGIN
    p ← alokasi memori untuk struct member baru
    p.info_member.nama_member ← info.nama_member
    p.info_member.target_berat ← info.target_berat
    p.info_member.tinggi_badan ← info.tinggi_badan
    
    // Inisialisasi array progress_berat dengan 0
    FOR i ← 0 TO 11 DO
        p.info_member.progress_berat[i] ← 0
    ENDFOR
    
    p.left ← nullptr
    p.right ← nullptr
    RETURN p
END
```

---

## PROCEDURE insertNode(root: adrMember [by reference], node: adrMember)
### ALGORITMA
```
BEGIN
    IF root = nullptr THEN
        root ← node
        OUTPUT "Member dengan nama ", node.info_member.nama_member, " berhasil terdaftar."
    ELSE IF node.info_member.nama_member < root.info_member.nama_member THEN
        insertNode(root.left, node)  // Recursive ke kiri
    ELSE IF node.info_member.nama_member > root.info_member.nama_member THEN
        insertNode(root.right, node) // Recursive ke kanan
    ELSE
        // Nama sudah ada (duplicate)
        OUTPUT "Member dengan nama ", node.info_member.nama_member, " sudah terdaftar."
        dealokasi node
    ENDIF
END
```
**Catatan:** Menggunakan recursive insertion untuk BST berdasarkan nama_member

---

## PROCEDURE tambahMember(root: adrMember [by reference])
### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== Tambah Member =========="
    CLEAR INPUT BUFFER
    
    // Validasi: nama tidak boleh kosong
    REPEAT
        OUTPUT "Nama                  : "
        INPUT info.nama_member (getline)
        IF info.nama_member kosong THEN
            OUTPUT "Nama tidak boleh kosong!"
        ENDIF
    UNTIL info.nama_member tidak kosong
    
    // Validasi: target berat (1-300 kg)
    REPEAT
        OUTPUT "Target Berat Badan    : "
        INPUT info.target_berat
        IF info.target_berat ≤ 0 OR info.target_berat > 300 THEN
            OUTPUT "Target berat harus antara 1-300 kg!"
        ENDIF
    UNTIL info.target_berat > 0 AND info.target_berat ≤ 300
    
    // Validasi: tinggi badan (50-250 cm)
    REPEAT
        OUTPUT "Tinggi Badan          : "
        INPUT info.tinggi_badan
        IF info.tinggi_badan ≤ 50 OR info.tinggi_badan > 250 THEN
            OUTPUT "Tinggi badan harus antara 50-250 cm!"
        ENDIF
    UNTIL info.tinggi_badan > 50 AND info.tinggi_badan ≤ 250
    
    OUTPUT "-----------------------------------"
    
    // Buat node dan insert ke tree
    p ← createNode(info)
    insertNode(root, p)
END
```

---

## FUNCTION findNode(root: adrMember, nama: string) → adrMember
### ALGORITMA
```
BEGIN
    // Cek tree kosong
    IF root = nullptr THEN
        RETURN nullptr
    ENDIF
    
    // Cek apakah node saat ini adalah yang dicari
    IF root.info_member.nama_member = nama THEN
        RETURN root
    ENDIF
    
    // Recursive search
    IF nama < root.info_member.nama_member THEN
        RETURN findNode(root.left, nama)
    ELSE IF nama > root.info_member.nama_member THEN
        RETURN findNode(root.right, nama)
    ENDIF
    
    RETURN nullptr
END
```
**Kompleksitas:** O(log n) untuk balanced tree, O(n) untuk skewed tree

---

## PROCEDURE updateProgMember(root: adrMember [by reference])
### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== UPDATE PROGRESS MEMBER =========="
    CLEAR INPUT BUFFER
    
    // Validasi: nama tidak boleh kosong
    REPEAT
        OUTPUT "Nama: "
        INPUT data.nama_member (getline)
        IF data.nama_member kosong THEN
            OUTPUT "Nama tidak boleh kosong!"
        ENDIF
    UNTIL data.nama_member tidak kosong
    
    // Cari member
    p ← findNode(root, data.nama_member)
    IF p = nullptr THEN
        OUTPUT "Nama ", data.nama_member, " belum terdaftar"
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    // Validasi: bulan (1-12)
    REPEAT
        OUTPUT "Bulan ke-(1 s.d 12): "
        INPUT bulan
        IF bulan < 1 OR bulan > 12 THEN
            OUTPUT "Bulan harus antara 1-12!"
        ENDIF
    UNTIL bulan ≥ 1 AND bulan ≤ 12
    
    CLEAR INPUT BUFFER
    
    // Validasi: berat badan (1-300 kg)
    REPEAT
        OUTPUT "Berat Badan: "
        INPUT data.target_berat
        IF data.target_berat ≤ 0 OR data.target_berat > 300 THEN
            OUTPUT "Berat harus antara 1-300 kg!"
        ENDIF
    UNTIL data.target_berat > 0 AND data.target_berat ≤ 300
    
    OUTPUT "-------------------------------------------"
    
    // Update progress di array (index = bulan - 1)
    p.info_member.progress_berat[bulan-1] ← data.target_berat
    OUTPUT "Update! ", data.nama_member, " pada bulan ke-", bulan, " dengan berat badan ", data.target_berat
END
```

---

## FUNCTION findMin(root: adrMember) → adrMember
### ALGORITMA
```
BEGIN
    WHILE root.left ≠ nullptr DO
        root ← root.left
    ENDWHILE
    RETURN root
END
```
**Catatan:** Helper function untuk menemukan node terkecil (paling kiri)

---

## FUNCTION deleteNode(root: adrMember, nama: string) → adrMember
### ALGORITMA
```
BEGIN
    IF root = nullptr THEN
        RETURN nullptr
    ENDIF
    
    // Cari node yang akan dihapus
    IF nama < root.info_member.nama_member THEN
        root.left ← deleteNode(root.left, nama)
    ELSE IF nama > root.info_member.nama_member THEN
        root.right ← deleteNode(root.right, nama)
    ELSE
        // Node ditemukan - 3 kasus:
        
        // KASUS 1: Node tanpa left child
        IF root.left = nullptr THEN
            temp ← root.right
            dealokasi root
            RETURN temp
        // KASUS 2: Node tanpa right child
        ELSE IF root.right = nullptr THEN
            temp ← root.left
            dealokasi root
            RETURN temp
        ENDIF
        
        // KASUS 3: Node dengan 2 children
        // Cari inorder successor (terkecil di right subtree)
        temp ← findMin(root.right)
        
        // Copy data successor ke node ini
        root.info_member ← temp.info_member
        
        // Hapus successor
        root.right ← deleteNode(root.right, temp.info_member.nama_member)
    ENDIF
    
    RETURN root
END
```

---

## PROCEDURE hapusMember(root: adrMember [by reference])
### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== HAPUS MEMBER =========="
    
    IF root = nullptr THEN
        OUTPUT "Belum ada member yang terdaftar."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    CLEAR INPUT BUFFER
    
    // Validasi: nama tidak boleh kosong
    REPEAT
        OUTPUT "Nama member yang akan dihapus: "
        INPUT nama (getline)
        IF nama kosong THEN
            OUTPUT "Nama tidak boleh kosong!"
        ENDIF
    UNTIL nama tidak kosong
    
    OUTPUT "----------------------------------"
    
    // Cek apakah member ada
    found ← findNode(root, nama)
    IF found = nullptr THEN
        OUTPUT "Member dengan nama ", nama, " tidak ditemukan."
    ELSE
        root ← deleteNode(root, nama)
        OUTPUT "Member dengan nama ", nama, " berhasil dihapus."
    ENDIF
    
    WAIT FOR ENTER
END
```

---

## PROCEDURE detailMember(root: adrMember)
### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== DETAIL MEMBER =========="
    
    IF root = nullptr THEN
        OUTPUT "Belum ada member yang terdaftar."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    CLEAR INPUT BUFFER
    
    // Validasi: nama tidak boleh kosong
    REPEAT
        OUTPUT "Nama member: "
        INPUT nama (getline)
        IF nama kosong THEN
            OUTPUT "Nama tidak boleh kosong!"
        ENDIF
    UNTIL nama tidak kosong
    
    OUTPUT "----------------------------------"
    
    // Cari member
    found ← findNode(root, nama)
    IF found = nullptr THEN
        OUTPUT "Member dengan nama ", nama, " tidak ditemukan."
    ELSE
        OUTPUT ""
        OUTPUT "Informasi Member:"
        OUTPUT "Nama                  : ", found.info_member.nama_member
        OUTPUT "Target Berat Badan    : ", found.info_member.target_berat, " kg"
        OUTPUT "Tinggi Badan          : ", found.info_member.tinggi_badan, " cm"
        
        OUTPUT ""
        OUTPUT "Progress Berat Badan per Bulan:"
        hasProgress ← false
        FOR i ← 0 TO 11 DO
            IF found.info_member.progress_berat[i] ≠ 0 THEN
                OUTPUT "Bulan ", (i+1), "  : ", found.info_member.progress_berat[i], " kg"
                hasProgress ← true
            ENDIF
        ENDFOR
        
        IF NOT hasProgress THEN
            OUTPUT "(Belum ada data progress)"
        ENDIF
    ENDIF
    
    WAIT FOR ENTER
END
```

---

# BAGIAN B: FUNGSI TRAVERSAL BST

## PROCEDURE inorder(root: adrMember)
### ALGORITMA
```
BEGIN
    IF root ≠ nullptr THEN
        inorder(root.left)
        OUTPUT "- ", root.info_member.nama_member, " (Target BB: ", root.info_member.target_berat, " kg, TB: ", root.info_member.tinggi_badan, " cm)"
        inorder(root.right)
    ENDIF
END
```
**Urutan:** Left → Root → Right (Hasil terurut alfabetis)

---

## PROCEDURE preorder(root: adrMember)
### ALGORITMA
```
BEGIN
    IF root ≠ nullptr THEN
        OUTPUT "- ", root.info_member.nama_member, " (Target BB: ", root.info_member.target_berat, " kg, TB: ", root.info_member.tinggi_badan, " cm)"
        preorder(root.left)
        preorder(root.right)
    ENDIF
END
```
**Urutan:** Root → Left → Right

---

## PROCEDURE postorder(root: adrMember)
### ALGORITMA
```
BEGIN
    IF root ≠ nullptr THEN
        postorder(root.left)
        postorder(root.right)
        OUTPUT "- ", root.info_member.nama_member, " (Target BB: ", root.info_member.target_berat, " kg, TB: ", root.info_member.tinggi_badan, " cm)"
    ENDIF
END
```
**Urutan:** Left → Right → Root

---

## PROCEDURE levelOrder(root: adrMember)
### ALGORITMA
```
BEGIN
    IF root = nullptr THEN
        RETURN
    ENDIF
    
    // Menggunakan queue untuk BFS
    queue ← empty queue
    enqueue(queue, root)
    
    WHILE queue tidak kosong DO
        current ← dequeue(queue)
        OUTPUT "- ", current.info_member.nama_member, " (Target BB: ", current.info_member.target_berat, " kg, TB: ", current.info_member.tinggi_badan, " cm)"
        
        IF current.left ≠ nullptr THEN
            enqueue(queue, current.left)
        ENDIF
        
        IF current.right ≠ nullptr THEN
            enqueue(queue, current.right)
        ENDIF
    ENDWHILE
END
```
**Urutan:** Level by level (Breadth-First Search)

---

# BAGIAN C: MENU MEMBER

## PROCEDURE lihatSemuaMember(root: adrMember)
### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== LIHAT SEMUA MEMBER =========="
    
    IF root = nullptr THEN
        OUTPUT "Belum ada member yang terdaftar."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    OUTPUT "1. Inorder (Alfabetis)"
    OUTPUT "2. Preorder"
    OUTPUT "3. Postorder"
    OUTPUT "----------------------------------------"
    OUTPUT "Pilihan: "
    INPUT pilihan
    
    OUTPUT ""
    OUTPUT "Daftar Member:"
    CASE pilihan OF
        1: inorder(root)
        2: preorder(root)
        3: postorder(root)
        DEFAULT: OUTPUT "Pilihan tidak valid"
    ENDCASE
    
    WAIT FOR ENTER
END
```

---

## PROCEDURE menuMember(root: adrMember [by reference])
### ALGORITMA
```
BEGIN
    REPEAT
        CLS
        OUTPUT "========== Member =========="
        OUTPUT "1. Tambah member"
        OUTPUT "2. Update progress member"
        OUTPUT "3. Lihat detail member"
        OUTPUT "4. Lihat semua member"
        OUTPUT "5. Hapus member"
        OUTPUT "6. Statistik Member"
        OUTPUT "7. Kembali"
        OUTPUT "--------------------------------"
        OUTPUT "Pilihan: "
        INPUT pilihanMenu
        
        CASE pilihanMenu OF
            1: tambahMember(root)
            2: updateProgMember(root)
            3: detailMember(root)
            4: lihatSemuaMember(root)
            5: hapusMember(root)
            6: menuStatistikMember(root)
            DEFAULT: // Tidak melakukan apa-apa
        ENDCASE
        
    UNTIL pilihanMenu = 7
END
```

---

# BAGIAN D: FUNGSI MULTI LINKED LIST - PAKET

## FUNCTION createPaket(nama: string, kesulitan: string) → adrPaket
### ALGORITMA
```
BEGIN
    p ← alokasi memori untuk struct paketLatihan baru
    p.nama_paket ← nama
    p.kesulitan ← kesulitan
    p.next ← nullptr
    p.first ← nullptr
    RETURN p
END
```

---

## FUNCTION createGerakan(nama: string, isBerbasisWaktu: boolean, frekuensi: integer, sets: integer) → adrGerakan
### ALGORITMA
```
BEGIN
    p ← alokasi memori untuk struct jenisGerakan baru
    p.nama_gerakan ← nama
    p.isBerbasisWaktu ← isBerbasisWaktu
    p.frekuensi ← frekuensi
    p.sets ← sets
    p.next ← nullptr
    RETURN p
END
```

---

## PROCEDURE insertPaket(head: adrPaket [by reference], newPaket: adrPaket)
### ALGORITMA
```
BEGIN
    IF head = nullptr THEN
        head ← newPaket
    ELSE
        newPaket.next ← head
        head ← newPaket
    ENDIF
END
```
**Catatan:** Head insertion untuk efisiensi O(1)

---

## PROCEDURE insertGerakan(paket: adrPaket, newGerakan: adrGerakan)
### ALGORITMA
```
BEGIN
    IF paket.first = nullptr THEN
        paket.first ← newGerakan
    ELSE
        temp ← paket.first
        WHILE temp.next ≠ nullptr DO
            temp ← temp.next
        ENDWHILE
        temp.next ← newGerakan
    ENDIF
END
```
**Catatan:** Tail insertion untuk gerakan dalam paket

---

## FUNCTION findPaket(head: adrPaket, nama: string, kesulitan: string) → adrPaket
### ALGORITMA
```
BEGIN
    temp ← head
    WHILE temp ≠ nullptr DO
        IF temp.nama_paket = nama AND temp.kesulitan = kesulitan THEN
            RETURN temp
        ENDIF
        temp ← temp.next
    ENDWHILE
    RETURN nullptr
END
```

---

## FUNCTION countPaketByName(head: adrPaket, nama: string) → integer
### ALGORITMA
```
BEGIN
    temp ← head
    count ← 0
    WHILE temp ≠ nullptr DO
        IF temp.nama_paket = nama THEN
            count ← count + 1
        ENDIF
        temp ← temp.next
    ENDWHILE
    RETURN count
END
```
**Catatan:** Untuk smart search - cek berapa banyak paket dengan nama sama

---

## FUNCTION findPaketByName(head: adrPaket, nama: string) → adrPaket
### ALGORITMA
```
BEGIN
    temp ← head
    WHILE temp ≠ nullptr DO
        IF temp.nama_paket = nama THEN
            RETURN temp
        ENDIF
        temp ← temp.next
    ENDWHILE
    RETURN nullptr
END
```

---

## FUNCTION isGerakanExists(paket: adrPaket, namaGerakan: string) → boolean
### ALGORITMA  
```
BEGIN
    temp ← paket.first
    WHILE temp ≠ nullptr DO
        IF temp.nama_gerakan = namaGerakan THEN
            RETURN true
        ENDIF
        temp ← temp.next
    ENDWHILE
    RETURN false
END
```

---

## PROCEDURE deletePaket(head: adrPaket [by reference], nama: string, kesulitan: string)
### ALGORITMA
```
BEGIN
    IF head = nullptr THEN
        RETURN
    ENDIF
    
    temp ← head
    prev ← nullptr
    
    // Cari paket yang akan dihapus
    WHILE temp ≠ nullptr AND NOT (temp.nama_paket = nama AND temp.kesulitan = kesulitan) DO
        prev ← temp
        temp ← temp.next
    ENDWHILE
    
    // Jika tidak ditemukan
    IF temp = nullptr THEN
        OUTPUT "Paket tidak ditemukan."
        RETURN
    ENDIF
    
    // Hapus semua gerakan di paket
    gerakan ← temp.first
    WHILE gerakan ≠ nullptr DO
        toDelete ← gerakan
        gerakan ← gerakan.next
        dealokasi toDelete
    ENDWHILE
    
    // Hapus paket dari list
    IF prev = nullptr THEN
        head ← temp.next
    ELSE
        prev.next ← temp.next
    ENDIF
    
    dealokasi temp
    OUTPUT "Paket ", nama, " (", kesulitan, ") berhasil dihapus."
END
```

---

## PROCEDURE deleteGerakan(paket: adrPaket, namaGerakan: string)
### ALGORITMA
```
BEGIN
    IF paket.first = nullptr THEN
        OUTPUT "Paket tidak memiliki gerakan."
        RETURN
    ENDIF
    
    temp ← paket.first
    prev ← nullptr
    
    // Cari gerakan yang akan dihapus
    WHILE temp ≠ nullptr AND temp.nama_gerakan ≠ namaGerakan DO
        prev ← temp
        temp ← temp.next
    ENDWHILE
    
    // Jika tidak ditemukan
    IF temp = nullptr THEN
        OUTPUT "Gerakan tidak ditemukan."
        RETURN
    ENDIF
    
    // Hapus gerakan dari list
    IF prev = nullptr THEN
        paket.first ← temp.next
    ELSE
        prev.next ← temp.next
    ENDIF
    
    dealokasi temp
    OUTPUT "Gerakan ", namaGerakan, " berhasil dihapus."
END
```

---

# BAGIAN E: MENU PAKET LATIHAN

## PROCEDURE tambahPaket(headPaket: adrPaket [by reference])
### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== TAMBAH PAKET LATIHAN =========="
    
    CLEAR INPUT BUFFER
    
    // Validasi: nama paket tidak boleh kosong
    REPEAT
        OUTPUT "Nama Paket         : "
        INPUT nama (getline)
        IF nama kosong THEN
            OUTPUT "Nama paket tidak boleh kosong!"
        ENDIF
    UNTIL nama tidak kosong
    
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
    
    OUTPUT "-----------------------------------------"
    
    // Cek duplikasi
    found ← findPaket(headPaket, nama, kesulitan)
    IF found ≠ nullptr THEN
        OUTPUT "Paket ", nama, " (", kesulitan, ") sudah ada."
    ELSE
        newPaket ← createPaket(nama, kesulitan)
        insertPaket(headPaket, newPaket)
        OUTPUT "Paket ", nama, " (", kesulitan, ") berhasil ditambahkan."
    ENDIF
    
    WAIT FOR ENTER
END
```

---

## PROCEDURE tambahGerakan(headPaket: adrPaket)
### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== TAMBAH GERAKAN KE PAKET =========="
    
    IF headPaket = nullptr THEN
        OUTPUT "Belum ada paket latihan. Tambahkan paket terlebih dahulu."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    CLEAR INPUT BUFFER
    OUTPUT "Nama Paket         : "
    INPUT namaPaket (getline)
    
    // Smart search
    count ← countPaketByName(headPaket, namaPaket)
    
    IF count = 0 THEN
        OUTPUT "Paket tidak ditemukan."
        WAIT FOR ENTER
        RETURN
    ELSE IF count = 1 THEN
        // Hanya 1 paket, langsung gunakan
        paket ← findPaketByName(headPaket, namaPaket)
    ELSE
        // Multiple paket, tanyakan kesulitan
        OUTPUT "Kesulitan          : "
        INPUT kesulitan (getline)
        paket ← findPaket(headPaket, namaPaket, kesulitan)
        IF paket = nullptr THEN
            OUTPUT "Paket tidak ditemukan."
            WAIT FOR ENTER
            RETURN
        ENDIF
    ENDIF
    
    // Validasi: nama gerakan tidak boleh kosong
    REPEAT
        OUTPUT "Nama Gerakan       : "
        INPUT namaGerakan (getline)
        IF namaGerakan kosong THEN
            OUTPUT "Nama gerakan tidak boleh kosong!"
        ENDIF
    UNTIL namaGerakan tidak kosong
    
    // Validasi: cek duplikasi gerakan
    IF isGerakanExists(paket, namaGerakan) THEN
        OUTPUT "Gerakan dengan nama \"", namaGerakan, "\" sudah ada dalam paket ini."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    // Validasi: berbasis waktu (y/n)
    REPEAT
        OUTPUT "Berbasis waktu? (y/n): "
        INPUT jenisInput (getline)
        IF jenisInput kosong THEN
            OUTPUT "Input tidak boleh kosong!"
        ELSE IF jenisInput ≠ "y" AND jenisInput ≠ "Y" AND jenisInput ≠ "n" AND jenisInput ≠ "N" THEN
            OUTPUT "Input harus 'y' atau 'n'!"
            jenisInput ← ""
        ENDIF
    UNTIL jenisInput tidak kosong
    
    IF jenisInput = "y" OR jenisInput = "Y" THEN
        // Berbasis waktu
        isBerbasisWaktu ← true
        REPEAT
            OUTPUT "Durasi (detik)     : "
            INPUT frekuensi
            IF frekuensi ≤ 0 THEN
                OUTPUT "Durasi harus lebih dari 0!"
            ENDIF
        UNTIL frekuensi > 0
        sets ← 0
    ELSE
        // Berbasis reps
        isBerbasisWaktu ← false
        REPEAT
            OUTPUT "Reps               : "
            INPUT frekuensi
            IF frekuensi ≤ 0 THEN
                OUTPUT "Reps harus lebih dari 0!"
            ENDIF
        UNTIL frekuensi > 0
        
        REPEAT
            OUTPUT "Sets               : "
            INPUT sets
            IF sets ≤ 0 THEN
                OUTPUT "Sets harus lebih dari 0!"
            ENDIF
        UNTIL sets > 0
    ENDIF
    
    OUTPUT "--------------------------------------------"
    
    newGerakan ← createGerakan(namaGerakan, isBerbasisWaktu, frekuensi, sets)
    insertGerakan(paket, newGerakan)
    OUTPUT "Gerakan ", namaGerakan, " berhasil ditambahkan ke paket ", namaPaket, "."
    
    WAIT FOR ENTER
END
```

---

## PROCEDURE hapusPaket(headPaket: adrPaket [by reference])
### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== HAPUS PAKET LATIHAN =========="
    
    IF headPaket = nullptr THEN
        OUTPUT "Belum ada paket latihan."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    CLEAR INPUT BUFFER
    OUTPUT "Nama Paket         : "
    INPUT nama (getline)
    OUTPUT "Kesulitan          : "
    INPUT kesulitan (getline)
    OUTPUT "----------------------------------------"
    
    deletePaket(headPaket, nama, kesulitan)
    
    WAIT FOR ENTER
END
```

---

## PROCEDURE hapusGerakan(headPaket: adrPaket)
### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== HAPUS GERAKAN DARI PAKET =========="
    
    IF headPaket = nullptr THEN
        OUTPUT "Belum ada paket latihan."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    CLEAR INPUT BUFFER
    OUTPUT "Nama Paket         : "
    INPUT namaPaket (getline)
    
    // Smart search
    count ← countPaketByName(headPaket, namaPaket)
    
    IF count = 0 THEN
        OUTPUT "Paket tidak ditemukan."
        WAIT FOR ENTER
        RETURN
    ELSE IF count = 1 THEN
        paket ← findPaketByName(headPaket, namaPaket)
    ELSE
        OUTPUT "Kesulitan          : "
        INPUT kesulitan (getline)
        paket ← findPaket(headPaket, namaPaket, kesulitan)
        IF paket = nullptr THEN
            OUTPUT "Paket tidak ditemukan."
            WAIT FOR ENTER
            RETURN
        ENDIF
    ENDIF
    
    OUTPUT "Nama Gerakan       : "
    INPUT namaGerakan (getline)
    OUTPUT "---------------------------------------------"
    
    deleteGerakan(paket, namaGerakan)
    
    WAIT FOR ENTER
END
```

---

## PROCEDURE updatePaket(headPaket: adrPaket)
### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== UPDATE PAKET LATIHAN =========="
    
    IF headPaket = nullptr THEN
        OUTPUT "Belum ada paket latihan."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    CLEAR INPUT BUFFER
    OUTPUT "Nama Paket Lama    : "
    INPUT nama (getline)
    
    // Input kesulitan lama dengan menu
    OUTPUT ""
    OUTPUT "Kesulitan Lama:"
    OUTPUT "1. Beginner"
    OUTPUT "2. Intermediate"
    OUTPUT "3. Advanced"
    OUTPUT "Pilihan (1-3)      : "
    INPUT pilihanKesulitanLama
    
    CASE pilihanKesulitanLama OF
        1: kesulitan ← "Beginner"
        2: kesulitan ← "Intermediate"
        3: kesulitan ← "Advanced"
        DEFAULT:
            kesulitan ← "Beginner"
    ENDCASE
    
    // Cari paket
    paket ← findPaket(headPaket, nama, kesulitan)
    IF paket = nullptr THEN
        OUTPUT "Paket tidak ditemukan."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    // Validasi: nama baru tidak boleh kosong
    REPEAT
        OUTPUT ""
        OUTPUT "Nama Paket Baru    : "
        INPUT namaBaru (getline)
        IF namaBaru kosong THEN
            OUTPUT "Nama paket tidak boleh kosong!"
        ENDIF
    UNTIL namaBaru tidak kosong
    
    // Input kesulitan baru dengan menu
    OUTPUT ""
    OUTPUT "Kesulitan Baru:"
    OUTPUT "1. Beginner"
    OUTPUT "2. Intermediate"
    OUTPUT "3. Advanced"
    OUTPUT "Pilihan (1-3)      : "
    INPUT pilihanKesulitanBaru
    
    CASE pilihanKesulitanBaru OF
        1: kesulitanBaru ← "Beginner"
        2: kesulitanBaru ← "Intermediate"
        3: kesulitanBaru ← "Advanced"
        DEFAULT:
            kesulitanBaru ← "Beginner"
    ENDCASE
    
    OUTPUT "------------------------------------------"
    
    // Update data paket
    paket.nama_paket ← namaBaru
    paket.kesulitan ← kesulitanBaru
    OUTPUT "Paket berhasil diupdate."
    
    WAIT FOR ENTER
END
```

---

## PROCEDURE updateGerakan(headPaket: adrPaket)
### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== UPDATE GERAKAN =========="
    
    IF headPaket = nullptr THEN
        OUTPUT "Belum ada paket latihan."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    CLEAR INPUT BUFFER
    OUTPUT "Nama Paket         : "
    INPUT namaPaket (getline)
    
    // Smart search
    count ← countPaketByName(headPaket, namaPaket)
    
    IF count = 0 THEN
        OUTPUT "Paket tidak ditemukan."
        WAIT FOR ENTER
        RETURN
    ELSE IF count = 1 THEN
        paket ← findPaketByName(headPaket, namaPaket)
    ELSE
        OUTPUT "Kesulitan          : "
        INPUT kesulitan (getline)
        paket ← findPaket(headPaket, namaPaket, kesulitan)
        IF paket = nullptr THEN
            OUTPUT "Paket tidak ditemukan."
            WAIT FOR ENTER
            RETURN
        ENDIF
    ENDIF
    
    // Validasi: nama gerakan lama tidak boleh kosong
    REPEAT
        OUTPUT "Nama Gerakan Lama  : "
        INPUT namaGerakanLama (getline)
        IF namaGerakanLama kosong THEN
            OUTPUT "Nama gerakan tidak boleh kosong!"
        ENDIF
    UNTIL namaGerakanLama tidak kosong
    
    // Cari gerakan
    temp ← paket.first
    WHILE temp ≠ nullptr AND temp.nama_gerakan ≠ namaGerakanLama DO
        temp ← temp.next
    ENDWHILE
    
    IF temp = nullptr THEN
        OUTPUT "Gerakan tidak ditemukan."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    // Validasi: nama gerakan baru tidak boleh kosong
    REPEAT
        OUTPUT "Nama Gerakan Baru  : "
        INPUT namaGerakanBaru (getline)
        IF namaGerakanBaru kosong THEN
            OUTPUT "Nama gerakan tidak boleh kosong!"
        ENDIF
    UNTIL namaGerakanBaru tidak kosong
    
    // Validasi: berbasis waktu (y/n)
    REPEAT
        OUTPUT "Berbasis waktu? (y/n): "
        INPUT jenisInput (getline)
        IF jenisInput kosong THEN
            OUTPUT "Input tidak boleh kosong!"
        ELSE IF jenisInput ≠ "y" AND jenisInput ≠ "Y" AND jenisInput ≠ "n" AND jenisInput ≠ "N" THEN
            OUTPUT "Input harus 'y' atau 'n'!"
            jenisInput ← ""
        ENDIF
    UNTIL jenisInput tidak kosong
    
    IF jenisInput = "y" OR jenisInput = "Y" THEN
        isBerbasisWaktu ← true
        REPEAT
            OUTPUT "Durasi (detik)     : "
            INPUT frekuensi
            IF frekuensi ≤ 0 THEN
                OUTPUT "Durasi harus lebih dari 0!"
            ENDIF
        UNTIL frekuensi > 0
        sets ← 0
    ELSE
        isBerbasisWaktu ← false
        REPEAT
            OUTPUT "Reps               : "
            INPUT frekuensi
            IF frekuensi ≤ 0 THEN
                OUTPUT "Reps harus lebih dari 0!"
            ENDIF
        UNTIL frekuensi > 0
        
        REPEAT
            OUTPUT "Sets               : "
            INPUT sets
            IF sets ≤ 0 THEN
                OUTPUT "Sets harus lebih dari 0!"
            ENDIF
        UNTIL sets > 0
    ENDIF
    
    OUTPUT "------------------------------------"
    
    // Update data gerakan
    temp.nama_gerakan ← namaGerakanBaru
    temp.isBerbasisWaktu ← isBerbasisWaktu
    temp.frekuensi ← frekuensi
    temp.sets ← sets
    OUTPUT "Gerakan berhasil diupdate."
    
    WAIT FOR ENTER
END
```

---

## PROCEDURE lihatSemuaPaket(headPaket: adrPaket)
### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== SEMUA PAKET LATIHAN =========="
    
    IF headPaket = nullptr THEN
        OUTPUT "Belum ada paket latihan."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    temp ← headPaket
    no ← 1
    
    OUTPUT ""
    OUTPUT "Daftar Paket:"
    WHILE temp ≠ nullptr DO
        OUTPUT no, ". ", temp.nama_paket, " - ", temp.kesulitan
        
        // Hitung jumlah gerakan
        countGerakan ← 0
        gerakan ← temp.first
        WHILE gerakan ≠ nullptr DO
            countGerakan ← countGerakan + 1
            gerakan ← gerakan.next
        ENDWHILE
        
        OUTPUT "   Jumlah gerakan: ", countGerakan
        no ← no + 1
        temp ← temp.next
    ENDWHILE
    
    WAIT FOR ENTER
END
```

---

## PROCEDURE detailPaket(headPaket: adrPaket)
### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== DETAIL PAKET LATIHAN =========="
    
    IF headPaket = nullptr THEN
        OUTPUT "Belum ada paket latihan."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    CLEAR INPUT BUFFER
    OUTPUT "Nama Paket         : "
    INPUT namaPaket (getline)
    
    // Smart search
    count ← countPaketByName(headPaket, namaPaket)
    
    IF count = 0 THEN
        OUTPUT "Paket tidak ditemukan."
        WAIT FOR ENTER
        RETURN
    ELSE IF count = 1 THEN
        paket ← findPaketByName(headPaket, namaPaket)
    ELSE
        OUTPUT "Kesulitan          : "
        INPUT kesulitan (getline)
        paket ← findPaket(headPaket, namaPaket, kesulitan)
        IF paket = nullptr THEN
            OUTPUT "Paket tidak ditemukan."
            WAIT FOR ENTER
            RETURN
        ENDIF
    ENDIF
    
    OUTPUT "----------------------------------------"
    OUTPUT ""
    OUTPUT "Informasi Paket:"
    OUTPUT "Nama Paket         : ", paket.nama_paket
    OUTPUT "Kesulitan          : ", paket.kesulitan
    OUTPUT ""
    
    IF paket.first = nullptr THEN
        OUTPUT "Belum ada gerakan dalam paket ini."
    ELSE
        OUTPUT "Daftar Gerakan:"
        gerakan ← paket.first
        no ← 1
        WHILE gerakan ≠ nullptr DO
            OUTPUT no, ". ", gerakan.nama_gerakan
            IF gerakan.isBerbasisWaktu THEN
                OUTPUT "   Durasi: ", gerakan.frekuensi, " detik"
            ELSE
                OUTPUT "   Reps: ", gerakan.frekuensi, " | Sets: ", gerakan.sets
            ENDIF
            no ← no + 1
            gerakan ← gerakan.next
        ENDWHILE
    ENDIF
    
    WAIT FOR ENTER
END
```

---

## PROCEDURE menuLatihan(headPaket: adrPaket [by reference])
### ALGORITMA
```
BEGIN
    REPEAT
        CLS
        OUTPUT "========== MENU LATIHAN =========="
        OUTPUT "1. Tambah paket latihan"
        OUTPUT "2. Tambah gerakan ke paket"
        OUTPUT "3. Lihat semua paket"
        OUTPUT "4. Lihat detail paket"
        OUTPUT "5. Update paket"
        OUTPUT "6. Update gerakan"
        OUTPUT "7. Hapus paket"
        OUTPUT "8. Hapus gerakan"
        OUTPUT "9. Statistik Paket"
        OUTPUT "10. Kembali"
        OUTPUT "-----------------------------------"
        OUTPUT "Pilihan: "
        INPUT pilihanMenu
        
        CASE pilihanMenu OF
            1: tambahPaket(headPaket)
            2: tambahGerakan(headPaket)
            3: lihatSemuaPaket(headPaket)
            4: detailPaket(headPaket)
            5: updatePaket(headPaket)
            6: updateGerakan(headPaket)
            7: hapusPaket(headPaket)
            8: hapusGerakan(headPaket)
            9: menuStatistikPaket(headPaket)
            DEFAULT: // Tidak melakukan apa-apa
        ENDCASE
        
    UNTIL pilihanMenu = 10
END
```

---

# BAGIAN F: FUNGSI PENGOLAHAN BST

## FUNCTION countTotalMember(root: adrMember) → integer
### ALGORITMA
```
BEGIN
    IF root = nullptr THEN
        RETURN 0
    ELSE
        RETURN 1 + countTotalMember(root.left) + countTotalMember(root.right)
    ENDIF
END
```

---

## FUNCTION findMemberMaxWeight(root: adrMember) → adrMember
### ALGORITMA
```
BEGIN
    IF root = nullptr THEN
        RETURN nullptr
    ENDIF
    
    maxNode ← root
    leftMax ← findMemberMaxWeight(root.left)
    rightMax ← findMemberMaxWeight(root.right)
    
    IF leftMax ≠ nullptr AND leftMax.info_member.target_berat > maxNode.info_member.target_berat THEN
        maxNode ← leftMax
    ENDIF
    
    IF rightMax ≠ nullptr AND rightMax.info_member.target_berat > maxNode.info_member.target_berat THEN
        maxNode ← rightMax
    ENDIF
    
    RETURN maxNode
END
```

---

## FUNCTION findMemberMinWeight(root: adrMember) → adrMember
### ALGORITMA
```
BEGIN
    IF root = nullptr THEN
        RETURN nullptr
    ENDIF
    
    minNode ← root
    leftMin ← findMemberMinWeight(root.left)
    rightMin ← findMemberMinWeight(root.right)
    
    IF leftMin ≠ nullptr AND leftMin.info_member.target_berat < minNode.info_member.target_berat THEN
        minNode ← leftMin
    ENDIF
    
    IF rightMin ≠ nullptr AND rightMin.info_member.target_berat < minNode.info_member.target_berat THEN
        minNode ← rightMin
    ENDIF
    
    RETURN minNode
END
```

---

## FUNCTION averageTargetWeight(root: adrMember, count: integer [by reference]) → float
### ALGORITMA
```
BEGIN
    IF root = nullptr THEN
        RETURN 0
    ENDIF
    
    count ← count + 1
    leftSum ← averageTargetWeight(root.left, count)
    rightSum ← averageTargetWeight(root.right, count)
    
    RETURN root.info_member.target_berat + leftSum + rightSum
END
```
**Catatan:** Count di-pass by reference untuk menghitung total node

---

# BAGIAN G: FUNGSI PENGOLAHAN MLL

## FUNCTION countTotalPaket(head: adrPaket) → integer
### ALGORITMA
```
BEGIN
    temp ← head
    count ← 0
    WHILE temp ≠ nullptr DO
        count ← count + 1
        temp ← temp.next
    ENDWHILE
    RETURN count
END
```

---

## FUNCTION countGerakanInPaket(paket: adrPaket) → integer
### ALGORITMA
```
BEGIN
    temp ← paket.first
    count ← 0
    WHILE temp ≠ nullptr DO
        count ← count + 1
        temp ← temp.next
    ENDWHILE
    RETURN count
END
```

---

## FUNCTION findPaketMostExercises(head: adrPaket) → adrPaket
### ALGORITMA
```
BEGIN
    IF head = nullptr THEN
        RETURN nullptr
    ENDIF
    
    maxPaket ← head
    maxCount ← countGerakanInPaket(head)
    temp ← head.next
    
    WHILE temp ≠ nullptr DO
        currentCount ← countGerakanInPaket(temp)
        IF currentCount > maxCount THEN
            maxCount ← currentCount
            maxPaket ← temp
        ENDIF
        temp ← temp.next
    ENDWHILE
    
    RETURN maxPaket
END
```

---

## FUNCTION findPaketLeastExercises(head: adrPaket) → adrPaket
### ALGORITMA
```
BEGIN
    IF head = nullptr THEN
        RETURN nullptr
    ENDIF
    
    minPaket ← head
    minCount ← countGerakanInPaket(head)
    temp ← head.next
    
    WHILE temp ≠ nullptr DO
        currentCount ← countGerakanInPaket(temp)
        IF currentCount < minCount THEN
            minCount ← currentCount
            minPaket ← temp
        ENDIF
        temp ← temp.next
    ENDWHILE
    
    RETURN minPaket
END
```

---

## PROCEDURE viewPaketByKesulitan(head: adrPaket, kesulitan: string)
### ALGORITMA
```
BEGIN
    temp ← head
    no ← 1
    found ← false
    
    OUTPUT ""
    OUTPUT "Paket dengan kesulitan ", kesulitan, ":"
    WHILE temp ≠ nullptr DO
        IF temp.kesulitan = kesulitan THEN
            OUTPUT no, ". ", temp.nama_paket
            found ← true
            no ← no + 1
        ENDIF
        temp ← temp.next
    ENDWHILE
    
    IF NOT found THEN
        OUTPUT "(Tidak ada paket dengan kesulitan ini)"
    ENDIF
END
```

---

# BAGIAN H: MENU STATISTIK

## PROCEDURE menuStatistikMember(root: adrMember)
### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== STATISTIK MEMBER =========="
    
    IF root = nullptr THEN
        OUTPUT "Belum ada member yang terdaftar."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    // Total member
    total ← countTotalMember(root)
    OUTPUT "Total Member           : ", total
    
    // Member dengan target tertinggi
    maxMember ← findMemberMaxWeight(root)
    OUTPUT "Target Berat Tertinggi : ", maxMember.info_member.nama_member, " (", maxMember.info_member.target_berat, " kg)"
    
    // Member dengan target terendah
    minMember ← findMemberMinWeight(root)
    OUTPUT "Target Berat Terendah  : ", minMember.info_member.nama_member, " (", minMember.info_member.target_berat, " kg)"
    
    // Rata-rata target berat
    count ← 0
    sum ← averageTargetWeight(root, count)
    avg ← sum / count
    OUTPUT "Rata-rata Target Berat : ", avg, " kg"
    
    WAIT FOR ENTER
END
```

---

## PROCEDURE menuStatistikPaket(headPaket: adrPaket)
### ALGORITMA
```
BEGIN
    CLS
    OUTPUT "========== STATISTIK PAKET =========="
    
    IF headPaket = nullptr THEN
        OUTPUT "Belum ada paket latihan."
        WAIT FOR ENTER
        RETURN
    ENDIF
    
    // Total paket
    total ← countTotalPaket(headPaket)
    OUTPUT "Total Paket            : ", total
    
    // Paket dengan gerakan terbanyak
    mostPaket ← findPaketMostExercises(headPaket)
    mostCount ← countGerakanInPaket(mostPaket)
    OUTPUT "Paket Terbanyak Gerakan: ", mostPaket.nama_paket, " (", mostCount, " gerakan)"
    
    // Paket dengan gerakan tersedikit
    leastPaket ← findPaketLeastExercises(headPaket)
    leastCount ← countGerakanInPaket(leastPaket)
    OUTPUT "Paket Tersedikit Gerakan: ", leastPaket.nama_paket, " (", leastCount, " gerakan)"
    
    // Paket berdasarkan kesulitan
    OUTPUT ""
    viewPaketByKesulitan(headPaket, "Beginner")
    viewPaketByKesulitan(headPaket, "Intermediate")
    viewPaketByKesulitan(headPaket, "Advanced")
    
    WAIT FOR ENTER
END
```

---

# PENJELASAN KESELURUHAN MODUL

## STRUKTUR DATA UTAMA

### 1. Binary Search Tree (BST) - Member
- **Node:** Berisi info member (nama, target berat, tinggi, progress bulanan)
- **Ordering:** Berdasarkan nama_member (alfabetis)
- **Operasi:**
  - Insert: Recursive BST insertion
  - Search: Binary search O(log n)
  - Delete: 3 kasus (leaf, 1 child, 2 children)
  - Traversal: Inorder, Preorder, Postorder, Level Order

### 2. Multi Linked List (MLL) - Paket Latihan
- **Parent List:** Linked list paket (nama_paket, kesulitan)
- **Child List:** Linked list gerakan dalam setiap paket
- **Operasi:**
  - Insert paket: Head insertion O(1)
  - Insert gerakan: Tail insertion O(n)
  - Search: Linear search O(n)
  - Delete: Cascade delete (hapus semua gerakan dulu)

## FITUR KHUSUS

### Smart Search
- Menghitung jumlah paket dengan nama sama
- Jika hanya 1, langsung gunakan tanpa tanya kesulitan
- Jika >1, minta user pilih kesulitan
- Meningkatkan UX dan efisiensi

### Input Validation
- Semua input string divalidasi tidak boleh kosong
- Numeric input divalidasi dalam range yang masuk akal
- Menu-driven input untuk mengurangi error

### Statistik & Analytics
- **Member:** Total, min/max target berat, rata-rata
- **Paket:** Total, paket terbanyak/tersedikit gerakan, filter by kesulitan
- Menggunakan recursive traversal untuk perhitungan

## KOMPLEKSITAS WAKTU

### BST Operations:
- Insert: O(log n) average, O(n) worst
- Search: O(log n) average, O(n) worst
- Delete: O(log n) average, O(n) worst
- Traversal: O(n)

### MLL Operations:
- Insert paket (head): O(1)
- Insert gerakan (tail): O(m) dimana m = jumlah gerakan
- Search paket: O(n) dimana n = jumlah paket
- Delete paket: O(n + m) untuk delete paket dan semua gerakannya

## VALIDASI INPUT

### Range Validations:
- Target berat: 1-300 kg
- Tinggi badan: 50-250 cm
- Bulan: 1-12
- Durasi/Reps/Sets: > 0

### Format Validations:
- String tidak boleh kosong
- Boolean input (y/n) harus exact match
- Menu selection menggunakan switch-case dengan default