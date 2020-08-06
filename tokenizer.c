#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nelem(s) (sizeof(s)/sizeof(s[0]))
#define nil 0

int
strtoken(char *inp, char **tok, int ntok, char *sep)
{

	char	*savp, *p;
	int	i;


	p = inp;
	for(i = 0; i < ntok; i++) {
		tok[i] = strtok_r(p, sep, &savp);
		if(tok[i] == nil)
			break;
		p = nil;
	}

	return i;
}

int
main()
{
	char	*sep = "/";
	char *tt = "/home/tadiparthi/hari";
	char *str;

	char	*tok[10];
	int	i, ntok, len;

	len = strlen(tt);
	str = malloc(sizeof(len+1));	
	if(!str) {
		printf("no memory\n");
		return;
	}

	memset(str, 0, len+1);
	memmove(str, tt, len);

	ntok = strtoken(str, tok, nelem(tok), sep);

	for(i = 0; i < ntok; i++)
		printf("tok[%d]=%s\n", i, tok[i]);
}
#ifdef __cpluscplus__
void
tokenize_str(const string &str, vector<string> &res, char delim)
{
	istringstream input(str);
	string tok;
	while(getline(input, tok, delim)) {
		res.push_back(tok);
	}
}
#endif
