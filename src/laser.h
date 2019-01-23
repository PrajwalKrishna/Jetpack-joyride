#include "main.h"
#include "firebox.h"

const int num = 16;

#ifndef LASER_H
#define LASER_H


class Laser {
public:
    Laser() {}
    Laser(float x, float y, double theta, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t box();
    bool collision(bounding_box_t player);
private:
    VAO *object;
    static constexpr double height = 0.3f;
    static constexpr double width = 0.3f;
    Firebox firebox[num];
};

#endif // LASER_H
