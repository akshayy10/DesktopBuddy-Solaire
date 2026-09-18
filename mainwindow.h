#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QDialog>
#include <QTimer>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void idle_animations();
    void audioStatechange(QMediaPlayer::PlaybackState state);
    void speak(const QString &text,const QUrl &audio);
    void updateSubs();

private:
    Ui::Dialog *ui;
    QLabel *subtitle;
    QTimer timer;
    int frame = 0;
    QMediaPlayer player;
    QAudioOutput audioOutput;
    bool clicked;

    int subtitlechar = 0;
    QTimer subtitletimer;
    QString fullsubtitles;
    
    QVector<QPixmap> frames;
};

#endif