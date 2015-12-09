#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "fft.h"

#define n 32768
#define sp 10000000

#define KRED "\x1B[31m"
#define KYEL "\x1B[33m"
#define KGRN "\x1B[32m"
#define KWHT "\x1B[37m"

double data[n], mag[n/2];
double musicTime[sp], musicLeft[sp];
double re, im;
int i, j, k, fs = 44100;
int freq[10], level[10];
int count, tindex, chillTemp;
FILE *dfile;


void readInMusic() {
    FILE *mfile;
    mfile = fopen("music.dat", "r");

    char line[55];
    char *pch;

    for (i = 0; i < sp; i++) {
        fgets(line, 55, mfile);
        
        pch = strtok(line, " ");
        musicTime[i] = atof(pch);

        pch = strtok(NULL, " ");
        musicLeft[i] = atof(pch);
        //musicLeft[i] = 0.0;
    }
    //musicLeft[0] = 1.0;
}

void makeData(double time) {
    for (i = tindex; i < sp; i++) {
        if (time <= musicTime[i]) {
            tindex = i;
            break;
        }
    }

    for (i = 0; i < n; i++) {
        data[i] = musicLeft[tindex+i];
    }
}

void calcLevels() {
    realft(data-1, n, 1);

    mag[0] = sqrt(data[0]*data[0]);
    for (j = 1; j < n/2; j++) {
        re = data[2*j];
        im = data[2*j+1];
        //re = data[i];
        //im = data[n-i];
        mag[j] = sqrt(re*re + im*im);
    }


    //for (i = 0; i < n/2; i+=100) {
    //    printf("%d: %f\n", i, mag[i]);
    //}
    //printf("%f\n", mag[2047]);
    //printf("%f\n", mag[2048]);
    //printf("%f\n", mag[2090]);
    
    //sleep(1);


    for (j = 0; j < 10; j++) {
        level[j] = 0.5*(mag[freq[j]] + mag[freq[j]+1]);
        //printf("%d\n", level[j]);
        level[j] = (int) (20*log10(level[j]+1.0) + j);
        //printf("%d\n", level[j]);
    }
}

void display() {
    dfile = fopen("display", "w");
    count = 0;
    //for (j = n/4; j > 0; j -= n/(30*4)) {
    for (j = 60; j > 0; j-=2) {
        for (k = 0; k < 10; k++) {
            if (level[k] >= j) {
                if (count < 3) {
                    //printf("%sxx  ", KRED);
                    fprintf(dfile, "%sxx  ", KRED);
                    //printf("xx ");
                }
                else if (count < 10) {
                    //printf("%sxx  ", KYEL);
                    fprintf(dfile, "%sxx  ", KYEL);
                    //printf("xx ");
                }
                else {
                    //printf("%sxx  ", KGRN);
                    fprintf(dfile, "%sxx  ", KGRN);
                    //printf("xx ");
                }
            }
            else {
                //printf("    ");
                fprintf(dfile, "    ");
                //printf("sss");
            }
        }

        //printf("%s\n", KWHT);
        fprintf(dfile, "%s\n", KWHT);
        //printf("\n");
        count++;
    }

    fclose(dfile);
}

void chill(int ct) {
    for (i = 0; i < ct; i++) {
        chillTemp = pow(2.0,5.0);
    }
}

int main(int argc, const char *argv[]) {
    readInMusic();

    //for (i = 0; i < 10*n; i++) {
    //    printf("%f: %f\n", musicTime[i], musicLeft[i]);
    //}
   
    //return 0;

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
    //sleep(1);

    //for (i = 0; i < 30; i++) {
    //    printf("\n");
    //}

    fputs("get_property time_pos\n", mp);
    fflush(mp);
    fgets(str, 55, info);
    fflush(info);

    //for (i = 0; i < 100; i++) {
    while (1) {
        fputs("get_property time_pos\n", mp);
        fflush(mp);
        fgets(str, 55, info);
        fflush(info);

        //if (str[0] != 'A') {
        //    printf("%s\n", str);
        //    break;
        //}

        //printf("%f\n", atof(str+13));

        makeData(atof(str+13));
        calcLevels();
        //system("clear");
        //for (i = 0; i < 40; i++) {
        //    printf("\n");
        //}
        //system("clear");
        display();
        //sleep(1);
        //chill(100000);
    }

    fputs("stop\n", mp);
    fclose(mp);
    
    return 0;
}
