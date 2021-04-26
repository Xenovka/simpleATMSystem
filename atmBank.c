#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//Struct
struct data {
    char userPIN[7], nama[250], noRek[20], namaBank[100];
    float saldoUser;
    struct data *next;
} pengguna[255], *head, *tail, *node;

struct dataBank {
    char nama[100], kode[10];
} kodeBank[50];

//GLOBAL VARIABLE
char insertPin[7];
int dataTotal = 0, index = 0, counter = 0;

//Functions
void showMenu();
int menuLagi();
void readData();
void pinToAsterisk(char pin[]);
int checkPin();
int transaksiLagi();
int transfer();
int gantiPin();
void outputPenarikan(float jumlah);
void transaksiLain();
int penarikanTunai();
void antarBank();
void lanjutTransaksi();
void antarRekening();
void updateSaldo(float jumlah);
int menu();

int main() {
    head = tail = node = NULL;

    readData();

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+\t   SELAMAT DATANG DI ATM BCA-KW     \t+\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\n\t\tMasukkan PIN Anda :\n\t\t       ");

    pinToAsterisk(insertPin);

    checkPin();

    return 0;
}

void showMenu() {
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+\t               MENU               \t+\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+\t\t  1. Info Saldo\t\t\t+\n+\t\t  2. Transfer\t\t\t+\n+\t\t  3. Penarikan Tunai\t\t+\n+\t\t  4. Ganti PIN\t\t\t+\n+\t\t  0. Keluar\t\t\t+\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\n\nPilihan : ");
}

int menuLagi(){
    char insertUlangPIN[7];

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+\t   SELAMAT DATANG DI ATM BCA-KW     \t+\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\n\t\tMasukkan PIN Anda :\n\t\t       ");

    pinToAsterisk(insertUlangPIN);

    int ctr = 3;

    do{
        for(int j= 0; j < 3; j++) {
            if(strcmp(insertUlangPIN, insertPin) == 0) {
                menu();
                exit(0);
            }
        }
        printf("\n   PIN Atau BANK Salah! Batas input tersisa %d kali\n", ctr);
        printf("\t\tMasukkan PIN Anda : ");

        pinToAsterisk(insertUlangPIN);
        ctr--;
        if(ctr == 0) {
            system("cls");
            puts("||                  Maaf Kartu Anda Kami Blokir!               ||");
            puts("|| Harap Hubungi Kantor BCA Terdekat Untuk Membuka Blokir Ini! ||");
            return 0;
        }
    }while(ctr >= 0);


    return 0;
}
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


void readData() {
    FILE *fp = fopen("data.txt", "r");

    while(!feof(fp)) {
        fscanf(fp, "%[^#]#%[^#]#%[^#]#%[^#]#%f\n", &pengguna[dataTotal].nama, &pengguna[dataTotal].noRek, &pengguna[dataTotal].userPIN, &pengguna[dataTotal].namaBank, &pengguna[dataTotal].saldoUser);
        createNewNode(pengguna[dataTotal].nama, pengguna[dataTotal].noRek, pengguna[dataTotal].userPIN, pengguna[dataTotal].namaBank, pengguna[dataTotal].saldoUser);
        dataTotal++;
    }
    fclose(fp);
}

void pinToAsterisk(char pin[]) {
    char ch;
    int i = 0;

    /* 13 adalah nilai ASCII untuk ENTER */
    while((ch = getch()) != 13){
        if(i < 0)
            i = 0;
        /* 8 adalah nilai ASCII untuk BACKSPACE */
        if(ch == 8){
            putch('\b');
            putch(NULL);
            putch('\b');
            i--;
            continue;
        }

        pin[i++] = ch;
        putch('*');
    }

    pin[i] = '\0';
}

int checkPin() {
    int ctr = 3;

    do{
        for(index = 0; index <= dataTotal - 1; index++) {
            if(strcmp(pengguna[index].userPIN, insertPin) == 0 && strcmp(pengguna[index].namaBank, "BCA") == 0) {
                menu();
                return 0;
            }
        }

        printf("\n   PIN Atau BANK Salah! Batas input tersisa %d kali\n", ctr);
        printf("\t\tMasukkan PIN Anda : ");

        pinToAsterisk(insertPin);
        ctr--;

        if(ctr == 0) {
            system("cls");
            puts("||                  Maaf Kartu Anda Kami Blokir!               ||");
            puts("|| Harap Hubungi Kantor BCA Terdekat Untuk Membuka Blokir Ini! ||");
            return 0;
        }
    }while(ctr >= 0);

}

int transaksiLagi() {
    char userInput[2];

    printf("Transaksi Lagi ? [Y/N]\n");
    label:
    printf("Pilihan : ");
    scanf("%c", &userInput); fflush(stdin);

    if(userInput[0] == 'Y' || userInput[0] == 'y') {
        system("cls");
        menuLagi();
    } else if (userInput[0] == 'N' || userInput[0] == 'n') {
        return 0;
    } else {
        while(userInput[0] != 'N' || userInput[0] != 'n' || userInput[0] != 'Y' || userInput[0] != 'y') {
            printf("Input Tidak Diketahui!\n");
            goto label;
        }
    }
}

