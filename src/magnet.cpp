#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->count = 0;
    this->life = rand() % 20;

    // Our vertices. Three consecutive floats give a vertex; Three consecutive vertices give a triangle.
    // A rectangle has 2 triangles
    static const GLfloat vertex_buffer_data[] = {
        // Lower rectangle
       -width/2.0f,-height/2.0f, 0.0f, // triangle 1 : begin
       -width/2.0f,-height/2.0f + thickness, 0.0f,
        width/2.0f,-height/2.0f + thickness, 0.0f, // triangle 1 : end
        width/2.0f,-height/2.0f, 0.0f, // triangle 2 : begin
       -width/2.0f,-height/2.0f, 0.0f,
        width/2.0f,-height/2.0f + thickness, 0.0f, // triangle 2 : end

        // Left rectangle
       -width/2.0f + thickness,-height/2.0f + thickness, 0.0f, // triangle 1 : begin
       -width/2.0f,-height/2.0f + thickness, 0.0f,
       -width/2.0f, height/2.0f - thickness/2.0f, 0.0f, // triangle 1 : end
       -width/2.0f + thickness, height/2.0f - thickness/2.0f, 0.0f, // triangle 2 : begin
       -width/2.0f, height/2.0f - thickness/2.0f, 0.0f,
       -width/2.0f + thickness,-height/2.0f + thickness, 0.0f, // triangle 2 : end

       // Left rectangle
       width/2.0f - thickness,-height/2.0f + thickness, 0.0f, // triangle 1 : begin
       width/2.0f,-height/2.0f + thickness, 0.0f,
       width/2.0f, height/2.0f - thickness/2.0f, 0.0f, // triangle 1 : end
       width/2.0f - thickness, height/2.0f - thickness/2.0f, 0.0f, // triangle 2 : begin
       width/2.0f, height/2.0f - thickness/2.0f, 0.0f,
       width/2.0f - thickness,-height/2.0f + thickness, 0.0f, // triangle 2 : end
   };

    static const GLfloat vertex_buffer_data_2[] = {
        // Left rectangle
       -width/2.0f + thickness, height/2.0f, 0.0f, // triangle 1 : begin
       -width/2.0f, height/2.0f, 0.0f,
       -width/2.0f, height/2.0f - thickness/2.0f, 0.0f, // triangle 1 : end
       -width/2.0f + thickness, height/2.0f - thickness/2.0f, 0.0f, // triangle 2 : begin
       -width/2.0f, height/2.0f - thickness/2.0f, 0.0f,
       -width/2.0f + thickness,height/2.0f - thickness/2.0f + thickness, 0.0f, // triangle 2 : end
       // Left rectangle
       -width/2.0f + thickness,-height/2.0f + thickness, 0.0f, // triangle 1 : begin
       -width/2.0f,-height/2.0f + thickness, 0.0f,
       -width/2.0f, height/2.0f - thickness/2.0f, 0.0f, // triangle 1 : end
       -width/2.0f + thickness, height/2.0f - thickness/2.0f, 0.0f, // triangle 2 : begin
       -width/2.0f, height/2.0f - thickness/2.0f, 0.0f,
       -width/2.0f + thickness,-height/2.0f + thickness, 0.0f, // triangle 2 : end
       // Right rectangle
        width/2.0f - thickness,-height/2.0f + thickness, 0.0f, // triangle 1 : begin
        width/2.0f,-height/2.0f + thickness, 0.0f,
        width/2.0f, height/2.0f - thickness/2.0f, 0.0f, // triangle 1 : end
        width/2.0f - thickness, height/2.0f - thickness/2.0f, 0.0f, // triangle 2 : begin
        width/2.0f, height/2.0f - thickness/2.0f, 0.0f,
        width/2.0f - thickness,-height/2.0f + thickness, 0.0f, // triangle 2 : end
       // Right rectangle
        width/2.0f - thickness,-height/2.0f + thickness, 0.0f, // triangle 1 : begin
        width/2.0f,-height/2.0f + thickness, 0.0f,
        width/2.0f, height/2.0f - thickness/2.0f, 0.0f, // triangle 1 : end
        width/2.0f - thickness, height/2.0f - thickness/2.0f, 0.0f, // triangle 2 : begin
        width/2.0f, height/2.0f - thickness/2.0f, 0.0f,
        width/2.0f - thickness,-height/2.0f + thickness, 0.0f, // triangle 2 : end
    };
    this->object[1] = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data, COLOR_RED, GL_FILL);
    // this->object[2] = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data_2, COLOR_RED, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of  around which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -width, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[1]);
    // draw3DObject(this->object[2]);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bool Magnet::tick() {
    return this->count++ <= this->life;
}
