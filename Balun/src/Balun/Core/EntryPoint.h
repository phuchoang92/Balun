#pragma once


#ifdef BL_PLATFORM_WINDOWS

extern Balun::Application* Balun::CreateApplication();

int main() {
	
	Balun::Log::Init();
	Balun::Log::GetCoreLogger()->warn("Initialized Log!");
	Balun::Log::GetClientLogger()->info("meomeo!");

	auto app = Balun::CreateApplication();
	app->Run();
	delete app;
}

#endif // BL_PLATFORM_WINDOWS
