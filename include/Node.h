#pragma once

#include "color.h"
#include <string>
#include <iostream>

class Node {
   private:
    bool alive;
    bool wasBorn;
    bool died;
    std::string color;

   public:
    void die();
    void born();
    void nothing();
    void display();
    void setAlive(bool); 
    bool getAlive();
    std::string getColor();
};