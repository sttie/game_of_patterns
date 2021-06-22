#include <snapshots/field_snapshot.h>

using namespace Snapshots;


FieldSnapshot::FieldSnapshot(
        std::string name, Common::Date creation_date,
        std::vector<std::vector<Model::Cell>> cells,
        std::vector<std::shared_ptr<GameObject::NPC>> npcs,
        int rows, int columns, int cell_size, GameObject::Player player)
    : ISnapshot(std::move(name), creation_date)
    , cells(std::move(cells)), npcs(std::move(npcs))
    , rows(rows), columns(columns), cell_size(cell_size)
    , player(std::move(player)) {}


const std::vector<
        std::vector<Model::Cell>
>& FieldSnapshot::Cells() const { return cells; }

const std::vector<
        std::shared_ptr<GameObject::NPC>
>& FieldSnapshot::NPCs() const { return npcs; }

int FieldSnapshot::Rows() const { return rows; }
int FieldSnapshot::Columns() const { return columns; }
int FieldSnapshot::CellSize() const { return cell_size; }

const GameObject::Player&
FieldSnapshot::GetPlayer() const { return player; }


void FieldSnapshot::WriteSnapshot(Lib::OutRFile& out) const noexcept {
    Lib::Write(out, rows);
    Lib::Write(out, columns);
    Lib::Write(out, cell_size);
    Lib::Write(out, player);

    Lib::Write(out, cells);

    Lib::Write(out, static_cast<int>(npcs.size()));
    for (const auto& npc : npcs)
        Lib::Write(out, npc);
}