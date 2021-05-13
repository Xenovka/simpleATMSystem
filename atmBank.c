#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_LEN 100

typedef struct Menu{
    char angka[4];
    char fitur[30];

    struct Menu *next;
} Menu;
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

typedef struct Node {
  int key, height;
  struct Node *left, *right;
} Node;

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
char insertPin[7], insertUlangPin[7]; // digunakan untuk menampung PIN yang di insert oleh pengguna
int dataTotal = 0, index = 0, counter = 0, treeIndex = 0; // menyimpan iterasi untuk mencari index dari pengguna

int main() {
    head = tail = node = NULL;

    readData();
    sortingData();

    login(insertPin);

    return 0;
}

/*
* function sortingData ini digunakan untuk sort data yang ada di data.txt by name
* lalu di store ke file baru bernama sortedData. Function ini berjalan setiap program dijalankan
*/
int sortingData() {
    char strTempData[MAX_LEN]; // buat nampung data sementar
    char **strData = NULL; // masukin semua string yang dibaca
    int row = 0; // ini buat jumlah lines

    FILE *fpData = fopen("data.txt", "r");
    FILE *fpSorted = fopen("sortedData.txt", "w");

    while(fgets(strTempData, MAX_LEN, fpData) != NULL) {
        if(strchr(strTempData,'\n')) strTempData[strlen(strTempData)-1] = '\0';

        strData = (char**)realloc(strData, sizeof(char**)*(row+1));
        strData[row] = (char*)calloc(MAX_LEN,sizeof(char));
        strcpy(strData[row], strTempData);
        row++;
    }

    for(int i= 0; i < (row - 1); ++i) {
        for(int j = 0; j < ( row - i - 1); ++j) {
            if(strcmp(strData[j], strData[j+1]) > 0) {
                strcpy(strTempData, strData[j]);
                strcpy(strData[j], strData[j+1]);
                strcpy(strData[j+1], strTempData);
            }
        }
    }

    for(int i = 0; i < row; i++)
        fprintf(fpSorted,"%s\n",strData[i]);

    for(int i = 0; i < row; i++)
        free(strData[i]);

    free(strData);
    fclose(fpData);
    fclose(fpSorted);
}

void printSelamatDatang() {
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+%10sSELAMAT DATANG DI ATM BCA-KW%-9s+\n", "", "");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\n%16sMasukkan PIN Anda :\n%-22s", "", "");
}

