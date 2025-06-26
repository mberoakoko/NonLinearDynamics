//
// Created by mbero on 17/06/2025.
//

#ifndef UTIL_HPP
#define UTIL_HPP
#include <bits/stdc++.h>

namespace Utils {
    template<typename T>
    struct Observer {
        virtual ~Observer() {}
        virtual auto field_changed(const T& source , const std::string& field_name) = 0;
    };

    template<typename T>
    struct Observable {
        virtual ~Observable() {}

        auto subscribe(Observer<T>* observer) -> void {observers_.emplace_back(observer);};
        auto unsubscribe(Observer<T>* observer) -> void {
            std::erase(
                std::remove(std::begin(observers_), std::end(observers_), observer),
                std::end(observers_)
                );
        }
    private:
        std::vector<Observer<T> *> observers_;
    };

    template<typename T, typename E>
    class Result_t {
        std::variant<T, E> data_;
        bool is_success_;


        // Private constructor
        template<typename U, typename ...Args>
        explicit Result_t(std::in_place_t<U>, Args&&... args) {
            if constexpr (std::is_same_v<T, E>) {
                data_.template emplace<U>(std::forward<Args>(args)...);
                is_success_ = true;
            } else if constexpr (std::is_same_v<T, E>) {
                data_.template emplace<E>(std::forward<Args>(args)...);
                is_success_ = false;
            } else {
                static_assert(false, "invalid result");
            }

        }
    public:
        // ok factory constructor
        template<typename ...Args>
        auto ok(Args&& ... args) -> Result_t {
            return Result_t(std::in_place_type<E>, std::forward<Args>(args)...);
        }

        // error factory constructor
        template<typename ...Args>
        auto error(Args&& ... args) -> Result_t {
            return Result_t(std::in_place_type<E>, std::forward<Args>(args)...);
        }

        // Accessors
        [[nodiscard]] auto is_ok() const -> bool {return is_success_;}
        [[nodiscard]] auto is_error() const -> bool {return !is_success_;}

        auto value() const -> T& {
            if (!is_success_) {
                throw std::bad_variant_access();
            }
            return std::get<T>(data_);
        }

        auto error() const -> E& {
            if (is_success_) {
                throw std::bad_variant_access();
            }
            return std::get<E>(data_);
        }
        template<typename Dummy_t = void>
        using DummySFNAE_t = std::enable_if_t<std::is_void_v<T>, Dummy_t>;

        auto value() const -> DummySFNAE_t {
            if (!is_success_) {
                throw std::bad_variant_access();
            }
            return DummySFNAE_t(std::get<E>(data_));
        }

        template <typename F, typename U = std::invoke_result_t<F, T>>
        auto map(F&& f) -> Result_t<U, E> {
            if (is_ok()) {
                return Result_t<U, E>::ok(std::invoke(std::forward<F>(f), std::get<T>(std::move(data_))));
            }
            return Result_t<U, E>::error(std::get<E>(std::move(data_)));
        }

        template<typename F, typename U = std::invoke_result_t<F, T>>
        auto map(F&& f) && -> std::enable_if_t<std::is_void_v<T>, Result_t<U, E>> {
            if (is_ok()) {
                return Result_t<U, E>::ok(std::invoke(std::forward<F>(f)));
            }
            return Result_t<U, E>::error(std::get<E>(std::move(data_)));
        }
    };

    template<typename T, typename E>
    auto make_okay(T value) -> Result_t<E, E> {
        return Result_t<T, E>::ok(std::move(value));
    }

    template<typename T, typename E>
    auto make_error(E error) -> Result_t<T, E> {
        return Result_t<T, E>::error(std::move(error));
    }

    template<typename E>
    auto make_void() -> Result_t<void, E> {
        return Result_t<void, E>::ok();
    }

}
#endif //UTIL_HPP
