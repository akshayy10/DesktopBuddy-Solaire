#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPixmap>
#include <QDebug>
#include <QVector>
#include <QMouseEvent>



MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
    frames.append(QPixmap(":/images/frame0.png"));
    frames.append(QPixmap(":/images/frame1.png"));
    frames.append(QPixmap(":/images/frame2.png"));
    frames.append(QPixmap(":/images/frame3.png"));
    frames.append(QPixmap(":/images/frame4.png"));
    frames.append(QPixmap(":/images/frame5.png"));
    frames.append(QPixmap(":/images/frame6.png"));
    frames.append(QPixmap(":/images/frame7.png"));
    
    
 

    timer.start(500);
    
    connect(
        &timer,
        &QTimer::timeout,
        this,
        &MainWindow::idle_animations
    );

    connect(
        &subtitletimer,
        &QTimer::timeout,
        this,
        &MainWindow::updateSubs
    );
    connect(
        &player,
        &QMediaPlayer::playbackStateChanged,
        this,
        MainWindow::audioStatechange
    );
    
    subtitle = new QLabel(this);
    subtitle->hide();
    subtitle->setText("Hello ");
    subtitle->setGeometry(70,40,260,50);
    subtitle->setWordWrap(true);
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->raise();
    subtitle->setStyleSheet(
        "QLabel {"
        "background-color: rgba(0, 0, 0, 200);"
        "color: #E8E3D3;"
        "border: 1px solid #B8A46A;"
        "padding: 8px;"
        "}"
    );
    player.setAudioOutput(&audioOutput);
    audioOutput.setVolume(1.0);


}
void MainWindow::audioStatechange(QMediaPlayer::PlaybackState state){
    if(state == QMediaPlayer::StoppedState){
        subtitle->hide();
    }
}
void MainWindow::speak(const QString &text,const QUrl &audio){
    subtitletimer.start(200);
    subtitle->show();
    fullsubtitles = text;
    updateSubs();
    player.setSource(audio);
    player.play();
    
    }

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)
    {
        
        speak("Oh Hello, You dont look hollow",QUrl("qrc:/voicelines/v1.mp3"));


    }

    qDebug() << "7 - Function finished";
}
void MainWindow::idle_animations(){

    /*for(QPixmap image : frames){
        if(image.isNull()){
            qDebug() << "Image not loaded";
        }else{
            qDebug() << "Image loaded";
        }
    }*/ // to check frame loading

    if(frame >= frames.size()){
        frame=0;
    }
   
    ui->label->setPixmap(
        frames[frame].scaled(
            200,
            200,
            Qt::KeepAspectRatio,
            Qt::FastTransformation
        )
    );
    ui->label->adjustSize();
    adjustSize();
    frame++;
}
void MainWindow::updateSubs(){
    if(subtitlechar >= fullsubtitles.length()){
        subtitletimer.stop();
        return;
    }
    subtitlechar++;
    subtitle->setText(fullsubtitles.left(subtitlechar));
    
}

MainWindow::~MainWindow()
{
    delete ui;
}