#include "main.h"

#ifndef HEART_H
#define HEART_H

class Heart {
public:
    Heart() {}
    Heart(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t box();
private:
    VAO *object;
    static constexpr double height = 0.6f;
    static constexpr double width =  0.5f;
    static constexpr double speed_x = 0.05f;
};

#endif
