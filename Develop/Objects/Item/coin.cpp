#include "coin.h"

#include "../../Utility/ResourceManager.h"

#include "DxLib.h"

coin* coin::instance = nullptr;

coin::coin() :
	coin_animation()
{
	coin_sound = NULL;
}

coin::~coin()
{

}

void coin::Initialize()
{
	//アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	coin_animation = rm->GetImages("Resource/images/Item/coin.png", 4, 4, 1, 32, 32);
	//コインseの読み込み
	coin_sound = rm->GetSounds("Resource/Sounds/SE_CoinPickUp.wav");

	image = coin_animation[0];

	//エラーチェック
	if (image == -1)
	{
		throw("coinの画像がありません\n");
	}

	type = COIN;

}

void coin::Update(float delta_second)
{
	
	AnimeCount(delta_second);

}

void coin::Draw(const Vector2D& screen_offset) const
{



	if (flag == true)
	{
		__super::Draw(screen_offset);
	}

	/*__super::Draw(screen_offset);*/
}

void coin::Finalize()
{

}

void coin::AnimeCount(float delta_second)
{
	animation_time += delta_second;
	if (animation_time >= (1.0f / 8.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}
		// 画像の設定
		image = coin_animation[animation_num[animation_count]];
	}
}

void coin::Movement(float delta_second)
{

}

coin* coin::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new coin();
	}
	return instance;
}

void coin::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	//coinSEの再生
	PlaySoundMem(coin_sound, DX_PLAYTYPE_NORMAL, TRUE);
	flag = false;
	Finalize();
}


void coin::SetVelocity(float velo)
{
	location.x -= velo;
}