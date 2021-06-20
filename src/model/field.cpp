#include "../../include/model/field.h"

#include <stdexcept>
#include <algorithm>

using namespace std;
using namespace Lib;
using namespace Logging;
using namespace Model;


Field::Field(int rows_, int columns_, int cell_size_) {
    if (rows_ <= 0 || columns_ <= 0 || cell_size_ <= 0) {
        throw logic_error("Rows, columns or cell size cannot be negative");
    }

    rows = rows_;
    columns = columns_;
    cell_size = cell_size_;
    player = GameObject::Player();

    cells.Reserve(rows);
    for (Container<Cell>& cells_row : cells) {
        cells_row.Reserve(columns);
    }

    // Устанавливаем фиксированные "особые" точки
    FillField();
}

void Field::FillField() {
    using namespace Strategies;
    using CellType = Cell::CellType;

    cells[9][0] = Cell({0, 9}, CellType::ENTER);
    cells[0][9] = Cell({9, 0}, CellType::EXIT);

    for (int i = 1; i <= 2; i++) {
        cells[6][i] = Cell({i, 6}, CellType::OBSTACLE);
    }

    for (int i = 0; i < 3; i++) {
        cells[1+i][5+i] = Cell({5+i, 1+i}, CellType::OBSTACLE);
    }

    for (int i = 5; i <= 7; i++) {
        cells[7][i] = Cell({i, 7}, CellType::OBSTACLE);
    }

    for (int i = 1; i <= 4; i++) {
        cells[i][2] = Cell({2, i}, CellType::OBSTACLE);
    }

    cells[7][2] = Cell({2, 7}, CellType::OBSTACLE);
    cells[3][7] = Cell({7, 3}, CellType::OBSTACLE);

    cells[0][0].SetStrategy(std::make_shared<ScoresUp>());
    cells[4][5].SetStrategy(std::make_shared<ScoresUp>());
    cells[5][5].SetStrategy(std::make_shared<ScoresUp>());
    cells[8][1].SetStrategy(std::make_shared<ScoresUp>());

    cells[1][3].SetStrategy(std::make_shared<ScoresUp>());
    cells[9][6].SetStrategy(std::make_shared<ScoresUp>());

    cells[9][3].SetStrategy(std::make_shared<Teleport>(6, 1));
    cells[6][8].SetStrategy(std::make_shared<Teleport>(0, 1));
}

Container<Cell>& Field::operator[](int index) {
    return cells[index];
}

const Container<Cell>& Field::operator[](int index) const {
    return cells[index];
}


bool Field::IsEnemy(int x, int y) const {
    for (const auto& enemy_ptr : enemies) {
        if (x == enemy_ptr->X() && y == enemy_ptr->Y())
            return true;
    }
    return false;

//    return !any_of(enemies.begin(), enemies.end(), [x, y](const auto& enemy_ptr){
//        return enemy_ptr->X() != x && enemy_ptr->Y() != y;
//    });
}

bool Field::IsEnter(int x, int y) const {
    return cells[y][x].Type() == Cell::CellType::ENTER;
}

bool Field::IsExit(int x, int y) const {
    return cells[y][x].Type() == Cell::CellType::EXIT;
}

bool Field::IsObstacle(int x, int y) const {
    return cells[y][x].Type() == Cell::CellType::OBSTACLE;
}

bool Field::IsLivesUp(int x, int y) const {
    return cells[y][x].Type() == Cell::CellType::LIVES_UP;
}

bool Field::IsScoresUp(int x, int y) const {
    return cells[y][x].Type() == Cell::CellType::SCORES_UP;
}

bool Field::IsPortal(int x, int y) const {
    return cells[y][x].Type() == Cell::CellType::PORTAL;
}

bool Field::IsEmpty(int x, int y) const {
    return cells[y][x].Type() == Cell::CellType::EMPTY;
}



int Field::Rows() const {
    return rows;
}

int Field::Columns() const {
    return columns;
}

