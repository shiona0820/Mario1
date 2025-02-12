#pragma once


/*メモ
* 爆撃ハンターと過去の自分の作成したマリオのプロジェクトの見直しをする
* 爆撃ハンターで範囲を学ぶ、過去の自分の作成したマリオのプロジェクトでプレイヤーの動きを考える
* それぞれのクラスに当たり判定が設定されていないのは、おそらくサイズがないからかもしれない。サイズのことは調べる。
*/
#include "GameObjectBase.h"
#include "../Scene/SceneBase.h"
#include "../Utility/Vector2D.h"

// ゲームオブジェクトクラス
class GameObject : public GameObjectBase
{
public:
    GameObject() = default;
    virtual ~GameObject() = default;

    /// <summary>
    /// ゲームオブジェクト生成処理
    /// </summary>
    /// <typeparam name="OBJECT">生成するゲームオブジェクトクラス</typeparam>
    /// <param name="generate_location">生成位置</param>
    /// <returns>生成したゲームオブジェクトのポインタ</returns>
    template <class OBJECT>
    OBJECT* CreateObject(const Vector2D& generate_location)
    {
        if (owner_scene)
        {
            return owner_scene->CreateObject<OBJECT>(generate_location);
        }
        return nullptr;
    }

    /// <summary>
    /// オブジェクト破棄処理
    /// </summary>
    /// <param name="target">破棄を行うゲームオブジェクトのポインタ</param>
    void DestroyObject(GameObjectBase* target)
    {
        if (owner_scene)
        {
            owner_scene->DestroyObject(target);
        }
    }

    /// <summary>
    /// スクリーンオフセット情報取得処理
    /// </summary>
    /// <returns>スクリーンオフセット値</returns>
    const Vector2D GetScreenOffset() const
    {
        if (owner_scene)
        {
            return owner_scene->GetScreenOffset();
        }
        return Vector2D(0.0f, 0.0f);
    }
};
