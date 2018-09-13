#include "getphdr.h"

const char *getphtype(Elf32_Word type) {
	const char *res;
	if (type == ELF_PT_NULL)
		res = "NULL";
	else if (type == ELF_PT_LOAD)
		res = "LOAD";
	else if (type == ELF_PT_DYNAMIC)
		res = "DYNAMIC";
	else if (type == ELF_PT_INTERP)
		res = "INTERP";
	else if (type == ELF_PT_NOTE)
		res = "NOTE";
	else if (type == ELF_PT_SHLIB)
		res = "SHLIB";
	else if (type == ELF_PT_PHDR)
		res = "PHDR";
	else if (type == ELF_PT_TLS)
		res = "TLS";
	else if (type == ELF_PT_LOOS)
		res = "LOOS";
	else if (type == ELF_PT_HIOS)
		res = "HIOS";
	else if (type == ELF_PT_LOPROC)
		res = "LOPROC";
	else if (type == ELF_PT_HIPROC)
		res = "HIPROC";
	else if (type == ELF_PT_GNU_EH_FRAME)
		res = "GNU_EH_FRAME";
	else if (type == ELF_PT_SUNW_EH_FRAME)
		res = "SUNW_EH_FRAME";
	else if (type == ELF_PT_SUNW_UNWIND)
		res = "SUNW_UNWIND";
	else if (type == ELF_PT_GNU_STACK)
		res = "GNU_STACK";
	else if (type == ELF_PT_GNU_RELRO)
		res = "GNU_RELRO";
	else if (type == ELF_PT_OPENBSD_RANDOMIZE)
		res = "OPENBSD_RANDOMIZE";
	else if (type == ELF_PT_OPENBSD_WXNEEDED)
		res = "OPENBSD_WXNEEDED";
	else if (type == ELF_PT_OPENBSD_BOOTDATA)
		res = "OPENBSD_BOOTDATA";
	else if (type == ELF_PT_ARM_ARCHEXT)
		res = "ARCHEXT";
	else if (type == ELF_PT_ARM_EXIDX)
		res = "EXIDX";
	else if (type == ELF_PT_ARM_UNWIND)
		res = "UNWIND";
	else if (type == ELF_PT_MIPS_REGINFO)
		res = "MIPS_REGINFO";
	else if (type == ELF_PT_MIPS_RTPROC)
		res = "MIPS_RTPROC";
	else if (type == ELF_PT_MIPS_OPTIONS)
		res = "MIPS_OPTIONS";
	else if (type == ELF_PT_MIPS_ABIFLAGS)
		res = "MIPS_ABIFLAGS";
	else
	{
		QString other("(0x%1) <unknown>");
		other = other.arg(type, 8, 16, QLatin1Char('0'));
		res = other.toLocal8Bit().data();
	}
	return res;
}

