//
// Created by mbero on 15/06/2025.
//

#ifndef MULTISTEP_INTEGRATOR_HPP
#define MULTISTEP_INTEGRATOR_HPP
#include <bits/stdc++.h>
#include <optional>
#include <xtensor/xarray.hpp>
#include "../systems/system_base.hpp"
namespace Integrator {
    enum class ThetaTrapezoidalMode: std::uint8_t {
        Euler = 0, Trapezoidal = 1
    };

    template<ThetaTrapezoidalMode mode, typename T>
    class ThetaMethod {
    public:
        explicit ThetaMethod(
            const Systems::ISystem<T>& system,
            const double& dt,
            const xt::xarray<double>& initial_state,
            const std::optional<xt::xarray<double>>& initial_forcing)
        :   system_(system),
            u_forcing_(initial_forcing),
            x_state_(initial_state){}

        auto step(T t, const xt::xarray<T>& x_state, const std::optional<xt::xarray<T>>& u_forcing) -> xt::xarray<T> {
            auto temp_x_n_1 = system_.step(t + dt_ , x_state, u_forcing);
            x_state = x_state * dt_ * (mode * system_.step())
            return
        }

    private:
        Systems::ISystem<T> system_;
        xt::xarray<T> x_state_;
        xt::xarray<T> u_forcing_;
        double dt_;
        double theta
        ThetaTrapezoidalMode mode_ = mode;
    };
}
#endif //MULTISTEP_INTEGRATOR_HPP
