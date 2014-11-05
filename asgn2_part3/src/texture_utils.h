#ifndef _TEXTURE_UTILS_
#define _TEXTURE_UTILS_

/* Image type - contains height, width, and data */
class Image {
public:
  	Image();
  	~Image();
  	unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};

class Texture{
	GLuint texture_id;
	std::string filename;
	Image *image;
public: 
	Texture(GLuint tex_id, std::string fname);
	~Texture();
	int generate();
	int generate(GLenum format, bool white_is_transparent);
  int generate_white_is_transparent();
};

int ImageLoad(std::string filename, Image *image, bool white_is_transparent);

void calculate_normal(GLdouble a1, GLdouble a2, GLdouble a3,
                          GLdouble b1, GLdouble b2, GLdouble b3,
                          GLdouble c1, GLdouble c2, GLdouble c3,
                          GLdouble * normal);

void set_optimus_material();
void set_wall_material();
void set_glass_material();

//stores state of open gl animation frame
typedef struct state_t{
  int camera_no;

  //optimus_t variables. refer by optimus.<variable_name>
  int rotation_angle; //angle for rotation about axis
  int body_rotation_x; //rotate body about x axis
  int body_rotation_y; //rotate body about x axis
  int body_rotation_z; //rotate body about x axis
  int back_weel_slab_rotation; //rotation of back weel slab bout x axis
  int solder_rotation_zl; //left solder rotation angle about z axis
  int solder_rotation_yl; //left solder rotation angle about y axis
  int solder_rotation_xl; // left solder rotation angle about x axis
  int elbows_rotation_l; //left elbows rotarion angle about z axis
  int solder_rotation_zr; // right solder rotation angle about z axis
  int solder_rotation_yr; // right solder rotation angle about y axis
  int solder_rotation_xr; // right solder rotation angle about x axis
  int elbows_rotation_r; //right elbows rotarion angle about z axis
  int waist_rotation; // rotation of waist about y axis
  int upper_body_rotation; //rotation of upper body about x axis
  int lower_leg_rotation_l; //rotation of left lower leg about x axis
  int lower_leg_rotation_r; //rotation of right lower leg about x axis
  int front_weel_slab_rotation; //rotarion of slab contain weel around x axis
  int uper_leg_rotation_xl; //rotation of uper left leg about x axis
  int uper_leg_rotation_zl; //rotation of uper left leg about z axis
  int uper_leg_rotation_xr; //rotation of uper right leg about x axis
  int uper_leg_rotation_zr; //rotation of uper right leg about z axis
  int hood_feet_rotation_xl1; //rotation of left whole feet about x axis
  int hood_feet_rotation_xl2; //rotation of left uper feet about x axis
  int hood_feet_rotation_xr1; //rotation of right whole feet about x axis
  int hood_feet_rotation_xr2; //rotation of right uper feet about x axis
  float throat_translate_y; //translation of throat along y axis
  int truck_ceiling_rotation; //rotation of truck ceilig about x axis
  int front_glass_rotation; //totation of fron glass bout x axis
  int side_gate_rotation; //side gate rotation about x axis
  int weel_rotation; //roatation of weel about z axis
  float forword_backword_movement_z; // translate whole body along z axis
  float forword_backword_movement_x; // translate whole body along x axis

  float vertical_movement; // vertical movement of transformer(independent)

  bool headlight_on;  // whether headlight on (decide which texture to load)


  
} struct_t;
#endif