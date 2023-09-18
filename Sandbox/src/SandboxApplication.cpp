#include "SandboxApplication.hpp"


//===================================================
//Creation the application
Express::Application* Express::CreateApplication() 
{
	return new Sandbox();
}
//===================================================