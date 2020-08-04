#ifndef SOMCATEGORIESGRAPHLAYER_H
#define SOMCATEGORIESGRAPHLAYER_H

#include "GraphLayer.h"
#include "SelfOrganizingMapCategory.h"

struct CategoryTile
{
    CategoryTile(const QString& memberCountString, const QRectF& geometry, const QColor& color) : _memberCountString(memberCountString), _geometry(geometry), _color(color) {};
    CategoryTile(const CategoryTile& other) : _memberCountString(other._memberCountString), _geometry(other._geometry), _color(other._color) {};
    inline const QString& memberCountString() const { return _memberCountString; }
    inline const QRectF& geometry() const { return _geometry; }
    inline const QColor& color() const { return _color; }
private:
    QString _memberCountString;
    QRectF _geometry;
    QColor _color;
};

class SOMCategoriesGraphLayer: public GraphLayer
{
public:
    SOMCategoriesGraphLayer(const QVector<SelfOrganizingMapCategory<3>>& categories);

    virtual void draw(QPainter& painter, const QRectF& logicalBounds = QRectF(0, 0, 0, 0), const QTransform& viewportTransform = QTransform()) const override;


private:
    const QVector<SelfOrganizingMapCategory<3>>& _categories;
    QVector<CategoryTile> _tiles;

};

#endif // SOMCATEGORIESGRAPHLAYER_H
