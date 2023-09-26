#include <Express/Express.hpp>
#include <Express/Core/EntryPoint.hpp>

#include "QuadLayer.hpp"

class Sandbox : public Express::Application
{
public:
    Sandbox()
    {
        AddLayer(new QuadLayer());
    }

    ~Sandbox()
    {
    }
};

Express::Application* Express::CreateApplication()
{
    return new Sandbox();
}
