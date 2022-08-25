#pragma once

#include <QtWidgets/QWidget>
#include "ui_ShellcodeFramework.h"

class ShellcodeFramework : public QWidget
{
    Q_OBJECT

public:
    ShellcodeFramework(QWidget *parent = nullptr);
    ~ShellcodeFramework();

private:
    Ui::ShellcodeFrameworkClass ui;

private slots:
    void on_open_Shellcode();
    void on_pushButton_clicked();

    void on_pushButton_shellcode_clicked();

    void on_pushButton_Permissionmaintenance_clicked();

    void on_pushButton_shellcode_2_clicked();

    void on_pushButton_Permissionmaintenance_2_clicked();

    void on_pushButtonShellcoderaw_clicked();

    void on_pushButton_icon_clicked();

    void on_pushButton_file_clicked();

    void on_pushButton_generate_clicked();

    void on_pushButtonCleaner_clicked();
};
