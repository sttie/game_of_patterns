#pragma once

#include <string>

#include "snapshot.h"
#include "../common.h"
#include "../logging/notifier.h"
#include "../lib/my_container.hpp"
#include "../model/cell.h"
#include "../game_objects/enemy.hpp"
#include "../lib/raii_file.hpp"
#include "../game_objects/behavior_types.hpp"


namespace Snapshots {

    class FieldSnapshot : public ISnapshot {
    public:
        FieldSnapshot(std::string name, Common::Date creation_date,
                      Lib::Container<Lib::Container<Model::Cell>> cells_,
                      Lib::Container<std::shared_ptr<GameObject::IEnemy>> enemies_,
                      int rows_, int columns_, int cell_size_, GameObject::Player player_);


        const Lib::Container<
                Lib::Container<Model::Cell>
                >& Cells() const;
        const Lib::Container<
                std::shared_ptr<GameObject::IEnemy>
                >& Enemies() const;

        int Rows() const;
        int Columns() const;
        int CellSize() const;

        const GameObject::Player& GetPlayer() const;

        void WriteSnapshot(Lib::OutRFile& out) const noexcept;

    private:
        Lib::Container<Lib::Container<Model::Cell>> cells{};
        Lib::Container<std::shared_ptr<GameObject::IEnemy>> enemies{};

        int rows;
        int columns;
        int cell_size;

        GameObject::Player player{};
    };

    inline FieldSnapshot CreateNewSnapshot(
            std::string name,
            Common::Date creation_date,
            Lib::InRFile& in) {
        int rows = Lib::Read<int>(in);
        if (rows <= 0 ) {
            throw Lib::SerializeReadError("field's rows amount cannot be negative or zero");
        }

        int columns = Lib::Read<int>(in);
        if (columns <= 0 ) {
            throw Lib::SerializeReadError("field's columns amount cannot be negative or zero");
        }

        int cell_size = Lib::Read<int>(in);
        if (cell_size <= 0 ) {
            throw Lib::SerializeReadError("field's cell size cannot be negative or zero");
        }

        GameObject::Player player;
        player.Read(in);

        auto cells = Lib::Read<Lib::Container<Lib::Container<Model::Cell>>>(in);

        int enemies_amount = Lib::Read<int>(in);
        if (enemies_amount < 0) {
            throw Lib::SerializeReadError("enemies amount cannot be negative");
        }

        Lib::Container<std::shared_ptr<GameObject::IEnemy>> enemies;
        for (int i = 0; i < enemies_amount; ++i) {
            enemies.PushBack(GameObject::ReadEnemy(in));
        }

        return FieldSnapshot(std::move(name), creation_date,
                             std::move(cells), std::move(enemies),
                             rows, columns, cell_size, std::move(player));
    }

}