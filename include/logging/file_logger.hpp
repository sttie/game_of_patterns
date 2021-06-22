#pragma once

#include <string>

#include <lib/raii_file.hpp>
#include <logging/base_logger.h>


namespace Logging {
    class FileLogger : public Logger {
    public:
        explicit FileLogger(const std::string &filename)
                : outfile(filename) {}

        void Log(const std::string &out) override {
            outfile << out;
        }

    private:
        Lib::OutRFile outfile;
    };

}