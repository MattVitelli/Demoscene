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

//static const char densityFn[] = \

/*
"#define EPS 0.001\n"
"#define CHAMBER_SIZE 4\n"
"static const float chambers[] = { 0, 0, 3, 3, 2, 2, 2, 1, 1, 0, 0, 3, 3, 4, 3, 0, 1, 4, 0, 2, 1, 0, 2, 0, 0, 4, 0, 0, 4, 2, 1, 4, 4, 0, 3, 0, 1, 4, 0, 3, 2, 4, 0, 2, 3, 4, 0, 2, 2, 4, 2, 2, 2, 1, 1, 0, 2, 2, 2, 2, 2, 1, 1, 4, 4, 0, 3, 3, 0, 2, 4, 2, 4, 1, 0, 2, 4, 0, 2, 1, 4, 2, 2, 0, 0, 3, 2, 3, 4, 2, 3, 3, 1, 2, 1, 0, 2, 1, 3, 2, 0, 2, 1, 0, 4, 4, 3, 0, 1, 3, 1, 1, 0, 1, 3, 4, 4, 1, 3, 0, 2, 0, 4, 2, 4, 0, 1, 1, 0, 4, 4, 2, 1, 4, 0, 1, 1, 2, 0, 0, 0, 1, 2, 0, 1, 1, 3, 0, 3, 2, 0, 1, 3, 3, 0, 0, 2, 3, 0, 3, 3, 1, 0, 1, 4, 3, 4, 0, 0, 1, 3, 2, 0, 2, 4, 0, 3, 4, 0, 2, 2, 0, 3, 2, 4, 3, 4, 3, 4, 0, 4, 2, 1, 1, 2, 4, 1, 0, 1, 3, 1, 2, 4, 2, 4, 2, 0, 0, 3, 4, 1, 3, 2, 3, 1, 2, 2, 2, 1, 0, 3, 1, 1, 4, 2, 0, 1, 4, 0, 4, 4, 2, 2, 2, 0, 0, 1, 0, 3, 1, 2, 4, 4, 4, 3, 0, 0, 2, 0, 0, 1, 4, 4, 0, 0, 0, };"
*/

static const char densityPS[] = \

"static const int SHIFT = 1024;" //1024
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
"}"

"inline float GetWall(float2 tc) { float2 crd = floor((tc+SHIFT+5)*0.1)%CHAMBER_SIZE; return chambers[crd.x+crd.y*CHAMBER_SIZE];}"

