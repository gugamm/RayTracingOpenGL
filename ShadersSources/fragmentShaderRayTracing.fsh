//Fragment shader for RayTracing
//Implemented by Gustavo Martins
//OpenGL 4.3 core profile

/* gl_FragCoord will give us the pixel position between [0..w] and [0..h] */
/* negative z means how far(depth) is the object from the screen */
#version 430 core

//values from application
uniform vec3 rOrigin;
uniform float width;
uniform float height;

//Definition of a ray r = o + t*d
struct Ray {
  vec3 origin; //eye
  vec3 direction; //direciton
};

struct Sphere {
  float radios;
  vec3 point;
  vec4 color;
}

float piValue = 3.141592653;
Ray ray;
Sphere sphere;

vec3 calcRayDirection() {
  //dr = Pxy - eye
  vec3 pxy = vec3(gl_FragCoord.xy,0.0f);
  return pxy - rOrigin;
}

void main() {
  ray = Ray(rOrigin, calcRayDirection());
  sphere = (piValue, vec3(width/2,height/2,-100.0f),vec4(1.0f,0.0f,0.0f,1.0f)); //Creates a red sphere
  float a = dot()

}
