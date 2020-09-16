#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QMediaPlayer>
#include <QTime>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void timerEvent(QTimerEvent *e);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    int timerId; 

private slots:
    void on_actionOpen_triggered();
    void on_actionClose_triggered();
    void on_actionQuit_triggered();
    void on_actionAbout_triggered();
    void on_actionPlay_triggered();
    void on_actionStop_triggered();
    void on_horizontalSlider_sliderPressed();
    void on_horizontalSlider_sliderReleased();
};

#endif // MAINWINDOW_H
