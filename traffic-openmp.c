
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include <omp.h>
#include <time.h>

const int NB_CARS = 10;
const int NB_PLACES = 4;
const int MAX_SPEED = 20;

struct Car {
   int id;
   int speed;
   int place;
};

void initCar(struct Car *c, int n){

    c->id = n;
    c->speed = rand() % MAX_SPEED;
    c->place = rand() % NB_PLACES;

}

void initArrays(int * stoppedCars, int * place2Cars, int * merged){
    for(int i=0; i<NB_CARS; i++){
        stoppedCars[i] = place2Cars[i] = merged[i] = 0;
    }
}


void printCars(struct Car cars [NB_CARS]){

    for(int i = 0; i < NB_CARS; i++){
        printf("Car #%d --- speed: %d, place: %d\n", cars[i].id, cars[i].speed, cars[i].place);
    }

}

void printArrays(int * stoppedCars, int * place2Cars, int * merged){
    printf("Stopped Cars: ");
    for(int i=0; i<NB_CARS; i++){
        printf("%d ", stoppedCars[i]);
    }
    printf("\nPlace 2 Cars: ");
    for(int i=0; i<NB_CARS; i++){
        printf("%d ", place2Cars[i]);
    }
    printf("\nMerged result:");
    for(int i=0; i<NB_CARS; i++){
        printf("%d ", merged[i]);
    }
    printf("\n");
} 

/* void computeStoppedCars(int * stoppedCars, struct Car cars [NB_CARS]){
    for(int i=0; i<NB_CARS; i++){
        if(cars[i].speed == 0) stoppedCars[i] = 1;
    }
} 

void computePlace2Cars(int * place2Cars, struct Car cars [NB_CARS]){
    for(int i=0; i<NB_CARS; i++){
        if(cars[i].place == 2) place2Cars[i] = 1;
    }
} */

void computeArrays(struct Car cars [NB_CARS], int * place2Cars, int * stoppedCars, int * merged){

    omp_set_num_threads(4);
    #pragma omp parallel for
    for (int i=0; i<NB_CARS; i++){
        if(cars[i].place == 2){
            place2Cars[i] = 1;
        } 
        if(cars[i].speed == 0){
            stoppedCars[i] = 1;
        } 
        if (place2Cars[i] == 1 && stoppedCars[i] == 1){
            merged[i] = 1;
        }
    }
}


int main()
{

    // init
    struct Car cars [NB_CARS];
    srand(time(NULL));
    for(int i = 0; i < NB_CARS; i++){
        initCar(&cars[i], i);

    }

    printCars(cars);

    int stoppedCars[10] = {0};
    int place2Cars[10] = {0};
    int merged[10] = {0};

    printf("\n");

    initArrays(stoppedCars, place2Cars, merged);
    printf("Initialized arrays:\n");
    printArrays(stoppedCars, place2Cars, merged);
    computeArrays(cars, place2Cars, stoppedCars, merged);
    printf("\n");
    printf("Computed arrays:\n");
    printArrays(stoppedCars, place2Cars, merged);


    return 0;
}


