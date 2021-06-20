#include "../../include/model/field.h"
#include "../../include/graphics/draw.h"
#include "../../include/controller/states.h"
#include "../../include/controller/field_controller.h"
#include "../../include/graphics/file_dialog.h"

#include <iostream>

using namespace States;


PlayerTurn::PlayerTurn(
        Model::Field& field_model_,
        std::shared_ptr<Graphics::Drawer> field_view_)
    : ControllerState(field_model_)
    , field_view(std::move(field_view_))
    , up(field_model)
    , right(field_model)
    , down(field_model)
    , left(field_model) { }


bool PlayerTurn::RunState() {
    if (!field_view->IsOpen() || field_model.IsGameOver()) {
        return false;
    }

    sf::Event event;
    while (field_view->PollEvent(event) || event.type != sf::Event::KeyPressed) {
        if (event.type == sf::Event::Closed) {
            field_view->Close();
            return false;
        }

        field_view->Update();
    }


    if (event.key.code == sf::Keyboard::LShift) {
        SaveGame();
    }
    else if (event.key.code == sf::Keyboard::LControl) {
        LoadGame();
    }
    else if (event.key.code == sf::Keyboard::Up) {
        up.Execute();
    }
    else if (event.key.code == sf::Keyboard::Right) {
        right.Execute();
    }
    else if (event.key.code == sf::Keyboard::Down) {
        down.Execute();
    }
    else if (event.key.code == sf::Keyboard::Left) {
        left.Execute();
    }

    field_view->Update();

    return field_view->IsOpen() && !field_model.IsGameOver();
}


void PlayerTurn::LoadGame() {
    std::optional<Lib::InRFile> input;
    try {
        input = Lib::InRFile(FileDialog::OpenFile());
    }
    catch (const Lib::FileNotFoundError&) { return; }

    try {
        auto snapshot = Snapshots::CreateNewSnapshot(input->FileName(), Common::Date{}, *input);
        field_model.RestoreField(snapshot);
    } catch (const Lib::SerializeReadError& ex) {
        std::cout << "Some error occurred while game savefile reading: ";
        std::cout << ex.what() << std::endl;
    }
}

void PlayerTurn::SaveGame() {
    std::optional<Lib::OutRFile> outfile;
    try {
        outfile = Lib::OutRFile(FileDialog::CreateFile());
    }
    catch (const Lib::FileNotFoundError&) { return; }

    try {
        auto snapshot = field_model.SaveField(outfile->FileName(), Common::Date{});
        snapshot.WriteSnapshot(*outfile);
    } catch (const Lib::SerializeWriteError& ex) {
        std::cout << "Some error occurred while game saving: ";
        std::cout << ex.what() << std::endl;
    }
}


EnemyTurn::EnemyTurn(Model::Field& field_model)
    : ControllerState(field_model)
{
}

bool EnemyTurn::RunState() {
    field_model.UpdateEnemies();
    return true;
}