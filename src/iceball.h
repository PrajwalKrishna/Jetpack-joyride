#include "main.h"

#ifndef ICEBALL_H
#define ICEBALL_H


class Iceball {
public:
    Iceball() {}
    Iceball(float x, float y, float player_x, float player_y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t box();
private:
    VAO *object;
    static constexpr double height = 0.2f;
    static constexpr double width =  0.2f;
    double speed_x;
    double speed_y;
};

#endif // ICEBALL_H
