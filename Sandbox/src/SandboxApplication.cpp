#include "SandboxApplication.hpp"

#include "SandboxLayer.hpp"

Sandbox::Sandbox()
{
	AddLayer(new SandboxLayer());
}

Sandbox::~Sandbox()
{
}





//===================================================//
//-----------Creation of the application-------------//
//===================================================//
Express::Application* Express::CreateApplication() 
{
	return new Sandbox();
}

#include <Express/Core/EntryPoint.hpp>
//===================================================//