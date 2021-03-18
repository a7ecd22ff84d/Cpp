#ifndef MAZECONTROLS_H
#define MAZECONTROLS_H

#include <QWidget>

namespace Ui {
class MazeControls;
}

class MazeControls : public QWidget
{
    Q_OBJECT

public:
    explicit MazeControls(QWidget *parent = nullptr);
    ~MazeControls();

private:
    Ui::MazeControls *ui;
};

#endif // MAZECONTROLS_H
