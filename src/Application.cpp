#include "Application.h"
#include <GLFW/glfw3.h>
#include <ratio>

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

    if (!Load())
    {
        return;
    }

    while (!glfwWindowShouldClose(m_window))
    {
        Update();
        Render();
    }
}

void Application::Cleanup()
{
    glfwDestroyWindow(m_window);
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
        Cleanup();
        return false;
    }

    // Center the window
    const int32_t windowLeft = videoMode->width / 2 - m_width / 2;
    const int32_t windowTop = videoMode->height / 2 - m_height / 2;
    glfwSetWindowPos(m_window, windowLeft, windowTop);

    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, HandleResize);

    m_currentTime = std::chrono::high_resolution_clock::now();
    return true;
}

void Application::OnResize(const int32_t width, const int32_t height)
{
    m_width = width;
    m_height = height;
}

void Application::HandleResize(GLFWwindow* window, const int32_t width, const int32_t height)
{
    Application* application = static_cast<Application*>(glfwGetWindowUserPointer(window));
    application->OnResize(width, height);
}

GLFWwindow* Application::GetWindow() const
{
    return m_window;
}

int32_t Application::GetWindowWidth() const
{
    return m_width;
}

int32_t Application::GetWindowHeight() const
{
    return m_height;
}

void Application::Update()
{
    auto oldTime = m_currentTime;
    m_currentTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> timeSpan = (m_currentTime - oldTime);
    m_deltaTIme = static_cast<float> (timeSpan.count() / 1000.0);
    glfwPollEvents();
}
