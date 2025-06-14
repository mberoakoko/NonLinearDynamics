#include <iostream>
#include <limits>
#include <xtensor/xio.hpp>
#include <xtensor/xtensor.hpp>
#include <xtensor/xarray.hpp>
#include <xtensor/xrandom.hpp>
#include <xtensor/xview.hpp>
struct time_mesh {
    double dt;
    double t_final;

    auto generate() const -> xt::xarray<double> {
        return xt::linspace<double>(0, dt, round(t_final/dt));
    }
};

struct tensor_factory {
    static auto of(const std::vector<size_t>& shape) -> xt::xarray<double> {
        return xt::xarray<double, xt::layout_type::row_major>(shape);
    }
};


auto hello_world_x_tensor() -> void {

    xt::xarray<double> a0 = {{1., 2., 3.}, {4., 5., 6.}};
    std::cout << xt::print_options::precision(5) << a0 << std::endl;
    xt::xtensor<double, 2> a1 = xt::zeros<double>({2, 3});
    std::cout << xt::print_options::precision(5) << a1 << std::endl;
    xt::xtensor<double, 2> a2 = xt::zeros<double>({2, 3});
    std::cout <<xt::print_options::precision(5) << a1 * a2 << std::endl;
}

auto testing_standerd_libfuncs() -> void {
    auto t_mesh = time_mesh{.dt = 0.1, .t_final = 1.0}.generate();
    std::cout << xt::print_options::precision(5) << t_mesh << std::endl;
    auto output_array = xt::xarray<double>::from_shape(t_mesh.shape());
    std::ranges::transform(t_mesh, output_array.begin(), [](const auto& item){return item * 2;});
    std::cout << xt::print_options::precision(5) << output_array << std::endl;

    xt::xarray<double> a = {{1., 2., 3.}, {4., 5., 6.}};
    auto f = 2 * a;

    double d1 = a(0, 2);
    double d2 = f(1, 2);
    std::cout<< "d1 " << d1 << std::endl;
    std::cout<< "d2 " << d2 << std::endl;

}


auto force_eval() -> void {
    xt::xarray<double> xr = xt::random::rand<double>({10, 10});
    auto xr2 = xt::eval(xt::random::rand<double>({10, 10}));
    std::cout << xt::print_options::precision(5) << xr << std::endl;
}

auto test_creation() -> void {
    auto resultant_array = tensor_factory::of({1, 2, 3});
    std::cout<< xt::print_options::precision(4)<< resultant_array << std::endl;
};

auto views_demo() -> void {
    std::vector<size_t> shape = {3, 2, 4};
    xt::xarray<int> a(shape);
    a.fill(1);
    auto view_1 = xt::view(a, xt::range(0, 1), xt::all(), xt::range(1, 2));
    std::cout << xt::print_options::precision(0) << a << std::endl;
    std::cout << xt::print_options::precision(4) << view_1 << std::endl;

    auto neg_index_view = xt::view(a, xt::all(), xt::all(), -1);
    std::cout << xt::print_options::precision(0) << neg_index_view << std::endl;
}

int main() {
    force_eval();

    testing_standerd_libfuncs();
    test_creation();

    views_demo();
    return 0;
}