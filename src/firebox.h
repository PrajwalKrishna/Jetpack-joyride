#include "main.h"

#ifndef FIREBOX_H
#define FIREBOX_H


extern const color_t COLOR_ORANGE;
extern const color_t COLOR_YELLOW;

class Firebox {
public:
    Firebox() {}
    Firebox(float x, float y, double theta);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t box();
private:
    VAO *object[2];
    static constexpr double height = 0.3f;
    static constexpr double width = 0.3f;
    static constexpr double thickness = 0.03f;
};

#endif // FIREBOX_H
