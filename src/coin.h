#include "main.h"

#ifndef COIN_H
#define COIN_H

const color_t COIN_MAP[3] = {COLOR_YELLOW, COLOR_BLUE, COLOR_RED};

class Coin {
public:
    Coin() {}
    Coin(float x, float y, int type);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t box();
    int type;
private:
    VAO *object;
    static constexpr double height = 0.4f;
    static constexpr double width = 0.4f;
};

#endif // COIN_H