/*��̬����,����� https://docs.oracle.com/cd/E24847_01/html/E22196/chapter6-14428.html*/
const char *getphtypedesc(Elf32_Word type) {
	const char *res;
	if (type == ELF_PT_NULL)
		res = "������Ԫ��δ�ã��ṹ��������Ա����δ����ġ�";
	else if (type == ELF_PT_LOAD)
		res = "������Ԫ�ظ���һ���ɼ��صĶ�,�εĴ�С�� p_filesz �� p_memsz �������ļ��е��ֽڱ�ӳ�䵽�ڴ�ο�ʼ������� p_memsz ���� p_filesz,��ʣ�ࡱ���ֽ�Ҫ���㡣p_filesz ���ܴ��� p_memsz���ɼ��صĶ��ڳ���ͷ������и��� p_vaddr ��Ա���������С�";
	else if (type == ELF_PT_DYNAMIC)
		res = "����Ԫ�ظ�����̬������Ϣ��";
	else if (type == ELF_PT_INTERP)
		res = "����Ԫ�ظ���һ�� NULL ��β���ַ�����λ�úͳ���,���ַ��������������������á����ֶ����ͽ������ִ���ļ�������(����Ҳ�����ڹ���Ŀ���ļ��Ϸ���)����һ���ļ��в��ܳ���һ�����ϡ���������������͵Ķ�,�����������пɼ��ض���Ŀ��ǰ�档";
	else if (type == ELF_PT_NOTE)
		res = "������Ԫ�ظ���������Ϣ��λ�úʹ�С��";
	else if (type == ELF_PT_SHLIB)
		res = "�˶����ͱ�����,��������δָ���������������͵Ķεĳ����� ABI������";
	else if (type == ELF_PT_PHDR)
		res = "�����͵�����Ԫ���������,������˳���ͷ��������Ĵ�С��λ��,�Ȱ������ļ���Ҳ�������ڴ��е���Ϣ�������͵Ķ����ļ��в��ܳ���һ�����ϡ�����ֻ�г���ͷ�����ǳ�����ڴ�ӳ���һ����ʱ�������á�������ڴ����Ͷ�,����������пɼ��ض���Ŀ��ǰ�档";
	else if (type == ELF_PT_TLS)
		res = "ָ���ֲ߳̾��洢ģ��,����ʱ������ֲ߳̾����ݵĶ����������������ִ���̹߳����������͵�����Ԫ��һ��ָ�� TLS ��ʼ��ӳ���ָ��,TLS ��ʼ��ӳ��Ĵ�С(TLS initialisation image),��ʾģ���Ƿ�ʹ�þ�̬ TLS ģʽ�ı�ʶ�������ܹ�֧�־�̬ TLS ģʽ����";
	else if (type == ELF_PT_LOOS)
		res = "�˷�Χ�ڰ�����ֵ���������ض��ڲ���ϵͳ�����塣";
	else if (type == ELF_PT_HIOS)
		res = "�˷�Χ�ڰ�����ֵ���������ض��ڲ���ϵͳ�����塣";
	else if (type == ELF_PT_LOPROC)
		res = "�˷�Χ�ڰ�����ֵ������������ֵ�����������ض��ڴ����������塣";
	else if (type == ELF_PT_HIPROC)
		res = "�˷�Χ�ڰ�����ֵ������������ֵ�����������ض��ڴ����������塣";
	else if (type == ELF_PT_GNU_EH_FRAME)
		res = "GNU_EH_FRAME";
	else if (type == ELF_PT_SUNW_EH_FRAME)
		res = "�˶ΰ���ջ��չ��PT_SUNW_EH_FRAME �� PT_SUNW_EH_UNWIND ��Ч��";
	else if (type == ELF_PT_SUNW_UNWIND)
		res = "�˶ΰ���ջ��չ��";
	else if (type == ELF_PT_GNU_STACK)
		res = "GNU_STACK";
	else if (type == ELF_PT_GNU_RELRO)
		res = "GNU_RELRO";
	else if (type == ELF_PT_OPENBSD_RANDOMIZE)
		res = "OPENBSD_RANDOMIZE";
	else if (type == ELF_PT_OPENBSD_WXNEEDED)
		res = "OPENBSD_WXNEEDED";
	else if (type == ELF_PT_OPENBSD_BOOTDATA)
		res = "OPENBSD_BOOTDATA";
	else if (type == ELF_PT_ARM_ARCHEXT)
		res = "ARM_ARCHEXT";
	else if (type == ELF_PT_ARM_EXIDX)
		res = "ARM_EXIDX";
	else if (type == ELF_PT_ARM_UNWIND)
		res = "ARM_UNWIND";
	else if (type == ELF_PT_MIPS_REGINFO)
		res = "MIPS_REGINFO";
	else if (type == ELF_PT_MIPS_RTPROC)
		res = "MIPS_RTPROC";
	else if (type == ELF_PT_MIPS_OPTIONS)
		res = "MIPS_OPTIONS";
	else if (type == ELF_PT_MIPS_ABIFLAGS)
		res = "MIPS_ABIFLAGS";
	else
		res = "<unknown>";
	return res;
}

const QString getphflg(Elf32_Word flag)
{
	QString flags("");
	if (flag & PF_R)
		flags = flags.append(QString::fromLocal8Bit("��"));
	else
		flags = flags.append(QString::fromLocal8Bit(" "));

	if (flag & PF_W)
		flags = flags.append(QString::fromLocal8Bit("д"));
	else
		flags = flags.append(QString::fromLocal8Bit(" "));

	if (flag & PF_X)
		flags = flags.append(QString::fromLocal8Bit("ִ��"));
	else
		flags = flags.append(QString::fromLocal8Bit(" "));
	
	//if (flag & PF_MASKPROC)
	//	res = "����";
	return flags;
}
