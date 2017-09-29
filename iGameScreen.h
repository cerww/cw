#ifndef IGAMESCREEN_H
#define IGAMESCREEN_H
#include <vector>

class iGameScreen{    
    public:        
    virtual void draw() = 0;
    virtual std::pair<std::vector<int>,std::vector<int>>update() = 0;//things to delete, things to add
};

#endif // IGAMESCREEN_H
