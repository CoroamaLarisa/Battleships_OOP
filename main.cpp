#include "mainwindow.h"

#include <QApplication>
#include <QtMultimedia/QMediaPlaylist>
#include <QtMultimedia/QMediaPlayer>
#include "GUI.h"
using namespace std;

int main(int argc, char *argv[])
{
    QMediaPlaylist *playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl("C:/Users/Larisa/Downloads/doom.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();
    QApplication a(argc, argv);

    GUI gui;
    gui.show();
    return a.exec();
}
