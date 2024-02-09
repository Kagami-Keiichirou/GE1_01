#pragma once
#include <Windows.h>

// WindowsAPI
class WinApp {
public: //�����o�֐�
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	//������
	void Initialize();

	// �X�V
	bool Update();
	
	// �㏈��
	void Finalize();

	//Getter
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance() const { return w.hInstance; }

	// �E�B���h�E�T�C�Y
	static const int window_width = 1280;  // ����
	static const int window_height = 720;  // �c��
private:
	HWND hwnd = nullptr;
	WNDCLASSEX w{};

	MSG msg{};  // ���b�Z�[�W};
};