#pragma once

#include <memory>

#include "listener.h"
#include "../model/field.h"
#include "base_logger.h"

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