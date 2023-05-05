#pragma once

#include <iostream>
#include <string>
#include <string_view>

struct GLFWwindow;

class Application
{
public:
    Application(const std::string& title);
    virtual ~Application();
    // Entrypoint of the application
    void Run();

protected:
    virtual void Cleanup();
    virtual bool Initialize();
    virtual bool Load() = 0;
    virtual void Render() = 0;
    virtual void Update() = 0;

private:
    GLFWwindow* m_window = nullptr;
    int32_t m_width = 0;
    int32_t m_height = 0;
    std::string_view m_title;
};

