#pragma once
#include "SceneBase.h"

class GameOverScene : public SceneBase

{
public:

	// �R���X�g���N�^
	GameOverScene(void);

	// �f�X�g���N�^
	~GameOverScene(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	// �Q�[���I�[�o�[�摜
	int imgGameOver_;

};