/*
* function showMenu berfungsi untuk menampilkan tampilan awal program yang mana
* berisi daftar menu yang tersedia di program ATM inin
*/
void showMenu() {
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+%20sMENU%-23s+\n", "", "");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    Menu *stackmenu;
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
* function login berguna sesuai dengan nama function ini sendiri, yaitu meminta pengguna
* untuk login menggunakan PIN nya.
*/
int login(char userPin[]){

    printSelamatDatang();

    pinToAsterisk(userPin);
   
    checkPin(userPin);

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

    // 13 = ASCII untuk ENTER key
    while((ch = getch()) != 13){
        if(i < 0)
            i = 0;
        // 8 = ASCII untuk BACKSPACE key
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
* function checkPin berguna untuk membandingkan PIN yang diinput
* yang bertujuan untuk memastikan bahwa pengguna yang login benar-benar dari bank BCA-KW
*/
int checkPin(char pinToCheck[]) {
    int ctr = 3;

     // syntax do while dipakai untuk melakukan checking PIN yang diinsert oleh pengguna
    // Jika PIN yang dimasukkan oleh pengguna telah salah sebanyak 3x, pengguna akan terblokir dari ATM
    do{
        for(index = 0; index <= dataTotal - 1; index++) {
            if(strcmp(pengguna[index].userPIN, pinToCheck) == 0 && strcmp(pengguna[index].namaBank, "BCA") == 0) {
                menu();
                return 0;
            } else if (strcmp(insertPin, pinToCheck) == 0 && strcmp(pengguna[index].namaBank, "BCA") == 0) {
                menu();
                return 0;
            }
        }

        printf("\n   PIN Atau BANK Salah! Batas input tersisa %d kali\n", ctr);
        printf("\n%16sMasukkan PIN Anda : \n%-22s", "", "");

        pinToAsterisk(pinToCheck);
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

// function showTransferMenu berguna untuk menampilkan daftar transfer yang didukung oleh program ATM ini
int showTransferMenu() {
    int userInput;

    system("cls");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+%20sMENU%-23s+\n", "", "");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+%17s1. Antar Bank%-17s+\n+%17s2. Antar Rekening%-13s+\n+%17s0. Keluar%-21s+\n", "", "", "", "", "");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\nPilihan : ");
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

void showSaldoUser(float saldo) {
    system("cls");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+%60s+\n+%21sSisa Saldo : Rp %.f%-16s+\n+%-60s+\n", "", "", saldo, "", "");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
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


// Pengimplementasian AVL Tree
int height(struct Node *N){
  if(N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b){
  return (a > b) ? a : b;
}

Node *newNode(int item){
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->key = item;
  temp->left = temp->right = NULL;
  temp->height = 1;
  return temp;
}

Node *leftRotate(Node *x){
  Node *y = x->right;
  Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right))+1;
  y->height = max(height(y->left), height(y->right))+1;

  return y;
}

Node *rightRotate(Node *y){
  Node *x = y->left;
  Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right))+1;
  x->height = max(height(x->left), height(x->right))+1;

  return x;
}

int getBalance(Node *N){
  if(N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

Node *insert(Node *node, int key){
  if(node == NULL) return(newNode(key));

  if(key < node->key)
    node->left = insert(node->left, key);
  else if(key > node->key)
    node->right = insert(node->right, key);
  else
    return node;

  node->height = 1 + max(height(node->left),
                         height(node->right));

  int balance = getBalance(node);

  if(balance > 1 && key < node->left->key)
    return rightRotate(node);

  if(balance < -1 && key > node->right->key)
    return leftRotate(node);

  if(balance > 1 && key > node->left->key){
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if(balance < -1 && key < node->right->key){
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

void printInorder(Node *node){

  if(node == NULL) return;
  printInorder(node->left);
  treeIndex++;
  printf(">> %d) Rp. %d0.000,00 ", treeIndex, node->key);
  printf("\n");
  printInorder(node->right);
}
// Akhir dari pengimplementasian AVL Tree


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
            return;
        }
    }

    printf("Kode Bank yang Dimasukkan Salah!\n");
    goto label2;
}

/*
* function lanjutTransaksi berguna untuk menerima input nomor rekening yang dituju oleh pengguna
* dan menerima jumlah saldo yang ingin ditransfer.
*/
void lanjutTransaksi(inputKode){
    float saldoTransfer;
    char inputRek[11], userInput[2];
    int ctr = 0;

    FILE *fp = fopen("data.txt", "r");
    FILE *fp2 = fopen("rekeningData.txt", "r");

    printf("Masukkan Nomor Rekening Tujuan : ");
    scanf("%s", &inputRek); fflush(stdin);

    while(!feof(fp)) {
        fscanf(fp, "%[^#]#%[^#]#%[^#]#%[^#]#%f\n", &pengguna[ctr].nama, &pengguna[ctr].noRek, &pengguna[ctr].userPIN, &pengguna[ctr].namaBank, &pengguna[ctr].saldoUser);
        fscanf(fp2, "%[^#]#%[^\n]", rekeningData[ctr].noRek, &rekeningData[ctr].kode);


        if(strcmp(pengguna[ctr].noRek, inputRek) == 0 && strcmp(pengguna[ctr].namaBank, "BCA") != 0){
            if(strcmp(rekeningData[ctr].kode, inputKode) == 0){
                break;
            }else{
                printf("\nNomor Rekening yang Anda Tuju Tidak Terdaftar di Bank Tersebut!\n");
                return;
            }
        }
        ctr++;
    }

    if(strcmp(pengguna[ctr].noRek, inputRek) != 0){
        printf("Nomor Rekening yang Dimasukkan Salah!\n");
        return;
    }

    fclose(fp);

    printf("Masukkan Jumlah Uang yang Ingin Anda Transfer : ");
    scanf("%f", &saldoTransfer); fflush(stdin);

    if(saldoTransfer > pengguna[counter].saldoUser){
        printf("Saldo tidak mencukupi\n");
        return 0;
    }

    fp = fopen("data.txt", "r+");

    node = head;

    while(node != NULL){
        if(strcmp(node->nama, pengguna[ctr].nama) == 0) {
            node->saldoUser += saldoTransfer;
        }
        fprintf(fp, "%s#%s#%s#%s#%.f\n", node->nama, node->noRek, node->userPIN, node->namaBank, node->saldoUser);
        node = node->next;
    }

    fclose(fp);


    printf("Apakah Anda Yakin? [Y/N] : ");
    scanf("%s", &userInput); fflush(stdin);

    if(userInput[0] == 'Y' || userInput[0] == 'y') {
        outputPenarikan(saldoTransfer);
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
* function antarRekening berguna untuk melakukan transaksi transfer saldo kepada pengguna yang
* berasal dari bank BCA
*/
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

//function updateSaldo berguna untuk mengganti saldo sebelum transaksi dengan saldo setelah melakukan transaksi
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


//function menu berguna untuk menerima pilihan menu dari pengguna
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
        showTransferMenu();
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
