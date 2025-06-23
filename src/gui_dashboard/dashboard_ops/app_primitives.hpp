//
// Created by mbero on 23/06/2025.
//

#ifndef APP_PRIMITIVES_HPP
#define APP_PRIMITIVES_HPP
#include <bits/stdc++.h>
#include <SDL3/SDL.h>

#include <utility>
namespace Dashboard {
    class AppBase {
    public:
        ~AppBase() = default;
        virtual auto set_up() -> void = 0;
        virtual auto run() -> void {};
    };

    namespace Components {
        class Window {
            SDL_Window* window_ = nullptr;
            SDL_Renderer* renderer_ = nullptr;

            std::string window_title_;
            int width_, height_;
        public:
            explicit Window(std::string  window_title , const int& width, const int& height) noexcept
                : window_title_(std::move(window_title)), width_(width), height_(height) {
                init_window();
                init_renderer();
            };
            ~Window() {
                SDL_DestroyRenderer(renderer_);
                SDL_DestroyWindow(window_);
            };

            [[nodiscard]] auto get_window() const -> SDL_Window* { return window_; }
            [[nodiscard]] auto get_renderer() const -> SDL_Renderer* { return renderer_; }
        private:
            auto init_window()  -> void {
                std::cout <<  "Initializing window " << std::endl;
                constexpr auto WINDOW_FLAGS {
                    (SDL_WINDOW_OPENGL | SDL_WINDOW_HIGH_PIXEL_DENSITY),
                };
                SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
                window_ = SDL_CreateWindow(window_title_.c_str(), width_, height_, WINDOW_FLAGS);
            };
            auto init_renderer() -> void {
                std::cout << "Initializing renderer " << std::endl;
                renderer_ = SDL_CreateRenderer(window_, nullptr);
                if (renderer_ == nullptr) {
                    std::cerr << "Failed to create renderer" << std::endl;
                    return;
                }
            };
        };
    }
}
#endif //APP_PRIMITIVES_HPP
