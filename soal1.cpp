/**
 * ============================================================================
 * Program     : Kalkulator Sederhana Dua Bilangan (Soal 1)
 * Mata Kuliah : SIA103 Struktur Data
 * Topik       : Tugas 2 - Queue & Fundamental Programming
 * Nama        : Hellyos Ageng Haqiqie
 * NIM         : 163251001
 * Prodi       : Teknik Robotika dan Kecerdasan Buatan (TRKB)
 * Fakultas    : Fakultas Teknologi Maju dan Multidisiplin (FTMM)
 * Universitas : Universitas Airlangga
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

// Helper untuk memformat angka: jika bilangan bulat, tampilkan tanpa desimal
string formatBilangan(double val) {
    if (floor(val) == val && !isinf(val)) {
        stringstream ss;
        ss << fixed << setprecision(0) << val;
        return ss.str();
    }
    stringstream ss;
    ss << val;
    return ss.str();
}

// Fungsi utama kalkulator untuk melakukan operasi aritmatika dasar
bool hitungKalkulator(double bil1, char op, double bil2, double& hasil, string& pesanError) {
    switch (op) {
        case '+':
            hasil = bil1 + bil2;
            return true;
        case '-':
            hasil = bil1 - bil2;
            return true;
        case '*':
        case 'x':
        case 'X':
            hasil = bil1 * bil2;
            return true;
        case '/':
            if (bil2 == 0.0) {
                pesanError = "Kesalahan matematis: Pembagian dengan bilangan nol (division by zero) tidak terdefinisi!";
                return false;
            }
            hasil = bil1 / bil2;
            return true;
        default:
            pesanError = "Kesalahan: Operator '" + string(1, op) + "' tidak valid! Gunakan operator (+, -, *, /).";
            return false;
    }
}

// Prosedur demonstrasi otomatis sesuai contoh pada modul Tugas 2
void jalankanDemoOtomatis() {
    cout << "\n============================================================\n";
    cout << "     DEMONSTRASI OTOMATIS OPERASI KALKULATOR SEDERHANA      \n";
    cout << "============================================================\n";

    struct TestCase {
        double b1;
        char op;
        double b2;
    };

    TestCase tests[] = {
        {16.0, '/', 4.0},   // Contoh 1 dari lembar soal
        {12.0, '+', 2.0},   // Contoh 2 dari lembar soal
        {25.0, '-', 7.0},   // Pengurangan
        {8.0,  '*', 6.0},   // Perkalian
        {15.0, '/', 0.0},   // Uji penanganan error pembagian nol
        {10.0, '^', 2.0}    // Uji operator tidak valid
    };

    for (int i = 0; i < 6; ++i) {
        cout << "\n[Uji Kasus " << (i + 1) << "]\n";
        cout << "Masukkan bilangan 1: " << formatBilangan(tests[i].b1) << "\n";
        cout << "Masukkan operator  : " << tests[i].op << "\n";
        cout << "Masukkan bilangan 2: " << formatBilangan(tests[i].b2) << "\n";

        double hasil = 0.0;
        string err;
        if (hitungKalkulator(tests[i].b1, tests[i].op, tests[i].b2, hasil, err)) {
            cout << "Output: Hasilnya dari " << formatBilangan(tests[i].b1) << " " 
                 << tests[i].op << " " << formatBilangan(tests[i].b2) 
                 << " adalah " << formatBilangan(hasil) << "\n";
        } else {
            cout << "Output: " << err << "\n";
        }
    }
    cout << "\n============================================================\n";
}

int main() {
    int pilihanMode = 0;

    cout << "============================================================\n";
    cout << "   PROGRAM KALKULATOR SEDERHANA DUA BILANGAN (SOAL 1)       \n";
    cout << "   Nama : Hellyos Ageng Haqiqie (163251001)                 \n";
    cout << "   Prodi: Teknik Robotika dan Kecerdasan Buatan (FTMM)      \n";
    cout << "============================================================\n";
    cout << "Pilih mode eksekusi:\n";
    cout << "1. Jalankan Demonstrasi Otomatis (Sesuai Soal Tugas 2)\n";
    cout << "2. Masuk ke Mode Interaktif Manual (Input Pengguna)\n";
    cout << "Pilihan Anda (1/2): ";

    if (!(cin >> pilihanMode)) {
        pilihanMode = 1;
    }

    if (pilihanMode == 1) {
        jalankanDemoOtomatis();
    } else {
        char lanjut = 'y';
        while (lanjut == 'y' || lanjut == 'Y') {
            double bil1, bil2;
            char op;

            cout << "\n--- INPUT KALKULASI ---\n";
            cout << "Masukkan bilangan 1: ";
            while (!(cin >> bil1)) {
                cout << "[Error] Input bilangan tidak valid. Masukkan angka: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }

            cout << "Masukkan operator (+, -, *, /): ";
            cin >> op;

            cout << "Masukkan bilangan 2: ";
            while (!(cin >> bil2)) {
                cout << "[Error] Input bilangan tidak valid. Masukkan angka: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }

            double hasil = 0.0;
            string err;
            if (hitungKalkulator(bil1, op, bil2, hasil, err)) {
                cout << "Hasilnya dari " << formatBilangan(bil1) << " " 
                     << op << " " << formatBilangan(bil2) 
                     << " adalah " << formatBilangan(hasil) << "\n";
            } else {
                cout << "[Gagal] " << err << "\n";
            }

            cout << "\nHitung lagi? (y/n): ";
            cin >> lanjut;
        }
        cout << "\nTerima kasih telah menggunakan program kalkulator.\n";
    }

    return 0;
}
