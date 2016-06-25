#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <malloc.h>
#include <locale>
using namespace std;


#define NELEM 1000
#define RED 0
#define BLACK 1
int min_friend = 10000;
int max_friend = 0;
int min_word = 10000;
int max_word = 0;

//red black tree 구현
struct node
{
string key;
node *parent;
int color;
int friendnum = 0;
node *left;
node *right;
node *next;

};
class RBtree
{
node *root;
node *q;
public:
RBtree()
{
q = NULL;
root = NULL;
}
void insert_i(string id);
void insertfix(node *);
void leftrotate(node *);
void rightrotate(node *);
void del(string id);
node* successor(node *);
void delfix(node *);
void search(string id);


};

void RBtree::insert_i(string id)
{
node *p, *q;
node *t = new node;
t->key = id;
t->left = NULL;
t->right = NULL;
t->color = RED;
p = root;
q = NULL;
if (root == NULL)
{
root = t;
t->parent = NULL;
}
else
{
while (p != NULL)
{
q = p;
if (p->key<t->key)
p = p->right;
else
p = p->left;
}
t->parent = q;
if (q->key<t->key)
q->right = t;
else
q->left = t;
}
insertfix(t);
}

void RBtree::insertfix(node *t)
{
node *u;
if (root == t)
{
t->color = BLACK;
return ;
}
while (t->parent != NULL&&t->parent->color == RED)
{
node *g = t->parent->parent;
if (g->left == t->parent)
{
if (g->right != NULL)
{
u = g->right;
if (u->color == RED)
{
t->parent->color = BLACK;
u->color = BLACK;
g->color = RED;
t = g;
}
}
else
{
if (t->parent->right == t)
{
t = t->parent;
leftrotate(t);
}
t->parent->color = BLACK;
g->color = RED;
rightrotate(g);
}
}
else
{
if (g->left != NULL)
{
u = g->left;
if (u->color == RED)
{
t->parent->color = BLACK;
u->color = BLACK;
g->color = RED;
t = g;
}
}
else
{
if (t->parent->left == t)
{
t = t->parent;
rightrotate(t);
}
t->parent->color = BLACK;
g->color = RED;
leftrotate(g);
}
}
root->color = BLACK;
}
}
void RBtree::leftrotate(node *p)
{
if (p->right == NULL)
return;
else
{
node *y = p->right;
if (y->left != NULL)
{
p->right = y->left;
y->left->parent = p;
}
else p->right = NULL;
if (p->parent != NULL)
y->parent = p->parent;
if (p->parent == NULL)
root = y;
else
{
if (p == p->parent->left)
p->parent->left = y;
else
p->parent->right = y;
}
if (p->parent != NULL)
{
y->left = p;
p->parent = y;
}
}
}

void RBtree::rightrotate(node *p)
{
if (p->left == NULL)
return;
else
{
node *y = p->left;
if (y->right != NULL)
{
p->left = y->right;
y->right->parent = p;
}
else
p->left = NULL;
if (p->parent != NULL)
y->parent = p->parent;
if (p->parent == NULL)
root = y;
else
{
if (p == p->parent->left)
p->parent->left = y;
else
p->parent->right = y;
}
if (p->parent != NULL) {
y->right = p;
p->parent = y;
}
}
}

node* RBtree::successor(node *p)
{
node *y = NULL;
if (p->left != NULL)
{
y = p->left;
while (y->right != NULL)
y = y->right;
}
else
{
y = p->right;
while (y->left != NULL)
y = y->left;
}
return y;
}

void RBtree::search(string id)
{	string x;
x = id;
node *p = root;
int found = 0;
while (p != NULL&& found == 0)
{
if (p->key == x)
found = 1;
if (found == 0)
{
if (p->key<x)
p = p->right;
else
p = p->left;
}
}
if(p!=NULL) p->friendnum++;

}



