// #include <stdio.h>
// #include <complex.h>
// #include <math.h>
// #include <stdlib.h>
// #include <mpi.h>

// #define PI 3.141592653589793238462643383279502884

// void fft(complex double *X, int N) {
//     if (N <= 1) return;  // Trivijalni slučaj

//     // Podeli niz na dva pola
//     complex double even[N/2];
//     complex double odd[N/2];
//     for (int i = 0; i < N/2; i++) {
//         even[i] = X[i*2];
//         odd[i] = X[i*2 + 1];
//     }

//     // Rekurzivno primeni FFT na oba podniza
//     fft(even, N/2);
//     fft(odd, N/2);

//     // Kombinuj rezultate
//     for (int i = 0; i < N/2; i++) {
//         complex double t = cexp(-2.0 * I * PI * i / N) * odd[i];
//         X[i] = even[i] + t;
//         X[i + N/2] = even[i] - t;
//     }
// }

// int main(int argc, char *argv[]) {
//     MPI_Init(&argc, &argv);

//     int rank, size;
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     MPI_Comm_size(MPI_COMM_WORLD, &size);

//     // Primer niza za FFT
//     int N = 8;
//     complex double X[] = {1, 2, 3, 4, 4, 3, 2, 1};
//     double start_time, end_time;
    
//     // Svaki proces radi nad svojim deo niza
//     int local_size = N / size;
//     complex double local_X[local_size];
    
//     start_time = MPI_Wtime();
//     // Raspostranjivanje dela niza na sve procese
//     MPI_Scatter(X, local_size, MPI_C_DOUBLE_COMPLEX, local_X, local_size, MPI_C_DOUBLE_COMPLEX, 0, MPI_COMM_WORLD);

//     // Primena FFT na lokalnom delu niza
//     fft(local_X, local_size);

//     // Skupljanje rezultata sa svih procesa
//     MPI_Gather(local_X, local_size, MPI_C_DOUBLE_COMPLEX, X, local_size, MPI_C_DOUBLE_COMPLEX, 0, MPI_COMM_WORLD);
//     end_time = MPI_Wtime();
//     if (rank == 0) {
//          printf("Elapsed time: %f seconds\n", end_time - start_time);
//         // Ispis rezultata samo za proces sa rangom 0
//         for (int i = 0; i < N; i++) {
//             printf("X[%d] = %.2f + %.2fi\n", i, creal(X[i]), cimag(X[i]));
//         }
//     }

//     MPI_Finalize();
//     return 0;
// }
// int main(int argc, char *argv[]) {
//     MPI_Init(&argc, &argv);

//     int rank, size;
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     MPI_Comm_size(MPI_COMM_WORLD, &size);

//     // Primer niza za FFT
//     int rows = 50000;  // Broj redova
//     int cols = 8;  // Broj kolona

//     complex double X[rows][cols];

//     // Inicijalizacija svakog reda matrice
//     for (int i = 0; i < rows; i++) {
//         X[i][0] = 1;
//         X[i][1] = 2;
//         X[i][2] = 3;
//         X[i][3] = 4;
//         X[i][4] = 4;
//         X[i][5] = 3;
//         X[i][6] = 2;
//         X[i][7] = 1;
//     }
//     double start_time, end_time;
    
//     // Svaki proces radi nad svojim deo niza
//     int local_size = N / size;
//     complex double local_X[local_size];
    
//     start_time = MPI_Wtime();
//     // Raspostranjivanje dela niza na sve procese
//     MPI_Scatter(X, local_size, MPI_C_DOUBLE_COMPLEX, local_X, local_size, MPI_C_DOUBLE_COMPLEX, 0, MPI_COMM_WORLD);

//     // Primena FFT na lokalnom delu niza
//     for (int i = 0; i < rows; i++) {
//         fft(X[i], cols);
//     }

//     // Skupljanje rezultata sa svih procesa
//     MPI_Gather(local_X, local_size, MPI_C_DOUBLE_COMPLEX, X, local_size, MPI_C_DOUBLE_COMPLEX, 0, MPI_COMM_WORLD);
//     end_time = MPI_Wtime();
//     if (rank == 0) {
//          printf("Elapsed time: %f seconds\n", end_time - start_time);
//         // Ispis rezultata samo za proces sa rangom 0
//         for (int i = 0; i < N; i++) {
//             printf("X[%d] = %.2f + %.2fi\n", i, creal(X[i]), cimag(X[i]));
//         }
//     }

