#pragma once


namespace Logging {

    class Listener {
    public:
        virtual void Update() = 0;
    };

}