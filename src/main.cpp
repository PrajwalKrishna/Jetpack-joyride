#include "main.h"
#include "coin.h"
#include "constant.h"
#include "platform.h"
#include "player.h"
#include "timer.h"
#include <unistd.h>
#include "laser.h"
#include "firebeam.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Player player;
int points = 0;
Platform platform;
Coin coin[100];

Laser laser;
Firebeam firebeam;

float screen_zoom = 0.5, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 90;
float origin = 0.0f;

float frame = 0.0f;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( frame, 0, 1);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (frame, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    player.draw(VP);
    platform.draw(VP);
    laser.draw(VP);
    firebeam.draw(VP);

    // Coin render
    for(int i=0;i<=20;++i)
        coin[i].draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    if (left) {
        player.move(0);
    }
    if (right) {
      player.move(1);
    }
    if(space) {
      player.tickUp();
    }
}

void tick_elements() {
    player.tick();
    for(int i=0;i<=20;++i)
        coin[i].tick();

    laser.tick();
    firebeam.tick();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    player = Player(-7, FLOOR + 2.5f, COLOR_RED);
    platform = Platform(-8, FLOOR, COLOR_GREEN);
    laser = Laser(4, FLOOR + 9, M_PI/2, COLOR_GREEN);
    firebeam = Firebeam(0 ,0 , COLOR_YELLOW);

    for(int i=0;i<=20;++i)
    {
        int random = rand()%5;
        coin[i] = Coin(2.0+i*4,random- 2.0,COLOR_YELLOW);
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = WINDOW_WIDTH;
    int height = WINDOW_HEIGHT;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            // Detect collision from Laser
            if(laser.collision(player.box())) {
                    player.die();
            }

            // Detect collision with firebeam
            if(detect_collision(player.box(), firebeam.box())){
                player.die();
            }

            // Detect coin capture
            for(int i=0; i<20 ; i++)
            {
                if(detect_collision(player.box(),coin[i].box()))
                {
                    coin[i].position.y -= 200;
                    points++;
                    printf("Points earned = %d\n",points);
                }
            }

            tick_elements();
            tick_input(window);
            frame += SCREEN_SPEED;
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
        // Sleep for CPU freeup
        usleep(10000);
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
