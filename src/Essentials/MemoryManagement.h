#pragma once

namespace Gum
{

    /**
     * A safer alternative to delete
     */
    template<typename T>
    void _delete(T*& ptr)
    {
        if(ptr != nullptr)
            delete ptr;
        ptr = nullptr;
    }
};