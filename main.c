#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int **malloc2d(int nr, int nc);
int *malloc1d(int size);
void print1d(int *array, int length);
void separa(int **matrice, int nr, int nc, int *arrayBianchi, int *arrayNeri, int sizeBianche, int sizeNeri);
void calculateSize(int nr, int nc, int *sizeBianche, int *sizeNeri);

int main( )
{
    int **matrice;

    FILE *fpR;
    if ((fpR = fopen("../mat.txt", "r")) == NULL) {
        printf("Error opening file\n");
        exit(-1);
    }
    int nr, nc;
    fscanf(fpR, "%d %d", &nr, &nc);

    matrice = malloc2d(nr, nc);



    for (int i = 0; i < nr; ++i) {
        for (int j = 0; j < nc; ++j) {
            fscanf(fpR, "%d", &matrice[i][j]);
//            matrice[i][j] = i + j;
        }
    }

    for (int i = 0; i < nr; ++i) {
        for (int j = 0; j < nc; ++j) {
            printf("%d", matrice[i][j]);
        }
        printf("\n");
    }


    int sizeBianche = 0, sizeNeri = 0;
    calculateSize(nr, nc, &sizeBianche, &sizeNeri);
    printf("\ntotal slots %d, N bianchi %d N neri %d", nc*nr, sizeBianche, sizeNeri);

    int *arrayBianchi = NULL, *arrayNeri = NULL; //malloc1d(sizeNeri);
    // malloc1d(sizeBianche)
    separa(matrice, nr, nc, arrayBianchi, arrayNeri, sizeBianche, sizeNeri);
    return 0;
}

void calculateSize(int nr, int nc, int *sizeBianche, int *sizeNeri) {
    int nRbianche = ceil((double )nr / 2);
    int nRnere = nr - nRbianche;

    int nCbianche = ceil((double) nr / 2);
    int nCnere = nc - nCbianche;

    *sizeBianche = nRbianche * nCbianche + nRnere * nCnere;
    *sizeNeri = nRnere * nCbianche + nRbianche * nCnere;
}

void separa(int **matrice, int nr, int nc, int *arrayBianchi, int *arrayNeri, int sizeBianche, int sizeNeri) {
    int indexWhite = 0, indexBlack = 0;
    arrayBianchi = malloc1d(sizeBianche);
    arrayNeri = malloc1d(sizeNeri);

    for (int i = 0; i < nr; ++i) {
        for (int j = 0; j < nc; ++j) {
            if(i % 2 == 0) {
                if(j % 2 == 0) {
                    // RIGHE BIANCHE COLONNE BIANCHE
                    *(arrayBianchi + indexWhite++) = matrice[i][j];
                } else {
                    // RIGHE BIANCHE COLONNE NERE
                    *(arrayNeri + indexBlack++) = matrice[i][j];
                }
            } else {
                if(j % 2 == 0) {
                    // RIGHE NERE COLONNE NERE
                    *(arrayNeri + indexBlack++) = matrice[i][j];
                } else {
                    *(arrayBianchi + indexWhite++) = matrice[i][j];
                    // RIGHE NERE COLONNE BIANCHE
                }
            }
        }
    }

    printf("\nARRAY BIANCHI\n");
    print1d(arrayBianchi, indexWhite);
    printf("\nARRAY NERI\n");
    print1d(arrayNeri, indexBlack);
}

void print1d(int *array, int length) {
    for(int i = 0; i < length; i++) {
        printf("%d\n", *(array + i));
    }
}

int *malloc1d(int size) {
    return malloc(sizeof(int) * size);
}

int **malloc2d(int nr, int nc) {
    int **m;

    m = malloc(nr * sizeof(int *));

    for (int i = 0; i < nr; ++i) {
        m[i] = malloc(nc * sizeof(int));
    }

    return m;
}
