#include "SOMCategoriesGraphLayer.h"

SOMCategoriesGraphLayer::SOMCategoriesGraphLayer
(
    const QVector<SelfOrganizingMapCategory<3>>& categories
):
    GraphLayer(),
    _categories(categories)
{
    for (const auto& category : _categories)
    {
        const auto& position = category.unit().position();
        const auto left = position[0];
        const auto bottom = position[1];

        const auto& categoryValue = category.unit().value();
        const auto red = categoryValue[0] > 1.0 ? 255 : static_cast<int>(categoryValue[0] * 255);
        const auto green = categoryValue[1] > 1.0 ? 255 : static_cast<int>(categoryValue[1] * 255);
        const auto blue = categoryValue[2] > 1.0 ? 255 : static_cast<int>(categoryValue[2] * 255);

        const QColor color(red, green, blue);

        _tiles.push_back(CategoryTile(QString::number(category.items().count()), QRectF(left, bottom, 1.0, 1.0), color));
    }
}

void SOMCategoriesGraphLayer::draw
(
    QPainter& painter,
    const QRectF& logicalBounds,
    const QTransform& viewportTransform
)   const
{
    painter.setPen(Qt::black);
    for (const auto& tile : _tiles)
    {
        const bool containedOnX = (tile.geometry().left() < logicalBounds.right() || tile.geometry().right() > logicalBounds.left());
        const bool containedOnY = (tile.geometry().bottom() > logicalBounds.top() || tile.geometry().top() < logicalBounds.bottom());
        if (containedOnX && containedOnY)
        {
            const auto drawingRect = viewportTransform.mapRect(tile.geometry());
            painter.fillRect(drawingRect, tile.color());
            painter.drawText(drawingRect, Qt::AlignCenter, tile.memberCountString());
        }
    }
}
