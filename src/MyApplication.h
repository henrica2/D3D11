#pragma once

#include <d3d11.h> // D3D11 Core
#include <dxgi1_3.h> // DXGI Core
#include <wr1.h> // Microsoft COM resource management

#include "Application.h"

class MyApplication final : public Application
{
    template <typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
    MyApplication(const std::string& title);
    ~MyApplication() override;

protected:
    bool Load() override;
    void Render() override;
    void Update() override;
};

