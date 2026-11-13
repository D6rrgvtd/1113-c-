#pragma once

#include <UniDx.h>
#include <UniDx/Rigidbody.h>


class CBController : public UniDx::Behaviour
{
public:
    virtual void Start() override;
    virtual void Update() override;
    // CBController.h の private などのメンバ変数部分
    bool isInvert = false;

private:
    UniDx::ComPtr<ID3D11Buffer> constantBuffer;    // シェーダー定数バッファ
    int colorIndex = 0;
};


