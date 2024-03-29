#include "dragon.h"
#include "main.h"

Dragon::Dragon(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->pre_count = 0;

    // Our vertices. Three consecutive floats give a vertex; Three consecutive vertices give a triangle.
    // A rectangle has 2 triangles
    static const GLfloat vertex_buffer_data[] = {
        width/2.0f, height/1.8f, 0.0f, // triangle 1 : begin
       -width/2.0f,        0.0f, 0.0f,
        width/2.0f,-height/1.8f, 0.0f, // triangle 1 : end
              0.0f,        0.0f, 0.0f, // triangle 2 : begin
              0.0f,-height/1.8f, 0.0f,
        width/4.0f,        0.0f, 0.0f, // triangle 2 : end
              0.0f,        0.0f, 0.0f, // triangle 3 : begin
              0.0f, height/1.8f, 0.0f,
        width/4.0f,        0.0f, 0.0f, // triangle 3 : end
   };

    this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, COLOR_BLUE, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of  around which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -width, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bool Dragon::shoot(int counter) {
    if(counter - this->pre_count > 60){
        this->pre_count = counter;
        return true;
    }
    return false;
}


void Dragon::tick(float player_x, float player_y) {
    // Screen motion
    this->position.x += SCREEN_SPEED/3.0f;
    this->position.x -= speed_x;

    this->position.x += (player_x - this->position.x)/300;
    this->position.y += (player_y - this->position.y)/300;

    if(player_y - this->position.y > 0)
        this->rotation = -atan((player_x - this->position.x)/(player_y - this->position.y)) - M_PI/2;
    else
        this->rotation = -atan((player_x - this->position.x)/(player_y - this->position.y)) + M_PI/2;
}

bounding_box_t Dragon::box() {
    bounding_box_t box = {this->position.x,this->position.y,width,height};
    return box;
}
