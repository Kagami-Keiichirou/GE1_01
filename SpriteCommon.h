#pragma once
#include <wrl.h>
#include <string>
#include <dxcapi.h>
#include <d3d12.h>

#include "DirectXCommon.h"

class SpriteCommon {
private:
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	//������
	void Initialize(DirectXCommon* dxCommon);

	//Getter
	ID3D12RootSignature* GetRootSignature() { return rootSignature.Get(); }
	ID3D12PipelineState* GetPipelineState() { return pipelineState.Get(); }
private:
	static IDxcBlob* CompileShader(
		//Complier����shader�t�@�C���p�X
		const std::wstring& filePath,
		//Compiler�Ɏg�p����Profile
		const wchar_t* profile,
		//DXC
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler
	);

	DirectXCommon* dxCommon_ = nullptr;

	ComPtr<ID3D12RootSignature> rootSignature;
	ComPtr<ID3D12PipelineState> pipelineState;
};