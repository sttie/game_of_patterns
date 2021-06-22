#pragma once

#include <cstdint>
#include <tuple>
#include <optional>
#include <vector>

#include <game_objects/npc.h>
#include <model/cell.h>
#include <game_objects/player.h>
#include <logging/notifier.h>
#include <common.h>
#include <snapshots/field_snapshot.h>


namespace Model {

    class Field {
    public:
        enum class Move {
            UP,
            RIGHT,
            DOWN,
            LEFT
        };

        static Field& GetField(int rows_,
                               int columns_,
                               int cell_size_);
        static Field& GetField();
        static void ClearField();

        Field(const Field& other_field) = delete;
        Field& operator=(const Field& other_field) = delete;

        Field(Field&& other_field) noexcept;
        Field& operator=(Field&& other_field) noexcept;

        std::vector<Cell>& operator[](int index);
        const std::vector<Cell>& operator[](int index) const;

        bool IsNPC(int x, int y) const;
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
        void MovePlayer(const Move& direction);

        void AddListener(Logging::Notifier::ListenerPtr new_listener);

        auto begin();
        auto end();
        const auto begin() const;
        const auto end() const;

        void AddNPC(std::shared_ptr<GameObject::NPC> npc);

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

        std::vector<std::vector<Cell>> cells{};
        std::vector<std::shared_ptr<GameObject::NPC>> npcs{};

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