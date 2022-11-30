#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <malloc.h>
#include <string.h>

using namespace std;

typedef struct {
	double weight;
	double parent, lchild, rchild;
}HTNode, *HuffmanCode;

typedef char** Huffman;

void Select(HuffmanCode& HT, int n, int& s1, int& s2);
void huffmanCoding(HuffmanCode& HT, double* w, int n);
void HuffCoding(HuffmanCode& HT, Huffman& HC, int n);


//���±�Ϊ1��i-1�ķ�Χ�ҵ�Ȩֵ��С������ֵ���±꣬����s1��ȨֵС��s2��Ȩֵ
void Select(HuffmanCode& HT, int n, int& s1, int& s2)
{
	int min = - 1;
	//�ҵ�һ����Сֵ
	for (int i = 1; i <= n; i++) //��һ����׼ֵ
	{
		if (HT[i].parent == 0)
		{
			min = i;
			break;
		}
	}
	for (int i = min + 1; i <= n; i++) //�Ƚ�
	{
		if (HT[i].parent == 0 && HT[i].weight < HT[min].weight)
			min = i;
	}
	s1 = min; //��һ����Сֵ��s1
	//�ҵڶ�����Сֵ
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0 && i != s1)
		{
			min = i;
			break;
		}
	}
	for (int i = min + 1; i <= n; i++)
	{
		if (HT[i].parent == 0 && HT[i].weight < HT[min].weight && i != s1)
			min = i;
	}
	s2 = min; //�ڶ�����Сֵ��s2
}

//����
void huffmanCoding(HuffmanCode& HT, double* w, int n)
{
	int m = 2 * n - 1; //���������ܽ����
	HT = (HuffmanCode)malloc((m + 1) * sizeof(HTNode)); //��m+1��HTNode����Ϊ�±�Ϊ0��HTNode���洢����

	for (int i = 1; i <= n; i++)
	{
		HT[i].weight = w[i - 1]; //��Ȩֵ��n��Ҷ�ӽ��
		HT[i].parent = 0;
	}

	for (int i = n + 1; i <= m; i++) //������������
	{
		//ѡ��Ȩֵ��С��s1��s2���������ǵĸ����
		int s1, s2;
		Select(HT, i - 1, s1, s2); //���±�Ϊ1��i-1�ķ�Χ�ҵ�Ȩֵ��С������ֵ���±꣬����s1��ȨֵС��s2��Ȩֵ
		HT[i].weight = HT[s1].weight + HT[s2].weight; //i��Ȩ����s1��s2��Ȩ��֮��
		HT[s1].parent = i; //s1�ĸ�����i
		HT[s2].parent = i; //s2�ĸ�����i
		HT[i].lchild = s1; //������s1
		HT[i].rchild = s2; //�Һ�����s2
	}

	//��ӡ���������и����֮��Ĺ�ϵ
	printf("��������Ϊ:>\n");
	printf("�±�   Ȩֵ     �����   ����   �Һ���\n");
	printf("0                                  \n");
	for (int i = 1; i <= m; i++)
	{
		printf("%-4d   %-6.2lf   %-6d   %-6d   %-6d\n", i,
			HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
	}
	printf("\n");
}


//���ɹ���������
void HuffCoding(HuffmanCode& HT, Huffman& HC, int n)
{
	HC = (Huffman)malloc(sizeof(char*) * (n + 1)); //��n+1���ռ䣬��Ϊ�±�Ϊ0�Ŀռ䲻��
	char* code = (char*)malloc(sizeof(char) * n); //�����ռ䣬�����Ϊn(�ʱ��ǰn-1�����ڴ洢���ݣ����1�����ڴ��'\0')
	code[n - 1] = '\0'; //�����ռ����һ��λ��Ϊ'\0'
	for (int i = 1; i <= n; i++)
	{
		int start = n - 1; //ÿ���������ݵĹ���������֮ǰ���Ƚ�startָ��ָ��'\0'
		int c = i; //���ڽ��еĵ�i�����ݵı���
		int p = HT[c].parent; //�ҵ������ݵĸ����
		while (p) //ֱ�������Ϊ0���������Ϊ�����ʱ��ֹͣ
		{
			if (HT[p].lchild == c) //����ý�����丸�������ӣ������Ϊ0������Ϊ1
				code[--start] = '0';
			else
				code[--start] = '1';
			c = p; //�������Ͻ��б���
			p = HT[c].parent; //c�ĸ����
		}
		HC[i] = (char*)malloc(sizeof(char) * (n - start)); //�������ڴ洢������ڴ�ռ�
		strcpy(HC[i], &code[start]); //�����뿽�����ַ�ָ�������е���Ӧλ��
	}
	free(code); //�ͷŸ����ռ�
}

string text;
double w[1000];

void TextFrequencyAnalysis()
{
	int temp[1000] = {0};
	int length = text.length();
	int i;
	for (i = 0; i < length; i++)
	{
		temp[text[i] - 'a' + 1] ++;
	}
	
	int l = i;
	long sum = 0;
	for (i = 1; i <= 26; i++) sum += temp[i];

	for (i = 1; i <= 26; i++) w[i] = temp[i] / 1.0 / sum;

	for (i = 1; i <= 26; i++) cout << w[i] << endl;
}

int main(void)
{
	cin >> text;
	TextFrequencyAnalysis();
	


	HuffmanCode HT;
	huffmanCoding(HT, w, 26); //������������

	Huffman HC;
	HuffCoding(HT, HC, 26); //��������������

	for (int i = 1; i <= 26; i++) //��ӡ����������
	{
		printf("����%.2lf�ı���Ϊ:%s\n", HT[i].weight, HC[i]);
	}
	free(w);
	return 0;
}