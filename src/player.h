#include "main.h"

#ifndef BALL_H
#define BALL_H


class Player {
public:
    Player() {}
    Player(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void tickUp();
    void move(int direction);
    double speed;
    bounding_box_t box();
    void die();
private:
    VAO *object;
    double speed_x;
    static constexpr double height = 1.0f;
    static constexpr double width = 0.5f;
    int lives = 3;
};

#endif // BALL_H
