#include "huffman.h"

char text[10000];
double w[10000];
int temp[100];

int main(void) 
{
	//读取测试字符串
	FILE* fp = NULL;
	fp = fopen("textfile.txt", "r");
	fgets(text, 8000, (FILE*)fp);
	fclose(fp);
	
	//字符串统计
	TextFrequencyAnalysis();

	HuffmanCode HT;
	huffmanCoding(HT, w, 26); //构建哈夫曼树

	Huffman HC;
	HuffCoding(HT, HC, 26); //构建哈夫曼编码

	//将编码结果写入codefile
	int length = strlen(text);
	fp = fopen("codefile.txt", "w");
	for (int i = 0; i < length; i++)
	{
		fputs(HC[text[i] - 'a' + 1], fp);
		fputc(' ', fp);
	}

	return 0;
}