//     MPI_Finalize();
//     return 0;
// }

//##############################################################

#include <stdio.h>
#include <complex.h>
#include <math.h>
#include <stdlib.h>
#include <mpi.h>

#define PI 3.141592653589793238462643383279502884

void fft(complex double *X, int N);

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Primer niza za FFT
    int rows = 50000;  // Broj redova
    int cols = 8;  // Broj kolona

    // Ukupan broj elemenata u matrici
    int total_elements = rows * cols;

    // Svaki proces dobija deo matrice
    int local_rows = rows / size;
    int local_elements = local_rows * cols;

    // Kreiranje lokalnog niza koji će svaki proces obraditi
    complex double* local_X = (complex double*)malloc(local_elements * sizeof(complex double));

    // Kreiranje niza za skupljanje rezultata
    complex double* gathered_X = NULL;
    double start_time, end_time;

    // Inicijalizacija svakog reda matrice samo za proces sa rangom 0
    if (rank == 0) {
        complex double X[rows][cols];
        for (int i = 0; i < rows; i++) {
            X[i][0] = 1;
            X[i][1] = 2;
            X[i][2] = 3;
            X[i][3] = 4;
            X[i][4] = 4;
            X[i][5] = 3;
            X[i][6] = 2;
            X[i][7] = 1;
        }

        // Raspostranjivanje dela matrice na sve procese
        MPI_Scatter(X, local_elements, MPI_C_DOUBLE_COMPLEX, local_X, local_elements, MPI_C_DOUBLE_COMPLEX, 0, MPI_COMM_WORLD);

        // Alociranje memorije za gathered_X samo u procesu sa rangom 0
        int buffer_size = total_elements * sizeof(complex double);
        gathered_X = (complex double*)malloc(buffer_size);
        start_time = MPI_Wtime();
    } else {
        // Svaki drugi proces samo dobija deo matrice
        MPI_Scatter(NULL, 0, MPI_DATATYPE_NULL, local_X, local_elements, MPI_C_DOUBLE_COMPLEX, 0, MPI_COMM_WORLD);
    }


    // Primena FFT na lokalnom delu niza
    for (int i = 0; i < local_rows; i++) {
        fft(&local_X[i * cols], cols);
    }

    // Skupljanje rezultata sa svih procesa
    MPI_Gather(local_X, local_elements, MPI_C_DOUBLE_COMPLEX, gathered_X, local_elements, MPI_C_DOUBLE_COMPLEX, 0, MPI_COMM_WORLD);
    end_time = MPI_Wtime();

    if (rank == 0) {
        printf("%f\n", end_time - start_time);

        // Ispis rezultata samo za proces sa rangom 0
        // for (int i = 0; i < rows; i++) {
        //     printf("Row %d: ", i + 1);
        //     for (int j = 0; j < cols; j++) {
        //         printf("%.2f + %.2fi\t", creal(gathered_X[i * cols + j]), cimag(gathered_X[i * cols + j]));
        //     }
        //     printf("\n");
        // }

        // Oslobađanje alocirane memorije
        free(gathered_X);
    }

    free(local_X);
    MPI_Finalize();
    return 0;
}

void fft(complex double *X, int N) {
    if (N <= 1) return;  // Trivijalni slučaj

    // Podeli niz na dva pola
    complex double even[N/2];
    complex double odd[N/2];
    for (int i = 0; i < N/2; i++) {
        even[i] = X[i*2];
        odd[i] = X[i*2 + 1];
    }

    // Rekurzivno primeni FFT na oba podniza
    fft(even, N/2);
    fft(odd, N/2);

    // Kombinuj rezultate
    for (int i = 0; i < N/2; i++) {
        complex double t = cexp(-2.0 * I * PI * i / N) * odd[i];
        X[i] = even[i] + t;
        X[i + N/2] = even[i] - t;
    }
}