int transfer() {
    int userInput;

    system("cls");

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+\t               MENU               \t+\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+\t\t 1. Antar Bank \t\t\t+\n+\t\t 2. Antar Rekening \t\t+\n+\t\t 0. Keluar \t\t\t+\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\n\nPilihan : ");
    scanf("%d", &userInput);

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

int gantiPin() {
    char pinLama[7], pinBaru[7], konfirmasiPIN[7];

    printf("%s\n", insertPin);
    printf("Masukkan PIN Lama : ");
    pinToAsterisk(pinLama);

    FILE *fp = fopen("data.txt", "r+");

    if(strcmp(insertPin, pinLama) == 0){

        printf("\nMasukkan PIN Baru : ");
        pinToAsterisk(pinBaru);

        printf("\nKonfirmasi PIN Baru : ");
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

            printf("\nPIN Berhasil Diganti!\n\n");
            transaksiLagi();

        } else {
            printf("\n\nPIN Tidak Cocok!");
            printf("\nProses Dibatalkan!\n");
            return 0;
        }

    } else {
        printf("\n\nPin yang Anda Masukkan Salah!\n");
        return 0;
    }

    fclose(fp);

}

void outputPenarikan(float jumlah) {
    FILE *fp = fopen("data.txt", "r+");

    node = head;

    while(node != NULL){
        if(strcmp(node->nama, pengguna[index].nama) == 0) {
            node->saldoUser -= jumlah;
            system("cls");
            printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("+\t\t\t\t\t\t\t     +\n+\t\t     Sisa Saldo : %.2f    \t     +\n+\t\t\t\t\t\t\t     +\n", node->saldoUser);
            printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        }
        fprintf(fp, "%s#%s#%s#%s#%.f\n", node->nama, node->noRek, node->userPIN, node->namaBank, node->saldoUser);
        node = node->next;
    }
}

void transaksiLain() {
    int inputPenarikan;

    system("cls");
    printf("Masukkan Nominal Penarikan : ");
    scanf("%d", &inputPenarikan); fflush(stdin);

    outputPenarikan(inputPenarikan);
    printf("\n");
    transaksiLagi();
}

int penarikanTunai() {
    int userInput;

    system("cls");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+  1 >> Rp 50.000,00\t\t\t\t\t Rp 1.000.000,00 << 4\t+\n");
    printf("+  2 >> Rp 100.000,00\t\t\t\t\t Rp 1.500.000,00 << 5\t+\n");
    printf("+  3 >> Rp 500.000,00\t\t\t\t\t Rp 2.500.000,00 << 6\t+\n");
    printf("+  9 >> Transaksi Lain\t\t\t\t\t\tKeluar   << 0\t+\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\nPilihan : ");
    scanf("%d", &userInput); fflush(stdin);

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

void antarBank(){
    int counter = 0;
    char inputKode[10], inputRekening[15];
    FILE *fp = fopen("kodeBank.txt", "r");

    while(!feof(fp)) {
        fscanf(fp, "%[^#]#%[^\n]\n", &kodeBank[counter].nama, &kodeBank[counter].kode);
        counter++;
    }

    fclose(fp);

    system("cls");
    printf("========================================================================\n");
    printf("\t\t             DAFTAR BANK           \n");
    printf("========================================================================\n");
    printf("\n");
    for(int j=0;j<counter;j++){
        if(j % 2 == 0){
            printf(">>%-27s - %s   || ", kodeBank[j].nama, kodeBank[j].kode);
        } else {
            printf("   %s - %20s<<\n", kodeBank[j].kode, kodeBank[j].nama);
        }
    }

    label2:
    printf("\nInput Kode Bank yang Ingin Dituju : ");
    scanf("%s", &inputKode); fflush(stdin);

    for(int j=0;j<counter;j++){
        if(strcmp(kodeBank[j].kode, inputKode) == 0){
            lanjutTransaksi();
            return;
        }
    }

    printf("Kode Bank yang Dimasukkan Salah!\n");
    goto label2;
}

void lanjutTransaksi(){
    float saldoTransfer;
    char inputRek[20], userInput[2];
    int counter = 0, ctr = 0;

    FILE *fp = fopen("data.txt", "r");
    FILE *fp2 = fopen("rekeningData.txt", "r");

    printf("Masukkan Nomor Rekening Tujuan : ");
    scanf("%s", &inputRek); fflush(stdin);

    while(!feof(fp)) {
        fscanf(fp, "%[^#]#%[^#]#%[^#]#%[^#]#%f\n", &pengguna[counter].nama, &pengguna[counter].noRek, &pengguna[counter].userPIN, &pengguna[counter].namaBank, &pengguna[counter].saldoUser);

        if(strcmp(pengguna[counter].noRek, inputRek) == 0 && strcmp(pengguna[counter].namaBank, 'BCA') != 0){
            break;
        }

        counter++;
    }

    fclose(fp);

    printf("Masukkan Jumlah Uang yang Ingin Anda Transfer : ");
    scanf("%f", &saldoTransfer); fflush(stdin);
    printf("Apakah Anda Yakin? [Y/N] : ");
    scanf("%s", &userInput); fflush(stdin);

    if(userInput[0] == 'Y' || userInput[0] == 'y') {
        outputPenarikan(saldoTransfer);
        updateSaldo(saldoTransfer);
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

void antarRekening(){
    float saldoTransfer;
    char inputRek[20], userInput[2];

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
    printf("Apakah Anda Yakin? [Y/N] : ");
    scanf("%s", &userInput); fflush(stdin);

    if(userInput[0] == 'Y' || userInput[0] == 'y') {
        outputPenarikan(saldoTransfer);
        updateSaldo(saldoTransfer);
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
}

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
        printf("Saldo Rekening Anda : Rp %.2f\n", pengguna[index].saldoUser);
        transaksiLagi();
        break;
    case 2:
        transfer();
        break;
    case 3:
        penarikanTunai();
        break;
    case 4:
        gantiPin();
        break;
    case 0:
        return (0);
    }
}
