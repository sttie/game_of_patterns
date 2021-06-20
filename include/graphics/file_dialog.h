#pragma once

#include <string>
#include <QFileDialog>


class FileDialog {
public:
    static std::string OpenFile() {
        auto filename = QFileDialog::getOpenFileName();
        return filename.toStdString();
    }

    static std::string CreateFile() {
        auto filename = QFileDialog::getSaveFileName();
        return filename.toStdString();
    }
};