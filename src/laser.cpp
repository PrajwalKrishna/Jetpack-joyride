#include "firebox.h"
#include "laser.h"
#include "main.h"


Laser::Laser(float x, float y, double theta, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;

    for(int i=0;i < num; i++) {
        firebox[i] = Firebox(cos(theta) * i * 0.3, sin(theta) * i * 0.3, color);
    }

   //  // Our vertices. Three consecutive floats give a vertex; Three consecutive vertices give a triangle.
   //  // A rectangle has 2 triangles
   //  static const GLfloat vertex_buffer_data[] = {
   //      width/2, height/2, 0.0f, // triangle 1 : begin
   //     -width/2, height/2, 0.0f,
   //      width/2,-height/2, 0.0f, // triangle 1 : end
   //     -width/2, height/2, 0.0f, // triangle 2 : begin
   //     -width/2,-height/2, 0.0f,
   //      width/2,-height/2, 0.0f, // triangle 2 : end
   // };
   //
   //  this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Laser::draw(glm::mat4 VP) {
    // Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of  around which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -width, 0));
    // Matrices.model *= (translate * rotate);
    // glm::mat4 MVP = VP * Matrices.model;
    // glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->object);

    for(int i=0; i < num; i++) {
        firebox[i].draw(VP * translate);
    }
}

void Laser::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Laser::tick() {
    // this->rotation += speed;
    // this->position.x -= speed/100;
    // this->position.y -= speed;
}

bool Laser::collision(bounding_box_t player) {
    for(int i=0;i < num; i++) {
        bounding_box_t player_local = { player.x - this->position.x, player.y - this->position.y, player.width, player.height};
        if(detect_collision(player_local, firebox[i].box())){
            // printf("%f %f \n", player.x, firebox[i].position.x);
            printf("Collide = %d\n",i);
            return true;
        }
    }
    return false;
};
