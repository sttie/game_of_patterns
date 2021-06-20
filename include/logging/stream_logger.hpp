#pragma once

#include <fstream>

#include "base_logger.h"


namespace Logging {

    class StreamLogger : public Logger {
    public:
        explicit StreamLogger(std::ostream &out_stream_)
                : out_stream(out_stream_) {}

        void Log(const std::string &out) override {
            out_stream << out;
        }


    private:
        std::ostream &out_stream;
    };

}