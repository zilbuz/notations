#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void changeGradeText(const QString &text);

    std::unique_ptr<Ui::MainWindow> m_Ui;

private slots:
    void onTextChanged(QString notes);
};

#endif // MAINWINDOW_H
