//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008                                        //
//--------------------------------------------------------------------------//

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <GL/gl.h>
#include <math.h>
#include "config.h"
#include "ext.h"
#include "shaders/fsh_rayt.inl"
#include "shaders/vsh_2d.inl"
#include "fp.h"

//=================================================================================================================


static void initShader( int *pid, const char *vs, const char *fs )
{
    pid[0] = oglCreateProgram();                           
	const int vsId = oglCreateShader( GL_VERTEX_SHADER ); 
	const int fsId = oglCreateShader( GL_FRAGMENT_SHADER );
	oglShaderSource( vsId, 1, &vs, 0 );
	oglShaderSource( fsId, 1, &fs, 0 );
    oglCompileShader( vsId );
    oglCompileShader( fsId );
	oglAttachShader( pid[0], fsId );
	oglAttachShader( pid[0], vsId );
	oglLinkProgram( pid[0] );

    #ifdef DEBUG
        int		result;
        char    info[1536];
        oglGetObjectParameteriv( vsId,   GL_OBJECT_COMPILE_STATUS_ARB, &result ); oglGetInfoLog( vsId,   1024, NULL, (char *)info ); if( !result ) DebugBreak();
        oglGetObjectParameteriv( fsId,   GL_OBJECT_COMPILE_STATUS_ARB, &result ); oglGetInfoLog( fsId,   1024, NULL, (char *)info ); if( !result ) DebugBreak();
        oglGetObjectParameteriv( pid[0], GL_OBJECT_LINK_STATUS_ARB,    &result ); oglGetInfoLog( pid[0], 1024, NULL, (char*)info ); if( !result ) DebugBreak();
    #endif
}

//=================================================================================================================

static int   pid;

//=================================================================================================================

int intro_init( void )
{
    if( !EXT_Init() )
        return( 0 );
    initShader( &pid, vsh_2d, fsh_rayt );
    return 1;
}

//=================================================================================================================

static float fparams[4*4];

void intro_do( long time )
{
    //--- update parameters -----------------------------------------

    const float t  = 0.001f*(float)time;

    // camera position
    fparams[ 0] = 2.0f*sinf(1.0f*t+0.1f);
    fparams[ 1] = 0.0f;
    fparams[ 2] = 2.0f*cosf(1.0f*t);
    // camera target
    fparams[ 4] = 0.0f;
    fparams[ 5] = 0.0f;
    fparams[ 6] = 0.0f;
    // sphere
    fparams[ 8] = 0.0f;
    fparams[ 9] = 0.0f;
    fparams[10] = 0.0f;
    fparams[11] = 1.0f;

    //--- render -----------------------------------------

    oglUseProgram( pid );
    oglUniform4fv( oglGetUniformLocation( pid, "fpar" ),  4, fparams );
    glRects( -1, -1, 1, 1 );
}