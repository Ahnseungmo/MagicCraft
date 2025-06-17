#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
    vertexShader = Shader::AddVS(L"Tutorial.hlsl");
    pixelShader = Shader::AddPS(L"Tutorial.hlsl");    

    int n = 100;

    float stepAngle = PI * 2 / n;
    float radius = 100.0f;

    vertices.emplace_back(0, 0, 1, 0, 0);

    for (int i = 0; i < n; i++)
    {
        float x = cos(stepAngle * i) * radius;
        float y = sin(stepAngle * i) * radius;

        vertices.emplace_back(x, y);
    }

    for (int i = 0; i < n; i++)
    {
        indices.push_back(0);

        int index = i + 2;
        if (index > n)
            index -= n;

        indices.push_back(index);
        indices.push_back(i + 1);
    }


    //VertexBuffer
    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexColor), vertices.size());
    //IndexBuffer
    indexBuffer = new IndexBuffer(indices.data(), indices.size());

    worldBuffer = new MatrixBuffer();
    

    matWorld._11 = 1;
    matWorld._22 = 1;
    matWorld._33 = 1;
    matWorld._44 = 1;

    colorBuffer = new ColorBuffer();
    colorBuffer->Set(1, 0, 0);
}

TutorialScene::~TutorialScene()
{
    delete vertexBuffer;
    delete indexBuffer;

    delete colorBuffer;
}

void TutorialScene::Update()
{
    if (Input::Get()->IsKeyPress('D'))
    {
        //matWorld._41 += 100.0f * DELTA;
        pos.x += 100.0f * DELTA;
    }
    
    if (Input::Get()->IsKeyPress('W'))
    {
        //matWorld._42 += 100.0f * DELTA;
        pos.y += 100.0f * DELTA;
    }    

    if (Input::Get()->IsKeyDown('1'))
        colorBuffer->Set(1, 0, 0);

    if (Input::Get()->IsKeyDown('2'))
        colorBuffer->Set(0, 1, 0);

    if (Input::Get()->IsKeyDown('3'))
        colorBuffer->Set(0, 0, 1);

    //world = XMLoadFloat4x4(&matWorld);
    world = XMMatrixTranslation(pos.x, pos.y, 0.0f);
}

void TutorialScene::Render()
{   
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);    

    colorBuffer->SetPS(0);

    vertexBuffer->Set();
    indexBuffer->Set();

    vertexShader->Set();
    pixelShader->Set();

    //DC->Draw(vertices.size(), 0);
    DC->DrawIndexed(indices.size(), 0, 0);
}
