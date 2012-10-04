//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008                                        //
//--------------------------------------------------------------------------//

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <GL/gl.h>
#include <math.h>
#include "glext.h"

#define XRES    800
#define YRES    600

#include "shader.h"

const static PIXELFORMATDESCRIPTOR pfd = {0,0,PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

static DEVMODE screenSettings = { 
    #if _MSC_VER < 1400
    {0},0,0,148,0,0x001c0000,{0},0,0,0,0,0,0,0,0,0,{0},0,32,XRES,YRES,0,0,      // Visual C++ 6.0
    #else
    {0},0,0,156,0,0x001c0000,{0},0,0,0,0,0,{0},0,32,XRES,YRES,{0}, 0,           // Visuatl Studio 2005
    #endif
    #if(WINVER >= 0x0400)
    0,0,0,0,0,0,
    #if (WINVER >= 0x0500) || (_WIN32_WINNT >= 0x0400)
    0,0
    #endif
    #endif
    };

//--------------------------------------------------------------------------//

//extern "C" int _fltused = 0;

void entrypoint( void )
{ 
    // full screen
    if( ChangeDisplaySettings(&screenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL) return; ShowCursor( 0 );

    // create windows
    HDC hDC = GetDC( CreateWindow("edit", 0, WS_POPUP|WS_VISIBLE|WS_MAXIMIZE, 0,0,0,0,0,0,0,0) );

    // init opengl
    SetPixelFormat(hDC, ChoosePixelFormat(hDC, &pfd), &pfd);
    wglMakeCurrent(hDC, wglCreateContext(hDC));

    // create shader
    const int p = ((PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram"))();
    const int s = ((PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader"))(GL_FRAGMENT_SHADER);	
    ((PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource"))(s, 1, &fragmentShader, 0);
    ((PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader"))(s);
    ((PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader"))(p,s);
    ((PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram"))(p);
    ((PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram"))(p);

    // run
    do
    { 
        glColor3us((unsigned short)GetTickCount(),0,0);
        glRects(-1,-1,1,1);
        SwapBuffers(hDC); //wglSwapLayerBuffers( hDC, WGL_SWAP_MAIN_PLANE );
    }while ( !GetAsyncKeyState(VK_ESCAPE) );

    ExitProcess( 0 );
}
