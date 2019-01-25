#include "firebox.h"
#include "main.h"

Firebox::Firebox(float x, float y, double theta) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;

    static const GLfloat vertex_buffer_data_2[] = {
         width/2.0f, width/2.0f * sin(theta) + 4 * thickness, 0.0f, // triangle 1 : begin
        -width/2.0f,-width/2.0f * sin(theta), 0.0f,
         width/2.0f, width/2.0f * sin(theta) - 4 * thickness, 0.0f, // triangle 1 : end
        -width/2.0f,-width/2.0f * sin(theta) + 4 * thickness, 0.0f, // triangle 2 : begin
        -width/2.0f,-width/2.0f * sin(theta) - 4 * thickness, 0.0f,
         width/2.0f, width/2.0f * sin(theta), 0.0f, // triangle 2 : end
    };

   static const GLfloat vertex_buffer_data[] = {
        width/2.0f, width/2.0f * sin(theta) + thickness, 0.0f, // triangle 1 : begin
       -width/2.0f,-width/2.0f * sin(theta), 0.0f,
        width/2.0f, width/2.0f * sin(theta) - thickness, 0.0f, // triangle 1 : end
       -width/2.0f,-width/2.0f * sin(theta) + thickness, 0.0f, // triangle 2 : begin
       -width/2.0f,-width/2.0f * sin(theta) - thickness, 0.0f,
        width/2.0f, width/2.0f * sin(theta), 0.0f, // triangle 2 : end
   };
   this->object[0] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_2, COLOR_RED, GL_FILL);
   this->object[1] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);
}

void Firebox::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of  around which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -width, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
}

void Firebox::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Firebox::tick() {
    // this->rotation += speed;
    // this->position.x -= speed/100;
    // this->position.y -= speed;
}

bounding_box_t Firebox::box() {
    bounding_box_t box = {this->position.x,this->position.y,width,height};
    return box;
}
