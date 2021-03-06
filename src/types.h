#pragma once

#include "debug.h"
#include "basic_types.h"
#include "collection_types.h"
#include "memory_types.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>

struct Rectangle
{
    glm::vec2 position = glm::vec2(0, 0);
    float32 width = 0;
    float32 height = 0;
};

struct Color
{
    uint8 r = 255, g = 255, b = 255, a = 255;

    Color() : r(255), g(255), b(255), a(255) {}
    Color(uint8 r, uint8 g, uint8 b, uint8 a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

static const Color cWhite = Color { 255, 255, 255, 255 };
static const Color cBlack = Color { 255, 0, 0, 0 };

static const int cPaletteMaxColors = 256;
struct ColorPalette {
    Color colors[cPaletteMaxColors];
    int size = 0;

    void addColor(Color color)
    {
        colors[size++] = color;
    }
};

struct PaletteImage {
    int _width = 0;
    int _height = 0;
    int _size = 0;
    uint8* _data = nullptr;
    ColorPalette* palette = nullptr;
};

typedef uint Texture;

struct Mesh
{
    foundation::Array<glm::vec3>* vertices = nullptr;
    foundation::Array<glm::vec3>* normals = nullptr;
    foundation::Array<glm::vec2>* uvs = nullptr;
    foundation::Array<glm::vec4>* colors = nullptr;
    foundation::Array<uint32>* indices = nullptr;

    byte buffer[sizeof(foundation::Array<glm::vec3>) * 5];

    Mesh();
    Mesh(foundation::Allocator& _a);
    ~Mesh();
};

struct MeshInstance
{
    uint arrayId = 0;
    uint vertexBuffer = 0;
    uint normalBuffer = 0;
    uint uvBuffer = 0;
    uint colorBuffer = 0;
    uint indexBuffer = 0;
    uint32 indexCount = 0;
};

enum class ShaderType
{
    cVertex,
    cFragment
};

struct Shader
{
    ShaderType shaderType;
    uint shaderId = 0;
};

enum class VertexAttributeType
{
    cPosition,
    cNormal,
    cUv0,
    cUv1,
    cUv2,
    cUv3,
    cColor0,
    cColor1,
    cCount,
};

struct ShaderProgram
{
    uint programId = 0;
    uint attribSlots[(int)VertexAttributeType::cCount] = { 0 };
    foundation::Hash<int>* uniforms;
};

struct Material
{
    ShaderProgram* program;
};

enum class ProjectionType
{
    cPerspective,
    cOrtho,
};

struct Camera
{
    glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
    glm::quat rotation = glm::quat();

    ProjectionType projectionType;
    float32 fov;
    float32 aspectRatio;
    float32 orthoSize;
    float32 nearZ;
    float32 farZ;
};