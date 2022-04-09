#include <spdlog/sinks/stdout_color_sinks.h>

#include "Log.h"

namespace Solar
{
     std::shared_ptr <spdlog::logger> Log::s_CoreLogger;
     std::shared_ptr <spdlog::logger> Log::s_ClientLogger;

    void Log::Init()
    {
        //TODO: get pattern from a file?? in order to remove recompilation
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger = spdlog::stdout_color_mt("SOLAR");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);
    }
}