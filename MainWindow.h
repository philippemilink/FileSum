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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QCryptographicHash>
#include <QClipboard>

#include "AboutDialog.h"


namespace Ui
{
    class MainWindow;
}


class MainWindow : public QWidget
{
    Q_OBJECT
    

    public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    private slots:
    void on_buttonQuit_clicked();
    void on_buttonSelect_clicked();
    void on_buttonHash_clicked();
    void on_buttonMd5_clicked();
    void on_buttonAbout_clicked();
    void clearValues();
    

    private:
    QString hash(QCryptographicHash::Algorithm algorithm);

    Ui::MainWindow *ui;
    QString m_filePath;
    QClipboard* m_clipboard;
};

#endif // MAINWINDOW_H
