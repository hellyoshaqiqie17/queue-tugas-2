/**
 * ============================================================================
 * Program     : Sistem Antrian Teller BRI Cik Ditiro (Soal 2)
 * Mata Kuliah : SIA103 Struktur Data
 * Topik       : Tugas 2 - Queue (Antrian) FCFS & Dual Menu
 * Nama        : Hellyos Ageng Haqiqie
 * NIM         : 163251001
 * Prodi       : Teknik Robotika dan Kecerdasan Buatan (TRKB)
 * Fakultas    : Fakultas Teknologi Maju dan Multidisiplin (FTMM)
 * Universitas : Universitas Airlangga
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

// Struktur Data Node Nasabah untuk Linked List Queue
struct NodeNasabah {
    int nomorAntrian;
    string namaNasabah;
    string keperluan;
    NodeNasabah* next;

    NodeNasabah(int no, const string& nama, const string& kep)
        : nomorAntrian(no), namaNasabah(nama), keperluan(kep), next(nullptr) {}
};

// Kelas Queue berbasis Linked List untuk Nasabah (Disiplin FCFS)
class QueueNasabah {
private:
    NodeNasabah* front;
    NodeNasabah* rear;
    int count;

public:
    QueueNasabah() : front(nullptr), rear(nullptr), count(0) {}

    ~QueueNasabah() {
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

    // Operasi Enqueue (Nasabah Mengambil Nomor Antrian)
    void enqueue(int no, const string& nama, const string& kep) {
        NodeNasabah* baru = new NodeNasabah(no, nama, kep);
        if (isEmpty()) {
            front = rear = baru;
        } else {
            rear->next = baru;
            rear = baru;
        }
        count++;
    }

    // Operasi Dequeue (Teller Memanggil Nasabah Terdepan Sesuai FCFS)
    bool dequeue(int& noOut, string& namaOut, string& kepOut) {
        if (isEmpty()) {
            return false;
        }
        NodeNasabah* temp = front;
        noOut = temp->nomorAntrian;
        namaOut = temp->namaNasabah;
        kepOut = temp->keperluan;

        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        count--;
        return true;
    }

    void dequeue() {
        if (!isEmpty()) {
            NodeNasabah* temp = front;
            front = front->next;
            if (front == nullptr) rear = nullptr;
            delete temp;
            count--;
        }
    }

    // Peek elemen paling depan
    bool peek(int& noOut, string& namaOut) const {
        if (isEmpty()) return false;
        noOut = front->nomorAntrian;
        namaOut = front->namaNasabah;
        return true;
    }

    // Menghitung berapa nasabah yang mengantri di depan nomor tertentu
    int posisiAntrian(int noCari) const {
        NodeNasabah* curr = front;
        int posisi = 0;
        while (curr != nullptr) {
            if (curr->nomorAntrian == noCari) {
                return posisi;
            }
            posisi++;
            curr = curr->next;
        }
        return -1; // Tidak ditemukan di antrian
    }

    // Menampilkan seluruh daftar antrian
    void tampilkanAntrian() const {
        if (isEmpty()) {
            cout << "|            [Antrian Kosong - Tidak ada nasabah menunggu]             |\n";
            return;
        }
        NodeNasabah* curr = front;
        int urutan = 1;
        while (curr != nullptr) {
            cout << "| " << setw(4) << urutan++ 
                 << " | No. " << setw(5) << curr->nomorAntrian 
                 << " | " << left << setw(22) << curr->namaNasabah 
                 << " | " << setw(25) << curr->keperluan << " |\n";
            curr = curr->next;
        }
    }
};

// Struktur Data Status Teller
struct Teller {
    int idTeller;
    string namaTeller;
    bool isMelayani;
    int nomorNasabahAktif;
    string namaNasabahAktif;
    string keperluanAktif;
    int totalNasabahDilayani;

    Teller(int id, const string& nama)
        : idTeller(id), namaTeller(nama), isMelayani(false),
          nomorNasabahAktif(0), namaNasabahAktif("-"), keperluanAktif("-"),
          totalNasabahDilayani(0) {}
};

// Kelas Sistem Antrian Bank BRI Cik Ditiro
class SistemAntrianBRI {
private:
    QueueNasabah antrianBank;
    vector<Teller> daftarTeller;
    int counterNomorAntrian;
    const int JUMLAH_TELLER = 7;

public:
    SistemAntrianBRI() : counterNomorAntrian(0) {
        // Inisialisasi 7 Teller pada Bank BRI Cik Ditiro
        for (int i = 1; i <= JUMLAH_TELLER; ++i) {
            daftarTeller.emplace_back(i, "Teller " + to_string(i) + " (Loket " + to_string(i) + ")");
        }
    }

    // === FITUR MENU NASABAH ===

    int nasabahAmbilAntrian(const string& nama, const string& keperluan) {
        counterNomorAntrian++;
        antrianBank.enqueue(counterNomorAntrian, nama, keperluan);
        return counterNomorAntrian;
    }

    void cekStatusAntrianNasabah(int noAntrian) {
        int posisi = antrianBank.posisiAntrian(noAntrian);
        cout << "\n------------------------------------------------------------\n";
        cout << "STATUS NOMOR ANTRIAN: " << noAntrian << "\n";
        cout << "------------------------------------------------------------\n";
        if (posisi == 0) {
            cout << ">> Anda berada di URUTAN PERTAMA! Harap bersiap dipanggil ke loket teller.\n";
        } else if (posisi > 0) {
            cout << ">> Anda berada di antrian ke-" << (posisi + 1) << ".\n";
            cout << ">> Terdapat " << posisi << " nasabah di depan antrian Anda.\n";
        } else {
            // Cek apakah sedang dilayani di salah satu teller
            bool sedangDilayani = false;
            for (const auto& t : daftarTeller) {
                if (t.isMelayani && t.nomorNasabahAktif == noAntrian) {
                    cout << ">> Nasabah dengan nomor " << noAntrian 
                         << " saat ini SEDANG DILAYANI di " << t.namaTeller << ".\n";
                    sedangDilayani = true;
                    break;
                }
            }
            if (!sedangDilayani) {
                cout << ">> Nomor antrian " << noAntrian 
                     << " tidak ditemukan dalam antrian tunggu (mungkin telah selesai dilayani).\n";
            }
        }
        cout << "------------------------------------------------------------\n";
    }

    void lihatDaftarAntrian() const {
        cout << "\n====================================================================\n";
        cout << "         DAFTAR ANTRIAN NASABAH TUNGGU - BRI CIK DITIRO            \n";
        cout << "====================================================================\n";
        cout << "+------+------------+------------------------+---------------------------+\n";
        cout << "| Pos  | Nomor      | Nama Nasabah           | Keperluan Layanan         |\n";
        cout << "+------+------------+------------------------+---------------------------+\n";
        antrianBank.tampilkanAntrian();
        cout << "+------+------------+------------------------+---------------------------+\n";
        cout << "Total Nasabah Menunggu Antrian: " << antrianBank.size() << " orang.\n";
    }

    // === FITUR MENU TELLER ===

    bool panggilNasabahBerikutnya(int idTeller) {
        if (idTeller < 1 || idTeller > JUMLAH_TELLER) {
            cout << "[Error] ID Teller tidak valid (pilih 1 - 7)!\n";
            return false;
        }

        Teller& t = daftarTeller[idTeller - 1];

        if (t.isMelayani) {
            cout << "[Peringatan] " << t.namaTeller 
                 << " masih melayani Nasabah No. " << t.nomorNasabahAktif 
                 << " (" << t.namaNasabahAktif << "). Selesaikan pelayanan terlebih dahulu!\n";
            return false;
        }

        int no;
        string nama, kep;
        if (antrianBank.dequeue(no, nama, kep)) {
            t.isMelayani = true;
            t.nomorNasabahAktif = no;
            t.namaNasabahAktif = nama;
            t.keperluanAktif = kep;
            cout << "\n[PANGGILAN DIBERIKAN]\n";
            cout << ">> \"Nomor Antrian " << no << " (" << nama 
                 << ") silakan menuju ke " << t.namaTeller << " untuk layanan " << kep << ".\"\n";
            return true;
        } else {
            cout << "[Informasi] Antrian nasabah sedang KOSONG. Tidak ada nasabah untuk dilayani.\n";
            return false;
        }
    }

    bool selesaikanPelayanan(int idTeller) {
        if (idTeller < 1 || idTeller > JUMLAH_TELLER) {
            cout << "[Error] ID Teller tidak valid (pilih 1 - 7)!\n";
            return false;
        }

        Teller& t = daftarTeller[idTeller - 1];
        if (!t.isMelayani) {
            cout << "[Informasi] " << t.namaTeller << " saat ini sedang IDLE (tidak sedang melayani nasabah).\n";
            return false;
        }

        cout << "\n[PELAYANAN SELESAI]\n";
        cout << ">> " << t.namaTeller << " telah selesai melayani Nasabah No. " 
             << t.nomorNasabahAktif << " (" << t.namaNasabahAktif << ").\n";
        cout << ">> Nasabah telah meninggalkan sistem antrian.\n";

        t.isMelayani = false;
        t.nomorNasabahAktif = 0;
        t.namaNasabahAktif = "-";
        t.keperluanAktif = "-";
        t.totalNasabahDilayani++;
        return true;
    }

    void tampilkanStatusSemuaTeller() const {
        cout << "\n========================================================================================\n";
        cout << "                    STATUS 7 TELLER OPERASIONAL - BRI CIK DITIRO                        \n";
        cout << "========================================================================================\n";
        cout << "+----+-----------------------------+------------+------------+--------------------+---+\n";
        cout << "| ID | Loket / Nama Teller         | Status     | No Nasabah | Nama Nasabah       |Tot|\n";
        cout << "+----+-----------------------------+------------+------------+--------------------+---+\n";
        for (const auto& t : daftarTeller) {
            cout << "| " << setw(2) << t.idTeller 
                 << " | " << left << setw(27) << t.namaTeller 
                 << " | " << setw(10) << (t.isMelayani ? "SIBUK" : "IDLE (SIAP)")
                 << " | " << right << setw(10) << (t.isMelayani ? to_string(t.nomorNasabahAktif) : "-")
                 << " | " << left << setw(18) << (t.isMelayani ? t.namaNasabahAktif : "-")
                 << " | " << right << setw(2) << t.totalNasabahDilayani << "|\n";
        }
        cout << "+----+-----------------------------+------------+------------+--------------------+---+\n";
    }

    // Jalankan Simulasi Otomatis FCFS
    void jalankanSimulasiOtomatis() {
        cout << "\n====================================================================\n";
        cout << "   MENJALANKAN SIMULASI LENGKAP SISTEM ANTRIAN TELLER BRI CIK DITIRO\n";
        cout << "====================================================================\n";

        cout << "\n>>> 1. KEDATANGAN NASABAH (ENQUEUE SESUAI FCFS)\n";
        nasabahAmbilAntrian("hellyos ageng", "Setor Tunai");
        cout << "[Tiket Diambil] No. 1: hellyos ageng (Setor Tunai)\n";
        nasabahAmbilAntrian("haqiqie", "Pembukaan Rekening");
        cout << "[Tiket Diambil] No. 2: haqiqie (Pembukaan Rekening)\n";
        nasabahAmbilAntrian("ageng haqiqie", "Tarik Tunai");
        cout << "[Tiket Diambil] No. 3: ageng haqiqie (Tarik Tunai)\n";
        nasabahAmbilAntrian("bambang pamungkas", "Penggantian Kartu ATM");
        cout << "[Tiket Diambil] No. 4: bambang pamungkas (Penggantian Kartu ATM)\n";
        nasabahAmbilAntrian("erling halland", "Transfer Antarbank");
        cout << "[Tiket Diambil] No. 5: erling halland (Transfer Antarbank)\n";
        nasabahAmbilAntrian("C. ronaldo", "Kliring Cek");
        cout << "[Tiket Diambil] No. 6: C. ronaldo (Kliring Cek)\n";
        nasabahAmbilAntrian("Mark zuckerberg", "Setor Tunai");
        cout << "[Tiket Diambil] No. 7: Mark zuckerberg (Setor Tunai)\n";
        nasabahAmbilAntrian("elon musk", "Pembayaran Pajak");
        cout << "[Tiket Diambil] No. 8: elon musk (Pembayaran Pajak)\n";

        lihatDaftarAntrian();

        cout << "\n>>> 2. TELLER MELAKUKAN PEMANGGILAN NASABAH SESUAI FCFS (DEQUEUE)\n";
        // Panggil nasabah pada Teller 1, 2, 3, 4, 5, 6, 7
        panggilNasabahBerikutnya(1); // Melayani No. 1
        panggilNasabahBerikutnya(2); // Melayani No. 2
        panggilNasabahBerikutnya(3); // Melayani No. 3
        panggilNasabahBerikutnya(4); // Melayani No. 4

        tampilkanStatusSemuaTeller();
        lihatDaftarAntrian();

        cout << "\n>>> 3. CEK STATUS ANTRIAN OLEH NASABAH NO. 5 DAN NO. 8\n";
        cekStatusAntrianNasabah(5); // Harus di posisi 0 (terdepan berikutnya)
        cekStatusAntrianNasabah(8); // Berada di posisi 3

        cout << "\n>>> 4. TELLER 1 DAN TELLER 2 MENYELESAIKAN PELAYANAN\n";
        selesaikanPelayanan(1);
        selesaikanPelayanan(2);

        cout << "\n>>> 5. TELLER 1 DAN TELLER 2 MEMANGGIL NASABAH BERIKUTNYA\n";
        panggilNasabahBerikutnya(1); // Melayani No. 5
        panggilNasabahBerikutnya(2); // Melayani No. 6

        tampilkanStatusSemuaTeller();
        lihatDaftarAntrian();
        cout << "\n[SIMULASI SELESAI DENGAN SUKSES]\n";
    }
};

int main() {
    SistemAntrianBRI sistemBRI;
    int menuUtama = 0;

    cout << "============================================================\n";
    cout << "    SISTEM INFORMASI ANTRIAN TELLER BANK BRI CIK DITIRO     \n";
    cout << "    Nama : Hellyos Ageng Haqiqie (163251001)                \n";
    cout << "    Prodi: Teknik Robotika dan Kecerdasan Buatan (FTMM)     \n";
    cout << "============================================================\n";

    while (true) {
        cout << "\n========================================\n";
        cout << "               MENU UTAMA               \n";
        cout << "========================================\n";
        cout << "1. Menu Nasabah\n";
        cout << "2. Menu Teller (7 Loket Operasional)\n";
        cout << "3. Jalankan Simulasi Otomatis (Demo Lengkap)\n";
        cout << "4. Keluar\n";
        cout << "Pilih opsi [1-4]: ";

        if (!(cin >> menuUtama)) {
            break;
        }

        if (menuUtama == 1) {
            // === MENU NASABAH ===
            int menuNasabah = 0;
            while (true) {
                cout << "\n--- MENU KHUSUS NASABAH ---\n";
                cout << "1. Ambil Nomor Antrian Baru\n";
                cout << "2. Cek Status & Sisa Antrian di Depan Saya\n";
                cout << "3. Lihat Daftar Antrian Saat Ini\n";
                cout << "4. Kembali ke Menu Utama\n";
                cout << "Pilih menu nasabah [1-4]: ";
                if (!(cin >> menuNasabah) || menuNasabah == 4) break;

                if (menuNasabah == 1) {
                    cin.ignore();
                    string nama, kep;
                    cout << "Masukkan Nama Nasabah     : ";
                    getline(cin, nama);
                    cout << "Masukkan Keperluan Layanan : ";
                    getline(cin, kep);
                    int no = sistemBRI.nasabahAmbilAntrian(nama, kep);
                    cout << "\n[BERHASIL] Tiket Antrian Anda: NO. " << no << "\n";
                    cout << "Silakan menunggu hingga nomor Anda dipanggil oleh salah satu teller.\n";
                } else if (menuNasabah == 2) {
                    int no;
                    cout << "Masukkan Nomor Antrian Anda: ";
                    cin >> no;
                    sistemBRI.cekStatusAntrianNasabah(no);
                } else if (menuNasabah == 3) {
                    sistemBRI.lihatDaftarAntrian();
                } else {
                    cout << "[Error] Pilihan menu nasabah tidak valid!\n";
                }
            }
        } else if (menuUtama == 2) {
            // === MENU TELLER ===
            int menuTeller = 0;
            while (true) {
                cout << "\n--- MENU KHUSUS TELLER (7 TELLER BRI) ---\n";
                cout << "1. Panggil / Layani Nasabah Berikutnya (FCFS)\n";
                cout << "2. Selesaikan Pelayanan Nasabah\n";
                cout << "3. Tampilkan Status 7 Loket Teller\n";
                cout << "4. Lihat Antrian Nasabah Menunggu\n";
                cout << "5. Kembali ke Menu Utama\n";
                cout << "Pilih menu teller [1-5]: ";
                if (!(cin >> menuTeller) || menuTeller == 5) break;

                if (menuTeller == 1) {
                    int idT;
                    cout << "Pilih ID Teller yang memanggil (1-7): ";
                    cin >> idT;
                    sistemBRI.panggilNasabahBerikutnya(idT);
                } else if (menuTeller == 2) {
                    int idT;
                    cout << "Pilih ID Teller yang selesai (1-7): ";
                    cin >> idT;
                    sistemBRI.selesaikanPelayanan(idT);
                } else if (menuTeller == 3) {
                    sistemBRI.tampilkanStatusSemuaTeller();
                } else if (menuTeller == 4) {
                    sistemBRI.lihatDaftarAntrian();
                } else {
                    cout << "[Error] Pilihan menu teller tidak valid!\n";
                }
            }
        } else if (menuUtama == 3) {
            sistemBRI.jalankanSimulasiOtomatis();
        } else if (menuUtama == 4) {
            cout << "\nTerima kasih. Program Sistem Antrian BRI Cik Ditiro ditutup.\n";
            break;
        } else {
            cout << "[Error] Opsi menu utama tidak valid!\n";
        }
    }

    return 0;
}
