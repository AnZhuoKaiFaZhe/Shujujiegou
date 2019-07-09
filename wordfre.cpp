#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

struct T_node{
    int cnt, v;
    T_node *next[26];//���Ը������Ĵ�С�ı�
    T_node(){
        cnt = 0, v = 0;
        for(int i = 0; i < 26; i++) next[i] = NULL;
    }
};

struct Tree{
    T_node root;
    void Insert(string str){//����
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

    int  findtree(char *str){//����
        T_node *pre = &root, *now;
        int len = strlen(str);
        for(int i = 0; i < len; i++){
            int id = str[i]-'a';
            now = pre->next[id];
            if(!now) return 0;
            pre = now;
        }
        return pre->cnt;//��Ԫ�صĸ���
    }

    int lowbit(int x){ return x&(-x); }//ȡ���λ
    void Output_Same(string str, T_node *cur){//һ���ݹ�
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
    int Find_Same(char *str){//������strΪǰ׺�ĵ���
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

    void dealTrie(T_node *T){//ɾ��
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

void to_Lower(char *str){//ת��ΪСд
    int len = strlen(str);
    for(int i = 0; i < len; i++){
        str[i] = tolower(str[i]);
    }
}

int main(){
    char s[100];
    string buf;
    freopen("F:\\codeblocks\\workspace\\Withinlaw.txt", "r", stdin);//�ļ�����
    while(~scanf("%s", s)){//�ļ�����  ���ļ�����ʱ����
        int len = strlen(s);
        for(int i = 0; i < len; i++){
            if(isalpha(s[i])) s[i] = tolower(s[i]);
            else s[i] = ' ';
        }
        stringstream ss(s);
        while(ss>>buf){
            T.Insert(buf);//����
        }
    }
    freopen("CON", "r", stdin);//����̨����
    cout << "������Ҫ��ѯ�ĵ���:" << endl;
    char str[100];
    while(cin >> str){
        to_Lower(str);
        int cnt = T.findtree(str);
        cout << "���ѯ�ĵ��ʳ��ִ����� " << cnt << endl;
        T.Find_Same(str);
        cout << endl;
        cout << "������Ҫ��ѯ�ĵ���:" << endl;
    }
    return 0;
}
