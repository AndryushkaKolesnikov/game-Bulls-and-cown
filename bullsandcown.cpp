#include "bullsandcown.h"
#include "ui_bullsandcown.h"
//....................................................................
BullsAndCown::BullsAndCown(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BullsAndCown)
{
    currentButton = 0;
    ui->setupUi(this);
    QChar Buttom[3][3] = {{'1', '2', '3'},
                          {'4', '5', '6'},
                          {'7', '8', '9'}};

    QGridLayout* gridLayoutmain = new QGridLayout;
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j) {
            gridLayoutmain->addWidget(createButton(Buttom[i][j]),
                                  i, j);
        }
    }
    gridLayoutmain->addWidget(createButton("0"),3 ,0);
    QPushButton* PushButtonChech = new QPushButton(QObject::tr("Check"));
    PushButtonChech->setMaximumSize(100, 100);
    connect(PushButtonChech, SIGNAL(clicked(bool)),
            this, SLOT(slotCheck()));

    gridLayoutmain->addWidget(PushButtonChech, 3, 1, 1, 2);

    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(int)),
            this, SLOT(slotButtonClicked(int)));

    for(int i = 0; i < 4; i++) {
        massivPushButtons[i] = new QPushButton;
        massivPushButtons[i]->setMinimumSize(100, 100);
        connect(massivPushButtons[i], SIGNAL(clicked(bool)),
                signalMapper, SLOT(map()));
        signalMapper->setMapping(massivPushButtons[i], i);
        gridLayoutmain->addWidget(massivPushButtons[i], 0, 3+i);
    }
    LabelAnswer = new QLabel;
    LabelGameStatus = new QLabel(QObject::tr("Start a new game"));
    QPushButton* PushButtonNewGame = new QPushButton(QObject::tr("A new game"));
    connect(PushButtonNewGame, SIGNAL(clicked(bool)),
            this, SLOT(slotNewGame()));

    LabelHistory = new QLabel("History");
    QGridLayout* GridLayout = new QGridLayout;
    GridLayout->addWidget(LabelAnswer, 0, 0, 1, 2);
    GridLayout->addWidget(LabelGameStatus,1, 0, 1, 2);
    GridLayout->addWidget(PushButtonNewGame, 2, 0);
    GridLayout->addWidget(LabelHistory, 2, 1);
    gridLayoutmain->addLayout(GridLayout, 1, 4, 3, 4);
    ui->centralwidget->setLayout(gridLayoutmain);
}
//....................................................................
BullsAndCown::~BullsAndCown()
{
    delete ui;
}
//....................................................................
QPushButton* BullsAndCown::createButton(QString str)
{
    QPushButton* PushButton = new QPushButton(str);
    PushButton->setMinimumSize(100, 100);
    connect(PushButton, SIGNAL(clicked(bool)),
            SLOT(slotButtonClickedNumbers()));
    return PushButton;
}
//....................................................................
void BullsAndCown::slotButtonClickedNumbers()
{
    massivPushButtons[currentButton]->setText(
        ((QPushButton*)sender())->text());
    if(currentButton == 3) currentButton = 0;
    else currentButton++;
}
//....................................................................
void BullsAndCown::slotButtonClicked(int i)
{
    currentButton = i;
    qDebug() << QObject::tr("changing the current button") << i;
}
//....................................................................
void BullsAndCown::slotNewGame()
{
    RandomGenerationInt();
    qDebug() << QObject::tr("generating an array");
    for (int i = 0; i < 4; i++) {
        qDebug() << intmassiv[i];
    }
    LabelGameStatus->setText(QObject::tr("The new game has begun"));
}
//....................................................................
void BullsAndCown::RandomGenerationInt()
{
    QSet<int> uniqueNumbers;
    int index = 0;

    while (uniqueNumbers.size() < 4) {
        int randomNumber = QRandomGenerator::global()->bounded(10);
        if (!uniqueNumbers.contains(randomNumber)) {
            uniqueNumbers.insert(randomNumber);
            intmassiv[index++] = randomNumber;
        }
    }
}
//....................................................................
void BullsAndCown::slotCheck()
{
    int ColBulls = 0, ColCowns = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (QString::number(intmassiv[i]) ==
                    (massivPushButtons[j]->text()) && i == j) {
                ColBulls++;
            }
            else if(QString::number(intmassiv[i]) ==
                       (massivPushButtons[j]->text())) {
                ColCowns++;
            }
        }
    }
    if (ColBulls == 4) {
        LabelAnswer->setText(QObject::tr("That's right! The hidden number ") +
                             QString::number(intmassiv[0])
                             + QString::number(intmassiv[1])
                             + QString::number(intmassiv[2])
                             + QString::number(intmassiv[3]));
        LabelGameStatus->setText(QObject::tr("Start a new game"));
    }
    LabelHistory->setText(LabelHistory->text() + "\n" + QObject::tr("Number  ")
                          + massivPushButtons[0]->text() +
                          massivPushButtons[1]->text() +
                          massivPushButtons[2]->text()
                          + massivPushButtons[3]->text()
                          + QObject::tr("  Bulls:  ") +
                          QString::number(ColBulls) +
                          QObject::tr("  Cows:  ") + QString::number(ColCowns));
}
//....................................................................
