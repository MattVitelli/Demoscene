#ifndef _SHADER_CODE_H
#define _SHADER_CODE_H

static const char shaderCodeVS[] = \
"struct PSIN { float4 Pos : POSITION0; float2 TexCoord : TEXCOORD0; };"
"PSIN vs_main(float2 Pos : POSITION0, float2 TexCoord : TEXCOORD0)"
"{"
	"PSIN OUT;"
	"OUT.Pos = float4(Pos.xy,0,1);"
	"OUT.TexCoord = TexCoord.xy;"
	"return OUT;"
"}";

static const char generic2DVS[] = \
"struct PSIN { float4 Pos : POSITION0; float2 TexCoord : TEXCOORD0; };"
"PSIN vs_main(float2 Pos : POSITION0, float2 TexCoord : TEXCOORD0)"
"{"
	"PSIN OUT;"
	"OUT.Pos = float4(Pos.xy,0,1);"
	"OUT.TexCoord = Pos.xy;"
	"return OUT;"
"}";

static const char densityVS[] = \
"struct PSIN { float4 Pos : POSITION0; float3 Ray : TEXCOORD0; };"
"PSIN vs_main(float2 Pos : POSITION0, float2 TexCoord : TEXCOORD0, uniform float4x4 InvViewProj : register(C0))"
"{"
	"PSIN OUT;"
	"OUT.Pos = float4(Pos.xy,0,1);"
	"float4 ray = mul(float4(Pos.xy,1,1), InvViewProj);"
	"OUT.Ray = ray.xyz / ray.w;"
	"return OUT;"
"}";

static const char densityFunctionsPS[] = \
"inline float sdSphere(float3 wp, float4 sphere)"
"{"
	"return length(wp-sphere.xyz)-sphere.w;"
"}"

"inline float sdPlane(float3 wp, float4 plane)"
"{"
	"return dot(wp, plane.xyz) + plane.w;"
"}"

"inline float sdBox( float3 p, float3 b )"
"{"
	"float3 d = abs(p) - b;"
	"return min(max(d.x,max(d.y,d.z)),0.0) + length(max(d,0.0));"
"}"

"inline float sdCylinder(float3 wp, float3 cylinderPos, float2 cylinder)"
"{"
    "float3 diff = wp-cylinderPos;"
    "float d = length(diff.xz)-cylinder.x;"
	"return max(-diff.y-cylinder.y,max(d,diff.y-cylinder.y));"
"}"

"inline float sdOctPrism(float3 p, float2 h)"
"{"
    "float3 q = abs(p);"
    "return max(q.z-h.y,max(q.x*0.70711+q.y*0.70711,max(q.x,q.y))-h.x);"
"}"

"inline float udRoundBox( float3 p, float4 b)"
"{"
	"return length(max(abs(p)-b.xyz,0.0))-b.w;"
"}"

"inline float sdColumn(float3 p)"
"{"
	"float3 u = p-float3(0,0,-2);"
	"float scale = lerp(1, 0.85, cos(u.z*9)*0.5+0.5);"
	"float2x2 matS = float2x2(scale,0,0,scale);"
    "u.xy = mul(matS, u.xy);"
	"float t1 = sdOctPrism(u, float2(2,1));"
	"float3 d = p-float3(0,0,3);"
	"float c = cos(0.5*d.z);"
    "float s = sin(0.5*d.z);"
    "float2x2 mat = float2x2(c,-s,s,c);"
    "d.xy = mul(mat, d.xy);"
	"float t2 = sdOctPrism(d, float2(1,5));"
	"float3 w = p-float3(0,0,8);"
	"float scale2 = lerp(1, 0.86, cos(w.z*8.85)*0.5+0.5);"
	"float2x2 matS2 = float2x2(scale2,0,0,scale2);"
    "w.xy = mul(matS2, w.xy);"
	"float t3 = sdOctPrism(w, float2(2.2,0.5));"
	"return min(t1,min(t2,t3));"
"}";

static const char distanceFunctionPS[] = \

