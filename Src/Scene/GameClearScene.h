#pragma once
#include "SceneBase.h"

class GameClearScene : public SceneBase

{
public:

	// �R���X�g���N�^
	GameClearScene(void);

	// �f�X�g���N�^
	~GameClearScene(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	// �Q�[���I�[�o�[�摜
	int imgGameClear_;

};

