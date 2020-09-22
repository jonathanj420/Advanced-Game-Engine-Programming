
#include "Precompiled.h"

Circle::Circle(const std::vector<Vector2> InVertices)
{
    float x = 0.0f;
    float y = 0.0f;

	// 위치 정보를 받아 중심과 반지름의 값을 구하는 로직 ( 직접 구현할 것 )
    for (int i = 0; i < InVertices.size(); i++) {
        x += InVertices[i].X;
        y += InVertices[i].Y;
    }
    x = x / InVertices.size();
    y = y / InVertices.size();

    Center = Vector2(x, y);


    Radius = (*std::max_element(InVertices.begin(), InVertices.end(),
        [&](Vector2 const& InLeft, Vector2 const& InRight)
        {
            return (Center - InLeft).SizeSquared() < (Center - InRight).SizeSquared();
        }
    )).Size();

}
