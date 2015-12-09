#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "fft.h"

#define n 4096

#define KRED "\x1B[31m"
#define KYEL "\x1B[33m"
#define KGRN "\x1B[32m"
#define KWHT "\x1B[37m"

double data[n], mag[n/2], music;
double re, im;
int i, j, k, fs = 44100;
int freq[10], level[10];
int count;


void makeData(double time) {
    
}

void calcLevels() {
    realft(data-1, n, 1);

    mag[0] = sqrt(data[0]*data[0]);
    for (j = 1; j < n/2; j++) {
        re = data[2*j];
        im = data[2*j+1];
        mag[j] = sqrt(re*re + im*im);
    }

    for (j = 0; j < 10; j++) {
        level[j] = 0.5*(mag[freq[j]] + mag[freq[j]+1]);
    }
}

void display() {
    count = 0;
    for (j = n/4; j > 0; j -= n/(30*4)) {
        for (k = 0; k < 10; k++) {
            if (level[k] >= j) {
                if (count < 3) {
                    printf("%sxx ", KRED);
                }
                else if (count < 10) {
                    printf("%sxx ", KYEL);
                }
                else {
                    printf("%sxx ", KGRN);
                }
            }
            else {
                printf("   ");
            }
        }

        printf("%s\n", KWHT);
        count++;
    }
}

int main(int argc, const char *argv[]) {
    for (i = 0; i < 10; i++) {
        freq[i] = (int) (pow(2.0, 5.0+i)*n/fs);
    }

    FILE *mp, *info;

    system("rm info");
    system("touch info");

    mp = popen("mplayer -slave -quiet violin.wav > info", "w");

    info = fopen("info", "r");
 
    char str[55];

    for (i = 0; i < 20; i++) {
        fgets(str, 55, info);
    }

    fflush(info);
    system("rm info");
    sleep(1);

    for (i = 0; i < 30; i++) {
        printf("\n");
    }

    fputs("get_property time_pos\n", mp);
    fflush(mp);
    fgets(str, 55, info);
    fflush(info);

    for (i = 0; i < 100; i++) {
        fputs("get_property time_pos\n", mp);
        fflush(mp);
        fgets(str, 55, info);
        fflush(info);

        //if (str[0] != 'A') {
        //    printf("%s\n", str);
        //    break;
        //}

        printf("%f\n", atof(str+13));
    }

    fputs("stop\n", mp);
    fclose(mp);
    
    return 0;
}
/*



    //clock_t start, end;
    //start = clock();

    //for (i = 0; i < 10000; i++) {
        for (i = 0; i < n; i++) {
            data[i] = sin(pow(2.0,atof(argv[1]))*2*3.14159*i/fs);
        }
        
        calcLevels(5);
        display();
    //}

    //end = clock();

    //printf("Time: %f\n", (float) (end-start) / (float) CLOCKS_PER_SEC);

    //for (i = 0; i < 10; i++) {
    //    printf("%d: %d, %d\n", (int) pow(2.0, 5.0+i), freq[i]*fs/n, level[i]);
    //}

    //FILE *music
    //music = fopen("music.dat", "r");


    return 0;
}

*/
