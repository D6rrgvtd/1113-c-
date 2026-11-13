#include "CBController.h"

#include <UniDx/D3DManager.h>
#include <UniDx/Input.h>



using namespace UniDx;

namespace
{
    // 定数バッファ（型定義自体はシェーダーに伝わらないことに注意）
    struct CBParam // register(b0)
    {
        Color baseColor;
        int alostColor;
        float padding[3];
    };
    constexpr int CBSlot = 0;

    Color colorTable[] =
    {
        Color(1, 0, 1.2),
        Color(1, 1, 0.2),
        Color(1, 5, 1),
        Color(0, 1, 1),
        Color(0.5, 0.2, 0.2),
        Color(2, 0.5, 0),
        Color(1, 1, 0.5),
        Color(2,2,2),
        Color(0,0,0),
        Color(0.3,0.5,0.6)
    };
    constexpr int tableSize = sizeof(colorTable) / sizeof(Color);
}


void CBController::Start()
{
    D3D11_BUFFER_DESC desc{};
    desc.ByteWidth = sizeof(CBParam);       // 構造体のサイズを指定
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.CPUAccessFlags = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;

    // 定数バッファを確保
    D3DManager::getInstance()->GetDevice()->CreateBuffer(&desc, nullptr, constantBuffer.GetAddressOf());
}


void CBController::Update()
{
    if(Input::GetKeyDown(Keyboard::Right))
    {
        colorIndex = (colorIndex + 1) % tableSize;
    }

    if (Input::GetKeyDown(Keyboard::Left))
    {
        colorIndex = (colorIndex - 1+tableSize) % tableSize;
    }
    if (Input::GetKeyDown(Keyboard::Space))
    {
        isInvert = !isInvert;
    }

    CBParam cb;

    // カラーテーブルから現在のインデクスの色を設定
    cb.baseColor = colorTable[colorIndex];
    cb.alostColor = isInvert ? 1 : 0;

    // 定数バッファを更新
    D3DManager::getInstance()->GetContext()->UpdateSubresource(constantBuffer.Get(), 0, nullptr, &cb, 0, 0);

    // シェーダーへ設定
    ID3D11Buffer* cbs[1] = { constantBuffer.Get() };
    D3DManager::getInstance()->GetContext()->VSSetConstantBuffers(CBSlot, 1, cbs);
    D3DManager::getInstance()->GetContext()->PSSetConstantBuffers(CBSlot, 1, cbs);

}