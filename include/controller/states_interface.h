#pragma once

#include <model/field.h>


namespace States {

    class ControllerState {
    public:
        explicit ControllerState(Model::Field& field_model_)
            : field_model(field_model_) {}


        virtual bool RunState() = 0;

    protected:
        Model::Field& field_model;
    };

}