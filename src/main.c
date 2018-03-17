
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROWS  50
#define COLS  50
#define MSECS 25000
static int size;
static int noAnts;

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

static inline void step(mm *ants, int noAnts) {
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
    }
    int y = 0;
    int x;
    for (y = 0; y < noAnts; y++) {
        print_world[ants[y].y][ants[y].x] = '#';
    }

    for (y = 0; y < size; y++) {
        printf("\n");
        for (x = 0; x < size; x++) {
            printf("%c ", print_world[y][x]);
        }
    }

}

int main(void) {
    printf("Podaj wymiary planszy: ");
    scanf("%d", &size);
    if (size < 1) {
        printf("Zbyt mala plansza!\n");
        return 100;
    }
    printf("\n");

    int steps;
    printf("Liczba krokow: ");
    scanf("%d", &steps);
    if (steps < 1) {
        printf("Liczba krokow musi być dodatnia!\n");
        return 101;
    }
    printf("\n");

    printf("Liczba mrowek: ");
    scanf("%d", &noAnts);
    if (noAnts < 1) {
         printf("Liczba mrowek musi być dodatnia!\n");
         return 102;
     }


    int rows;
    int columns;
    for (rows = 0; rows < size; rows++) {
        for (columns = 0; columns < size; columns++) {
            world[rows][columns] = '1';
            print_world[rows][columns] = '1';
        }
    }
    mm *array_of_ants = (mm *) malloc(noAnts * sizeof(mm));
    int x = 0;
    for (x = 0; x < noAnts; x++) {
        array_of_ants[x].x = 2 * x + (size - 2 * noAnts) / 2;
        array_of_ants[x].y = x + (size - noAnts) / 2;
        array_of_ants[x].dir = RIGHT;
    }
    for (x = 0; x < noAnts; x++) {
        printf("\n%i %i %i\n", array_of_ants[x].x, array_of_ants[x].y, array_of_ants[x].dir);
    }
    fflush(stdout);
    size_t i = 0;

    for (i; i < steps; i++) {
        if (usleep(MSECS) == -1) {
            fprintf(stderr, "usleep failed");
            exit(1);
        }
        step(array_of_ants, noAnts);
        printf("Step: %d\n", i + 1);
    }
    for (x = 0; x < noAnts; x++) {
        free(array_of_ants);
    }

    puts("Done.");
}