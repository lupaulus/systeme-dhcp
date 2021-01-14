#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	// tab contenant les deux file descriptor
	int pipedes[2];

	// réalisation de la connection entre deux process
	pipe(pipedes);

	//exécution de la première commande	
	if (fork() == 0) {
		close(pipedes[0]);
		dup2(pipedes[1], 1);
		close(pipedes[1]);

        // première partie de la commande ' ps eaux ' 
		execlp ("ps", "ps", "eaux", (void*)0);
		exit(1);
	}
	
	// exécution de la deuxième commande
	if (fork() == 0 ) {
		close(pipedes[1]);
		dup2(pipedes[0], 0);

		// On crée la redirection 
		int fd = open("/dev/null", O_WRONLY);
		dup2(fd, 1);
		// Deuxième partie ' | grep "^root"  '
		execlp ("grep", "grep", "^root", (void*)0);

		exit(1);
	}

	close(pipedes[1]);
	close(pipedes[0]);

	wait(&pipedes[1]);
	wait(&pipedes[0]);

	write(1, "root est connecté\n", 20);
	return 0; 
}