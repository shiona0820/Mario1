#pragma once

#include "../Develop/Utility/Vector2D.h"
#include <vector>
#include <algorithm>  // for std::max, std::min

// オブジェクトタイプの定義
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

// 矩形コリジョン構造体
class RectCollision
{
public:
    bool is_blocking;                             // すり抜け判定フラグ
    eObjectType object_type;                      // 自身のオブジェクトタイプ
    std::vector<eObjectType> hit_object_type;     // 適用するオブジェクトタイプ
    Vector2D top_left;                            // 矩形の左上の座標
    Vector2D bottom_right;                        // 矩形の右下の座標

    RectCollision();
    ~RectCollision();

    // 当たり判定対象確認処理
    bool IsCheckHitTarget(eObjectType hit_object) const;

    // 矩形の幅と高さを取得
    float GetWidth() const;
    float GetHeight() const;

    // 矩形の位置を更新する
    void SetPosition(const Vector2D& position, float width, float height);
};

// 矩形同士の当たり判定確認関数
bool IsCheckCollision(const RectCollision& rect1, const RectCollision& rect2);
