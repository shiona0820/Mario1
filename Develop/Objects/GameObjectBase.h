#pragma once

#include "../Utility/Vector2D.h"
#include "../Utility/Collision.h"

#define D_OBJECT_SIZE	(32.0f)			// �ǂ̃T�C�Y

/// <summary>
/// �����̎��
/// </summary>
enum eMobilityType
{
	Stationary,		// �Œ�
	Movable,		// ��
};

/// <summary>
/// �����蔻��̏㉺���E�A�Փ˖ʔ���
/// </summary>
enum class eCollisionSide
{
	Top,
	Bottom,
	Left,
	Right,
	None
};

enum eType {
	MARIO,
	KURIBO,
	COIN,
};

// �Q�[���I�u�W�F�N�g���N���X
class GameObjectBase
{
protected:
	class SceneBase* owner_scene;	// ���L����V�[�����
	Vector2D			location;		// �ʒu���W
	Collision	        collision;		// �����蔻����
	int					image;			// �摜���
	int					z_layer;		// ���C���[���
	eMobilityType		mobility;		// ����
	Vector2D            velocity;
	bool                flip_flag;      //���]�t���O
	bool				draw_collision_box;	//�����蔻���`��t���O

	int type;//�I�u�W�F�N�g�̃^�C�v
	int coinUI;

public:
	GameObjectBase();
	virtual ~GameObjectBase();

	/// <summary>
		/// ����������
		/// </summary>
	virtual void Initialize();
	/// <summary>
		/// �X�V����
		/// </summary>
		/// <param name="delta_second">1�t���[��������̎���</param>
	virtual void Update(float delta_second);
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="screen_offset">�I�t�Z�b�g�l</param>
	virtual void Draw(const Vector2D& screen_offset) const;
	/// <summary>
	/// �f�o�b�O�p�����蔻��`�揈��
	/// </summary>
	virtual void DrawCollision(const Vector2D& screen_offset) const;
	/// <summary>
	/// �I��������
	/// </summary>
	virtual void Finalize();


public:
	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(GameObjectBase* hit_object);

	//�����蔻��̏Փ˖ʂ�Ԃ�
	eCollisionSide GetCollisionSide(const GameObjectBase& other) const;

public:
	/// <summary>
	/// ���L�V�[�����̐ݒ�
	/// </summary>
	/// <param name="scene">���L�V�[�����</param>
	void SetOwnerScene(class SceneBase* scene);

	/// <summary>
	/// �ʒu���W�擾����
	/// </summary>
	/// <returns>�ʒu���W���</returns>
	const Vector2D& GetLocation() const;

	/// <summary>
	/// �ʒu���ύX����
	/// </summary>
	/// <param name="location">�ύX�������ʒu���</param>
	void SetLocation(const Vector2D& location);

	/// <summary>
	/// �����蔻��擾����
	/// </summary>
	/// <returns>�����蔻����</returns>
	Collision GetCollision() const;

	/// <summary>
	/// �y���C���[���擾����
	/// </summary>
	/// <returns>�y���C���[���</returns>
	const int GetZLayer() const;

	/// <summary>
	/// �������̎擾����
	/// </summary>
	/// <returns>�������</returns>
	const eMobilityType GetMobility() const;

	/// <summary>
	/// �f�o�b�O�p�����蔻��\���t���O��ݒ肷��
	/// </summary>
	void SetDrawCollisionBox(bool flag);

	bool flag;
};
