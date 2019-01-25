#include "heart.h"
#include "main.h"

Heart::Heart(float x, float y) {
    this->position = glm::vec3(x, y, 0);

    // A rectangle has 2 triangles
    static const GLfloat vertex_buffer_data[] = {
        width/2.0f, height/2.0f, 0.0f, // triangle 1 : begin
       -width/2.0f,        0.0f, 0.0f,
        width/2.0f,        0.0f, 0.0f, // triangle 1 : end
       -width/2.0f, height/2.0f, 0.0f, // triangle 2 : begin
       -width/2.0f,        0.0f, 0.0f,
        width/2.0f,        0.0f, 0.0f, // triangle 2 : end
       -width/2.0f,        0.0f, 0.0f, // triangle 3 : begin
        width/2.0f,        0.0f, 0.0f,
              0.0f,-height/2.0f, 0.0f  // triangle 3 : end
   };

    this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Heart::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of  around which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -width, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Heart::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Heart::tick() {
    // X Axis
    this->position.x -= this->speed_x;
}

bounding_box_t Heart::box() {
    bounding_box_t box = {this->position.x,this->position.y,width,height};
    return box;
}
