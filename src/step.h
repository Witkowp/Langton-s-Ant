#ifndef LANGTON_S_ANT_STEP_H
#define LANGTON_S_ANT_STEP_H
typedef struct movement {
    int x;
    int y;
    int dir;
} mm;

void step(char** world, char** print_world,mm *ants, int noAnts,int size);
#endif
