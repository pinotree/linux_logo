/* Handles arm64 (aarch64)  chips on Linux architecture   */
/* by Vince Weaver <vince@deater.net>        */

/* Heavily based on the util-linux code by Riku Voipio */
/* see sys-utils/lscpu-arm.c */

/* FIXME: */
/* Processor and processor are different */
/* big/little systems might list both? */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>  /* atof */

#include "../sysinfo.h"
#include "../include/generic.h"

/* Currently maxes out at 2 for Big/Little setups? */
#define MAX_IMPLEMENTERS	2
#define MAX_PARTS		2

/* Known Vendors */
static struct vendor_list_type {
	int id;
	char name[20];
} vendor_list[] = {
	{ 0x41,	"ARM"},
	{ 0x42,	"Broadcom"},
	{ 0x43,	"Cavium"},
	{ 0x44,	"DEC"},
	{ 0x48,	"HiSilicon"},
	{ 0x4d, "Motorola"}, /* Freescale? */
	{ 0x4e,	"Nvidia"},
	{ 0x50,	"APM"},
	{ 0x51,	"Qualcomm"},
	{ 0x53,	"Samsung"},
	{ 0x56,	"Marvell"},
	{ 0x61,	"Apple"},
	{ 0x66,	"Faraday"},
	{ 0x69,	"Intel"},
	{ -1,	"Unknown"},
};

static void handle_arm(int part,char *model_string) {

	switch(part) {
		case 0x810:
			strncpy(model_string,"ARM810",7);
			break;
		case 0x920:
			strncpy(model_string,"ARM920",7);
			break;
		case 0x922:
			strncpy(model_string,"ARM922",7);
			break;
		case 0x926:
			strncpy(model_string,"ARM926",7);
			break;
		case 0x940:
			strncpy(model_string,"ARM940",7);
			break;
		case 0x946:
			strncpy(model_string,"ARM946",7);
			break;
		case 0x966:
			strncpy(model_string,"ARM966",7);
			break;
		case 0xa20:
			strncpy(model_string,"ARM1020",8);
			break;
		case 0xa22:
			strncpy(model_string,"ARM1022",8);
			break;
		case 0xa26:
			strncpy(model_string,"ARM1026",8);
			break;
		case 0xb02:
			strncpy(model_string,"ARM11 MPCore",13);
			break;
		case 0xb36:
			strncpy(model_string,"ARM1136",8);
			break;
		case 0xb56:
			strncpy(model_string,"ARM1156",8);
			break;
		case 0xb76:
			strncpy(model_string,"ARM1176",8);
			break;
		case 0xc05:
			strncpy(model_string,"Cortex-A5",10);
			break;
		case 0xc07:
			strncpy(model_string,"Cortex-A7",10);
			break;
		case 0xc08:
			strncpy(model_string,"Cortex-A8",10);
			break;
		case 0xc09:
			strncpy(model_string,"Cortex-A9",10);
			break;
		case 0xc0d:	/* Originally A12 */
			strncpy(model_string,"Cortex-A17",11);
			break;
		case 0xc0e:
			strncpy(model_string,"Cortex-A17",11);
			break;
		case 0xc0f:
			strncpy(model_string,"Cortex-A15",11);
			break;
		case 0xc14:
			strncpy(model_string,"Cortex-R4",10);
			break;
		case 0xc15:
			strncpy(model_string,"Cortex-R5",10);
			break;
		case 0xc17:
			strncpy(model_string,"Cortex-R7",10);
			break;
		case 0xc18:
			strncpy(model_string,"Cortex-R8",10);
			break;
		case 0xc20:
			strncpy(model_string,"Cortex-M0",10);
			break;
		case 0xc21:
			strncpy(model_string,"Cortex-M1",10);
			break;
		case 0xc23:
			strncpy(model_string,"Cortex-M3",10);
			break;
		case 0xc24:
			strncpy(model_string,"Cortex-M4",10);
			break;
		case 0xc27:
			strncpy(model_string,"Cortex-M7",10);
			break;
		case 0xc60:
			strncpy(model_string,"Cortex-M0+",11);
			break;
		case 0xd00:
			strncpy(model_string,"Foundation",11);
			break;
		case 0xd01:
			strncpy(model_string,"Cortex-A32",11);
			break;
		case 0xd03:
			strncpy(model_string,"Cortex-A53",11);
			break;
		case 0xd04:
			strncpy(model_string,"Cortex-A35",11);
			break;
		case 0xd05:
			strncpy(model_string,"Cortex-A55",11);
			break;
		case 0xd07:
			strncpy(model_string,"Cortex-A57",11);
			break;
		case 0xd08:
			strncpy(model_string,"Cortex-A72",11);
			break;
		case 0xd09:
			strncpy(model_string,"Cortex-A73",11);
			break;
		case 0xd0a:
			strncpy(model_string,"Cortex-A75",11);
			break;
		case 0xd0b:
			strncpy(model_string,"Cortex-A76",11);
			break;
		case 0xd0c:
			strncpy(model_string,"Neoverse-N1",12);
			break;
		case 0xd13:
			strncpy(model_string,"Cortex-R52",11);
			break;
		case 0xd20:
			strncpy(model_string,"Cortex-M23",11);
			break;
		case 0xd21:
			strncpy(model_string,"Cortex-M33",11);
			break;
		case 0xd4a:
			strncpy(model_string,"Neoverse-E1",12);
			break;
		default:
			strncpy(model_string,"Unknown",8);
			break;
	}
}

