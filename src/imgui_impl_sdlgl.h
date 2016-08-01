struct SDL_Window;
typedef union SDL_Event SDL_Event;

IMGUI_API bool ImGui_SdlGl_Init(SDL_Window* window);
IMGUI_API void ImGui_SdlGl_Shutdown();
IMGUI_API void ImGui_SdlGl_NewFrame(SDL_Window* window);
IMGUI_API bool ImGui_SdlGl_ProcessEvent(SDL_Event* event);

IMGUI_API void ImGui_SdlGl_InvalidateDeviceObjects();
IMGUI_API bool ImGui_SdlGl_CreateDeviceObjects();