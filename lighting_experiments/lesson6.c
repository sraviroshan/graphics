//
// This code was created by Jeff Molofee '99 (ported to Linux/GLUT by Richard Campbell '99)
//
// If you've found this code useful, please let me know.
//
// Visit me at www.demonews.com/hosted/nehe 
// (email Richard Campbell at ulmont@bellsouth.net)
//
#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <unistd.h>     // needed to sleep.

/* ascii code for the escape key */
#define ESCAPE 27


/* The number of our GLUT window */
int window; 
GLdouble normal_buffer[3];

/* floats for x rotation, y rotation, z rotation */
int xrot, yrot, zrot;

/* storage for one texture  */
int texture[1];

/* Image type - contains height, width, and data */
struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
typedef struct Image Image;

// quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.  
// See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.
int ImageLoad(char *filename, Image *image) {
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp;                          // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL)
    {
	printf("File Not Found : %s\n",filename);
	return 0;
    }
    
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);

    // read the width
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
	printf("Error reading width from %s.\n", filename);
	return 0;
    }
    printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height 
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
	printf("Error reading height from %s.\n", filename);
	return 0;
    }
    printf("Height of %s: %lu\n", filename, image->sizeY);
    
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = image->sizeX * image->sizeY * 3;

    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
	printf("Error reading planes from %s.\n", filename);
	return 0;
    }
    if (planes != 1) {
	printf("Planes from %s is not 1: %u\n", filename, planes);
	return 0;
    }

    // read the bpp
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
	printf("Error reading bpp from %s.\n", filename);
	return 0;
    }
    if (bpp != 24) {
	printf("Bpp from %s is not 24: %u\n", filename, bpp);
	return 0;
    }
	
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);

    // read the data. 
    image->data = (char *) malloc(size);
    if (image->data == NULL) {
	printf("Error allocating memory for color-corrected image data");
	return 0;	
    }

    if ((i = fread(image->data, size, 1, file)) != 1) {
	printf("Error reading image data from %s.\n", filename);
	return 0;
    }

    for (i=0;i<size;i+=3) { // GRB (swap first and second colours)
	temp = image->data[i];
	image->data[i] = image->data[i+1];
	image->data[i+1] = temp;
    unsigned int a = (unsigned char) image->data[i];
    }
    
    // we're done.
    return 1;
}
    
// Load Bitmaps And Convert To Textures
void LoadGLTextures() {	
    // Load Texture
    Image *image1;
    
    // allocate space for texture
    image1 = (Image *) malloc(sizeof(Image));
    if (image1 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }

    if (!ImageLoad("Data/lesson6/torso_front.bmp", image1)) {
	exit(1);
    }        

    // Create Texture	
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    unsigned char pixels[] = {
        0, 0, 0, 255, 255, 255,
        255, 255, 255, 0, 0, 0
    };
    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
    //glTexImage2D(GL_TEXTURE_2D, 0, 3, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
};

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
{
    LoadGLTextures();				// Load The Texture(s) 
    glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);	// Clear The Background Color To Blue 
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    glEnable(GL_NORMALIZE);			//Enable force normalization of normals by open gl
    glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				// Reset The Projection Matrix
    
    //gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window
    
    glMatrixMode(GL_MODELVIEW);
    
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 }; //
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; //this is the most important component as in "color" of the light
	GLfloat light_specular[] = { 0.0, 1.0, 0.0, 1.0 };
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
    if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
	Height=1;

    glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
    
}

//components 1,2,3 are x,y,z respectively
void calculate_normal(GLdouble a1, GLdouble a2, GLdouble a3,
						  GLdouble b1, GLdouble b2, GLdouble b3,
						  GLdouble c1, GLdouble c2, GLdouble c3,
						  GLdouble * normal){
	GLdouble u1 = b1 - a1;
	GLdouble u2 = b2 - a2;
	GLdouble u3 = b3 - a3;

	GLdouble v1 = c1 - b1;
	GLdouble v2 = c2 - b2;
	GLdouble v3 = c3 - b3;

    normal[0] = (u2*v3 - u3*v2);
    normal[1] = (u3*v1 - u1*v3);
    normal[2] = (u1*v2 - u2*v1); //done
}

