#include "vec2.hpp"
vec2::vec2(double x, double y) {
    this->x = x;
    this->y = y;
}

vec2 vec2::operator+(const vec2 &b) const {
    return vec2(x + b.x, y + b.y);
}

vec2 vec2::operator-(const vec2 &b) const {
    return vec2(x - b.x, y - b.y);
}

bool vec2::operator==(const vec2 &b) const {
    if(b.x == this->x && b.y == this->y) {
        return true;
    } else {
        return false;
    }
}

void vec2::set(double x, double y) {
    this->x = x;
    this->y = y;
}
