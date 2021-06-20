#pragma once

#include "../model/field.h"

namespace Commands {

    class FieldCommand {
    public:
        explicit FieldCommand(Model::Field &field_ref_)
                : field_ref(field_ref_) {}

        virtual void Execute() const = 0;

    protected:
        Model::Field &field_ref;
    };

}