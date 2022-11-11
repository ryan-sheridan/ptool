#include "ptool.h"

void listprocs();
void proc_error();
pid_t findpid(char *name);
int killproc(char *name);

int main(int argc, char *argv[]) {
	char name[80];

	if(argc == 1) {
		proc_error(3);
		return 1;
	}

	if(strcmp(argv[1],"kill")==0) {
		if(argc!=3){
			proc_error(3);
			return 1;
		}

		if(strlen(argv[2])>=80) {
			proc_error(2);
			return 1;
		}

		strcpy(name, argv[2]);

		if(!killproc(name)) {
			return 1;
		}

	} else if (strcmp(argv[1],"find")==0) {
		if(argc!=3){
			proc_error(3);
			return 1;
		}

		if(strlen(argv[2])>=80) {
			proc_error(2);
			return 1;
		}

		strcpy(name, argv[2]);

		if(!findpid(name)){
			proc_error(1);
			return 1;
		}

	} else if (strcmp(argv[1],"list")==0) {
		listprocs();
		return 0;
	}
	return 0;
}