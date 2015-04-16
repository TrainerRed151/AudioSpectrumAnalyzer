#include <stdio.h>
#include <math.h>
#include "fft.h"

#define n 1024


double data[n], mag[n/2], music;
double re, im;
int i, j, k, fs = 44100;
int freq[10], level[10];


void calcLevels(double time) {
    realft(data-1, n, 1);

    mag[0] = sqrt(data[0]*data[0]);
    for (j = 1; j < n/2; j++) {
        re = data[2*j];
        im = data[2*j+1];
        mag[j] = sqrt(re*re + im*im);
    }

    for (j = 0; j < 10; j++) {
        level[j] = 10*log10(mag[freq[j]]);
    }
}

void display() {
    for (j = 30; j > 0; j--) {
        for (k = 0; k < 10; k++) {
            if (level[k] >= j) {
                printf("x");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main(int argc, const char *argv[]) {
    for (i = 0; i < 10; i++) {
        freq[i] = (int) (pow(2.0, 5.0+i)*n/fs);
    }
    
    for (i = 0; i < n; i++) {
        data[i] = sin(pow(2.0,15.0)*2*3.14159*i/fs);
    }

    calcLevels(5);
    display();

    for (i = 0; i < 10; i++) {
        //printf("%d, %d\n", freq[i], level[i]);
    }

    return 0;
}
