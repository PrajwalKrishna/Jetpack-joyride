#include "player.h"
#include "constant.h"
#include "main.h"

Player::Player(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    speed_x = 0.03;
    // Our vertices. Three consecutive floats give a vertex; Three consecutive vertices give a triangle.
    // A rectangle has 2 triangles
    static const GLfloat vertex_buffer_data[] = {
         width/2, height/2, 0.0f, // triangle 1 : begin
        -width/2, height/2, 0.0f,
         width/2,-height/2, 0.0f, // triangle 1 : end
        -width/2, height/2, 0.0f, // triangle 2 : begin
        -width/2,-height/2, 0.0f,
         width/2,-height/2, 0.0f, // triangle 2 : end
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Player::move( int direction) {
  // zero = left
  // one = right
  if(direction)
    this->position.x += speed_x;
  else if(this->position.x > -8.0)
    this->position.x -= speed_x;
}

void Player::tick() {
    this->speed_x += 0.0001;

    // Move player along screen
    this->position.x += SCREEN_SPEED;

    if(this->position.y > FLOOR + height/2)
      this->speed += GRAVITY;
    else
      this->speed = 0;
    this->position.y -= speed;
}

void Player::tickUp() {
  if(this->position.y < CEILING - height/2 - 0.5)
    this->position.y += 0.5;
  else if(this->position.y <= CEILING - height/2){
    this->position.y += CEILING - height/2 - this->position.y;
    this->speed = 0;
 }
  // else
  //   this->speed = 0;
  printf("Player %f %f\n",this->position.y, CEILING);
}

bounding_box_t Player::box() {
    bounding_box_t box = {this->position.x, this->position.y, width, height};
    return box;
}

void Player::die() {
    this->lives--;
    printf("Player died \t Lives left = %d\n",this->lives);
}
