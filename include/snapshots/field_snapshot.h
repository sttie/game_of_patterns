#pragma once

#include <string>
#include <vector>

#include <snapshots/snapshot.h>
#include <common.h>
#include <logging/notifier.h>
#include <model/cell.h>
#include <game_objects/npc.h>
#include <lib/raii_file.hpp>


namespace Snapshots {

    class FieldSnapshot : public ISnapshot {
    public:
        FieldSnapshot(std::string name, Common::Date creation_date,
                      std::vector<std::vector<Model::Cell>> cells,
                      std::vector<std::shared_ptr<GameObject::NPC>> npcs,
                      int rows, int columns, int cell_size, GameObject::Player player);


        const std::vector<
                std::vector<Model::Cell>
                >& Cells() const;
        const std::vector<
                std::shared_ptr<GameObject::NPC>
                >& NPCs() const;

        int Rows() const;
        int Columns() const;
        int CellSize() const;

        const GameObject::Player& GetPlayer() const;

        void WriteSnapshot(Lib::OutRFile& out) const noexcept;

    private:
        std::vector<std::vector<Model::Cell>> cells{};
        std::vector<std::shared_ptr<GameObject::NPC>> npcs{};

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

        auto cells = Lib::Read<std::vector<std::vector<Model::Cell>>>(in);

        int npcs_amount = Lib::Read<int>(in);
        if (npcs_amount < 0) {
            throw Lib::SerializeReadError("enemies amount cannot be negative");
        }

        std::vector<std::shared_ptr<GameObject::NPC>> npcs;
        for (int i = 0; i < npcs_amount; ++i) {
            throw std::logic_error("Not implemented");
            // npcs.PushBack(GameObject::ReadEnemy(in));
        }

        return FieldSnapshot(std::move(name), creation_date,
                             std::move(cells), std::move(npcs),
                             rows, columns, cell_size, std::move(player));
    }

}