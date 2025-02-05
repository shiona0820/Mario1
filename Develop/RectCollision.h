#pragma once

#include "../Develop/Utility/Vector2D.h"
#include <vector>

// オブジェクトタイプの定義
enum class eObjectType : unsigned char
{
    none,
    player,
    enemy,
    wall,
    item,
};

// 矩形コリジョン構造体
class RectCollision
{
public:
    bool is_blocking;                             // すり抜け判定フラグ
    eObjectType object_type;                      // 自身のオブジェクトタイプ
    std::vector<eObjectType> hit_object_type;     // 適用するオブジェクトタイプ
    Vector2D top_left;                            // 矩形の左上の座標
    Vector2D bottom_right;                        // 矩形の右下の座標

    RectCollision() :
        is_blocking(false),
        object_type(eObjectType::none),
        top_left(0.0f, 0.0f),
        bottom_right(0.0f, 0.0f) {
    }

    ~RectCollision() = default;

    // 当たり判定対象確認処理
    bool IsCheckHitTarget(eObjectType hit_object) const;

    // 矩形の幅と高さを取得
    float GetWidth() const { return bottom_right.x - top_left.x; }
    float GetHeight() const { return bottom_right.y - top_left.y; }

    // 矩形の位置を更新する
    void SetPosition(const Vector2D& position, float width, float height)
    {
        top_left = position;
        bottom_right = Vector2D(position.x + width, position.y + height);
    }
};

// 矩形同士の当たり判定確認関数
bool IsCheckCollision(const RectCollision& rect1, const RectCollision& rect2);
