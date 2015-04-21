#ifndef SNOWFLAKE_H
#define SNOWFLAKE_H

#include <cstdint>
#include "../include/CA.h"

class Snowflake : public CA::AnimatedCA2D, public CA::FirstOrderCA2D
{
public:

    Snowflake(uint32_t W, uint32_t H, uint32_t delay = 0, bool save = false) : AnimatedCA(W, H, 2, delay, save), FirstOrderCA2D(W * H, W, 7)
    {
        srand(time(NULL));
    }

private:

    std::vector<CA::C2D> N(CA::C2D c)
    {
        auto result = std::vector<CA::C2D>();

        result.reserve(7);
        for (int32_t k = -1; k <= 1; k++)
            for (int32_t j = -1; j <= 1; j++)
                if ((j != -1 || k != -1) && (j != 1 || k != 1))
                    result.push_back(L[CA::mod(c.x + j, W) + W * CA::mod(c.y + k, H)]);

        return result;
    }

    CA::State delta(CA::C2D c, std::vector<CA::State> qs)
    {
        int sum = 0;

        for (uint32_t i = 0; i < 7; i++)
            if (i != 3)
                if (qs[i] == Q[1])
                    sum++;

        return Q[qs[3] == Q[1] || (qs[3] == Q[0] && sum == 1)];
    }

    CA::State q0(CA::C2D c)
    {
        return Q[c.x == W / 2 && c.y == H / 2];
    }
};

#endif // SNOWFLAKE_H