void RBtree::del(string id)
{
	string x;
	x = id;
node *p;
p = root;
node *y = NULL;
node *q = NULL;
int found = 0;
while (p != NULL&&found == 0)
{
if (p->key == x)
found = 1;
if (found == 0)
{
if (p->key<x)
p = p->right;
else
p = p->left;
}
}

if (p->left == NULL || p->right == NULL)
y = p;
else
y = successor(p);
if (y->left != NULL)
q = y->left;
else
{
if (y->right != NULL)
q = y->right;
else
q = NULL;
}
if (q != NULL)
q->parent = y->parent;
if (y->parent == NULL)
root = q;
else
{
if (y == y->parent->left)
y->parent->left = q;
else
y->parent->right = q;
}
if (y != p)
{
p->color = y->color;
p->key = y->key;
}
if (y->color == BLACK)
delfix(q);
}

void RBtree::delfix(node *p)
{
node *s;
while (p != root&&p->color == BLACK)
{
if (p->parent->left == p)
{
s = p->parent->right;
if (s->color == RED)
{
s->color = BLACK;
p->parent->color = RED;
leftrotate(p->parent);
s = p->parent->right;
}
if (s->right->color == BLACK&&s->left->color == BLACK)
{
s->color = RED;
p = p->parent;
}
else
{
if (s->right->color == BLACK)
{
s->left->color == BLACK;
s->color = RED;
rightrotate(s);
s = p->parent->right;
}
s->color = p->parent->color;
p->parent->color = BLACK;
s->right->color = BLACK;
leftrotate(p->parent);
p = root;
}
}
else
{
s = p->parent->left;
if (s->color == RED)
{
s->color = BLACK;
p->parent->color = RED;
rightrotate(p->parent);
s = p->parent->left;
}
if (s->left->color == BLACK&&s->right->color == BLACK)
{
s->color = RED;
p = p->parent;
}
else
{
if (s->left->color == BLACK)
{
s->right->color = BLACK;
s->color = RED;
leftrotate(s);
s = p->parent->left;
}
s->color = p->parent->color;
p->parent->color = BLACK;
s->left->color = BLACK;
rightrotate(p->parent);
p = root;
}
}
p->color = BLACK;
root->color = BLACK;
}
}

///////////////////////////////////////////////////////////////////////////////////////

