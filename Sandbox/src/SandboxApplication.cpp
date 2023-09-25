#include "SandboxLayer.hpp"

#include <Express/Express.hpp>

class Sandbox : public Express::Application
{
public:
	Sandbox();
	virtual ~Sandbox();

private:
};


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