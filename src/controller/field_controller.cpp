#include <controller/field_controller.h>

using namespace Controller;

FieldController::FieldController(
        std::shared_ptr<States::ControllerState> initial_state)
    : current_state(move(initial_state))
{
    if (current_state == nullptr)
        throw std::logic_error("state pointer cannot be null");
}


bool FieldController::Run() {
    return current_state->RunState();
}

void FieldController::SetState(
        std::shared_ptr<States::ControllerState> new_state) {
    if (new_state == nullptr)
        throw std::logic_error("state pointer cannot be null");

    current_state = move(new_state);
}