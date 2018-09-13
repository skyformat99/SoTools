#pragma once
#include "elf.h"
#include "qstring.h"
#include "qdebug.h"

using namespace std;
//��Ч��
#define 	SHT_NULL		0
//����Ρ�����Ρ����ݶζ����������͵�
#define 	SHT_PROGBITS	1
//��ʾ�öε�����Ϊ���ű�
#define 	SHT_SYMTAB		2
//��ʾ�öε�����Ϊ�ַ�����
#define 	SHT_STRTAB		3
//�ض�λ���öΰ������ض�λ��Ϣ������ο�����̬��ַ������ض�λ�� ��һ��
#define 	SHT_RELA		4
//���ű�Ĺ�ϣ��
#define 	SHT_HASH		5
//��̬������Ϣ
#define 	SHT_DYNAMIC		6
//��ʾ����Ϣ
#define 	SHT_NOTE		7
//��ʾ�ö����ļ���û���ݣ�����.bss��
#define 	SHT_NOBITS		8
//�öΰ������ض�λ��Ϣ
#define 	SHT_REL			9
//����
#define 	SHT_SHLIB		10
//��̬���ӵķ��ű�
#define 	SHT_DYNSYM		11
#define 	SHT_INIT_ARRAY	14
#define 	SHT_FINI_ARRAY	15
#define 	SHT_PREINIT_ARRAY	16
#define 	SHT_GROUP		17
#define 	SHT_SYMTAB_SHNDX	18
#define 	SHT_NUM			19
#define 	SHT_SUNW_CAPCHAIN 1879048175
#define		SHT_SUNW_CAPINFO  1879048176
#define		SHT_SUNW_SYMSORT  1879048177
#define		SHT_SUNW_TLSSORT  1879048178
#define		SHT_SUNW_LDYNSYM  1879048179
#define		SHT_SUNW_DOF  1879048180
#define		SHT_SUNW_CAP  1879048181
#define		SHT_SUNW_SIGNATURE  1879048182
#define		SHT_SUNW_ANNOTATE  1879048183
#define		SHT_SUNW_DEBUGSTR  1879048184
#define		SHT_SUNW_DEBUG  1879048185
#define		SHT_SUNW_MOVE  1879048186
#define		SHT_SUNW_COMDAT  1879048187
#define		SHT_SUNW_SYMINFO  1879048188
#define		SHT_SUNW_VERDEF  1879048189
#define		SHT_SUNW_VERNEED  1879048190
#define		SHT_SUNW_VERSYM  1879048191
#define		SHT_SPARC_GOTDATA  1879048192
#define		SHT_ARM_EXIDX  1879048193
#define		SHT_ARM_PREEMPTMAP  1879048194
#define		SHT_ARM_ATTRIBUTES  1879048195

// Section Attribute Flags

