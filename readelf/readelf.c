/* This is a simplefied ELF reader.
 * You can contact me if you find any bugs.
 *
 * Luming Wang<wlm199558@126.com>
 */

#include "kerelf.h"
#include <stdio.h>
/* Overview:
 *   Check whether it is a ELF file.
 *
 * Pre-Condition:
 *   binary must longer than 4 byte.
 *
 * Post-Condition:
 *   Return 0 if `binary` isn't an elf. Otherwise
 * return 1.
 */
int is_elf_format(u_char *binary)
{
        Elf32_Ehdr *ehdr = (Elf32_Ehdr *)binary;
        if (ehdr->e_ident[EI_MAG0] == ELFMAG0 &&
                ehdr->e_ident[EI_MAG1] == ELFMAG1 &&
                ehdr->e_ident[EI_MAG2] == ELFMAG2 &&
                ehdr->e_ident[EI_MAG3] == ELFMAG3) {
                return 1;
        }

        return 0;
}

#define REVERSE_32(x) ((((x)&0xff)<<24)|(((x)&0xff00)<<8)|(((x)&0xff0000)>>8)|(((x)&0xff000000)>>24))
#define REVERSE_16(x) ((((x)&0xff)<<8)|(((x)&0xff00)>>8))

/* Overview:
 *   read an elf format binary file. get ELF's information
 *
 * Pre-Condition:
 *   `binary` can't be NULL and `size` is the size of binary.
 *
 * Post-Condition:
 *   Return 0 if success. Otherwise return < 0.
 *   If success, output address of every section in ELF.
 */

/*
    Exercise 1.2. Please complete func "readelf". 
*/

#ifndef EI_DATA
#define EI_DATA 5
#endif

int readelf(u_char *binary, int size)
{
        Elf32_Ehdr *ehdr = (Elf32_Ehdr *)binary;

        int Nr;

        Elf32_Phdr *phdr = NULL;

        u_char *ptr_ph_table = NULL;
        Elf32_Half ph_entry_count;
        Elf32_Half ph_entry_size;


        // check whether `binary` is a ELF file.
        if (size < 4 || !is_elf_format(binary)) {
                printf("not a standard elf format\n");
                return 0;
        }

        // get section table addr, section header number and section header size.
	if (ehdr -> e_ident[EI_DATA] == 1) {
		ptr_ph_table = binary + ehdr -> e_phoff;
		ph_entry_count = ehdr -> e_phnum;
		ph_entry_size = ehdr -> e_phentsize;
		for (Nr = 0; Nr < ph_entry_count; Nr++) {
			phdr = (Elf32_Phdr*)(ptr_ph_table + Nr * ph_entry_size);
			printf("%d:0x%x,0x%x\n", Nr, phdr -> p_filesz, phdr -> p_memsz);
		}
	} else {
		ptr_ph_table = binary + REVERSE_32(ehdr -> e_phoff);
		ph_entry_count = REVERSE_16(ehdr -> e_phnum);
		ph_entry_size = REVERSE_16(ehdr -> e_phentsize);
		for (Nr = 0; Nr < ph_entry_count; Nr++) {
			phdr = (Elf32_Phdr*)(ptr_ph_table + Nr * ph_entry_size);
			printf("%d:0x%x,0x%x\n", Nr, REVERSE_32(phdr -> p_filesz), REVERSE_32(phdr -> p_memsz));
		}
	}
	//printf("%x,%x\n",REVERSE_32(0x12345678),REVERSE_16(0x1234));
        // for each section header, output section number and section addr. 
        // hint: section number starts at 0.
	//printf("%d",ehdr->e_type);

        return 0;
}

