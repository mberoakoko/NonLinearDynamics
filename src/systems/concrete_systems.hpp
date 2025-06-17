//
// Created by mbero on 14/06/2025.
//

#ifndef CONCRETE_SYSTEMS_HPP
#define CONCRETE_SYSTEMS_HPP
#include <bits/stdc++.h>
#include <optional>
#include <xtensor/xarray.hpp>
#include "system_base.hpp"

namespace Systems {

    class LotkaVolterra: public Systems::ISystem<double> {
    public:
        struct Params {
            double alpha ;
            double beta ;
            double gamma;
            double delta;
        };
        explicit LotkaVolterra(double alpha, double beta, double gamma, double delta)
        :   Systems::ISystem<double>(),
            alpha_(alpha),
            beta_(beta),
            gamma_(gamma),
            delta_(delta) {}
        explicit LotkaVolterra(const Params& params)
        :   LotkaVolterra(params.alpha, params.beta, params.gamma, params.delta){};

        auto update(double t, const xt::xarray<double> &x_state,
            const std::optional<xt::xarray_container<xt::uvector<double>>> &u_forcing) -> xt::xarray<double> override {
            xt::xarray<double> result(state_shape);
            result(0) = alpha_ * x_state(0) + beta_ * x_state(0) * x_state(1);
            result(1) = -gamma_ * x_state(1) + delta_ * x_state(1) * x_state(0);
            return result;
        };

        auto output(double t, const xt::xarray<double> &x_state,
            const std::optional<xt::xarray_container<xt::uvector<double>>> &u_forcing) -> xt::xarray<double> override {
            return x_state;
        };

        auto get_state_shape() const -> std::vector<std::size_t> { return state_shape; };
    private:
        double alpha_, beta_, gamma_, delta_;
        std::vector<std::size_t> state_shape {2 };

    };
}
#endif //CONCRETE_SYSTEMS_HPP
