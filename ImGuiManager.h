#pragma once
#include "DirectXCommon.h"

class ImGuiManager
{
public:
	// ������
	static void Initialize(HWND hwnd, DirectXCommon* dxCommon);
	// �X�V�J�n
	static void NewFrame();
	// �X�V�I��
	static void CreateCommand();
	// �R�}���h��ǂ�
	static void CommandsExcute(ID3D12GraphicsCommandList* commandList);
	// new����
	static ImGuiManager* Create();
	// �f�X�g���N�^
	~ImGuiManager();

	void ShowDemo();
};

