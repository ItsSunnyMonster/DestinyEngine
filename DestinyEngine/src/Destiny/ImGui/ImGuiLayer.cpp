#include "ImGuiLayer.hpp"

#include <imgui.h>

#include "Destiny/Application.hpp"
#include <backends/imgui_impl_win32.h>

Destiny::ImGuiLayer::ImGuiLayer()
	: Layer("ImGuiLayer")
{
}

Destiny::ImGuiLayer::~ImGuiLayer()
{
}

void Destiny::ImGuiLayer::onAttach()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	//io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	//io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImFontConfig config;
	config.Density = ImGui_ImplWin32_GetDpiScaleForHwnd(Application::get()->getWindow()->getNativeWindow());
	config.OversampleH = 1;
	config.OversampleV = 1;
	config.FontBuilderFlags = 1;
	io.Fonts->AddFontFromFileTTF("assets/fonts/cjk/NotoSansSC-Regular.otf", 20, &config, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());

	Ref<Window> wnd = Application::get()->getWindow();
	wnd->initImGuiImpl();
	wnd->getContext()->initImGuiImpl();
}

void Destiny::ImGuiLayer::onDetach()
{
	Ref<Window> wnd = Application::get()->getWindow();
	wnd->destroyImGuiImpl();
	wnd->getContext()->destroyImGuiImpl();
	ImGui::DestroyContext();
}

void Destiny::ImGuiLayer::onUpdate()
{
}

void Destiny::ImGuiLayer::onEvent(Event& event)
{
}

void Destiny::ImGuiLayer::onImGuiRender()
{
	static bool show;
	ImGui::ShowDemoWindow(&show);
}
