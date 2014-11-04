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
	int generate(GLenum format);
};

int ImageLoad(std::string filename, Image *image);

void calculate_normal(GLdouble a1, GLdouble a2, GLdouble a3,
                          GLdouble b1, GLdouble b2, GLdouble b3,
                          GLdouble c1, GLdouble c2, GLdouble c3,
                          GLdouble * normal);

void set_optimus_material();
void set_wall_material();
void set_glass_material();

#endif