/* The main drawing function. */
void DrawGLScene()
{
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
    glLoadIdentity();				// Reset The View

    /**********/
    GLfloat light_position[] = { 0.0, 10.0, 0.0, 1.0 }; //last is zero means directional
														//last non-zero means positional with omni directional
														//use spotlight functionalilty to emit in a cone
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
	GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    /**********/

    glTranslatef(0.0f,0.0f,-5.0f);              // move 5 units into the screen.
    
    glRotatef(xrot,1.0f,0.0f,0.0f);		// Rotate On The X Axis
    glRotatef(yrot,0.0f,1.0f,0.0f);		// Rotate On The Y Axis
    glRotatef(zrot,0.0f,0.0f,1.0f);		// Rotate On The Z Axis
    
    

    glBindTexture(GL_TEXTURE_2D, texture[0]);   // choose the texture to use.

    glBegin(GL_QUADS);		                // begin drawing a cube
    
    // Front Face (note that the texture's corners have to match the quad's corners)
    GLdouble a[] = {1, 0, 0};
   GLdouble b[] = {0, 0, -1};
   GLdouble c[] = {-1, 0, 0};
   GLdouble d[] = {0, 0, 1};
   GLdouble e[] = {0, 1, 0};
   GLdouble f[] = {0, -1, 0};
   
   GLfloat mat_specular[] = { 0.0, 1.0, 0.0, 1.0 };
   GLfloat mat_shininess[] = { 120.0 };
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   

   calculate_normal(-1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f, normal_buffer);
   glNormal3dv(normal_buffer);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
    
    // Back Face

    calculate_normal(-1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, normal_buffer);
    glNormal3dv(normal_buffer);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
	
    // Top Face

    calculate_normal(-1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f, normal_buffer);
    glNormal3dv(normal_buffer);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
    
    // Bottom Face  
    
    calculate_normal(-1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f, normal_buffer);
    glNormal3dv(normal_buffer);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
    
    // Right face

    calculate_normal( 1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f, normal_buffer);
    glNormal3dv(normal_buffer);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
    
    // Left Face
    
    calculate_normal(-1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, normal_buffer);
    glNormal3dv(normal_buffer);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
    
    glEnd();                                    // done with the polygon.

    // since this is double buffered, swap the buffers to display what just got drawn.
    glutSwapBuffers();
}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y) 
{
    /* avoid thrashing this procedure */
    usleep(100);

    /* If escape is pressed, kill everything. */
    if (key == ESCAPE) 
    { 
	/* shut down our window */
	glutDestroyWindow(window); 
      
      /* exit the program...normal termination. */
	exit(0);                   
    }
    else if (key == 'x') 
    { 
        xrot = (xrot+10) % 360;
    }
    else if (key == 'y') 
    { 
        yrot = (yrot+10) % 360;
    }
    else if (key == 'z') 
    { 
        zrot = (zrot+10) % 360;
    }
    else if (key == 'e') 
    { 
        glEnable(GL_LIGHTING);
    }
    else if (key == 'd') 
    { 
        glDisable(GL_LIGHTING);
    }
    else if (key == '1') 
    { 
        glEnable(GL_LIGHT0);
    }
    else if (key == '2') 
    { 
        glDisable(GL_LIGHT0);
    }
}

int main(int argc, char **argv) 
{  
    /* Initialize GLUT state - glut will take any command line arguments that pertain to it or 
       X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */  
    glutInit(&argc, argv);  

    /* Select type of Display mode:   
     Double buffer 
     RGBA color
     Alpha components supported 
     Depth buffer */  
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  

    /* get a 640 x 480 window */
    glutInitWindowSize(640, 480);  

    /* the window starts at the upper left corner of the screen */
    glutInitWindowPosition(0, 0);  

    /* Open a window */  
    window = glutCreateWindow("Jeff Molofee's GL Code Tutorial ... NeHe '99");  

    /* Register the function to do all our OpenGL drawing. */
    glutDisplayFunc(&DrawGLScene);  

    /* Go fullscreen.  This is as soon as possible. */
    glutFullScreen();

    /* Even if there are no events, redraw our gl scene. */
    glutIdleFunc(&DrawGLScene);

    /* Register the function called when our window is resized. */
    glutReshapeFunc(&ReSizeGLScene);

    /* Register the function called when the keyboard is pressed. */
    glutKeyboardFunc(&keyPressed);

    /* Initialize our window. */
    InitGL(640, 480);
  
    /* Start Event Processing Engine */  
    glutMainLoop();  

    return 1;
}

