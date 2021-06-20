#pragma once

#include "../lib/unit_testing.hpp"
#include "../model/field.h"
#include "../snapshots/field_snapshot.h"


inline void TestSnapshot() {
    using namespace Model;

    // Write
    auto field_model = Field::GetField(10, 10, 80);
    auto snapshot = field_model.SaveField("test_save1", {});

    const auto& cells = snapshot.Cells();
    const auto& enemies = snapshot.Enemies();
    auto rows = snapshot.Rows();
    auto columns = snapshot.Columns();
    auto cell_size = snapshot.CellSize();
    const auto& player = snapshot.GetPlayer();

    {
        Lib::OutRFile outfile1("test_save1");
        snapshot.WriteSnapshot(outfile1);
    }

    // Read
    Lib::InRFile infile1("test_save1");
    auto file_snapshot = Snapshots::CreateNewSnapshot("test_save1", {}, infile1);

    const auto& file_cells = file_snapshot.Cells();
    const auto& file_enemies = file_snapshot.Enemies();
    auto file_rows = file_snapshot.Rows();
    auto file_columns = file_snapshot.Columns();
    auto file_cell_size = file_snapshot.CellSize();
    const auto& file_player = file_snapshot.GetPlayer();

    ASSERT_EQUAL(cells.size(), file_cells.size());
    ASSERT_EQUAL(enemies.size(), file_enemies.size());
    ASSERT_EQUAL(rows, file_rows);
    ASSERT_EQUAL(columns, file_columns);
    ASSERT_EQUAL(cell_size, file_cell_size);
    ASSERT_EQUAL(player, file_player);

    for (int i = 0; i < cells.size(); ++i) {
        for (int j = 0; j < cells[i].size(); ++j)
            ASSERT_EQUAL(cells[i][j], file_cells[i][j]);
    }
    for (int i = 0; i < enemies.size(); ++i) {
        ASSERT_EQUAL(enemies[i], file_enemies[i]);
    }

    Field::ClearField();
}