#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_SrtOpenButton_clicked();

    void on_WavOpenButton_clicked();

    void on_StartButton_clicked();

    void on_ClearButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
