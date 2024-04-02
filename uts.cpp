#include <iostream>
#include <string>
using namespace std;

// mendifinisikan struct tamu yang menyimpan data tamu
struct Tamu {
    string nama;
    string ktp;
    string alamat;
    int umur;
    string telepon;
    string email;
    string checkin;
    string checkout;
    string catatan;
    char kelamin; // Menggunakan char untuk tipe kelamin
};

// mendifinisikan struct kamar yang menyimpan data kamar
struct Kamar {
    int Nokamar;
    string roomType;
    bool balkon;
    bool bathub;
    bool sarapan;
    bool booked;
};

// mendifinisikan struct reservasi yang menyimpan data tamu dan data kamar
struct Reservasi {
    Tamu dataTamu;
    Kamar dataKamar;
    Reservasi* next;
};

// deklarasi pointer head yang menunjuk ke awal daftar reservasi. Diinisialisasi dengan nullptr.
Reservasi* head = nullptr;

// menentukan jumlah maksimal kamar hotel
const int MAX_KAMAR = 50;

// fungsi untuk pembersihan layar terminal
void bersih() {
#ifdef _WIN32
    system("cls");  // untuk Windows
#else
    system("clear");  // untuk Unix-like systems
#endif
}

// fungsi menampilkan header program
void kepala() {
    cout << "============================================" << endl;
    cout << "||        Reservasi Hotel Blue Cosmo      ||" << endl;
    cout << "============================================" << endl;
}

// fungsi menentukan nomor kamar beserta fasilitas yang didapat
void inisialisasiKamar() {
    int nomorkamarstandard = 100;
    int nomorkamardeluxe = 200;
    int nomorkamarsuperior = 300;
    int nomorkamarpresidential = 400;
    
    // Inisialisasi kamar standard
    for (int i = 0; i < 18; i++) {
        Kamar kamar = {nomorkamarstandard++, "standard", false, false, false, false};
        Reservasi* newReservasi = new Reservasi;
        newReservasi->dataKamar = kamar;
        newReservasi->next = nullptr;
        if (head == nullptr) {
            head = newReservasi;
        } else {
            Reservasi* temp = head;
            while (temp->next != nullptr)
                temp = temp->next;
            temp->next = newReservasi;
        }
    }

    // Inisialisasi kamar deluxe
    for (int j = 0; j < 18; j++) {
        Kamar kamar = {nomorkamardeluxe++, "deluxe", false, false, true, false};
        Reservasi* newReservasi = new Reservasi;
        newReservasi->dataKamar = kamar;
        newReservasi->next = nullptr;
        Reservasi* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newReservasi;
    }

    // Inisialisasi kamar superior
    for (int k = 0; k < 7; k++) {
        Kamar kamar = {nomorkamarsuperior++, "superior", false, true, true, false};
        Reservasi* newReservasi = new Reservasi;
        newReservasi->dataKamar = kamar;
        newReservasi->next = nullptr;
        Reservasi* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newReservasi;
    }

    // Inisialisasi kamar presidential
    for (int l = 0; l < 7; l++) {
        Kamar kamar = {nomorkamarpresidential++, "presidential", true, true, true, false};
        Reservasi* newReservasi = new Reservasi;
        newReservasi->dataKamar = kamar;
        newReservasi->next = nullptr;
        Reservasi* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newReservasi;
    }
}

