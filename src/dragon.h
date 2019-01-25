#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H

class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float player_x, float player_y);
    bounding_box_t box();
private:
    VAO *object;
    static constexpr double height = 0.8f;
    static constexpr double width =  1.2f;
    static constexpr double speed_x = 0.04f;
};

#endif // DRAGON_H
