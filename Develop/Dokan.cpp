#include "Dokan.h"
#include "DxLib.h"

Dokan::Dokan()
{

}

Dokan::~Dokan()
{

}

void Dokan::Initialize()
{
	// 当たり判定の設定
	box_size = 32.0f;
}

void Dokan::Draw(const Vector2D& screen_offset) const
{

}

void Dokan::Finalize()
{

}

void Dokan::OnHitCollision(GameObject* hit_object)
{
	//もし、4つ目の土管に入ったら地下マップへ行く
}