#include "slpch.h"

#include <sstream>
#include <fstream>
#include <string>

#include "FileReader.h"

namespace Solar
{
    std::string FileReader::ReadFile(const std::string& filePath)
    {
        std::ifstream stream(filePath);
        std::stringstream ss;

        std::string line;
        while (getline(stream, line))
        {
            ss << line;
        }

        return ss.str();
    }
}
