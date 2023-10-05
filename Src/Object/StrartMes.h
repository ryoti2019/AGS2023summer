#pragma once
#include "../Scene/GameScene.h"

class StartMes
{

public:

	static constexpr int SIZE_X = 300;
	static constexpr int SIZE_Y = 200;


	StartMes();
	~StartMes();

	void Init();
	void Update(void);
	void Release(void);
	void Draw(void);

	enum class Mes {
		No3,
		No2,
		No1,
		GO,
		Max
	};

	// �X�^�[�g���b�Z�[�W�̃J�E���^
	int GetCnt(void);

private:

	// �Q�[���V�[���̃|�C���^�ϐ�
	GameScene* gameScene_;

	int count_;
	int imageHdl_[static_cast<int>(Mes::Max)];

	// �J�E���g�_�E���̉�
	int cntDown_;

	// �J�E���g�_�E���̃X�^�[�g
	int start_;

};

