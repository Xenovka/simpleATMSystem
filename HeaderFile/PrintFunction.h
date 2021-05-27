#include <stdio.h>
#include "AVLTree.h"

/*
* function showMenu berfungsi untuk menampilkan tampilan awal program yang mana
* berisi daftar menu yang tersedia di program ATM inin
*/
void showMenu() {
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+%22sMENU%-21s+\n", "", "");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    struct Menu *stackmenu;
    stackmenu = NULL;
    push(&stackmenu, "1. ", "Info Saldo");
    push(&stackmenu, "2. ", "Transfer");
    push(&stackmenu, "3. ", "Penarikan Tunai");
    push(&stackmenu, "4. ", "Ganti PIN");
    push(&stackmenu, "0. ", "Keluar");

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\nPilihan : ");
}

/*
* function showWelcome berguna sebagai reuseable function yang menampilkan
* tampilan login agar dapat digunakan difunction lain
*/
void showWelcome() {
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+%10sSELAMAT DATANG DI ATM BCA-KW%-9s+\n", "", "");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\n%16sMasukkan PIN Anda :\n%-22s", "", "");
}

// * Function showSaldoUser merupakan reuseable function yang digunakan untuk menampilkan sisa saldo pengguna
void showSaldoUser(float saldo) {
    system("cls");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+%60s+\n+%21sSisa Saldo : Rp %8.f%-15s+\n+%-60s+\n", "", "", saldo, "", "");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
}

// * Function showTransferMenu berguna untuk menampilkan daftar transfer yang didukung oleh program ATM ini
void showTransferMenu() {
  system("cls");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+%22sMENU%-21s+\n", "", "");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+%17s1. Antar Bank%-17s+\n+%17s2. Antar Rekening%-13s+\n+%17s0. Keluar%-21s+\n", "", "", "", "", "", "");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\nPilihan : ");
}

/*
* Function showMenuPenarikanTunai berguna untuk menampilkan daftar nominal penarikan tunai
* yang disediakan secara default oleh program ATM ini.
*/
int showMenuPenarikanTunai() {
    Node *root = NULL;

    int saldoPenarikan[] = {250, 5, 50, 150, 10, 100};

    for(int i=0; i<6; i++) {
        root = insert(root, saldoPenarikan[i]);
    }

    system("cls");
    printf("++++++++++++++++++++++++++++++++++\n");
    printf("+     Pilih Jumlah Penarikan     +\n");
    printf("++++++++++++++++++++++++++++++++++\n");
    printInorder(root);
    printf("+%7s9) Transaksi lain%-8s+\n", "", "");
    printf("+%7s0) Exit%-18s+\n", "", "");
    printf("++++++++++++++++++++++++++++++++++");
    printf("\n\nPilihan : ");
    scanPenarikan();
}

