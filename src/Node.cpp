#include "Node.h"

#define LOG(content) std::cout << content << std::endl

void Node::die() {
    this->died    = true;
    this->alive   = false;
    this->wasBorn = false;
    this->color   = RED_BG;
}

void Node::born() {
    this->died    = false;
    this->alive   = true;
    this->wasBorn = true;
    this->color   = GREEN_BG;
}

void Node::nothing() {
    this->died    = false;
    this->wasBorn = false;
    this->color   = this->alive ? WHITE_BG : RESET;
}

void Node::display() {
    std::cout << this->color << "  " << RESET;
}

void Node::setAlive(bool alive) {
    this->alive = alive;
    if (alive) this->color = GREEN_BG;
    else       this->color = RESET;
}

bool Node::getAlive() {
    return this->alive;
}

std::string Node::getColor() {
    return this->color;
}