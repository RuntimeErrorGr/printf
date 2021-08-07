#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
static int write_stdout(const char *token, int length) {
	int rc;
	int bytes_written = 0;

	do {
		rc = write(1, token + bytes_written, length - bytes_written);
		if (rc < 0)
			return rc;

		bytes_written += rc;
	} while (bytes_written < length);

	return bytes_written;
}

int numberDigits(int no) {
	int digits = 0;
	while(no) {
		digits++;
		no /= 10;
	}
	return digits;
}

char* strrev(char* str) {
	char* p1 = str;
	char* p2 = str + strlen(str) - 1;
	while(p2 > p1) {
		char temp = *p1;
		*p1 = *p2;
		*p2 = temp;
		p1++;
		p2--;
	}
	return str;
}
char* strlwr(char * s) {
    char *t = s;
    while (*t != '\0') {
        if (*t >= 'A' && *t <= 'Z' ) {
            *t = *t + ('a' - 'A');
        }
        t++;
    }
 	return s;
}
char* itoa(int arg, int* len) {
	char* string = calloc(sizeof(char), numberDigits(arg) + 1);
	if(!string) {
		return NULL;
	}
	int i = 0;
	if(arg >= 0) {
		while(arg) {
			int decimal = arg % 10;
			arg /= 10;
			char c = decimal + '0';
			string[i] = c;
			i++;
		}
	}
	else {
		while(arg) {
			int decimal = arg % 10;
			arg /= 10;
			char c = abs(decimal) + '0';
			string[i] = c;
			i++;
		}
	}
	*len += strlen(string);
	return string;
}
char* utoa(unsigned int arg, int* len) {
	char* string = calloc(sizeof(char), numberDigits(arg) * 2);
	if(!string) {
		return NULL;
	}
	int i = 0;
	if(arg >= 0) {
		while(arg) {
			int decimal = arg % 10;
			arg /= 10;
			char c = decimal + '0';
			string[i] = c;
			i++;
		}
	}
	*len += strlen(string);
	return string;
}
char* htoa(int arg, int* len) {
	char* string = calloc(sizeof(char), numberDigits(arg) * 4);
	if(!string) {
		return NULL;
	}
	int i = 0;
	if(arg >= 0) {
		while(arg) {
			int rest = arg % 16;
			if(rest < 10) { 
				string[i] = rest + 48;
				i++;
			}
			else {
				string[i] = rest + 55;
				i++;
			}
			arg /= 16;
		}
	}
	else {
		u_int aux = arg;
		while(aux) {
			int rest = aux % 16;
			if(rest < 10) {
				string[i] = rest + 48;
				i++;
			}
			else {
				string[i] = rest + 55;
				i++;
			}
			aux /= 16;
		}
	}
	*len += strlen(string);
	return string;
}
int iocla_printf(const char *format, ...) {
	char spec = 0;
	int len = 0;
	const char* ptr = format;
	va_list args;
	va_start(args, format);
	while(*ptr != '\0') {
		if(*ptr != '%') {
			write_stdout(ptr, 1);
			ptr++;
			len++;
		}
		else {
			if(*(ptr + 1) == '%') {
				write_stdout(ptr, 1);
				spec++;
				len++;
				ptr++;
			}
			if(*(ptr + 1) == 'd') {
				if(spec == 0) {
					int arg = va_arg(args, int);
					char* string = calloc(sizeof(char), numberDigits(arg));
					if(!string) {
						exit(0);
					}
					if(arg > 0) {
						strcpy(string, itoa(arg, &len));
						write_stdout(strrev(string), strlen(string));
						free(string);
					}
					else {
						char* aux = calloc(sizeof(char), numberDigits(arg)+1);
						if(!string) {
							exit(0);
						}
						aux[0] = '-';
						len++;
						strcat(aux, strrev(itoa(arg, &len)));
						write_stdout(aux, strlen(aux));
						free(aux);
						free(string);
					}
					ptr++;
				}
			}
			if(*(ptr + 1) == 'u') {
				unsigned int arg = va_arg(args, unsigned int);
				char* string = calloc(sizeof(char), numberDigits(arg) * 2);
				if(!string) {
					exit(0);
				}
				strcpy(string, utoa(arg, &len));
				if(arg > 0) {
					write_stdout(strrev(string), strlen(string));
					free(string);
				}
				ptr++;
			}
			if(*(ptr + 1) == 'x') {
				int arg = va_arg(args, int);
				char* string = calloc(sizeof(char), numberDigits(arg) * 4);
				if(!string) {
					exit(0);
				}
				strcpy(string, htoa(arg, &len));
				write_stdout(strlwr(strrev(string)), strlen(string));
				free(string);
				ptr++;
			}	
			if(*(ptr + 1) == 'c') {
				int arg = va_arg(args, int);
				char c = arg;
				write_stdout(&c, 1);
				len++;
				ptr++;
			}
			if(*(ptr + 1) == 's') {
				char* arg = va_arg(args, char*);
				write_stdout(arg, strlen(arg));
				len += strlen(arg);
				ptr++;
			}
			ptr++;
		}
	}

	va_end(args);
	return len;
}
