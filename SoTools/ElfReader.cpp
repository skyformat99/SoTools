#include "ElfReader.h"

ElfReader::ElfReader()
{

}

ElfReader::ElfReader(SoTools *ui)
{
	mainUi = ui;
}

ElfReader::~ElfReader(void) 
{
	//pSoFile.close;
}

void ElfReader::setUI(Ui::SoToolsClass ui) 
{
	pUi = ui;
}

int ElfReader::loadSo(const char* soFilePath) 
{
	pSoFilePath = soFilePath;
	pSoFile.open(pSoFilePath, ios::binary);
	if (!pSoFile) 
	{
		//pUi.messageEdit->setText("Read so file error!");
		QString err("select file path:%1,Read so file error!");
		err = err.arg(pSoFilePath);
		mainUi->statusLabel->setText(err);
		return -1;
	}
	return 0;
}

/*
	ELFͷ��(ELF_Header): ÿ��ELF�ļ����������һ��ELF_Header,�������˺ܶ���Ҫ����Ϣ�������������ļ�����֯,��: �汾��Ϣ,�����Ϣ,ƫ����Ϣ�ȡ�����ִ��Ҳ�����������ṩ����Ϣ��
*/
void ElfReader::parseElfHeader()
{
	if (!pSoFile) 
	{
		return;
	}


	char *buf =new char[E32_HEAD_MAGIC_SIZE];
	pSoFile.read(buf, E32_HEAD_MAGIC_SIZE);
	elfHeader = (Elf32_Ehdr *)buf;
	char magicValue[sizeof(elfHeader->e_ident)];
	unsigned char EI_MAG0 = elfHeader->e_ident[0];
	unsigned char EI_MAG1 = elfHeader->e_ident[1];
	unsigned char EI_MAG2 = elfHeader->e_ident[2];
	unsigned char EI_MAG3 = elfHeader->e_ident[3];
	unsigned char EI_MAG4 = elfHeader->e_ident[4];
	unsigned char EI_MAG5 = elfHeader->e_ident[5];
	unsigned char EI_MAG6 = elfHeader->e_ident[6];
	unsigned char EI_MAG7 = elfHeader->e_ident[7];
	unsigned char EI_MAG8 = elfHeader->e_ident[8];
	unsigned char EI_MAG9 = elfHeader->e_ident[9];
	unsigned char EI_MAG10 = elfHeader->e_ident[10];
	unsigned char EI_MAG11 = elfHeader->e_ident[11];
	unsigned char EI_MAG12 = elfHeader->e_ident[12];
	unsigned char EI_MAG13 = elfHeader->e_ident[13];
	unsigned char EI_MAG14 = elfHeader->e_ident[14];
	unsigned char EI_MAG15 = elfHeader->e_ident[15];

	QString magic("%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 %14 %15 %16");
	magic = magic.arg(EI_MAG0,2,16, QLatin1Char('0'))
		.arg(EI_MAG1, 2, 16, QLatin1Char('0'))
		.arg(EI_MAG2, 2, 16, QLatin1Char('0'))
		.arg(EI_MAG3, 2, 16, QLatin1Char('0'))
		.arg(EI_MAG4, 2, 16, QLatin1Char('0'))
		.arg(EI_MAG5, 2, 16, QLatin1Char('0'))
		.arg(EI_MAG6, 2, 16, QLatin1Char('0'))
		.arg(EI_MAG7, 2, 16, QLatin1Char('0'))
		.arg(EI_MAG8, 2, 16, QLatin1Char('0'))
		.arg(EI_MAG9, 2, 16, QLatin1Char('0'))
		.arg(EI_MAG10, 2, 16, QLatin1Char('0'))
		.arg(EI_MAG11, 2, 16, QLatin1Char('0'))
		.arg(EI_MAG12, 2, 16, QLatin1Char('0'))
		.arg(EI_MAG13, 2, 16, QLatin1Char('0'))
		.arg(EI_MAG14, 2, 16, QLatin1Char('0'))
		.arg(EI_MAG15, 2, 16, QLatin1Char('0'))
		;
	//sprintf(magicValue, "%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx", elfHeader->e_ident[0], elfHeader->e_ident[1], elfHeader->e_ident[2], elfHeader->e_ident[3], elfHeader->e_ident[4], elfHeader->e_ident[5], elfHeader->e_ident[6], elfHeader->e_ident[7], elfHeader->e_ident[8], elfHeader->e_ident[9], elfHeader->e_ident[10], elfHeader->e_ident[11], elfHeader->e_ident[12], elfHeader->e_ident[13], elfHeader->e_ident[14], elfHeader->e_ident[15]);
	pUi.magicEdit->setText(magic);

	//��ʶ�ļ�����𣬻���˵��������ȡħ��ֵ�еĵ�4��λ
	if (EI_MAG4 == ELFCLASSNONE) 
	{
		pUi.classKeyEdit->setText("ELFCLASSNONE");
		pUi.classValueEdit->setText(QString::fromLocal8Bit("�Ƿ����"));
	}
	else if (EI_MAG4 == ELFCLASS32) 
	{
		pUi.classKeyEdit->setText("ELF32");
		pUi.classValueEdit->setText(QString::fromLocal8Bit("32λ����"));
	}
	else if (EI_MAG4 == ELFCLASS64) 
	{
		pUi.classKeyEdit->setText("ELF64");
		pUi.classValueEdit->setText(QString::fromLocal8Bit("64λ����"));
	}
	else 
	{
		//QString::fromStdString(to_string(ei_class))
		//QString::number(50,10);
		pUi.classKeyEdit->setText(QString::number(EI_MAG4));
		pUi.classValueEdit->setText(QString::fromLocal8Bit("δֵ֪"));
	}
	//�����������ض����ݵ����ݱ��뷽ʽ,һ�㶼��01������˻���С�˷�ʽ��ȡֵ��Ϊ3�֣�ELFDATANONE��0���Ƿ����ݱ��룻ELFDATA2LSB��1����λ��ǰ��ELFDATA2MSB��2����λ��ǰ��
	__u16 ei_data = (__u16)EI_MAG5;
	if (EI_MAG5 == ELFDATANONE) 
	{
		pUi.dataKeyEdit->setText("ELFDATANONE");
		pUi.dataValueEdit->setText(QString::fromLocal8Bit("�Ƿ����ݱ���"));
	}
	else if (EI_MAG5 == ELFDATA2LSB) 
	{
		pUi.dataKeyEdit->setText("little endian");
		pUi.dataValueEdit->setText(QString::fromLocal8Bit("С��"));
	}
	else if (EI_MAG5 == ELFDATA2MSB) 
	{
		pUi.dataKeyEdit->setText("big endian");
		pUi.dataValueEdit->setText(QString::fromLocal8Bit("���"));
	}
	else 
	{
		pUi.dataKeyEdit->setText(QString::number(EI_MAG5));
		pUi.dataValueEdit->setText(QString::fromLocal8Bit("δֵ֪"));
	}

	//EI_VERSION �ļ��汾,�̶�ֵ01 EV_CURRENT
	pUi.eiVersionKeyEdit->setText(QString::number(EI_MAG6));

	//oa/abi����ϵͳ����
	pUi.osAbiKeyEdit->setText(QString::number(EI_MAG7));
	pUi.osAbiValueEdit->setText(ebl_osabi_name(EI_MAG7));

	//ABI�汾
	pUi.abiVersionKeyEdit->setText(QString::number(EI_MAG8));

	//Ŀ���ļ����� 
	if (elfHeader->e_type == ELF_ET_NONE) 
	{
		pUi.typeKeyEdit->setText("NONE (None)");
		pUi.typeValueEdit->setText(QString::fromLocal8Bit("δ֪��ʽ"));
	}else if (elfHeader->e_type == ELF_ET_REL) 
	{
		pUi.typeKeyEdit->setText("REL (Relocatable file)");
		pUi.typeValueEdit->setText(QString::fromLocal8Bit("���ض�λ�ļ�"));
	}
	else if (elfHeader->e_type == ELF_ET_EXEC)
	{
		pUi.typeKeyEdit->setText("EXEC (Executable file)");
		pUi.typeValueEdit->setText(QString::fromLocal8Bit("��ִ���ļ�"));
	}
	else if (elfHeader->e_type == ELF_ET_DYN)
	{
		pUi.typeKeyEdit->setText("DYN (Shared object file)");
		pUi.typeValueEdit->setText(QString::fromLocal8Bit("����Ŀ���ļ�"));
	}
	else if (elfHeader->e_type == ELF_ET_CORE)
	{
		pUi.typeKeyEdit->setText("CORE (Core file)");
		pUi.typeValueEdit->setText(QString::fromLocal8Bit("ת����ʽ"));
	}
	else if (elfHeader->e_type >= ELF_ET_LOOS && elfHeader->e_type <= ELF_ET_HIOS)
	{
		QString str("OS Specific: (%1)");
		str = str.arg(elfHeader->e_type);
		pUi.typeKeyEdit->setText(str);
		pUi.typeValueEdit->setText(QString::fromLocal8Bit("�ض�������"));
	}
	else if (elfHeader->e_type == ELF_ET_CORE)
	{
		QString str("Processor Specific: (%1)");
		str = str.arg(elfHeader->e_type);
		pUi.typeKeyEdit->setText(str);
		pUi.typeValueEdit->setText(QString::fromLocal8Bit("�ض�������"));
	}
	else
	{
		pUi.typeKeyEdit->setText(QString::number(elfHeader->e_type));
		pUi.typeValueEdit->setText(QString::fromLocal8Bit("δֵ֪"));
	}

	//����������
	QString machine("(0x%1) %2");
	machine = machine.arg(elfHeader->e_machine, 2, 16, QLatin1Char('0')).arg(e_machine(elfHeader->e_machine));
	pUi.machineKeyEdit->setText(machine);

	//Ŀ���ļ��汾
	QString targetVersion("0x%1 %2");
	targetVersion = targetVersion.arg(elfHeader->e_version, 2, 16, QLatin1Char('0')).arg(QString::fromLocal8Bit("��ǰ�汾"));
	pUi.versionKeyEdit->setText(targetVersion);

	//������������ַ
	QString entryPoint("0x%1");
	entryPoint = entryPoint.arg(elfHeader->e_entry, 2, 16, QLatin1Char('0'));
	pUi.entryPointKeyEdit->setText(entryPoint);

	//����ͷ�����ƫ����
	QString phoff("%1 (bytes into file)");
	phoff = phoff.arg(elfHeader->e_phoff);
	pUi.phoffKeyEdit->setText(phoff);

	//����ͷ������ƫ����������ļ�û�н���ͷ����񣬿���Ϊ0
	QString shoff("%1 (bytes into file)");
	shoff = shoff.arg(elfHeader->e_shoff);
	pUi.shoffKeyEdit->setText(shoff);

	//�������ļ���صģ��ض��ڴ������ı�־����־���Ʋ���EF_machine_flag�ĸ�ʽ
	QString flag("0x%1");
	flag = flag.arg(elfHeader->e_flags, 2, 16);
	pUi.flagKeyEdit->setText(flag);

	//elfͷ���Ĵ�С
	QString elfHeadSize("%1 (bytes)");
	elfHeadSize = elfHeadSize.arg(elfHeader->e_ehsize);
	pUi.ehsizeKeyEdit->setText(elfHeadSize);

	//����ͷ�����ı����С
	QString phentsize("%1 (bytes)");
	phentsize = phentsize.arg(elfHeader->e_phentsize);
	pUi.phentsizeKeyEdit->setText(phentsize);

	//����ͷ�����ı�������
	pUi.phnumKeyEdit->setText(QString::number(elfHeader->e_phnum));

	//����ͷ�����ı����С
	QString shentsize("%1 (bytes)");
	shentsize = shentsize.arg(elfHeader->e_shentsize);
	pUi.shentsizeKeyEdit->setText(shentsize);

	//����ͷ�����ı�������
	pUi.shnumKeyEdit->setText(QString::number(elfHeader->e_shnum));

	//����ͷ�����������������ַ�������صı��������������ļ�û�н��������ַ�����Щ��������ΪSHN_UNDEF
	pUi.shstrndxKeyEdit->setText(QString::number(elfHeader->e_shstrndx));
}

