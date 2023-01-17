#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>

std::string operator+(std::string const &a, int b)
{
    std::ostringstream oss;
    oss << a << b;
    return oss.str();
}

std::string timeS(int t)
{
    // current date/time based on current system
    time_t now = time(0);

    std::string ret = "";

    tm *ltm = localtime(&now);

    ret = ret + (1 + ltm->tm_mon) + "/";
    ret = ret + (ltm->tm_mday + t) + "/";
    ret = ret + (1900 + ltm->tm_year);

    return ret;
}

void insertTasks(std::fstream &file, std::string date)
{
    std::string inputs = "0";
    std::cout << "For " + date + ": (if no tasks , enter -1)" << std::endl;
    file << "For " + date << std::endl;
    while (inputs != "-1")
    {
        std::cout << "\t +";
        std::getline(std::cin, inputs);
        if (inputs != "")
        {
            file << "\t +" + inputs << std::endl;
        }
    }
}

void viewTasks(std::fstream &file, std::string date)
{
    std::string output = "0";
    bool there = false, found = false;
    while (std::getline(file, output))
    {
        if (output == "For " + date || there)
        {
            there = true;
            found = true;
            std::cout << output << std::endl;
        }
        if (output == "\t +-1")
        {
            there = false;
        }
    }
    if (!found)
    {
        std::cout << "Day Doesnt exist in the database" << std::endl;
    }
}

int main(int argc, const char **argv)
{
    std::fstream file;
    std::string today = timeS(0);
    std::string tomorrow = timeS(1);
    std::string anydate;
    int need = 0;
    file.open("Tasks.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    if (!file)
    {
        std::cout << "File creation failed";
    }
    std::cout << "What do you want to do ?" << std::endl;
    std::cout << "\t/1  Insert tasks for tomorrow" << std::endl;
    std::cout << "\t/2  Insert tasks for today if u slept too late" << std::endl;
    std::cout << "\t/3  View tasks of today" << std::endl;
    std::cout << "\t/4  View tasks of a any day" << std::endl;
    std::cin >> need;
    switch (need)
    {
    case 1:
        insertTasks(file, tomorrow);
        break;
    case 2:
        insertTasks(file, today);
        break;
    case 3:
        viewTasks(file, today);
        break;
    case 4:
        std::cout << "Format: (mm/dd/yyyy)" << std::endl
                  << "\t";
        std::cin >> anydate;
        viewTasks(file, anydate);
        break;

    default:
        break;
    }

    return 0;
}