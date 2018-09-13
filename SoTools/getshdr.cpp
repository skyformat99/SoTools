#include "getshdr.h"

const QString getshtype(Elf32_Word type)
{
	const char *res;
	if (type == SHT_NULL)
		res = "NULL";
	else if (type == SHT_PROGBITS)
		res = "PROGBITS";
	else if (type == SHT_SYMTAB)
		res = "SYMTAB";
	else if (type == SHT_STRTAB)
		res = "STRTAB";
	else if (type == SHT_RELA)
		res = "RELA";
	else if (type == SHT_HASH)
		res = "HASH";
	else if (type == SHT_DYNAMIC)
		res = "DYNAMIC";
	else if (type == SHT_NOTE)
		res = "NOTE";
	else if (type == SHT_NOBITS)
		res = "NOBITS";
	else if (type == SHT_REL)
		res = "REL";
	else if (type == SHT_SHLIB)
		res = "SHLIB";
	else if (type == SHT_DYNSYM)
		res = "DYNSYM";
	else if (type == SHT_INIT_ARRAY)
		res = "INIT_ARRAY";
	else if (type == SHT_FINI_ARRAY)
		res = "FINI_ARRAY";
	else if (type == SHT_PREINIT_ARRAY)
		res = "PREINIT_ARRAY";
	else if (type == SHT_GROUP)
		res = "GROUP";
	else if (type == SHT_SYMTAB_SHNDX)
		res = "SYMTAB_SHNDX";
	else if (type == SHT_NUM)
		res = "NUM";
	else if (type == SHT_SUNW_CAPCHAIN)
		res = "SUNW_CAPCHAIN";
	else if (type == SHT_SUNW_CAPINFO)
		res = "SUNW_CAPINFO";
	else if (type == SHT_SUNW_SYMSORT)
		res = "SUNW_SYMSORT";
	else if (type == SHT_SUNW_TLSSORT)
		res = "SUNW_TLSSORT";
	else if (type == SHT_SUNW_LDYNSYM)
		res = "SUNW_LDYNSYM";
	else if (type == SHT_SUNW_DOF)
		res = "SUNW_DOF";
	else if (type == SHT_SUNW_CAP)
		res = "SUNW_CAP";
	else if (type == SHT_SUNW_SIGNATURE)
		res = "SUNW_SIGNATURE";
	else if (type == SHT_SUNW_ANNOTATE)
		res = "SUNW_ANNOTATE";
	else if (type == SHT_SUNW_DEBUGSTR)
		res = "SUNW_DEBUGSTR";
	else if (type == SHT_SUNW_DEBUG)
		res = "SUNW_DEBUG";
	else if (type == SHT_SUNW_MOVE)
		res = "SUNW_MOVE";
	else if (type == SHT_SUNW_COMDAT)
		res = "SUNW_COMDAT";
	else if (type == SHT_SUNW_SYMINFO)
		res = "SUNW_SYMINFO";
	else if (type == SHT_SUNW_VERDEF)
		res = "SUNW_VERDEF";
	else if (type == SHT_SUNW_VERNEED)
		res = "SUNW_VERNEED";
	else if (type == SHT_SUNW_VERSYM)
		res = "SUNW_VERSYM";
	else if (type == SHT_SPARC_GOTDATA)
		res = "SPARC_GOTDATA";
	else if (type == SHT_ARM_EXIDX)
		res = "ARM_EXIDX";
	else if (type == SHT_ARM_PREEMPTMAP)
		res = "ARM_PREEMPTMAP";
	else if (type == SHT_ARM_ATTRIBUTES)
		res = "ARM_ATTRIBUTES";
	else
	{
		QString other("%1 <unknown>");
		other = other.arg(type);
		return other;
	}
	return QString(res);
}