void ElfReader::parseProgramHeader()
{
	if (!pSoFile)
	{
		return;
	}
	Elf32_Phdr *pheader;
	const __u32 size = elfHeader->e_phentsize;

	//char *buf = new char;


	//pUi.magicEdit->setText(QString::number(pheader->p_offset));
	//������������
	int columnCount = 8;
	int rowCount = elfHeader->e_phnum;
	pUi.phTable->setColumnCount(columnCount);
	pUi.phTable->setRowCount(rowCount + 1);

	QString phInfo(QString::fromLocal8Bit("����ͷ����(Program_Header_Table): �� %1 ������ͷ, ���ļ� %2 �ֽڿ�ʼ\r\n\t��ѡ��һ�������ڸ���ϵͳ������ڴ��д���ӳ��,��ͼ��Ҳ���Կ�����,�г���ͷ������ж�,�жξͱ����г���ͷ�������д�Ÿ����εĻ�����Ϣ(������ַָ��)��\r\n\t---��Ҫ�鿴�����ֶε�ֵ����������ڱ������档"));
	phInfo = phInfo.arg(rowCount,0,10).arg(elfHeader->e_ehsize, 0, 10);
	pUi.phinfoLabel->setText(phInfo);
	//QStringList headerTab;
	//headerTab << "Type" << "Offset" << "VirtAddr" << "PhysAddr" << "FileSiz" << "MemSiz" << "Flg" << "Align";
	//pUi.phTable->setHorizontalHeaderLabels(headerTab);
	//
	QTableWidgetItem *headeritem = new QTableWidgetItem(QString::fromLocal8Bit("������(Type)"));
	//headeritem->setTextAlignment(Qt::AlignCenter);
	headeritem->setToolTip(QString::fromLocal8Bit("�����Ա�����������Ԫ������ʲô���ĶΣ�������ν�������Ԫ�ص���Ϣ��"));
	pUi.phTable->setHorizontalHeaderItem(0, headeritem);

	QTableWidgetItem *headeritem1 = new QTableWidgetItem(QString::fromLocal8Bit("��ƫ��(Offset)"));
	headeritem1->setToolTip(QString::fromLocal8Bit("�˳�Ա�������ļ�ͷ���öε�һ���ֽڵ�ƫ�ơ�"));
	pUi.phTable->setHorizontalHeaderItem(1, headeritem1);

	QTableWidgetItem *headeritem2 = new QTableWidgetItem(QString::fromLocal8Bit("�������ַ(VirtAddr)"));
	headeritem2->setToolTip(QString::fromLocal8Bit("�˳�Ա�����εĵ�һ���ֽڽ����ŵ��ڴ��е������ַ��"));
	pUi.phTable->setHorizontalHeaderItem(2, headeritem2);

	QTableWidgetItem *headeritem3 = new QTableWidgetItem(QString::fromLocal8Bit("�����ַ(PhysAddr)"));
	headeritem3->setToolTip(QString::fromLocal8Bit("�˳�Ա�������������ַ��ص�ϵͳ�С���Ϊ System V ��������Ӧ�ó���������ַ��Ϣ�����ֶζ����ִ���ļ��͹���Ŀ���ļ����ԣ�����������δָ���ġ�"));
	pUi.phTable->setHorizontalHeaderItem(3, headeritem3);

	QTableWidgetItem *headeritem4 = new QTableWidgetItem(QString::fromLocal8Bit("���ļ��ֽ���(FileSiz)"));
	headeritem4->setToolTip(QString::fromLocal8Bit("�˳�Ա���������ļ�ӳ������ռ���ֽ���������Ϊ 0��"));
	pUi.phTable->setHorizontalHeaderItem(4, headeritem4);

	QTableWidgetItem *headeritem5 = new QTableWidgetItem(QString::fromLocal8Bit("���ڴ��ֽ���(MemSiz)"));
	headeritem5->setToolTip(QString::fromLocal8Bit("�˳�Ա���������ڴ�ӳ����ռ�õ��ֽ���������Ϊ 0��"));
	pUi.phTable->setHorizontalHeaderItem(5, headeritem5);

	QTableWidgetItem *headeritem6 = new QTableWidgetItem(QString::fromLocal8Bit("�α�־(Flag)"));
	headeritem6->setToolTip(QString::fromLocal8Bit("�˳�Ա���������صı�־��ֵ��1,��ִ�еĶ�;2,��д�Ķ�;4,�ɶ��Ķ�;0,����"));
	pUi.phTable->setHorizontalHeaderItem(6, headeritem6);

	QTableWidgetItem *headeritem7 = new QTableWidgetItem(QString::fromLocal8Bit("�ζ��뷽ʽ(Align)"));
	headeritem7->setToolTip(QString::fromLocal8Bit("�ɼ��صĽ��̶ε� p_vaddr �� p_offset ȡֵ������ʣ�����ڶ�ҳ���С��ȡģ���ԡ��˳�Ա���������ļ��к��ڴ������ ���롣��ֵ 0 �� 1 ��ʾ����Ҫ���롣���� p_align Ӧ���Ǹ� �������������� 2 ���ݴ�����p_vaddr �� p_offset �� p_align ȡģ��Ӧ����ȡ�"));
	pUi.phTable->setHorizontalHeaderItem(7, headeritem7);
	//�Զ��������
	pUi.phTable->horizontalHeader()->setStretchLastSection(true);
	pUi.phTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	pUi.phTable->verticalHeader()->setVisible(false);
	//���ܶԱ�����ݽ����޸�
	pUi.phTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	pUi.phTable->setSelectionMode(QAbstractItemView::ExtendedSelection);  //�ɶ�ѡ��Ctrl��Shift��  Ctrl+A�����ԣ�
	pUi.phTable->setStyleSheet("selection-background-color:lightblue;"); //����ѡ�б���ɫ

	//�ñ�ͷ�����ֿ���
	pUi.phTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
	QFont font = pUi.phTable->horizontalHeader()->font();
	font.setBold(true);
	pUi.phTable->horizontalHeader()->setFont(font);
	pUi.phTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //���ñ�ͷ����ɫ

	pSoFile.seekg(elfHeader->e_ehsize);
	//qDebug() <<"num=" << rowCount << endl;
	bool hasInterp = false;
	size_t interpRow;
	Elf32_Off interpOff;
	Elf32_Word interpSize;
	for(int row = 0; row < rowCount; row++)
	{
		char buf[32];
		pSoFile.read(buf, size);
		pheader = (Elf32_Phdr *)buf;
		//qDebug() << row << endl;
		setPhRow(hasInterp ? row+1:row, pheader);
		/* We can show the user the name of the interpreter.  */
		if (pheader->p_type == ELF_PT_INTERP) 
		{

			QTableWidgetItem *item = new QTableWidgetItem(QString::fromLocal8Bit("[Requesting program interpreter: /system/bin/linker]"));
			item->setTextAlignment(Qt::AlignCenter);
			item->setToolTip("hello");
			pUi.phTable->setSpan(row + 1, 0, 1, columnCount);
			pUi.phTable->setItem(row + 1, 0, item);
			hasInterp = true;
			interpRow = row + 1;
			interpOff = pheader->p_offset;
			interpSize = pheader->p_filesz;
		}
		else if (pheader->p_type == ELF_PT_GNU_RELRO)
		{
			//has_relro = true;
			//relro_from = phdr->p_vaddr;
			//relro_to = relro_from + phdr->p_memsz;
		}
	}
	if (hasInterp) 
	{
		pSoFile.seekg(interpOff);
		char *interpValue = new char[interpSize];
		pSoFile.read(interpValue, interpSize);

		QString interpStr("[Requesting program interpreter: %1]");
		interpStr = interpStr.arg(interpValue);
		QTableWidgetItem *itemInterp = new QTableWidgetItem(interpStr);
		itemInterp->setTextAlignment(Qt::AlignCenter);
		itemInterp->setToolTip(QString::fromLocal8Bit("ʹ�õĶ�̬������·������Ҫ����ʵ�ֹ����ļ���������"));
		pUi.phTable->setSpan(interpRow, 0, 1, columnCount);
		pUi.phTable->setItem(interpRow, 0, itemInterp);
		delete[]interpValue;
	}
}

