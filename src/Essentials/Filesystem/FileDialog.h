#pragma once
#include <functional>
#include <string>

namespace Gum {
namespace Filesystem {

    enum ACTION 
    {
        SAVE,
        OPEN
    };

    void selectFileDialog(std::string defaultpath, ACTION action, std::function<void(std::string)> callback);
    void selectMultipleFileDialog();
}};