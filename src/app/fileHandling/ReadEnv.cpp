// ReadEnv.cpp
#include "ReadEnv.hpp"
#include "IO.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

std::string ReadEnv::getenv()
{
    std::string env_path = ".env";
    IO io(env_path);
    std::fstream f_stream = io.getFileStream();

    if (!f_stream.is_open())
    {
        std::cerr << "Warning: Unable to open .env file, using default key 0" << std::endl;
        return "0";
    }

    std::stringstream buffer;
    buffer << f_stream.rdbuf();
    std::string content = buffer.str();
    size_t end = content.find_last_not_of(" \t\n\r");
    if (end != std::string::npos)
    {
        content = content.substr(0, end + 1);
    }

    return content;
}