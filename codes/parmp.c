#include <stdio.h>
#include <complex.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>

#define PI 3.141592653589793238462643383279502884

// void fft(complex double *X, int N) {
//     if (N <= 1) return;  // Trivijalni slučaj
//     printf("NIT:%d\n",omp_get_thread_num());
//     // Podeli niz na dva pola
//     complex double even[N/2];
//     complex double odd[N/2];

//     // Prva petlja - paralelizacija
//     #pragma omp parallel for
//     for (int i = 0; i < N/2; i++) {
//         even[i] = X[i*2];
//         // printf("%.2f",creal(X[i*2]));
//         odd[i] = X[i*2 + 1];
//     }

//     // Rekurzivno primeni FFT na oba podniza
//     #pragma omp parallel sections
//     {
//         #pragma omp section
//         fft(even, N/2);

//         #pragma omp section
//         fft(odd, N/2);
//     }

//     // Kombinuj rezultate
//     #pragma omp parallel for
//     for (int i = 0; i < N/2; i++) {
//         complex double t = cexp(-2.0 * I * PI * i / N) * odd[i];
        
//         #pragma omp critical
//         {
//             X[i] = even[i] + t;
//             X[i + N/2] = even[i] - t;
//         }
//     }
// }

// int main() {
//     // Primer niza za FFT
//     int N = 8;
//     complex double X[] = {1, 2, 3, 4, 4, 3, 2, 1};
//     double start = omp_get_wtime();
//     // Paralelizacija glavnog poziva FFT-a
//     #pragma omp parallel
//     #pragma omp single
//     fft(X, N);
//     double end = omp_get_wtime();
//     printf("%.15f\n", end-start);

//     // Ispis rezultata
//     for (int i = 0; i < N; i++) {
//         printf("X[%d] = %.2f + %.2fi\n", i, creal(X[i]), cimag(X[i]));
//     }
// }

#include <stdio.h>
#include <complex.h>
#include <math.h>
#include <omp.h>

#define PI 3.141592653589793238462643383279502884

void fft(complex double *X, int N);

int main() {
    // Primer niza za FFT
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

    double start = omp_get_wtime();
    
    // Paralelizacija glavnog poziva FFT-a
    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        fft(X[i], cols);
    }
    
    double end = omp_get_wtime();
    // printf("Vreme izvrsavanja: %.15f sekundi\n", end - start);
    printf("%.15f\n", end - start);

    // Ispis rezultata
    // for (int i = 0; i < rows; i++) {
    //     printf("Row %d: ", i + 1);
    //     for (int j = 0; j < cols; j++) {
    //         printf("%.2f + %.2fi\t", creal(X[i][j]), cimag(X[i][j]));
    //     }
    //     printf("\n");
    // }

    return 0;
}

void fft(complex double *X, int N) {
    if (N <= 1) return;  // Trivijalni slučaj

    // Podeli niz na dva pola
    complex double even[N/2];
    complex double odd[N/2];

    // Prva petlja - paralelizacija
    #pragma omp parallel for
    for (int i = 0; i < N/2; i++) {
        even[i] = X[i*2];
        odd[i] = X[i*2 + 1];
    }

    // Rekurzivno primeni FFT na oba podniza
    #pragma omp parallel sections
    {
        #pragma omp section
        fft(even, N/2);

        #pragma omp section
        fft(odd, N/2);
    }

    // Kombinuj rezultate
    #pragma omp parallel for
    for (int i = 0; i < N/2; i++) {
        complex double t = cexp(-2.0 * I * PI * i / N) * odd[i];
        
        #pragma omp critical
        {
            X[i] = even[i] + t;
            X[i + N/2] = even[i] - t;
        }
    }
}
