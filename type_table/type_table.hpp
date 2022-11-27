#pragma once

namespace ampersand::type_table {
    template <typename... T>
    struct type_table {
        using            size_type       = std::size_t;
        static constexpr size_type count = sizeof...(T);
    };
}