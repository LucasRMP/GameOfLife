#include "Node.h"
#include "Timer.h"
#include <iostream>
#include <linux/const.h>
#include <random>

#define LOG(content) std::cout << content << std::endl

#define SIZE      30 //SIZE OF THE CANVAS
#define CHANCE    40 //CHANCE (%) OF A NODE TO START ALIVE
#define FPS       10 //FRAME RATE
#define GAME_TIME 15 //TIME TO ELAPSE (sec) BEFORE THE GAME ENDS IF THE TABLE IS NOT COMPLETELY DEAD 

Node** update(Node**);
int display(Node**);
int checkNeighbors(Node**, int, int);
void setup(Node***);

int main() {
    
    system("clear");
    Node **currTable;
    setup(&currTable);

    //GAME LOOP
    Timer timer;
    bool done = false;        
    timer.setInterval([&](){
        system("clear");
        LOG("Conway's Game of Life - By: Lucas Pessone - Made in c++17\n");
        if (display(currTable)) {
            LOG("\nPress ctrl+c to exit");
            currTable = update(currTable);
        }
        else {
            LOG("Your lineage of nodes was extinguished! Thanks for playing!\n\n");
            done = true;
        }
    }, 1000/FPS);

    timer.setTimeout([&](){
        LOG("Your lineage of nodes came close to a stable species, thanks for playing!");
        done = true;
    }, 1000 * GAME_TIME);

    while(!done); //KEEP MAIN THREAD ACTIVE WHILE THE GAME LOOP IS RUNNING

    for(int i = 0; i < SIZE; i++, delete[] currTable[i]);
    delete[] currTable; 
    return 0;
}

void setup(Node*** currTable) {
    *currTable = new Node*[SIZE];
    for (int i = 0; i < SIZE; i++) {
        (*currTable)[i] = new Node[SIZE];
    }
    std::random_device dice;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            bool alive = dice()%100 < CHANCE;
            (*currTable)[i][j].setAlive(alive);
        }
    }
    dice.~random_device();
}

int checkNeighbors(int posX, int posY, Node** currTable) {
    int neighbors = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            bool conditionA = posX + i >= 0 && posX + i < SIZE;
            bool conditionB = posY + j >= 0 && posY + j < SIZE;
            if (conditionA && conditionB) {
                neighbors += (int)currTable[posX+i][posY+j].getAlive();
            }
        }
    }
    neighbors -= (int)currTable[posX][posY].getAlive();
    return neighbors;
}

Node** update(Node** currTable) {
    Node **newTable = new Node*[SIZE];
    for (int i = 0; i < SIZE; i++) {
        newTable[i] = new Node[SIZE];
        for (int j = 0; j < SIZE; j++) {
           newTable[i][j] = currTable[i][j];
        }
    }
    for (int i = 0; i < SIZE; i++) {
       for (int j = 0; j < SIZE; j++) {
            int nNeighbors = checkNeighbors(i, j, currTable);
            bool alive = currTable[i][j].getAlive();

            if (alive) {
                if (nNeighbors <= 1 || nNeighbors >= 4) newTable[i][j].die();
                else newTable[i][j].nothing();
            }
            else {
                if (nNeighbors == 3) newTable[i][j].born();
                else newTable[i][j].nothing();
            }
        }
    }
    return newTable;
}

int display(Node** currTable) {
    int aliveNodes = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            currTable[i][j].display();
            if (currTable[i][j].getAlive()) aliveNodes++;
        }
        std::cout << std::endl;
    }
    return aliveNodes;
}