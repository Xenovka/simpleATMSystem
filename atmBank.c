#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "./HeaderFile/GlobalVariableAndStruct.h"
#include "./HeaderFile/Stack.h"
#include "./HeaderFile/PrintFunction.h"
#include "./HeaderFile/Sorting.h"
#include "./HeaderFile/Reuseable.h"

int main() {
    head = tail = node = NULL;

    readData();
    sortingData();

    login(insertPin);

    return 0;
}

// * Function antarRekening berguna untuk melakukan transaksi transfer saldo kepada pengguna yang berasal dari bank BCA
void antarRekening(){

    char inputRek[20];

    FILE *fp = fopen("data.txt", "r");

    system("cls");
    printf("%10sMasukkan Nomor Rekening Tujuan :\n%21s", "", "");
    scanf("%s", &inputRek); fflush(stdin);

    while(!feof(fp)) {

        fscanf(fp, "%[^#]#%[^#]#%[^#]#%[^#]#%f\n", &pengguna[counter].nama, &pengguna[counter].noRek, &pengguna[counter].userPIN, &pengguna[counter].namaBank, &pengguna[counter].saldoUser);

        if(strcmp(pengguna[counter].noRek, inputRek) == 0 && strcmp(pengguna[counter].namaBank, "BCA") == 0){
            break;
        }

        counter++;

    }

    if(strcmp(pengguna[counter].noRek, inputRek) != 0 && strcmp(pengguna[counter].namaBank, "BCA") != 0){
        printf("Nomor Rekening yang Anda Masukkan Tidak Terdaftar!\n");
        return;
    }

    cekSaldo();

    fclose(fp);
}

/*
* Function antarBank berguna untuk menampilkan daftar bank yang dapat dituju dengan kode banknya.
* User menginput kode bank yang akan dituju.
*/
int antarBank(){
    int counter = 0;
    char inputKode[10];
    FILE *fp = fopen("kodeBank.txt", "r");

    while(!feof(fp)) {
        fscanf(fp, "%[^#]#%[^\n]\n", &kodeBank[counter].nama, &kodeBank[counter].kode);
        counter++;
    }

    fclose(fp);

    system("cls");
    printf("=======================================================\n");
    printf("%24sDAFTAR BANK\n", "");
    printf("=======================================================\n");
    printf("\n");
    for(int j=0;j<counter;j++){
        if(j % 2 == 0){
            printf(">> %-18s - %3s || ", kodeBank[j].nama, kodeBank[j].kode);
        } else {
            printf("%-3s - %15s <<\n", kodeBank[j].kode, kodeBank[j].nama);
        }
    }

    label2:
    printf("\nInput Kode Bank yang Ingin Dituju : ");
    scanf("%s", &inputKode); fflush(stdin);

    if(strcmp(inputKode, "014") == 0){
        printf("\nSilahkan Gunakan Transfer Antar Rekening.\n");
        return 0;
    }

    for(int j=0;j<counter;j++){
        if(strcmp(kodeBank[j].kode, inputKode) == 0){
            lanjutTransaksi(inputKode);
            return 0;
        }
    }

    printf("Kode Bank yang Dimasukkan Salah!\n");
    goto label2;
}

/*
* Function lanjutTransaksi berguna untuk menerima input nomor rekening yang dituju oleh pengguna
* dan menerima jumlah saldo yang ingin ditransfer.
*/
int lanjutTransaksi(char inputKode[]){

    char inputRek[11];
    int ctr = 0;

    FILE *fpData = fopen("data.txt", "r");
    FILE *fpRekeningData = fopen("rekeningData.txt", "r");

    system("cls");
    printf("%10sMasukkan Nomor Rekening Tujuan :\n%21s", "", "");
    scanf("%s", &inputRek); fflush(stdin);

    while(!feof(fpData)) {
        fscanf(fpData, "%[^#]#%[^#]#%[^#]#%[^#]#%f\n", &pengguna[counter].nama, &pengguna[counter].noRek, &pengguna[counter].userPIN, &pengguna[counter].namaBank, &pengguna[counter].saldoUser);
        fscanf(fpRekeningData, "%[^#]#%[^\n]", rekeningData[counter].noRek, &rekeningData[counter].kode);

        if(strcmp(pengguna[counter].noRek, inputRek) == 0 && strcmp(pengguna[counter].namaBank, "BCA") != 0){
            if(strcmp(rekeningData[counter].kode, inputKode) == 0){
                break;
            }
        }

        counter++;
    }

    if(strcmp(pengguna[counter].noRek, inputRek) != 0){
        printf("%7sNomor Rekening yang Dimasukkan Salah!\n", "");
        return 0;
    }

    cekSaldo();

    fclose(fpData);
}

