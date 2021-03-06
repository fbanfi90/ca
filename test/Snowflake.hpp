#pragma once

#include "CA.h"

class Snowflake :
        public CA::IAnimatedCA2D,
        public CA::IFirstOrderCA2D,
        public CA::ICentralInitCA2D
{
public:

    Snowflake(uint32_t width, uint32_t height, uint32_t delay = 0, bool save = false) :
            IAnimatedCA(width, height, 2, delay, save),
            IFirstOrderCA2D(7),
            ICentralInitCA2D(1, 0)
    {
        srand(time(NULL));
    }

private:

    std::vector<CA::C2D> N(const CA::C2D& c)
    {
        auto result = std::vector<CA::C2D>();

        result.reserve(7);
        for (int32_t k = -1; k <= 1; k++)
            for (int32_t j = -1; j <= 1; j++)
                if ((j != -1 || k != -1) && (j != 1 || k != 1))
                    result.push_back(L[CA::mod(c.x + j, width) + width * CA::mod(c.y + k, height)]);

        return result;
    }

    CA::State delta(const CA::C2D& c, const std::vector<CA::State>& qs)
    {
        int sum = 0;

        for (uint32_t i = 0; i < 7; i++)
            if (i != 3)
                if (qs[i] == Q[1])
                    sum++;

        return Q[qs[3] == Q[1] || (qs[3] == Q[0] && sum == 1)];
    }
};
