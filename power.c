#include <stdio.h>
#include <math.h>
#include "fft.h"

#define n 1024


double data[n], mag[n/2], music;
double re, im;
int i, j, index;

void fft(double time) {
    /* code */
}

int main(int argc, const char *argv[]) {
    double data[n], mag[n/2];
    
    int i;
    for (i = 0; i < n; i++) {
        data[i] = sin(i);
    }

    realft(data-1, n, 1);

    double re, im;
    mag[0] = sqrt(data[0]*data[0]);
    for (i = 1; i < n/2; i++) {
        re = data[2*i];
        im = data[2*i+1];
        mag[i] = sqrt(re*re + im*im);
    }

    for (i = 0; i < n/2-1; i++) {
        printf("%f, ", mag[i]);
    }
    printf("%f\n", mag[n/2-1]);

    return 0;
}
