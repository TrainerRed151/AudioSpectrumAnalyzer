#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "fft.h"
#include <ncurses.h>

#define n 16384

#define KRED "\x1B[31m"
#define KYEL "\x1B[33m"
#define KGRN "\x1B[32m"
#define KWHT "\x1B[37m"
//#define KRED ""
//#define KYEL ""
//#define KGRN ""
//#define KWHT ""

double data[n], music[n], mag[n/2];
double re, im;
int i, j, k, fs = 32768;
int freq[10], level[10];
char buf[2];
int count;//, tindex, chillTemp;
//FILE *dfile;

/*
void readInMusic() {
    for (i = 1; i < n; i++) {
        music[i-1] = music[i];
        data[i-1] = music[i];
    }
    
    fflush(stdin);
    fread(buf, 4, 1, stdin);
    music[n-1] = (int)*(short*)buf + (int)*(short*)(buf+2);
    //printf("%f\n", data[n-1]);
}

*/

void readInMusic() {
    i = 0;
    fflush(stdin);
    while (fread(buf, 4, 1, stdin)) {
        data[i] = (int)*(short*)buf + (int)*(short*)(buf+2);
        //printf("%f\n", data[i]);
        
        i++;
        if (i >= n) {
            return;
        }
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
        //printf("%f\n", mag[j]);
    }


    for (j = 0; j < 10; j++) {
        //level[j] = (mag[freq[j-1]] + mag[freq[j]] + mag[freq[j+2]])/3.0;
        level[j] = mag[freq[j]];
        //printf("%d\n", level[j]);
        //level[j] = (int) (5*log10(level[j]+1.0));
        //printf("%d\n", level[j]);
        level[j] = 1e-5*level[j];
        //printf("%d\n", level[j]);
    }
}

void display() {
    //dfile = fopen("display", "w");
    move(0,0);
    count = 0;
    //for (j = n/4; j > 0; j -= n/(30*4)) {
    for (j = 50; j > 0; j-=2) {
        for (k = 0; k < 10; k++) {
            if (level[k] >= j) {
                if (count < 3) {
                    //printf("%sxx  ", KRED);
                    //fprintf(dfile, "%sxx  ", KRED);
                    attron(COLOR_PAIR(2));
                    printw("xx  ");
                }
                else if (count < 10) {
                    //printf("%sxx  ", KYEL);
                    //fprintf(dfile, "%sxx  ", KYEL);
                    attron(COLOR_PAIR(3));
                    printw("xx  ");
                }
                else {
                    //printf("%sxx  ", KGRN);
                    //fprintf(dfile, "%sxx  ", KGRN);
                    attron(COLOR_PAIR(4));
                    printw("xx  ");
                }
            }
            else {
                //printf("    ");
                //fprintf(dfile, "    ");
                printw("    ");
            }
        }

        //printf("%s\n", KWHT);
        //fprintf(dfile, "%s\n", KWHT);
        attron(COLOR_PAIR(1));
        printw("\n");
        count++;
    }

    //fclose(dfile);
}

int main(int argc, const char *argv[]) {
    for (i = 0; i < 10; i++) {
        //freq[i] = (int) (pow(2.0, 5.0+i)*n/fs);
        freq[i] = (int) (pow(2.0, 4.0+i));
        //printf("%d\n", freq[i]);
    }

    //freq = {16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};

    
    system("clear");

    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    
    while (1) {
        readInMusic();
        calcLevels();
        //system("clear");
        //for (i = 0; i < 40; i++) {
        //    printf("\n");
        //}
        //system("clear");
        display();
        refresh();
        //sleep(1);
        //chill(100000);
    }


    endwin();
    
    return 0;
}
