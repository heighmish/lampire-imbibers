#pragma once

namespace lampire {
struct Input {
    bool moveLeft;
    bool moveRight;
    bool moveUp;
    bool moveDown;
    bool isMouseDown;
};

Input checkInputs();
}  // namespace lampire
