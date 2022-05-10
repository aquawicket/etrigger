///// GLImage.h /////////////////////////////////////////////////////////////////////
//
// This is a simple class built on top of OpenGL that manages drawing images 
// in a higher-level and quicker way.
//
/////////////////////////////////////////////////////////////////////////////////////

#ifndef GLIMAGE_H
#define GLIMAGE_H
 
// include OpenGL
#ifdef __WXMAC__
#include "OpenGL/gl.h"
#else
#include <windows.h>
#include <GL/gl.h>
#endif

#include <cmath> 
#include "wx/image.h"
#include "wx/wx.h"

class Image;
 
//////////////
class GLImage
{
public:

	GLImage(wxString path);
	GLImage(const char** xpm);
	~GLImage();
	void SetImage(Image* image);
	void Render();
    void SetFlip(bool x, bool y);
    void Move(int x, int y);
    void SetHotspot(int x, int y);
    void Scale(float x, float y);
    void Scale(float k);
    void Rotate(int angle);

	Image* image;

    int x;
	int y;
	int width;
	int height;
	int angle;
	int hotspotX;
	int hotspotY;
    float xscale;
	float yscale;
    bool xflip;
	bool yflip;  
};

///////////
class Image
{
    GLuint* ID;
    
public:
 
	/*
	 * it is preferable to use textures that are a power of two. this loader will automatically
	 * resize texture to be a power of two, filling the remaining areas with black.
	 * width/height are the width of the actual loaded image.
	 * textureWidth/Height are the total width of the texture, including black filling.
	 * tex_coord_x/y are the texture coord parameter you must give OpenGL when rendering
	 * to get only the image, without the black filling.
	 */
    int width, height, textureWidth, textureHeight;
    float tex_coord_x, tex_coord_y;
    
    GLuint* getID();
    Image();
    Image(wxString path);
	Image(const char** xpm);
    ~Image();
    void load(wxString path);
	void load(const char** xpm);
        
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////
GLuint* loadImage(wxString path, int* imageWidth, int* imageHeight, int* textureWidth, int* textureHeight);
GLuint* loadImage(const char** xpm, int* imageWidth, int* imageHeight, int* textureWidth, int* textureHeight);
 
 
#endif //GLIMAGE