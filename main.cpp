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

