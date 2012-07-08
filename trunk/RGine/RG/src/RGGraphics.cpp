#include "RGGraphics.h"

#include "RGImage.h"

#include "RGScene.h"

///Static Declaration

//Screen
int RGGraphics::width = 320;
int RGGraphics::height = 240;
int RGGraphics::depth = 32;

//Timer
int RGGraphics::timerStartTicks = 0;
int RGGraphics::timerPausedTicks = 0;
bool RGGraphics::timerPaused = false;
bool RGGraphics::timerStarted = false;
int RGGraphics::fps = 60;

//Texture
map<string,GLuint> RGGraphics::textureMap;

///Methods

RGGraphics::RGGraphics() {
}

void RGGraphics::init() {
    //sdl
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(width,height,depth,SDL_OPENGL|SDL_RESIZABLE);
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_WM_SetCaption( "RGine Game" , NULL);
    atexit(SDL_Quit);

    //SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    //SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    //SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    //SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );

    //opengl
    glClearColor(0.0,0.0,0.0,1.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    //glEnable(GL_COLOR_MATERIAL);
    //glAlphaFunc(GL_LESS,0.9f);
    //glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    //glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    //glColor4ub(255,0,0,255);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //TODO remove this, test purpose only
    //glEnable(GL_NORMALIZE);

    resize(width,height);

    //fps control timer
    timerInit();
    timerStart();
}

void RGGraphics::loadTexture( string filename, string key ) {
    GLuint texture;			// This is a handle to our texture object
    SDL_Surface *surface = NULL;	// This surface will tell us the details of the image
    GLenum texture_format;
    GLint  nOfColors;

    void *raw;
    int w,h,i,j,bpp;
    Uint8 *srcPixel, *dstPixel;
    Uint32 truePixel;

    //Load the image using SDL_image
    surface = IMG_Load( filename.c_str() );

    //RGImage image;
//    image.load(filename);
//    surface = image.image;

    //If the image loaded
    if( surface != NULL ) {
//        w = surface->w;
//        h = surface->h;
//        raw = (void*)malloc(w*h*4);
//        dstPixel = (Uint8 *) raw;
//
//        //Create an optimized image
//        surface = SDL_DisplayFormat( surface );
//
//        //Prepares the surface for direct pixel access
//        SDL_LockSurface(surface);
//
//        bpp = surface->format->BytesPerPixel;
//
//        for(int i=h-1; i>=0; i--) {
//            for(int j=0; j<w; j++) {
//                (Uint8 *) surface->pixels + i * surface->pitch + j * bpp;
//                switch(bpp) {
//                case 1:
//                    truePixel = *srcPixel;
//                    break;
//                case 2:
//                    truePixel = *((Uint16*)srcPixel);
//                    break;
//                case 3:
//                    if(SDL_BYTEORDER == SDL_LIL_ENDIAN) {
//                        truePixel = srcPixel[0] << 16 | srcPixel[1] << 8 | srcPixel[2];
//                    } else {
//                        truePixel = srcPixel[0] | srcPixel[1] << 8 | srcPixel[2] << 16;
//                    }
//                    break;
//                case 4:
//                    truePixel = *((Uint32*)srcPixel);
//                    break;
//                default:
//                    //error
//                    return;
//                    break;
//                }
//
//                SDL_GetRGBA( truePixel, surface->format, &(dstPixel[0]), &(dstPixel[1]), &(dstPixel[2]), &(dstPixel[3]));
//                dstPixel+=4;
//            }
//        }
//
//        SDL_UnlockSurface(surface);
//        SDL_FreeSurface(surface);

        // Check that the image's width is a power of 2
        if ( (surface->w & (surface->w - 1)) != 0 ) {
            printf("warning: image.bmp's width is not a power of 2\n");
        }

        // Also check if the height is a power of 2
        if ( (surface->h & (surface->h - 1)) != 0 ) {
            printf("warning: image.bmp's height is not a power of 2\n");
        }

        // get the number of channels in the SDL surface
        nOfColors = surface->format->BytesPerPixel;
        if (nOfColors == 4) {   // contains an alpha channel
            if (surface->format->Rmask == 0x000000ff){
                texture_format = GL_RGBA;
                //cout << "rgba" << endl;
            }else{
                texture_format = GL_BGRA;
                //cout << "bgra" << endl;
            }
        } else if (nOfColors == 3) {   // no alpha channel
            if (surface->format->Rmask == 0x000000ff){
                texture_format = GL_RGB;
                //cout << "rgb" << endl;
            }else{
                texture_format = GL_BGR;
                //cout << "bgr" << endl;
            }
        } else {
            printf("warning: the image is not truecolor..  this will probably break\n");
            SDL_Quit();
            // this error should not go unhandled
        }

        // Have OpenGL generate a texture object handle for us
        glGenTextures( 1, &texture );

        // Bind the texture object
        glBindTexture( GL_TEXTURE_2D, texture );

        // Set the texture's stretching properties
//        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR /*GL_NEAREST/LINEAR*/);
//        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

        // Edit the texture object's image data using the information SDL_Surface gives us
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA , w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,  (Uint8 *)raw);

        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,texture_format, GL_UNSIGNED_BYTE, surface->pixels );
        //glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        /*glTexImage2D( GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0,
                      GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels );*/

        //free(raw);

    } else {
        printf("SDL could not load image.bmp: %s\n", SDL_GetError());
        SDL_Quit();
        //return 1;
    }

