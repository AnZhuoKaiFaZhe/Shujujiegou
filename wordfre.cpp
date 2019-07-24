#include<iostream>
#include<algorithm>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
#define MAX_LINE 1024
//节点
struct trienode 
{		
		int count;//词频
		trienode *next[26];//26叉树
};
//链表节点
struct node
{
	string str;
	int count;
	node *next;
	node(string str = "", int count=0)
	{
		this->count = count;
		this->str = str;
		next = NULL;
	}
};
node follow[26];

//链表插入
void insert(string str, int count)
	{
		int pos = str[0] - 'a';
		node *p = new node(str, count);
		node *q = &follow[pos]; //将p插在q的下一个位置 所以要找到最后一个大于p的位置 因为可能是个空链表  所以q要从头指针开始
		while (q->next != NULL && ((count < (q->next->count)) || (q->next->count == count && q->next->str<str))) {
			q = q->next;
		}
		if (q->next == NULL) {//插在链尾
			q->next = p;
		}
		else {
			p->next = q->next;
			q->next = p;
		}
	}

int dfs(trienode *p, string str="")
	{
		int count = 0;
		if (p->count)
		{
			count++;
			insert(str, p->count);
		}
		for (int i = 0; i < 26; i++)
		{
			trienode *q = p->next[i];
			if (q == NULL)continue;
				char c = 'a' + i;
				string s = str+c;
				count +=dfs(q, s);
			}
		return count;
	}
int getmaxcount()
{
	int count =0;
	for (int i = 0; i < 26; i++) { if (follow[i].next != NULL)count = max(count, follow[i].next->count); else continue; }
	for (int i = 0; i < 26; i++)
	{
		node *n = follow[i].next;
		if (n != NULL)
		{
			while (n->count == count) {
				cout << n->str << " " ;
				n = n->next;
			}
		}
	}
	return count;
}

void save() 
{
	ofstream ofs;
	ofs.open("5.txt", ios::out);
	for (int i = 0; i < 26; i++) {
		node *p = follow[i].next;
		while (p!=NULL&&p->count) {
			ofs<<p->str<<" "<<p->count<<endl;
			p=p->next;
		}
	}

}

//初始化字典树
trienode *creat()
{
	trienode *p=new trienode;
	for (int i = 0; i < 26; i++) 
	{
		p->next[i] = NULL;
	}
	p->count = 0;
	return p;
}

struct trietree
{
	trienode *root=creat();
	int count;
	trietree() { count = 0; }

	//插入单词
	void insert(string str) 
	{
		int len = str.length();//字符串长度
		trienode *t,*p = root;
		for(int i=0;i<len;i++) 
		{
			int pos = str[i] - 'a';//插入节点位置
			if (p->next[pos] == NULL)
			{
				t=creat();
				p->next[pos] = t;
			}
			p = p->next[pos];//指向下一个节点
		}
		p->count++;
	}

	//计算单词频率
	int calsincount(char *str)
	{
		int len = strlen(str);
		trienode *p = root;
		for (int i = 0; i < len; i++)
		{
			int pos = str[i] - 'a';
			if (p->next[pos] == NULL)			
				return 0;
			p = p->next[pos];
		}
		return p->count;
	}

	//输出具有相同前缀的字母
	void outputsame(string str, trienode *q) {
		if (q->count) cout << str << " " << q->count << endl;
		for(int i=0;i<26;i++){
			char c = 'a' + i;
			string s = str + c;
			trienode *next = q->next[i];
			if (next != NULL)
			{	
				outputsame(s, next);
			}
		}
	}
	int findsame(char *str) {
		trienode *p = root;
		int len = strlen(str);
		for (int i = 0; i < len; i++) {
			int pos = str[i] - 'a';
			p = p->next[pos];
			if (!p) return 0;
		}
		outputsame(str, p);
	}


	//删除字典树
	void deletrie(trienode *n) 
	{
		if (n == NULL)return;
		for (int i = 0; i < 26; i++)
		{
			if(n->next[i])
			deletrie(n->next[i]);
		}
		free(n);
	}
};
trietree tree;

void str_lower(char *str)
{
	for (unsigned int i = 0; i < strlen(str); i++)
	{
		if (isupper(str[i]))
			str[i] = tolower(str[i]);
	}
}
//文章处理
void articledeal()
{
	int articlecount = 0;
	ifstream ifs;//文件输入流
	ifs.open("Withinlaw.txt", ios::in);
	if (!ifs.is_open())
	{
		cerr << "Could not open file" << endl;
		exit(0);

	}

	string line;
	string word;
	while (getline(ifs,line))
	{
		int len = line.length();
		for (int i = 0; i < len; i++)
		{
			if (line[i]>='A'&&line[i]<='Z'||line[i]>='a'&&line[i]<='z')line[i] = tolower(line[i]);
			else line[i] = ' ';				
		}
		istringstream iss(line);//字符串输入流
		while (iss >> word)
		{
			articlecount++;
			tree.insert(word);//插入单词和建树
		}
	}
	int difcount = dfs(tree.root);
	save();
	cout << "本篇一共有 " << articlecount << " 个单词" << endl;
	cout << "不同单词数有 " << difcount << " 个单词" << endl;
	ifs.clear();
	ifs.close();
}

int main()
{
	articledeal();
	cout << endl;
	cout << "1,查找单词词频" << endl;
	cout << "2，查找词频最多" << endl;
	cout << "3,查找相同前缀单词及词频" << endl;
	cout << "4,查看存储数据" << endl;
	int opera;
	cout << "输入你要进行的操作:" << endl;
	while (cin >> opera) 
	{
		char s[100];
		if (opera == 1) //查找单词词频
			{
				cout << "输入你要查询的单词:";
				cin >> s;
				str_lower(s);
				cout << "你查询的单词出现次数有 " << tree.calsincount(s) << " 次" << endl;

			}
		else if (opera == 2) 
		{//查找词频最多
			cout << "词频最多的是："<<endl;
			cout<<getmaxcount();
			cout << " 次"<<endl;
		}
		else if (opera == 3)
		{//查找相同前缀单词及词频
			cout << "输入你要查询的前缀：";
			cin >> s;
			str_lower(s);
			cout << "具有相同前缀的有：" << endl;
			tree.findsame(s);
			cout << endl;
		}
		else if (opera == 4)
		{//查找相同前缀单词及词频
			system("5.txt");//打开txt
		}
		else
		{
			cout << "无效操作" << endl;
		}
		cout << "输入你要进行的操作:" << endl;
	}
	return 0;

}
