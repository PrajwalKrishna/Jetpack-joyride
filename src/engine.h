#include "main.h"
#include <vector>

// Include objects
#include "platform.h"
#include "player.h"
#include "magnet.h"
#include "coin.h"
#include "boomerang.h"
#include "heart.h"
#include "missile.h"
#include "dragon.h"
#include "seven_segment_display.h"

#ifndef ENGINE_H
#define ENGINE_H

class Engine {
public:
    Engine() {}
    Engine(int level);
    void draw(glm::mat4 VP);
    void tick();
    void collider();
    void tick_input(GLFWwindow *window);
private:
    Platform base,roof;
    Player player;
    int score;
    int counter;
    Number_display number_display;
    std::vector<Magnet> magnets;
    std::vector<Coin> coins;
    std::vector<Boomerang> boomerangs;
    std::vector<Heart> hearts;
    std::vector<Missile> missiles;
    std::vector<Dragon> dragons;
};

#endif // ENGINE_H
