/**
 * ============================================================================
 * Program     : Simulasi Tempat Parkir Mobil dengan Penampungan Sementara (Soal 4)
 * Mata Kuliah : SIA103 Struktur Data
 * Topik       : Tugas 2 - Queue (Antrian) Simulasi Parkir Jalur Tunggal
 * Nama        : Hellyos Ageng Haqiqie
 * NIM         : 163251001
 * Prodi       : Teknik Robotika dan Kecerdasan Buatan (TRKB)
 * Fakultas    : Fakultas Teknologi Maju dan Multidisiplin (FTMM)
 * Universitas : Universitas Airlangga
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Node Mobil untuk Linked List Queue
struct NodeMobil {
    string platNomor;
    string merkModel;
    NodeMobil* next;

    NodeMobil(const string& plat, const string& merk = "Mobil Pribadi")
        : platNomor(plat), merkModel(merk), next(nullptr) {}
};

// Kelas Queue Tempat Parkir
class ParkirQueue {
private:
    NodeMobil* front;
    NodeMobil* rear;
    int count;
    int kapasitas;

public:
    ParkirQueue(int cap = 10) : front(nullptr), rear(nullptr), count(0), kapasitas(cap) {}

    ~ParkirQueue() {
        clear();
    }

    void clear() {
        while (!isEmpty()) {
            string p, m;
            dequeue(p, m);
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    bool isFull() const {
        return count >= kapasitas;
    }

    int size() const {
        return count;
    }

    int getKapasitas() const {
        return kapasitas;
    }

    // 1. Proses Mobil Masuk (Enqueue)
    bool enqueue(const string& plat, const string& merk = "Mobil") {
        if (isFull()) {
            cout << "[GAGAL PARKIR] Tempat parkir sudah penuh (Kapasitas " << kapasitas << " mobil)!\n";
            return false;
        }

        NodeMobil* baru = new NodeMobil(plat, merk);
        if (isEmpty()) {
            front = rear = baru;
        } else {
            rear->next = baru;
            rear = baru;
        }
        count++;
        cout << "[MOBIL MASUK] Mobil (" << plat << " - " << merk << ") berhasil parkir di antrian ke-" << count << ".\n";
        return true;
    }

    // 2. Proses Mobil Paling Depan Keluar (Dequeue)
    bool dequeue(string& platKeluar, string& merkKeluar) {
        if (isEmpty()) {
            cout << "[GAGAL KELUAR] Tempat parkir kosong, tidak ada mobil untuk keluar.\n";
            return false;
        }

        NodeMobil* temp = front;
        platKeluar = temp->platNomor;
        merkKeluar = temp->merkModel;

        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        count--;
        return true;
    }

    // Mencari posisi mobil berdasarkan plat nomor (1-based index dari front)
    int cariPosisiMobil(const string& plat) const {
        NodeMobil* curr = front;
        int pos = 1;
        while (curr != nullptr) {
            if (curr->platNomor == plat) {
                return pos;
            }
            curr = curr->next;
            pos++;
        }
        return -1; // Tidak ditemukan
    }

    // 3. Proses Mobil Tengah Keluar dengan Penampungan Sementara
    bool mobilTengahKeluar(const string& platTarget) {
        if (isEmpty()) {
            cout << "[GAGAL] Tempat parkir kosong!\n";
            return false;
        }

        int posisiTarget = cariPosisiMobil(platTarget);
        if (posisiTarget == -1) {
            cout << "[GAGAL] Mobil dengan plat \"" << platTarget << "\" tidak ditemukan di area parkir!\n";
            return false;
        }

        cout << "\n====================================================================\n";
        cout << "   PROSES PENGELUARAN MOBIL DARI AREA PARKIR DENGAN BUFFER ANTRIAN  \n";
        cout << "====================================================================\n";
        cout << "Target Mobil Keluar : " << platTarget << " (Berada pada Posisi ke-" << posisiTarget << " dari Depan)\n";

        // Kasus Khusus: Jika target berada di posisi paling depan (posisi 1)
        if (posisiTarget == 1) {
            string p, m;
            dequeue(p, m);
            cout << ">> Mobil berada di paling depan. Langsung keluar tanpa perlu memindahkan mobil lain.\n";
            cout << ">> [SUKSES KELUAR] Mobil " << p << " (" << m << ") telah meninggalkan area parkir.\n";
            cout << "====================================================================\n";
            return true;
        }

        // Penampungan Sementara Mobil (Queue Sementara)
        ParkirQueue penampunganSementara(kapasitas);

        cout << "\n[FASE 1] Memindahkan mobil-mobil di depan target ke penampungan sementara:\n";
        // Keluarkan mobil di depan target sebanyak (posisiTarget - 1)
        for (int i = 1; i < posisiTarget; ++i) {
            string p, m;
            dequeue(p, m);
            penampunganSementara.enqueue(p, m);
            cout << "   -> Mobil (" << p << ") dipindahkan sementara ke area penampungan.\n";
        }

        // Keluarkan mobil target
        string targetPlat, targetMerk;
        dequeue(targetPlat, targetMerk);
        cout << "\n[FASE 2] Mobil Target Keluar:\n";
        cout << "   -> [SUKSES KELUAR] Mobil (" << targetPlat << " - " << targetMerk << ") keluar dari area parkir!\n";

        // Masukkan kembali mobil dari penampungan sementara dan menyusun tempat parkir kembali
        cout << "\n[FASE 3] Memasukkan kembali mobil dari penampungan sementara ke tempat parkir:\n";
        // Agar urutan mobil di depan target tersusun kembali persis seperti semula di depan antrian parkir,
        // kita pindahkan kembali isi penampungan sementara ke antrian baru lalu gabungkan dengan sisa parkir
        ParkirQueue parkirBaru(kapasitas);

        // Masukkan mobil-mobil dari penampungan sementara ke parkirBaru
        while (!penampunganSementara.isEmpty()) {
            string p, m;
            penampunganSementara.dequeue(p, m);
            parkirBaru.enqueue(p, m);
            cout << "   -> Mobil (" << p << ") dimasukkan kembali ke tempat parkir utama.\n";
        }

        // Masukkan sisa mobil yang tadinya di belakang target (jika ada) ke parkirBaru
        while (!isEmpty()) {
            string p, m;
            dequeue(p, m);
            parkirBaru.enqueue(p, m);
        }

        // Pindahkan seluruh isi parkirBaru ke antrian utama (this)
        while (!parkirBaru.isEmpty()) {
            string p, m;
            parkirBaru.dequeue(p, m);
            enqueue(p, m);
        }

        cout << "\n[SELESAI] Tempat parkir berhasil disusun kembali seperti semula.\n";
        cout << "====================================================================\n";
        return true;
    }

    // Menampilkan status seluruh mobil di area parkir
    void tampilkanStatusParkir() const {
        cout << "\n====================================================================\n";
        cout << "                  KONDISI TEMPAT PARKIR SAAT INI                    \n";
        cout << "====================================================================\n";
        cout << "Kapasitas Terisi: " << count << " / " << kapasitas << " mobil.\n";
        cout << "+--------+---------------------+-----------------------------------+\n";
        cout << "| Posisi | Plat Nomor          | Tipe / Merk Mobil                 |\n";
        cout << "+--------+---------------------+-----------------------------------+\n";
        if (isEmpty()) {
            cout << "|       [TEMPAT PARKIR KOSONG - TIDAK ADA KENDARAAN TERPARKIR]     |\n";
        } else {
            NodeMobil* curr = front;
            int pos = 1;
            while (curr != nullptr) {
                string keterangan = "";
                if (pos == 1 && count == 1) keterangan = " (Depan & Belakang)";
                else if (pos == 1) keterangan = " (Paling Depan / Siap Keluar)";
                else if (pos == count) keterangan = " (Paling Belakang / Terakhir)";

                cout << "| " << setw(6) << pos 
                     << " | " << left << setw(19) << curr->platNomor 
                     << " | " << setw(33) << (curr->merkModel + keterangan) << " |\n";
                curr = curr->next;
                pos++;
            }
        }
        cout << "+--------+---------------------+-----------------------------------+\n";
    }
};

// Prosedur demonstrasi otomatis sesuai proses yang diinstruksikan dalam soal
void jalankanDemoOtomatis(ParkirQueue& parkir) {
    cout << "\n====================================================================\n";
    cout << "     MENJALANKAN DEMONSTRASI OTOMATIS SIMULASI TEMPAT PARKIR        \n";
    cout << "====================================================================\n";

    cout << "\n>>> 1. PROSES MOBIL MASUK (PARKIR BEBERAPA MOBIL SECARA BERURUTAN)\n";
    parkir.enqueue("L 1001 RK", "Toyota Avanza");
    parkir.enqueue("B 2026 AI", "Honda Civic");
    parkir.enqueue("N 3333 TR", "Mitsubishi Xpander"); // Mobil tengah
    parkir.enqueue("W 4567 FT", "Suzuki Ertiga");
    parkir.enqueue("D 5555 MM", "Hyundai Ioniq 5");

    parkir.tampilkanStatusParkir();

    cout << "\n>>> 2. PROSES MOBIL PALING DEPAN KELUAR (NORMAL DEQUEUE)\n";
    string platKeluar, merkKeluar;
    if (parkir.dequeue(platKeluar, merkKeluar)) {
        cout << "[MOBIL KELUAR] Mobil paling depan (" << platKeluar << " - " 
             << merkKeluar << ") telah keluar dari parkir.\n";
    }
    parkir.tampilkanStatusParkir();

    cout << "\n>>> 3. PROSES MOBIL TENGAH KELUAR DENGAN PENAMPUNGAN SEMENTARA\n";
    cout << "[SKENARIO] Mobil 'N 3333 TR' (yang berada di tengah) ingin keluar...\n";
    parkir.mobilTengahKeluar("N 3333 TR");

    parkir.tampilkanStatusParkir();

    cout << "\n>>> 4. PROSES PENAMBAHAN MOBIL BARU LAGI SETELAH DISUSUN KEMBALI\n";
    parkir.enqueue("L 8888 UN", "Daihatsu Terios");
    parkir.tampilkanStatusParkir();
}

int main() {
    ParkirQueue parkir(8); // Kapasitas 8 mobil
    int opsi = 0;

    cout << "============================================================\n";
    cout << "     SIMULASI TEMPAT PARKIR MOBIL BERBASIS QUEUE (SOAL 4)   \n";
    cout << "     Nama : Hellyos Ageng Haqiqie (163251001)               \n";
    cout << "     Prodi: Teknik Robotika dan Kecerdasan Buatan (FTMM)    \n";
    cout << "============================================================\n";

    while (true) {
        cout << "\n--- MENU SIMULASI PARKIR ---\n";
        cout << "1. Mobil Masuk (Enqueue)\n";
        cout << "2. Mobil Paling Depan Keluar (Dequeue)\n";
        cout << "3. Mobil Tengah Keluar (Dengan Penampungan Sementara)\n";
        cout << "4. Tampilkan Status Tempat Parkir\n";
        cout << "5. Jalankan Demonstrasi Otomatis Lengkap\n";
        cout << "6. Keluar Program\n";
        cout << "Pilih opsi [1-6]: ";

        if (!(cin >> opsi)) break;

        if (opsi == 1) {
            cin.ignore();
            string plat, merk;
            cout << "Masukkan Nomor Plat Mobil (mis. L 1234 AB): ";
            getline(cin, plat);
            cout << "Masukkan Merk / Jenis Mobil               : ";
            getline(cin, merk);
            parkir.enqueue(plat, merk);
        } else if (opsi == 2) {
            string p, m;
            if (parkir.dequeue(p, m)) {
                cout << "[SUKSES] Mobil paling depan (" << p << " - " << m << ") telah keluar.\n";
            }
        } else if (opsi == 3) {
            cin.ignore();
            string platTarget;
            cout << "Masukkan Plat Nomor Mobil yang Ingin Keluar: ";
            getline(cin, platTarget);
            parkir.mobilTengahKeluar(platTarget);
        } else if (opsi == 4) {
            parkir.tampilkanStatusParkir();
        } else if (opsi == 5) {
            parkir.clear();
            jalankanDemoOtomatis(parkir);
        } else if (opsi == 6) {
            cout << "Program simulasi parkir selesai. Terima kasih.\n";
            break;
        } else {
            cout << "[Error] Pilihan menu tidak valid!\n";
        }
    }

    return 0;
}
