///// GLImage.cpp ///////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////////////

#include "GLImage.h"

///////////////////////////////
GLImage::GLImage(wxString path)
{
	x=0;
    y=0;
	width = 0;
	height = 0;
    hotspotX=0;
    hotspotY=0;
    angle=0;
    
    xscale=1;
    yscale=1;
 
    xflip=false;
    yflip=false;

	image = new Image(path);
	SetImage(image);
}

//////////////////////////////////
GLImage::GLImage(const char** xpm)
{
	x=0;
    y=0;
	width = 0;
	height = 0;
    hotspotX=0;
    hotspotY=0;
    angle=0;
    
    xscale=1;
    yscale=1;
 
    xflip=false;
    yflip=false;

	image = new Image(xpm);
	SetImage(image);
}

///////////////////
GLImage::~GLImage()
{
	delete image;
}

/////////////////////////////////////
void GLImage::SetImage(Image* image)
{
    GLImage::image=image;
	GLImage::width = image->width;
	GLImage::height = image->height;
}
 
//////////////////////////////////////
void GLImage::SetFlip(bool x, bool y)
{
    xflip=x;
    yflip=y;
}
 
///////////////////////////////////////
void GLImage::SetHotspot(int x, int y)
{
    hotspotX=x;
    hotspotY=y;
}
 
/////////////////////////////////
void GLImage::Move(int x, int y)
{
    GLImage::x=x;
    GLImage::y=y;
}
 
//////////////////////////////////////
void GLImage::Scale(float x, float y)
{
    GLImage::xscale=x;
    GLImage::yscale=y;
}
 
/////////////////////////////
void GLImage::Scale(float k)
{
    GLImage::xscale=k;
    GLImage::yscale=k;
}
 
////////////////////////////////
void GLImage::Rotate(int angle)
{
    GLImage::angle=angle;
}
 
///////////////////////
void GLImage::Render()
{
    assert(image!=NULL);
    
    glLoadIdentity();
 
    glTranslatef(x,y,0);
    
    if(xscale!=1 || yscale!=1)
	{
        glScalef(xscale, yscale, 1);
    }
    
    if(angle!=0)
	{
        glRotatef(angle, 0,0,1);   
    }
    
    glBindTexture(GL_TEXTURE_2D, image->getID()[0] );
    
    glBegin(GL_QUADS);
    
	glColor3f(1.0f, 1.0f, 1.0f); 
    glTexCoord2f(xflip? image->tex_coord_x : 0, yflip? 0 : image->tex_coord_y);
    glVertex2f( -hotspotX, -hotspotY );
    
    glTexCoord2f(xflip? 0 : image->tex_coord_x, yflip? 0 : image->tex_coord_y);
    glVertex2f( image->width-hotspotX, -hotspotY );
    
    glTexCoord2f(xflip? 0 : image->tex_coord_x, yflip? image->tex_coord_y : 0);
    glVertex2f( image->width-hotspotX, image->height-hotspotY );
    
    glTexCoord2f(xflip? image->tex_coord_x : 0, yflip? image->tex_coord_y : 0);
    glVertex2f( -hotspotX, image->height-hotspotY );
    
    glEnd();
    
}





//////////////
Image::Image()
{
}
 
///////////////////////////
Image::Image(wxString path)
{
    load(path);
}

///////////////////////////
Image::Image(const char** xpm)
{
    load(xpm);
}

///////////////
Image::~Image()
{
    glDeleteTextures (1, ID);
	delete ID;
}
 
///////////////////////////////
void Image::load(wxString path)
{
    ID=loadImage(path, &width, &height, &textureWidth, &textureHeight);
    
    tex_coord_x = (float)width/(float)textureWidth;
    tex_coord_y = (float)height/(float)textureHeight;
}

//////////////////////////////////
void Image::load(const char** xpm)
{
    ID=loadImage(xpm, &width, &height, &textureWidth, &textureHeight);
    
    tex_coord_x = (float)width/(float)textureWidth;
    tex_coord_y = (float)height/(float)textureHeight;
}
 
//////////////////////
GLuint* Image::getID()
{
    return ID;
}