static void handle_broadcom(int part,char *model_string) {

	switch(part) {

		case 0x0f:
			strncpy(model_string,"Brahma B15",11);
			break;
		case 0x100:
			strncpy(model_string,"Brahma B53",11);
			break;
		case 0x516:
			strncpy(model_string,"ThunderX2",11);
			break;
		default:
			strncpy(model_string,"Unknown",8);
			break;
	}
}

static void handle_cavium(int part,char *model_string) {

	switch(part) {
		case 0x0a0:
			strncpy(model_string,"ThunderX",9);
			break;
		case 0x0a1:
			strncpy(model_string,"ThunderX 88XX",14);
			break;
		case 0x0a2:
			strncpy(model_string,"ThunderX 81XX",14);
			break;
		case 0x0a3:
			strncpy(model_string,"ThunderX 83XX",14);
			break;
		case 0x0af:
			strncpy(model_string,"ThunderX2 99XX",15);
			break;
		default:
			strncpy(model_string,"Unknown",8);
			break;
	}
}


static void handle_dec(int part,char *model_string) {

	switch(part) {
		case 0xa10:
			strncpy(model_string,"SA110",6);
			break;
		case 0xa11:
			strncpy(model_string,"SA1100",7);
			break;
		default:
			strncpy(model_string,"Unknown",8);
			break;
	}
}

static void handle_hisilicon(int part,char *model_string) {

	switch(part) {
		case 0xd01:
			strncpy(model_string,"Kunpeng-920",12);
			break;
		default:
			strncpy(model_string,"Unknown",8);
			break;
	}
}

static void handle_nvidia(int part,char *model_string) {

	switch(part) {
		case 0x000:
			strncpy(model_string,"Denver",7);
			break;
		case 0x003:
			strncpy(model_string,"Denver 2",9);
			break;
		default:
			strncpy(model_string,"Unknown",8);
			break;
	}
}

static void handle_apm(int part,char *model_string) {

	switch(part) {
		case 0x000:
			strncpy(model_string,"X-Gene",7);
			break;
		default:
			strncpy(model_string,"Unknown",8);
			break;
	}
}

static void handle_qualcomm(int part,char *model_string) {

	switch(part) {
		case 0x00f:
			strncpy(model_string,"Scorpion",9);
			break;
		case 0x02d:
			strncpy(model_string,"Scorpion",9);
			break;
		case 0x04d:
			strncpy(model_string,"Krait",6);
			break;
		case 0x06f:
			strncpy(model_string,"Krait",6);
			break;
		case 0x201:
			strncpy(model_string,"Kryo",5);
			break;
		case 0x205:
			strncpy(model_string,"Kryo",5);
			break;
		case 0x211:
			strncpy(model_string,"Kryo",5);
			break;
		case 0x800:
			strncpy(model_string,"Falkor V1/Kryo",15);
			break;
		case 0x801:
			strncpy(model_string,"Kryo V2",8);
			break;
		case 0xc00:
			strncpy(model_string,"Falkor",7);
			break;
		case 0xc01:
			strncpy(model_string,"Saphira",8);
			break;
		default:
			strncpy(model_string,"Unknown",8);
			break;
	}
}

static void handle_samsung(int part,char *model_string) {

	switch(part) {
		case 0x001:
			strncpy(model_string,"Exynos-M1",10);
			break;
		default:
			strncpy(model_string,"Unknown",8);
			break;
	}
}

