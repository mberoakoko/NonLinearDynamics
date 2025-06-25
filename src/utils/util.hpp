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
        bool is_success_ { false };


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

    };
}
#endif //UTIL_HPP
