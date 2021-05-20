//#include "GlobalVariableAndStruct.h"

/*
* Function ini berfungsi sesuai dengan penamaannya, yaitu untuk mengubah PIN yang
* diinput oleh user menjadi bintang/asterisk (*) seperti layaknya di ATM pada umumnya.
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
* Function transaksiLagi berguna untuk memastikan apakah user ingin melakukan transaksi lagi
* setelah melakukan sebuah transaksi dengan menerima input dari user berupa 'Y/y' atau 'N/n'.
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
        if(userInput[0] != 'N' || userInput[0] != 'n' || userInput[0] != 'Y' || userInput[0] != 'y') {
            printf("Input Tidak Diketahui!\n\n");
            goto label;
        }
    }
}

/*
* Function outputPenarikan berguna untuk mengurangi saldo pengguna sesuai dengan jumlah saldo yang
* dipilih oleh pengguna, setelah itu menampilkan sisa saldo yang dimiliki pengguna.
*/
void outputPenarikan(float jumlah) {
    
    FILE *fp = fopen("data.txt", "r+");

    node = head;

    while(node != NULL){
        if(jumlah > pengguna[index].saldoUser){
            printf("++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("+%8sMaaf, Saldo Anda Tidak Mencukupi!%-9s+\n", "", "");
            printf("++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            return 0;
        }

        if(strcmp(node->nama, pengguna[index].nama) == 0) {
            node->saldoUser -= jumlah;
            showSaldoUser(node->saldoUser);
        }
        fprintf(fp, "%s#%s#%s#%s#%.f\n", node->nama, node->noRek, node->userPIN, node->namaBank, node->saldoUser);
        node = node->next;
    }

    fclose(fp);
}

// Function updateSaldo berguna untuk mengganti saldo sebelum transaksi dengan saldo setelah melakukan transaksi
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

// Function confirmation berguna untuk mengkonfirmasi kembali jumlah saldo yang ingin ditransfer
void confirmation(float Jumlahsaldo) {
    char userInput[2];

    printf("%11sApakah Anda Yakin? [Y/N] : ", "");
    scanf("%s", &userInput); fflush(stdin);

    if(userInput[0] == 'Y' || userInput[0] == 'y') {
        outputPenarikan(Jumlahsaldo);
        printf("\nTransaksi Berhasil!");
        getch();
    } else if (userInput[0] == 'N' || userInput[0] == 'n') {
        return;
    } else {
        while(userInput[0] != 'N' || userInput[0] != 'n' || userInput[0] != 'Y' || userInput[0] != 'y') {
            printf("Input Tidak Diketahui!\n\n");
        }
    }
}

void cekSaldo(){
    float saldoTransfer;
    printf("%3sMasukkan Jumlah Uang yang Ingin Anda Transfer :\n%22s", "", "");
    scanf("%f", &saldoTransfer); fflush(stdin);

    if(saldoTransfer > pengguna[index].saldoUser){
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("+%8sMaaf, Saldo Anda Tidak Mencukupi!%-9s+\n", "");
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        return 0;
    }

    confirmation(saldoTransfer);

    updateSaldo(saldoTransfer);
}

