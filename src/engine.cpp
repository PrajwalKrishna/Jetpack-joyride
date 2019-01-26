#include "engine.h"
#include <algorithm>

// template <typename T> bool filter (T m) { return (m.position.x < FRAME - ARENA_WIDTH); }
bool filter (Magnet m) { return (m.position.x < FRAME - ARENA_WIDTH); }
bool filter_2 (Coin m) { return (m.position.x < FRAME - ARENA_WIDTH); }
bool filter_3 (Boomerang m) { return (m.position.x < FRAME - ARENA_WIDTH); }
bool filter_4 (Heart m) { return (m.position.x < FRAME - ARENA_WIDTH); }
bool filter_5 (Missile m) { return (m.position.x < FRAME - ARENA_WIDTH); }
bool filter_6 (Dragon m) { return (m.position.x < FRAME - ARENA_WIDTH); }
bool filter_7 (Firebeam m) { return (m.position.x < FRAME - ARENA_WIDTH); }
bool filter_8 (Laser m) { return (m.position.x < FRAME - ARENA_WIDTH); }
bool filter_9 (Waterball m) { return (m.position.y  == GRAVE); }
bool filter_10 (Shield m) { return (m.position.x < FRAME - ARENA_WIDTH); }

Engine::Engine(int level) {
    this->base = Platform(-8, FLOOR, COLOR_GREEN);
    this->roof = Platform(-8, CEILING + 2.0f, COLOR_GREEN);
    this->player = Player(-7, FLOOR + 2.5f, COLOR_ORANGE);
    this->score = 0;
    this->score_display = Number_display(FRAME - 2.0f, CEILING + 1.0f, this->score);
    this->life_display = Number_display(FRAME + 2.0f, CEILING + 1.0f, this->player.lives);
    this->counter = 0;
}

void Engine::draw(glm::mat4 VP) {
    this->roof.draw(VP);
    this->base.draw(VP);

    this->player.draw(VP);
    this->score_display.draw(VP);
    this->life_display.draw(VP);

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

    this->firebeams.erase(std::remove_if(this->firebeams.begin(), this->firebeams.end(), filter_7), this->firebeams.end());
    for (auto it = this->firebeams.begin(); it != this->firebeams.end(); it++)
        it->draw(VP);

    this->lasers.erase(std::remove_if(this->lasers.begin(), this->lasers.end(), filter_8), this->lasers.end());
    for (auto it = this->lasers.begin(); it != this->lasers.end(); it++)
        it->draw(VP);

    this->waterballs.erase(std::remove_if(this->waterballs.begin(), this->waterballs.end(), filter_9), this->waterballs.end());
    for (auto it = this->waterballs.begin(); it != this->waterballs.end(); it++)
        it->draw(VP);

    this->shields.erase(std::remove_if(this->shields.begin(), this->shields.end(), filter_10), this->shields.end());
    for (auto it = this->shields.begin(); it != this->shields.end(); it++)
        it->draw(VP);

}

