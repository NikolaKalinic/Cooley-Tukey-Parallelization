// #include <stdio.h>
// #include <complex.h>
// #include <math.h>
// #include <time.h>

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

// int main() {
//     // Primer niza za FFT
//     int N = 8;
//     complex double X[] = {1, 2, 3, 4, 4, 3, 2, 1};
//     struct timespec start, end;
//     double elapsed_time;

//     clock_gettime(CLOCK_MONOTONIC, &start);
//     // Primena FFT na niz
//     fft(X, N);
//     clock_gettime(CLOCK_MONOTONIC, &end);
//     elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

//     printf("Vreme izvrsavanja: %f sekundi\n", elapsed_time);

//     // Ispis rezultata
//     for (int i = 0; i < N; i++) {
//         printf("X[%d] = %.2f + %.2fi\n", i, creal(X[i]), cimag(X[i]));
//     }

//     return 0;
// }

#include <stdio.h>
#include <complex.h>
#include <math.h>
#include <time.h>

#define PI 3.141592653589793238462643383279502884

void fft(complex double *X, int N) {
    if (N <= 1) return;
    complex double even[N/2];
    complex double odd[N/2];
    for (int i = 0; i < N/2; i++) {
        even[i] = X[i*2];
        odd[i] = X[i*2 + 1];
    }
    fft(even, N/2);
    fft(odd, N/2);
    for (int i = 0; i < N/2; i++) {
        complex double t = cexp(-2.0 * I * PI * i / N) * odd[i];
        X[i] = even[i] + t;
        X[i + N/2] = even[i] - t;
    }
}

int main() {
    int rows = 50000;  // Broj redova
    int cols = 8;  // Broj kolona

    complex double X[rows][cols];

    // Inicijalizacija svakog reda matrice
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
    struct timespec start, end;
    double elapsed_time;

    clock_gettime(CLOCK_MONOTONIC, &start);

    // Primena FFT nad svakim redom matrice
    for (int i = 0; i < rows; i++) {
        fft(X[i], cols);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // printf("Vreme izvrsavanja: %f sekundi\n", elapsed_time);
    printf("%f\n", elapsed_time);

    // Ispis rezultata
    // for (int i = 0; i < rows; i++) {
    //     printf("Row %d:\n", i + 1);
    //     for (int j = 0; j < cols; j++) {
    //         printf("%.2f + %.2fi\t", creal(X[i][j]), cimag(X[i][j]));
    //     }
    //     printf("\n");
    // }

    return 0;
}