void ElfReader::parseSectionHeader()
{
	if (!pSoFile)
	{
		return;
	}
	//e_shoff ��Ա�������ļ�ͷ������ͷ������ƫ���ֽ���
	size_t shoff = elfHeader->e_shoff;
	//e_shnum �����������Ŀ��Ŀ
	size_t shnum = elfHeader->e_shnum;
	//e_shentsize ����ÿ����Ŀ���ֽ���������Щ��Ϣ�п���ȷ�еض� λ�����ľ���λ�á�����
	size_t size = elfHeader->e_shentsize;
	//ÿ������ͷ�����ݽṹ����
	Elf32_Shdr *sheader;

	size_t cnt;	
	
	QString phentsize(QString::fromLocal8Bit("\t�� %1 ����ͷ��, �ļ���ƫ�Ƶ�ַ 0x%2\r\n\t---��Ҫ�鿴�����ֶε�ֵ����������ڱ������档\r\n\t---�������(Name)�鿴����"));
	phentsize = phentsize.arg(shnum).arg(shoff, 0, 16);
	pUi.shinfoLabel->setText(phentsize);

	pUi.shTable->setColumnCount(11);
	pUi.shTable->setRowCount(shnum);

	//QStringList headerTab;
	//headerTab << "[Nr]" << "Name" << "Type" << "Addr" << "Off" << "Size" << "ES" << "Flg" << "Lk" << "Inf" << "Al";
	//pUi.shTable->setHorizontalHeaderLabels(headerTab);

	QTableWidgetItem *headeritem = new QTableWidgetItem(QString::fromLocal8Bit("�к�[Nr]"));
	headeritem->setToolTip(QString::fromLocal8Bit("һ�д���һ������ͷ��"));
	pUi.shTable->setHorizontalHeaderItem(0, headeritem);

	QTableWidgetItem *headeritem1 = new QTableWidgetItem(QString::fromLocal8Bit("����(Name)"));
	headeritem1->setToolTip(QString::fromLocal8Bit("Section Name ����"));
	pUi.shTable->setHorizontalHeaderItem(1, headeritem1);

	QTableWidgetItem *headeritem2 = new QTableWidgetItem(QString::fromLocal8Bit("����(Type)"));
	headeritem2->setToolTip(QString::fromLocal8Bit("Section Type �ε����ͣ���Ҫ�����ε������Ƕε����ͺͱ�־λ"));
	pUi.shTable->setHorizontalHeaderItem(2, headeritem2);

	QTableWidgetItem *headeritem3 = new QTableWidgetItem(QString::fromLocal8Bit("��ַ(Addr)"));
	headeritem3->setToolTip(QString::fromLocal8Bit("Section Address �������ַ,����öο��Ա����أ���sh_addrΪ�öα����غ��ڽ��̵�ַ�ռ��е������ַ������sh_addrΪ0"));
	pUi.shTable->setHorizontalHeaderItem(3, headeritem3);

	QTableWidgetItem *headeritem4 = new QTableWidgetItem(QString::fromLocal8Bit("ƫ��(Off)"));
	headeritem4->setToolTip(QString::fromLocal8Bit("Section Offset��ƫ�ƣ�����öδ������ļ��У����ʾ�ö����ļ��е�ƫ�ƣ����������壬����sh_offset����BSS����˵��û������"));
	pUi.shTable->setHorizontalHeaderItem(4, headeritem4);

	QTableWidgetItem *headeritem5 = new QTableWidgetItem(QString::fromLocal8Bit("����(Size)"));
	headeritem5->setToolTip(QString::fromLocal8Bit("Section Size �εĳ���"));
	pUi.shTable->setHorizontalHeaderItem(5, headeritem5);

	QTableWidgetItem *headeritem6 = new QTableWidgetItem(QString::fromLocal8Bit("���(ES)"));
	headeritem6->setToolTip(QString::fromLocal8Bit("Section Entry Size��ĳ���"));
	pUi.shTable->setHorizontalHeaderItem(6, headeritem6);

	QTableWidgetItem *headeritem7 = new QTableWidgetItem(QString::fromLocal8Bit("���(Flg)"));
	headeritem7->setToolTip(QString::fromLocal8Bit("Section flag�εı��λ����ʾ�ý��ڽ��������ַ�ռ��е����ԣ������Ƿ��д����ִ�е�"));
	pUi.shTable->setHorizontalHeaderItem(7, headeritem7);

	QTableWidgetItem *headeritem8 = new QTableWidgetItem(QString::fromLocal8Bit("����(Lk)"));
	headeritem8->setToolTip(QString::fromLocal8Bit("Section Link �ε����ӣ���������������Ǻ�������صģ������ض�λ�����ű�ȣ���ôsh_link��sh_info������Ա���������壬���������Σ���������Ա��û����"));
	pUi.shTable->setHorizontalHeaderItem(8, headeritem8);

	QTableWidgetItem *headeritem9 = new QTableWidgetItem(QString::fromLocal8Bit("��Ϣ(Inf)"));
	headeritem9->setToolTip(QString::fromLocal8Bit("Section Information �ε���Ϣ�����ε�����"));
	pUi.shTable->setHorizontalHeaderItem(9, headeritem9);

	QTableWidgetItem *headeritem10 = new QTableWidgetItem(QString::fromLocal8Bit("��Ӧ(Al)"));
	headeritem10->setToolTip(QString::fromLocal8Bit("Section Address Alignment �ε�ַ���룬��Щ�ζ��ڵ�ַ������Ҫ�󣬱������Ǽ����и��θտ�ʼ��λ�ð�����һ��double��������ΪIntel x86ϵͳҪ�󸡵����Ĵ洢��ַ�����Ǳ������������Ҳ����˵����double�����ĵ�ַ������8�ֽڵ���������������һ������˵������sh_addr������8�������������sh_addralignΪ0��1�����ʾ�ö�û�ж���Ҫ��"));
	pUi.shTable->setHorizontalHeaderItem(10, headeritem10);

	pUi.shTable->horizontalHeader()->setStretchLastSection(true);
	pUi.shTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	pUi.shTable->verticalHeader()->setVisible(false);
	//���ܶԱ�����ݽ����޸�
	pUi.shTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	pUi.shTable->setSelectionMode(QAbstractItemView::ExtendedSelection);  //�ɶ�ѡ��Ctrl��Shift��  Ctrl+A�����ԣ�
	pUi.shTable->setStyleSheet("selection-background-color:lightblue;"); //����ѡ�б���ɫ

	//�ñ�ͷ�����ֿ���
	pUi.shTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
	QFont font = pUi.shTable->horizontalHeader()->font();
	font.setBold(true);
	pUi.shTable->horizontalHeader()->setFont(font);
	pUi.shTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //���ñ�ͷ����ɫ
	//����ˮƽ������
	pUi.shTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	pUi.shTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	pUi.shTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	pUi.shTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

	pUi.shTable->setSelectionBehavior(QAbstractItemView::SelectRows); //����ѡ����Ϊ������Ϊ��λ
	pUi.shTable->setSelectionMode(QAbstractItemView::SingleSelection); //����ѡ��ģʽ��ѡ����

	shstrtabs = new size_t[shnum];
	mainUi->sectionHeaders = new Elf32_Shdr[shnum];
	pSoFile.seekg(shoff);
	for (cnt = 0; cnt < shnum; ++cnt)
	{
		char buf[40];
		pSoFile.read(buf, size);
		sheader = (Elf32_Shdr *)buf;
		mainUi->sectionHeaders[cnt] = (*sheader);
		setShRow(cnt, sheader);
	}

	//��Name�����¶�ȡ�ַ���
	for (cnt = 0; cnt < shnum; ++cnt)
	{
		size_t start = shstrtabs[cnt];
		
		//
		pSoFile.seekg(sectionHeaderOffset + start);
		char shNameValue[20];
		pSoFile.read(shNameValue, 20);

		QTableWidgetItem *item = new QTableWidgetItem(QString::fromLocal8Bit(shNameValue));
		item->setTextAlignment(Qt::AlignCenter);
		pUi.shTable->setItem(cnt, 1, item);

	}
	delete []shstrtabs;
	shstrtabs = NULL;
}

