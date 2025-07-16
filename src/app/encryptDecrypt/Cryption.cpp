#include "Cryption.hpp"
#include "../processes/Task.hpp"
#include "../fileHandling/ReadEnv.hpp"
#include <iostream>
#include <sstream>
#include <vector>

int executeCryption(const std::string &taskData)
{
    try
    {
        Task task = Task::fromString(taskData);
        ReadEnv env;
        std::string envKey = env.getenv();
        int key = std::stoi(envKey);

        if (key == 0)
        {
            std::cerr << "Warning: Using key 0 - encryption/decryption will have no effect" << std::endl;
        }

        std::vector<char> buffer;
        char ch;
        while (task.f_stream.get(ch))
        {
            buffer.push_back(ch);
        }

        task.f_stream.clear();
        task.f_stream.seekp(0, std::ios::beg);

        if (task.action == Action::ENCRYPT)
        {
            for (char &c : buffer)
            {
                c = (c + key) % 256;
            }
        }
        else
        {
            for (char &c : buffer)
            {
                c = (c - key + 256) % 256;
            }
        }

        task.f_stream.write(buffer.data(), buffer.size());
        task.f_stream.close();

        std::cout << "Successfully processed: " << task.filePath << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in executeCryption: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}