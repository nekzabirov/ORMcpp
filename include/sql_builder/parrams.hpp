//
// Created by Nekbakht Zabirov on 25.10.2024.
//

#ifndef PARRAMS_HP
#define PARRAMS_HP
#include <ostream>

namespace nek::sql {
    template<typename T>
    concept Streamable = requires(std::ostream &os, T t)
    {
        os << t;
    };
}

#endif //PARRAMS_HP
