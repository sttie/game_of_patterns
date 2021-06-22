#include <logging/notifier.h>


void Logging::Notifier::Subscribe(ListenerPtr new_listener) {
    listeners.push_back(std::move(new_listener));
}

void Logging::Notifier::Notify() {
    for (ListenerPtr& listener : listeners) {
        if (listener != nullptr)
            listener->Update();
    }
}