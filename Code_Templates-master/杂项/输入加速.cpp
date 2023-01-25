//������������
template <class T>
inline void scan_d(T &ret) {
	char c; ret=0;
	while((c=getchar())<'0'||c>'9');
	while(c>='0'&&c<='9') ret=ret*10+(c-'0'),c=getchar();
}
 

//��������������
template <class T>
inline bool scan_d(T &ret) {
   char c; int sgn;
   if(c=getchar(),c==EOF) return 0; //EOF
   while(c!='-'&&(c<'0'||c>'9')) c=getchar();
   sgn=(c=='-')?-1:1;
   ret=(c=='-')?0:(c-'0');
   while(c=getchar(),c>='0'&&c<='9') ret=ret*10+(c-'0');
   ret*=sgn;
   return 1;
}
 

//������������,(int,long long,float,double)
template <class T>
bool scan_d(T &ret){
	char c; int sgn; T bit=0.1;
	if(c=getchar(),c==EOF) return 0;
	while(c!='-'&&c!='.'&&(c<'0'||c>'9')) c=getchar();
	sgn=(c=='-')?-1:1;
	ret=(c=='-')?0:(c-'0');
	while(c=getchar(),c>='0'&&c<='9') ret=ret*10+(c-'0');
	if(c==' '||c=='\n'){ ret*=sgn; return 1; }
	while(c=getchar(),c>='0'&&c<='9') ret+=(c-'0')*bit,bit/=10;
	ret*=sgn;
	return 1;
}



// ���������

#define MAXN 100100
int a[MAXN];
char line[3000010];

void get() {
    int idx = 0, t = 0, s = 0;
    getchar();
    gets(line);

    while (line[idx]) {
        if (line[idx] >= '0' && line[idx] <= '9') {
            s = s * 10 + line[idx] - '0';
        }
        else {
            a[t++] = s;
            s = 0;
        }
        ++idx;
    }
    if (s) {
        a[t++] = s;
    }
}
