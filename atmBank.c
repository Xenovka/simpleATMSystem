#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "./HeaderFile/PrintFunction.h"
#include "./HeaderFile/Sorting.h"
#include "./HeaderFile/AVLTree.h"

/*
* Struct data berfungsi untuk menyimpan data semua user yang dapat melakukan transaksi yang
* sudah kami siapkan di file txt yang bernama data.txt
*/
struct data {
    char userPIN[7], nama[250], noRek[20], namaBank[100];
    float saldoUser;
    struct data *next;
} pengguna[255], sort[255], *head, *tail, *node;

/*
* Struct dataBank berfungsi menyimpan daftar nama bank beserta dengan kode bank
* yang dapat melakukan transaksi pada program ATM bank kami
*/
struct dataBank {
    char nama[100], kode[10];
} kodeBank[50];

typedef struct Menu{
    char angka[4];
    char fitur[30];

    struct Menu *next;
} Menu;

int isEmpty(Menu *stack){
    if(stack == NULL)
        return 1;
    return 0;
}


void push(Menu **stack, char angka[], char fitur[]){
    Menu *data = (Menu*) malloc(sizeof(Menu));
    strcpy(data->angka, angka);
    strcpy(data->fitur, fitur);
    data->next = NULL;

    if(!isEmpty(*stack)) data->next = *stack;
    *stack = data;
    printf("+%20s%-27s+\n", angka, fitur);
}

/*
* Struct rekeningData berfungsi untuk menyimpan data nomor rekening pengguna
* beserta kode bank yang akan kami gunakan pada saat transaksi nantinya
*/
struct rekeningData{
    char noRek[20], kode[10];
}rekeningData[50];

//GLOBAL VARIABLE
char insertPin[7], insertUlangPin[7]; // * digunakan untuk menampung PIN yang di insert oleh pengguna
int dataTotal = 0, index = 0, counter = 0;// * menyimpan iterasi untuk mencari index dari pengguna

int main() {
    head = tail = node = NULL;

    readData();
    sortingData();

    login(insertPin);

    return 0;
}

/*
* function login berguna sesuai dengan nama function ini sendiri, yaitu meminta pengguna
* untuk login menggunakan PIN nya.
*/
int login(char userPin[]){

    showWelcome();

    pinToAsterisk(userPin);

    int ctr = 3;

    // ! BLOM FIX
    // * syntax do while dipakai untuk melakukan checking PIN yang diinsert oleh pengguna
    // * Jika PIN yang dimasukkan oleh pengguna telah salah sebanyak 3x, pengguna akan terblokir dari ATM
    do{
        for(index = 0; index <= dataTotal - 1; index++) {
            if(strcmp(pengguna[index].userPIN, userPin) == 0 && strcmp(pengguna[index].namaBank, "BCA") == 0) {
                menu();
                return 0;
            }
        }

        printf("\n   PIN Atau BANK Salah! Batas input tersisa %d kali\n", ctr);
        printf("\n%16sMasukkan PIN Anda : \n%-22s", "", "");

        pinToAsterisk(userPin);
        ctr--;

        if(ctr == 0) {
            system("cls");
            printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("+%20sMaaf Kartu Anda Kami Blokir!%-17s+\n", "", "");
            printf("+%3sHarap Hubungi Kantor BCA Terdekat Untuk Membuka Blokir Ini!%-3s+\n", "", "");
            printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            return 0;
        }
    }while(ctr >= 0);

    return 0;
}


// Penerapan Linked List berdasarkan Struct data yang mana akan memasukkan data ke struct tersebut
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
    }else {
        tail->next = node;
        tail = node;
    }
}

