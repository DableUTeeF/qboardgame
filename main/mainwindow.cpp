#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(int type, Dialog *base, QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow), m_iBoardSize(8) // TODO where is BoardSize actually used?
{
    ui->setupUi(this);
    base_diag = base;
    gametype = type;
    this->setFixedSize(this->geometry().width(),this->geometry().height());

    // Todo set fixed size of graphicsView and of MainWindow itself.
    // I don't know the size - look at ui option.
    //ui->graphicsViewBoard->setFixedSize(m_iWidgetSize - m_iWidgetBorder, m_iWidgetSize - m_iWidgetBorder);
    ui->graphicsViewBoard->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsViewBoard->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsViewBoard->setRenderHint(QPainter::Antialiasing,true);
    ui->graphicsViewBoard->setRenderHint(QPainter::SmoothPixmapTransform, true);

    // set multi row text edit
    ui->textEditEvents->setWordWrapMode(QTextOption::WordWrap);
    ui->textEditInfo->setWordWrapMode(QTextOption::WordWrap);

    // check if time input is double!!!!!
    ui->lineEditTimeLimit->setValidator(new QDoubleValidator(0, 100, 2, this));

    connect(ui->pushButtonNewGame, SIGNAL(released()), this, SLOT(startNewGame()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::closeEvent (QCloseEvent *event)
{
    delete ui;
    base_diag->show();
}
void MainWindow::startNewGame()
{
    qDebug() << "Starting New Game!";
    //qDebug() << m_iMapSize;
    m_uiGameScene = new UIGameScene(this, m_iBoardSize, m_iBoardSize, gametype);
    ui->graphicsViewBoard->setScene(m_uiGameScene);

    // create new GameLogic here to avoid swalloing KeyBoard Input
    m_gameEngine = new GameEngine(this, m_uiGameScene, ui->textEditEvents, ui->textEditInfo);
    m_chessEngine = new ChessEngine(this, m_uiGameScene, ui->textEditEvents, ui->textEditInfo);
    //ui->graphicsViewBoard->setScene(m_uiGameScene);

    // TODO let palyer choose color.

    // get selection from comboBox
    int numberOfHumanPlayers = ui->comboBoxNumberOfHumans->currentIndex() + 1;
    // get user input for time limit
    double timeLimit = ui->lineEditTimeLimit->text().toDouble();
    if(gametype==0)
    {
        connect(m_uiGameScene, SIGNAL(newMouseEvent(QPointF)), m_gameEngine, SLOT(mouseReleased(QPointF)));
        m_gameEngine->startGame(numberOfHumanPlayers, timeLimit);
    }
    else
    {
        connect(m_uiGameScene, SIGNAL(newMouseEvent(QPointF)), m_chessEngine, SLOT(mouseReleased(QPointF)));
        m_chessEngine->startGame(numberOfHumanPlayers, timeLimit);
    }

}
