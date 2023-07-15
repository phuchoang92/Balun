#pragma once


#ifdef BL_PLATFORM_WINDOWS

extern Balun::Application* Balun::CreateApplication();

int main() {
	
	Balun::Log::Init();
	Balun::Log::GetCoreLogger()->warn("Initialized Log!");
	Balun::Log::GetClientLogger()->info("meomeo!");

	BL_PROFILE_BEGIN_SESSION("Startup", "BalunProfile-Startup.json");
	auto app = Balun::CreateApplication();
	BL_PROFILE_END_SESSION();

	BL_PROFILE_BEGIN_SESSION("Runtime", "HazelProfile-Runtime.json");
	app->Run();
	BL_PROFILE_END_SESSION();

	BL_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Shutdown.json");
	delete app;
	BL_PROFILE_END_SESSION();
}

#endif // BL_PLATFORM_WINDOWS
