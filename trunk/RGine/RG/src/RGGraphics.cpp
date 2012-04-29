#include "RGGraphics.h"

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

    //opengl
    glClearColor(0,0,0,1);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    //glEnable(GL_BLEND);
    //glBlendFunc (GL_RGB,GL_ONE_MINUS_SRC_COLOR);

    resize(width,height);

    //fps control timer
    timerInit();
    timerStart();
}

void RGGraphics::resize(int w, int h) {
    width = w;
    height = h;
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glViewport(0,0,width, height);
    glOrtho( 0.0,width, 0.0,height , -2000,1000);
    //glFrustum (-width/20,width/20, -height/20,height/20, 50,6000);
    glMatrixMode(GL_TEXTURE);
    //glRotatef(180,0,0,1);
    //glScalef(-1,1,1);
    //texture
    glMatrixMode( GL_MODELVIEW );
}

void RGGraphics::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //glBindTexture( GL_TEXTURE_2D, texture2 );

    glColor4f(1,1,1,1);

    useTexture("tex2");

    static float c=0;

    glTranslatef(100,100,0);
    glRotatef(c+=0.1,0,1,0);
    glRotatef(c/3,1,0,0);

    glBegin(GL_QUADS);
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
    glTexCoord2f(0,1);
    glVertex3f(100,-100,-100);
    glTexCoord2f(1,1);
    glVertex3f(100,-100,100);
    glTexCoord2f(1,0);
    glVertex3f(-100,-100,100);
    glTexCoord2f(0,0);
    glVertex3f(-100,-100,-100);
    glEnd();

    SDL_GL_SwapBuffers();
}

void RGGraphics::delay() {
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

void RGGraphics::loadTexture( string filename, string key ) {
    GLuint texture;			// This is a handle to our texture object
    SDL_Surface *surface = NULL;	// This surface will tell us the details of the image
    GLenum texture_format;
    GLint  nOfColors;

    //Load the image using SDL_image
    surface = IMG_Load( filename.c_str() );

    //If the image loaded
    if( surface != NULL ) {
        //Create an optimized image
        surface = SDL_DisplayFormat( surface );

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
            if (surface->format->Rmask == 0x000000ff)
                texture_format = GL_RGBA;
            else
                texture_format = GL_BGRA;
        } else if (nOfColors == 3) {   // no alpha channel
            if (surface->format->Rmask == 0x000000ff)
                texture_format = GL_RGB;
            else
                texture_format = GL_BGR;
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
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        // Edit the texture object's image data using the information SDL_Surface gives us
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
                      texture_format, GL_UNSIGNED_BYTE, surface->pixels );

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
