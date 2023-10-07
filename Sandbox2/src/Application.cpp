#include <Express/Express.hpp>
#include <Express/Core/EntryPoint.hpp>

#include "QuadLayer.hpp"
#include "CustomImGuiLayer.hpp"

class Sandbox : public Express::Application
{
public:
    Sandbox()
    {
        //AddLayer(new QuadLayer());
        AddLayer(new CustomImGuiLayer());
    }

    ~Sandbox()
    {
    }
};

Express::Application* Express::CreateApplication()
{
    return new Sandbox();
}
