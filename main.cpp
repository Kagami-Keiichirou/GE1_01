#include "input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "Sprite.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    //ポインタ
    Input* input_ = nullptr;
    WinApp* winApp_ = nullptr;
    DirectXCommon* dxCommon_ = nullptr;
    SpriteCommon* spriteCommon_ = nullptr;
    Sprite* sprite_ = nullptr;

    // windowsAPIの初期化
    winApp_ = new WinApp();
    winApp_->Initialize();

    // dxの初期化
    dxCommon_ = new DirectXCommon();
    dxCommon_->Initialize(winApp_);

    // 入力の初期化
    input_ = new Input();
    input_->Initialize(winApp_);

    // スプライトコモンの初期化
    spriteCommon_ = new SpriteCommon();
    spriteCommon_->Initialize(dxCommon_);

    // スプライトの初期化
    sprite_ = new Sprite();
    sprite_->Initialize(dxCommon_, spriteCommon_);

    // ゲームループ
    while (true) {
        //更新
        if (winApp_->Update() == true) {
            break;
        }

        //入力の更新
        input_->Update();

        //更新前処理
        dxCommon_->PreDraw(); 
        
        sprite_->Draw();

        //更新後処理
        dxCommon_->PostDraw();
    }

    // 入力解放
    delete input_;
    // WindowsAPI解放
    winApp_->Finalize();
    delete winApp_;

    delete dxCommon_;

    delete spriteCommon_;

    delete sprite_;

    return 0;
}
