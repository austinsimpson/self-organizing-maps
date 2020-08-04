#ifndef SELFORGANIZINGMAPCATEGORY_H
#define SELFORGANIZINGMAPCATEGORY_H

#include <QVector>

#include "VectorND.h"
#include "SelfOrganizingMapUnit.h"

template <int Dimension>
class SelfOrganizingMapCategory
{
public:
    SelfOrganizingMapCategory
    (
        const SelfOrganizingMapUnit<Dimension>& unit
    ):
        _unit{unit}
    {

    }

    const SelfOrganizingMapUnit<Dimension>& unit() const
    {
        return _unit;
    }

    QVector<VectorND<Dimension>>& items()
    {
        return _items;
    }

    const QVector<VectorND<Dimension>>& items() const
    {
        return _items;
    }

private:
    SelfOrganizingMapUnit<Dimension> _unit;
    QVector<VectorND<Dimension>> _items;
};

#endif // SELFORGANIZINGMAPCATEGORY_H
