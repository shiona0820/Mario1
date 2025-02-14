#include "RectCollision.h"

RectCollision::RectCollision()
    : is_blocking(false),
    object_type(eObjectType::none),
    top_left(0.0f, 0.0f),
    bottom_right(0.0f, 0.0f) {
}

RectCollision::~RectCollision() = default;

bool RectCollision::IsCheckHitTarget(eObjectType targetType) const
{
    if (hit_object_type.empty()) return false;  // �����ŋ�Ȃ瑦���^�[��

    for (size_t i = 0; i < hit_object_type.size(); i++)
    {
        if (hit_object_type[i] == targetType)
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

bool RectCollision::IsColliding(const RectCollision& other) const
{
    return !(this->bottom_right.x < other.top_left.x ||  // �����̉E�[������̍��[��荶
        this->top_left.x > other.bottom_right.x ||  // �����̍��[������̉E�[���E
        this->bottom_right.y < other.top_left.y ||  // �����̉��[������̏�[����
        this->top_left.y > other.bottom_right.y);   // �����̏�[������̉��[��艺
}

