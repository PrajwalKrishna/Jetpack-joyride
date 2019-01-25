#include "seven_segment_display.h"
#include "main.h"

Segment::Segment(float x, float y,float rotation, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = rotation;

   static const GLfloat vertex_buffer_data[] = {
       SEGMENT_LENGTH/2.0f, THICKNESS/2.0f, 0.0f, // triangle 1 : begin
      -SEGMENT_LENGTH/2.0f, THICKNESS/2.0f, 0.0f,
      -SEGMENT_LENGTH/2.0f,-THICKNESS/2.0f, 0.0f, // triangle 1 : end
       SEGMENT_LENGTH/2.0f,-THICKNESS/2.0f, 0.0f, // triangle 2 : begin
      -SEGMENT_LENGTH/2.0f,-THICKNESS/2.0f, 0.0f,
       SEGMENT_LENGTH/2.0f, THICKNESS/2.0f, 0.0f, // triangle 2 : end
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

const double vertex[7][3] = {
    {                0.0f, SEGMENT_LENGTH  , 0      },
    { SEGMENT_LENGTH/2.0f, SEGMENT_LENGTH/2.0f, M_PI/2.0f },
    { SEGMENT_LENGTH/2.0f,-SEGMENT_LENGTH/2.0f, M_PI/2.0f },
    {                0.0f,-SEGMENT_LENGTH  , 0      },
    {-SEGMENT_LENGTH/2.0f,-SEGMENT_LENGTH/2.0f, M_PI/2.0f },
    {-SEGMENT_LENGTH/2.0f, SEGMENT_LENGTH/2.0f, M_PI/2.0f },
    {            0.0f ,             0.0f, 0      }
};

 const bool decoder[10][7] = {
     {1,1,1,1,1,1,0}, //0
     {0,1,1,0,0,0,0}, //1
     {1,1,0,1,1,0,1}, //2
     {1,1,1,1,0,0,1}, //3
     {0,1,1,0,0,1,1}, //4
     {1,0,1,1,0,1,1}, //5
     {1,0,1,1,1,1,1}, //6
     {1,1,1,0,0,0,0}, //7
     {1,1,1,1,1,1,1}, //8
     {1,1,1,1,0,1,1}  //9
 };

Digit_display::Digit_display(float x, float y, int digit) {
    this->position = glm::vec3(x, y, 0);
    for(int i=0; i<7; i++){
        if(!decoder[digit][i])
            this->segments[i] = Segment(x + vertex[i][0], y + vertex[i][1], vertex[i][2], COLOR_LIGHT_GREEN);
        else
            this->segments[i] = Segment(x + vertex[i][0], y + vertex[i][1], vertex[i][2], COLOR_DARK_GREEN);
    }
}

void Digit_display::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of  around which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    for(int i=0;i<7;i++) {
        this->segments[i].draw(MVP);
    }
}

void Digit_display::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Digit_display::tick() {
    // this->rotation += speed;
    // this->position.x -= speed/100;
    // // this->position.y -= speed;
}

Number_display::Number_display(float x, float y, int num) {
    this->position = glm::vec3(x, y, 0);
    this->count = 0;
    int arr[MAX_DIGITS];

    arr[0] = 0;

    while(num){
        arr[this->count++] = num % 10;
        num /= 10;
    }
    if(this->count == 0)
        this->count++;

    for(int i=this->count-1;i>=0;i--){
        this->digits[i] = Digit_display(x + i * SEGMENT_LENGTH/1.5f, y, arr[i]);
    }
}

void Number_display::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of  around which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    for(int i=0;i<this->count;i++) {
        this->digits[i].draw(MVP);
    }
};

void Number_display::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
