
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROWS  50
#define COLS  50
#define GENS  50
#define MSECS 25000

enum {
    WHITE, BLACK
};
enum {
    LEFT, RIGHT, UP, DOWN
};

static char world[ROWS][COLS];
static char print_world[ROWS][COLS];
typedef struct movement {
    int x;
    int y;
    int dir;
} mm;

static inline void step( mm *ants,int size) {
    int i=0;

    for(i;i<size;i++) {
        switch (world[ants[i].y][ants[i].x]) {
            case '1':
                world[ants[i].y][ants[i].x] = '0';
                print_world[ants[i].y][ants[i].x]='0';
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
                print_world[ants[i].y][ants[i].x]='0';
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
    }
    int y = 0;
    int x;
    for(y=0;y<size;y++){
        print_world[ants[y].y][ants[y].x]='#';
    }

    for(y=0;y<ROWS;y++){
        printf("\n");
        for(x=0;x<COLS;x++){
            printf("%c ",print_world[y][x]);
        }
    }
    /*for (y; y < ROWS; y++) {
        //       _sleep(1000);
        printf("\n");
        int x = 0;
        for (x; x < COLS; x++)
            if (ants[i].y == y && ants[i].x == x)
                printf("%c ", '@');
            else
                printf("%c ", (world[y][x]) ? '=' : '.');
    }*/


}

int main(void) {
    int size = 10;
/*    mm cell = {
            .x   = 20,
            .y   = 20,
            .dir = RIGHT,
    };*/
    int rows;
    int columns;
    for(rows=0;rows<ROWS;rows++){
        for(columns=0;columns<COLS; columns++){
            world[rows][columns]='1';
            print_world[rows][columns]='1';
        }
    }
    mm* array_of_ants = (mm*)malloc(size * sizeof(mm));
    int x = 0;
    for (x=0; x < size; x++) {
        array_of_ants[x].x = 2 * x + size;
        array_of_ants[x].y = x + size;
        array_of_ants[x].dir = RIGHT;
    }
    for (x=0; x < size; x++) {
        printf("\n%i %i %i\n",array_of_ants[x].x,array_of_ants[x].y,array_of_ants[x].dir);
    }
    fflush(stdout);
    size_t i = 0;

    for (i; i < GENS; i++) {
        if (usleep(MSECS) == -1) {
            fprintf(stderr, "usleep failed");
            exit(1);
        }
        step(array_of_ants,size);
        printf("Step: %d\n", i);
    }
    for(x=0;x<size;x++){
        free(array_of_ants);
    }

    puts("Done.");
}