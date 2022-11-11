#include "ptool.h"

pid_t pid;
pid_t pids[4096];
int sig = SIGTERM;

void proc_error(int type) {
	switch (type){
		case 0:
			printf("[\e[0;35mkillproc\33[m] \033[0;31mcannot find find that process!\33[m\n");
			break;
		case 1:
			printf("[\e[0;35mfindpid\33[m] \033[0;31mcannot find that proccess!\33[m\n");
			break;
		case 2:
			printf("[\e[0;35mstrlen\33[m] \033[0;31mprocess name has to be less than 80 characters.\33[m\n");
			break;
		case 3:
			printf("usage:\n\tkill [name]\n\tfind [name]\n\tlist\33[m\n");
			break;
		case 4:
			printf("[\e[0;35mkillproc\33[m] \033[0;31myou have to be root!\33[m\n");
			break;
	}
}

void listprocs(){
	int num_procs = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
	pid_t pids[num_procs];
	bzero(pids, sizeof(pids));
	proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));

	for(int i=0;i<num_procs;i++){
		if(pids[i]==0) { continue; }

		char proc_path[PROC_PIDPATHINFO_MAXSIZE];
		bzero(proc_path, PROC_PIDPATHINFO_MAXSIZE);
		proc_pidpath(pids[i], proc_path, sizeof(proc_path));

		printf("[\e[0;35m%d\33[m] [\e[0;94m%s\33[m]\n", pids[i], proc_path);
	}
}

pid_t findpid(char* name) {
	int num_procs = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
	pid_t pids[num_procs];
	bzero(pids, sizeof(pids));
	proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));

	for(int i=0;i<num_procs;i++){
		if(pids[i]==0) { continue; }

		char proc_path[PROC_PIDPATHINFO_MAXSIZE];
		bzero(proc_path, PROC_PIDPATHINFO_MAXSIZE);
		proc_pidpath(pids[i], proc_path, sizeof(proc_path));

		if(strcmp(&proc_path[strlen(proc_path)-strlen(name)], name)==0) {
			printf("[\e[0;35m%d\33[m] [\e[0;94m%s\33[m] \033[32mfound\33[m\n", pids[i], &proc_path[strlen(proc_path)-strlen(name)]);
			return pids[i];
		}
	}
	proc_error(1);
	return 2147483647;
}

int killproc(char* name) {
	if(getuid()){
		proc_error(4);
		return 1;
	}

	pid = findpid(name);

	if(pid==2147483647){
		return 1;
	} else {
		proc_terminate(pid, &sig);
		printf("[\e[0;35m%d\33[m] [\e[0;94m%s\33[m] \033[32mterminated with SIGTERM\33[m\n", pid, name);
		return 1;
	}
	return 1;
}