//////////////////////////////////////////////////////////////////////////////////////////////////////////
GLuint* loadImage(wxString path, int* imageWidth, int* imageHeight, int* textureWidth, int* textureHeight)
{
	
	GLuint* ID=new GLuint[1];
	glGenTextures( 1, &ID[0] );
	
	glBindTexture( GL_TEXTURE_2D, *ID );
	
	// the first time, init image handlers (remove this part if you do it somewhere else in your app)
	static bool is_first_time = true;
	if(is_first_time)
	{
		wxInitAllImageHandlers();
		
		is_first_time = false;
	}
	
	// check the file exists
	if(!wxFileExists(path))
	{
		wxMessageBox( _("Failed to load resource image") );
		exit(1);	
	}
    
	wxImage* img=new wxImage( path );
	
	(*imageWidth)=img->GetWidth();
	(*imageHeight)=img->GetHeight();
	
	glPixelStorei(GL_UNPACK_ALIGNMENT,   1   );
	
    /*
     * Many graphics card require that textures be power of two.
     * Below is a simple implementation, probably not optimal but working.
     * If your texture sizes are not restricted to power of 2s, you can
     * of course adapt the bit below as needed.
     */
    
	float power_of_two_that_gives_correct_width=std::log((float)(*imageWidth))/std::log(2.0);
	float power_of_two_that_gives_correct_height=std::log((float)(*imageHeight))/std::log(2.0);
	
        // check if image dimensions are a power of two
        if( (int)power_of_two_that_gives_correct_width == power_of_two_that_gives_correct_width &&
            (int)power_of_two_that_gives_correct_height == power_of_two_that_gives_correct_height)
        {
                // note: must make a local copy before passing the data to OpenGL, as GetData() returns RGB 
                // and we want the Alpha channel if it's present. Additionally OpenGL seems to interpret the 
                // data upside-down so we need to compensate for that.
                GLubyte *bitmapData=img->GetData();
                GLubyte *alphaData=img->GetAlpha();
                GLubyte *imageData;
 
                int bytesPerPixel = img->HasAlpha() ?  4 : 3;
 
                int imageSize = (*imageWidth) * (*imageHeight) * bytesPerPixel;
                imageData=(GLubyte *)malloc(imageSize);
 
                int rev_val=(*imageHeight)-1;
 
                for(int y=0; y<(*imageHeight); ++y)
                {
                        for(int x=0; x<(*imageWidth); ++x)
                        {
                                imageData[(x+y*(*imageWidth))*bytesPerPixel+0]=
                                        bitmapData[( x+(rev_val-y)*(*imageWidth))*3];
 
                                imageData[(x+y*(*imageWidth))*bytesPerPixel+1]=
                                        bitmapData[( x+(rev_val-y)*(*imageWidth))*3 + 1];
 
                                imageData[(x+y*(*imageWidth))*bytesPerPixel+2]=
                                        bitmapData[( x+(rev_val-y)*(*imageWidth))*3 + 2];
 
                                if(bytesPerPixel==4) imageData[(x+y*(*imageWidth))*bytesPerPixel+3]=
                                        alphaData[ x+(rev_val-y)*(*imageWidth) ];
                        }//next
                }//next
 
                // if yes, everything is fine
                glTexImage2D(GL_TEXTURE_2D,
                             0,
                             bytesPerPixel,
                             *imageWidth,
                             *imageHeight,
                             0,
                             img->HasAlpha() ?  GL_RGBA : GL_RGB,
                             GL_UNSIGNED_BYTE,
                             imageData);
 
                (*textureWidth)  = (*imageWidth);
                (*textureHeight) = (*imageHeight);
 
                free(imageData);
        }
	else // texture is not a power of two. We need to resize it
	{
		
		int newWidth=(int)std::pow( 2.0, (int)(std::ceil(power_of_two_that_gives_correct_width)) );
		int newHeight=(int)std::pow( 2.0, (int)(std::ceil(power_of_two_that_gives_correct_height)) );
		
		//printf("Unsupported image size. Recommand values: %i %i\n",newWidth,newHeight);   
		
		GLubyte	*bitmapData=img->GetData();
		GLubyte        *alphaData=img->GetAlpha();
		GLubyte	*imageData;
		
		int old_bytesPerPixel = 3;
		int bytesPerPixel = img->HasAlpha() ?  4 : 3;
		
		int imageSize = newWidth * newHeight * bytesPerPixel;
		imageData=(GLubyte *)malloc(imageSize);
		
		int rev_val=(*imageHeight)-1;
		
		for(int y=0; y<newHeight; ++y)
		{
			for(int x=0; x<newWidth; ++x)
			{
				
				if( x<(*imageWidth) && y<(*imageHeight) ){
					imageData[(x+y*newWidth)*bytesPerPixel+0]=
					bitmapData[( x+(rev_val-y)*(*imageWidth))*old_bytesPerPixel + 0];
					
					imageData[(x+y*newWidth)*bytesPerPixel+1]=
						bitmapData[( x+(rev_val-y)*(*imageWidth))*old_bytesPerPixel + 1];
					
					imageData[(x+y*newWidth)*bytesPerPixel+2]=
						bitmapData[( x+(rev_val-y)*(*imageWidth))*old_bytesPerPixel + 2];
					
					if(bytesPerPixel==4) imageData[(x+y*newWidth)*bytesPerPixel+3]=
						alphaData[ x+(rev_val-y)*(*imageWidth) ];
					
				}
				else
				{
					
					imageData[(x+y*newWidth)*bytesPerPixel+0] = 0;
					imageData[(x+y*newWidth)*bytesPerPixel+1] = 0;
					imageData[(x+y*newWidth)*bytesPerPixel+2] = 0;
					if(bytesPerPixel==4) imageData[(x+y*newWidth)*bytesPerPixel+3] = 0;
				}
				
			}//next
		}//next
		
		
		glTexImage2D(GL_TEXTURE_2D,
					 0,
					 img->HasAlpha() ?  4 : 3,
					 newWidth,
					 newHeight,
					 0, 
					 img->HasAlpha() ?  GL_RGBA : GL_RGB, 
					 GL_UNSIGNED_BYTE,
					 imageData);
		
		(*textureWidth)=newWidth;
		(*textureHeight)=newHeight;
		
		free(imageData);
	}
	
	// set texture parameters as you wish
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP/*_TO_EDGE*/);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP/*_TO_EDGE*/);
	
	delete img;
	return ID;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GLuint* loadImage(const char** xpm, int* imageWidth, int* imageHeight, int* textureWidth, int* textureHeight)
{
	
	GLuint* ID=new GLuint[1];
	glGenTextures( 1, &ID[0] );
	
	glBindTexture( GL_TEXTURE_2D, *ID );
	
	// the first time, init image handlers (remove this part if you do it somewhere else in your app)
	static bool is_first_time = true;
	if(is_first_time)
	{
		wxInitAllImageHandlers();
		
		is_first_time = false;
	}
	    
	wxImage* img=new wxImage( xpm );
	
	(*imageWidth)=img->GetWidth();
	(*imageHeight)=img->GetHeight();
	
	glPixelStorei(GL_UNPACK_ALIGNMENT,   1   );
	
    /*
     * Many graphics card require that textures be power of two.
     * Below is a simple implementation, probably not optimal but working.
     * If your texture sizes are not restricted to power of 2s, you can
     * of course adapt the bit below as needed.
     */
    
	float power_of_two_that_gives_correct_width=std::log((float)(*imageWidth))/std::log(2.0);
	float power_of_two_that_gives_correct_height=std::log((float)(*imageHeight))/std::log(2.0);
	
        // check if image dimensions are a power of two
        if( (int)power_of_two_that_gives_correct_width == power_of_two_that_gives_correct_width &&
            (int)power_of_two_that_gives_correct_height == power_of_two_that_gives_correct_height)
        {
                // note: must make a local copy before passing the data to OpenGL, as GetData() returns RGB 
                // and we want the Alpha channel if it's present. Additionally OpenGL seems to interpret the 
                // data upside-down so we need to compensate for that.
                GLubyte *bitmapData=img->GetData();
                GLubyte *alphaData=img->GetAlpha();
                GLubyte *imageData;
 
                int bytesPerPixel = img->HasAlpha() ?  4 : 3;
 
                int imageSize = (*imageWidth) * (*imageHeight) * bytesPerPixel;
                imageData=(GLubyte *)malloc(imageSize);
 
                int rev_val=(*imageHeight)-1;
 
                for(int y=0; y<(*imageHeight); ++y)
                {
                        for(int x=0; x<(*imageWidth); ++x)
                        {
                                imageData[(x+y*(*imageWidth))*bytesPerPixel+0]=
                                        bitmapData[( x+(rev_val-y)*(*imageWidth))*3];
 
                                imageData[(x+y*(*imageWidth))*bytesPerPixel+1]=
                                        bitmapData[( x+(rev_val-y)*(*imageWidth))*3 + 1];
 
                                imageData[(x+y*(*imageWidth))*bytesPerPixel+2]=
                                        bitmapData[( x+(rev_val-y)*(*imageWidth))*3 + 2];
 
                                if(bytesPerPixel==4) imageData[(x+y*(*imageWidth))*bytesPerPixel+3]=
                                        alphaData[ x+(rev_val-y)*(*imageWidth) ];
                        }//next
                }//next
 
                // if yes, everything is fine
                glTexImage2D(GL_TEXTURE_2D,
                             0,
                             bytesPerPixel,
                             *imageWidth,
                             *imageHeight,
                             0,
                             img->HasAlpha() ?  GL_RGBA : GL_RGB,
                             GL_UNSIGNED_BYTE,
                             imageData);
 
                (*textureWidth)  = (*imageWidth);
                (*textureHeight) = (*imageHeight);
 
                free(imageData);
        }
	else // texture is not a power of two. We need to resize it
	{
		
		int newWidth=(int)std::pow( 2.0, (int)(std::ceil(power_of_two_that_gives_correct_width)) );
		int newHeight=(int)std::pow( 2.0, (int)(std::ceil(power_of_two_that_gives_correct_height)) );
		
		//printf("Unsupported image size. Recommand values: %i %i\n",newWidth,newHeight);   
		
		GLubyte	*bitmapData=img->GetData();
		GLubyte        *alphaData=img->GetAlpha();
		GLubyte	*imageData;
		
		int old_bytesPerPixel = 3;
		int bytesPerPixel = img->HasAlpha() ?  4 : 3;
		
		int imageSize = newWidth * newHeight * bytesPerPixel;
		imageData=(GLubyte *)malloc(imageSize);
		
		int rev_val=(*imageHeight)-1;
		
		for(int y=0; y<newHeight; ++y)
		{
			for(int x=0; x<newWidth; ++x)
			{
				
				if( x<(*imageWidth) && y<(*imageHeight) ){
					imageData[(x+y*newWidth)*bytesPerPixel+0]=
					bitmapData[( x+(rev_val-y)*(*imageWidth))*old_bytesPerPixel + 0];
					
					imageData[(x+y*newWidth)*bytesPerPixel+1]=
						bitmapData[( x+(rev_val-y)*(*imageWidth))*old_bytesPerPixel + 1];
					
					imageData[(x+y*newWidth)*bytesPerPixel+2]=
						bitmapData[( x+(rev_val-y)*(*imageWidth))*old_bytesPerPixel + 2];
					
					if(bytesPerPixel==4) imageData[(x+y*newWidth)*bytesPerPixel+3]=
						alphaData[ x+(rev_val-y)*(*imageWidth) ];
					
				}
				else
				{
					
					imageData[(x+y*newWidth)*bytesPerPixel+0] = 0;
					imageData[(x+y*newWidth)*bytesPerPixel+1] = 0;
					imageData[(x+y*newWidth)*bytesPerPixel+2] = 0;
					if(bytesPerPixel==4) imageData[(x+y*newWidth)*bytesPerPixel+3] = 0;
				}
				
			}//next
		}//next
		
		
		glTexImage2D(GL_TEXTURE_2D,
					 0,
					 img->HasAlpha() ?  4 : 3,
					 newWidth,
					 newHeight,
					 0, 
					 img->HasAlpha() ?  GL_RGBA : GL_RGB, 
					 GL_UNSIGNED_BYTE,
					 imageData);
		
		(*textureWidth)=newWidth;
		(*textureHeight)=newHeight;
		
		free(imageData);
	}
	
	// set texture parameters as you wish
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP/*_TO_EDGE*/);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP/*_TO_EDGE*/);
	
	delete img;
	return ID;
}