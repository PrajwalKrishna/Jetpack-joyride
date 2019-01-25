#include "seven_segment_display.h"
#include "main.h"

Segment::Segment(float x, float y,float rotation, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = rotation;

   static const GLfloat vertex_buffer_data[] = {
       SEGMENT_LENGTH/2, THICKNESS/2, 0.0f, // triangle 1 : begin
      -SEGMENT_LENGTH/2, THICKNESS/2, 0.0f,
      -SEGMENT_LENGTH/2,-THICKNESS/2, 0.0f, // triangle 1 : end
       SEGMENT_LENGTH/2,-THICKNESS/2, 0.0f, // triangle 2 : begin
      -SEGMENT_LENGTH/2,-THICKNESS/2, 0.0f,
       SEGMENT_LENGTH/2, THICKNESS/2, 0.0f, // triangle 2 : end
   };
   this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Segment::draw(glm::mat4 VP) {
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

void Segment::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


Seven_segment_display::Seven_segment_display(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

}

void Seven_segment_display::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of  around which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // for(int i=0;i<7;i++)
        // draw3DObject(this->object[i]);
}

void Seven_segment_display::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Seven_segment_display::tick() {
    // this->rotation += speed;
    // this->position.x -= speed/100;
    // // this->position.y -= speed;
}