//The section contains data that should be writable during process execution.
//��ʾ�ö��ڽ��̾����п�д
#define	SHF_WRITE	0x1
//The section occupies memory during process execution. Some control sections do not reside in the memory image of an object file; this attribute is off for those sections.
//��ʾ�ö��ڽ��̾�������Ҫ����ռ䣬��Щ����ָʾ�������Ϣ�Ķβ���Ҫ�ڽ��̿ռ��б�����ռ䣬����һ�㲻���������־�������Ρ����ݶκ�.bss�ζ����������־λ
#define	SHF_ALLOC	0x2
//The section contains executable machine instructions.
//��ʾ�ö��ڽ��̿ռ��п��Ա�ִ�У�һ��ָ�����
#define	SHF_EXECINSTR	0x4
/*
The data in the section may be merged to eliminate duplication. Unless the SHF_STRINGS flag is also set, 
the data elements in the section are of a uniform size. The size of each element is specified in the section header's sh_entsize field. 
If the SHF_STRINGS flag is also set, the data elements consist of null-terminated character strings. 
The size of each character is specified in the section header's sh_entsize field.
Each element in the section is compared against other elements in sections with the same name, 
type and flags. Elements that would have identical values at program run-time may be merged. 
Relocations referencing elements of such sections must be resolved to the merged locations of the referenced values. 
Note that any relocatable values, including values that would result in run-time relocations, 
must be analyzed to determine whether the run-time values would actually be identical. 
An ABI-conforming object file may not depend on specific elements being merged, 
and an ABI-conforming link editor may choose not to merge specific elements.
*/
#define	SHF_MERGE		0x10
/*
The data elements in the section consist of null-terminated character strings. 
The size of each character is specified in the section header's sh_entsize field.
*/
#define	SHF_STRINGS		0x20
//The sh_info field of this section header holds a section header table index.
#define	SHF_INFO_LINK	0x40
/*
This flag adds special ordering requirements for link editors. 
The requirements apply if the sh_link field of this section's header references another section (the linked-to section). 
If this section is combined with other sections in the output file, it must appear in the same relative order with respect to those sections, 
as the linked-to section appears with respect to sections the linked-to section is combined with.
*/
#define	SHF_LINK_ORDER	0x80
/*
This section requires special OS-specific processing (beyond the standard linking rules) to avoid incorrect behavior. 
If this section has either an sh_type value or contains sh_flags bits in the OS-specific ranges for those fields, 
and a link editor processing this section does not recognize those values, 
then the link editor should reject the object file containing this section with an error.
*/
#define	SHF_OS_NONCONFORMING	0x100
/*
This section is a member (perhaps the only one) of a section group. 
The section must be referenced by a section of type SHT_GROUP. 
The SHF_GROUP flag may be set only for sections contained in relocatable objects (objects with the ELF header e_type member set to ET_REL). See below for further details.
*/
#define	SHF_GROUP		0x200
//This section holds Thread-Local Storage, meaning that each separate execution flow has its own distinct instance of this data. Implementations need not support this flag.
#define	SHF_TLS			0x400
//All bits included in this mask are reserved for operating system-specific semantics.
#define	SHF_MASKOS		0x0ff00000
//All bits included in this mask are reserved for processor-specific semantics. If meanings are specified, the processor supplement explains them.
#define	SHF_MASKPROC	0xf0000000
/*
This section requires ordering in relation to other sections of the same type. Ordered sections are combined within the section pointed to by the sh_link entry. The sh_link entry of an ordered section can point to itself.
If the sh_info entry of the ordered section is a valid section within the same input file, the ordered section will be sorted based on the relative ordering within the output file of the section pointed to by the sh_info entry.
The special sh_info values SHN_BEFORE and SHN_AFTER (see Table 7-11) imply that the sorted section is to precede or follow, respectively, all other sections in the set being ordered. Input file link-line order is preserved if multiple sections in an ordered set have one of these special values.
In the absence of the sh_info ordering information, sections from a single input file combined within one section of the output file will be contiguous and have the same relative ordering as they did in the input file. The contributions from multiple input files will appear in link-line order.
*/
#define	SHF_ORDERED		0x40000000
/*
This section is excluded from input to the link-edit of an executable or shared object. This flag is ignored if the SHF_ALLOC flag is also set, or if relocations exist against the section.
*/
#define	SHF_EXCLUDE		0x80000000

//�ε����Ͷ�Ӧ��ϵ
const QString getshtype(Elf32_Word type);

//�ε����Ͷ�Ӧ��ϵ����
const QString getshtypedesc(Elf32_Word type);

/*
	A section header's sh_flags member holds 1-bit flags that describe the section's attributes. Defined values appear in the following table; other values are reserved.
	If a flag bit is set in sh_flags, the attribute is ``on'' for the section. Otherwise, the attribute is ``off'' or does not apply. Undefined attributes are set to zero.
*/
const QString getshflag(Elf32_Word sh_flags);
