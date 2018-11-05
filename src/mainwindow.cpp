#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

using namespace std;

QString inputWavFileName, cmd, inputSrtFileName;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

class QFileDialogTester : public QFileDialog
{
public:
  void openWavFile()
  {
    inputWavFileName =  QFileDialog::getOpenFileName(
          this,
          "Open .wav Input file",
          QDir::currentPath(),
          "All files (*.*) ;; WAV files (*.wav)");
  }
  void openSrtFile(){
      inputSrtFileName =  QFileDialog::getOpenFileName(
            this,
            "Open .srt Input file",
            QDir::currentPath(),
            "All files (*.*) ;; SubRip text files (*.srt)");
  }
};


QString exec(const char* cmd) {
    char buffer[128];
    QString result = "";
    FILE* pipe = _popen(cmd, "r");
    if (!pipe) throw runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
        _pclose(pipe);
        throw;
    }
    _pclose(pipe);
    return result;
}

void MainWindow::on_SrtOpenButton_clicked()
{
    QFileDialogTester OpenSrt;
    OpenSrt.openSrtFile();
    ui->ChosenSrtLabel->setText("Input .srt file was chosen");
}

void MainWindow::on_WavOpenButton_clicked()
{
    QFileDialogTester OpenWav;
    OpenWav.openWavFile();
    ui->ChosenWavLabel->setText("Input .wav file was chosen");

}

void MainWindow::on_StartButton_clicked()
{
    QString path = qApp->applicationDirPath();
    ui->ChosenWavLabel->setText("No input .wav file chosen");
    ui->ChosenSrtLabel->setText("No input .srt file chosen");
#if defined(Q_OS_WIN)
    cmd = path + "/ccaligner.exe -wav ";
#elif defined(Q_OS_WIN32)
    cmd = path + "/ccaligner.exe -wav ";
#else
    cmd = path + "/./ccaligner -wav ";
#endif
    cmd.append(inputWavFileName);
    cmd.append(" -srt ");
    cmd.append(inputSrtFileName);
    QByteArray ba = cmd.toLocal8Bit();
    const char *c = ba.data();
    QString ccalignerOutput = exec(c);
    ccalignerOutput.remove(0, 284);
    ui->ActivityTextbox->setPlainText(ccalignerOutput);
}

void MainWindow::on_ClearButton_clicked()
{
    ui->ActivityTextbox->setPlainText("");
}
