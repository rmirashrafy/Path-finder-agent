#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <cmath>
#include <string.h>

using namespace std;

struct position
{
    int x;
    int y;
};

/* in this int array :
    goal is set to 100
    start is set to 0
    every tunnel is 3
    unvisited sq is -1
    visited sq is 1
    vectors are a digit number where first digit is Direction(clockwise and in 8 directions) and 
    the second and so on are the amount of steps 
    agent has to be added in this file
    visited tunnels and vectors are 100+3(or vector value)
    visited goal 1000
*/

class PositionStack {
private:
    position* arr;
    int top;
    int capacity;

public:
    PositionStack(int size) {
        arr = new position[size];
        capacity = size;
        top = -1;
    }

    ~PositionStack() {
        delete[] arr;
    }

    // Function to add a position `pos` to the stack
    void push(position pos) {
        if (isFull()) {
            cout << "Overflow: Stack is full\n";
            return;
        }
        arr[++top] = pos;
    }

    // Function to pop the top position from the stack
    position pop() {
        if (isEmpty()) {
            cout << "Underflow: Stack is empty\n";
            return {-1, -1}; // Return an invalid position
        }
        return arr[top--];
    }

    // Function to return the top position of the stack
    position peek() {
        if (isEmpty()) {
            cout << "Underflow: Stack is empty\n";
            return {-1, -1}; // Return an invalid position
        }
        return arr[top];
    }

    // Function to return the size of the stack
    int size() {
        return top + 1;
    }

    // Function to check if the stack is empty
    bool isEmpty() {
        return top == -1;
    }

    // Function to check if the stack is full
    bool isFull() {
        return top == capacity - 1;
    }
};