void ElfReader::closeSo()
{
	if (!pSoFile)
	{
		return;
	}
	pSoFile.close();
}

//ÿһ�н�������
void ElfReader::setShRow(int row, Elf32_Shdr *sheader)
{
	//������
	QString nr("[%1]");
	nr = nr.arg(row, 2, 10, QLatin1Char(' '));
	QTableWidgetItem *item = new QTableWidgetItem(nr);
	item->setTextAlignment(Qt::AlignCenter);
	//item->setToolTip(QString::fromLocal8Bit(getphtypedesc(pheader->p_type)));
	pUi.shTable->setItem(row, 0, item);

	QString shName("%1");
	shName = shName.arg(sheader->sh_name);
	QTableWidgetItem *item1 = new QTableWidgetItem(shName);
	item1->setTextAlignment(Qt::AlignCenter);
	pUi.shTable->setItem(row, 1, item1);
	shstrtabs[row] = sheader->sh_name;

	QTableWidgetItem *item2 = new QTableWidgetItem(getshtype(sheader->sh_type));
	item2->setTextAlignment(Qt::AlignCenter);
	item2->setToolTip(getshtypedesc(sheader->sh_type));
	pUi.shTable->setItem(row, 2, item2);
	//��sh_type����.shstrtab��ֵ�ǣ���¼�����ַ�����ƫ�Ƶ�ַ�ͳ���
	if (sheader->sh_type == SHT_STRTAB) {
		sectionHeaderAddress = sheader->sh_addr;
		sectionHeaderOffset = sheader->sh_offset;
		sectionHeaderSize = sheader->sh_size;
	}

	QString shAddr("%1");
	shAddr = shAddr.arg(sheader->sh_addr, 8, 16, QLatin1Char('0'));
	QTableWidgetItem *item3 = new QTableWidgetItem(shAddr);
	item3->setTextAlignment(Qt::AlignCenter);
	pUi.shTable->setItem(row, 3, item3);

	QString shOff("%1");
	shOff = shOff.arg(sheader->sh_offset, 6, 16, QLatin1Char('0'));
	QTableWidgetItem *item4 = new QTableWidgetItem(shOff);
	item4->setTextAlignment(Qt::AlignCenter);
	pUi.shTable->setItem(row, 4, item4);

	QString shSize("%1");
	shSize = shSize.arg(sheader->sh_size, 6, 16, QLatin1Char('0'));
	QTableWidgetItem *item5 = new QTableWidgetItem(shSize);
	item5->setTextAlignment(Qt::AlignCenter);
	pUi.shTable->setItem(row, 5, item5);

	QString shEs("%1");
	shEs = shEs.arg(sheader->sh_entsize, 2, 16, QLatin1Char('0'));
	QTableWidgetItem *item6 = new QTableWidgetItem(shEs);
	item6->setTextAlignment(Qt::AlignCenter);
	pUi.shTable->setItem(row, 6, item6);

	QString shFlag("%1");
	shFlag = shFlag.arg(getshflag(sheader->sh_flags));
	QTableWidgetItem *item7 = new QTableWidgetItem(shFlag);
	item7->setTextAlignment(Qt::AlignCenter);
	pUi.shTable->setItem(row, 7, item7);

	QString shLk("%1");
	shLk = shLk.arg(sheader->sh_link);
	QTableWidgetItem *item8 = new QTableWidgetItem(shLk);
	item8->setTextAlignment(Qt::AlignCenter);
	pUi.shTable->setItem(row, 8, item8);

	QString shInf("%1");
	shInf = shInf.arg(sheader->sh_info);
	QTableWidgetItem *item9 = new QTableWidgetItem(shInf);
	item9->setTextAlignment(Qt::AlignCenter);
	pUi.shTable->setItem(row, 9, item9);

	QString shAl("%1");
	shAl = shAl.arg(sheader->sh_addralign);
	QTableWidgetItem *item10 = new QTableWidgetItem(shAl);
	item10->setTextAlignment(Qt::AlignCenter);
	pUi.shTable->setItem(row, 10, item10);
}

