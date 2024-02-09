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
public:	//メンバ関数
	
	//初期化
	void Initialize(WinApp* winApp);
	//更新
	void Update();

	bool PushKey(BYTE keyNumber);

	bool TriggerKey(BYTE keyNumber);

private: //メンバ関数
	WinApp* winApp_ = nullptr;

	//キーボードのデバイス
	Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard;
	// DirectInputの初期化
	Microsoft::WRL::ComPtr<IDirectInput8> directInput;

	// 全キーの状態
	BYTE key[256] = {};
	// 前回の全キーの状態
	BYTE keyPre[256] = {};
};