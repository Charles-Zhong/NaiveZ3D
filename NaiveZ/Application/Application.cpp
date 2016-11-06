#include <iostream>

#include "Include/Application.h"
#include "../Core/GLRender/Include/GLViewPort.h"
//#include "../Core/GLRender/Include/GLRenderSystem.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

namespace NaiveZ3D
{
	Application::Application(const std::string& appName, GLsizei width, GLsizei height)
		:mAppName_(appName),
		mWidth_(width),
		mHeight_(height)
	{
		mGLRenderSystemPtr_ = GLRSPtr(new GLRenderSystem);
	}

	bool Application::Init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		mWindow_ = glfwCreateWindow(mWidth_, mHeight_, mAppName_.c_str(), nullptr, nullptr);
		if (mWindow_ == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(mWindow_);

		SetKeyCallback(KeyCallback);

		return mGLRenderSystemPtr_->Init(this);
	}

	void Application::Run()
	{
		while (!glfwWindowShouldClose(mWindow_))
		{
			// Check and call events
			glfwPollEvents();

			mGLRenderSystemPtr_->Run(0);

			glfwSwapBuffers(mWindow_);
		}
	}

	void Application::Terminate()
	{
		glfwTerminate();
	}

	void Application::SetKeyCallback(KeyCallbackDef cb)
	{
		glfwSetKeyCallback(mWindow_, cb);
	}
}