// Free the SDL_Surface only if it was successfully created
    if ( surface ) {
        SDL_FreeSurface( surface );
    }

    RGGraphics::textureMap[key] = texture;
}

void RGGraphics::useTexture(string key) {
    glBindTexture( GL_TEXTURE_2D, textureMap[key] );
}

void RGGraphics::renderScene() {
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glOrtho( 0.0,width, 0.0,height , -2000,1000);
    glFrustum (-width/20,width/20, -height/20,height/20, 50,6000);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Enables and disables
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void RGGraphics::renderInterface() {
    //Set Ortho for interface render
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0,width, 0.0,height , -2000,1000);
    //glFrustum (-width/20,width/20, -height/20,height/20, 50,6000);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Enables and disables
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
}

void RGGraphics::resize(int w, int h) {
    width = w;
    height = h;
    glViewport(0,0,width, height);
}

void RGGraphics::render(RGScene *scene) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //renderScene();

    renderInterface();

    scene->render();
    //renderInterface();
/*
    //glBindTexture( GL_TEXTURE_2D, texture2 );

    glColor4f(1,1,1,1);

    useTexture("tex2");

    static float c=0;

    glTranslatef(0,0,-400);
    //glTranslatef(0,0,100);
    glRotatef(c+=0.1,0,1,0);
    glRotatef(c/3,1,0,0);

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0,0,-400);
    //glTranslatef(0,0,100);
    glRotatef(c/2,0,1,0);
    glRotatef(c/6,1,0,0);
    //glScaled(0.5,0.5,0.5);
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0,1);
    glVertex3f(-100,-100,100);
    glTexCoord2f(1,1);
    glVertex3f(100,-100,100);
    glTexCoord2f(1,0);
    glVertex3f(100,100,100);
    glTexCoord2f(0,0);
    glVertex3f(-100,100,100);
    glEnd();
    useTexture("tex1");
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    glTexCoord2f(0,1);
    glVertex3f(100,-100,100);
    glTexCoord2f(1,1);
    glVertex3f(100,-100,-100);
    glTexCoord2f(1,0);
    glVertex3f(100,100,-100);
    glTexCoord2f(0,0);
    glVertex3f(100,100,100);
    glEnd();
    useTexture("tex1");
    glBegin(GL_QUADS);
    glNormal3f(-1,0,0);
    glTexCoord2f(0,1);
    glVertex3f(-100,-100,-100);
    glTexCoord2f(1,1);
    glVertex3f(-100,-100,100);
    glTexCoord2f(1,0);
    glVertex3f(-100,100,100);
    glTexCoord2f(0,0);
    glVertex3f(-100,100,-100);
    glEnd();
    useTexture("tex2");
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glTexCoord2f(0,1);
    glVertex3f(100,-100,-100);
    glTexCoord2f(1,1);
    glVertex3f(-100,-100,-100);
    glTexCoord2f(1,0);
    glVertex3f(-100,100,-100);
    glTexCoord2f(0,0);
    glVertex3f(100,100,-100);
    glEnd();
    useTexture("tex3");
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(0,1);
    glVertex3f(-100,100,100);
    glTexCoord2f(1,1);
    glVertex3f(100,100,100);
    glTexCoord2f(1,0);
    glVertex3f(100,100,-100);
    glTexCoord2f(0,0);
    glVertex3f(-100,100,-100);
    glEnd();
    useTexture("tex3");
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
    glTexCoord2f(0,1);
    glVertex3f(100,-100,-100);
    glTexCoord2f(1,1);
    glVertex3f(100,-100,100);
    glTexCoord2f(1,0);
    glVertex3f(-100,-100,100);
    glTexCoord2f(0,0);
    glVertex3f(-100,-100,-100);
    glEnd();
    glPopMatrix();

    renderInterface();

    useTexture("tex4");
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0,1);
    glVertex2f(0,0);
    glTexCoord2f(1,1);
    glVertex2f(640,0);
    glTexCoord2f(1,0);
    glVertex2f(640,480);
    glTexCoord2f(0,0);
    glVertex2f(0,480);
    glEnd();
*/
    SDL_GL_SwapBuffers();

    timerDelay();
}

void RGGraphics::end() {
    SDL_Quit();
}

void RGGraphics::timerInit() {
    timerStartTicks = 0;
    timerPausedTicks = 0;
    timerPaused = false;
    timerStarted = false;
    fps = 60;
}
void RGGraphics::timerStart() {
    timerStarted = true;
    timerPaused = false;
    timerStartTicks = SDL_GetTicks();
}
void RGGraphics::timerStop() {
    timerStarted = false;
    timerPaused = false;
}
void RGGraphics::timerPause() {
    if ( ( timerStarted == true ) && ( timerPaused == false ) ) {
        timerPaused = true;
        timerPausedTicks = SDL_GetTicks() - timerStartTicks;
    }
}
void RGGraphics::timerUnpause() {
    if ( timerPaused == true ) {
        timerPaused = false;
        timerStartTicks = SDL_GetTicks() - timerPausedTicks;
        timerPausedTicks = 0;
    }
}
int RGGraphics::timerGetTicks() {
    if ( timerStarted == true ) {
        if ( timerPaused == true ) {
            return timerPausedTicks;
        } else {
            return SDL_GetTicks() - timerStartTicks;
        }
    }
    return 0;
}
void RGGraphics::timerDelay() {
    if ( timerGetTicks() < 1000 / fps ) {
        SDL_Delay( ( 1000 / fps ) - timerGetTicks() );
    }
}
