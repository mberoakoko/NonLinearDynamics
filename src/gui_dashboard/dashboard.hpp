//
// Created by mbero on 23/06/2025.
//

#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP
#include <imgui.h>

#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"
#include "src/gui_dashboard/dashboard_ops/app_primitives.hpp"
namespace Application {
    const int APP_WIDTH = 800;
    const int APP_HEIGHT = 600;

    static void DemoWindowWidgetsPlotting()
{
    // Plot/Graph widgets are not very good.
// Consider using a third-party library such as ImPlot: https://github.com/epezent/implot
// (see others https://github.com/ocornut/imgui/wiki/Useful-Extensions)
    if (ImGui::TreeNode("Plotting"))
    {
        ImGui::Text("Need better plotting and graphing? Consider using ImPlot:");
        ImGui::TextLinkOpenURL("https://github.com/epezent/implot");
        ImGui::Separator();

        static bool animate = true;
        ImGui::Checkbox("Animate", &animate);

        // Plot as lines and plot as histogram
        static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
        ImGui::PlotLines("Frame Times", arr, IM_ARRAYSIZE(arr));
        ImGui::PlotHistogram("Histogram", arr, IM_ARRAYSIZE(arr), 0, NULL, 0.0f, 1.0f, ImVec2(0, 80.0f));
        //ImGui::SameLine(); HelpMarker("Consider using ImPlot instead!");

        // Fill an array of contiguous float values to plot
        // Tip: If your float aren't contiguous but part of a structure, you can pass a pointer to your first float
        // and the sizeof() of your structure in the "stride" parameter.
        static float values[90] = {};
        static int values_offset = 0;
        static double refresh_time = 0.0;
        if (!animate || refresh_time == 0.0)
            refresh_time = ImGui::GetTime();
        while (refresh_time < ImGui::GetTime()) // Create data at fixed 60 Hz rate for the demo
        {
            static float phase = 0.0f;
            values[values_offset] = cosf(phase);
            values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
            phase += 0.10f * values_offset;
            refresh_time += 1.0f / 60.0f;
        }

        // Plots can display overlay texts
        // (in this example, we will display an average value)
        {
            float average = 0.0f;
            for (int n = 0; n < IM_ARRAYSIZE(values); n++)
                average += values[n];
            average /= (float)IM_ARRAYSIZE(values);
            char overlay[32];
            sprintf(overlay, "avg %f", average);
            ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, overlay, -1.0f, 1.0f, ImVec2(0, 80.0f));
        }

        // Use functions to generate output
        // FIXME: This is actually VERY awkward because current plot API only pass in indices.
        // We probably want an API passing floats and user provide sample rate/count.
        struct Funcs
        {
            static float Sin(void*, int i) { return sinf(i * 0.1f); }
            static float Saw(void*, int i) { return (i & 1) ? 1.0f : -1.0f; }
        };
        static int func_type = 0, display_count = 70;
        ImGui::SeparatorText("Functions");
        ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
        ImGui::Combo("func", &func_type, "Sin\0Saw\0");
        ImGui::SameLine();
        ImGui::SliderInt("Sample count", &display_count, 1, 400);
        float (*func)(void*, int) = (func_type == 0) ? Funcs::Sin : Funcs::Saw;
        ImGui::PlotLines("Lines##2", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, ImVec2(0, 80));
        ImGui::PlotHistogram("Histogram##2", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, ImVec2(0, 80));

        ImGui::TreePop();
    }
}

    class Dashboard final: public DashboardBase::AppBase{
        bool is_running { false };
        bool exit_status { false };

        std::unique_ptr<DashboardBase::Components::Window> window_ { nullptr };
    public:
        explicit Dashboard() {
            set_up();
        }



        ~Dashboard() override {
            ImGui_ImplSDLRenderer3_Shutdown();
            ImGui_ImplSDL3_Shutdown();
            ImGui::DestroyContext();
            SDL_Quit();
        }

        auto setup_imgui() const -> void {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io{ImGui::GetIO()};

            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

            ImGui_ImplSDL3_InitForSDLRenderer(window_->get_window(), window_->get_renderer());
            ImGui_ImplSDLRenderer3_Init(window_->get_renderer());
        }

        auto run() -> int override {
            if ( exit_status ) {
                return exit_status;
            }
            is_running = true;

            setup_imgui();

            while ( is_running ) {
                SDL_Event event;
                while ( SDL_PollEvent( &event ) ) { // Event handlers should be hooked here
                    ImGui_ImplSDL3_ProcessEvent(&event);
                    if (event.type == SDL_EVENT_QUIT) {
                        is_running = false;
                    }
                }

                ImGui_ImplSDLRenderer3_NewFrame();
                ImGui_ImplSDL3_NewFrame();
                ImGui::NewFrame();
                DemoWindowWidgetsPlotting();
                ImGui::Render();
                SDL_SetRenderDrawColor(
                   window_->get_renderer(), 0, 0, 0, 0);
                SDL_RenderClear(window_->get_renderer());
                ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), window_->get_renderer());
                SDL_RenderPresent(window_->get_renderer());
            }
            return exit_status;
        };
        auto set_up() -> void override {
            if (bool init_results = SDL_Init({SDL_INIT_VIDEO | SDL_INIT_EVENTS}); !init_results) {
                std::cerr << "Init failed with flags "<<
                    "(SDL_INIT_VIDEO | SDL_INIT_EVENTS)" << std::endl;
                std::cerr << SDL_GetError() << std::endl;
                exit_status = true;
            };

            window_ = std::make_unique<DashboardBase::Components::Window>(DashboardBase::Components::Window::Params{
                        .window_title = "Dashboard Application",
                        .width = APP_WIDTH,
                        .height = APP_HEIGHT
            });
            std::cout<< "hello there " << std::endl;
            std::cout<< "hello there " << std::endl;
            std::cout<< "hello there " << std::endl;

        };

    };
}
#endif //DASHBOARD_HPP
