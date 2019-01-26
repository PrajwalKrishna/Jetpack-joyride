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
    VAO *object[2];
    static constexpr double height = 0.4f;
    static constexpr double thickness = 0.3f;
    static constexpr double width =  1.2f;
    static constexpr double speed_x = 0.1f;
};

#endif // MISSILE_H
