#pragma once

#ifdef EX_PLATFORM_WINDOWS

extern Express::Application* Express::CreateApplication();

int main(int argc, char* argv[])
{
	Express::Application* app = Express::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif