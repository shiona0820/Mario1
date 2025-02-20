#include "Player.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

#define D_PLAYER_SPEED	(50.0f)
#define D_GRAVITY (9.807f)   //重力加速ど


Player* Player::instance = nullptr;

Player::Player() :
	move_animation(),
	jump_animation(),
	dying_animation(),
	velocity(0.0f),
	player_state(ePlayerState::IDLE),
	now_direction_state(eDirectionState::LEFT),
	next_direction_state(eDirectionState::LEFT),
	animation_time(0.0f),
	//old_panel(ePanelID::NONE),
	player(nullptr),
	scroll_end(false),
	jump_location(Vector2D(0.0f)),
	jump_velocity(Vector2D(0.0f))
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	// アニメーション画像の読み込み
	move_animation = rm->GetImages("Resource/images/Mario/mario.png", 9, 9, 1, 32, 32);
	jump_animation = rm->GetImages("Resource/images/Mario/mario.png", 9, 9, 1, 32, 32);
	//ジャンプのSE
	jump_SE = rm->GetSounds("Resource/Sounds/SE_SuperJump.wav");

	//当たり判定を設定
	collision.SetSize(D_OBJECT_SIZE, D_OBJECT_SIZE);

	//オブジェクトタイプを設定
	collision.SetObjectType(eObjectType::ePlayer);

	//当たるオブジェクトタイプを設定
	collision.SetHitObjectType({ eObjectType::eEnemy, eObjectType::eGround });

	//当たり判定の描画フラグ
	SetDrawCollisionBox(false);

	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;

	// お試し用(変数)
	// プレイヤー初期位置と速度
	is_on_ground = true;
	// スクロール初期化
	scroll_offset = 0.0f;
	ground_y = 500.0f;    // 地面のY座標
	//ここまで*/

	image = move_animation[0];
	//エラーチェック
	if (image == -1)
	{
		throw("マリオの画像がありません\n");
	}
}

void Player::Update(float delta_second)
{
	//重力速度の計算
	if (!is_on_ground) {
		velocity.y += D_GRAVITY * delta_second;
	}

	if (location.y + velocity.y * delta_second >= ground_y) // 地面位置に達した場合
	{
		location.y = ground_y;
		velocity.y = 0.0f;
		g_velocity = 0.0f;
		is_on_ground = true;
		player_state = ePlayerState::IDLE;
	}

	//当たり判定の位置を取得する
	Vector2D collisionPosition = collision.GetPosition();
	//当たり判定の位置を更新する
	collision.SetPosition(location);

	InputManager* Input = InputManager::GetInstance();

	// プレイヤー状態によって、動作を変える
	switch (player_state)
	{
	case ePlayerState::IDLE:
		// 画像の設定
		image = move_animation[0];
		velocity.x = 0;
		if (Input->GetKey(KEY_INPUT_A) || Input->GetKey(KEY_INPUT_D))
		{
			player_state = ePlayerState::MOVE;
			
		}
		else if (Input->GetKeyDown(KEY_INPUT_SPACE))
		{
			player_state = ePlayerState::Jump;
			/*PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);*/
		}
		break;

	case ePlayerState::MOVE:
		// 移動処理
		Movement(delta_second);
		// アニメーション制御
		AnimationControl(delta_second);
		break;

	case ePlayerState::DIE:
		// 死亡中のアニメーション
		animation_time += delta_second;
		if (animation_time >= 0.07f)
		{
			animation_time = 0.0f;
			animation_count++;
			// 復活させる
			if (animation_count >= dying_animation.size())
			{
				player_state = ePlayerState::IDLE;
				animation_count = 0;
				is_destroy = true;
			}
		}
		image = dying_animation[animation_count];
		break;

		case ePlayerState::Damage:
			//ダメージを受けた時のアニメーション
			animation_time += delta_second;

		case ePlayerState::Jump:
			// 移動処理
			Movement(delta_second);
			PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);

			break;

	default:
		break;
	}
	location += velocity;
}

void Player::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Player::Finalize()
{
	// 動的配列の解放
	move_animation.clear();
	dying_animation.clear();
}

