#include "main.h"
#include <vector>
#include <algorithm>

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
#include "firebeam.h"
#include "laser.h"
#include "shield.h"
#include "waterball.h"
#include "iceball.h"
#include "semi_ring.h"

#ifndef ENGINE_H
#define ENGINE_H

template <typename T> bool filter(T& type) { return ((type.position.x < FRAME - ARENA_WIDTH) || (type.position.y  == GRAVE)); }

template <typename T> void draw_template(std::vector<T> type, glm::mat4 VP) {
    type.erase(std::remove_if(type.begin(), type.end(), filter<T>), type.end());
    for (auto it = type.begin(); it != type.end(); it++)
        it->draw(VP);
}

class Engine {
public:
    Engine() {}
    Engine(int level);
    void draw(glm::mat4 VP);
    void tick();
    void collider();
    int get_life();
    void tick_input(GLFWwindow *window);
private:
    Platform base,roof;
    Player player;
    int score;
    int counter;
    Number_display score_display;
    Number_display life_display;
    std::vector<Magnet> magnets;
    std::vector<Coin> coins;
    std::vector<Boomerang> boomerangs;
    std::vector<Heart> hearts;
    std::vector<Missile> missiles;
    std::vector<Dragon> dragons;
    std::vector<Firebeam> firebeams;
    std::vector<Laser> lasers;
    std::vector<Waterball> waterballs;
    std::vector<Shield> shields;
    std::vector<Iceball> iceballs;
    std::vector<Ring> rings;
};

#endif // ENGINE_H
