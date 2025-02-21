#include "kuribo.h"

#include "../../Utility/ResourceManager.h"
#include "../Mario/Player.h"

#include "DxLib.h"

kuribo* kuribo::instance = nullptr;

kuribo::kuribo():
	move_animation(),
	kuribo_state(eKuriboState::WALK)
{

}

kuribo::~kuribo()
{

}

void kuribo::Initialize()
{
	//アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/images/Enemy/kuribo.png", 3, 3, 1, 32, 32);

	image = move_animation[0];

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eBlock);

	//エラーチェック
	if (image == -1)
	{
		throw("クリボーの画像がありません\n");
	}

	velocity.x = -0.1;

	//当たり判定を設定
	collision.SetSize(D_OBJECT_SIZE, D_OBJECT_SIZE);

	//オブジェクトタイプを設定
	collision.SetObjectType(eObjectType::eEnemy);

	//当たるオブジェクトタイプを設定
	collision.SetHitObjectType({ eObjectType::ePlayer, eObjectType::eGround });

	//当たり判定の描画フラグ
	SetDrawCollisionBox(false);

}


void kuribo::Update(float delta_second)
{
	velocity.x = -0.1;
	location += velocity;

	//当たり判定の位置を取得する
	Vector2D collisionPosition = collision.GetPosition();
	//当たり判定の位置を更新する
	collision.SetPosition(location);

	switch (kuribo_state)
	{
	case WALK:
		// アニメーション制御
		AnimeCount(delta_second);
		break;
	case STEP:
		
		break;
	default:
		break;
	}

}

void kuribo::Draw(const Vector2D& screen_offset) const 
{
	__super::Draw(screen_offset);
}

void kuribo::Finalize()
{

}

void kuribo::OnHitCollision(GameObject* hit_object)
{

	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		//kuriboを消滅する
		owner_scene->DestroyObject(this);
	}
}


void kuribo::AnimeCount(float delta_second)
{
	// 移動中のアニメーション
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
		image = move_animation[animation_num[animation_count]];
	}
}

void kuribo::Movement(float delta_second)
{

}

kuribo* kuribo::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new kuribo();
	}
	return instance;
}

void kuribo::SetVelocity(float velo)
{
	location.x -= velo;
}