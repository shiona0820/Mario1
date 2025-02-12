#include "HatenaBlock.h"

#include "Utility/ResourceManager.h"
#include "DxLib.h"

Hatena::Hatena() : 
	 animation()
	,animation_count(0)
	,animation_time(0.0f)
{

}

Hatena::~Hatena()
{

}

void Hatena::Initialize()
{
	// 画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	//animation[animation_count] = rm->GetImages("Resource/Images/Block/hatena.png")[0];
	image = rm->GetImages("Resource/Images/Block/hatena.png")[0];
}

void Hatena::Update(float delta_second)
{
	//image = animation[animation_count];
	AnimationControl(delta_second);
}

void Hatena::Finalize()
{

}

void Hatena::OnHitCollision(GameObject* hit_object)
{
	//マリオに叩かれると、キノコを出し、
	//空ブロックになる

}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Hatena::AnimationControl(float delta_second)
{
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 4)
		{
			animation_count = 0;
		}

		//画像の設定
		image = animation[animation_count];
	}
}