const QString getshtypedesc(Elf32_Word type)
{
	const char *res;
	if (type == SHT_NULL)
		res = "��Ч��";
	else if (type == SHT_PROGBITS)
		res = "����Ρ�����Ρ����ݶζ����������͵�";
	else if (type == SHT_SYMTAB)
		res = "��ʾ�öε�����Ϊ���ű�";
	else if (type == SHT_STRTAB)
		res = "��ʾ�öε�����Ϊ�ַ�����";
	else if (type == SHT_RELA)
		res = "�ض�λ���öΰ������ض�λ��Ϣ������ο�����̬��ַ������ض�λ�� ��һ��";
	else if (type == SHT_HASH)
		res = "���ű�Ĺ�ϣ��";
	else if (type == SHT_DYNAMIC)
		res = "��̬������Ϣ";
	else if (type == SHT_NOTE)
		res = "��ʾ����Ϣ";
	else if (type == SHT_NOBITS)
		res = "��ʾ�ö����ļ���û���ݣ�����.bss��";
	else if (type == SHT_REL)
		res = "�öΰ������ض�λ��Ϣ";
	else if (type == SHT_SHLIB)
		res = "����";
	else if (type == SHT_DYNSYM)
		res = "��̬���ӵķ��ű�";
	else if (type == SHT_INIT_ARRAY)
		res = "INIT_ARRAY";
	else if (type == SHT_FINI_ARRAY)
		res = "FINI_ARRAY";
	else if (type == SHT_PREINIT_ARRAY)
		res = "PREINIT_ARRAY";
	else if (type == SHT_GROUP)
		res = "GROUP";
	else if (type == SHT_SYMTAB_SHNDX)
		res = "SYMTAB_SHNDX";
	else if (type == SHT_NUM)
		res = "NUM";
	else if (type == SHT_SUNW_CAPCHAIN)
		res = "SUNW_CAPCHAIN";
	else if (type == SHT_SUNW_CAPINFO)
		res = "SUNW_CAPINFO";
	else if (type == SHT_SUNW_SYMSORT)
		res = "SUNW_SYMSORT";
	else if (type == SHT_SUNW_TLSSORT)
		res = "SUNW_TLSSORT";
	else if (type == SHT_SUNW_LDYNSYM)
		res = "SUNW_LDYNSYM";
	else if (type == SHT_SUNW_DOF)
		res = "SUNW_DOF";
	else if (type == SHT_SUNW_CAP)
		res = "SUNW_CAP";
	else if (type == SHT_SUNW_SIGNATURE)
		res = "SUNW_SIGNATURE";
	else if (type == SHT_SUNW_ANNOTATE)
		res = "SUNW_ANNOTATE";
	else if (type == SHT_SUNW_DEBUGSTR)
		res = "SUNW_DEBUGSTR";
	else if (type == SHT_SUNW_DEBUG)
		res = "SUNW_DEBUG";
	else if (type == SHT_SUNW_MOVE)
		res = "SUNW_MOVE";
	else if (type == SHT_SUNW_COMDAT)
		res = "SUNW_COMDAT";
	else if (type == SHT_SUNW_SYMINFO)
		res = "SUNW_SYMINFO";
	else if (type == SHT_SUNW_VERDEF)
		res = "SUNW_VERDEF";
	else if (type == SHT_SUNW_VERNEED)
		res = "SUNW_VERNEED";
	else if (type == SHT_SUNW_VERSYM)
		res = "SUNW_VERSYM";
	else if (type == SHT_SPARC_GOTDATA)
		res = "SPARC_GOTDATA";
	else if (type == SHT_ARM_EXIDX)
		res = "ARM_EXIDX";
	else if (type == SHT_ARM_PREEMPTMAP)
		res = "ARM_PREEMPTMAP";
	else if (type == SHT_ARM_ATTRIBUTES)
		res = "ARM_ATTRIBUTES";
	else
	{
		QString other("%1 <unknown>");
		other = other.arg(type);
		return other;
	}
	return QString::fromLocal8Bit(res);
}

const QString getshflag(Elf32_Word sh_flags)
{
	char flagbuf[20];
	char *cp = flagbuf;
	if (sh_flags & SHF_WRITE)
		*cp++ = 'W';
	if (sh_flags & SHF_ALLOC)
		*cp++ = 'A';
	if (sh_flags & SHF_EXECINSTR)
		*cp++ = 'X';
	if (sh_flags & SHF_MERGE)
		*cp++ = 'M';
	if (sh_flags & SHF_STRINGS)
		*cp++ = 'S';
	if (sh_flags & SHF_INFO_LINK)
		*cp++ = 'I';
	if (sh_flags & SHF_LINK_ORDER)
		*cp++ = 'L';
	if (sh_flags & SHF_OS_NONCONFORMING)
		*cp++ = 'N';
	if (sh_flags & SHF_GROUP)
		*cp++ = 'G';
	if (sh_flags & SHF_TLS)
		*cp++ = 'T';
	if (sh_flags & SHF_ORDERED)
		*cp++ = 'O';
	if (sh_flags & SHF_EXCLUDE)
		*cp++ = 'E';
	*cp = '\0';
	return QString::fromLocal8Bit(flagbuf);
}