// function readData berfungsi untuk membaca seluruh data yang ada di file data.txt
void readData() {
    FILE *fp = fopen("data.txt", "r");

    while(!feof(fp)) {
        fscanf(fp, "%[^#]#%[^#]#%[^#]#%[^#]#%f\n", &pengguna[dataTotal].nama, &pengguna[dataTotal].noRek, &pengguna[dataTotal].userPIN, &pengguna[dataTotal].namaBank, &pengguna[dataTotal].saldoUser);

        createNewNode(pengguna[dataTotal].nama, pengguna[dataTotal].noRek, pengguna[dataTotal].userPIN, pengguna[dataTotal].namaBank, pengguna[dataTotal].saldoUser);
        dataTotal++;
    }

    fclose(fp);
}

/*
* function ini berfungsi sesuai dengan penamaannya, yaitu untuk mengubah PIN yang
* di input oleh user menjadi bintang/ asterisk (*) seperti layaknya di ATM pada umumnya
*/
void pinToAsterisk(char pin[]) {
    char ch;
    int i = 0;

    // * 13 = ASCII untuk ENTER key
    while((ch = getch()) != 13){
        if(i < 0)
            i = 0;
        // * 8 = ASCII untuk BACKSPACE key
        if(ch == 8){
            printf("%c%c%c", '\b', 32, '\b');
            i--;
            continue;
        }

        pin[i++] = ch;
        putch('*');
    }

    pin[i] = '\0';
}

/*
* function transaksiLagi berguna untuk memastikan apakah user ingin melakukan transaksi lagi
* setelah melakukan sebuah transaksi dengan menerima input dari user berupa Y/y atau N/n
*/
int transaksiLagi() {
    char userInput[2];

    printf("Transaksi Lagi ? [Y/N]\n");
    label:
    printf("Pilihan : ");
    scanf("%c", &userInput); fflush(stdin);

    if(userInput[0] == 'Y' || userInput[0] == 'y') {
        system("cls");
        login(insertUlangPin);
    } else if (userInput[0] == 'N' || userInput[0] == 'n') {
        return 0;
    } else {
        while(userInput[0] != 'N' || userInput[0] != 'n' || userInput[0] != 'Y' || userInput[0] != 'y') {
            printf("Input Tidak Diketahui!\n");
            goto label;
        }
    }
}

