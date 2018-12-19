// Preprocessor Directives
#ifndef GLITTER
#define GLITTER
#pragma once

// System Headers
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

#ifndef __EMSCRIPTEN__
#include <glad/glad.h>
#endif

// Define Some Constants
const int mWidth = 1280;
const int mHeight = 800;

#endif //~ Glitter Header
