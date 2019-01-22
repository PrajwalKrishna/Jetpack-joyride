#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    speed_x = 0.01;
    // Our vertices. Three consecutive floats give a vertex; Three consecutive vertices give a triangle.
    // A rectangle has 2 triangles
    static const GLfloat vertex_buffer_data[] = {
         0.0f, 0.0f, 0.0f, // triangle 1 : begin
         1.5f, 4.0f, 0.0f,
         1.5f, 0.0f, 0.0f, // triangle 1 : end
         0.0f, 4.0f, 0.0f, // triangle 2 : begin
         1.5f, 4.0f, 0.0f,
         0.0f, 0.0f, 0.0f, // triangle 2 : end
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
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

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Ball::move( int direction) {
  // zero = left
  // one = right
  if(direction)
    this->position.x += speed_x;
  else if(this->position.x > -8.0)
    this->position.x -= speed_x;
}
void Ball::tick() {
    // this->rotation += speed;
    // printf("X = %f\n",this->position.x);
    this->speed_x += 0.0001;
    // this->position.x += speed_x;

    double FLOOR = -5;
    double GRAVITY = 0.001;
    if(this->position.y > FLOOR)
      this->speed += GRAVITY;
    else
      this->speed = 0;
    // printf("Height = %f\n", this->position.y);
    this->position.y -= speed;
}

void Ball::tickUp() {
  int CELLING = 8;
  if(this->position.y < CELLING)
    this->position.y += 0.1;
}

// void Ball::tickGravity() {
//   int FLOOR = -2;
//   if(this->position.y > FLOOR)
//     this->speed += 0.05;
//   else
//     this->speed = 0;
// }
