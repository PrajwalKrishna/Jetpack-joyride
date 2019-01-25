#include "main.h"

#ifndef Seven_segment_display_H
#define Seven_segment_display_H

const float SEGMENT_LENGTH = 0.5;
const float THICKNESS = 0.06;

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

class Seven_segment_display {
public:
    Seven_segment_display() {}
    Seven_segment_display(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object[7];
};

#endif // Seven_segment_display_H
