#include <stdio.h>
#include <stdlib.h>
#include "step.h"


enum {
    WHITE, BLACK
};
enum {
    LEFT, RIGHT, UP, DOWN
};

void step(char** world, char** print_world,mm *ants, int noAnts,int size) {
    int i = 0;

    for (i; i < noAnts; i++) {
        switch (world[ants[i].y][ants[i].x]) {
            case '1':
                world[ants[i].y][ants[i].x] = '0';
                print_world[ants[i].y][ants[i].x] = '0';
                switch (ants[i].dir) {
                    case LEFT:
                        ants[i].y--;
                        ants[i].dir = UP;
                        break;
                    case RIGHT:
                        ants[i].y++;
                        ants[i].dir = DOWN;
                        break;
                    case UP:
                        ants[i].x++;
                        ants[i].dir = RIGHT;
                        break;
                    case DOWN:
                        ants[i].x--;
                        ants[i].dir = LEFT;
                        break;
                }
                break;
            case '0':
                world[ants[i].y][ants[i].x] = '1';
                print_world[ants[i].y][ants[i].x] = '1';
                switch (ants[i].dir) {
                    case LEFT:
                        ants[i].y++;
                        ants[i].dir = DOWN;
                        break;
                    case RIGHT:
                        ants[i].y--;
                        ants[i].dir = UP;
                        break;
                    case UP:
                        ants[i].x--;
                        ants[i].dir = LEFT;
                        break;
                    case DOWN:
                        ants[i].x++;
                        ants[i].dir = RIGHT;
                }

        }
        ants[i].x=abs(ants[i].x %( size-1));
        ants[i].y=abs(ants[i].y %( size-1));
    }


}
