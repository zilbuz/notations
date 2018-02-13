#include <QtCore/QDebug>
#include <QtGui/QRegExpValidator>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    m_Ui{std::make_unique<Ui::MainWindow>()}
{
    m_Ui->setupUi(this);

    m_Ui->lineEdit->setValidator(new QRegExpValidator{QRegExp{"[A-Da-d]{4}"}, this});

    connect(m_Ui->lineEdit, SIGNAL(textChanged(QString)), SLOT(onTextChanged(QString)));
}

MainWindow::~MainWindow() = default;

void MainWindow::changeGradeText(const QString &text)
{
    m_Ui->grade->setText(text);
}

void MainWindow::onTextChanged(QString lettersAsQString)
{
    auto letters = lettersAsQString.toUpper().toLatin1();
    auto idx = 0;

    auto switchLetter = [&letters, &idx] (auto a, auto b, auto c, auto d, auto finished) {
        return [&letters, &idx, a, b, c, d, finished] {
            if (letters.size() > idx) {
                switch (letters[idx++]) {
                case 'A':
                    a();
                    break;
                case 'B':
                    b();
                    break;
                case 'C':
                    c();
                    break;
                case 'D':
                    d();
                    break;
                default:
                    Q_ASSERT(false);
                }
            }
            else {
                finished();
            }
        };
    };

    auto affectGrade = [this, switchLetter] (int init) {
        return switchLetter(
            [this, init] { changeGradeText(QString::number(init)); },
            [this, init] { changeGradeText(QString::number(init - 1)); },
            [this, init] { changeGradeText(QString::number(init - 2)); },
            [this, init] { changeGradeText(QString::number(init - 3)); },
            [this, init] { changeGradeText(tr("de %1 à %2").arg(init - 3).arg(init)); }
        );
    };

    auto process = switchLetter(
                switchLetter( // A
                    switchLetter( // AA
                        affectGrade(20), // AAA
                        affectGrade(18), // AAB
                        affectGrade(16), // AAC
                        affectGrade(15), // AAD
                        [this] {changeGradeText("de 12 à 20");}
                    ),
                    switchLetter( // AB
                        affectGrade(18), // ABA
                        affectGrade(16), // ABB
                        affectGrade(14), // ABC
                        affectGrade(13), // ABD
                        [this] {changeGradeText("de 10 à 18");}
                    ),
                    switchLetter( // AC
                        affectGrade(15), // ACA
                        affectGrade(13), // ACB
                        affectGrade(11), // ACC
                        affectGrade(10), // ACD
                        [this] {changeGradeText("de 7 à 15");}
                    ),
                    switchLetter( // AD
                        affectGrade(13), // ADA
                        affectGrade(11), // ADB
                        affectGrade(9),  // ADC
                        affectGrade(8),  // ADD
                        [this] {changeGradeText("de 5 à 13");}
                    ),
                    [this] {changeGradeText("de 5 à 20");}
                ),
                switchLetter( // B
                    switchLetter( // BA
                        affectGrade(19), // BAA
                        affectGrade(17), // BAB
                        affectGrade(15), // BAC
                        affectGrade(14), // BAD
                        [this] {changeGradeText("de 11 à 19");}
                    ),
                    switchLetter( // BB
                        affectGrade(17), // BBA
                        affectGrade(15), // BBB
                        affectGrade(13), // BBC
                        affectGrade(12), // BBD
                        [this] {changeGradeText("de 9 à 17");}
                    ),
                    switchLetter( // BC
                        affectGrade(14), // BCA
                        affectGrade(12), // BCB
                        affectGrade(10), // BCC
                        affectGrade(9),  // BCD
                        [this] {changeGradeText("de 6 à 14");}
                    ),
                    switchLetter( // BD
                        affectGrade(12), // BDA
                        affectGrade(10), // BDB
                        affectGrade(8),  // BDC
                        affectGrade(7),  // BDD
                        [this] {changeGradeText("de 4 à 12");}
                    ),
                    [this] {changeGradeText("de 4 à 19");}
                ),
                switchLetter( // C
                    switchLetter( // CA
                        affectGrade(17), // CAA
                        affectGrade(15), // CAB
                        affectGrade(13), // CAC
                        affectGrade(12), // CAD
                        [this] {changeGradeText("de 9 à 17");}
                    ),
                    switchLetter( // CB
                        affectGrade(15), // CBA
                        affectGrade(13), // CBB
                        affectGrade(11), // CBC
                        affectGrade(10), // CBD
                        [this] {changeGradeText("de 7 à 15");}
                    ),
                    switchLetter( // CC
                        affectGrade(12), // CCA
                        affectGrade(10), // CCB
                        affectGrade(8),  // CCC
                        affectGrade(7),  // CCD
                        [this] {changeGradeText("de 4 à 12");}
                    ),
                    switchLetter( // CD
                        affectGrade(10), // CDA
                        affectGrade(8), // CDB
                        affectGrade(6), // CDC
                        affectGrade(5), // CDD
                        [this] {changeGradeText("de 2 à 10");}
                    ),
                    [this] {changeGradeText("de 2 à 17");}
                ),
                switchLetter( // D
                    switchLetter( // DA
                        affectGrade(16), // DAA
                        affectGrade(14), // DAB
                        affectGrade(12), // DAC
                        affectGrade(11), // DAD
                        [this] {changeGradeText("de 8 à 16");}
                    ),
                    switchLetter( // DB
                        affectGrade(14), // DBA
                        affectGrade(12), // DBB
                        affectGrade(10), // DBC
                        affectGrade(9),  // DBD
                        [this] {changeGradeText("de 6 à 14");}
                    ),
                    switchLetter( // DC
                        affectGrade(11), // DCA
                        affectGrade(9),  // DCB
                        affectGrade(7),  // DCC
                        affectGrade(6),  // DCD
                        [this] {changeGradeText("de 3 à 11");}
                    ),
                    switchLetter( // DD
                        affectGrade(9), // DDA
                        affectGrade(7), // DDB
                        affectGrade(5), // DDC
                        affectGrade(4), // DDD
                        [this] {changeGradeText("de 1 à 9");}
                    ),
                    [this] {changeGradeText("de 1 à 16");}
                ),
                [this] {changeGradeText("de 1 à 20");}
    );

    process();
}