// * function showTransferMenu berguna untuk menampilkan daftar transfer yang didukung oleh program ATM ini
int transferMenu() {
    int userInput;

    showTransferMenu();
    scanf("%d", &userInput); fflush(stdin);

    while(userInput != 1 && userInput != 2 && userInput != 0) {
        printf("Input Tidak Diketahui!\nPilih Menu : ");
        scanf("%d", &userInput); fflush(stdin);
    }

    switch(userInput) {
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
* function gantiPin berguna untuk user yang ingin mengganti PIN miliknya dengan memasukkan PIN lama
* setelah itu user akan diminta memasukkan PIN baru yang ingin dibuat dan melakukan konfirmasi
* konfirmasi dilakukan dengan menginput PIN baru sekali lagi
* setelah itu proses gantiPin selesai
*/
int gantiPin() {
    char pinLama[7], pinBaru[7], konfirmasiPIN[7];

    system("cls");
    printf("%17sMasukkan PIN Lama : \n%24s", "", "");
    pinToAsterisk(pinLama);

    FILE *fp = fopen("data.txt", "r+");

    if(strcmp(insertPin, pinLama) == 0){

        printf("\n%16s Masukkan PIN Baru : \n%24s", "", "");
        pinToAsterisk(pinBaru);

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

            printf("\n%16sPIN Berhasil Diganti!\n\n", "");
            return 0;

        } else {
            printf("\n\n%18sPIN Tidak Cocok!", "");
            printf("\n%17sProses Dibatalkan!\n", "");
            return 0;
        }

    } else {
        printf("\n\n%11sPin yang Anda Masukkan Salah!\n", "");
        return 0;
    }

    fclose(fp);

}

/*
* function outputPenarikan berguna untuk mengurangi saldo pengguna sesuai dengan jumlah saldo yang
* dipilih oleh pengguna, setelah itu menampilkan sisa saldo yang dimiliki pengguna
*/
void outputPenarikan(float jumlah) {
    FILE *fp = fopen("data.txt", "r+");

    node = head;

    while(node != NULL){
        if(strcmp(node->nama, pengguna[index].nama) == 0) {
            node->saldoUser -= jumlah;
            showSaldoUser(node->saldoUser);
        }
        fprintf(fp, "%s#%s#%s#%s#%.f\n", node->nama, node->noRek, node->userPIN, node->namaBank, node->saldoUser);
        node = node->next;
    }

    fclose(fp);
}

/*
* function transaksiLain berguna untuk user yang ingin melakukan transaksi,
* tetapi nomimal transfer yang diinginkan tidak terdapat di menu, sehingga user dapat menginput
* nominal transfer yang diinginkan secara manual
*/
void transaksiLain() {
    int inputPenarikan;

    system("cls");
    printf("Masukkan Nominal Penarikan : ");
    scanf("%d", &inputPenarikan); fflush(stdin);

    outputPenarikan(inputPenarikan);
    printf("\n");
    transaksiLagi();
}

/*
* function showMenuPenarikanTunai berguna untuk menampilkan daftar nominal penarikan tunai
* yang disediakan secara default oleh program ATM ini
*/
int showMenuPenarikanTunai() {
    int userInput;

    Node *root = NULL;

    int saldoPenarikan[] = {250, 5, 50, 150, 10, 100};

    for(int i=0; i<6; i++) {
        root = insert(root, saldoPenarikan[i]);
    }

    system("cls");
    printf("++++++++++++++++++++++++++++++++++\n");
    printf("+     Pilih Jumlah Penarikan     +\n");
    printf("++++++++++++++++++++++++++++++++++\n\n");
    printInorder(root);
    printf(">> 9) Transaksi lain\n");
    printf(">> 0) Exit\n");
    printf("\n+++++++++++++++++++++++++++++++++");
    printf("\n\nPilihan : "); scanf("%d", &userInput); fflush(stdin);

    switch(userInput){
    case 1:
        outputPenarikan(50000);
        transaksiLagi();
        break;
    case 2:
        outputPenarikan(100000);
        transaksiLagi();
        break;
    case 3:
        outputPenarikan(500000);
        transaksiLagi();
        break;
    case 4:
        outputPenarikan(1000000);
        transaksiLagi();
        break;
    case 5:
        outputPenarikan(1500000);
        transaksiLagi();
        break;
    case 6:
        outputPenarikan(2500000);
        transaksiLagi();
        break;
    case 9:
        transaksiLain();
        break;
    case 0:
        return 0;
    }
}

void confirmation(float Jumlahsaldo) {
    char userInput[2];

    printf("Apakah Anda Yakin? [Y/N] : ");
    scanf("%s", &userInput); fflush(stdin);

    if(userInput[0] == 'Y' || userInput[0] == 'y') {
        outputPenarikan(Jumlahsaldo);
        printf("\nTransaksi Berhasil!");
        getch();
    } else if (userInput[0] == 'N' || userInput[0] == 'n') {
        return;
    } else {
        while(userInput[0] != 'N' || userInput[0] != 'n' || userInput[0] != 'Y' || userInput[0] != 'y') {
            printf("Input Tidak Diketahui!\n");
        }
    }
}

/*
* function antarBank berguna untuk menampilkan daftar bank yang dapat dituju
* dan menerima input kodeBank
*/
int antarBank(){
    int counter = 0;
    char inputKode[10], inputRekening[15];
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
        printf("Silahkan Gunakan Transfer Antar Rekening.\n");
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
* function lanjutTransaksi berguna untuk menerima input nomor rekening yang dituju oleh pengguna
* dan menerima jumlah saldo yang ingin ditransfer.
*/
int lanjutTransaksi(char inputKode[]){
    float saldoTransfer;
    char inputRek[11];
    int ctr = 0;

    FILE *fpData = fopen("data.txt", "r");
    FILE *fpRekeningData = fopen("rekeningData.txt", "r");

    printf("Masukkan Nomor Rekening Tujuan : ");
    scanf("%s", &inputRek); fflush(stdin);

    while(!feof(fpData)) {
        fscanf(fpData, "%[^#]#%[^#]#%[^#]#%[^#]#%f\n", &pengguna[ctr].nama, &pengguna[ctr].noRek, &pengguna[ctr].userPIN, &pengguna[ctr].namaBank, &pengguna[ctr].saldoUser);
        fscanf(fpRekeningData, "%[^#]#%[^\n]", rekeningData[ctr].noRek, &rekeningData[ctr].kode);


        if(strcmp(pengguna[ctr].noRek, inputRek) == 0 && strcmp(pengguna[ctr].namaBank, "BCA") != 0){
            if(strcmp(rekeningData[ctr].kode, inputKode) == 0){
                break;
            }else{
                printf("\nNomor Rekening yang Anda Tuju Tidak Terdaftar di Bank Tersebut!\n");
                return 0;
            }
        }
        ctr++;
    }

    if(strcmp(pengguna[ctr].noRek, inputRek) != 0){
        printf("Nomor Rekening yang Dimasukkan Salah!\n");
        return 0;
    }

    fclose(fpData);

    printf("Masukkan Jumlah Uang yang Ingin Anda Transfer : ");
    scanf("%f", &saldoTransfer); fflush(stdin);

    if(saldoTransfer > pengguna[counter].saldoUser){
        printf("Saldo tidak mencukupi\n");
        return 0;
    }

    updateSaldo(saldoTransfer);

    confirmation(saldoTransfer);
}

/*
* function antarRekening berguna untuk melakukan transaksi transfer saldo kepada pengguna yang
* berasal dari bank BCA
*/
void antarRekening(){
    float saldoTransfer;
    char inputRek[20];

    FILE *fp = fopen("data.txt", "r");

    printf("Masukkan Nomor Rekening Tujuan : ");
    scanf("%s", &inputRek); fflush(stdin);

    while(!feof(fp)) {

        fscanf(fp, "%[^#]#%[^#]#%[^#]#%[^#]#%f\n", &pengguna[counter].nama, &pengguna[counter].noRek, &pengguna[counter].userPIN, &pengguna[counter].namaBank, &pengguna[counter].saldoUser);

        if(strcmp(pengguna[counter].noRek, inputRek) == 0 && strcmp(pengguna[counter].namaBank, "BCA") == 0){
            break;
        }

        counter++;

    }

    fclose(fp);

    if(strcmp(pengguna[counter].noRek, inputRek) != 0 && strcmp(pengguna[counter].namaBank, "BCA") != 0){
        printf("Nomor Rekening yang Anda Masukkan Tidak Terdaftar!\n");
        return;
    }

    printf("Masukkan Jumlah Uang yang Ingin Anda Transfer : ");
    scanf("%f", &saldoTransfer); fflush(stdin);

    confirmation(saldoTransfer);

}

// * function updateSaldo berguna untuk mengganti saldo sebelum transaksi dengan saldo setelah melakukan transaksi
void updateSaldo(float jumlah) {
    FILE *fp = fopen("data.txt", "r+");

    node = head;

    while(node != NULL){
        if(strcmp(node->nama, pengguna[counter].nama) == 0) {
            node->saldoUser += jumlah;
        }
        fprintf(fp, "%s#%s#%s#%s#%.f\n", node->nama, node->noRek, node->userPIN, node->namaBank, node->saldoUser);
        node = node->next;
    }

    fclose(fp);
}


// * function menu berguna untuk menerima pilihan menu dari pengguna
int menu() {
    int userInput;

    system("cls");
    showMenu();
    scanf("%d", &userInput); fflush(stdin);

    while(userInput != 1 && userInput != 2 && userInput != 3 && userInput != 4 && userInput != 0) {
        printf("Input Tidak Diketahui!\nPilih Menu : ");
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
