#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H

class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t box();
private:
    VAO *object;
    static constexpr double height = 0.4f;
    static constexpr double width =  0.4f;
    static constexpr double deacceleration =  0.001f;
    static constexpr double angular_velocity = 1.0f;
    double speed_x;
    double speed_y;
};

#endif // BOOMERANG_H
