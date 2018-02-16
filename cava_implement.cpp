// Copyright © 2018 Brian Pomerantz. All Rights Reserved.

#include <iostream>
#include <ncurses.h>
#include <string>

#define maxScreen 50

using namespace std;

void display(int level[10]) {
    move(0,0);
    int count = 0;
    for (int j = maxScreen; j > 0; j-=2) {
        for (int k = 0; k < 10; k++) {
            if (level[k] >= j) {
                if (count < 3) {
                    attron(COLOR_PAIR(2));
                    printw("xx  ");
                }
                else if (count < 10) {
                    attron(COLOR_PAIR(3));
                    printw("xx  ");
                }
                else {
                    attron(COLOR_PAIR(4));
                    printw("xx  ");
                }
            }
            else {
                printw("    ");
            }
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

    while (1) {
        cin >> data;
        
        //cout << data << endl;

        leftPos = 0;
        for (int i = 0; i < 10; i++) {
            rightPos = data.find(';', leftPos);
            //cout << rightPos << ", " << data.substr(leftPos, rightPos) << " ";
            level[i] = stoi(data.substr(leftPos, rightPos));
            //cout << level[i] << endl;
            leftPos = rightPos + 1;
        }
        


        display(level);
        refresh();
    }

    endwin();

    return 0;
}
