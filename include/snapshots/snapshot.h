#pragma once

#include <string>

#include "../common.h"


namespace Snapshots {

    class ISnapshot {
    public:
        const std::string &Name() const { return name; }
        Common::Date CreationDate() const { return creation_date; }

    protected:
        ISnapshot(std::string name_, Common::Date creation_date_)
                : name(std::move(name_)), creation_date(creation_date_) {}

        std::string name;
        Common::Date creation_date;
    };

}