#include "semi_ring.h"
#include "main.h"

Ring::Ring(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = -90;
    speed = 1;
    // Our vertices. Three consecutive floats give a vertex; Three consecutive vertices give a triangle.
    // A rectangle has 2 triangles
    int num = NUM;
    float a,  b;
    for(int i=0;i < num; i++) {
         a = radius * cos(M_PI/num * i);
         b = radius * sin(M_PI/num * i);
        GLfloat temp[] = {
             a + thickness, b + thickness, 0.0f, // triangle 1 : begin
             a - thickness, b + thickness, 0.0f,
             a - thickness, b - thickness, 0.0f, // triangle 1 : end
             a + thickness, b - thickness, 0.0f, // triangle 2 : begin
             a + thickness, b + thickness, 0.0f,
             a - thickness, b - thickness, 0.0f // triangle 2 : end
         };
        this->object[i] = create3DObject(GL_TRIANGLES, 2*3, temp, COLOR_LIGHT_GREEN, GL_FILL);
    }
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0.2, 0.2, 0.9));
    // No need as coords centered at 0, 0, 0 of  around which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -width, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<NUM ; i++)
        draw3DObject(this->object[i]);
}

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ring::tick() {
    this->rotation += speed;
    this->position.x -= speed/100;
    // this->position.y -= speed;
}

bounding_box_t Ring::box() {
    bounding_box_t box = {this->position.x,this->position.y,width,height};
    return box;
}
