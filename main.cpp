#include "Ebony.h"
#include <memory>

int main() {
    auto app = std::make_unique<Ebony::Application>();
    app->Run();
}