//ÿһ�г���ͷ����
void ElfReader::setPhRow(int row, Elf32_Phdr *pheader)
{
	//������
	QTableWidgetItem *item = new QTableWidgetItem(QString::fromLocal8Bit(getphtype(pheader->p_type)));
	item->setTextAlignment(Qt::AlignCenter);
	item->setToolTip(QString::fromLocal8Bit(getphtypedesc(pheader->p_type)));
	pUi.phTable->setItem(row, 0, item);

	QString phOffset("0x%1");
	phOffset = phOffset.arg(pheader->p_offset, 6, 16, QLatin1Char('0'));
	QTableWidgetItem *item1 = new QTableWidgetItem(phOffset);
	item1->setTextAlignment(Qt::AlignCenter);
	pUi.phTable->setItem(row, 1, item1);

	QString phVirtAddr("0x%1");
	phVirtAddr = phVirtAddr.arg(pheader->p_vaddr, 8, 16, QLatin1Char('0'));
	QTableWidgetItem *item2 = new QTableWidgetItem(phVirtAddr);
	item2->setTextAlignment(Qt::AlignCenter);
	pUi.phTable->setItem(row, 2, item2);

	QString phPhysAddr("0x%1");
	phPhysAddr = phPhysAddr.arg(pheader->p_paddr, 8, 16, QLatin1Char('0'));
	QTableWidgetItem *item3 = new QTableWidgetItem(phPhysAddr);
	item3->setTextAlignment(Qt::AlignCenter);
	pUi.phTable->setItem(row, 3, item3);

	QString phFileSiz("0x%1");
	phFileSiz = phFileSiz.arg(pheader->p_filesz, 5, 16, QLatin1Char('0'));
	QTableWidgetItem *item4 = new QTableWidgetItem(phFileSiz);
	item4->setTextAlignment(Qt::AlignCenter);
	pUi.phTable->setItem(row, 4, item4);

	QString phMemSize("0x%1");
	phMemSize = phMemSize.arg(pheader->p_memsz, 5, 16, QLatin1Char('0'));
	QTableWidgetItem *item5 = new QTableWidgetItem(phMemSize);
	item5->setTextAlignment(Qt::AlignCenter);
	pUi.phTable->setItem(row, 5, item5);

	QTableWidgetItem *item6 = new QTableWidgetItem(getphflg(pheader->p_flags));
	item6->setTextAlignment(Qt::AlignCenter);
	pUi.phTable->setItem(row, 6, item6);

	QString phAlign("0x%1");
	phAlign = phAlign.arg(pheader->p_align, 0, 16, QLatin1Char('0'));
	QTableWidgetItem *item7 = new QTableWidgetItem(phAlign);
	item7->setTextAlignment(Qt::AlignCenter);
	pUi.phTable->setItem(row, 7, item7);
}



