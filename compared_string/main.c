#include <stdio.h>
#include <stdlib.h>

int cmpstr(const char* s1, const char* s2);
void strNcpy(char* dst, const char* src, int n);
int stringlen(char* str);
void matchSubString(char* s1, char* s2);

int main(int argc, char *const argv[])
{
	/* char* s1 = "abba"; */
	/* char* s2 = "ababbba abbabbabbabbaacc"; */
	/* for( int i=0; i<argc; i++ ) */
	/* { */
		/* printf("%s\n", argv[i]); */
	/* } */
	char* s1 = (char*)malloc(1000000);
	char* s2 = (char*)malloc(1000000);
	printf("please input your match strings: \n");
	scanf("%[^\n] %[^\n]", s1, s2);
	
	/* printf("%s\n%s", s1, s2); */
	matchSubString(s1, s2);

	free(s1);
	free(s2);
	return 0;

}


/**
 * s1和s2的长度一律小于10000
 * s1的长度必须小于s2, s2为母串, s1为需要查找的子串
 * 如果在s2中找到了s1的存在, 输出s1在s2中的范围下标. 没找到就输出-1
 *
 * */
void matchSubString(char* s1, char* s2)
{
	const int MAX = 10000;
	int len1 = stringlen(s1);
	int len2 = stringlen(s2);
	if( len1 > MAX && len2 > MAX && len1 > len2 ) {
		printf("字符串长度不能大于10000, 或子串长度大于母串\n");
		return;
	}
	if(s1 == NULL && s2 == NULL)
	{
		return;
	}
	if(len1 == len2) 
	{
		printf("%d %d", 0,len1-1);
		return;
	}

	char* temp_str = (char*)malloc(len1+1);
	for( int count=0; count < len2; count++ )
	{

		strNcpy(temp_str, s2+count, len1);
		/* printf("%s - %s\n", temp_str, s1); // a test */
		if( cmpstr(s1, temp_str) == 0 )
		{
		
			printf("%d,%d", count, count+stringlen(temp_str)-1);
			count = count + (len1 - 1);

		}

	}

	free(temp_str);
}

/**
 * the function is to determine if s1 is equal to s2?
 * */
int cmpstr(const char* s1, const char* s2)
{
	unsigned char c1, c2;
	do {
		c1 = (unsigned char)*s1++;
		c2 = (unsigned char)*s2++;
		if ( c1 =='\0' ) 
			return c1 - c2;
	} while( c1 == c2 );
	return c1 - c2;
}


/**
 * @dst: target value
 * @src: origin strings
 * @n: copy *n* characters to dst
 * the function of this function is to copy a certain  number of characters 
 * to another variable.
 * */
void strNcpy(char* dst, const char* src, int n)
{
	for ( int idx=0; idx < n; idx++ )
	{
		*dst++ = *src++;
	}
	*dst++ = '\0';
}


/**
 * @str: str will be calculated
 * the function is to calculate the length of the string.
 * */
int stringlen(char* str)
{
	int count = 0;
	while ( *str++ != '\0' )
	{
		count++;
	}
	return count;
}
