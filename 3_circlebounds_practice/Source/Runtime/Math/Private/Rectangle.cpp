#include "Precompiled.h"

Rectangle::Rectangle(const std::vector<Vector2> InVertices)
{
    // 직접 구현해보시오.
    Min = Vector2::Zero;
    Max = Vector2::Zero;

    for (auto it = InVertices.begin(); it != InVertices.end(); ++it)
    {
        (*this) += *it;
    }

}