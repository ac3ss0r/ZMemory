 #include <stdio.h>
 
 /* 
 this is an example program written 
 to test hooking, patching and runtime
 injections on android
 */

int getval() {
	return 5;
}

void printvals(char * str, int num) {
	printf("args: %s, %d\n", str, num);
}

int main() {
	printf("Basic loop test");
	getchar();
	for (int i = 0; i < 10; i++) {
		printf("%d ", i);
	}
	printf("\n");
	
	printf("Method call tests");
	getchar();
	printf("retval: %d\n", getval());
	printvals("A test string", 5);
	
	printf("Breakpoints tests");
	getchar();
	#ifdef __aarch64__ 
	asm("BRK 0"); 
	#else 
	asm("BKPT 0"); 
	#endif
	printf("Tests finished.");
	return 0;
}