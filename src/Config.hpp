#ifndef CONFIG_HPP
#define CONFIG_HPP

#define NS_BEGIN namespace Lumina {
#define NS_END }

#define DELETECOM(x) {if(x) {x->Release(); x = 0;} }

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Lumina Engine"

#define ENABLE_VSYNC true

#define PER_FRAME_SLOT 0
#define PER_MATERIAL_SLOT 1
#define PER_OBJECT_SLOT 2
#define LIGHTING_SLOT 3
#define SHADOWS_SLOT 4
#define MISC_SLOT 5 // TODO: Find a better way to do this


#define NUM_DIRECTIONAL_LIGHTS 1
#define NUM_POINT_LIGHTS 1
#define NUM_SPOT_LIGHTS 1

#define PI 3.1415926535f
#define TWOPI  6.283185307f
#define HALFPI 1.57079632675f;
#define QUARTERPI 0.785398163375f

float DegreesToRadians(float d);
float RadiansToDegrees(float r);

#include <Windows.h>
#include <d3d11.h>
#include <vector>
#include <map>
#include <string>
#include <typeinfo>
#include <cassert>
#include <memory>

#include "Utility\Debug\Debug.hpp"
#include "Utility\Timer.hpp"

typedef unsigned int uint;

#endif