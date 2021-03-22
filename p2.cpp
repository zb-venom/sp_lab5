#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <time.h>

using namespace std;

string ptr, str, user;
int old_str = - 2, end_str = -2, i = 1, c_tid = 0;
pthread_mutex_t mutex; 	
void *thread(void *arg);

int main(int argc, char *argv[], char *enpv[]) {	
	pthread_mutex_init(&mutex,NULL);
	cout << "[program]:\t\tstart\n[user]:\t\t\tEnter your text (enter ex to start example program): ";
	if (argv[1]) { cout << argv[1] << endl; str = argv[1];}
	else getline(cin, str);	
	if (str == "ex") str = "bbbbbbbbbbbbbb. asdasdasdasda asd asd asd. bbb. aasgdfahgsgdfjhshfkjsd.";
	if (str[str.length()-1] != '.') str.insert(str.length(), 1, '.'); 	
	cout << "[original text]:\t" << str << "\n[user]:\t\t\tDisplay only duplicate triads (y/n): ";
	if (argv[2]) { cout << argv[2] << endl; user = argv[2];}
	else cin >> user;		
	cout << "\n[program]:\t\tDivide the text into parts";
	while (1) {	
		old_str = end_str + 2;
		end_str = str.find('.', end_str + 2) < str.length() - 1 ? str.find('.', end_str + 3) : str.length() - 1;
		c_tid++;
		cout << '.' << flush; sleep(1); 
		if (end_str > str.length() - 2) break;
	}
	old_str = - 2, end_str = -2;
    pthread_t tid[c_tid];  
	for(int j =0; j < c_tid; j++) pthread_create(&tid[j],NULL,thread,NULL);	
	for(int j =0; j < c_tid; j++) pthread_join(tid[j], NULL);	
    pthread_mutex_destroy(&mutex);
    cout << "\n\n[mutex]:\t\tdestroy\n[program]:\t\tend\n";
	return 0;
}

void *thread(void *arg) {
	pthread_mutex_lock(&mutex); 	
	old_str = end_str + 2;
	end_str = str.find('.', end_str + 2) < str.length() - 1 ? str.find('.', end_str + 3) : str.length() - 1;
	ptr = str.substr(old_str, end_str - old_str);
	char p[ptr.length()+1];
	strcpy(p, ptr.c_str());
	cout << "\n\n[program]:\t\tcreate thread " << i << "\n[thread_id]:\t\t" << pthread_self() << "\n[mutex]:\t\tlock\n";	
	i++;
	char u[1];
	strcpy(u, user.c_str());
	pid_t pid = 0;
	int   status;		
	pid = fork();	
	if (pid == 0) execl("p1", "", u, p,  NULL);
	if (pid > 0) {
		cout << "[child_program_pid]:\t" << pid << "\n[program]:\t\t" << p << endl;
		pid = wait(&status);
	}			
    cout << "[mutex]:\t\tunlock";
    pthread_mutex_unlock(&mutex);
	return 0;
}
