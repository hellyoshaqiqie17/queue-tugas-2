# Tugas 2 Struktur Data (SIA103) - Queue (Antrian)

Repository ini berisi implementasi kode sumber C++ untuk penyelesaian **Tugas 2 Praktikum Struktur Data (SIA103)** dengan topik utama **Struktur Data Queue (Antrian)**, Program Studi S1 Teknik Robotika dan Kecerdasan Buatan (TRKB), Fakultas Teknologi Maju dan Multidisiplin (FTMM), Universitas Airlangga.

**Identitas Mahasiswa:**
- **Nama**  : Hellyos Ageng Haqiqie
- **NIM**   : 163251001
- **Kelas** : RK-A1 & RK-A2
- **Dosen Pengampu** :
  - Purbandini, S.Si., M.Kom. (PJMK)
  - Yutika Amelia Effendi, S.Kom., M.Kom.
  - Rodik Wahyu Indrawan, S.ST., M.Tr.T.
- **Topik** : *Queue (Antrian) - First-In First-Out (FIFO) & First-Come First-Served (FCFS)*

---

## Ringkasan Soal dan Implementasi

### 1. Soal 1: Program Kalkulator Sederhana Dua Bilangan (`soal1.cpp`)
Program aritmatika dasar yang menerima dua bilangan dan sebuah operator matematika:
- **Operasi yang Didukung**: Penjumlahan (`+`), pengurangan (`-`), perkalian (`*`), dan pembagian (`/`).
- **Validasi Galat**: Penanganan khusus pembagian dengan nol (*division by zero*) dan verifikasi masukan operator yang tidak valid.
- **Pemformatan Angka**: Menampilkan bilangan bulat tanpa pecahan desimal berlebih sesuai spesifikasi contoh tugas.

### 2. Soal 2: Sistem Antrian Teller Bank BRI Cik Ditiro (`soal2.cpp`)
Simulasi antrian perbankan multiserver berbasis disiplin FCFS (*First Come First Served*):
- **Struktur Data**: Antrian berbasis *Linked List Queue* dinamis.
- **Pelayan**: Memiliki 7 loket teller operasional (*Teller 1* s.d. *Teller 7*).
- **Dual Menu (Dua Menu Terpisah)**:
  - **Menu Nasabah**: Pengambilan tiket antrian baru, cek status/sisa nasabah di depan antrian, dan melihat daftar antrian saat ini.
  - **Menu Teller**: Pemanggilan nasabah terdepan FCFS oleh teller tertentu (1--7), penyelesaian pelayanan transaksi nasabah, dan pemantauan status 7 loket (SIBUK/IDLE).

### 3. Soal 3: Perhitungan Waktu Tunggu Pasien Berobat (`soal3.cpp`)
Program perhitungan estimasi waktu tunggu pasien klinik/rumah sakit menggunakan algoritma antrian:
- **Masukan**: Nomor antrian paling awal ($N_{awal}$), nomor antrian paling akhir ($N_{akhir}$), nomor antrian pengguna ($N_{anda}$), dan perkiraan durasi periksa per pasien ($t_{periksa}$ dalam menit).
- **Algoritma**: 
  $$\text{Pasien di Depan} = N_{anda} - N_{awal}$$
  $$\text{Total Waktu Tunggu} = \text{Pasien di Depan} \times t_{periksa}$$
- **Hasil Sesuai Soal**: Untuk antrian 1--10, nomor Anda 6, dan waktu periksa 4 menit, program menghasilkan output: `Anda Harus Menunggu 20 Menit Sampai Giliran Anda`.

### 4. Soal 4: Simulasi Tempat Parkir Mobil dengan Buffer Sementara (`soal4.cpp`)
Simulasi pengelolaan tempat parkir linier jalur tunggal berkapasitas terbatas:
- **Elemen Data**: Nomor plat mobil (mis. `L 1001 RK`, `B 2026 AI`, dll) beserta jenis kendaraan.
- **Tiga Proses Wajib**:
  1. **Mobil Masuk**: Memasuki antrian parkir dari posisi paling belakang (*enqueue*).
  2. **Mobil Paling Depan Keluar**: Keluar langsung dari posisi terdepan (*dequeue*).
  3. **Mobil Tengah Keluar**: Mobil di tengah keluar dengan memindahkan mobil-mobil di depannya ke penampungan sementara (*temporary queue buffer*), mengeluarkan mobil target, kemudian memasukkan kembali mobil-mobil dari penampungan sementara dan menyusun tempat parkir kembali ke urutan semula.

---

## Petunjuk Kompilasi dan Eksekusi

Kompilasi kode program dapat dilakukan menggunakan kompiler `g++` (standar C++17 atau C++20):

```bash
# Kompilasi seluruh program
g++ -std=c++17 -Wall -Wextra -O2 soal1.cpp -o soal1.exe
g++ -std=c++17 -Wall -Wextra -O2 soal2.cpp -o soal2.exe
g++ -std=c++17 -Wall -Wextra -O2 soal3.cpp -o soal3.exe
g++ -std=c++17 -Wall -Wextra -O2 soal4.cpp -o soal4.exe
```

Untuk menjalankan program:
```bash
.\soal1.exe
.\soal2.exe
.\soal3.exe
.\soal4.exe
```

Setiap program menyediakan mode demonstrasi otomatis (sesuai contoh soal modul) serta mode interaktif manual untuk pengujian bebas oleh pengguna.

---

## Struktur Direktori Repositori

```
queue-tugas-2/
├── images/
│   └── logo_unair.png
├── output/
│   ├── output_soal1.txt
│   ├── output_soal2.txt
│   ├── output_soal3.txt
│   └── output_soal4.txt
├── references.bib
├── run_tests.py
├── soal1.cpp
├── soal2.cpp
├── soal3.cpp
├── soal4.cpp
├── .gitignore
└── README.md
```
*(Catatan: Sesuai instruksi penugasan, berkas laporan LaTeX `main2.tex` tidak disertakan dalam repositori GitHub).*
