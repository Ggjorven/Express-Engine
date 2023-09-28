#include "TriangleLayer.hpp"

class Sandbox : public Express::Application
{
public:
	Sandbox()
	{
		AddLayer(new TriangleLayer());
	}

	virtual ~Sandbox() {}

private:
};



//===================================================//
//-----------Creation of the application-------------//
//===================================================//
Express::Application* Express::CreateApplication() 
{
	return new Sandbox();
}

#include <Express/Core/EntryPoint.hpp>
//===================================================//