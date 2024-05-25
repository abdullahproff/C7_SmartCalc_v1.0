#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->zero, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->one, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->two, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->three, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->four, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->five, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->six, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->seven, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->eight, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->nine, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->add, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->sub, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->mul, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->division, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->root, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->degree, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->bracket_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->bracket_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->variable_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
}
MainWindow::~MainWindow() { delete ui, delete graph; }

void MainWindow::on_equals_clicked() {
  QString str = ui->result_show->text();
  QByteArray byte_string = str.toLocal8Bit();
  char *equation = byte_string.data();
  if ((str.contains('x')) && (ui->input_x->text() == "") &&
      (!validator(equation))) {
    graph = new Graph;
    graph->show();
    graph->graphics(equation);
  } else {
    double x;
    double *X = NULL;
    if ((str.contains('x')) && ui->input_x->text() != "") {
      x = ui->input_x->text().toDouble();
      X = &x;
    }
    double res = 0;
    if (!calculator(equation, X, &res)) {
      QString numberResult = QString::number(res, 'g', 15);
      ui->result_show->setText(numberResult);
    }
  }
}

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString input = ui->result_show->text();
  if (input == "0") {
    ui->result_show->clear();
  }
  QString newlabel = ui->result_show->text() + button->text();
  ui->result_show->setText(newlabel);
}

void MainWindow::on_dot_clicked() {
  if (!(ui->result_show->text().contains('.'))) {
    ui->result_show->setText(ui->result_show->text() + '.');
  }
}

void MainWindow::on_delete_2_clicked() {
  ui->result_show->setText("0");
  ui->input_x->setText("");
}
