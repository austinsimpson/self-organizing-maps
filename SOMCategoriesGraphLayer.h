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
