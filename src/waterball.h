#include "main.h"

#ifndef WATERBALL_H
#define WATERBALL_H


class Waterball {
public:
    Waterball() {}
    Waterball(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void die();
    void tick();
    double speed;
    bounding_box_t box();
private:
    VAO *object;
    static constexpr double height = 0.4f;
    static constexpr double width =  0.4f;
    double speed_x;
    double speed_y;
};

#endif // WATERBALL_H
