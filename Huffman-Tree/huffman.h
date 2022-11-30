
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>


typedef struct {
	double weight;
	int parent, lchild, rchild;
}HTNode, * HuffmanCode;

typedef char** Huffman;

extern char text[10000];
extern double w[10000];
extern int temp[100];

void Select(HuffmanCode& HT, int n, int& s1, int& s2);
void huffmanCoding(HuffmanCode& HT, double* w, int n);
void HuffCoding(HuffmanCode& HT, Huffman& HC, int n);
void TextFrequencyAnalysis();
