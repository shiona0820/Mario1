#include "RectCollision.h"

RectCollision::RectCollision()
    : is_blocking(false),
    object_type(eObjectType::none),
    top_left(0.0f, 0.0f),
    bottom_right(0.0f, 0.0f) {
}

RectCollision::~RectCollision() = default;

bool RectCollision::IsCheckHitTarget(eObjectType hit_object) const
{
    for (eObjectType type : hit_object_type)
    {
        if (type == hit_object)
        {
            return true;
        }
    }
    return false;
}

float RectCollision::GetWidth() const
{
    return bottom_right.x - top_left.x;
}

float RectCollision::GetHeight() const
{
    return bottom_right.y - top_left.y;
}

void RectCollision::SetPosition(const Vector2D& position, float width, float height)
{
    top_left = position;
    bottom_right = Vector2D(position.x + width, position.y + height);
}

bool IsCheckCollision(const RectCollision& rect1, const RectCollision& rect2)
{
    return !(rect1.bottom_right.x <= rect2.top_left.x ||
        rect1.top_left.x >= rect2.bottom_right.x ||
        rect1.bottom_right.y <= rect2.top_left.y ||
        rect1.top_left.y >= rect2.bottom_right.y);
}