// fungsi yang meminta staf untuk melakukan proses check in
// yang didalamnya meminta staf untuk menginput data-data beserta kamar
void checkin() {
    cout << "||              Masukan Data              ||" << endl;
    Tamu tamu;
    cout << "||Nama         : ";
    cin.ignore();
    getline(cin, tamu.nama);
    cout << "||Nomor KTP    : ";
    getline(cin, tamu.ktp);
    cout << "||Alamat       : ";
    getline(cin, tamu.alamat);
    cout << "||Umur         : ";
    cin >> tamu.umur;
    cout << "||Telepon      : ";
    cin.ignore();
    getline(cin, tamu.telepon);
    cout << "||Email        : ";
    getline(cin, tamu.email);
    cout << "||Kelamin (L/P): ";
    cin >> tamu.kelamin;
    cout << "||Check-in (DD-MM-YYYY) : ";
    cin >> tamu.checkin;
    cout << "||Check-out (DD-MM-YYY): ";
    cin >> tamu.checkout;
    cout << "||Catatan Kebutuhan     : ";
    cin.ignore();
    getline(cin, tamu.catatan);

    cout << "Data berhasil disimpan (enter untuk melanjutkan)...";
    cin.ignore(); // Membersihkan buffer input sebelum menunggu masukan
    cin.get(); // Menunggu pengguna menekan tombol sebelum melanjutkan
    bersih();

    cout << "||           Masukan Detail Kamar          ||" << endl;
    cout << "=============================================" << endl;
    cout << "||Tipe Kamar        ||Nomor Kamar          ||" << endl;
    cout << "||1.Standard        ||101-118              ||" << endl;
    cout << "||2.Deluxe          ||201-218              ||" << endl;
    cout << "||3.Superior        ||301-307              ||" << endl;
    cout << "||4.Presidential    ||401-407              ||" << endl;
    cout << "=============================================" << endl;
    bool berhasilCheckin = false;
        do {
        cout << "||Nomor Kamar: ";
        int nomorKamar;
        cin >> nomorKamar;

        // Temukan kamar sesuai nomor yang dimasukkan
        Reservasi* temp = head;
        while (temp != nullptr) {
            if (temp->dataKamar.Nokamar == nomorKamar && !temp->dataKamar.booked) {
                // Jika kamar ditemukan dan belum dibooked, isi data tamu dan tandai kamar sebagai dibooked
                temp->dataTamu = tamu;
                temp->dataKamar.booked = true;
                berhasilCheckin = true;
                cout << "Check-in berhasil!" << endl;
                cout << "Tekan tombol apapun untuk kembali ke menu utama...";
                cin.ignore(); // Membersihkan buffer input sebelum menunggu masukan
                cin.get(); // Menunggu pengguna menekan tombol sebelum melanjutkan
                bersih();
                break;
            }
            temp = temp->next;
        }
        if (!berhasilCheckin) {
            cout << "Nomor kamar tidak valid atau sudah dibooked. Silakan coba lagi." << endl;
        }
    } while (!berhasilCheckin);
}

// fungsi untuk staff melakukan checkout
void checkout() {
    kepala();
    cout << "============================================" << endl;
    cout << "||Masukan nomor kamar yang akan dicheckout||" << endl;
    cout << "||";
    int nomorKamar;
    cin >> nomorKamar;
    
    // Temukan kamar sesuai nomor yang dimasukkan
    Reservasi* temp = head;
    while (temp != nullptr) {
        if (temp->dataKamar.Nokamar == nomorKamar && temp->dataKamar.booked) {
            // Temukan kamar sesuai nomor yang dimasukkan dan buat kamar tersebut tersedia kembali
            temp->dataKamar.booked = false;
            cout << "Checkout berhasil!" << endl;
            cout << "Tekan tombol apapun untuk kembali ke menu utama...";
            cin.ignore(); // Membersihkan buffer input sebelum menunggu masukan
            cin.get(); // Menunggu pengguna menekan tombol sebelum melanjutkan
            bersih();
        }
        temp = temp->next;
    }
    cout << "Nomor kamar tidak valid atau belum dibooked." << endl;
}

// fungsi untuk menampilkan data reservasi seperti nomor kamar dan tamu yang menginap
void tampilkanreservasi() {
    kepala();
    Reservasi* temp = head;
    while (temp != nullptr) {
        if (temp->dataKamar.booked) {
            cout << "Nomor Kamar: " << temp->dataKamar.Nokamar << endl;
            cout << "Tipe Kamar: " << temp->dataKamar.roomType << endl;
            cout << "Nama Tamu: " << temp->dataTamu.nama << endl;
            cout << "Nomor KTP: " << temp->dataTamu.ktp << endl;
            cout << "Alamat: " << temp->dataTamu.alamat << endl;
            cout << "Umur: " << temp->dataTamu.umur << endl;
            cout << "Telepon: " << temp->dataTamu.telepon << endl;
            cout << "Email: " << temp->dataTamu.email << endl;
            cout << "Check-in: " << temp->dataTamu.checkin << endl;
            cout << "Check-out: " << temp->dataTamu.checkout << endl;
            cout << "Catatan Kebutuhan: " << temp->dataTamu.catatan << endl;
            cout << "=================================" << endl;
        }
        temp = temp->next;
    }
        cout << "Tekan tombol apapun untuk kembali ke menu utama...";
        cin.ignore(); // Membersihkan buffer input sebelum menunggu masukan
        cin.get(); // Menunggu pengguna menekan tombol sebelum melanjutkan
        bersih();
}

int main() {
    inisialisasiKamar();

    char pilihan;
    do {
    kepala();
    cout << "||1. Checked-in                           ||" << endl;
    cout << "||2. Checked-out                          ||" << endl;
    cout << "||3. Tampilkan reservasi on progress      ||" << endl;
    cout << "||4. Exit                                 ||" << endl;
    cout << "============================================" << endl;
    cout << "||            Masukan Pilihan             ||" << endl;
    cout << "||";
    cin >> pilihan;

        switch (pilihan) {
            case '1':
                bersih();
                checkin();
                break;
            case '2':
                bersih();
                checkout();
                break;
            case '3':
                bersih();
                tampilkanreservasi();
                break;
            case '4':
                cout << "Program selesai." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }
    } while (pilihan != '4');

    return 0;
}
