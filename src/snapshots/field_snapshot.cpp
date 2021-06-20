#include "../../include/snapshots/field_snapshot.h"

using namespace Snapshots;


FieldSnapshot::FieldSnapshot(
        std::string name, Common::Date creation_date,
        Lib::Container<Lib::Container<Model::Cell>> cells_,
        Lib::Container<std::shared_ptr<GameObject::IEnemy>> enemies_,
        int rows_, int columns_, int cell_size_, GameObject::Player player_)
    : ISnapshot(std::move(name), creation_date)
    , cells(std::move(cells_)), enemies(std::move(enemies_))
    , rows(rows_), columns(columns_), cell_size(cell_size_)
    , player(std::move(player_)) {}


const Lib::Container<
        Lib::Container<Model::Cell>
>& FieldSnapshot::Cells() const { return cells; }

const Lib::Container<
        std::shared_ptr<GameObject::IEnemy>
>& FieldSnapshot::Enemies() const { return enemies; }

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

    Lib::Write(out, static_cast<int>(enemies.size()));
    for (const auto& enemy : enemies)
        Lib::Write(out, enemy);
}