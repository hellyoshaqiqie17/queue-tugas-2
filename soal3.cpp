/**
 * ============================================================================
 * Program     : Perhitungan Estimasi Waktu Tunggu Pasien (Soal 3)
 * Mata Kuliah : SIA103 Struktur Data
 * Topik       : Tugas 2 - Queue (Antrian) Simulasi Klinik / Rumah Sakit
 * Nama        : Hellyos Ageng Haqiqie
 * NIM         : 163251001
 * Prodi       : Teknik Robotika dan Kecerdasan Buatan (TRKB)
 * Fakultas    : Fakultas Teknologi Maju dan Multidisiplin (FTMM)
 * Universitas : Universitas Airlangga
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Struktur Node untuk Linked List Queue Pasien
struct NodePasien {
    int noAntrian;
    NodePasien* next;
    NodePasien(int no) : noAntrian(no), next(nullptr) {}
};

// Kelas Queue Pasien
class QueuePasien {
private:
    NodePasien* front;
    NodePasien* rear;
    int count;

public:
    QueuePasien() : front(nullptr), rear(nullptr), count(0) {}

    ~QueuePasien() {
        clear();
    }

    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    int size() const {
        return count;
    }

    // Enqueue pasien ke antrian
    void enqueue(int no) {
        NodePasien* baru = new NodePasien(no);
        if (isEmpty()) {
            front = rear = baru;
        } else {
            rear->next = baru;
            rear = baru;
        }
        count++;
    }

    // Dequeue pasien saat dipanggil dokter
    bool dequeue(int& noKeluar) {
        if (isEmpty()) return false;
        NodePasien* temp = front;
        noKeluar = temp->noAntrian;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
        count--;
        return true;
    }

    void dequeue() {
        if (!isEmpty()) {
            NodePasien* temp = front;
            front = front->next;
            if (front == nullptr) rear = nullptr;
            delete temp;
            count--;
        }
    }

    int getFront() const {
        if (isEmpty()) return -1;
        return front->noAntrian;
    }

    // Menampilkan seluruh antrian saat ini
    void cetakAntrian() const {
        NodePasien* curr = front;
        while (curr != nullptr) {
            cout << curr->noAntrian << (curr->next != nullptr ? " " : "");
            curr = curr->next;
        }
        cout << "\n";
    }

    // Menghitung jumlah pasien di depan nomor tertentu
    int hitungPasienDiDepan(int noPasien) const {
        NodePasien* curr = front;
        int hitung = 0;
        bool ketemu = false;

        while (curr != nullptr) {
            if (curr->noAntrian == noPasien) {
                ketemu = true;
                break;
            }
            hitung++;
            curr = curr->next;
        }
        return ketemu ? hitung : -1;
    }
};

// Prosedur demonstrasi otomatis sesuai persis dengan spesifikasi modul Tugas 2
void jalankanDemoSesuaiSoal() {
    cout << "\n============================================================\n";
    cout << "     DEMO ESTIMASI WAKTU TUNGGU PASIEN (SESUAI SOAL PDF)   \n";
    cout << "============================================================\n";

    int noAwal = 1;
    int noAkhir = 10;
    int noAnda = 6;
    int waktuPeriksaPerPasien = 4; // dalam menit

    cout << "No Antrian Paling Awal(mis.1) : " << noAwal << "\n";
    cout << "No Antrian Paling Akhir(mis.10) : " << noAkhir << "\n";

    // Membangun Queue antrian
    QueuePasien q;
    for (int i = noAwal; i <= noAkhir; ++i) {
        q.enqueue(i);
    }

    cout << "No Antrian Saat Ini :\n";
    q.cetakAntrian();

    cout << "No Antrian Anda(" << noAwal << "-" << noAkhir << ") : " << noAnda << "\n";
    cout << "Perkiraan Waktu Periksa Per Pasien(menit) : " << waktuPeriksaPerPasien << "\n\n";

    // Algoritma Queue untuk menghitung waktu tunggu
    int jumlahDiDepan = q.hitungPasienDiDepan(noAnda);
    if (jumlahDiDepan != -1) {
        int totalWaktuTunggu = jumlahDiDepan * waktuPeriksaPerPasien;
        cout << "Anda Harus Menunggu " << totalWaktuTunggu << " Menit Sampai Giliran Anda\n";
        cout << "------------------------------------------------------------\n";
        cout << "Penjelasan Rincian Perhitungan:\n";
        cout << "  - Pasien sedang dilayani dokter : Nomor " << q.getFront() << "\n";
        cout << "  - Jumlah pasien di depan Anda   : " << jumlahDiDepan << " orang\n";
        cout << "  - Estimasi waktu per pasien     : " << waktuPeriksaPerPasien << " menit\n";
        cout << "  - Total waktu tunggu            : " << jumlahDiDepan << " x " 
             << waktuPeriksaPerPasien << " = " << totalWaktuTunggu << " Menit.\n";
    } else {
        cout << "Nomor antrian tidak valid atau tidak ada dalam daftar antrian aktif.\n";
    }
    cout << "============================================================\n";
}

int main() {
    int mode = 0;

    cout << "============================================================\n";
    cout << "   PROGRAM ESTIMASI WAKTU TUNGGU PASIEN KLINIK (SOAL 3)    \n";
    cout << "   Nama : Hellyos Ageng Haqiqie (163251001)                 \n";
    cout << "   Prodi: Teknik Robotika dan Kecerdasan Buatan (FTMM)      \n";
    cout << "============================================================\n";
    cout << "Pilih mode eksekusi:\n";
    cout << "1. Jalankan Demonstrasi Otomatis (Persis Contoh Soal PDF)\n";
    cout << "2. Masuk ke Mode Interaktif Manual (Input Fleksibel Pengguna)\n";
    cout << "Pilihan Anda (1/2): ";

    if (!(cin >> mode)) {
        mode = 1;
    }

    if (mode == 1) {
        jalankanDemoSesuaiSoal();
    } else {
        int noAwal, noAkhir, noAnda, waktuPeriksa;

        cout << "\n--- INPUT DATA ANTRIAN PASIEN ---\n";
        cout << "No Antrian Paling Awal(mis.1) : ";
        cin >> noAwal;
        cout << "No Antrian Paling Akhir(mis.10) : ";
        cin >> noAkhir;

        if (noAwal > noAkhir || noAwal <= 0) {
            cout << "[Error] Rentang nomor antrian tidak valid!\n";
            return 1;
        }

        QueuePasien q;
        for (int i = noAwal; i <= noAkhir; ++i) {
            q.enqueue(i);
        }

        cout << "\nNo Antrian Saat Ini :\n";
        q.cetakAntrian();

        cout << "No Antrian Anda(" << noAwal << "-" << noAkhir << ") : ";
        cin >> noAnda;

        cout << "Perkiraan Waktu Periksa Per Pasien(menit) : ";
        cin >> waktuPeriksa;

        int pasienDiDepan = q.hitungPasienDiDepan(noAnda);
        cout << "\n------------------------------------------------------------\n";
        if (pasienDiDepan == 0) {
            cout << "Nomor antrian Anda (" << noAnda << ") adalah GILIRAN SEKARANG!\n";
            cout << "Waktu tunggu: 0 Menit (Silakan langsung masuk ruang periksa).\n";
        } else if (pasienDiDepan > 0) {
            int totalWaktu = pasienDiDepan * waktuPeriksa;
            cout << "Anda Harus Menunggu " << totalWaktu << " Menit Sampai Giliran Anda\n";
            cout << "(Terdapat " << pasienDiDepan << " pasien di depan Anda)\n";
        } else {
            cout << "Nomor antrian Anda (" << noAnda << ") tidak ditemukan dalam antrian aktif!\n";
        }
        cout << "------------------------------------------------------------\n";
    }

    return 0;
}
