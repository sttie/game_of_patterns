#pragma once

#include "command.h"
#include "../model/field.h"

namespace Commands {

    class MoveCommand : public FieldCommand {
    public:
        explicit MoveCommand(Model::Field &field_ref_)
                : FieldCommand(field_ref_) {}
    };

    class MoveUp : public MoveCommand {
    public:
        explicit MoveUp(Model::Field &field_ref_)
                : MoveCommand(field_ref_) {}

        void Execute() const override {
            field_ref.MovePlayer(Model::Field::Move::UP);
        }
    };

    class MoveRight : public MoveCommand {
    public:
        explicit MoveRight(Model::Field &field_ref_)
                : MoveCommand(field_ref_) {}

        void Execute() const override {
            field_ref.MovePlayer(Model::Field::Move::RIGHT);
        }
    };

    class MoveDown : public MoveCommand {
    public:
        explicit MoveDown(Model::Field &field_ref_)
                : MoveCommand(field_ref_) {}

        void Execute() const override {
            field_ref.MovePlayer(Model::Field::Move::DOWN);
        }
    };

    class MoveLeft : public MoveCommand {
    public:
        explicit MoveLeft(Model::Field &field_ref_)
                : MoveCommand(field_ref_) {}

        void Execute() const override {
            field_ref.MovePlayer(Model::Field::Move::LEFT);
        }
    };

}