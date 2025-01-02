#include "Playground.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <math.h>

/*
TODO : core dromp get checked
check the random range s
change all the random prodactions
cleaning the code
*/

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
    GoalPositionX = 4 + rand() % (size - 5 + 1);
    GoalPositionY = 4 + rand() % (size - 5 + 1);

    //Number of tunnels in [1-n] range
    int NumberOfTunnels;
    NumberOfTunnels = 1 + rand() % (size - 2 +1);
    // cout<<NumberOfTunnels<<"\n";

    //Number of vectors in [1-n] range
    // int NumberOfVectors;
    // NumberOfVectors = 1 + rand() % (size - 2 +1);

    //Position of tunnels, first row:X, Second row:Y
    //int TunnelsPositionsArray[NumberOfTunnels][2];
    int TempPosX,TempPosY,TempStatic;

    // Define range
        int min = 0;
        int max = size;

    int const degree[8] ={90, 45, 0, 305, 270, 335, 180, 135};
    
    for(int i = 0; i < NumberOfTunnels; i++) {

        // Initialize a random number generator
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(min, max);

        // Generate random number in the range [min, max]
        // int randomValue = distrib(gen);

        //Random number in (1,n) range
        TempPosX = distrib(gen);
        TempPosY = distrib(gen);

        ThePlayGround[TempPosX][TempPosY] = 3;
    }

    //TODO: what if vector and tunnel happend to be the same place
    for (int i = 0; i < size; i++)
    {

        for (int j = 0; j < size; j++)
        {
            /* code */
                // TempStatic = rand() % 10 + 1;
            //TempPosY = 1 + 4 + rand() % (size - 5);

            // Define range
            int min = 1;
            int max = 10;

            // Initialize a random number generator
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distrib(min, max);

            // Generate random number in the range [min, max]
            int randomValue = distrib(gen);

            int Direction, Steps;
            //random number from 1-8
            Direction = 1 + rand() % (8);

            // Define range
            // min = 1;
            // max = size;

            // // Initialize a random number generator
            // random_device rd;
            // mt19937 gen(rd());
            // uniform_int_distribution<> distrib(min, max);

            // Generate random number in the range [min, max]
            // Steps = distrib(gen)/2;

            //Random number in (1,n) range
            //TODO: it needs to be fixed realated to agent position
            Steps = 1+ rand() % ((size/2));

            //check if the action is even possible
            int endXpos, endYpos;
            int degreeValue = (degree[Direction-1])*(M_PI/180);
            endXpos = i + (Steps*cos(degreeValue));
            endYpos = j + (Steps*sin(degreeValue));
            bool possibleMove;

            if(endXpos>(size-1) || endXpos<0){
                possibleMove = false;
            }
            else if(endYpos>(size-1) || endYpos<0){
                possibleMove = false;
            }
            else{
                possibleMove = true;
            }

            int mix = Steps*10 + Direction;
            cout<<" i , j: "<<i<<" ,"<<j<<" mix: "<<mix<<" degree: "<<degree[Direction-1]<<" endX: "<<endXpos<<" endY: "<<endYpos<<" possible move: "<<possibleMove<<"\n";

            if(ThePlayGround[i][j]!=3 && randomValue<=3 && possibleMove){
                ThePlayGround[i][j] = mix;
            }
        }
        

    }

    ThePlayGround[0][0]=0;
    ThePlayGround[GoalPositionX][GoalPositionY]=100;
    
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
