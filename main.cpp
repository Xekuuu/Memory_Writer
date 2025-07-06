#include "mainwindow.h"

#include <QApplication>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <windows.h>
#include <tlhelp32.h>

// qt specific string function
QString fromWideChar(const wchar_t* wstr) {
    return QString::fromWCharArray(wstr);
}

void RunningProcesses(QTableWidget* table) {
    table->setRowCount(0);
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels({"Process Name", "PID"});

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return;

    PROCESSENTRY32 processes;
    processes.dwSize = sizeof(PROCESSENTRY32);

    int row = 0;
    if (Process32First(hSnapshot, &processes)) {
        do {
            table->insertRow(row);

            QTableWidgetItem* nameItem = new QTableWidgetItem(fromWideChar(processes.szExeFile));
            QTableWidgetItem* pidItem = new QTableWidgetItem(QString::number(processes.th32ProcessID));

            table->setItem(row, 0, nameItem);
            table->setItem(row, 1, pidItem);

            row++;
        } while (Process32Next(hSnapshot, &processes));
    }

    CloseHandle(hSnapshot);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
