#include "Playground.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <math.h>
#include <cmath>

/*
TODO : core dromp get checked
check the random range s
change all the random prodactions -->its working
what if vector and tunnel happend to be the same place 
--> tunnel existing will be checked and then there where no tunnel a vector is placed
*/

using namespace std;

Playground::Playground(int size) : size(size), ThePlayGround(size, std::vector<int>(size, -1)) {
    initialize();
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

    int TempPosX,TempPosY,TempStatic;

    // range of random numbers
    int min = 0;
    int max = size;

    //defining degree list to be able to calculate end Position of each vector
    int const degree[8] ={180, 135, 90, 45, 0, 315, 270, 225};
    
    for(int i = 0; i < NumberOfTunnels; i++) {

        // Initialize a random number generator
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(min, max);

        //Random number in (1,n) range
        TempPosX = distrib(gen);
        TempPosY = distrib(gen);
        ThePlayGround[TempPosX][TempPosY] = 3;
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            //creating 30% chance of vector in a sq
            int min = 1;
            int max = 10;
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distrib(min, max);
            int randomValue = distrib(gen);

            int Direction, Steps;
            //random number from 1-8
            Direction = 1 + rand() % (8);
            Steps = 1+ rand() % ((size/2));
            if(Steps%2==0){
                Steps=(1.4)*(Steps); // this is because the crossing directions have to go sqrt(2)
            }

            // ThePlayGround[i][j] = i*1000+j; // this is just for checking the grids

            //check if the action is even possible in the playground
            double endXpos, endYpos;
            double degreeValue = (degree[Direction-1])*(M_PI/180);
            endYpos = j + (Steps*sin(degreeValue));
            endXpos = i + (Steps*cos(degreeValue));
            
            endXpos = round(endXpos);
            endYpos = round(endYpos);

            bool possibleMove;

            if((endXpos<(size) && endXpos>=0)  &&  (endYpos<(size) && endYpos>=0)){
                possibleMove = true;
            }
            else{
                possibleMove = false;
            }

            int mix = Steps*10 + Direction;
            //vector selection log
            cout<<" i , j: "<<i<<" ,"<<j<<" mix: "<<mix<<" degree: "<<degreeValue<<" deg: "<<degree[Direction-1]<<" endX: "<<endXpos<<" endY: "<<endYpos<<" possible move: "<<possibleMove<<"\n";

            if(ThePlayGround[i][j]!=3  && possibleMove && randomValue<=3){
                ThePlayGround[i][j] = mix;
            }
        }
        

    }

    ThePlayGround[0][0]=0;
    ThePlayGround[GoalPositionX][GoalPositionY]=100;
    
}

