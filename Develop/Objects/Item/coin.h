#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

class coin : public GameObject
{
private:
	std::vector<GameObject*>objects;

	std::vector<int> coin_animation;   //こいんのアニメーション

	//アニメーション用
	const int animation_num[2] = { 0,1 };
	int animation_count;
	float animation_time;

	int coin_sound;

	static coin* instance;
	coin* Coin;

public:

	coin();
	~coin();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/*virtual void OnHitCollision(GameObject* hit_object) ;*/

	void SetVelocity(float velo);

	static coin* GetInstance();

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object);

private:

	void Movement(float delta_second);
	void AnimeCount(float delta_second);

	//オブジェクト生成処理
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		//指定したクラスを生成する
		T* new_instance = new T();
		//GameObjectクラスを継承しているか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw ("ゲームオブジェクトが生成できませんでした");
		}

		//初期化処理
		new_object->Initialize();
		//位置情報の設定
		new_object->SetLocation(location);

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}
};

