#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H

class Missile {
public:
    Missile() {}
    Missile(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t box();
private:
    VAO *object;
    static constexpr double height = 0.4f;
    static constexpr double width =  1.0f;
    double speed_x;
};

#endif // MISSILE_H