"inline float distFn(float3 wp, out float attrib)"
"{"
	"float b;"
	"float t = sdSphere(wp, float4(0,5,-3,1));"
	"attrib = 1;"
	"b = sdPlane(wp, float4(0,1,0,3));"
	"if(b < t) { t = b; attrib = 3; }"
	"float3 c = float3(10, 1, 10);"
	//"float3 d = wp;"
	"float3 d = (wp+SHIFT) % c - 0.5*c;"
    "d.y = wp.y;"
	"b = sdColumn(d.xzy);"
	"if(b < t) { t = b; attrib = 2; }"
	"b = sdPlane(wp, float4(0,-1,0,9));"
	"if(b < t) { t = b; attrib = 0; }"
	"float2 tiles = float2(1.45, 1.45);"
	"float walls = GetWall(wp.xz);"

	"float3 d2 = d;"//(wp+SHIFT) % c - 0.5*c;"
	"d2.xz += 0.5*c.xz;"
	"float diff = wp.y-3;"
	"float f = (cos(4*wp.y)*0.5+0.5)*saturate(diff*diff*0.085-0.4);"
	"float thick = lerp(0.05, 0.55, f);"
	"if(walls == 1 || walls == 3 || walls == 5 || walls == 7 || walls == 9 || walls == 11 || walls == 13 || walls == 15)"
	"{b = udRoundBox(d2-float3(0,3,5), float4(10,6,thick,0.2));}"
	"if(walls == 4 || walls == 5 || walls == 6 || walls == 7 || walls == 12 || walls == 13 || walls == 14 || walls == 15)"
	"{b = min(b, udRoundBox(d2-float3(5,3,0), float4(thick,6,10,0.2)));}"
	"if(walls == 2 || walls == 3 || walls == 6 || walls == 7 || walls == 10 || walls == 11 || walls == 14 || walls == 15)"
	"{b = min(b, udRoundBox(d2-float3(0,3,-5), float4(10,6,thick,0.2)));}"
	"if(walls == 8 || walls == 9 || walls == 10 || walls == 11 || walls == 12 || walls == 13 || walls == 14 || walls == 15)"
	"{b = min(b, udRoundBox(d2-float3(-5,3,0), float4(thick,6,10,0.2)));}"
	/*
	"float diff = d.y-3;"
	"float f = (cos(4*d.y)*0.5+0.5)*saturate(diff*diff*0.085-0.4);"
	"float thick = lerp(0.05, 0.55, f);"
	"b = udRoundBox(d-float3(0,3,0), float4(10,6,thick,0.2));"
	"b = min(b, udRoundBox(d-float3(0,3,0), float4(thick,6,10,0.2)));"
	*/
	/*
	"if(walls == 1 || walls == 3 || walls == 5 || walls == 7 || walls == 9 || walls == 11 || walls == 13 || walls == 15) b = max(-sdPlane(d, float4(1,0,0,-1)), b);"
	"if(walls == 2 || walls == 3 || walls == 6 || walls == 7 || walls == 10 || walls == 11 || walls == 14 || walls == 15) b = max(-sdPlane(d, float4(-1,0,0,1)), b);"
	"if(walls == 4 || walls == 5 || walls == 6 || walls == 7 || walls == 12 || walls == 13 || walls == 14 || walls == 15) b = max(-sdPlane(d, float4(0,0,1,-1)), b);"
	"if(walls == 8 || walls == 9 || walls == 10 || walls == 11 || walls == 12 || walls == 13 || walls == 14 || walls == 15) b = max(-sdPlane(d, float4(0,0,-1,1)), b);"
	*/
	/*
	"if(walls == 1 || walls == 3 || walls == 5 || walls == 7 || walls == 9 || walls == 11 || walls == 13 || walls == 15) b = max(8*-sdBox(d-float3(0,3,-0.5), float3(10,6,0.5)), b);"
	"if(walls == 2 || walls == 3 || walls == 6 || walls == 7 || walls == 10 || walls == 11 || walls == 14 || walls == 15) b = max(8*-sdBox(d-float3(0,3,0.5), float3(10,6,0.5)), b);"
	"if(walls == 4 || walls == 5 || walls == 6 || walls == 7 || walls == 12 || walls == 13 || walls == 14 || walls == 15) b = max(8*-sdBox(d-float3(-0.5,3,0), float3(0.5,6,10)), b);"
	"if(walls == 8 || walls == 9 || walls == 10 || walls == 11 || walls == 12 || walls == 13 || walls == 14 || walls == 15) b = max(8*-sdBox(d-float3(0.5,3,0), float3(0.5,6,10)), b);"
	*/
	/*
	"if(walls == 1 || walls == 3 || walls == 5 || walls == 7 || walls == 9 || walls == 11 || walls == 13 || walls == 15) b = max(8*-sdBox(d-float3(0,3,-0.5), float3(10,6,0.5)), b);"
	"if(walls == 2 || walls == 3 || walls == 6 || walls == 7 || walls == 10 || walls == 11 || walls == 14 || walls == 15) b = max(8*-sdBox(d-float3(0,3,0.5), float3(10,6,0.5)), b);"
	"if(walls == 4 || walls == 5 || walls == 6 || walls == 7 || walls == 12 || walls == 13 || walls == 14 || walls == 15) b = max(8*-sdBox(d-float3(-0.5,3,0), float3(0.5,6,10)), b);"
	"if(walls == 8 || walls == 9 || walls == 10 || walls == 11 || walls == 12 || walls == 13 || walls == 14 || walls == 15) b = max(8*-sdBox(d-float3(0.5,3,0), float3(0.5,6,10)), b);"
	*/
	"if(b < t) { t = b; attrib = 5; }"

	"d.xz = (wp.xz+1024) % tiles - 0.5*tiles;"
	"b = udRoundBox(d-float3(0,-3,0), float4(0.5,0.15,0.5,0.2));"
	"if(b < t) { t = b; attrib = 4; }"
	"return t;"
"}"

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

	"const int linear_search_steps=32;"
    "float t=999;"
	"float3 samplePos = EyePos+rD*Planes.x;"
	"float numIter = 0;"
	"float attribID = 0;"
	"for(int i=0;(i<linear_search_steps && (abs(t) > EPS)); i++)"
	"{"
		"t = distFn(samplePos, attribID);"
		"samplePos += t*rD;"
		"numIter++;"
	"}"
    "t = length(samplePos-EyePos);"

	//"float3 N; N.x = distFn(samplePos+float3(EPS,0,0))-distFn(samplePos-float3(EPS,0,0)); N.y = distFn(samplePos+float3(0,EPS,0))-distFn(samplePos-float3(0,EPS,0)); N.z = distFn(samplePos+float3(0,0,EPS))-distFn(samplePos-float3(0,0,EPS)); N = normalize(N);"
	"float3 N = normalize(cross(ddy(rD*t),ddx(rD*t)));"
	"float4 projPos = mul(float4(samplePos.xyz,1), ViewProj);"
	"PSOUT OUT;"
	"float2 crd = floor((samplePos.xz+SHIFT+5)*0.1)%CHAMBER_SIZE; attribID = (crd.x+crd.y*CHAMBER_SIZE)/(CHAMBER_SIZE*CHAMBER_SIZE);"
	"OUT.Color = float4(N,1) * attribID;"//tex2D(NoiseMap, GetTCWall(samplePos.xz)).x//((samplePos.xz+1024)*invRes)/10 + 0.5*invRes).x*0.2 * float4(N,1);"
	"return OUT;"
"}";

static const char shaderCodePS[] = \

"float4 ps_main(float2 TC : TEXCOORD0):color"
"{"
	"return float4(TC.x,TC.y,0.4,1);"
"}";

#endif