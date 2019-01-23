#include "digit.h"
#include "main.h"

Digit::Digit(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a vertex; Three consecutive vertices give a triangle.
    // A rectangle has 2 triangles
    static const GLfloat vertex_buffer_data[] = {
         0.0f, 0.0f, 0.0f, // triangle 1 : begin
         0.6f, 0.4f, 0.0f,
         0.6f, 0.0f, 0.0f, // triangle 1 : end
         0.0f, 0.4f, 0.0f, // triangle 2 : begin
         0.6f, 0.4f, 0.0f,
         0.0f, 0.0f, 0.0f, // triangle 2 : end
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Digit::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of  around which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Digit::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Digit::tick() {
    this->rotation += speed;
    this->position.x -= speed/100;
    // this->position.y -= speed;
}
