#include <iostream>
#include <fstream>
#include <string>

class LogCommand 
{
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};


class ConsoleLogCommand : public LogCommand
{
public:
    void print(const std::string& message)
    {
        std::cout << message << std::endl;
    }
};

class FileLogCommand : public LogCommand
{
private:
    std::string FilePath;

public:
    FileLogCommand(const std::string& path) : FilePath(path){}

    void print(const std::string& message) override
    {
        std::ofstream outFile(FilePath, std::ios::app);
        if (outFile.is_open())
        {
            outFile << message << std::endl;

            outFile.close();
        }

        else
        {
            std::cerr << "Ошибка открытия файла!!!" << FilePath << std::endl;
        }
    }
};

static const void print(LogCommand& command, const std::string& message)
{
    command.print(message);
}


int main()
{
    ConsoleLogCommand consoleLogger;
    FileLogCommand fileLogger("Log.txt");

    print(consoleLogger, "сообщение в консоли.");
    print(fileLogger, "сообщение в файла.");

    return 0;
}