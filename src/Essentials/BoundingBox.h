#pragma once
#include <Maths/vec.h>

template<typename T, int S>
struct tbbox
{
    tvec<T, S> pos, size;
    tbbox(tvec<T, S> pos, tvec<T, S> size)
    {
        this->pos = pos;
        this->size = size;
    }

    tvec<T, S> getPos()  { return pos; }
    tvec<T, S> getSize() { return size; }
};

typedef tbbox<float, 2> bbox2;
typedef tbbox<int,   2> bbox2i;
typedef tbbox<float, 3> bbox3;
typedef tbbox<int,   3> bbox3i;