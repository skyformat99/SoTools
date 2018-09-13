#pragma once

#include <QtWidgets/QMainWindow>
#include <fstream>
#include "ui_SectionWindow.h"
#include "qdebug.h"
#include "elf.h"
#include "getshdr.h"

class SectionWindow : public QMainWindow
{
	Q_OBJECT

public:
	SectionWindow(QWidget *parent = Q_NULLPTR);
	~SectionWindow();
private:
	Ui::SectionWindowClass ui;
	int openSo();

	void parseInterp(Elf32_Shdr *);

private slots:
	//���մ��ݹ��������ݵĲ�
	void receiveData(char *, QString, Elf32_Shdr *);

};