/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void Player::OnHitCollision(GameObjectBase* hit_object)
{
	/*/ 当たった、オブジェクトが壁だったら
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// 当たり判定情報を取得して、カプセルがある位置を求める
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// 最近傍点を求める
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Playerからnear_pointへの方向ベクトルを取得
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// めり込んだ差分
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diffの分だけ戻る
		location += dv.Normalize() * diff;
	}

	// 当たった、オブジェクトが通常餌だったら
	if (hit_object->GetCollision().object_type == eObjectType::food)
	{
		food_count++;

	}

	// 当たった、オブジェクトがパワー餌だったら
	if (hit_object->GetCollision().object_type == eObjectType::power_food)
	{
		food_count++;
		is_power_up = true;
	}*/

	/*/ 当たったオブジェクトが敵だったら
	if (hit_object->GetCollision().object_type == eObjectType::enemy)
	{

	}*/

	// 当たったオブジェクトが土管だったら
	// 当たったオブジェクトがゴールフラッグなら

}

/// <summary>
/// プレイヤーの状態を取得する
/// </summary>
/// <returns>プレイヤーの状態</returns>
ePlayerState Player::GetPlayerState() const
{
	return player_state;
}

/// <summary>
/// プレイヤーがパワーアップしてるか確認する
/// </summary>
/// <returns>プレイヤーの状態</returns>
bool Player::GetPowerUp() const
{
	return is_power_up;
}

/// <summary>
/// パワーダウンさせる
/// </summary>
void Player::SetPowerDown()
{
	is_power_up = false;
}

bool Player::GetDestroy() const
{
	return is_destroy;
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Player::Movement(float delta_second)
{

	InputManager* Input = InputManager::GetInstance();

	//Aボタンを押したら左に進む
	if (Input->GetKey(KEY_INPUT_A))
	{
		velocity.x = -0.8f;
		flip_flag = true;

		//SPACEを押したらジャンプさせたい
		//SE鳴らす
		if (Input->GetKeyDown(KEY_INPUT_SPACE))
		{

			player_state = ePlayerState::Jump;

			// ジャンプ中のアニメーション
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
				image = jump_animation[jump_animation_num[animation_count]];
			}

			PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);
		}
		player_state = ePlayerState::MOVE;
	}

	//Dボタンを押したら右に進む
	else if (Input->GetKey(KEY_INPUT_D))
	{
		velocity.x = 0.8f;
		flip_flag = false;

		//SPACEを押したらジャンプさせたい
		//SE鳴らす
		if (Input->GetKeyDown(KEY_INPUT_SPACE))
		{

			player_state = ePlayerState::Jump;

			// ジャンプ中のアニメーション
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
				image = jump_animation[jump_animation_num[animation_count]];
			}

			PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);
		}

		player_state = ePlayerState::MOVE;
	}

	//SPACEを押したらジャンプさせたい
	//SE鳴らす
	else if(Input->GetKey(KEY_INPUT_SPACE))
	{
		// ジャンプ中のアニメーション
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
			image = jump_animation[jump_animation_num[animation_count]];
		}
		player_state = ePlayerState::Jump;

		PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);

	}
	else
	{
		velocity.x = 0;
		player_state = ePlayerState::IDLE;
	}

	//画面外に行かないようにする処理
	if (location.x < 16.0f)
	{
		location.x = 16.0f;
	}

	//画面中央より先に進まない
	if (scroll_end == false)
	{
		if (location.x >= 640.0f / 2)
		{
			location.x = 640.0f / 2;
		}
	}
	else
	{
		//画面外に行かないようにする処理
		if (location.x > 600.0f)
		{
			location.x = 600.0f;
		}
	}
}

/// <summary>
/// ジャンプ処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Player::JumpMoment(float delta_second)
{
	InputManager* Input = InputManager::GetInstance();

		if (Input->GetKey(KEY_INPUT_SPACE) && is_on_ground == true)
		{
			velocity.y = -4.0f;
			JumpAnimationControl(delta_second);
			player_state = ePlayerState::Jump;
			is_on_ground = false;
			PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);
		}
}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Player::AnimationControl(float delta_second)
{
	// 移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= (1.0f / 8.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 4)
		{
			animation_count = 0;
		}
		// 画像の設定
			image = move_animation[animation_num[animation_count]];
	}
}

/// <summary>
/// 左右移動アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Player::WalkAnimationControl(float delta_second)
{
	// 移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= (1.0f / 8.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 4)
		{
			animation_count = 0;
		}
		// 画像の設定
		image = move_animation[animation_num[animation_count]];
	}
}

/// <summary>
/// ジャンプするアニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Player::JumpAnimationControl(float delta_second)
{
	// ジャンプ中のアニメーション
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
		image = jump_animation[jump_animation_num[animation_count]];
	}

	PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);
}

Player* Player::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Player();
	}
	return instance;
}

const Vector2D& Player::GetVelocity() const
{
	return velocity;
}

void Player::SetScrollEnd()
{
	scroll_end = true;
}

ePlayerState Player::PlayerState()
{
	return player_state;
}
