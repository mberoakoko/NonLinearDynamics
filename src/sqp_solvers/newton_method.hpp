//
// Created by mbero on 17/06/2025.
//

#ifndef NEWTON_METHOD_HPP
#define NEWTON_METHOD_HPP
#include <bits/stdc++.h>
#include <xtensor/xarray.hpp>
namespace Solvers {

    template<typename T>
    using NewtonDirection = std::function<xt::xarray<T>(xt::xarray<T>)>;

    template<typename T>
    using func = std::function(xt::xarray<T>(xt::xarray<T>));

    template<typename T>
    class NewtonMethod {
        T tol;
    public:
        struct params {
            func<T> f;
            NewtonDirection<T> delta_x;
            T tolerance;
        };

        explicit NewtonMethod(func<T> func, NewtonDirection<T> delta_x, const T& tolerance)
        :   tol(tolerance),
            func_(func),
            delta_x_(delta_x){};

        explicit NewtonMethod(params p): tol(p.tolerance), func_(p.f), delta_x_(p.delta_x){};

        auto step(const xt::xarray<T>& x) -> xt::xarray<T> {
            xt::xarray<T> res(x);
            while (xt::abs(func_(res)) > tol) {

            }
        };

    private:
        params params_;
        func func_;
        NewtonDirection<T> delta_x_;
    };
}
#endif //NEWTON_METHOD_HPP
