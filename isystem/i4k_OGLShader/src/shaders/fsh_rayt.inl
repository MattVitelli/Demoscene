//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008                                        //
//--------------------------------------------------------------------------//

static const char fsh_rayt[] = \

"uniform vec4 fpar[4];"

"float interesctSphere(in vec3 rO, in vec3 rD, in vec4 sph)"
"{"
    "vec3  p = rO - sph.xyz;"
    "float b = dot( p, rD );"
    "float c = dot( p, p ) - sph.w*sph.w;"
    "float h = b*b - c;"
    "if( h>0.0 )"
    "{"
        "h = -b - sqrt( h );"
    "}"
	"return h;"
"}"



"void main(void)"
"{"
    "vec3 wrd = normalize(gl_TexCoord[0].xyz);"
    "vec3 wro = fpar[0].xyz;"
    "float dif = dot( gl_TexCoord[1].xy-vec2(0.5), vec2(0.707) );"

    "float t = interesctSphere(wro,wrd,fpar[2]);"
    "if(t>0.0)"
    "{"
        "vec3 inter = wro + t*wrd;"
        "vec3 norma = normalize( inter - fpar[2].xyz );"
        "dif = dot(norma,vec3(0.57703));"
    "}"
    "gl_FragColor = dif*vec4(0.5,0.4,0.3,0.0) + vec4(0.5,0.5,0.5,1.0);"
"}";
