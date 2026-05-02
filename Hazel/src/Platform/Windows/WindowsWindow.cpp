#include "hzpch.h"
#include "WindowsWindow.h"
#include"Hazel/Events/KeyEvent.h"
#include"Hazel/Events/MouseEvent.h"
#include"Hazel/Events/ApplicationEvent.h"

#include"glad/glad.h"

namespace Hazel
{

    static bool s_GLFWInitialized = false;

    static void GLFWGetErrorCallback(int errorCode, const char* error)
    {
        HZ_CORE_ERROR("GLFW ERROR: ErrorCode: {0} Error: {1}", errorCode, error);
    }
    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }


    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        Init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        ShutDown();
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }


    void WindowsWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
        this->m_Data.VSync = enabled;
    }


    void WindowsWindow::Init(const WindowProps& prop)
    {
        m_Data.Title = prop.Title;
        m_Data.Width = prop.Width;
        m_Data.Height = prop.Height;

        HZ_CORE_INFO("Creating Widndow {0},({1},{2})", m_Data.Title, m_Data.Width, m_Data.Height);
        if (!s_GLFWInitialized)
        {
            int success = glfwInit();
            HZ_CORE_ASSERT(success, "Failed to Initialize glfw Widnow");
            glfwSetErrorCallback(GLFWGetErrorCallback);
            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);

        //Loading Glad
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        HZ_CORE_ASSERT(status, "Failed to inisitated glad Loader");
        
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) 
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                data.Width = width;
                data.Height = height;


                WindowResizeEvent event(width, height);
                data.EventCallback(event);

            });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                WindowCloseEvent event;
                data.EventCallback(event);

        });
        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scanmode, int action, int mods)
            {

                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                switch (action)
                {
					case GLFW_PRESS:
					{

						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{

						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{

						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
                }


		});

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) 
		{
		   WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
           switch (action)
           {
			   case GLFW_PRESS:
			   {
				   MouseButtonPressedEvent event(button);
				   data.EventCallback(event);
				   break;

			   }
			   case GLFW_RELEASE:
			   {
				   MouseButtonReleasedEvent event(button);
				   data.EventCallback(event);
				   break;

			   }
           }
              
            

		});

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double offsetX, double offsetY)
		{
		   WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		   MouseScrolledEvent event((float)offsetX, (float)offsetY);
		   data.EventCallback(event);
		});

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) 
        {
			   WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
               MouseMovedEvent event((float)xpos, (float)ypos);
               data.EventCallback(event);
        });





    }

    void WindowsWindow::ShutDown()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
}
