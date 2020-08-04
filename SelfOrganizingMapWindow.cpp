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

#include "SelfOrganizingMapWindow.h"

#include "SOMCategoriesGraphLayer.h"

#include <QImage>
#include <QFileDialog>

SelfOrganizingMapWindow::SelfOrganizingMapWindow
(
    QWidget* parent
):
    QMainWindow(parent),
    Ui::SelfOrganizingMapWindow(),
    _imageMap(10)
{
    setupUi(this);

    connect(_actionOpen, &QAction::triggered, [this]() {
        const QString fileName = QFileDialog::getOpenFileName();
        if (QFile::exists(fileName))
        {
            _originalImage = QImage(fileName);
            _originalPictureLabel->setPixmap(QPixmap::fromImage(_originalImage));
            _trainButton->setEnabled(true);
        }
    });

    connect(_actionSave, &QAction::triggered, [this]() {
        const QString filePath = QFileDialog::getSaveFileName(this, "Save the reconstructed image.", QDir::homePath(), "*.png | *.jpg");
        _approximatedImage.save(filePath);
    });

    connect(_iterationsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), [this] (int value) {
        _imageMap.setNumberOfIterations(static_cast<size_t>(value));
    });

    connect(_gridLengthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), [this] (int value) {
        _imageMap.setGridLength(static_cast<size_t>(value));
    });

    connect(_trainButton, &QPushButton::clicked, [this] (){
        if (_originalImage.isNull() == false)
        {
            loadAndTrainOnImage(_originalImage);
            _graphWidget->reset();
            _graphWidget->addLayer(std::make_unique<SOMCategoriesGraphLayer>(_imageMap.categories()));

            generateApproximateImage();
            _approximatedImageLabel->setPixmap(QPixmap::fromImage(_approximatedImage));
        }
    });
}

SelfOrganizingMapWindow::~SelfOrganizingMapWindow()
{

}

void SelfOrganizingMapWindow::loadAndTrainOnImage
(
    const QImage& image
)
{
    QVector<VectorND<3>> trainingPoints;

    for (const auto y: range(0, image.height()))
    {
        for (const auto x: range(0, image.width()))
        {
            QRgb pixel = image.pixel(x, y);
            trainingPoints.push_back(VectorND<3>{ static_cast<qreal>(qRed(pixel)) / 255, static_cast<qreal>(qGreen(pixel)) / 255, static_cast<qreal>(qBlue(pixel)) / 255 });
        }
    }

    _imageMap.setTrainingPoints(trainingPoints);
    _imageMap.train();

}

void SelfOrganizingMapWindow::generateApproximateImage()
{
    const auto width = _originalImage.width();
    const auto height = _originalImage.height();
    const auto& trainingPoints = _imageMap.trainingPoints();

    _approximatedImage = QImage(width, height, QImage::Format::Format_RGB888);
    for (const int y : range(0, height))
    {
        for (const int x : range(0, width))
        {
            const auto& bmu = _imageMap.findBestMatchingUnit(trainingPoints[y * width + x]);
            const auto& unitValue = bmu.value();
            const int red = unitValue[0] > 1.0 ? 255 : static_cast<int>(unitValue[0] * 255);
            const int green  = unitValue[1] > 1.0 ? 255 : static_cast<int>(unitValue[1] * 255);
            const int blue = unitValue[2] > 1.0 ? 255 : static_cast<int>(unitValue[2] * 255);
            const auto color = qRgb(red, green, blue);
            _approximatedImage.setPixel(x, y, color);
        }
    }
}

void SelfOrganizingMapWindow::showEvent
(
    QShowEvent* showEvent
)
{
    Q_UNUSED (showEvent);
    _graphWidget->centerOnLogicalCoordinate(QPointF(0.0, 0.0));
}
