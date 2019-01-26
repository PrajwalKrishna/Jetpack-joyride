#include "main.h"

#ifndef RING_H
#define RING_H

const int NUM = 32;

class Ring {
public:
    Ring() {}
    Ring(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t box();
private:
    VAO *object[NUM];
    static constexpr double radius = 2.0f;
    static constexpr double height = radius * 2;
    static constexpr double width = radius;
    static constexpr double thickness = 0.01f;
};

#endif // RING_H
