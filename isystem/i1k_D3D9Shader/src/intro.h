//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008                                        //
//--------------------------------------------------------------------------//

#ifndef _DEMO_H_
#define _DEMO_H_

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <d3d9.h>
#include "InputManager.h"

void intro_init( IDirect3DDevice9 *d3dDevice );
void intro_handle_input(InputManager *input, float time);
void intro_do( IDirect3DDevice9 *d3dDevice, float time);
void intro_end( IDirect3DDevice9 *d3dDevice );

#endif
