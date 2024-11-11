#ifndef BULLSANDCOWN_H
#define BULLSANDCOWN_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QDebug>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui {
class BullsAndCown;
}
QT_END_NAMESPACE

class BullsAndCown : public QMainWindow
{
    Q_OBJECT
private:
    Ui::BullsAndCown *ui;
    QPushButton* massivPushButtons[4];
    int intmassiv[4];
    int currentButton;
    QLabel* LabelAnswer;
    QLabel* LabelGameStatus;
    QLabel* LabelHistory;

public:
    BullsAndCown(QWidget *parent = nullptr);
    ~BullsAndCown();
    QPushButton* createButton(QString);
    void RandomGenerationInt();

public slots:
    void slotButtonClickedNumbers();
    void slotButtonClicked(int);
    void slotNewGame();
    void slotCheck();

};
#endif // BULLSANDCOWN_H
