#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("Ready", 0);
    ui->actionPlay->setText("");
    ui->actionStop->setText("");

    player = nullptr;
    timerId = -1;
}

MainWindow::~MainWindow()
{
    if (player)
    {
        delete player;
        player = nullptr;
    }

    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    int position = player->position() / 1000;
    int duration = player->duration() / 1000;

    if (ui->horizontalSlider->maximum() == 0)
    {
        ui->horizontalSlider->setRange(0, duration);
    }
    ui->horizontalSlider->setValue(position);

    if (position >= duration)
    {
        killTimer(timerId);
        ui->horizontalSlider->setValue(0);
        ui->actionPlay->setIcon(QPixmap(":/icons/play.png"));
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("MP3 Files(*.mp3)"));

    if (timerId > 0)
    {
        killTimer(timerId);
        timerId = -1;
    }    

    if (player)
    {
        delete player;
        player = nullptr;
    }

    if (path.length() == 0)
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));

        ui->actionPlay->setIcon(QPixmap(":/icons/play.png"));
        ui->horizontalSlider->setRange(0, 0);
        ui->statusbar->showMessage(tr("Ready"), 0);
    }
    else
    {
        ui->statusbar->showMessage(path, 0);

        player = new QMediaPlayer;
        player->setMedia(QUrl::fromLocalFile(path));
        player->setVolume(100); // Default is 100
    }
}

void MainWindow::on_actionClose_triggered()
{
    if (player)
    {
        delete player;
        player = nullptr;
    }

    if (timerId > 0)
    {
        killTimer(timerId);
        timerId = -1;
    }

    ui->actionPlay->setIcon(QPixmap(":/icons/play.png"));
    ui->horizontalSlider->setRange(0, 0);
    ui->statusbar->showMessage(tr("Ready"), 0);
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About"), tr("It is written by Qt."));
}

void MainWindow::on_actionPlay_triggered()
{
    if (player)
    {
        QMediaPlayer::State state = player->state();
        if (state == QMediaPlayer::StoppedState)
        {
            player->play();
            ui->actionPlay->setIcon(QPixmap(":/icons/pause.png"));

            timerId = startTimer(1000);
            ui->horizontalSlider->setRange(0, 0);
        }
        else if (state == QMediaPlayer::PausedState)
        {
            player->play();
            ui->actionPlay->setIcon(QPixmap(":/icons/pause.png"));
        }
        else if (state == QMediaPlayer::PlayingState)
        {
            player->pause();
            ui->actionPlay->setIcon(QPixmap(":/icons/play.png"));
        }
    }
}

void MainWindow::on_actionStop_triggered()
{
    if (player)
    {
        if (timerId > 0)
            killTimer(timerId);
        timerId = -1;

        int state = player->mediaStatus();
        if (state != QMediaPlayer::StoppedState)
        {
            player->stop();
            ui->horizontalSlider->setValue(0);
            ui->actionPlay->setIcon(QPixmap(":/icons/play.png"));
        }
    }
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    killTimer(timerId);
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    int value = ui->horizontalSlider->value();
    player->setPosition(value * 1000);
    timerId = startTimer(1000);
}