// * Penerapan Linked List berdasarkan Struct data. Data dari Struct akan dimasukkan ke dalam Linked List.
void createNewNode(char nama[], char noRek[], char userPIN[], char namaBank[], float saldoUser) {
    node = (struct data*) malloc(sizeof(struct data));
    node->next = NULL;

    strcpy(node->nama, nama);
    strcpy(node->noRek, noRek);
    strcpy(node->userPIN, userPIN);
    strcpy(node->namaBank, namaBank);
    node->saldoUser = saldoUser;

    if(head == NULL){
        head = tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
}

/*
* Function gantiPin berguna untuk user yang ingin mengganti PIN miliknya dengan memasukkan PIN lama,
* setelah itu user akan diminta memasukkan PIN baru dan melakukan konfirmasi.
* Konfirmasi dilakukan dengan menginput PIN baru sekali lagi, lalu proses gantiPin selesai.
*/
int gantiPin() {
    char pinLama[7], pinBaru[7], konfirmasiPIN[7];

    system("cls");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    label3:
    printf("%17sMasukkan PIN Lama : \n%24s", "", "");
    pinToAsterisk(pinLama);

    FILE *fp = fopen("data.txt", "r+");

    if(strcmp(insertPin, pinLama) == 0){
        printf("\n%16s Masukkan PIN Baru : \n%24s", "", "");
        pinToAsterisk(pinBaru);

        if(strcmp(pinLama, pinBaru) == 0){
            printf("\n%5sPIN baru tidak boleh sama dengan PIN lama!\n\n",  "");
            goto label3;
        }

        printf("\n%16sKonfirmasi PIN Baru : \n%24s", "", "");
        pinToAsterisk(konfirmasiPIN);

        if(strcmp(pinBaru, konfirmasiPIN) == 0){
            node = head;
            while(node != NULL){
                if(strcmp(pengguna[index].nama, node->nama) == 0){
                    strcpy(node->userPIN, pinBaru);
                    strcpy(insertPin, pinBaru);
                }
                fprintf(fp, "%s#%s#%s#%s#%.f\n", node->nama, node->noRek, node->userPIN, node->namaBank, node->saldoUser);
                node = node->next;
            }

            printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("+%15sPIN Berhasil Diganti!%-14s+\n", "", "");
            printf("++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            return 0;

        } else {
            printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("+%17sPIN Tidak Cocok!%-17s+\n", "");
            printf("+%16sProses Dibatalkan!%-16s+", "", "");
            printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            return 0;
        }

    } else {
        printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("+%10sPin yang Anda Masukkan Salah!%-11s+", "","");
        printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        return 0;
    }

    fclose(fp);

}

// * Function readData berfungsi untuk membaca seluruh data yang ada di file "data.txt"
void readData() {
    FILE *fp = fopen("data.txt", "r");

    while(!feof(fp)) {
        fscanf(fp, "%[^#]#%[^#]#%[^#]#%[^#]#%f\n", &pengguna[dataTotal].nama, &pengguna[dataTotal].noRek, &pengguna[dataTotal].userPIN, &pengguna[dataTotal].namaBank, &pengguna[dataTotal].saldoUser);

        createNewNode(pengguna[dataTotal].nama, pengguna[dataTotal].noRek, pengguna[dataTotal].userPIN, pengguna[dataTotal].namaBank, pengguna[dataTotal].saldoUser);
        dataTotal++;
    }

    fclose(fp);
}

// * Function transferMenu berguna untuk menampilkan daftar transfer yang didukung oleh program ATM ini
int transferMenu() {
    int userInput;

    showTransferMenu();
    scanf("%d", &userInput); fflush(stdin);

    while(userInput != 1 && userInput != 2 && userInput != 0) {
        printf("Input Tidak Diketahui!\n\nPilih Menu : ");
        scanf("%d", &userInput); fflush(stdin);
    }

    switch(userInput){
        case 1:
            antarBank();
            break;
        case 2:
            antarRekening();
            break;
        case 0:
            return 0;
    }
}

/*
* Function login berguna sesuai dengan nama function ini sendiri, yaitu meminta pengguna
* untuk login menggunakan PIN-nya.
*/
int login(char userPin[]){
    char inputRek[20];
    int isValid = 0;

    showWelcome();

    scanf("%s", &inputRek); fflush(stdin);

    do {
        for(index = 0; index <= dataTotal - 1; index++) {
            if(strcmp(pengguna[index].noRek, inputRek) == 0 && strcmp(pengguna[index].namaBank, "BCA") == 0) {
                goto lanjut;
            } 
        } 

        isValid = 1;
        printf("\n%10sNomor Rekening Tidak Diketahui!\n", "");
        return 0;
    } while (isValid == 0);

    lanjut:
    printf("\n%16sMasukkan PIN Anda :\n%-22s", "", "");
    pinToAsterisk(userPin);

    int ctr = 3;

    // * Syntax do while dipakai untuk melakukan checking PIN yang diinsert oleh pengguna
    // * Jika PIN yang dimasukkan oleh pengguna telah salah sebanyak 3x, pengguna akan terblokir dari ATM
    do {
        // * Jika sebelumnya belum melakukan transaksi, maka akan masuk ke dalam function 'if'.
        if (!flag){
            for(index = 0; index <= dataTotal - 1; index++) {
                if(strcmp(pengguna[index].userPIN, userPin) == 0 && strcmp(pengguna[index].namaBank, "BCA") == 0 && strcmp(pengguna[index].noRek, inputRek) == 0) {
                    flag = 1;
                    menu();
                    return 0;
                }
            }
        }

        // * Jika sudah pernah melakukan transaksi dan akan melakukan transaksi lagi, maka akan masuk ke dalam fungsi 'else'.
        else {
            if(strcmp(insertPin, userPin) == 0){
                menu();
                return 0;
            }
        }

        printf("\n   PIN Atau BANK Salah! Batas input tersisa %d kali\n", ctr);
        printf("\n%16sMasukkan PIN Anda : \n%-22s", "", "");

        pinToAsterisk(userPin);
        ctr--;

    } while(ctr > 0);

    while(ctr = 3) {
        system("cls");
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("+%20sMaaf Kartu Anda Kami Blokir!%-17s+\n", "", "");
        printf("+%3sHarap Hubungi Kantor BCA Terdekat Untuk Membuka Blokir Ini!%-3s+\n", "", "");
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        return 0;
    }

    return 0;
}

/*
* Function transaksiLain berguna untuk user yang ingin melakukan penarikan tunai,
* tetapi nominal yang diinginkan tidak ada di menu. User dapat menginput nominal transfer yang diinginkan secara manual.
*/
void transaksiLain() {
    float inputPenarikan;

    system("cls");
    printf("%12sMasukkan Nominal Penarikan : \n%20s", "", "");
    scanf("%f", &inputPenarikan); fflush(stdin);

    outputPenarikan(inputPenarikan);
    printf("\n");

}

// * function scanPenarikan berguna untuk melakukan update setelah pengguna melakukan penarikan tunai sesuai dengan pilihan
void scanPenarikan(){
    int userInput;
    scanf("%d", &userInput);
    fflush(stdin);

    switch(userInput){
    case 1:
        outputPenarikan(50000);
        break;
    case 2:
        outputPenarikan(100000);
        break;
    case 3:
        outputPenarikan(500000);
        break;
    case 4:
        outputPenarikan(1000000);
        break;
    case 5:
        outputPenarikan(1500000);
        break;
    case 6:
        outputPenarikan(2500000);
        break;
    case 9:
        transaksiLain();
        break;
    case 0:
        return 0;
    }
}

// * Function menu berguna untuk menerima pilihan menu dari pengguna
int menu() {
    int userInput;

    system("cls");
    showMenu();
    scanf("%d", &userInput); fflush(stdin);

    while(userInput != 1 && userInput != 2 && userInput != 3 && userInput != 4 && userInput != 0) {
        printf("Input Tidak Diketahui!\n\nPilih Menu : ");
        scanf("%d", &userInput); fflush(stdin);
    }

    switch(userInput){
    case 1:
        showSaldoUser(pengguna[index].saldoUser);
        transaksiLagi();
        break;
    case 2:
        transferMenu();
        break;
    case 3:
        showMenuPenarikanTunai();
        break;
    case 4:
        gantiPin();
        break;
    case 0:
        return 0;
    }
}

