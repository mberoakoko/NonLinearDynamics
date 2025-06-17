//
// Created by mbero on 14/06/2025.
//

#ifndef SYSTEM_BASE_HPP
#define SYSTEM_BASE_HPP
#include <optional>
#include <xtensor/xarray.hpp>

namespace Systems {
    template<typename T>
    class ISystem {
    public:
        virtual ~ISystem() = default;

        virtual auto update(T t, const xt::xarray<T>& x_state, const std::optional<xt::xarray<T>>& u_forcing) -> xt::xarray<T> = 0;
        virtual auto output(T t, const xt::xarray<T>& x_state, const std::optional<xt::xarray<T>>& u_forcing) -> xt::xarray<T> = 0;

        virtual auto step(T t , const xt::xarray<T>& x_state, const std::optional<xt::xarray<T>>& u_forcing) -> xt::xarray<T>{
            auto temp_state = update(t, x_state, u_forcing);
            return output(t, temp_state, u_forcing);
        }


    };

}

#endif //SYSTEM_BASE_HPP
