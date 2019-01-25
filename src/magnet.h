#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H

class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bool tick();
private:
    VAO *object[2];
    static constexpr double height = 1.2f;
    static constexpr double width =  1.0f;
    static constexpr double thickness = 0.3f;
    int count;
    int life;
};

#endif // MAGNET_H
