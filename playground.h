#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <vector>

class Playground {
public:
    Playground(int size);
    void initialize();
    std::vector<std::vector<int>> getPlayground() const;
    int getGoalPositionX() const;
    int getGoalPositionY() const;

private:
    int size;
    std::vector<std::vector<int>> ThePlayGround;
    int GoalPositionX;
    int GoalPositionY;
    void generateRandomValues();
};

#endif // PLAYGROUND_H
