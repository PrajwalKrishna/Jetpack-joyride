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
    bounding_box_t box();
    void magnetic_motion(float x, float y);
    void die();
    void get_life();
    int lives = 5;
    bool shoot(int counter);
    bool shield;
private:
    VAO *object;
    VAO *shield_object;
    double speed_x;
    double speed_y;
    int pre_count = 0;
    static constexpr double height = 1.0f;
    static constexpr double width = 0.5f;
};

#endif // BALL_H
