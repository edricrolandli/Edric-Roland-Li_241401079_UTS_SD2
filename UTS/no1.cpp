#include <iostream>
using namespace std;

struct Pesanan {
    string nama_hewan;
    string menu;
    int waktu_datang;
    int status_vip;
};

int main() {
    system("CLS");

    int jumlah_pesanan;

    cout << "Masukkan jumlah pesanan: "; cin >> jumlah_pesanan;

    // buat dynamic array manual 
    Pesanan* daftar_pesanan = new Pesanan[jumlah_pesanan];

    for (int i = 0; i < jumlah_pesanan; i++) {
        cout << "\nPesanan " << i + 1 << ":\n";

        cout << "Nama hewan: "; cin >> ws; getline(cin, daftar_pesanan[i].nama_hewan); // biar ga error
        cout << "Menu pesanan: "; getline(cin, daftar_pesanan[i].menu);
        cout << "Status VIP (1=biasa, 2=VIP): "; cin >> daftar_pesanan[i].status_vip;

        daftar_pesanan[i].waktu_datang = i + 1;
    }

    // sorting manual
    for (int i = 0; i < jumlah_pesanan - 1; i++) { // intinya ini check semua jumlah pesanan yg ada
        for (int j = 0; j < jumlah_pesanan - i - 1; j++) { // ini bandingin ANTAR PESANAN yang ada
            bool perlu_tukar = false;

            if (daftar_pesanan[j].status_vip < daftar_pesanan[j + 1].status_vip) // status vipnya gimana? kalau yang kiri lebih kecil, maka perlu tukar (karena bukan vip)
                perlu_tukar = true;
            else if (daftar_pesanan[j].status_vip == daftar_pesanan[j + 1].status_vip &&
                     daftar_pesanan[j].waktu_datang > daftar_pesanan[j + 1].waktu_datang) // ini casenya kalau status vip sama, jadi bandingin dari waktu datangnya, kalau waktu datangnya lebih gede ya tukar lagi
                perlu_tukar = true;

            if (perlu_tukar) {
                Pesanan temp = daftar_pesanan[j]; // temp = nyimipen dulu
                daftar_pesanan[j] = daftar_pesanan[j + 1]; // biar bisa diganti ke yg bener, misal yg vip
                daftar_pesanan[j + 1] = temp; // terus yang salah tadi, ganti ke yg tadi uda disimpen
            }
        }
    }

    for (int i = 0; i < jumlah_pesanan; i++) {
        cout << i + 1 << ". " << daftar_pesanan[i].nama_hewan << " - " << daftar_pesanan[i].menu; //formatnya biar angka, terus nama hewan - nama pesanan
        if (daftar_pesanan[i].status_vip == 2)
            cout << "  [VIP]";
        cout << endl;
        // klo ada vip nya
    }

    // Hapus memory
    delete[] daftar_pesanan;
}
