#pragma once

#include <memory>

#include <logging/listener.h>
#include <vector>


namespace Logging {

    class Notifier {
    public:
        using ListenerPtr = std::shared_ptr<Listener>;

        void Subscribe(ListenerPtr new_listener);

        void Notify();

    private:
        std::vector<ListenerPtr> listeners;
    };

}