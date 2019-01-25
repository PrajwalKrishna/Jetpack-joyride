// #include "dashboard.h"
// #include "seven_segment_display.h"
// #include "main.h"
//
// Dashboard::Dashboard(float x, float y, double theta) {
//     this->position = glm::vec3(x, y, 0);
//     this->rotation = 0;
//
//     this->score
// }
//
// void Dashboard::draw(glm::mat4 VP) {
//     Matrices.model = glm::mat4(1.0f);
//     glm::mat4 translate = glm::translate (this->position);    // glTranslatef
//     glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
//     // No need as coords centered at 0, 0, 0 of  around which we waant to rotate
//     // rotate          = rotate * glm::translate(glm::vec3(0, -width, 0));
//     Matrices.model *= (translate * rotate);
//     glm::mat4 MVP = VP * Matrices.model;
//     // glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
//     // draw3DObject(this->object);
//
//     for(int i=0; i < num; i++) {
//         firebox[i].draw(MVP);
//     }
// }
//
// void Dashboard::set_position(float x, float y) {
//     this->position = glm::vec3(x, y, 0);
// }
//
// void Dashboard::tick() {
//     // this->rotation += speed;
//     // this->position.x -= speed/100;
//     // this->position.y -= speed;
// }
