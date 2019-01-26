#include "engine.h"
#include <algorithm>

// template <typename T> bool filter (T m) { return (m.position.x < FRAME - ARENA_WIDTH); }
bool filter (Magnet m) { return (m.position.x < FRAME - ARENA_WIDTH); }
bool filter_2 (Coin m) { return (m.position.x < FRAME - ARENA_WIDTH); }
bool filter_3 (Boomerang m) { return (m.position.x < FRAME - ARENA_WIDTH); }
bool filter_4 (Heart m) { return (m.position.x < FRAME - ARENA_WIDTH); }
bool filter_5 (Missile m) { return (m.position.x < FRAME - ARENA_WIDTH); }
bool filter_6 (Dragon m) { return (m.position.x < FRAME - ARENA_WIDTH); }

Engine::Engine(int level) {
    this->base = Platform(-8, FLOOR, COLOR_GREEN);
    this->roof = Platform(-8, CEILING + 2.0f, COLOR_GREEN);
    this->player = Player(-7, FLOOR + 2.5f, COLOR_ORANGE);
    this->score = 1;
    this->number_display = Number_display(FRAME, CEILING + 1.0f, this->score);
    this->counter = 0;
}

void Engine::draw(glm::mat4 VP) {
    this->roof.draw(VP);
    this->base.draw(VP);

    this->player.draw(VP);
    this->number_display.draw(VP);

    this->magnets.erase(std::remove_if(this->magnets.begin(), this->magnets.end(), filter), this->magnets.end());
    for (auto it = this->magnets.begin(); it != this->magnets.end(); it++)
        it->draw(VP);

    this->coins.erase(std::remove_if(this->coins.begin(), this->coins.end(), filter_2), this->coins.end());
    for (auto it = this->coins.begin(); it != this->coins.end(); it++)
        it->draw(VP);

    this->boomerangs.erase(std::remove_if(this->boomerangs.begin(), this->boomerangs.end(), filter_3), this->boomerangs.end());
    for (auto it = this->boomerangs.begin(); it != this->boomerangs.end(); it++)
        it->draw(VP);

    this->hearts.erase(std::remove_if(this->hearts.begin(), this->hearts.end(), filter_4), this->hearts.end());
    for (auto it = this->hearts.begin(); it != this->hearts.end(); it++)
        it->draw(VP);

    this->missiles.erase(std::remove_if(this->missiles.begin(), this->missiles.end(), filter_5), this->missiles.end());
    for (auto it = this->missiles.begin(); it != this->missiles.end(); it++)
        it->draw(VP);

    this->dragons.erase(std::remove_if(this->dragons.begin(), this->dragons.end(), filter_6), this->dragons.end());
    for (auto it = this->dragons.begin(); it != this->dragons.end(); it++)
        it->draw(VP);
}

void Engine::tick() {
    this->counter++;
    this->player.tick();
    this->number_display = Number_display(FRAME, CEILING + 1.0f, this->score);

    // Produce stuffs
    if(counter%942 == 7)
        this->magnets.push_back(Magnet(FRAME + rand()%ARENA_WIDTH, SAFE_FLOOR + rand()%ARENA_HEIGHT));
    if((counter%32) == 7)
        this->coins.push_back(Coin(FRAME + ARENA_WIDTH + rand()%ARENA_WIDTH, SAFE_FLOOR + rand()%ARENA_HEIGHT, COLOR_YELLOW));
    if((counter%64) == 7)
        this->coins.push_back(Coin(FRAME + ARENA_WIDTH + rand()%ARENA_WIDTH, SAFE_FLOOR + rand()%ARENA_HEIGHT, COLOR_BLUE));
    if((counter%128) == 7)
        this->coins.push_back(Coin(FRAME + ARENA_WIDTH + rand()%ARENA_WIDTH, SAFE_FLOOR + rand()%ARENA_HEIGHT, COLOR_RED));
    if(counter%256 == 7)
        this->boomerangs.push_back(Boomerang(FRAME + ARENA_WIDTH + rand()%ARENA_WIDTH/2, SAFE_FLOOR + ARENA_HEIGHT, COLOR_ORANGE));
    if(counter%256 == 7)
        this->boomerangs.push_back(Boomerang(FRAME + ARENA_WIDTH + rand()%ARENA_WIDTH/2, SAFE_FLOOR + rand()%ARENA_HEIGHT, COLOR_ORANGE));
    if((counter%512) == 7)
        this->hearts.push_back(Heart(FRAME + ARENA_WIDTH + rand()%ARENA_WIDTH, SAFE_FLOOR + rand()%ARENA_HEIGHT));
    if((counter%600) == 7)
        this->missiles.push_back(Missile(FRAME + ARENA_WIDTH, SAFE_FLOOR + rand()%ARENA_HEIGHT, COLOR_RED));
    if((counter%800) == 7)
        this->dragons.push_back(Dragon(FRAME + ARENA_WIDTH + rand()%ARENA_WIDTH, SAFE_FLOOR + rand()%ARENA_HEIGHT));

    // Tick other stuff
    for (auto it = this->magnets.begin(); it != this->magnets.end(); it++) {
        it->tick(player.position.x, player.position.y);
        player.magnetic_motion(it->position.x, it->position.y);
    }
    for (auto it = this->coins.begin(); it != this->coins.end(); it++)
        it->tick();
    for (auto it = this->boomerangs.begin(); it != this->boomerangs.end(); it++)
        it->tick();
    for (auto it = this->hearts.begin(); it != this->hearts.end(); it++)
        it->tick();
    for (auto it = this->missiles.begin(); it != this->missiles.end(); it++)
        it->tick();
    for (auto it = this->dragons.begin(); it != this->dragons.end(); it++)
        it->tick(player.position.x, player.position.y);
}

void Engine::tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);

    if (left) {
        this->player.move(0);
    }
    if (right) {
      this->player.move(1);
    }
    if (space || up) {
      this->player.tickUp();
    }
    if (down) {
        // player.shoot();
    }
}

void Engine::collider() {
    // Detect coin capture
    for (auto it = this->coins.begin(); it != this->coins.end(); it++) {
        if(detect_collision(player.box(),it->box()))
        {
            it->position.y -= 100;
            score++;
            // if(it->color == COLOR_RED)
            //     score++;
            // if(it->color == COLOR_BLUE)
            //     score+=2;
            // printf("Points earned = %d\n",score);
        }
    }

    // Detect collision with boomerang
    for (auto it = this->boomerangs.begin(); it != this->boomerangs.end(); it++) {
        if(detect_collision(player.box(), it->box())){
            player.die();
            it->position.y = -100;
            it->speed_x = -10000;
        }
    }
    // Detect heart capture
    for (auto it = this->hearts.begin(); it != this->hearts.end(); it++) {
        if(detect_collision(player.box(),it->box()))
        {
            it->position.y -= 100;
            player.get_life();
        }
    }
    // Detect collision with missile
    for (auto it = this->missiles.begin(); it != this->missiles.end(); it++) {
        if(detect_collision(player.box(), it->box())){
            player.die();
            it->position.y = -100;
        }
    }
}
