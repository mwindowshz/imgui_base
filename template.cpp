//use this with base imgui reposetory and it will compile. with the rest of the examples.

#include "imgui.h"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

GLFWwindow* _window = nullptr;

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
int initImGui(int widht, int height)
{

	std::atomic<bool> _window_initialized = false;
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit()) {
		_window_initialized = false;
		return -1;
	}
	// glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	const char* glsl_version = "#version 140";// "#version 130";
											  // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
											  // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	_window = glfwCreateWindow(widht, height, fmt::format("{}", app_version).c_str(), nullptr, nullptr);
	if (!_window)
	{
		std::cout << "could not create debug window, possibly no OpenGL support" << std::endl;
		_window_initialized = false;
		_window_initialized.notify_all();
		return 0;
	}
	//glfwSetWindowCloseCallback(_window, [](GLFWwindow* window) { glfwSetWindowShouldClose(window, GL_FALSE); });
	glfwMakeContextCurrent(_window);
	glfwSwapInterval(1);
	gl3wInit();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
																//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
																//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
																//io.ConfigViewportsNoAutoMerge = true;
																//io.ConfigViewportsNoTaskBarIcon = true;
																// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init(nullptr);

	io.Fonts->AddFontDefault();
	// Load default font
	/*ImFontConfig fontConfig;
	fontConfig.FontDataOwnedByAtlas = false;
	ImFont* robotoFont = io.Fonts->AddFontFromMemoryTTF((void*)g_RobotoRegular, sizeof(g_RobotoRegular), 20.0f, &fontConfig);
	io.FontDefault = robotoFont;
//
	static const ImWchar iconsRanges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig iconsCfg; iconsCfg.MergeMode = true; iconsCfg.PixelSnapH = true; iconsCfg.FontDataOwnedByAtlas = false;
	ImFont* fontt = io.Fonts->AddFontFromMemoryTTF(&fontAwesomeRawData, sizeof fontAwesomeRawData, 13.0f, &iconsCfg, iconsRanges);
*/
	io.IniFilename = "imgui_program.ini";
	_window_initialized = true;
	_window_initialized.notify_all();
	return 1;
}
void ImGuiLoopBegin()
{
	glfwPollEvents();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//start new frame with imgui
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
}
void ImGuiLoopEnd()
{
	ImGuiIO& io = ImGui::GetIO();
	//finish render loop
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
	glfwSwapBuffers(_window);
}
void ImGuiClose()
{
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(_window);
	glfwTerminate();
}
int ImGuiDraw()
{
	ImGuiIO& io = ImGui::GetIO();




	bool _exit_flag = false;
	while (!_exit_flag && !glfwWindowShouldClose(_window))
	{

		ImGuiLoopBegin();
		//create windows here
		ImGui::ShowDemoWindow();

		ImGuiLoopEnd();

	}
	ImGuiClose();
	return 0;
}

int main(int argc, const char* argv[])
{
  int win_width = 700;
	int win_height = 650;

	initImGui(win_width, win_height);
  
  return 1;
}
