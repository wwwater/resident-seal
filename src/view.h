#ifndef VIEW_H
#define VIEW_H

#include <QFrame>
#include <QGraphicsView>

QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QSlider)
QT_FORWARD_DECLARE_CLASS(QToolButton)

class View;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(View *v) : QGraphicsView(), view(v) { }

protected:
    void wheelEvent(QWheelEvent *);

private:
    View *view;
};

class View : public QFrame
{
    Q_OBJECT
public:
    View(const QString &name, QWidget *parent = 0);

    QGraphicsView *view() const;

public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);

private slots:
    void setupMatrix();

private:
    GraphicsView *graphicsView;
    QSlider *zoomSlider;

};

#endif

