#pragma once

#include <string>


namespace Logging {

    class Logger {
    public:
        virtual void Log(const std::string &out) = 0;

        virtual ~Logger() = default;
    };

}