#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFiles();
    void play();
    void pause();
    void stop();
    void setVolume(int value);
    void updatePosition(qint64 position);
    void setPosition(int position);
    void playlistDoubleClicked(QListWidgetItem *item);
    void handleMediaFinished();
    void nextTrack();
    void prevTrack();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QStringList songs;
    int currentIndex = -1;
};

#endif // MAINWINDOW_H