static void handle_marvell(int part,char *model_string) {

	switch(part) {
		case 0x0131:
			strncpy(model_string,"Feroceon 88FR131",17);
			break;
		case 0x0581:
			strncpy(model_string,"PJ4/PJ4b",9);
			break;
		case 0x0584:
			strncpy(model_string,"PJ4B-MP",8);
			break;
		default:
			strncpy(model_string,"Unknown",8);
			break;
	}
}

static void handle_faraday(int part,char *model_string) {

	switch(part) {
		case 0x0526:
			strncpy(model_string,"FA526",6);
			break;
		case 0x0626:
			strncpy(model_string,"FA626",6);
			break;
		default:
			strncpy(model_string,"Unknown",8);
			break;
	}
}

static void handle_intel(int part,char *model_string) {

	switch(part) {
		case 0x200:
			strncpy(model_string,"i80200",7);
			break;
		case 0x210:
			strncpy(model_string,"PXA250A",8);
			break;
		case 0x212:
			strncpy(model_string,"PXA210A",8);
			break;
		case 0x242:
			strncpy(model_string,"i80321-400",11);
			break;
		case 0x243:
			strncpy(model_string,"i80321-600",11);
			break;
		case 0x290:
			strncpy(model_string,"PXA250B/PXA26x",15);
			break;
		case 0x292:
			strncpy(model_string,"PXA210B",8);
			break;
		case 0x2c2:
			strncpy(model_string,"i80321-400-B0",14);
			break;
		case 0x2c3:
			strncpy(model_string,"i80321-600-B0",14);
			break;
		case 0x2d0:
			strncpy(model_string,"PXA250C/PXA255/PXA26x",22);
			break;
		case 0x2d2:
			strncpy(model_string,"PXA210C",8);
			break;
		case 0x411:
			strncpy(model_string,"PXA27x",7);
			break;
		case 0x41c:
			strncpy(model_string,"IPX425-533",11);
			break;
		case 0x41d:
			strncpy(model_string,"IPX425-400",11);
			break;
		case 0x41f:
			strncpy(model_string,"IPX425-266",11);
			break;
		case 0x682:
			strncpy(model_string,"PXA32x",7);
			break;
		case 0x683:
			strncpy(model_string,"PXA930/PXA935",14);
			break;
		case 0x688:
			strncpy(model_string,"PXA30x",7);
			break;
		case 0x689:
			strncpy(model_string,"PXA31x",7);
			break;
		case 0xb11:
			strncpy(model_string,"SA1110",7);
			break;
		case 0xc12:
			strncpy(model_string,"IPX1200",8);
			break;
		default:
			strncpy(model_string,"Unknown",8);
			break;
	}
}


static void implementer_append(int which,char *vendor,char *string) {

	if (which==0) {
		strncpy(string,vendor,BUFSIZ);
	}
	else {
		strncat(string,"/",2);
		strncat(string,vendor,BUFSIZ);
	}
}

