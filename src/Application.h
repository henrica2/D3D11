#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <chrono>

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

    static void HandleResize(GLFWwindow*, int32_t width, int32_t height);
    virtual void OnResize(int32_t width, int32_t height);

    [[nodiscard]] GLFWwindow* GetWindow() const;
    [[nodiscard]] int32_t GetWindowWidth() const;
    [[nodiscard]] int32_t GetWindowHeight() const;

    int32_t m_width = 0;
    int32_t m_height = 0;
    float m_deltaTIme = 0.016f;

private:
    std::chrono::high_resolution_clock::time_point m_currentTime;
    GLFWwindow* m_window = nullptr;
    std::string_view m_title;
};

