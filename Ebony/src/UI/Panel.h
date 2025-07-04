#pragma once
namespace Ebony {

/// Abstract base for any UI “panel” (window)
class UIPanel {
public:
    virtual ~UIPanel() = default;
    virtual void Render() = 0;
};

} // namespace Ebony
