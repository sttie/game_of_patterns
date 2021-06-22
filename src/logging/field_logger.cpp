#include <logging/field_logger.h>
#include <chrono>
#include <string>


Logging::FieldLogger::FieldLogger(
        const Model::Field& field_ref, std::unique_ptr<Logger> logger_)
        : field(field_ref)
        , logger(std::move(logger_))
{
}

void Logging::FieldLogger::Update() {
    auto current_time = std::chrono::system_clock::now();
    auto end_time = std::chrono::system_clock::to_time_t(current_time);
    logger->Log(std::string(std::ctime(&end_time)));

    logger->Log("Player's position: "
                + std::to_string(field.PlayerX())
                + "," + std::to_string(field.PlayerY())
                + "\n");
    logger->Log("Player's lives: " + std::to_string(field.PlayerLives()) + "\n");
    logger->Log("Player's scores: " + std::to_string(field.PlayerScores()) + "\n");
    logger->Log("Active cells:\n");
    for (int row = 0; row < field.Rows(); ++row) {
        for (int col = 0; col < field.Columns(); ++col) {
            if (field[row][col].WithStrategy()) {
                logger->Log(std::to_string(row) + ","
                            + std::to_string(col) + ": "
                            + field[row][col].StringType() + "\n");
            }
        }
    }

    logger->Log("\n");
}