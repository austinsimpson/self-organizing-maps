//Copyright(c) 2020 Austin Simpson
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#ifndef SELFORGANIZINGMAPUNIT_H
#define SELFORGANIZINGMAPUNIT_H

#include "VectorND.h"

constexpr auto kLearningRate = 0.01;

template <int Dimension>
class SelfOrganizingMapUnit
{
public:
    SelfOrganizingMapUnit(const VectorND<Dimension>& value, const VectorND<2>& position) : _value(value), _position(position)
    {

    }

    const VectorND<Dimension>& value() const
    {
        return _value;
    }

    VectorND<Dimension>& value()
    {
        return _value;
    }

    const VectorND<2>& position() const
    {
        return _position;
    }

private:
    VectorND<Dimension> _value;
    VectorND<2> _position;
};

#endif // SELFORGANIZINGMAPUNIT_H
