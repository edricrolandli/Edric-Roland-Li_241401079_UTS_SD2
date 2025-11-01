#include <iostream>
using namespace std;

// struktur node untuk linked list
struct Barang {
    string nama;
    int harga;
    int jumlah;
    Barang* next;
};

// Tambah di depan
void tambah_depan(Barang*& head, string nama, int harga, int jumlah) {
    // intinya disini dia buat node baru, terus tiap isi dari nodenya diisi dengan yg baru
    Barang* baru = new Barang;
    baru->nama = nama;
    baru->harga = harga;
    baru->jumlah = jumlah;
    baru->next = head;
    head = baru; // disini dihubungkan ke paling depan, karena langsung dari head
}

// Tambah di belakang
void tambah_belakang(Barang*& head, string nama, int harga, int jumlah) {
    Barang* baru = new Barang;
    baru->nama = nama;
    baru->harga = harga;
    baru->jumlah = jumlah;
    baru->next = NULL;

    // disini pengecekan dulu, kalau semua masih kosong, maka inilah menjadi node barunya
    if (head == NULL) 
    {
        head = baru;
    } 
    // buat temp node dulu, isinya head, kenapa? biar bisa nanti diganti dgn yg "BARU"
    // kalau sudah ada, nah ini pakai while, dia ngecek node mana yang nantinya itu NULL
    // karena kalau terakhirnya NULL sudah pasti dialah yg terakhir
    // kalau uda ketemu, temp tadi yang uda berisi, di sambungkan lah 
    else 
    {
        Barang* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = baru;
    }
}

// tambah setelah barang tertentu (tengah)
void tambah_setelah(Barang*& head, string target, string nama, int harga, int jumlah) {
    // biasa ya, cek dulu kalau kosong dibuat jadi baru
    if (head == NULL) 
    {
        cout << "Keranjang masih kosong. Barang ditambahkan sebagai barang pertama.\n";
        tambah_depan(head, nama, harga, jumlah);
        return;
    }

    // kalau enggak, buat temp juga seperti sebelumnya
    Barang* temp = head;

    // check sampai ketemu nama sesuai target yg diinginkan
    while (temp != NULL && temp->nama != target)
        temp = temp->next;

    // case kalau gak ada samsek
    if (temp == NULL) 
    {
        cout << "Barang dengan nama \"" << target << "\" tidak ditemukan.\n";
        return;
    }

    // buat node baru
    Barang* baru = new Barang;
    baru->nama = nama;
    baru->harga = harga;
    baru->jumlah = jumlah;

    // inilah tahap dimana yg baru dibuat tadi, itu next alamatnya jadi sama kayak yg si target
    baru->next = temp->next;
    // B -> C | Z -> C
    // A B "Z" C - NULL

    // nah terus target gimana? next nodenya jadi yg si "baru"
    temp->next = baru;
}

//  Fungsi Hapus Barang 
void hapus_barang(Barang*& head, string nama_hapus) {
    if (head == NULL) 
    {
        cout << "Keranjang kosong.\n";
        return;
    }

    Barang* temp = head; // nyari yg mau dihapus
    Barang* prev = NULL; // nyari yg SEBELUM DIHAPUS

    // nyari yg namanya sesuai
    while (temp != NULL && temp->nama != nama_hapus) 
    {
        prev = temp; // prev bakal selalu di belakang temp
        temp = temp->next; // temp bakal terus maju
    }

    // HEAD A B C NULL

    // ini kalau yg dicari itu gak ada
    if (temp == NULL) 
    {
        cout << "Barang tidak ditemukan di keranjang.\n";
        return;
    }

    // ini case kalau sebenarnya hapus org pertama  
    // posisi head diganti jadi orang kedua (next)
    if (prev == NULL)
        head = temp->next;

    // "A" B C

    // tapi kalau bukan, dia sebenarnya lebih ke ganti posisi, tapi seolah menghapus, jadi yg tadinya tersambung, sekarang prev itu next nodenya jadi si setelah temp (temp = yg dihapus ingat)
    else
        prev->next = temp->next;

    // A "B" C NULL
    // A C NULL

    // hapusss
    delete temp;
    cout << "Barang \"" << nama_hapus << "\" berhasil dihapus.\n";
}

