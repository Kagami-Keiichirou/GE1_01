#include "sprite.h"
#include "d3d12.h"
#include <wrl.h>

#include "DirectXMath.h"

using namespace Microsoft::WRL;
using namespace DirectX;

void Sprite::Initialize(DirectXCommon* dxCommon, SpriteCommon* common)
{
	dxCommon_ = dxCommon;
	common_ = common;

	//VertexResource
	D3D12_HEAP_PROPERTIES uploadHeapPropertimes{};
	uploadHeapPropertimes.Type = D3D12_HEAP_TYPE_UPLOAD;
	D3D12_RESOURCE_DESC vertexResourceDesc{};
	vertexResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	vertexResourceDesc.Width = sizeof(XMFLOAT4) * 3;
	vertexResourceDesc.Height = 1;
	vertexResourceDesc.DepthOrArraySize = 1;
	vertexResourceDesc.MipLevels = 1;
	vertexResourceDesc.SampleDesc.Count = 1;
	vertexResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	HRESULT result = dxCommon_->GetDevice()->CreateCommittedResource(
		&uploadHeapPropertimes, D3D12_HEAP_FLAG_NONE,
		&vertexResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertexResource));
	assert(SUCCEEDED(result));

	//頂点バッファービューを作成する
	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = sizeof(XMFLOAT4) * 3;
	vertexBufferView.StrideInBytes = sizeof(XMFLOAT4);
}

void Sprite::Draw() {
	XMFLOAT4* vertexData = nullptr;
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	//左下
	vertexData[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
	//上
	vertexData[1] = { 0.0f, 0.5f, 0.0f, 1.0f };
	//右下
	vertexData[2] = { 0.5f, -0.5f, 0.0f, 1.0f };

	dxCommon_->GetCommandList()->SetGraphicsRootSignature(common_->GetRootSignature());
	dxCommon_->GetCommandList()->SetPipelineState(common_->GetPipelineState());
	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
	dxCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//マテリアルCBufferの場所を設定
	dxCommon_->GetCommandList()->DrawInstanced(3,1,0,0);
}