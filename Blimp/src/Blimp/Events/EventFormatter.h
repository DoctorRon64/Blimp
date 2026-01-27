#pragma once
#include "Event.h"

#include <spdlog/fmt/fmt.h>

namespace fmt {
template<typename T>
struct formatter<T, char, std::enable_if_t<std::is_base_of_v<Blimp::Event, T>>> 
    : formatter<std::string_view> {
    template<typename FormatContext>
    auto format(const T& value, FormatContext& ctx) const {
        std::string text = value.ToString();
        return formatter<std::string_view>::format(text, ctx);
    }
};
}