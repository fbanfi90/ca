#ifndef BRIAN_S_BRAIN_H
#define BRIAN_S_BRAIN_H

#include <cstdint>
#include "CA.h"

class BriansBrain :
        public CA::IAnimatedCA2D,
        public CA::IFirstOrderCA2D,
        public CA::IRandomInitCA<CA::C2D>
{
public:

    BriansBrain(uint32_t W, uint32_t H, uint32_t delay = 0, bool save = false) :
            IAnimatedCA(W, H, 3, delay, save),
            IFirstOrderCA2D(W * H, W, 9),
            IRandomInitCA(3)
    {
        srand(time(NULL));
    }

private:

    std::vector<CA::C2D> N(const CA::C2D& c)
    {
        auto result = std::vector<CA::C2D>();

        result.reserve(9);
        for (int32_t k = -1; k <= 1; k++)
            for (int32_t j = -1; j <= 1; j++)
                result.push_back(L[CA::mod(c.x + j, W) + W * CA::mod(c.y + k, H)]);

        return result;
    }

    CA::State delta(const CA::C2D& c, const std::vector<CA::State>& qs)
    {
        uint32_t sum = 0;

        for (uint32_t i = 0; i < 9; i++)
            if (i != 4)
                if (qs[i] == Q[2])
                    sum++;

        return Q[qs[4] == Q[0] && sum == 2 ? 2 : qs[4] == Q[2]];
    }
};

#endif // BRIAN_S_BRAIN_H
