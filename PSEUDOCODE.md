# PSEUDOCODE - GYM & FITNESS TRACKER SYSTEM

## 📋 Daftar Isi

1. [Binary Search Tree (BST) - Member Management](#bst-member-management)
2. [Multi Linked List (MLL) - Paket Latihan](#mll-paket-latihan)
3. [Linked List - Relasi Member-Paket](#relasi-member-paket)
4. [Statistics & Analytics](#statistics-analytics)
5. [Helper Functions](#helper-functions)

---

## 🌳 BST - Member Management

### 1. Create Node
```
FUNCTION createNode(info)
    INPUT: info (infoMember)
    OUTPUT: adrMember (pointer to new node)
    
    ALGORITHM:
    1. Alokasi memory untuk newNode
    2. SET newNode.info_member = info
    3. SET newNode.left = NULL
    4. SET newNode.right = NULL
    5. RETURN newNode
END FUNCTION
```

### 2. Insert Node (BST)
```
PROCEDURE insertNode(root, newNode)
    INPUT: root (adrMember), newNode (adrMember)
    OUTPUT: root yang sudah di-update
    
    ALGORITHM:
    1. IF root == NULL THEN
          root = newNode
    2. ELSE IF newNode.nama_member < root.nama_member THEN
          insertNode(root.left, newNode)
    3. ELSE IF newNode.nama_member > root.nama_member THEN
          insertNode(root.right, newNode)
    4. ELSE
          PRINT "Member sudah ada"
    5. END IF
END PROCEDURE
```

### 3. Find Node (Search)
```
FUNCTION findNode(root, nama)
    INPUT: root (adrMember), nama (string)
    OUTPUT: adrMember (pointer to found node or NULL)
    
    ALGORITHM:
    1. IF root == NULL THEN
          RETURN NULL
    2. IF nama == root.nama_member THEN
          RETURN root
    3. ELSE IF nama < root.nama_member THEN
          RETURN findNode(root.left, nama)
    4. ELSE
          RETURN findNode(root.right, nama)
    5. END IF
END FUNCTION
```

### 4. Find Minimum Node
```
FUNCTION findMin(root)
    INPUT: root (adrMember)
    OUTPUT: adrMember (node dengan nilai minimum)
    
    ALGORITHM:
    1. WHILE root.left != NULL DO
          root = root.left
    2. END WHILE
    3. RETURN root
END FUNCTION
```

### 5. Delete Node (BST)
```
FUNCTION deleteNode(root, nama)
    INPUT: root (adrMember), nama (string)
    OUTPUT: root yang sudah di-update
    
    ALGORITHM:
    1. IF root == NULL THEN
          RETURN NULL
    2. END IF
    
    3. IF nama < root.nama_member THEN
          root.left = deleteNode(root.left, nama)
    4. ELSE IF nama > root.nama_member THEN
          root.right = deleteNode(root.right, nama)
    5. ELSE
          // Node ditemukan
          a. IF root.left == NULL THEN
                temp = root.right
                DELETE root
                RETURN temp
          b. ELSE IF root.right == NULL THEN
                temp = root.left
                DELETE root
                RETURN temp
          c. ELSE
                // Node memiliki 2 children
                i. minNode = findMin(root.right)
                ii. root.info_member = minNode.info_member
                iii. root.right = deleteNode(root.right, minNode.nama_member)
          d. END IF
    6. END IF
    
    7. RETURN root
END FUNCTION
```

### 6. Inorder Traversal (Left → Root → Right)
```
PROCEDURE inorder(root)
    INPUT: root (adrMember)
    OUTPUT: Print semua node secara inorder
    
    ALGORITHM:
    1. IF root != NULL THEN
          a. inorder(root.left)
          b. PRINT root.info_member
          c. inorder(root.right)
    2. END IF
END PROCEDURE
```

### 7. Preorder Traversal (Root → Left → Right)
```
PROCEDURE preorder(root)
    INPUT: root (adrMember)
    OUTPUT: Print semua node secara preorder
    
    ALGORITHM:
    1. IF root != NULL THEN
          a. PRINT root.info_member
          b. preorder(root.left)
          c. preorder(root.right)
    2. END IF
END PROCEDURE
```

### 8. Postorder Traversal (Left → Right → Root)
```
PROCEDURE postorder(root)
    INPUT: root (adrMember)
    OUTPUT: Print semua node secara postorder
    
    ALGORITHM:
    1. IF root != NULL THEN
          a. postorder(root.left)
          b. postorder(root.right)
          c. PRINT root.info_member
    2. END IF
END PROCEDURE
```

### 9. Level Order Traversal (BFS)
```
PROCEDURE levelOrder(root)
    INPUT: root (adrMember)
    OUTPUT: Print semua node secara level order
    
    ALGORITHM:
    1. IF root == NULL THEN
          RETURN
    2. END IF
    
    3. DECLARE queue[100]
    4. front = 0, rear = 0
    
    5. queue[rear++] = root
    
    6. WHILE front < rear DO
          a. current = queue[front++]
          b. PRINT current.info_member
          
          c. IF current.left != NULL THEN
                queue[rear++] = current.left
          d. END IF
          
          e. IF current.right != NULL THEN
                queue[rear++] = current.right
          f. END IF
    7. END WHILE
END PROCEDURE
```

---

## 🔗 MLL - Paket Latihan

### 1. Create Paket
```
FUNCTION createPaket(nama, kesulitan)
    INPUT: nama (string), kesulitan (string)
    OUTPUT: adrPaket (pointer to new paket)
    
    ALGORITHM:
    1. Alokasi memory untuk newPaket
    2. SET newPaket.nama_paket = nama
    3. SET newPaket.kesulitan = kesulitan
    4. SET newPaket.first = NULL   // Pointer ke child list
    5. SET newPaket.next = NULL    // Pointer ke paket berikutnya
    6. RETURN newPaket
END FUNCTION
```

### 2. Insert Paket (Parent List)
```
PROCEDURE insertPaket(head, newPaket)
    INPUT: head (adrPaket), newPaket (adrPaket)
    OUTPUT: head yang sudah di-update
    
    ALGORITHM (Head Insertion):
    1. IF head == NULL THEN
          head = newPaket
    2. ELSE
          newPaket.next = head
          head = newPaket
    3. END IF
END PROCEDURE
```

### 3. Create Gerakan (Child)
```
FUNCTION createGerakan(nama, isBerbasisWaktu, frekuensi, sets)
    INPUT: nama (string), isBerbasisWaktu (bool), 
           frekuensi (int), sets (int)
    OUTPUT: adrGerakan (pointer to new gerakan)
    
    ALGORITHM:
    1. Alokasi memory untuk newGerakan
    2. SET newGerakan.nama_gerakan = nama
    3. SET newGerakan.isBerbasisWaktu = isBerbasisWaktu
    4. SET newGerakan.frekuensi = frekuensi
    5. SET newGerakan.sets = sets
    6. SET newGerakan.next = NULL
    7. RETURN newGerakan
END FUNCTION
```

### 4. Insert Gerakan (Child List)
```
PROCEDURE insertGerakan(paket, newGerakan)
    INPUT: paket (adrPaket), newGerakan (adrGerakan)
    OUTPUT: paket dengan gerakan yang sudah ditambahkan
    
    ALGORITHM (Tail Insertion):
    1. IF paket.first == NULL THEN
          paket.first = newGerakan
    2. ELSE
          current = paket.first
          WHILE current.next != NULL DO
             current = current.next
          END WHILE
          current.next = newGerakan
    3. END IF
END PROCEDURE
```

### 5. Find Paket (dengan nama dan kesulitan)
```
FUNCTION findPaket(head, nama, kesulitan)
    INPUT: head (adrPaket), nama (string), kesulitan (string)
    OUTPUT: adrPaket (pointer to found paket or NULL)
    
    ALGORITHM:
    1. temp = head
    2. WHILE temp != NULL DO
          IF temp.nama_paket == nama AND temp.kesulitan == kesulitan THEN
             RETURN temp
          END IF
          temp = temp.next
    3. END WHILE
    4. RETURN NULL
END FUNCTION
```

### 6. Count Paket By Name
```
FUNCTION countPaketByName(head, nama)
    INPUT: head (adrPaket), nama (string)
    OUTPUT: count (integer)
    
    ALGORITHM:
    1. count = 0
    2. temp = head
    3. WHILE temp != NULL DO
          IF temp.nama_paket == nama THEN
             count++
          END IF
          temp = temp.next
    4. END WHILE
    5. RETURN count
END FUNCTION
```

### 7. Find Paket By Name Only
```
FUNCTION findPaketByName(head, nama)
    INPUT: head (adrPaket), nama (string)
    OUTPUT: adrPaket (pointer to first paket with matching name)
    
    ALGORITHM:
    1. temp = head
    2. WHILE temp != NULL DO
          IF temp.nama_paket == nama THEN
             RETURN temp
          END IF
          temp = temp.next
    3. END WHILE
    4. RETURN NULL
END FUNCTION
```

### 8. Is Gerakan Exists
```
FUNCTION isGerakanExists(paket, namaGerakan)
    INPUT: paket (adrPaket), namaGerakan (string)
    OUTPUT: boolean (true/false)
    
    ALGORITHM:
    1. temp = paket.first
    2. WHILE temp != NULL DO
          IF temp.nama_gerakan == namaGerakan THEN
             RETURN true
          END IF
          temp = temp.next
    3. END WHILE
    4. RETURN false
END FUNCTION
```

### 9. Delete Paket (Cascade Delete)
```
PROCEDURE deletePaket(head, nama, kesulitan)
    INPUT: head (adrPaket), nama (string), kesulitan (string)
    OUTPUT: head yang sudah di-update
    
    ALGORITHM:
    1. temp = head
    2. prev = NULL
    
    3. // Cari paket yang akan dihapus
    4. WHILE temp != NULL AND (temp.nama_paket != nama OR temp.kesulitan != kesulitan) DO
          prev = temp
          temp = temp.next
    5. END WHILE
    
    6. IF temp == NULL THEN
          PRINT "Paket tidak ditemukan"
          RETURN
    7. END IF
    
    8. // Hapus semua gerakan di paket (cascade)
    9. gerakan = temp.first
    10. WHILE gerakan != NULL DO
          toDelete = gerakan
          gerakan = gerakan.next
          DELETE toDelete
    11. END WHILE
    
    12. // Hapus paket dari list
    13. IF prev == NULL THEN
          head = temp.next
    14. ELSE
          prev.next = temp.next
    15. END IF
    
    16. DELETE temp
    17. PRINT "Paket berhasil dihapus"
END PROCEDURE
```

### 10. Delete Gerakan
```
PROCEDURE deleteGerakan(paket, namaGerakan)
    INPUT: paket (adrPaket), namaGerakan (string)
    OUTPUT: paket dengan gerakan yang sudah dihapus
    
    ALGORITHM:
    1. IF paket.first == NULL THEN
          PRINT "Paket tidak memiliki gerakan"
          RETURN
    2. END IF
    
    3. temp = paket.first
    4. prev = NULL
    
    5. // Cari gerakan yang akan dihapus
    6. WHILE temp != NULL AND temp.nama_gerakan != namaGerakan DO
          prev = temp
          temp = temp.next
    7. END WHILE
    
    8. IF temp == NULL THEN
          PRINT "Gerakan tidak ditemukan"
          RETURN
    9. END IF
    
    10. // Hapus gerakan dari list
    11. IF prev == NULL THEN
          paket.first = temp.next
    12. ELSE
          prev.next = temp.next
    13. END IF
    
    14. DELETE temp
    15. PRINT "Gerakan berhasil dihapus"
END PROCEDURE
```

---

## 📊 Relasi Member-Paket

### 1. Create Relasi
```
FUNCTION createRelasi(namaMember, namaPaket, kesulitanPaket)
    INPUT: namaMember (string), namaPaket (string), 
           kesulitanPaket (string)
    OUTPUT: adrRelasi (pointer to new relasi)
    
    ALGORITHM:
    1. Alokasi memory untuk newRelasi
    2. SET newRelasi.nama_member = namaMember
    3. SET newRelasi.nama_paket = namaPaket
    4. SET newRelasi.kesulitan_paket = kesulitanPaket
    5. SET newRelasi.next = NULL
    6. RETURN newRelasi
END FUNCTION
```

### 2. Insert Relasi
```
PROCEDURE insertRelasi(head, newRelasi)
    INPUT: head (adrRelasi), newRelasi (adrRelasi)
    OUTPUT: head yang sudah di-update
    
    ALGORITHM (Head Insertion):
    1. IF head == NULL THEN
          head = newRelasi
    2. ELSE
          newRelasi.next = head
          head = newRelasi
    3. END IF
END PROCEDURE
```

### 3. Is Relasi Exists
```
FUNCTION isRelasiExists(head, namaMember, namaPaket, kesulitan)
    INPUT: head (adrRelasi), namaMember (string), 
           namaPaket (string), kesulitan (string)
    OUTPUT: boolean (true/false)
    
    ALGORITHM:
    1. temp = head
    2. WHILE temp != NULL DO
          IF temp.nama_member == namaMember AND 
             temp.nama_paket == namaPaket AND 
             temp.kesulitan_paket == kesulitan THEN
             RETURN true
          END IF
          temp = temp.next
    3. END WHILE
    4. RETURN false
END FUNCTION
```

### 4. Delete Relasi
```
PROCEDURE deleteRelasi(head, namaMember, namaPaket, kesulitan)
    INPUT: head (adrRelasi), namaMember (string), 
           namaPaket (string), kesulitan (string)
    OUTPUT: head yang sudah di-update
    
    ALGORITHM:
    1. temp = head
    2. prev = NULL
    
    3. // Cari relasi yang akan dihapus
    4. WHILE temp != NULL AND 
            (temp.nama_member != namaMember OR 
             temp.nama_paket != namaPaket OR 
             temp.kesulitan_paket != kesulitan) DO
          prev = temp
          temp = temp.next
    5. END WHILE
    
    6. IF temp == NULL THEN
          PRINT "Relasi tidak ditemukan"
          RETURN
    7. END IF
    
    8. // Hapus relasi dari list
    9. IF prev == NULL THEN
          head = temp.next
    10. ELSE
          prev.next = temp.next
    11. END IF
    
    12. DELETE temp
    13. PRINT "Relasi berhasil dihapus"
END PROCEDURE
```

### 5. Assign Paket to Member (with Smart Search)
```
PROCEDURE assignPaketToMember(headRelasi, rootMember, headPaket)
    INPUT: headRelasi (adrRelasi), rootMember (adrMember), 
           headPaket (adrPaket)
    OUTPUT: headRelasi yang sudah di-update
    
    ALGORITHM:
    1. INPUT namaMember
    2. member = findNode(rootMember, namaMember)
    3. IF member == NULL THEN
          PRINT "Member tidak ditemukan"
          RETURN
    4. END IF
    
    5. INPUT namaPaket
    6. count = countPaketByName(headPaket, namaPaket)
    
    7. IF count == 0 THEN
          PRINT "Paket tidak ditemukan"
          RETURN
    8. ELSE IF count == 1 THEN
          // Hanya ada 1 paket, langsung gunakan
          paket = findPaketByName(headPaket, namaPaket)
          kesulitan = paket.kesulitan
    9. ELSE
          // Ada > 1 paket dengan nama sama, tanya kesulitan
          INPUT kesulitan
          paket = findPaket(headPaket, namaPaket, kesulitan)
          IF paket == NULL THEN
             PRINT "Paket tidak ditemukan"
             RETURN
          END IF
    10. END IF
    
    11. // Cek apakah relasi sudah ada
    12. IF isRelasiExists(headRelasi, namaMember, namaPaket, kesulitan) THEN
          PRINT "Member sudah memiliki paket ini"
          RETURN
    13. END IF
    
    14. // Buat dan insert relasi baru
    15. newRelasi = createRelasi(namaMember, namaPaket, kesulitan)
    16. insertRelasi(headRelasi, newRelasi)
    17. PRINT "Paket berhasil di-assign"
END PROCEDURE
```

---

## 📈 Statistics & Analytics

### 1. Count Total Member
```
FUNCTION countTotalMember(root)
    INPUT: root (adrMember)
    OUTPUT: count (integer)
    
    ALGORITHM (Recursive):
    1. IF root == NULL THEN
          RETURN 0
    2. END IF
    
    3. RETURN 1 + countTotalMember(root.left) + countTotalMember(root.right)
END FUNCTION
```

### 2. Find Member Max Weight
```
FUNCTION findMemberMaxWeight(root)
    INPUT: root (adrMember)
    OUTPUT: adrMember (member dengan target berat tertinggi)
    
    ALGORITHM (Recursive):
    1. IF root == NULL THEN
          RETURN NULL
    2. END IF
    
    3. maxNode = root
    4. leftMax = findMemberMaxWeight(root.left)
    5. rightMax = findMemberMaxWeight(root.right)
    
    6. IF leftMax != NULL AND leftMax.target_berat > maxNode.target_berat THEN
          maxNode = leftMax
    7. END IF
    
    8. IF rightMax != NULL AND rightMax.target_berat > maxNode.target_berat THEN
          maxNode = rightMax
    9. END IF
    
    10. RETURN maxNode
END FUNCTION
```

### 3. Find Member Min Weight
```
FUNCTION findMemberMinWeight(root)
    INPUT: root (adrMember)
    OUTPUT: adrMember (member dengan target berat terendah)
    
    ALGORITHM (Recursive):
    1. IF root == NULL THEN
          RETURN NULL
    2. END IF
    
    3. minNode = root
    4. leftMin = findMemberMinWeight(root.left)
    5. rightMin = findMemberMinWeight(root.right)
    
    6. IF leftMin != NULL AND leftMin.target_berat < minNode.target_berat THEN
          minNode = leftMin
    7. END IF
    
    8. IF rightMin != NULL AND rightMin.target_berat < minNode.target_berat THEN
          minNode = rightMin
    9. END IF
    
    10. RETURN minNode
END FUNCTION
```

### 4. Average Target Weight
```
FUNCTION averageTargetWeight(root, count)
    INPUT: root (adrMember), count (int by reference)
    OUTPUT: average (float)
    
    ALGORITHM (Recursive):
    1. IF root == NULL THEN
          count = 0
          RETURN 0.0
    2. END IF
    
    3. leftCount = 0, rightCount = 0
    4. leftSum = averageTargetWeight(root.left, leftCount) * leftCount
    5. rightSum = averageTargetWeight(root.right, rightCount) * rightCount
    
    6. count = 1 + leftCount + rightCount
    7. totalSum = root.target_berat + leftSum + rightSum
    
    8. RETURN totalSum / count
END FUNCTION
```

### 5. Count Total Paket
```
FUNCTION countTotalPaket(head)
    INPUT: head (adrPaket)
    OUTPUT: count (integer)
    
    ALGORITHM:
    1. count = 0
    2. temp = head
    3. WHILE temp != NULL DO
          count++
          temp = temp.next
    4. END WHILE
    5. RETURN count
END FUNCTION
```

### 6. Count Gerakan in Paket
```
FUNCTION countGerakanInPaket(paket)
    INPUT: paket (adrPaket)
    OUTPUT: count (integer)
    
    ALGORITHM:
    1. count = 0
    2. temp = paket.first
    3. WHILE temp != NULL DO
          count++
          temp = temp.next
    4. END WHILE
    5. RETURN count
END FUNCTION
```

### 7. Find Paket Most Exercises
```
FUNCTION findPaketMostExercises(head)
    INPUT: head (adrPaket)
    OUTPUT: adrPaket (paket dengan gerakan terbanyak)
    
    ALGORITHM:
    1. IF head == NULL THEN
          RETURN NULL
    2. END IF
    
    3. maxPaket = head
    4. maxCount = countGerakanInPaket(head)
    
    5. temp = head.next
    6. WHILE temp != NULL DO
          currentCount = countGerakanInPaket(temp)
          IF currentCount > maxCount THEN
             maxCount = currentCount
             maxPaket = temp
          END IF
          temp = temp.next
    7. END WHILE
    
    8. RETURN maxPaket
END FUNCTION
```

### 8. Find Paket Least Exercises
```
FUNCTION findPaketLeastExercises(head)
    INPUT: head (adrPaket)
    OUTPUT: adrPaket (paket dengan gerakan tersedikit)
    
    ALGORITHM:
    1. IF head == NULL THEN
          RETURN NULL
    2. END IF
    
    3. minPaket = head
    4. minCount = countGerakanInPaket(head)
    
    5. temp = head.next
    6. WHILE temp != NULL DO
          currentCount = countGerakanInPaket(temp)
          IF currentCount < minCount THEN
             minCount = currentCount
             minPaket = temp
          END IF
          temp = temp.next
    7. END WHILE
    
    8. RETURN minPaket
END FUNCTION
```

### 9. View Paket By Kesulitan
```
PROCEDURE viewPaketByKesulitan(head, kesulitan)
    INPUT: head (adrPaket), kesulitan (string)
    OUTPUT: Print paket dengan kesulitan tertentu
    
    ALGORITHM:
    1. count = 0
    2. temp = head
    
    3. PRINT "Paket dengan kesulitan:", kesulitan
    
    4. WHILE temp != NULL DO
          IF temp.kesulitan == kesulitan THEN
             count++
             PRINT count, ".", temp.nama_paket, 
                   "(", countGerakanInPaket(temp), "gerakan)"
          END IF
          temp = temp.next
    5. END WHILE
    
    6. IF count == 0 THEN
          PRINT "Tidak ada paket dengan kesulitan ini"
    7. ELSE
          PRINT "Total:", count, "paket"
    8. END IF
END PROCEDURE
```

---

## 🛠️ Helper Functions

### 1. Update Progress Member
```
PROCEDURE updateProgMember(root)
    INPUT: root (adrMember)
    OUTPUT: Update progress member
    
    ALGORITHM:
    1. INPUT namaMember
    2. member = findNode(root, namaMember)
    
    3. IF member == NULL THEN
          PRINT "Member tidak ditemukan"
          RETURN
    4. END IF
    
    5. REPEAT
          INPUT bulan (1-12)
          IF bulan < 1 OR bulan > 12 THEN
             PRINT "Bulan harus 1-12"
          END IF
    6. UNTIL bulan >= 1 AND bulan <= 12
    
    7. REPEAT
          INPUT beratBaru
          IF beratBaru < 1 OR beratBaru > 300 THEN
             PRINT "Berat harus 1-300 kg"
          END IF
    8. UNTIL beratBaru >= 1 AND beratBaru <= 300
    
    9. member.progress_berat[bulan-1] = beratBaru
    10. PRINT "Progress berhasil diupdate"
END PROCEDURE
```

### 2. Tambah Member (dengan Validasi)
```
PROCEDURE tambahMember(root)
    INPUT: root (adrMember)
    OUTPUT: root yang sudah di-update
    
    ALGORITHM:
    1. REPEAT
          INPUT nama
          IF nama.empty() THEN
             PRINT "Nama tidak boleh kosong"
          END IF
    2. UNTIL NOT nama.empty()
    
    3. REPEAT
          INPUT targetBerat
          IF targetBerat < 1 OR targetBerat > 300 THEN
             PRINT "Target berat harus 1-300 kg"
          END IF
    4. UNTIL targetBerat >= 1 AND targetBerat <= 300
    
    5. REPEAT
          INPUT tinggiBadan
          IF tinggiBadan < 50 OR tinggiBadan > 250 THEN
             PRINT "Tinggi badan harus 50-250 cm"
          END IF
    6. UNTIL tinggiBadan >= 50 AND tinggiBadan <= 250
    
    7. // Inisialisasi progress berat dengan 0
    8. FOR i = 0 TO 11 DO
          progressBerat[i] = 0
    9. END FOR
    
    10. info.nama_member = nama
    11. info.target_berat = targetBerat
    12. info.tinggi_badan = tinggiBadan
    13. info.progress_berat = progressBerat
    
    14. newNode = createNode(info)
    15. insertNode(root, newNode)
    16. PRINT "Member berhasil ditambahkan"
END PROCEDURE
```

### 3. Tambah Paket (dengan Menu Kesulitan)
```
PROCEDURE tambahPaket(headPaket)
    INPUT: headPaket (adrPaket)
    OUTPUT: headPaket yang sudah di-update
    
    ALGORITHM:
    1. REPEAT
          INPUT nama
          IF nama.empty() THEN
             PRINT "Nama paket tidak boleh kosong"
          END IF
    2. UNTIL NOT nama.empty()
    
    3. PRINT "Pilih Kesulitan:"
    4. PRINT "1. Beginner"
    5. PRINT "2. Intermediate"
    6. PRINT "3. Advanced"
    7. INPUT pilihanKesulitan
    
    8. SWITCH pilihanKesulitan
          CASE 1: kesulitan = "Beginner"; BREAK
          CASE 2: kesulitan = "Intermediate"; BREAK
          CASE 3: kesulitan = "Advanced"; BREAK
          DEFAULT: kesulitan = "Beginner"
                   PRINT "Pilihan tidak valid, default ke Beginner"
    9. END SWITCH
    
    10. // Cek apakah paket sudah ada
    11. found = findPaket(headPaket, nama, kesulitan)
    12. IF found != NULL THEN
          PRINT "Paket sudah ada"
          RETURN
    13. END IF
    
    14. newPaket = createPaket(nama, kesulitan)
    15. insertPaket(headPaket, newPaket)
    16. PRINT "Paket berhasil ditambahkan"
END PROCEDURE
```

### 4. Tambah Gerakan (dengan Validasi)
```
PROCEDURE tambahGerakan(headPaket)
    INPUT: headPaket (adrPaket)
    OUTPUT: Paket dengan gerakan baru
    
    ALGORITHM:
    1. IF headPaket == NULL THEN
          PRINT "Belum ada paket latihan"
          RETURN
    2. END IF
    
    3. INPUT namaPaket
    4. count = countPaketByName(headPaket, namaPaket)
    
    5. IF count == 0 THEN
          PRINT "Paket tidak ditemukan"
          RETURN
    6. ELSE IF count == 1 THEN
          paket = findPaketByName(headPaket, namaPaket)
    7. ELSE
          INPUT kesulitan
          paket = findPaket(headPaket, namaPaket, kesulitan)
          IF paket == NULL THEN
             PRINT "Paket tidak ditemukan"
             RETURN
          END IF
    8. END IF
    
    9. REPEAT
          INPUT namaGerakan
          IF namaGerakan.empty() THEN
             PRINT "Nama gerakan tidak boleh kosong"
          END IF
    10. UNTIL NOT namaGerakan.empty()
    
    11. // Cek duplicate
    12. IF isGerakanExists(paket, namaGerakan) THEN
          PRINT "Gerakan sudah ada dalam paket"
          RETURN
    13. END IF
    
    14. REPEAT
          INPUT jenisInput (y/n)
          IF jenisInput != "y" AND jenisInput != "Y" AND 
             jenisInput != "n" AND jenisInput != "N" THEN
             PRINT "Input harus 'y' atau 'n'"
          END IF
    15. UNTIL jenisInput == "y" OR jenisInput == "Y" OR 
              jenisInput == "n" OR jenisInput == "N"
    
    16. IF jenisInput == "y" OR jenisInput == "Y" THEN
          isBerbasisWaktu = true
          REPEAT
             INPUT durasi
             IF durasi <= 0 THEN
                PRINT "Durasi harus > 0"
             END IF
          UNTIL durasi > 0
          frekuensi = durasi
          sets = 0
    17. ELSE
          isBerbasisWaktu = false
          REPEAT
             INPUT reps
             IF reps <= 0 THEN
                PRINT "Reps harus > 0"
             END IF
          UNTIL reps > 0
          
          REPEAT
             INPUT sets
             IF sets <= 0 THEN
                PRINT "Sets harus > 0"
             END IF
          UNTIL sets > 0
          frekuensi = reps
    18. END IF
    
    19. newGerakan = createGerakan(namaGerakan, isBerbasisWaktu, frekuensi, sets)
    20. insertGerakan(paket, newGerakan)
    21. PRINT "Gerakan berhasil ditambahkan"
END PROCEDURE
```

---

## 🎯 Main Program Flow

```
PROGRAM GymFitnessTracker
    ALGORITHM:
    1. INITIALIZE:
       - root (BST Member) = NULL
       - headPaket (MLL Paket) = NULL
       - headRelasi (Linked List Relasi) = NULL
    
    2. REPEAT
          DISPLAY Main Menu:
          - 1. Info Member
          - 2. Info Latihan
          - 3. Relasi Member-Latihan
          - 4. Keluar
          
          INPUT pilihanMenu
          
          SWITCH pilihanMenu
             CASE 1:
                menuMember(root)
                BREAK
             CASE 2:
                menuLatihan(headPaket)
                BREAK
             CASE 3:
                menuRelasi(headRelasi, root, headPaket)
                BREAK
             CASE 4:
                EXIT
          END SWITCH
    3. UNTIL pilihanMenu == 4
    
    4. END PROGRAM
END PROGRAM
```

---

## 📝 Catatan Kompleksitas

| Operasi | BST | MLL | Linked List |
|---------|-----|-----|-------------|
| Insert | O(log n) avg, O(n) worst | O(1) head, O(n) tail | O(1) head |
| Search | O(log n) avg, O(n) worst | O(n) | O(n) |
| Delete | O(log n) avg, O(n) worst | O(n) | O(n) |
| Traversal | O(n) | O(n) | O(n) |
| Count | O(n) | O(n) | O(n) |
| Find Min/Max | O(n) | O(n) | O(n) |

---

**Catatan:**
- Semua pseudocode di atas menggunakan notasi standar algoritma
- Input validation diterapkan pada setiap fungsi yang memerlukan input user
- Cascade delete diimplementasikan pada delete paket (menghapus semua gerakan)
- Smart search digunakan untuk optimasi user experience