int main() {

	int Total_users = 0;
	int Total_friendship_records = 0;
	int Total_tweets = 0;
	int top1 = 0;
	int top2 = 0;
	int top3 = 0;
	int top4 = 0;
	int top5 = 0;
	string top1id;
	string top2id;
	string top3id;
	string top4id;
	string top5id;

	string id;
	string id2;
	string date;
	string name;
	string word;
	string trash;
	ifstream input;
	string ID[NELEM] = {};
	string WORD[NELEM] = {};
	string mostID[NELEM] = {};
	int WNUM[NELEM] ;
	int FNUM[NELEM];
	int WCOUNT[NELEM];
	int IDCOUNT[NELEM];
	input.open("user.txt");
	while (input.is_open())
			 {		 getline(input, id);
					 getline(input, date);
					 getline(input, name);
					 getline(input, trash);//enter 받기
					 if (id.size() == 0) break;
					 else {
						 Total_users++;
						 ID[Total_users]=id;
						 //obj.insert_i(id);

					}
			}
	input.close(); 
	
	for (int i = 0; i < NELEM; i++) { WNUM[i] = 0; FNUM[i] = 0; WCOUNT[i] = 0; IDCOUNT[i] = 0;}
	int wordflag ;
	int idflag;
	int idsize=0;
	int wordsize = 0;

	input.open("word.txt");
	while (input.is_open()) {
		wordflag = 0;
		idflag = 0;
		getline(input, id);
		getline(input, date);
		getline(input, word);
		getline(input, trash);//enter 받기
		if (id.size() == 0) break;
		else {
			Total_tweets++;

			for (int i = 0; i < idsize; i++) {			if(mostID[i]==id) { IDCOUNT[i]++; idflag = 1; break; } 	}
			if (idflag == 0) { mostID[idsize] = id; idsize++; }

			for (int i = 0; i < NELEM; i++) { if (ID[i] == id) WNUM[i]++; }
		}
	}
	input.close(); 

	for (int i = 0; i < idsize; i++) {if (IDCOUNT[i] > top1) { top1 = IDCOUNT[i]; top1id = mostID[i]; } }
	for (int i = 0; i < idsize; i++) {
	if (IDCOUNT[i] > top2&&IDCOUNT[i] < top1) { top2 = IDCOUNT[i]; top2id = mostID[i]; }
	}
	for (int i = 0; i < idsize; i++) {
		if (IDCOUNT[i] > top3&&IDCOUNT[i] < top2) { top3 = IDCOUNT[i]; top3id = mostID[i]; }
	}
	for (int i = 0; i < idsize; i++) {
		if (IDCOUNT[i] > top4&&IDCOUNT[i] < top3) { top4 = IDCOUNT[i]; top4id = mostID[i]; }
	}
	for (int i = 0; i < idsize; i++) {
		if (IDCOUNT[i] > top5&&IDCOUNT[i] < top4) { top5 = IDCOUNT[i]; top5id = mostID[i]; }
	}

	input.open("word.txt");
	while (input.is_open()) {
		getline(input, id);
		getline(input, date);
		getline(input, word);
		getline(input, trash);//enter 받기
		if (id.size() == 0) break;
		else {
			 for (int i = 0; i < NELEM; i++)
			{
				if (ID[i] == id) {
					if (WNUM[i] < min_word) min_word = WNUM[i];
					if (WNUM[i] > max_word) max_word = WNUM[i];
				}
			}		
		}
	}
	input.close();


	input.open("friend.txt");
	while (input.is_open()) {
		getline(input, id);
		getline(input, id2);
		getline(input, trash);//enter 받기
		if (id.size() == 0) break;
		else {
			Total_friendship_records++;
			for (int i = 0; i < NELEM; i++)
			{
				if (ID[i] == id) FNUM[i]++;
			}
		}
	}
	input.close(); 

	input.open("friend.txt");
	while (input.is_open()) {
		getline(input, id);
		getline(input, id2);
		getline(input, trash);//enter 받기
		if (id.size() == 0) break;
		else {
			for (int i = 0; i < NELEM; i++)
			{
				if (ID[i] == id) {
					if (FNUM[i] < min_friend) min_friend = FNUM[i];
					if (FNUM[i] > max_friend) max_friend = FNUM[i];
				};
			}
		}
	}
	input.close();
	

	int menu;
	while (1) {
		printf("0. Read data files \n");
		printf("1. display statistics \n");
		printf("2. Top 5 most tweeted words \n");
		printf("3. Top 5 most tweeted users \n");
		printf("4. Find users who tweeted a word \n");
		printf("5. Find all people who are friends of the above users \n");
		printf("6. Delete all mentions of a word \n");
		printf("7. Delete all users who mentioned a word \n");
		printf("8. Find strongly connected components \n");
		printf("9. Find shortest path from a given user \n");
		printf("99. Quit \n");
		printf("Select Menu: ");
		scanf_s("%d", &menu);
		printf("\n");

		if (menu == 0) {
			printf("Total users : %d \n", Total_users);
			printf("Total friendship records : %d \n", Total_friendship_records);
			printf("Total tweets : %d \n", Total_tweets);
			printf("\n");
		}

		else if (menu == 1) {
			
			printf("\n");
			printf("Average number of friends : %.1f\n", Total_friendship_records*1.00 / Total_users);
			printf("Minimum number of friends : %d \n", min_friend);
			printf("Maximum number of friends : %d \n", max_friend);
			printf("\n");
			printf("Average tweets per user : %.1f\n", Total_tweets*1.00 / Total_users);
			printf("Minimum tweets per user : %d \n", min_word);
			printf("Maximum tweets per user : %d \n", max_word);
			printf("\n");
		}
		else if (menu == 3) {
			printf("\n");
			printf("Top 5 most tweeted users\n");
			cout <<"1: " <<top1id << endl;
			cout << "2: "<< top2id << endl;
			cout << "3: " << top3id << endl;
			cout << "4: " << top4id << endl;
			cout << "5: " << top5id << endl;
			printf("\n");
		}

	}

}