"inline float distFn(float3 wp, out float attrib)"
"{"
	"float b;"
	"float t = sdSphere(wp, float4(0,5,-3,1));"
	"attrib = 1;"
	"b = sdPlane(wp, float4(0,1,0,3));"
	"if(b < t) { t = b; attrib = 3; }"
	"float3 d = (wp+SHIFT) % SCALE - 0.5*SCALE;"
    "d.y = wp.y;"
	"b = sdColumn(d.xzy);"
	"if(b < t) { t = b; attrib = 2; }"
	"b = sdPlane(wp, float4(0,-1,0,9));"
	"if(b < t) { t = b; attrib = 0; }"
	"float2 tiles = float2(1.45, 1.45);"

	"float3 d2 = (((wp+SHIFT)/SCALE + 0.5) % CHAMBER_SIZE)*SCALE;"
	"d2.y = wp.y;"
	"float diff = wp.y-3;"
	"float f = (cos(4*wp.y)*0.5+0.5)*saturate(diff*diff*0.085-0.4);"
	"float thick = lerp(0.05, 0.55, f);"
	"b = udRoundBox(d2-float3(0,3,CHAMBER_SIZE*SCALE*0.5), float4(thick,6,CHAMBER_SIZE*SCALE,0.2));"
	"b = min(b, udRoundBox(d2-float3((CHAMBER_SIZE-EPS)*SCALE,3,CHAMBER_SIZE*SCALE*0.5), float4(thick,6,CHAMBER_SIZE*SCALE,0.2)));"
	"b = min(b, udRoundBox(d2-float3(CHAMBER_SIZE*SCALE*0.5,3,0), float4(CHAMBER_SIZE*SCALE,6,thick,0.2)));"
	"b = min(b, udRoundBox(d2-float3(CHAMBER_SIZE*SCALE*0.5,3,(CHAMBER_SIZE-EPS)*SCALE), float4(CHAMBER_SIZE*SCALE,6,thick,0.2)));"
	"b = min(b, GetMazeWalls(d2-float3(0,3,0),float4(thick, 6, SCALE*0.5, 0.2)));"
	"if(b < t) { t = b; attrib = 5; }"

	"d.xz = (wp.xz+SHIFT) % TILES - 0.5*TILES;"
	"b = udRoundBox(d-float3(0,-3,0), float4(0.5,0.15,0.5,0.2));"
	"if(b < t) { t = b; attrib = 4; }"
	"return t;"
"}";

static const char densityPS[] = \

//"inline float GetWall(float2 tc) { float2 crd = floor((tc+SHIFT+5)*0.1)%CHAMBER_SIZE; return chambers[crd.x+crd.y*CHAMBER_SIZE];}"

"uniform sampler2D NoiseMap : register(S0);"
"uniform float2 invRes : register(C6);"

"inline float2 GetTCWall(float2 tc) { return ((tc+SHIFT)*invRes)*0.1 + 0.5*invRes; }"

"struct PSOUT"
"{"
	"float4 Color : COLOR0;"
"};"


"PSOUT ps_main(float3 Ray : TEXCOORD0, uniform float4x4 ViewProj : register(C0),"
"uniform float3 EyePos : register(C4), uniform float2 Planes : register(C5)"
"):color"
"{"
	"float3 rD = normalize(Ray);"
    "float t=999;"
	"float3 samplePos = EyePos+rD*Planes.x;"
	"float numIter = 0;"
	"float attribID = 0;"
	"for(int i=0;(i<SAMPLES && (abs(t) > EPS)); i++)"
	"{"
		"t = distFn(samplePos, attribID);"
		"samplePos += t*rD;"
		"numIter++;"
	"}"
    "t = length(samplePos-EyePos);"

	"float3 l = normalize(1);"
	"float m = 999;"
	"float3 shadowPos = samplePos+l*Planes.x;"
	"float shadowAttrib=-1;"
	"for(int i=0;(i<SHADOWSAMPLES && (abs(m) > EPS)); i++)"
	"{"
		"m = distFn(shadowPos, shadowAttrib);"
		"shadowPos += m*l;"
	"}"

	//"float3 N; N.x = distFn(samplePos+float3(EPS,0,0))-distFn(samplePos-float3(EPS,0,0)); N.y = distFn(samplePos+float3(0,EPS,0))-distFn(samplePos-float3(0,EPS,0)); N.z = distFn(samplePos+float3(0,0,EPS))-distFn(samplePos-float3(0,0,EPS)); N = normalize(N);"
	"float3 N = normalize(cross(ddy(rD*t),ddx(rD*t)));"
	"float4 projPos = mul(float4(samplePos.xyz,1), ViewProj);"
	"PSOUT OUT;"
	//"float2 crd = floor((samplePos.xz+SHIFT+5)*0.1)%CHAMBER_SIZE; attribID = (crd.x+crd.y*CHAMBER_SIZE)/(CHAMBER_SIZE*CHAMBER_SIZE);"
	"OUT.Color = float4(N,1) * attribID * ((shadowAttrib==0)+0.15);"//tex2D(NoiseMap, GetTCWall(samplePos.xz)).x//((samplePos.xz+1024)*invRes)/10 + 0.5*invRes).x*0.2 * float4(N,1);"
	"return OUT;"
"}";

static const char shaderCodePS[] = \

"float4 ps_main(float2 TC : TEXCOORD0):color"
"{"
	"return float4(TC.x,TC.y,0.4,1);"
"}";

#endif