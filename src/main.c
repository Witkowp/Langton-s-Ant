
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "create_png_file.h"
#include "step.h"

static int size;
static int noAnts;

void mapInitializer(char** world,char** print_world);
void createMap(char** map,int size);
void printer(char** print_world);



int main() {
    time_t t;
    printf("Podaj wymiary planszy: ");
    scanf("%d", &size);
    if (size < 1) {
        printf("Zbyt mala plansza!\n");
        return EXIT_FAILURE;
    }
    printf("\n");

    int steps;
    printf("Liczba krokow: ");
    scanf("%d", &steps);
    if (steps < 1) {
        printf("Liczba krokow musi być dodatnia!\n");
        return EXIT_FAILURE;
    }
    printf("\n");

    printf("Liczba mrowek: ");
    scanf("%d", &noAnts);
    if (noAnts < 1) {
        printf("Liczba mrowek musi być dodatnia!\n");
    	return EXIT_FAILURE;  
    }

    char** world=(char**)malloc(size*sizeof(char*));
    char** print_world=(char**)malloc(size*sizeof(char*));
   
    createMap(world,size);
    createMap(print_world,size);
   
    mapInitializer(world,print_world);
    srand((unsigned) time(&t));	 
    mm *array_of_ants = (mm *) malloc(noAnts * sizeof(mm));
    int x = 0;
    for (x = 0; x < noAnts; x++) {
	array_of_ants[x].x=rand()%size;
	array_of_ants[x].y=rand()%size;
        array_of_ants[x].dir=rand()%4;
    }
    fflush(stdout);
    size_t i = 0;

    for (i; i < steps; i++) {
        step(world,print_world,array_of_ants, noAnts,size);
    }

    int y = 0;
    for (y = 0; y < noAnts; y++) {
        print_world[array_of_ants[y].y][array_of_ants[y].x] = '#';
    }
    process_file(size,print_world);
    write_png_file("Mrowki.png");


    free(array_of_ants);
    for(y=0;y<size;y++){
	free(print_world[y]);
	free(world[y]);	
    }
    free(world);
    free(print_world);

    puts("Program wygenerował plik png o nazwie Mrowki.png");
}

void printer(char** print_world) {
    int y = 0,x=0;
    for (y = 0; y < size; y++) {
        printf("\n");
        for (x = 0; x < size; x++) {
            printf("%c ", print_world[y][x]);
        }
    }
}

void mapInitializer(char** world,char** print_world) {
    int rows;
    int columns;
    for (rows = 0; rows < size; rows++) {
        for (columns = 0; columns < size; columns++) {
            world[rows][columns] = '1';
            print_world[rows][columns] = '1';
        }
    }
}

void createMap(char** map,int size){
	int x;
	for(x=0;x<size;x++){
		map[x]=(char*)malloc(size*sizeof(char));
	}
}
