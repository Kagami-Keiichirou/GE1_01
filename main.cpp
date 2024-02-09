#include "input.h"
#include "WinApp.h"
#include "DirectXCommon.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    //ポインタ
    Input* input_ = nullptr;
    WinApp* winApp_ = nullptr;
    DirectXCommon* dxCommon_ = nullptr;

#pragma region WindowsAPI初期化処理

    // windowsAPIの初期化
    winApp_ = new WinApp();
    winApp_->Initialize();

#pragma endregion

#pragma region DirectX初期化処理
    
    // dxの初期化
    dxCommon_ = new DirectXCommon();
    dxCommon_->Initialize(winApp_);

#pragma endregion

    //入力の初期化
    input_ = new Input();
    input_ ->Initialize(winApp_);

    // ゲームループ
    while (true) {
        //更新
        if (winApp_->Update() == true) {
            break;
        }

        //入力の更新
        input_->Update();

        //更新前処理
        dxCommon_->PostDraw();

        //更新後処理
        dxCommon_->PostDraw();
    }

    // 入力解放
    delete input_;
    // WindowsAPI解放
    winApp_->Finalize();
    delete winApp_;

    delete dxCommon_;

    return 0;
}
