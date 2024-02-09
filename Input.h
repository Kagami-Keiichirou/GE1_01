#pragma once
#include "windows.h"
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#include "wrl.h"
#include "WinAPP.h"

class Input
{
public:	//�����o�֐�
	
	//������
	void Initialize(WinApp* winApp);
	//�X�V
	void Update();

	bool PushKey(BYTE keyNumber);

	bool TriggerKey(BYTE keyNumber);

private: //�����o�֐�
	WinApp* winApp_ = nullptr;

	//�L�[�{�[�h�̃f�o�C�X
	Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard;
	// DirectInput�̏�����
	Microsoft::WRL::ComPtr<IDirectInput8> directInput;

	// �S�L�[�̏��
	BYTE key[256] = {};
	// �O��̑S�L�[�̏��
	BYTE keyPre[256] = {};
};