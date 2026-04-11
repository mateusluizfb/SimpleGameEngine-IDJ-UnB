#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>

class Log
{
  public:
    static void info(const std::string &message) {
        std::cout << "\033[34mINFO\033[0m: " << message << std::endl; // blue
    }

    static void warning(const std::string &message) {
        std::cout << "\033[33mWARNING\033[0m: " << message << std::endl; // yellow
    }

    static void error(const std::string &message) {
        std::cerr << "\033[31mERROR\033[0m: " << message << std::endl; // red
    }

    static void debug(const std::string &message) {
        std::cout << "\033[32mDEBUG\033[0m: " << message << std::endl; // green
    }
};

#endif
