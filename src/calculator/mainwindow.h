#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <graph.h>

#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QString>
extern "C" {
#include "../smartcalc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_equals_clicked();
  void digits_numbers();

  void on_dot_clicked();

  void on_delete_2_clicked();

 private:
  Ui::MainWindow *ui;
  Graph *graph;
};
#endif  // MAINWINDOW_H
