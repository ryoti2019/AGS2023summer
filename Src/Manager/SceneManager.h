#pragma once
#include <chrono>
class SceneBase;
class Fader;
class Camera;

class SceneManager
{

public:

	static constexpr float DEFAULT_FPS = 60.0f;

	// �V�[���Ǘ��p
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		PLAYERSELECT,
		SELECT,
		GAMESELECT,
		GAME,
		GAME2,
		GAME3,
		GAME4,
		GAME5,
		RESULT
	};

	// �C���X�^���X�̐���
	static void CreateInstance(void);

	// �C���X�^���X�̎擾
	static SceneManager& GetInstance(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	// ��ԑJ��
	void ChangeScene(SCENE_ID nextId);

	// �V�[��ID�̎擾
	SCENE_ID GetSceneID(void);

	// �f���^�^�C���̎擾
	float GetDeltaTime(void) const;
	
	// �v���C���[�̐l���̎擾
	int GetPlayerNum(void);

	// �v���C���[�̐l���̎擾
	void SetPlayerNum(int num);

	// �o�g�����[�h�̎擾
	bool GetBattleMode(void);

	// �o�g�����[�h�̐ݒ�
	void SetBattleMode(bool battleMode);

	// ���������̐ݒ�
	void SetWin1(int win);
	void SetWin2(int win);
	void SetWin3(int win);
	void SetWin4(int win);

	int GetWin1(void);
	int GetWin2(void);
	int GetWin3(void);
	int GetWin4(void);

private:

	// �ÓI�C���X�^���X
	static SceneManager* instance_;

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;

	// �t�F�[�h
	Fader* fader_;

	// �e��V�[��
	SceneBase* scene_;

	// �J����
	Camera* camera_;

	// �V�[���J�ڒ�����
	bool isSceneChanging_;

	// �f���^�^�C��
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	SceneManager(void);
	// �R�s�[�R���X�g���N�^�����l
	SceneManager(const SceneManager&);
	// �f�X�g���N�^�����l
	~SceneManager(void);

	// �f���^�^�C�������Z�b�g����
	void ResetDeltaTime(void);

	// �V�[���J��
	void DoChangeScene(SCENE_ID sceneId);

	// �t�F�[�h
	void Fade(void);

	// �v���C���[�̐l��
	int playerNum_;

	// �v���C���[�̃��[�h
	bool battleMode_;

	// �v���C���[����������
	int win1_;
	int win2_;
	int win3_;
	int win4_;

};

