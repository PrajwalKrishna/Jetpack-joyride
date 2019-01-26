#include "main.h"

#ifndef Digit_display_H
#define Digit_display_H

const float SEGMENT_LENGTH = 0.5;
const float THICKNESS = 0.06;
const int MAX_DIGITS = 19;

class Segment {
public:
    Segment() {}
    Segment(float x, float y, float rotation, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *object;
};

class Digit_display {
public:
    Digit_display() {}
    Digit_display(float x, float y, int digit);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    Segment segments[7];
};

class Number_display {
public:
    Number_display() {}
    Number_display(float x, float y, int number);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
    Digit_display digits[MAX_DIGITS];
    int count;
};

#endif // Digit_display_H
