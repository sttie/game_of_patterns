#include <model/field.h>

#include <stdexcept>
#include <algorithm>

using namespace std;
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

    cells.resize(rows);
    for (std::vector<Cell>& cells_row : cells) {
        cells_row.resize(columns);
    }

    // Устанавливаем фиксированные "особые" точки
    // TODO: реализовать процедурную генерацию карты
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
    cells[0][0].SetType(CellType::SCORES_UP);

    cells[4][5].SetStrategy(std::make_shared<ScoresUp>());
    cells[4][5].SetType(CellType::SCORES_UP);

    cells[5][5].SetStrategy(std::make_shared<ScoresUp>());
    cells[5][5].SetType(CellType::SCORES_UP);

    cells[8][1].SetStrategy(std::make_shared<ScoresUp>());
    cells[8][1].SetType(CellType::SCORES_UP);


    cells[1][3].SetStrategy(std::make_shared<LivesUp>());
    cells[1][3].SetType(CellType::LIVES_UP);

    cells[9][6].SetStrategy(std::make_shared<LivesUp>());
    cells[9][6].SetType(CellType::LIVES_UP);

    cells[9][3].SetStrategy(std::make_shared<Teleport>(6, 1));
    cells[9][3].SetType(CellType::PORTAL);

    cells[6][8].SetStrategy(std::make_shared<Teleport>(0, 1));
    cells[6][8].SetType(CellType::PORTAL);
}

std::vector<Cell>& Field::operator[](int index) {
    return cells[index];
}

const std::vector<Cell>& Field::operator[](int index) const {
    return cells[index];
}


bool Field::IsNPC(int x, int y) const {
   return !none_of(npcs.begin(), npcs.end(), [x, y](const auto& npc_ptr){
       return npc_ptr->X() == x && npc_ptr->Y() == y;
   });
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

void Field::MovePlayer(const Move& direction) {
    int x = PlayerX(), y = PlayerY();

    if (direction == Move::UP && y > 0 && !IsObstacle(x, y-1))
        player.SetY(--y);
    else if (direction == Move::RIGHT && x < columns - 1 && !IsObstacle(x+1, y))
        player.SetX(++x);
    else if (direction == Move::DOWN && y < rows - 1 && !IsObstacle(x, y+1))
        player.SetY(++y);
    else if (direction == Move::LEFT && x > 0 && !IsObstacle(x-1, y))
        player.SetX(--x);

    cells[y][x].ApplyStrategy(player);

    // TODO: может перенести апдейт в контроллер? или дровер?
    // player.UpdateBuffs();

    notifier.Notify();
}

void Field::AddNPC(std::shared_ptr<GameObject::NPC> npc) {
    npcs.push_back(std::move(npc));
}

void Field::UpdateEnemies() {
    for (const auto& npc : npcs) {
        auto new_npc_position = npc->Move();
        while (new_npc_position.IsOutOfBounds(columns, rows) || IsObstacle(new_npc_position.x, new_npc_position.y))
            new_npc_position = npc->Move();
        npc->SetPosition(new_npc_position);
        
        if (npc->X() == player.X() && npc->Y() == player.Y()) {
            npc->InteractWithPlayer(player);
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


Field::Field(Field&& other_field) noexcept {
    rows = other_field.rows;
    columns = other_field.columns;
    cell_size = other_field.cell_size;
    cells = move(other_field.cells);
}


Field& Field::operator=(Field&& other_field) noexcept {
    rows = other_field.rows;
    columns = other_field.columns;
    cell_size = other_field.cell_size;
    cells = move(other_field.cells);

    return *this;
}


auto Field::begin() {
    return cells.begin();
}

auto Field::end() {
    return cells.end();
}

const auto Field::begin() const {
    return cells.begin();
}

const auto Field::end() const {
    return cells.end();
}


const Snapshots::FieldSnapshot& Field::SaveField(
        std::string name, Common::Date creation_date
) {
    field_snapshot = Snapshots::FieldSnapshot(
            std::move(name), creation_date,
            cells, npcs, rows, columns,
            cell_size, player
    );
    return field_snapshot.value();
}

void Field::RestoreField(const Snapshots::FieldSnapshot& restore_snapshot) noexcept {
    cells = restore_snapshot.Cells();
    npcs = restore_snapshot.NPCs();

    rows = restore_snapshot.Rows();
    columns = restore_snapshot.Columns();
    cell_size = restore_snapshot.CellSize();

    player = restore_snapshot.GetPlayer();

    field_snapshot = restore_snapshot;
}