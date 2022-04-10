#include "slpch.h"

#include "Application.h"
#include "Solar/Events/ApplicationEvent.h"

namespace Solar
{
    Application::Application()
    {

    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        //TODO: for testings
        WindowResizeEvent testEvent(1980, 1080);
        if (testEvent.IsInCategory(EventCategoryApplication))
        {
            SL_TRACE(testEvent);
        }

        while (true)
        {

        }
    }
}