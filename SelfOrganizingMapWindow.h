#ifndef SELFORGANIZINGMAPWINDOW_H
#define SELFORGANIZINGMAPWINDOW_H

#include <QMainWindow>

#include "ui_SelfOrganizingMapWindow.h"

#include "SelfOrganizingMap.h"

class SelfOrganizingMapWindow : public QMainWindow, public Ui::SelfOrganizingMapWindow
{
    Q_OBJECT

public:
    explicit SelfOrganizingMapWindow(QWidget* parent = nullptr);
    ~SelfOrganizingMapWindow();

    virtual void showEvent(QShowEvent* showEvent) override;

private slots:
    void loadAndTrainOnImage(const QImage& originalImage);
    void generateApproximateImage();
private:
    SelfOrganizingMap<3> _imageMap;
    QImage _originalImage;
    QImage _approximatedImage;
};

#endif // SELFORGANIZINGMAPWINDOW_H
