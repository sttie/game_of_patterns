#pragma once

#include <memory>

#include <logging/listener.h>
#include <model/field.h>
#include <logging/base_logger.h>

namespace Logging {

    class FieldLogger : public Listener {
    public:
        FieldLogger(const Model::Field& field_ref, std::unique_ptr<Logger> logger_);

        void Update() override;

    private:
        std::unique_ptr<Logger> logger;
        const Model::Field& field;
    };

}