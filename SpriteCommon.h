#pragma once
#include <wrl.h>
#include <string>
#include <dxcapi.h>

class SpriteCommon {
public:
	//初期化
	void Initialize();
private:
	static IDxcBlob* CompileShader(
		//Complierするshaderファイルパス
		const std::wstring& filePath,
		//Compilerに使用するProfile
		const wchar_t* profile,
		//DXC
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler
	);
};