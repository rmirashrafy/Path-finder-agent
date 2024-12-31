#include "Playground.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Playground::Playground(int size) : size(size), ThePlayGround(size, std::vector<int>(size, -1)) {
    initialize();
}

void Playground::initialize() {
    if (size <= 6) {
        cout << "Invalid size, The size must be more than 6." << endl;
        throw std::invalid_argument("Invalid size");
    }
    generateRandomValues();
}

void Playground::generateRandomValues() {
    //create a rand num based on time
    srand((unsigned) time(NULL));

    //Random goal position in (4-n] range 
    GoalPositionX = 1 + 4 + rand() % (size - 5 + 1);
    GoalPositionY = 1 + 4 + rand() % (size - 5 + 1);
    ThePlayGround[GoalPositionX][GoalPositionY]=100;

    //Number of tunnels in [1-n] range
    int NumberOfTunnels;
    NumberOfTunnels = 1 + rand() % (size - 2 +1);

    //Number of vectors in [1-n] range
    int NumberOfVectors;
    NumberOfVectors = 1 + rand() % (size - 2 +1);

    //Position of tunnels, first row:X, Second row:Y
    //int TunnelsPositionsArray[NumberOfTunnels][2];
    int TempPosX,TempPosY;

    for(int i = 0; i < NumberOfTunnels; i++) {
        //Random number in (1,n) range
        TempPosX = 1 + 4 + rand() % (size - 5);
        TempPosY = 1 + 4 + rand() % (size - 5);

        ThePlayGround[TempPosX][TempPosY] = 3;
    }

    //TODO: what if vector and tunnel happend to be the same place
    for (int i = 0; i < NumberOfVectors; i++)
    {
        TempPosX = 1 + 4 + rand() % (size - 5);
        TempPosY = 1 + 4 + rand() % (size - 5);
        int Direction, Steps;
        //random number from 1-8
        Direction = 1 + rand() % (8);
        //Random number in (1,n) range
        //TODO: it needs to be fixed realated to agent position
        Steps = rand() % (size - 5);
        int mix = Steps*10 + Direction;
        if(ThePlayGround[TempPosX][TempPosY]!=3){
            ThePlayGround[TempPosX][TempPosY] = mix;
        }

    }
}

std::vector<std::vector<int>> Playground::getPlayground() const {
    return ThePlayGround;
}

int Playground::getGoalPositionX() const {
    return GoalPositionX;
}

int Playground::getGoalPositionY() const {
    return GoalPositionY;
}
