#ifndef ____GetCalcs__
#define ____GetCalcs__

#include <tuple>

template<typename T>
struct GetCalcs;

template<typename... Ts>
struct GetCalcs <std::tuple<Ts...>> {
    using type = std::tuple<std::shared_ptr<Ts>...>;
    // using type = std::tuple<Ts&...>;
    type calcs = std::make_tuple(std::make_shared<Ts>()...);
};

#endif