int randomNumber(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

position EndPosition(int startX, int startY, int steps, int Direction) {
    //defining degree list to be able to calculate end Position of each vector
    int const degree[8] ={180, 135, 90, 45, 0, 315, 270, 225};
    // This function is supposed to return end x and y position
    // ThePlayGround[i][j] = i*1000+j; // this is just for checking the grids
    double endXpos, endYpos;
    double degreeValue = (degree[Direction - 1]) * (M_PI / 180.0);
    double st=steps;
    if(steps%2==0){
        st=(1.4)*(steps); // this is because the crossing directions have to go sqrt(2)
    }
    endYpos = startY + (st * sin(degreeValue));
    endXpos = startX + (st * cos(degreeValue));
    position endPosition;
    endPosition.x = round(endXpos);
    endPosition.y = round(endYpos);
    
    return endPosition;
}

// get color based on value
sf::Color getColor(int value) {
    if (value>100) return sf::Color::Green;
    switch (value) {
        case 0: return sf::Color::White;          // Start position
        case 1: return sf::Color::Green;          // Visited square
        case 3: return sf::Color::White;         // Tunnel
        case 100: return sf::Color::White;         // Goal
        case 1000: return sf::Color::Green;  //visited goal
        case -1: return sf::Color(205, 193, 180); // Unvisited square
        default: return sf::Color(238, 228, 218); // Other
    }
}

int main() {
    // Play ground sq size
    int LenghtOfPlayGround;
    cin >> LenghtOfPlayGround;

    if (LenghtOfPlayGround <= 6) {
        cout << "Invalid size, The size must be more than 6." << endl;
        return 1;
    }

    //Random goal position in (4-n] range
    int PlayGround[LenghtOfPlayGround][LenghtOfPlayGround];
    int GoalPositionX = randomNumber(4,LenghtOfPlayGround-1);
    int GoalPositionY = randomNumber(4,LenghtOfPlayGround-1);
    cout<<"GoalPositionX: "<<GoalPositionX<<"\t GoalPositionY: "<<GoalPositionY<<"\n";

    for (int i = 0; i < LenghtOfPlayGround; i++)//setting all indexes to -1
    {
        for (int j = 0; j < LenghtOfPlayGround; j++)
        {
            PlayGround[i][j] = -1;
        }
    }

    PlayGround[0][0]=0;//agent start point
    PlayGround[GoalPositionX][GoalPositionY]=100;

    //Number of tunnels in [1-n] range
    int NumberOfTunnels;
    NumberOfTunnels = randomNumber(1,LenghtOfPlayGround);
    cout<<"number of tunnels : "<<NumberOfTunnels<<"\n";
    int TempPosX,TempPosY,TempStatic;  

    for(int i = 0; i < NumberOfTunnels; i++) {//setting random tunnels
        //Random number in (1,n) range
        TempPosX = randomNumber(1,LenghtOfPlayGround-2);
        TempPosY = randomNumber(1,LenghtOfPlayGround-2);
        while((TempPosX==0 && TempPosY==0) || (GoalPositionX==TempPosX && GoalPositionY==TempPosY)){
            TempPosX = randomNumber(1,LenghtOfPlayGround-2);
            TempPosY = randomNumber(1,LenghtOfPlayGround-2);
            cout<<"is it even working"<<"\n";
        }
        PlayGround[TempPosX][TempPosY] = 3; 
    }

    for (int i = 0; i < LenghtOfPlayGround; i++) {//seting random vectors
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

    for (int i = 0; i < LenghtOfPlayGround; i++)//playgroung log
    {    
        for (int j = 0; j < LenghtOfPlayGround; j++)
        {
            cout<<PlayGround[i][j]<<"  ";
        }
        cout<<"\n";
    }

    //-------------------------agent-decisions--------------------------
    position agent;
    agent.x=0;
    agent.y=0;
    bool done=false;
    PositionStack positions(LenghtOfPlayGround*LenghtOfPlayGround);
    positions.push(agent);
    int f=0;
    
    position tempMove;
    int tempDir;
    bool NewRandMove=true;

    while (!done)
    {
        //random move
        if(NewRandMove){
            tempDir= randomNumber(1,8);
            tempMove= EndPosition(agent.x, agent.y, 1, tempDir);
        }

        if ((tempMove.x<(LenghtOfPlayGround) && tempMove.x>=0)  &&  (tempMove.y<(LenghtOfPlayGround) && tempMove.y>=0)){//check if the move is in the field
            
            cout<<"the selection destination (in the field): "<<agent.x<<" , "<<agent.y<<" , "<<PlayGround[tempMove.x][tempMove.y]<<" "<<tempDir<<" \n ";

            if(PlayGround[tempMove.x][tempMove.y]==100){//Goal
                //update agent position
                agent.x=tempMove.x;
                agent.y=tempMove.y;
                cout<<"goal";
                PlayGround[tempMove.x][tempMove.y]=1000;
                break;
            }
            else if((PlayGround[tempMove.x][tempMove.y]==3)){//Tunnel
                //back move untill still in the feild
                PlayGround[tempMove.x][tempMove.y]+=100;//mark the tunnel visited
                cout<<"tunnel visited in: ("<<tempMove.x<<","<<tempMove.y<<")\n";
                int c=0;
                while (!positions.isEmpty() && c<3)
                {
                    agent=positions.pop();
                    c++;
                    cout<<"Tunnel back move : "<<agent.x<<","<<agent.y<<"\n";
                }
                NewRandMove=true;
            }
            else if(PlayGround[tempMove.x][tempMove.y]==-1){//unvisited
                //visit the sq
                PlayGround[tempMove.x][tempMove.y]=1;
                agent.x=tempMove.x;
                agent.y=tempMove.y;
                positions.push(agent);
                cout<<"Visit: "<<agent.x<<","<<agent.y<<"\n";
                NewRandMove=true;
            }
            else if (PlayGround[tempMove.x][tempMove.y]==1 || PlayGround[tempMove.x][tempMove.y]>100){//already visited
                cout<<"the vector tunnel or sq is visited before or (0,0)"<<"\n";
                continue;
            }
            else if(PlayGround[tempMove.x][tempMove.y]==0){//Call no path
                // cout<<"No Path! ";
                // done=true;
                continue;
            }
            else{//Vector
                int vector = PlayGround[tempMove.x][tempMove.y];
                PlayGround[tempMove.x][tempMove.y]+=100;//mark it visited to know when a tunnel or vector was visited
                agent.x=tempMove.x;
                agent.y=tempMove.y;
                positions.push(agent);
                int steps = vector / 10;
                int direction = vector % 10;
                cout<<"Visit vector: ("<<agent.x<<","<<agent.y<<") steps: "<<steps<<" dir: "<<direction<<"\n";
                for (int c = 0; c < steps; c++)
                {
                    position tempMoveVector = EndPosition(agent.x, agent.y, 1, direction);
                    if ((tempMoveVector.x<(LenghtOfPlayGround) && tempMoveVector.x>=0)  &&  (tempMoveVector.y<(LenghtOfPlayGround) && tempMoveVector.y>=0))
                    {
                        agent = tempMoveVector;
                        if(PlayGround[agent.x][agent.y]==-1){
                            cout<<" jump of: "<<agent.x<<" , "<<agent.y;
                        }
                    }
                }
                positions.push(agent);
                //here is where the last vector ends and the landing sq shoild be checked for another decision
                if(PlayGround[agent.x][agent.y]==1){
                    NewRandMove=true;
                }
                if(PlayGround[agent.x][agent.y]==-1) //&& (PlayGround[agent.x][agent.y]==) (PlayGround[agent.x][agent.y]==-1) )
                {
                    PlayGround[agent.x][agent.y]=1;
                    NewRandMove=true;
                }
                else if(PlayGround[agent.x][agent.y]==100){
                    cout<<"Goal!";
                    break;
                    done=true;
                }
                else if(PlayGround[agent.x][agent.y]>100){
                    // PlayGround[agent.x][agent.y]-=100;
                    NewRandMove=true;//this is a problem if it lands from a vector to a already visited vector nothing happens
                }
                else{
                    NewRandMove=false;
                    tempMove= agent;
                }

            }
        }

        if (PlayGround[agent.x][agent.y]==100)
        {
            //end the cicle
            cout<<"\n"<<"Goal!";
            done = true;
            break;
        }
    }
    
    // Size of window and squares
    int screenWidth = sf::VideoMode::getDesktopMode().width; 
    int screenHeight = sf::VideoMode::getDesktopMode().height; 
    int windowWidth = screenWidth / 2; 
    int windowHeight = screenHeight ; 
    int squareSize = std::min(windowWidth, windowHeight) / LenghtOfPlayGround;
    // int squareSize = 90; //TODO : the sq size must create a fitting window in screen
    // int windowSize = LenghtOfPlayGround * squareSize;
    // Main window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Playground Grid");
    // font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    window.clear(sf::Color::White);
    const auto& grid = PlayGround;
    const char* arrows[8] =  {"↑","↑→","→","↓→","↓","←↓","←","←↑"};
    // const char* arrows[8] =  {"\u2190", "\u2196", "\u2191", "\u2197", "\u2192", "\u2198", "\u2193", "\u2199"};
    // const char* arrows[8] =  {"1", "2", "3", "4", "5", "6", "7", "8"};

    for (int i = 0; i < LenghtOfPlayGround; ++i) {
        for (int j = 0; j < LenghtOfPlayGround; ++j) {
            sf::RectangleShape square(sf::Vector2f(squareSize - 5, squareSize - 5));
            square.setPosition(j * squareSize, i * squareSize);
            square.setFillColor(getColor(grid[i][j]));
            square.setOutlineThickness(2);
            square.setOutlineColor(sf::Color::Black);
            window.draw(square);
            //grid[i][j]=grid[i][j]%100;

            // Add text for tunnels and goal
            if (grid[i][j] == 3 || grid[i][j] == 103) {//visited and unvisited tunnel
                // Display 'T' for tunnel
                sf::Text text;
                text.setFont(font);
                text.setString("T");
                text.setCharacterSize(squareSize / 2);
                text.setFillColor(sf::Color::Black);
                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                text.setPosition(j * squareSize + squareSize / 2, i * squareSize + squareSize / 2);
                window.draw(text);
            } else if (grid[i][j] == 100 || grid[i][j] == 1000) {
                // Display 'G' for goal
                sf::Text text;
                text.setFont(font);
                text.setString("G");
                text.setCharacterSize(squareSize / 2);
                text.setFillColor(sf::Color::Black);
                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                text.setPosition(j * squareSize + squareSize / 2, i * squareSize + squareSize / 2);
                window.draw(text);
            } else if (grid[i][j] != -1 && grid[i][j] != 0 && grid[i][j] != 1 ) { //&& grid[i][j] != 3 && grid[i][j] != 100
                int value = grid[i][j];
                value = value%100;
                int steps = value / 10;
                int direction = value % 10 - 1; // Adjust for zero-based indexing
                const char* arrow = arrows[direction]; // Use const char* for arrow symbol
                
                sf::Text text;
                text.setFont(font);
                // text.setString();
                // text.setString();
                text.setString(sf::String::fromUtf8(arrow, arrow + strlen(arrow)) + " * " + std::to_string(steps)); // Convert arrow to std::string
                // std::wstring arrowText = std::wstring(L"") + (wchar_t)(0x2190 + direction); // Unicode arrows start at U+2190
                // arrowText += L" * " + std::to_wstring(steps);
                // text.setString(arrowText);

                text.setCharacterSize(squareSize / 4);
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
