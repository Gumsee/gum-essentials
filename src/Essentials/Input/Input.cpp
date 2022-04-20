#pragma once

#include "Input.h"

namespace Gum {
namespace Input
{
    void init(Gum::Window* context)
    {
        Mouse = new InputMouseClass(context);
        Keyboard = new InputKeyboardClass();
        Controls = new InputControlsClass();
    }
}}