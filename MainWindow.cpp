/**********************************************************************
FileSum, a software to get hashes of files
    Copyright (C) 2013  Philippe SWARTVAGHER

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/


#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Dialog|Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);

    m_clipboard = QApplication::clipboard();

    setWindowTitle(tr("FileSum"));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_buttonQuit_clicked()
{
    QApplication::quit();
}


void MainWindow::on_buttonSelect_clicked()
{
    m_filePath = QFileDialog::getOpenFileName(this,
                                              tr("Select file"),
                                              QDir::homePath());
    if(m_filePath.isEmpty())
        return;

    clearValues();
    ui->labelState->setText("Click on button \"Get Hashes !\"");

    ui->lineEditFile->setText(m_filePath);
    ui->buttonHash->setEnabled(true);
}


void MainWindow::on_buttonHash_clicked()
{
    // MD5
    ui->buttonMd5->setEnabled(true);
    ui->lineEditMd5->setEnabled(true);
    ui->lineEditMd5->setText(hash(QCryptographicHash::Md5));

    ui->buttonHash->setEnabled(false);
    ui->labelState->clear();
}


QString MainWindow::hash(QCryptographicHash::Algorithm algorithm)
{
    ui->labelState->setText("Hashing...");

    QByteArray hashed;
    QFile* file = new QFile(m_filePath);

    if(file->open(QFile::ReadOnly))
    {
        hashed = QCryptographicHash::hash(file->readAll(), algorithm);
        file->close();
    }

    QString hash(hashed.toHex().data());

    if(hash.isEmpty())
        return tr("Error");
    else
        return hash;
}


void MainWindow::on_buttonMd5_clicked()
{
    m_clipboard->setText(ui->lineEditMd5->text());
    ui->labelState->setText(tr("MD5 hash was copied."));
}


void MainWindow::clearValues()
{
    ui->buttonMd5->setEnabled(false);

    ui->lineEditMd5->clear();
    ui->lineEditMd5->setEnabled(false);
}

void MainWindow::on_buttonAbout_clicked()
{
    AboutDialog* aboutWindow = new AboutDialog(this);
    aboutWindow->show();
}
