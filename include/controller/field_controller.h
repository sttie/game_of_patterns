#pragma once

#include <memory>

#include "states_interface.h"


namespace Controller {

    class FieldController {
    public:
        explicit FieldController(std::shared_ptr<States::ControllerState> initial_state);

        FieldController(const FieldController &) = delete;

        FieldController(FieldController &&) = delete;

        FieldController &operator=(const FieldController &) = delete;

        FieldController &operator=(FieldController &&) = delete;

        bool Run();

        void SetState(std::shared_ptr<States::ControllerState> new_state);

    private:
        std::shared_ptr<States::ControllerState> current_state;
    };

}