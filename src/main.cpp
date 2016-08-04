#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <cstdio>
#include <ctime>
#include <GL/gl3w.h>

#include "imgui.h"
#include "imgui_impl_sdlgl.h"

#include "palette_image.h"
#include "material.h"
#include "mesh.h"
#include "camera.h"
#include "math.h"
#include "memory.h"
#include "texture.h"

int run(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    foundation::memory_globals::init();

    int result = run(argc, argv);

    foundation::memory_globals::shutdown();
    
    return result;
}

int run(int argc, char* argv[]) {
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);

    auto window = SDL_CreateWindow("PaPiEd", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    gl3wInit();

    // init ImGui
    ImGui_SdlGl_Init(window);

    bool isRunning = true;

    ImVec4 clearColor = ImColor(114, 144, 154);

    srand(time(nullptr));
    PaletteImage image = palette_image::create(64, 64, &cDefaultPalette);
    for (int i = 0; i < image._size; ++i) {
        image._data[i] = (rand() % 5) * (256 / 4);
    }

    Texture indexTexture = texture::create();
    Texture paletteTexture = texture::create();
    texture::make_index_image(indexTexture, image);
    texture::make_palette(paletteTexture, image);

    Camera camera;
    camera.position = glm::vec3(0.f, 0.f, 3.f);
    camera.projectionType = ProjectionType::cOrtho;
    camera.fov = 90.f;
    camera.aspectRatio = 4.f / 3.f;
    camera.nearZ = 0.1f;
    camera.farZ = 100.f;
    camera.orthoSize = 1.f;

    Shader vertShader, fragShader;
    shader::load("shaders/palette-image.vert", ShaderType::cVertex, vertShader);
    shader::load("shaders/palette-image.frag", ShaderType::cFragment, fragShader);

    ShaderProgram program;
    shader::create_program(vertShader, fragShader, program);
    shader::ProgramGuard programGuard(program);

    Material material;
    material::create(&program, material);
    material::use(material);

    Mesh quadMesh;
    mesh::create_quad(quadMesh);

    MeshInstance quad = mesh::create_instance(quadMesh);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_SdlGl_ProcessEvent(&event);

            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                case SDL_KEYDOWN:
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        isRunning = false;
                    }
            }
        }

        ImGui_SdlGl_NewFrame(window);

        {
            static float f = 0.0f;
            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clearColor);
            //if (ImGui::Button("Test Window")) show_test_window ^= 1;
            //if (ImGui::Button("Another Window")) show_another_window ^= 1;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        material::use(material);

        glm::mat4 model;
        math::matrix::trs(glm::vec2(0.f, 0.f), 0.f, glm::vec2(1, 1), model);

        auto view = camera::view(camera);
        auto projection = camera::projection(camera);

        material::set_uniform<glm::mat4>(material, "view", view);
        material::set_uniform<glm::mat4>(material, "projection", projection);
        material::set_uniform<glm::mat4>(material, "model", model);

        MeshInstance activeMesh = quad;

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, indexTexture);
        material::set_uniform<uint>(material, "indexTexture", 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, paletteTexture);
        material::set_uniform<uint>(material, "paletteTexture", 1);

        {
            mesh::BindGuard guard(activeMesh);
            mesh::render(activeMesh);
        }

        ImGui::Render();
        SDL_GL_SwapWindow(window);
    }

    ImGui_SdlGl_Shutdown();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}