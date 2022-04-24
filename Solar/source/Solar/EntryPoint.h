#pragma once

#include <iostream>

#ifdef SL_PLATFROM_WINDOWS

extern Solar::Application* Solar::CreateApplication();

int main(int argc, char** argv)
{
    Solar::Log::Init();
    SL_CORE_WARN("Initialized Log!");

    for (int i = 0; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
    }

    auto app = Solar::CreateApplication();
    app->Run();
    delete app;
}

#endif