// Dafin Surya
// 23343032

#include <stdio.h>
#include <stdlib.h>

// Fungsi untuk menambahkan dua matriks
void tambah(int n, int **A, int **B, int **C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Fungsi untuk mengurangkan dua matriks
void kurang(int n, int **A, int **B, int **C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Fungsi untuk mengalikan dua matriks menggunakan algoritma Strassen
void strassen(int n, int **A, int **B, int **C) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    int n_baru = n / 2;

    // Alokasi memori untuk submatriks
    int **A11 = (int **)malloc(n_baru * sizeof(int *));
    int **A12 = (int **)malloc(n_baru * sizeof(int *));
    int **A21 = (int **)malloc(n_baru * sizeof(int *));
    int **A22 = (int **)malloc(n_baru * sizeof(int *));

    int **B11 = (int **)malloc(n_baru * sizeof(int *));
    int **B12 = (int **)malloc(n_baru * sizeof(int *));
    int **B21 = (int **)malloc(n_baru * sizeof(int *));
    int **B22 = (int **)malloc(n_baru * sizeof(int *));

    int **C11 = (int **)malloc(n_baru * sizeof(int *));
    int **C12 = (int **)malloc(n_baru * sizeof(int *));
    int **C21 = (int **)malloc(n_baru * sizeof(int *));
    int **C22 = (int **)malloc(n_baru * sizeof(int *));

    int **P1 = (int **)malloc(n_baru * sizeof(int *));
    int **P2 = (int **)malloc(n_baru * sizeof(int *));
    int **P3 = (int **)malloc(n_baru * sizeof(int *));
    int **P4 = (int **)malloc(n_baru * sizeof(int *));
    int **P5 = (int **)malloc(n_baru * sizeof(int *));
    int **P6 = (int **)malloc(n_baru * sizeof(int *));
    int **P7 = (int **)malloc(n_baru * sizeof(int *));

    int **temp1 = (int **)malloc(n_baru * sizeof(int *));
    int **temp2 = (int **)malloc(n_baru * sizeof(int *));

    for (int i = 0; i < n_baru; i++) {
        A11[i] = (int *)malloc(n_baru * sizeof(int));
        A12[i] = (int *)malloc(n_baru * sizeof(int));
        A21[i] = (int *)malloc(n_baru * sizeof(int));
        A22[i] = (int *)malloc(n_baru * sizeof(int));

        B11[i] = (int *)malloc(n_baru * sizeof(int));
        B12[i] = (int *)malloc(n_baru * sizeof(int));
        B21[i] = (int *)malloc(n_baru * sizeof(int));
        B22[i] = (int *)malloc(n_baru * sizeof(int));

        C11[i] = (int *)malloc(n_baru * sizeof(int));
        C12[i] = (int *)malloc(n_baru * sizeof(int));
        C21[i] = (int *)malloc(n_baru * sizeof(int));
        C22[i] = (int *)malloc(n_baru * sizeof(int));

        P1[i] = (int *)malloc(n_baru * sizeof(int));
        P2[i] = (int *)malloc(n_baru * sizeof(int));
        P3[i] = (int *)malloc(n_baru * sizeof(int));
        P4[i] = (int *)malloc(n_baru * sizeof(int));
        P5[i] = (int *)malloc(n_baru * sizeof(int));
        P6[i] = (int *)malloc(n_baru * sizeof(int));
        P7[i] = (int *)malloc(n_baru * sizeof(int));

        temp1[i] = (int *)malloc(n_baru * sizeof(int));
        temp2[i] = (int *)malloc(n_baru * sizeof(int));
    }

    // Membagi matriks A dan B menjadi 4 submatriks
    for (int i = 0; i < n_baru; i++) {
        for (int j = 0; j < n_baru; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + n_baru];
            A21[i][j] = A[i + n_baru][j];
            A22[i][j] = A[i + n_baru][j + n_baru];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + n_baru];
            B21[i][j] = B[i + n_baru][j];
            B22[i][j] = B[i + n_baru][j + n_baru];
        }
    }

    // Menghitung 7 produk Strassen
	tambah(n_baru, A11, A22, temp1); // temp1 = A11 + A22
	tambah(n_baru, B11, B22, temp2); // temp2 = B11 + B22
	strassen(n_baru, temp1, temp2, P1); // P1 = (A11 + A22) * (B11 + B22)

	tambah(n_baru, A21, A22, temp1); // temp1 = A21 + A22
	strassen(n_baru, temp1, B11, P2); // P2 = (A21 + A22) * B11

	kurang(n_baru, B12, B22, temp1); // temp1 = B12 - B22
	strassen(n_baru, A11, temp1, P3); // P3 = A11 * (B12 - B22)

	kurang(n_baru, B21, B11, temp1); // temp1 = B21 - B11
	strassen(n_baru, A22, temp1, P4); // P4 = A22 * (B21 - B11)

	tambah(n_baru, A11, A12, temp1); // temp1 = A11 + A12
	strassen(n_baru, temp1, B22, P5); // P5 = (A11 + A12) * B22

	kurang(n_baru, A21, A11, temp1); // temp1 = A21 - A11
	tambah(n_baru, B11, B12, temp2); // temp2 = B11 + B12
	strassen(n_baru, temp1, temp2, P6); // P6 = (A21 - A11) * (B11 + B12)

	kurang(n_baru, A12, A22, temp1); // temp1 = A12 - A22
	tambah(n_baru, B21, B22, temp2); // temp2 = B21 + B22
	strassen(n_baru, temp1, temp2, P7); // P7 = (A12 - A22) * (B21 + B22)

    // Menghitung submatriks C
	tambah(n_baru, P1, P4, temp1); // temp1 = P1 + P4
	kurang(n_baru, temp1, P5, temp2); // temp2 = (P1 + P4) - P5
	tambah(n_baru, temp2, P7, C11); // C11 = (P1 + P4 - P5) + P7

    tambah(n_baru, P3, P5, C12); // C12 = P3 + P5

    tambah(n_baru, P2, P4, C21); // C21 = P2 + P4

	tambah(n_baru, P1, P3, temp1); // temp1 = P1 + P3
	kurang(n_baru, temp1, P2, temp2); // temp2 = (P1 + P3) - P2
	tambah(n_baru, temp2, P6, C22); // C22 = (P1 + P3 - P2) + P6
	
    // Menggabungkan submatriks C menjadi matriks C
    for (int i = 0; i < n_baru; i++) {
        for (int j = 0; j < n_baru; j++) {
            C[i][j] = C11[i][j];
            C[i][j + n_baru] = C12[i][j];
            C[i + n_baru][j] = C21[i][j];
            C[i + n_baru][j + n_baru] = C22[i][j];
        }
    }

    // Membebaskan memori
    for (int i = 0; i < n_baru; i++) {
        free(A11[i]);
        free(A12[i]);
        free(A21[i]);
        free(A22[i]);

        free(B11[i]);
        free(B12[i]);
        free(B21[i]);
        free(B22[i]);

        free(C11[i]);
        free(C12[i]);
        free(C21[i]);
        free(C22[i]);

        free(P1[i]);
        free(P2[i]);
        free(P3[i]);
        free(P4[i]);
        free(P5[i]);
        free(P6[i]);
        free(P7[i]);

        free(temp1[i]);
        free(temp2[i]);
    }
    free(A11);
    free(A12);
    free(A21);
    free(A22);

    free(B11);
    free(B12);
    free(B21);
    free(B22);

    free(C11);
    free(C12);
    free(C21);
    free(C22);

    free(P1);
    free(P2);
    free(P3);
    free(P4);
    free(P5);
    free(P6);
    free(P7);

    free(temp1);
    free(temp2);
}

int main() {
    int n = 4; // Ukuran matriks (harus pangkat dari 2)
	
	// Alokasi memori untuk setiap matriks
    int **A = (int **)malloc(n * sizeof(int *));
    int **B = (int **)malloc(n * sizeof(int *));
    int **C = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++) {
        A[i] = (int *)malloc(n * sizeof(int));
        B[i] = (int *)malloc(n * sizeof(int));
        C[i] = (int *)malloc(n * sizeof(int));
    }

    // Inisialisasi matriks A dan B
    int nilai = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = nilai++;
            B[i][j] = nilai++;
        }
    }
    
    // Menampilkan matriks A dan B
    printf("Matriks awal :\nMatriks A :\n");
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }
    printf("\nMatriks B : \n");
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", B[i][j]);
        }
        printf("\n");
    }

    // Mengalikan matriks A dan B menggunakan algoritma Strassen
    strassen(n, A, B, C);

    // Menampilkan hasil perkalian matriks
    printf("\nHasil perkalian matriks :\n");
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", C[i][j]);
        }
        printf("\n");
    }

    // Membebaskan memori
    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
    return 0;
}