int Field::CellSize() const {
    return cell_size;
}

bool Field::IsGameOver() const {
    return (player.X() == 9 && player.Y() == 0
           && player.Scores() >= 200) || player.Lives() <= 0;
}


int Field::PlayerX() const {
    return player.X();
}

int Field::PlayerY() const {
    return player.Y();
}

int Field::PlayerLives() const {
    return player.Lives();
}

int Field::PlayerScores() const {
    return player.Scores();
}

void Field::MovePlayer(Move direction) {
    int x = PlayerX(),
        y = PlayerY();

    if (direction == Move::UP && y > 0 && !IsObstacle(x, y-1))
        player.SetY(--y);
    else if (direction == Move::RIGHT && x < columns - 1 && !IsObstacle(x+1, y))
        player.SetX(++x);
    else if (direction == Move::DOWN && y < rows - 1 && !IsObstacle(x, y+1))
        player.SetY(++y);
    else if (direction == Move::LEFT && x > 0 && !IsObstacle(x-1, y))
        player.SetX(--x);

    // Взаимодействие с новой клеткой
    player + cells[y][x];
    // TODO: может перенести апдейт в контроллер? или дровер?
    player.UpdateBuffs();

    notifier.Notify();
}

void Field::UpdateEnemies() {
    for (const auto& enemy_ptr : enemies) {
        enemy_ptr->Move();
        if (enemy_ptr->X() == player.X() && enemy_ptr->Y() == player.Y()) {
            (*enemy_ptr) + player;
        }
    }
}


void Field::AddListener(Notifier::ListenerPtr new_listener) {
    notifier.Subscribe(move(new_listener));
}


Field& Field::GetField(int rows_, int columns_, int cell_size_) {
    if (field != nullptr) {
        throw logic_error("Unable to redefine Field object");
    }

    field = std::make_shared<Field>(Field(rows_, columns_, cell_size_));
    return *field;
}

Field& Field::GetField() {
    if (field == nullptr) {
        throw logic_error("Field object has not been created yet");
    }

    return *field;
}

void Field::ClearField() {
    field.reset();
    field = nullptr;
}


Field::Field(const Field& other_field) {
    rows = other_field.rows;
    columns = other_field.columns;
    cell_size = other_field.cell_size;
    cells = other_field.cells;
}

Field::Field(Field&& other_field) noexcept {
    rows = other_field.rows;
    columns = other_field.columns;
    cell_size = other_field.cell_size;
    cells = move(other_field.cells);
}


Field& Field::operator=(const Field& other_field) {
    rows = other_field.rows;
    columns = other_field.columns;
    cell_size = other_field.cell_size;
    cells = other_field.cells;

    return *this;
}

Field& Field::operator=(Field&& other_field) noexcept {
    rows = other_field.rows;
    columns = other_field.columns;
    cell_size = other_field.cell_size;
    cells = move(other_field.cells);

    return *this;
}


Container<Cell>* Field::begin() {
    return cells.begin();
}

Container<Cell>* Field::end() {
    return cells.end();
}

const Container<Cell>* Field::begin() const {
    return cells.begin();
}

const Container<Cell>* Field::end() const {
    return cells.end();
}


const Snapshots::FieldSnapshot& Field::SaveField(
        std::string name, Common::Date creation_date
) {
    field_snapshot = Snapshots::FieldSnapshot(
            std::move(name), creation_date,
            cells, enemies, rows, columns,
            cell_size, player
    );
    return field_snapshot.value();
}

void Field::RestoreField(const Snapshots::FieldSnapshot& restore_snapshot) noexcept {
    cells = restore_snapshot.Cells();
    enemies = restore_snapshot.Enemies();

    rows = restore_snapshot.Rows();
    columns = restore_snapshot.Columns();
    cell_size = restore_snapshot.CellSize();

    player = restore_snapshot.GetPlayer();

    field_snapshot = restore_snapshot;
}