void Engine::tick() {
    this->counter++;
    this->player.tick();
    this->score_display = Number_display(FRAME - 3.0f, CEILING + 1.0f, this->score);
    this->life_display = Number_display(FRAME + 3.0f, CEILING + 1.0f, this->player.lives);

    // Produce stuffs
    if(counter%942 == 7)
        this->magnets.push_back(Magnet(FRAME + rand()%ARENA_WIDTH, SAFE_FLOOR + rand()%ARENA_HEIGHT));
    if((counter%67) == 7)
        this->coins.push_back(Coin(FRAME + ARENA_WIDTH + rand()%ARENA_WIDTH, SAFE_FLOOR + rand()%ARENA_HEIGHT, 0));
    if((counter%127) == 7)
        this->coins.push_back(Coin(FRAME + ARENA_WIDTH + rand()%ARENA_WIDTH, SAFE_FLOOR + rand()%ARENA_HEIGHT, 1));
    if((counter%259) == 7)
        this->coins.push_back(Coin(FRAME + ARENA_WIDTH + rand()%ARENA_WIDTH, SAFE_FLOOR + rand()%ARENA_HEIGHT, 2));
    if(counter%401 == 7)
        this->boomerangs.push_back(Boomerang(FRAME + ARENA_WIDTH + rand()%ARENA_WIDTH/2, SAFE_FLOOR + ARENA_HEIGHT, COLOR_ORANGE));
    if(counter%629 == 7)
        this->boomerangs.push_back(Boomerang(FRAME + ARENA_WIDTH + rand()%ARENA_WIDTH/2, SAFE_FLOOR + rand()%ARENA_HEIGHT, COLOR_ORANGE));
    if((counter%512) == 7)
        this->hearts.push_back(Heart(FRAME + ARENA_WIDTH + rand()%ARENA_WIDTH, SAFE_FLOOR + rand()%ARENA_HEIGHT));
    if((counter%600) == 7)
        this->missiles.push_back(Missile(FRAME + ARENA_WIDTH, SAFE_FLOOR + rand()%ARENA_HEIGHT, COLOR_RED));
    if((counter%800) == 7)
        this->dragons.push_back(Dragon(FRAME + ARENA_WIDTH + rand()%ARENA_WIDTH, SAFE_FLOOR + rand()%ARENA_HEIGHT));
    if((counter%503) == 7)
        this->firebeams.push_back(Firebeam(FRAME + ARENA_WIDTH, SAFE_FLOOR + rand()%ARENA_HEIGHT, COLOR_RED));
    if((counter%209) == 7)
        this->lasers.push_back(Laser(FRAME + ARENA_WIDTH/2 + rand()%ARENA_WIDTH, SAFE_FLOOR + rand()%ARENA_HEIGHT, M_PI/(rand()%24)));
    if((counter%611) == 7)
        this->shields.push_back(Shield(FRAME + ARENA_WIDTH/2 + rand()%ARENA_WIDTH, SAFE_FLOOR + rand()%ARENA_HEIGHT));

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
    for (auto it = this->firebeams.begin(); it != this->firebeams.end(); it++)
        it->tick();
    for (auto it = this->lasers.begin(); it != this->lasers.end(); it++)
        it->tick();
    for (auto it = this->waterballs.begin(); it != this->waterballs.end(); it++)
        it->tick();
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
        if(this->player.shoot(this->counter)) {
            this->waterballs.push_back(Waterball(this->player.position.x + 0.1f, this->player.position.y - 0.1f));
            this->waterballs.push_back(Waterball(this->player.position.x, this->player.position.y));
            this->waterballs.push_back(Waterball(this->player.position.x - 0.1f, this->player.position.y + 0.1f));
        }
    }
}

int Engine::get_life() {
        return this->player.lives;
}

void Engine::collider() {
    // Detect coin capture
    for (auto it = this->coins.begin(); it != this->coins.end(); it++) {
        if(detect_collision(player.box(),it->box()))
        {
            it->position.y -= 100;
            score++;
            score+=it->type;
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
    // Detect collision with missile
    for (auto it = this->dragons.begin(); it != this->dragons.end(); it++) {
        if(detect_collision(player.box(), it->box())){
            player.die();
            it->position.y = -100;
        }
    }

    // Detect collision from firebeam
    for (auto it = this->firebeams.begin(); it != this->firebeams.end(); it++) {
        if(detect_collision(player.box(), it->box())){
            player.die();
            it->position.y = -100;
        }
    }

    // Detect collision from Laser
    for (auto it = this->lasers.begin(); it != this->lasers.end(); it++) {
        if(it->collision(player.box())){
            player.die();
            it->position.y = -100;
        }
    }

    // Detect collision from waterballs
    for (auto jt = this->waterballs.begin(); jt != this->waterballs.end(); jt++) {
        for (auto it = this->lasers.begin(); it != this->lasers.end(); it++) {
            if(it->collision(jt->box())){
                jt->position.y = GRAVE;
                it->position.y = -100;
            }
        }
    }

    // Detect collision from shield
    for (auto it = this->shields.begin(); it != this->shields.end(); it++) {
        if(detect_collision(player.box(), it->box())){
            player.shield = true;
            it->position.y = -100;
        }
    }

}
