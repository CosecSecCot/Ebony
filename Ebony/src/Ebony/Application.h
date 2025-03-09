#pragma once

#include <cstdint>

namespace Ebony {

class Application {
public:
    Application() = default;
    ~Application() = default;

    void Run() const;

private:
    uint32_t imageWidth = 256;
    uint32_t imageHeight = 256;
};

} // namespace Ebony
