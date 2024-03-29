#include "main.h"

#ifndef Digit_display_H
#define Digit_display_H

const float SEGMENT_LENGTH = 0.5;
const float THICKNESS = 0.06;
const int MAX_DIGITS = 19;

const bool decoder[10][7] = {
    {1,1,1,1,1,1,0}, //0
    {0,1,1,0,0,0,0}, //1
    {1,1,0,1,1,0,1}, //2
    {1,1,1,1,0,0,1}, //3
    {0,1,1,0,0,1,1}, //4
    {1,0,1,1,0,1,1}, //5
    {1,0,1,1,1,1,1}, //6
    {1,1,1,0,0,0,0}, //7
    {1,1,1,1,1,1,1}, //8
    {1,1,1,1,0,1,1}  //9
};

const double vertex[7][3] = {
    {                0.0f, SEGMENT_LENGTH  , 0      },
    { SEGMENT_LENGTH/2.0f, SEGMENT_LENGTH/2.0f, M_PI/2.0f },
    { SEGMENT_LENGTH/2.0f,-SEGMENT_LENGTH/2.0f, M_PI/2.0f },
    {                0.0f,-SEGMENT_LENGTH  , 0      },
    {-SEGMENT_LENGTH/2.0f,-SEGMENT_LENGTH/2.0f, M_PI/2.0f },
    {-SEGMENT_LENGTH/2.0f, SEGMENT_LENGTH/2.0f, M_PI/2.0f },
    {            0.0f ,             0.0f, 0      }
};
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
private:
    VAO *object;
    Digit_display digits[MAX_DIGITS];
    int count;
};

#endif // Digit_display_H
