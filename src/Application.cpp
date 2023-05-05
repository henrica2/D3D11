#include "Application.h"
#include <GLFW/glfw3.h>

Application::Application(const std::string& title)
{
    m_title = title;
}

Application::~Application()
{
    Cleanup();
}

void Application::Run()
{
    if (!Initialize())
    {
        return;
    }

    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();
        Update();
        Render();
    }
}

void Application::Cleanup()
{
    if (m_window = nullptr)
    {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }

    glfwTerminate();
}

bool Application::Initialize()
{
    if (!glfwInit())
    {
        std::cout << "GLFW: Unable to initialize\n";
        return false;
    }

    // Get primary monitor and its current resolution (videoMode)
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
    // Set window vars to cover 90% of main monitor
    m_width = static_cast<int32_t>(videoMode->width * 0.5f);
    m_height = static_cast<int32_t>(videoMode->height * 0.5f);

    // Since we have defined our own scaling above, disable glfw scaling
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);
    // GLFW uses OpenGL by default, so disable it here (using DX11)
    // glfwWindowHint has many other options that are useful
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_window = glfwCreateWindow(m_width, m_height, m_title.data(), nullptr, nullptr);

    if (m_window == nullptr)
    {
        std::cout << "GLFW: Unable to create window\n";
    }

    // Center the window
    const int32_t windowLeft = videoMode->width / 2 - m_width / 2;
    const int32_t windowTop = videoMode->height / 2 - m_height / 2;
    glfwSetWindowPos(m_window, windowLeft, windowTop);

    return true;
}
