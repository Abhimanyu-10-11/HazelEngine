#pragma once

#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::CreateApplication();

int main(int argc,char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("warn");
	int a = 4;
	HZ_INFO("variabel {0}", a);
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}
#endif // HZ_PLATFORM_WINDOWS


