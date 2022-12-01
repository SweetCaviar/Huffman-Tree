#include "huffman.h"

char text[10000];
double w[10000];
int temp[100];

int main(void) 
{
	//��ȡ�����ַ���
	FILE* fp = NULL;
	fp = fopen("textfile.txt", "r");
	fgets(text, 8000, (FILE*)fp);
	fclose(fp);
	
	//�ַ���ͳ��
	TextFrequencyAnalysis();

	HuffmanCode HT;
	huffmanCoding(HT, w, 26); //������������

	Huffman HC;
	HuffCoding(HT, HC, 26); //��������������

	//��������д��codefile
	int length = strlen(text);
	fp = fopen("codefile.txt", "w");
	for (int i = 0; i < length; i++)
	{
		fputs(HC[text[i] - 'a' + 1], fp);
		fputc(' ', fp);
	}

	return 0;
}