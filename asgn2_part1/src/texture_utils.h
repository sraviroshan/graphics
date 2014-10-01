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

#endif