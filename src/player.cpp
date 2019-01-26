#include "player.h"

#include "main.h"

Player::Player(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed_y = 0;
    speed_x = 0.05;
    // Our vertices. Three consecutive floats give a vertex; Three consecutive vertices give a triangle.
    // A rectangle has 2 triangles
    static const GLfloat vertex_buffer_data[] = {
         width/2.0f, height/2.0f, 0.0f, // triangle 1 : begin
        -width/2.0f, height/2.0f, 0.0f,
         width/2.0f,-height/2.0f, 0.0f, // triangle 1 : end
        -width/2.0f, height/2.0f, 0.0f, // triangle 2 : begin
        -width/2.0f,-height/2.0f, 0.0f,
         width/2.0f,-height/2.0f, 0.0f, // triangle 2 : end
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
  if(direction && this->position.x < FRAME + 8 - speed_x - width/2.0f)
    this->position.x += speed_x;
  else if(this->position.x > FRAME - 8 + speed_x + width/2.0f)
    this->position.x -= speed_x;
}

void Player::tick() {
    // Move player along screen
    this->position.x += SCREEN_SPEED;

    if(this->position.y > FLOOR + height/2.0f)
      this->speed_y -= GRAVITY;
    else
      this->speed_y = 0;
    this->position.y += speed_y;
}

void Player::tickUp() {
  if(this->position.y < CEILING - height/2.0f - 0.5)
    this->position.y += 0.5;
  else if(this->position.y <= CEILING - height/2.0f){
    this->position.y += CEILING - height/2.0f - this->position.y;
    this->speed_y = 0;
 }
}

bounding_box_t Player::box() {
    bounding_box_t box = {this->position.x, this->position.y, width, height};
    return box;
}

void Player::die() {
    this->lives--;
    printf("Player died \t Lives left = %d\n",this->lives);
}

void Player::get_life() {
    this->lives++;
    printf("Player gets life \t Lives left = %d\n",this->lives);
}

void Player::magnetic_motion(float x, float y) {
        this->position.x += (x - this->position.x)/(5 * MAGNETIC_ACCELERATION);
        this->position.y  += (y - this->position.y)/MAGNETIC_ACCELERATION;
}
