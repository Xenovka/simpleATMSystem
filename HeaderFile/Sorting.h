#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX_LEN 100

/*
* function sortingData ini digunakan untuk sort data yang ada di data.txt by name
* lalu di store ke file baru bernama sortedData. Function ini berjalan setiap program dijalankan
*/
int sortingData() {
    char strTempData[MAX_LEN]; // * buat nampung data sementara
    char **strData = NULL; // * masukin semua string yang dibaca
    int row = 0; // * ini buat jumlah lines

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