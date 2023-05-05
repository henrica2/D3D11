#pragma once

#include "Application.h"

class MyApplication final : public Application
{
public:
    MyApplication(const std::string& title);

protected:
    bool Load() override;
    void Render() override;
    void Update() override;
};

