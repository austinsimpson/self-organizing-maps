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
