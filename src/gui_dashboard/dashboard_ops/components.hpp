//
// Created by mbero on 24/06/2025.
//

#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <imgui.h>
#include <string>

namespace Components {

    class Button {
        std::string text_;
        bool disabled_;
    public:
        explicit Button(std::string text, bool disabled = false)
        noexcept:   text_(std::move(text)), disabled_(disabled) {
        }

        virtual ~Button() = default;

        auto get_text() const noexcept -> std::string {
            return text_;
        }
        auto get_disabled() const noexcept -> bool {
            return disabled_;
        }

        // auto render() const -> bool {
        //     return render_impl();
        // }

    protected:
        virtual auto render_impl() -> bool {
            if (disabled_) {
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
                ImGui::PushID(text_.c_str()); // Ensure unique ID for disabled state
            }
            bool clicked = ImGui::Button(text_.c_str());

            if (disabled_) {
                ImGui::PopID();
                ImGui::PopStyleVar();
            }
            return clicked;
        }
    };

}


#endif //COMPONENTS_HPP
