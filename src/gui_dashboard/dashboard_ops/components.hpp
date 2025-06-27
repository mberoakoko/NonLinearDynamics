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

    class DummyDataModel {
        std::uint16_t counter_ { 0 };
        std::string status_message_ { "Nothing to Show here" };
    public:
        [[nodiscard]]auto get_counter() const noexcept -> std::uint16_t { return counter_;}
        auto increment_counter()  noexcept -> std::uint16_t { return ++counter_;}
        auto decrement_counter()  noexcept -> std::uint16_t { return --counter_;}

        auto get_status_message() const noexcept -> std::string { return status_message_;}
        auto set_status_message(const std::string& message) noexcept -> void{ status_message_ = message;};

    };

    class ImGuiComponent {
    public:
        virtual ~ImGuiComponent() = default;
        virtual auto render() -> void = 0;
    };

    class CounterDisplayComponent final : public ImGuiComponent {
        DummyDataModel model_;
    public:
        explicit CounterDisplayComponent(const DummyDataModel& model): model_(model) {};
        auto render() -> void override {
            ImGui::Text("Current Count: %d ", model_.get_counter());
            if (ImGui::Button("Increment")) {
                model_.increment_counter();
                model_.set_status_message("Incremented the counter");
            }
            ImGui::SameLine();
            if (ImGui::Button("Decrement")) {
                model_.decrement_counter();
                model_.set_status_message("Decremented the counter");
            }
        };
    };

    class StatusBarComponent final : public ImGuiComponent {
    DummyDataModel model_;
    public:
        explicit StatusBarComponent(const DummyDataModel& model): model_(model) {};
        auto render() -> void override {
            ImGui::Separator();
            ImGui::Text("Current Status: %s", model_.get_status_message().c_str());

        }

    };

    class RenderingBlockElement final: public ImGuiComponent {
    public:
        explicit RenderingBlockElement()
            :   model_(std::make_unique<DummyDataModel>()),
                display_component_(std::make_unique<CounterDisplayComponent>(*model_)),
                status_bar_(std::make_unique<StatusBarComponent>(*model_)) {

        }

        auto render() -> void override {
            ImGui::Begin("My ImGui Dashboard (MVC-ish)");
            display_component_->render();
            ImGui::Spacing();
            status_bar_->render();
            ImGui::End();
        }


    private:
        std::unique_ptr<DummyDataModel> model_;
        std::unique_ptr<CounterDisplayComponent> display_component_;
        std::unique_ptr<StatusBarComponent> status_bar_;
    };

}


#endif //COMPONENTS_HPP
