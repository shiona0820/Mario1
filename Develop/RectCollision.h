#pragma once

#include "Utility/Vector2D.h"
#include <vector>

enum class eObjectType : unsigned char
{
    none,
    player,
    enemy,
    block,
    item,
    flag,
    dokan,
};

class RectCollision
{
public:
    bool is_blocking;
    eObjectType object_type;
    std::vector<eObjectType> hit_object_type;
    Vector2D top_left;
    Vector2D bottom_right;

    RectCollision();
    ~RectCollision();

    bool IsCheckHitTarget(eObjectType hit_object) const;
    float GetWidth() const;
    float GetHeight() const;
    void SetPosition(const Vector2D& position, float width, float height);
};

bool IsCheckCollision(const RectCollision& rect1, const RectCollision& rect2);
