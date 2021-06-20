#pragma once

#include <memory>

#include "states_interface.h"
#include "../commands/moves.hpp"
#include "../model/field.h"
#include "../graphics/draw.h"


namespace States {

    class PlayerTurn : public ControllerState {
    public:
        PlayerTurn(Model::Field& field_model_,
                   std::shared_ptr<Graphics::Drawer> field_view_);

        bool RunState() override;

    private:
        void LoadGame();
        void SaveGame();

        std::shared_ptr<Graphics::Drawer> field_view;
        Commands::MoveUp up;
        Commands::MoveRight right;
        Commands::MoveDown down;
        Commands::MoveLeft left;
    };


    class EnemyTurn : public ControllerState {
    public:
        explicit EnemyTurn(Model::Field& field_model);

        bool RunState() override;
    };

}