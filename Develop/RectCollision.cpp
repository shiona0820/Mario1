#include "RectCollision.h"
#include <algorithm>

// コンストラクタ
RectCollision::RectCollision()
    : is_blocking(false),
    object_type(eObjectType::none),
    top_left(0.0f, 0.0f),
    bottom_right(0.0f, 0.0f) {
}

RectCollision::~RectCollision() = default;

// 当たり判定対象のオブジェクトタイプか確認
bool RectCollision::IsCheckHitTarget(eObjectType hit_object) const
{
    for (eObjectType type : hit_object_type)
    {
        if (type == hit_object)
        {
            return true;  // 一致する場合、判定対象
        }
    }
    return false;  // 一致しない場合、判定対象ではない
}

// 矩形の幅を計算する
float RectCollision::GetWidth() const
{
    return bottom_right.x - top_left.x;
}

// 矩形の高さを計算する
float RectCollision::GetHeight() const
{
    return bottom_right.y - top_left.y;
}

// 矩形の位置を設定する
void RectCollision::SetPosition(const Vector2D& position, float width, float height)
{
    top_left = position;  // 左上の座標
    bottom_right = Vector2D(position.x + width, position.y + height);  // 幅と高さから右下座標を計算
}

// 矩形同士の当たり判定処理
bool IsCheckCollision(const RectCollision& rect1, const RectCollision& rect2)
{
    // 矩形が重なっているかを確認する条件
    return !(rect1.bottom_right.x < rect2.top_left.x ||   // rect1がrect2の左側
        rect1.top_left.x > rect2.bottom_right.x ||   // rect1がrect2の右側
        rect1.bottom_right.y < rect2.top_left.y ||   // rect1がrect2の上側
        rect1.top_left.y > rect2.bottom_right.y);    // rect1がrect2の下側
}
