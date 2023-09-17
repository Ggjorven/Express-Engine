#include <Express/Express.hpp>

class Sandbox : public Express::Application
{
public:
	Sandbox()
	{

	}

	virtual ~Sandbox()
	{

	}
};

Express::Application* Express::CreateApplication()
{
	return new Sandbox();
}