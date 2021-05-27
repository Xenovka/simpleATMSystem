#ifndef _VARANDSTRUCT_
#define _VARANDSTRUCT_



// * GLOBAL VARIABLE
char insertPin[7], insertUlangPin[7]; // * digunakan untuk menampung PIN yang di insert oleh pengguna
int dataTotal = 0, index = 0, counter = 0, flag = 0; // * menyimpan iterasi untuk mencari index dari pengguna

/*
* Struct data berfungsi untuk menyimpan data semua user yang dapat melakukan transaksi yang
* sudah disiapkan dalam file txt yang bernama "data.txt".
*/
struct data {
    char userPIN[7], nama[250], noRek[20], namaBank[100];
    float saldoUser;
    struct data *next;
} pengguna[255], sort[255], *head, *tail, *node;

/*
* Struct rekeningData berfungsi untuk menyimpan data nomor rekening pengguna
* beserta kode bank yang akan kami gunakan pada saat transaksi nantinya.
*/
struct rekeningData{
    char noRek[20], kode[10];
}rekeningData[50];

/*
* Typedef struct Menu berfungsi untuk menyimpan string yang kemudian akan ditampilkan
* pada menu nantinya.
*/
typedef struct Menu{
    char angka[4];
    char fitur[30];

    struct Menu *next;
} Menu;

/*
* Struct dataBank berfungsi untuk menyimpan daftar nama bank dan kode bank
* yang dapat melakukan transaksi pada program ATM bank kami.
*/
struct dataBank {
    char nama[100], kode[10];
} kodeBank[50];


#endif
