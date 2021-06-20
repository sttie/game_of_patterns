#pragma once

#include <cstdint>
#include <tuple>
#include <optional>

#include "../game_objects/enemy.hpp"
#include "../lib/my_container.hpp"
#include "cell.h"
#include "../game_objects/player.h"
#include "../logging/notifier.h"
#include "../common.h"
#include "../snapshots/field_snapshot.h"


namespace Model {

    class Field {
    public:
        enum class Move {
            UP,
            RIGHT,
            DOWN,
            LEFT
        };

        static Field &GetField(int rows_,
                               int columns_,
                               int cell_size_);
        static Field &GetField();
        static void ClearField();

        Field(const Field &other_field);
        Field(Field &&other_field) noexcept;

        Field &operator=(const Field &other_field);
        Field &operator=(Field &&other_field) noexcept;

        Lib::Container<Cell> &operator[](int index);
        const Lib::Container<Cell> &operator[](int index) const;

        bool IsEnemy(int x, int y) const;
        bool IsEnter(int x, int y) const;
        bool IsExit(int x, int y) const;
        bool IsObstacle(int x, int y) const;
        bool IsLivesUp(int x, int y) const;
        bool IsScoresUp(int x, int y) const;
        bool IsPortal(int x, int y) const;
        bool IsEmpty(int x, int y) const;

        int Rows() const;
        int Columns() const;
        int CellSize() const;
        bool IsGameOver() const;

        int PlayerX() const;
        int PlayerY() const;
        int PlayerLives() const;
        int PlayerScores() const;
        void MovePlayer(Move direction);

        void AddListener(Logging::Notifier::ListenerPtr new_listener);

        Lib::Container<Cell> *begin();
        Lib::Container<Cell> *end();
        const Lib::Container<Cell> *begin() const;
        const Lib::Container<Cell> *end() const;

        template<typename Moving, typename Attacking>
        void AddEnemy(std::shared_ptr<
                GameObject::StandardEnemy<Moving, Attacking>
                > new_enemy) {
            Lib::Container<Common::Position> obstacles;
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    if (IsObstacle(j, i))
                        obstacles.PushBack({j, i});
                }
            }

            new_enemy->SetMovingBorders({rows, columns}, obstacles);
            enemies.PushBack(std::move(new_enemy));
        }
        void UpdateEnemies();

        const Snapshots::FieldSnapshot& SaveField(std::string name, Common::Date creation_date);
        void RestoreField(const Snapshots::FieldSnapshot& restore_snapshot) noexcept;

    private:
        Field() = default;
        Field(int rows_,
              int columns_,
              int cell_size_);

        void FillField();

        static std::shared_ptr<Field> field;

        Lib::Container<Lib::Container<Cell>> cells{};
        Lib::Container<std::shared_ptr<GameObject::IEnemy>> enemies{};

        int rows;
        int columns;
        int cell_size;

        GameObject::Player player{0, 9};

        Logging::Notifier notifier;

        std::optional<Snapshots::FieldSnapshot> field_snapshot;
    };

    // Inline для external linkage
    inline std::shared_ptr<Field> Field::field = nullptr;

}