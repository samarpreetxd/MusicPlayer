#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , player(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
{
    ui->setupUi(this);
    player->setAudioOutput(audioOutput);

    connect(ui->btnOpen, &QPushButton::clicked, this, &MainWindow::openFiles);
    connect(ui->btnPlay, &QPushButton::clicked, this, &MainWindow::play);
    connect(ui->btnPause, &QPushButton::clicked, this, &MainWindow::pause);
    connect(ui->btnStop, &QPushButton::clicked, this, &MainWindow::stop);
    connect(ui->btnNext, &QPushButton::clicked, this, &MainWindow::nextTrack);
    connect(ui->btnPrev, &QPushButton::clicked, this, &MainWindow::prevTrack);

    connect(ui->volumeSlider, &QSlider::valueChanged, this, &MainWindow::setVolume);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::updatePosition);
    connect(ui->progressSlider, &QSlider::sliderMoved, this, &MainWindow::setPosition);

    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::playlistDoubleClicked);

    connect(player, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status){
        if (status == QMediaPlayer::EndOfMedia) handleMediaFinished();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFiles()
{
    QStringList files = QFileDialog::getOpenFileNames(
        this, "Open Music Files", "", "Audio Files (*.mp3 *.wav *.ogg)");

    for (const QString &file : files) {
        songs.append(file);
        ui->listWidget->addItem(file.section("/", -1));
    }

    if (currentIndex == -1 && !songs.isEmpty()) {
        currentIndex = 0;
        play();
    }
}

void MainWindow::play()
{
    if (currentIndex >= 0 && currentIndex < songs.size()) {
        if (player->source().isEmpty() ||
            player->source() != QUrl::fromLocalFile(songs[currentIndex])) {
            player->setSource(QUrl::fromLocalFile(songs[currentIndex]));
        }
        player->play();
    }
}

void MainWindow::pause()
{
    player->pause();
}

void MainWindow::stop()
{
    player->stop();
}

void MainWindow::setVolume(int value)
{
    audioOutput->setVolume(value / 100.0);
}

void MainWindow::updatePosition(qint64 position)
{
    ui->progressSlider->setMaximum(player->duration());
    ui->progressSlider->setValue(position);
}

void MainWindow::setPosition(int position)
{
    player->setPosition(position);
}

void MainWindow::playlistDoubleClicked(QListWidgetItem *item)
{
    currentIndex = ui->listWidget->row(item);
    play();
}

void MainWindow::handleMediaFinished()
{
    if (songs.isEmpty()) return;
    currentIndex = (currentIndex + 1) % songs.size();
    player->setSource(QUrl::fromLocalFile(songs[currentIndex]));
    player->play();
}

void MainWindow::nextTrack()
{
    if (songs.isEmpty()) return;
    currentIndex = (currentIndex + 1) % songs.size();
    player->setSource(QUrl::fromLocalFile(songs[currentIndex]));
    player->play();
}

void MainWindow::prevTrack()
{
    if (songs.isEmpty()) return;
    currentIndex = (currentIndex - 1 + songs.size()) % songs.size();
    player->setSource(QUrl::fromLocalFile(songs[currentIndex]));
    player->play();
}
