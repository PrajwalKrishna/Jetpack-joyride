#include "main.h"

#ifndef FIREBOX_H
#define FIREBOX_H


class Firebox {
public:
    Firebox() {}
    Firebox(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t box();
private:
    VAO *object;
    static constexpr double height = 0.3f;
    static constexpr double width = 0.3f;
};

#endif // FIREBOX_H
