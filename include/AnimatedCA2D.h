#ifndef ANIMATED_CA_2D_H
#define ANIMATED_CA_2D_H

#include "AnimatedCA.hpp"

namespace CA {

class AnimatedCA2D : virtual public AnimatedCA<C2D>
{
protected:

    AnimatedCA2D();

public:

    void animate();
};

} // CA

#endif // ANIMATED_CA_2D_H