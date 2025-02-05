#include "RectCollision.h"
#include <algorithm>  // std::max, std::min

/// <summary>
/// 当たり判定対象か確認する処理
/// </summary>
/// <param name="hit_object">相手のオブジェクトタイプ</param>
/// <returns>適用するオブジェクトなら true</returns>
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

/// <summary>
/// 矩形同士の当たり判定確認処理
/// </summary>
/// <param name="rect1">矩形1</param>
/// <param name="rect2">矩形2</param>
/// <returns>当たっているなら true</returns>
bool IsCheckCollision(const RectCollision& rect1, const RectCollision& rect2)
{
    // 軸分離法による判定（Axis-Aligned Bounding Box 判定）
    return !(rect1.bottom_right.x <= rect2.top_left.x || // rect1 が rect2 の左側にある
        rect1.top_left.x >= rect2.bottom_right.x ||  // rect1 が rect2 の右側にある
        rect1.bottom_right.y <= rect2.top_left.y ||  // rect1 が rect2 の上側にある
        rect1.top_left.y >= rect2.bottom_right.y);   // rect1 が rect2 の下側にある
}
