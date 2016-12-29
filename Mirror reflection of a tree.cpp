#include <stdio.h>
#include <iostream>
using namespace std;

#define MAXNODE 1024
char NodeInfoSeq[MAXNODE * 2];
char OutputDump[MAXNODE];
typedef struct fake_bt_node
{
	char info;
	struct fake_bt_node *lc;
	struct fake_bt_node *rc;
} fbtn;
fbtn* nStack[MAXNODE];
fbtn* nQueue[MAXNODE * 2];

fbtn *BuildFakeBinaryTree(int n)
{
	int sp = -1;

	fbtn *root = new fbtn;
	root->info = NodeInfoSeq[0];
	root->lc = NULL;
	root->rc = NULL;

	nStack[++sp] = root;

	for (int i = 2; i < 2 * n; i += 2)
	{

		fbtn *temp = new fbtn;
		temp->info = NodeInfoSeq[i];
		temp->lc = NULL;
		temp->rc = NULL;

		fbtn *curFa = nStack[sp];
		if (curFa->lc == NULL)
			curFa->lc = temp;
		else if (curFa->rc == NULL) 
			curFa->rc = temp;
		else
		{
			while (nStack[sp]->rc != NULL)
				--sp;
			nStack[sp]->rc = temp;
		}
		if (NodeInfoSeq[i + 1] == '0') 
			nStack[++sp] = temp;
	}
	return root;
}

void PrintMirrorImage(fbtn *root)
{
	int qf = 0, qr = -1; 
	int sp = -1;
	int dp = -1; 
	fbtn* head;
	nQueue[++qr] = root; 

	while (qr + 1 != qf)
	{
		head = nQueue[qf++];
		OutputDump[++dp] = head->info;
		
		if (head->lc)
		{
			fbtn *cc = head->lc; 

			while (cc != NULL)
			{
				nStack[++sp] = cc;
				cc = cc->rc;
			}
			while (sp != -1)
				nQueue[++qr] = nStack[sp--];
		}
	}

	for (int i = 0; i <= dp; i++)
	{
		if (OutputDump[i] != '$')
			cout << OutputDump[i] << ' ';
	}
}


void DeleteFakeBinaryTree(fbtn *root)
{
	if (root != NULL)
	{
		DeleteFakeBinaryTree(root->lc);
		DeleteFakeBinaryTree(root->rc);
		delete root;
		root = NULL;
	}
}

int main()
{
	int n, i = 0;
	char c;
	cin >> n;
	getchar(); 
	while ((c = getchar()) != '\n')
	{
		if (c != ' ')
			NodeInfoSeq[i++] = c;
	}
	fbtn *root = BuildFakeBinaryTree(n);
	PrintMirrorImage(root);
	DeleteFakeBinaryTree(root);
	return 0;
}