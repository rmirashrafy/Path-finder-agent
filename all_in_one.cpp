#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <cmath>

using namespace std;

/*
TODO : change the vector grid to array grid
write xny end pos funcs
*/

/* in this int array :
    goal is set to 100
    start is set to 0
    every tunnel is 3
    unvisited sq is -1
    visited sq is 1
    vectors are a digit number where first digit is Direction(clockwise and in 8 directions) and 
    the second and so on are the amount of steps 
    agent has to be added in this file
*/

int randomNumber(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}
void thefunctiontobefixed(){
    // ThePlayGround[i][j] = i*1000+j; // this is just for checking the grids
            //check if the action is even possible in the playground
            // double endXpos, endYpos;
            // double degreeValue = (degree[Direction-1])*(M_PI/180);
            // endYpos = j + (st*sin(degreeValue));
            // endXpos = i + (st*cos(degreeValue));
            
            // endXpos = round(endXpos);
            // endYpos = round(endYpos);

            // bool possibleMove;

            // if((endXpos<(LenghtOfPlayGround) && endXpos>=0)  &&  (endYpos<(LenghtOfPlayGround) && endYpos>=0)){
            //     possibleMove = true;
            // }
            // else{
            //     possibleMove = false;
            // }

}
// get color based on value
sf::Color getColor(int value) {
    switch (value) {
        case 0: return sf::Color::White;          // Start position
        case 1: return sf::Color::Green;          // Visited square
        case 3: return sf::Color::Yellow;         // Tunnel
        case 100: return sf::Color::Blue;         // Goal
        case -1: return sf::Color(205, 193, 180); // Unvisited square
        default: return sf::Color(238, 228, 218); // Other
    }
}

int main() {
    // Play ground sq size TODO: what if the input is less than 6?
    int LenghtOfPlayGround;
    cin >> LenghtOfPlayGround;

    if (LenghtOfPlayGround <= 6) {
        cout << "Invalid size, The size must be more than 6." << endl;
        return 1;
    }

    //Random goal position in (4-n] range
    int PlayGround[LenghtOfPlayGround][LenghtOfPlayGround];
    int GoalPositionX = randomNumber(4,LenghtOfPlayGround);
    int GoalPositionY = randomNumber(4,LenghtOfPlayGround);

    for (int i = 0; i < LenghtOfPlayGround; i++)
    {
        for (int j = 0; j < LenghtOfPlayGround; j++)
        {
            PlayGround[i][j] = -1;
        }
    }
    PlayGround[0][0]=0;
    PlayGround[GoalPositionX][GoalPositionY]=100;

    //Number of tunnels in [1-n] range
    int NumberOfTunnels;
    NumberOfTunnels = randomNumber(1,LenghtOfPlayGround);
    // cout<<NumberOfTunnels<<"\n";

    int TempPosX,TempPosY,TempStatic;

    //defining degree list to be able to calculate end Position of each vector
    int const degree[8] ={180, 135, 90, 45, 0, 315, 270, 225};
    
    for(int i = 0; i < NumberOfTunnels; i++) {
        //Random number in (1,n) range
        TempPosX = randomNumber(1,LenghtOfPlayGround-2);
        TempPosY = randomNumber(1,LenghtOfPlayGround-2);
        while((TempPosX==0 && TempPosY==0) || (GoalPositionX==TempPosX && GoalPositionY==TempPosY)){
            TempPosX = randomNumber(1,LenghtOfPlayGround-2);
            TempPosY = randomNumber(1,LenghtOfPlayGround-2);
        }
        PlayGround[TempPosX][TempPosY] = 3;
    }

    for (int i = 0; i < LenghtOfPlayGround; i++)
    {
        for (int j = 0; j < LenghtOfPlayGround; j++)
        {
            //creating 30% chance of vector in a sq
            int randomValue = randomNumber(1,10);
            int Direction, Steps;
            //random number from 1-8
            Direction = randomNumber(1,8);
            Steps = randomNumber(1,LenghtOfPlayGround/2);
            double st;
            if(Steps%2==0){
                st=(1.4)*(Steps); // this is because the crossing directions have to go sqrt(2)
            }
            
            int mix = Steps*10 + Direction;
            //vector selection log
            // cout<<" i , j: "<<i<<" ,"<<j<<" mix: "<<mix<<" degree: "<<degreeValue<<" deg: "<<degree[Direction-1]<<" endX: "<<endXpos<<" endY: "<<endYpos<<" possible move: "<<possibleMove<<"\n";

            if(PlayGround[i][j]!=3 && PlayGround[i][j]!=100 && PlayGround[i][j]!=0 && randomValue<=3){//&& possibleMove 
                PlayGround[i][j] = mix;
            }
            
        }
    }

    // Size of window and squares
    int squareSize = 90; //TODO : the sq size must create a fitting window in screen
    int windowSize = LenghtOfPlayGround * squareSize;

    // Main window
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Playground Grid");

    // font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    // Main window processing
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Grid drawing
        const auto& grid = PlayGround;
        for (int i = 0; i < LenghtOfPlayGround; ++i) {
            for (int j = 0; j < LenghtOfPlayGround; ++j) {
                sf::RectangleShape square(sf::Vector2f(squareSize - 5, squareSize - 5));
                square.setPosition(j * squareSize, i * squareSize);
                square.setFillColor(getColor(grid[i][j]));
                square.setOutlineThickness(2);
                square.setOutlineColor(sf::Color::Black);
                window.draw(square);

                // Add text if there is a vector
                if (grid[i][j] != -1 && grid[i][j] != 0 && grid[i][j] != 3 && grid[i][j] != 100) {
                    sf::Text text;
                    text.setFont(font);
                    text.setString(to_string(grid[i][j]));
                    text.setCharacterSize(24);
                    text.setFillColor(sf::Color::Black);
                    sf::FloatRect textRect = text.getLocalBounds();
                    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                    text.setPosition(j * squareSize + squareSize / 2, i * squareSize + squareSize / 2);
                    window.draw(text);
                }
            }
        }

        window.display();
    }

    return 0;
}
