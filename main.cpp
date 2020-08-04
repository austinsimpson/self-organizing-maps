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

#include <QApplication>

#include <iostream>
#include <QDebug>
#include <QPixmap>

#include "SelfOrganizingMapWindow.h"

#include "SelfOrganizingMap.h"

#include <QFile>
#include <QTextStream>
#include <QPainter>

#include <QDateTime>


constexpr int gridLength = 10;

QVector<VectorND<12>> loadWineDataset()
{
    auto min = VectorND<12>(std::numeric_limits<qreal>::max());
    auto max = VectorND<12>(std::numeric_limits<qreal>::min());

    QVector<VectorND<12>> result;

    QFile wineFile(":/data/winequality-red.csv");
    if (wineFile.open(QIODevice::ReadOnly))
    {
        QTextStream textStream(&wineFile);
        textStream.readLine();
        while (textStream.atEnd() == false)
        {
            auto lineSplit = textStream.readLine().split(',');
            VectorND<12> toAdd;
            for (const auto i : range(0, 12))
            {
                toAdd[i] = lineSplit[i].toDouble();
                if (toAdd[i] < min[i])
                    min[i] = toAdd[i];
                if (toAdd[i] > max[i])
                    max[i] = toAdd[i];
            }
            result.push_back(toAdd);
        }
    }

    const auto range = max - min;
    for (auto& vector : result)
    {
        vector -= min;
        vector.pointwiseDivide(range);
    }

    return result;
}

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    SelfOrganizingMapWindow window;
    window.show();


    return app.exec();
}

