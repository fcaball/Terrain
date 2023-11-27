#ifndef CARTE_H
#define CARTE_H

#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QRadioButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QImage>
#include <iostream>
#include <QFileDialog>
#include <QCheckBox>
#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <basics.h>
#include <window.h>
class Window;

class Cartes : public QWidget
{
    Q_OBJECT
public:
    explicit Cartes(QWidget *parent = nullptr);
    QSize taille_image;
    QLabel *gradient;
    QLabel *texture;
    QLabel *cretes;
    QLabel *rivieres;
    QVector<char> hauteurs;
    QVector<char> biomes;
    Window *w;

signals:



public slots:
    void initMap();
    void initMapBiome();
};

#endif // CARTE_H