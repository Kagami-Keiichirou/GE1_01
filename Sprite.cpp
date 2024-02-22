#include "sprite.h"
#include "d3d12.h"
#include <wrl.h>

#include "DirectXMath.h"
#include "BufferResource.h"

using namespace Microsoft::WRL;
using namespace DirectX;

void Sprite::Initialize(DirectXCommon* dxCommon, SpriteCommon* common)
{
	dxCommon_ = dxCommon;
	common_ = common;

	// ���_���
	CreateVertex();
	// �F
	CreateMaterial();
	// �s��
	CreateWVP();
}

void Sprite::Draw() {
	dxCommon_->GetCommandList()->SetGraphicsRootSignature(common_->GetRootSignature());
	dxCommon_->GetCommandList()->SetPipelineState(common_->GetPipelineState());
	// ���_���
	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
	dxCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// �F���
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	// �s��
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());
	
	dxCommon_->GetCommandList()->DrawInstanced(3,1,0,0);
}

void Sprite::CreateVertex() {
	//VertexResource
	vertexResource = CreateBufferResource(dxCommon_->GetDevice(), sizeof(XMFLOAT4) *3);

	//���_�o�b�t�@�[�r���[���쐬����
	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = sizeof(XMFLOAT4) * 3;
	vertexBufferView.StrideInBytes = sizeof(XMFLOAT4);

	//���_���
	XMFLOAT4* vertexData = nullptr;
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	vertexData[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
	vertexData[1] = { 0.0f, 0.5f, 0.0f, 1.0f };
	vertexData[2] = { 0.5f, -0.5f, 0.0f, 1.0f };
}

void Sprite::CreateMaterial()
{
	materialResource = CreateBufferResource(dxCommon_->GetDevice(), sizeof(XMFLOAT4));

	XMFLOAT4* materialData = nullptr;
	materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));

	// �F
	*materialData = color_;
}

void Sprite::CreateWVP()
{
	wvpResource = CreateBufferResource(dxCommon_->GetDevice(), sizeof(XMMATRIX));
	XMMATRIX* wvpData = nullptr;
	//�������ނ��߂̃A�h���X���擾
	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvpData));
	//����͐Ԃ���������ł݂�
	*wvpData = XMMatrixIdentity();
}
