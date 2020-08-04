#ifndef VECTORUTILITIES_H
#define VECTORUTILITIES_H

#include <QVector>

#include "VectorND.h"

class VectorUtilities
{
public:
    VectorUtilities() = delete;

    template <int N>
    static void Normalize(QVector<VectorND<N>>& vector);
};

#endif // VECTORUTILITIES_H