int get_cpu_info(struct cpu_info_type *cpu_info) {

	FILE *fff;
	char temp_string[BUFSIZ];
	char vendor_string[BUFSIZ],model_string[BUFSIZ],hardware_string[BUFSIZ];
	int cpu_count=0;
	float bogomips=0.0;
	int implementers[MAX_IMPLEMENTERS]={-1};
	int parts[MAX_PARTS]={-1},parts_vendor[MAX_PARTS]={-1};
	int num_implementers=0,num_parts=0;
	int i,v,temp_value,temp_vendor;

	vendor_string[0]=model_string[0]=hardware_string[0]=0;

	/* We get all of our info here from /proc/cpuinfo */
	if ((fff=fopen(get_cpuinfo_file(),"r") )!=NULL) {

		while ( (fgets(temp_string,BUFSIZ,fff)!=NULL) ) {

			if ( !(strncmp(temp_string,"CPU implementer",15))) {
				strncpy(vendor_string,
					parse_line(temp_string),
					BUFSIZ-1);
				clip_lf(vendor_string,BUFSIZ);

				temp_value=strtol(vendor_string,NULL,16);
				for(i=0;i<num_implementers;i++) {
					if (temp_value==implementers[i]) break;
				}
				if (i==num_implementers) {
					implementers[num_implementers]=temp_value;
					num_implementers++;
				}
			}

			if ( !(strncmp(temp_string,"CPU part",8))) {
				strncpy(vendor_string,
					parse_line(temp_string),
					BUFSIZ-1);
				clip_lf(vendor_string,BUFSIZ);

				temp_value=strtol(vendor_string,NULL,16);
				if (num_implementers==0) {
					temp_vendor=-1;
				}
				else {
					temp_vendor=implementers[num_implementers-1];
				}

				for (i=0;i<num_parts;i++) {
					if ((temp_value==parts[i]) &&
						(temp_vendor=parts_vendor[i])) {
						break;
					}
				}

				if (i==num_parts) {
					parts[num_parts]=temp_value;
					parts_vendor[num_parts]=temp_vendor;
					num_parts++;
				}
			}


			if ( !(strncmp(temp_string,"Hardware",8))) {
				strncpy(model_string,
					parse_line(temp_string),
					BUFSIZ-1);
				clip_lf(model_string,BUFSIZ);
			}

			if ( !(strncmp(temp_string,"cpu",3))) {
				strncpy(model_string,
					parse_line(temp_string),
					BUFSIZ-1);
				clip_lf(model_string,BUFSIZ);
			}

			/* ARM no longer supports bogomips, urgh */
			if ( !(strncmp(temp_string,"bogomips",8)) ||
				!(strncmp(temp_string,"BogoMips",8)) ||
				!(strncmp(temp_string,"BogoMIPS",8))) {

				bogomips+=atof(parse_line(temp_string));
			}

			if ( !(strncmp(temp_string,"processor",9)) ||
				!(strncmp(temp_string,"Processor",9))) {
			  	/* Cheating way to detect number of intel CPUs */

				cpu_count++;
			}

		}
	}

	/* Attempt to Pretty-print as Linux doesn't do this for us */
	/* Based on sys-utils/lscpu-arm.c from the util-linux package */

	/* Make a string with all vendors in it */
	for(i=0;i<num_implementers;i++) {
		v=0;
		while(vendor_list[v].id!=-1) {
			if (implementers[i]==vendor_list[v].id) {
				implementer_append(i,vendor_list[v].name,
							vendor_string);
				break;
			}
			v++;
		}
		if (vendor_list[v].id==-1) {
			implementer_append(i,"Unknown",vendor_string);
		}
	}
	strncpy_truncate(cpu_info->chip_vendor,vendor_string,
				SYSINFO_CHIP_VENDOR_SIZE);


	/* Make a string with all parts in it */
	for(i=0;i<num_parts;i++) {
		switch(parts_vendor[i]) {
			case 0x41: /* ARM */
				handle_arm(parts[i],model_string);
				break;

			case 0x42: /* Broadcom */
				handle_broadcom(parts[i],model_string);
				break;

			case 0x43: /* Cavium */
				handle_cavium(parts[i],model_string);
				break;

			case 0x44: /* DEC */
				handle_dec(parts[i],model_string);
				break;

			case 0x48: /* HiSilicon */
				handle_hisilicon(parts[i],model_string);
				break;

			case 0x4e: /* Nvidia */
				handle_nvidia(parts[i],model_string);
				break;

			case 0x50: /* APM */
				handle_apm(parts[i],model_string);
				break;

			case 0x51: /* Qualcomm */
				handle_qualcomm(parts[i],model_string);
				break;

			case 0x53: /* Samsung */
				handle_samsung(parts[i],model_string);
				break;

			case 0x56: /* Marvell */
				handle_marvell(parts[i],model_string);
				break;

			case 0x66: /* Faraday */
				handle_faraday(parts[i],model_string);
				break;

			case 0x69: /* Intel */
				handle_intel(parts[i],model_string);
				break;

			default:
				break;
		}
	}


	strncpy_truncate(cpu_info->chip_type,model_string,
				SYSINFO_CHIP_TYPE_SIZE);

	cpu_info->num_cpus=cpu_count;
	cpu_info->megahertz=0.0;
	cpu_info->bogomips=bogomips;

	return 0;
}

int get_hardware(char *hardware_string) {

	char temp_string[BUFSIZ];
	FILE *fff;

	if ((fff=fopen(get_cpuinfo_file(),"r") )!=NULL) {

		while ( (fgets(temp_string,BUFSIZ,fff)!=NULL) ) {

			if (!(strncmp(temp_string,"Hardware",8))) {
				strncpy(hardware_string,parse_line(temp_string),
					SYSINFO_HARDWARE_STRING_SIZE);
			}
		}
	}
	return 1;
}

	/* Some architectures might have better ways of detecting RAM size */
long long get_arch_specific_mem_size(void) {
	/* We have no special way of detecting RAM */
	return 0;
}
