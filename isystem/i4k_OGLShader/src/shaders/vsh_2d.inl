//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008                                        //
//--------------------------------------------------------------------------//

static const char vsh_2d[] = \
"uniform vec4 fpar[4];"
"void main(void)"
"{"
    "gl_Position=gl_Vertex;"
    "vec3 d=normalize(fpar[1].xyz-fpar[0].xyz);"
    "vec3 r=normalize(cross(d,vec3(0.0,1.0,0.0)));"
    "vec3 u=cross(r,d);"
    "vec3 e=vec3(gl_Vertex.x*1.333,gl_Vertex.y,.75);"   //    eye space ray
    "gl_TexCoord[0].xyz=mat3(r,u,d)*e;"                 //  world space ray
    "gl_TexCoord[1]=vec4(.5)+gl_Vertex*.5;"             // screen space coordinate
"}";
