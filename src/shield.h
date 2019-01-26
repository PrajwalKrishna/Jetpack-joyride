#include "main.h"

#ifndef SHIELD_H
#define SHIELD_H


class Shield {
public:
    Shield() {}
    Shield(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void move(int direction);
    bounding_box_t box();
private:
    VAO *object;
    static constexpr double height = 1.0f;
    static constexpr double width = 0.5f;
};

#endif // SHIELD_H