//  fungsi tampilkan kKeranjang 
void tampilkan_keranjang(Barang* head) {
    if (head == NULL) 
    {
        cout << "Keranjang kosong.\n";
        return;
    }

    Barang* temp = head;

    // buat dulu ya jadi 0, karena harus ditampung biar bisa di akumulasi smpe akhir
    int total_barang = 0;
    int total_harga = 0;

    // selama nodenya gak kosong
    // tampilkan blaa"
    while (temp != NULL) {
        cout << temp->nama << " - Rp" << temp->harga
             << " x" << temp->jumlah << endl;

        // total barang bakal nambah secara increment +1
        total_barang++;

        // total harga yang tadi udah di definisikan bakal nambah terus
        total_harga += temp->harga * temp->jumlah;

        // ini biar lanjut ke nextnya ya
        temp = temp->next;
    }

    cout << "\nTotal barang: " << total_barang << endl;
    cout << "Total harga: Rp" << total_harga << endl;
}

int main() {
    Barang* head = NULL;
    int jumlah_awal;

    cout << "Masukkan jumlah barang awal: "; cin >> jumlah_awal;

    for (int i = 0; i < jumlah_awal; i++) {
        string nama;
        int harga, jumlah;

        cout << "\nBarang " << i + 1 << ":\n";

        cout << "Nama: "; cin >> ws; getline(cin, nama); // intinya kalau masukin angka dia harus hapus dulu linenya biar bisa getline
        cout << "Harga: "; cin >> harga;
        cout << "Jumlah: "; cin >> jumlah;

        tambah_belakang(head, nama, harga, jumlah);
    }

    char tambah;
    // cek mau tambah gak
    cout << "\nApakah ingin menambah barang lagi? (y/n): "; cin >> tambah;

    while (tambah == 'y' || tambah == 'Y') {
        string nama, target;
        int harga, jumlah, posisi;

        cout << "Pilih posisi tambah barang:\n";
        cout << "1. Tambah di depan\n";
        cout << "2. Tambah di belakang\n";
        cout << "3. Tambah setelah barang tertentu\n";

        cout << "Pilihan: "; cin >> posisi;

        cout << "Nama barang: "; cin >> ws; getline(cin, nama); // masih sama 
        cout << "Harga: "; cin >> harga;
        cout << "Jumlah: "; cin >> jumlah;

        // ini tergantung user milih apa
        if (posisi == 1)
            tambah_depan(head, nama, harga, jumlah);
        else if (posisi == 2)
            tambah_belakang(head, nama, harga, jumlah);
        else if (posisi == 3) 
        {
            cout << "Tambahkan setelah barang apa : "; cin >> ws; getline(cin, target);
            tambah_setelah(head, target, nama, harga, jumlah);
        } 
        else
            cout << "Pilihan tidak valid.\n";

        cout << "\nApakah ingin menambah barang lagi? (y/n): "; cin >> tambah;
    }

    char hapus;
    // ini klo mau hapus
    cout << "\nApakah ingin menghapus barang? (y/n): "; cin >> hapus;

    if (hapus == 'y' || hapus == 'Y') 
    {
        string nama_hapus;
        cout << "Masukkan nama barang yang ingin dihapus: "; cin >> ws; getline(cin, nama_hapus);
        hapus_barang(head, nama_hapus);
    }

    cout << "\n=== Keranjang Belanja Anda ===\n";
    tampilkan_keranjang(head);

    // hapus memoriiii
    while (head != NULL) {
        Barang* hapus = head;
        head = head->next;
        delete hapus;
    }
}
