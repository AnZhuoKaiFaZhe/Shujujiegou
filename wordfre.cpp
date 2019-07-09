#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

struct T_node{
    int cnt, v;
    T_node *next[26];//可以根据树的大小改变
    T_node(){
        cnt = 0, v = 0;
        for(int i = 0; i < 26; i++) next[i] = NULL;
    }
};

struct Tree{
    T_node root;
    void Insert(string str){//插入
        T_node *pre = &root, *now;
        int len = str.length();
        for(int i = 0; i < len; i++){
            int id = str[i]-'a';
            pre->v = pre->v|(1<<id);
            now = pre->next[id];
            if(now == NULL){
                now = new T_node();
                //memset(now, 0, sizeof(T_node));
                pre->next[id] = now;
            }
            pre = now;
        }
        pre->cnt++;
    }

    int  findtree(char *str){//查找
        T_node *pre = &root, *now;
        int len = strlen(str);
        for(int i = 0; i < len; i++){
            int id = str[i]-'a';
            now = pre->next[id];
            if(!now) return 0;
            pre = now;
        }
        return pre->cnt;//树元素的个数
    }

    int lowbit(int x){ return x&(-x); }//取最低位
    void Output_Same(string str, T_node *cur){//一个递归
        if(cur->cnt) cout << str << " " << cur->cnt << endl;
        int v = cur->v;
        while(v){
            int id = lowbit(v);
            v -= id;
            id = log2(id);
            char c = 'a'+id;
            string s = str+c;
            T_node *next = cur->next[id];
            Output_Same(s, next);
        }
    }
    int Find_Same(char *str){//查找以str为前缀的单词
        T_node *pre = &root, *now;
        int len = strlen(str);
        for(int i = 0; i < len; i++){
            int id = str[i]-'a';
            now = pre->next[id];
            if(!now) return 0;
            pre = now;
        }
        Output_Same(str, pre);
    }

    void dealTrie(T_node *T){//删除
        int i;
        if(T == NULL) return;
        for(i=0;i<26;i++)
        {
            if(T->next[i]!=NULL)
                dealTrie(T->next[i]);
        }
        free(T);
    }
};
Tree T;

void to_Lower(char *str){//转化为小写
    int len = strlen(str);
    for(int i = 0; i < len; i++){
        str[i] = tolower(str[i]);
    }
}

int main(){
    char s[100];
    string buf;
    freopen("F:\\codeblocks\\workspace\\Withinlaw.txt", "r", stdin);//文件输入
    while(~scanf("%s", s)){//文件输入  到文件结束时结束
        int len = strlen(s);
        for(int i = 0; i < len; i++){
            if(isalpha(s[i])) s[i] = tolower(s[i]);
            else s[i] = ' ';
        }
        stringstream ss(s);
        while(ss>>buf){
            T.Insert(buf);//建树
        }
    }
    freopen("CON", "r", stdin);//控制台输入
    cout << "输入你要查询的单词:" << endl;
    char str[100];
    while(cin >> str){
        to_Lower(str);
        int cnt = T.findtree(str);
        cout << "你查询的单词出现次数： " << cnt << endl;
        T.Find_Same(str);
        cout << endl;
        cout << "输入你要查询的单词:" << endl;
    }
    return 0;
}
