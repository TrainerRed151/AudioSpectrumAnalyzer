// Copyright © 2018 Brian Pomerantz. All Rights Reserved.

#include <iostream>
#include <ncurses.h>
#include <string>

using namespace std;

void display(int level[10], int maxScreen, int maxCols) {
    int num_xs = maxCols/10 - 2;
    move(0,0);
    int count = 0;
    for (int j = maxScreen; j > 0; j--) {
        for (int k = 0; k < 10; k++) {
            if (level[k] >= j) {
                if (count < maxScreen*0.1) {
                    attron(COLOR_PAIR(2));
                }
                else if (count < maxScreen*0.35) {
                    attron(COLOR_PAIR(3));
                }
                else {
                    attron(COLOR_PAIR(4));
                }

                for (int c = 0; c < num_xs; c++) {
                  printw("x");
                }
            }
            else {
                for (int c = 0; c < num_xs; c++) {
                  printw(" ");
                }
            }

            printw("  ");
        }

        attron(COLOR_PAIR(1));
        printw("\n");
        count++;
    }
}

int main(int argc, const char *argv[]) {
    system("clear");

    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);


    string data;
    int leftPos, rightPos;
    int level[10];
    int lines = atoi(argv[1]);
    int cols = atoi(argv[2]);

    while (1) {
        cin >> data;
        
        leftPos = 0;
        for (int i = 0; i < 10; i++) {
            rightPos = data.find(';', leftPos);
            level[i] = stoi(data.substr(leftPos, rightPos));
            leftPos = rightPos + 1;
        }

        display(level, lines, cols);
        refresh();
    }

    endwin();

    return 0;
}
