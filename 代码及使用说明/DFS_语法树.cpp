#include<bits/stdc++.h>
#include"DSJ_�ʷ�����.h"
using namespace std;
const int max_len=11;//max_lenΪ�ڵ��ַ�������󳤶ȣ�����Ϊ11�� 
					 //���˸��ַ�Ϊһ���ڵ��С 
char token[20],token1[40];
char yufa_in[300];//�ʷ������ļ���
char yufa_out[300];
char tree_map[100][1000];	//������ 
FILE *fin,*fout;
set<string>se;
struct node{
	string st;
	vector<node*>son;
	int cnt; 
	node* addSon(string s){
		node* Son=new node();
		Son->st=s;
		son.push_back(Son);
		return Son;
	}
} *Root; 
int program();
int declaration_list(node* fa);
int declaration_stat(node* fa);
int statement_list(node* fa);
int statement(node* fa);
int if_stat(node* fa);
int while_stat(node* fa);
int for_stat(node* fa);
int read_stat(node* fa);
int write_stat(node* fa);
int compound_stat(node* fa);
int expression_stat(node* fa);
int expression(node* fa);
int bool_expr(node* fa);
int additive_expr(node* fa);
int term(node* fa);
int factor(node* fa);
int fun_declaration(node* fa);//
int fun_body(node* fa);//
int main_declaration(node* fa);//
int call_stat(node* fa);//
void out(node* p){
	p->addSon(token1);
}
void draw_line(int x,int y1,int y2){//��y1��y2 ��һ��ֱ�� 
	for(int i=y1+1;i<y2;i++) tree_map[x][i]='-';
} 
void string_out(int x,int y,string s){	//�ַ�������������� 
	int l=y-5;
	int len=s.length();
	int space=(max_len-len)/2;			//ǰ���ո���� 
	for(int i=0;i<space;i++) tree_map[x][l++]=' ';//���ǰ���ո� 
	for(int i=0;i<len;i++)  tree_map[x][l++]=s[i];//����ַ���  
}
void tree_out(int x,int y,node* p){//��(x,y)�����ڵ�p�������� 
	string_out(x,y,p->st);			//��(x,y) ����������ڵ���Ϣ 
	int num=p->son.size();		//��������
	if(num==0) return ;			//Ҷ�ӽڵ㣬���� 
	tree_map[x+1][y]='|';		//������ 
	int len=p->cnt;				//�������
	int pos[num];				//����λ�� 
	pos[0]=y-len*max_len/2+p->son[0]->cnt*max_len/2;//ȷ����һ���ӽڵ��λ�� 
	for(int i=1;i<num;i++){
		pos[i]=pos[i-1]+(p->son[i-1]->cnt+p->son[i]->cnt)/2*11+1;//�����ӽڵ��λ�� 
	}
	draw_line(x+2,pos[0],pos[num-1]);	//�ӵ�һ���ӽڵ㵽���һ�������� 
	for(int i=0;i<num;i++){
		tree_map[x+3][pos[i]]='|';		//������ 
		tree_out(x+4,pos[i],p->son[i]);	//�ݹ黭���� 
	}
	return ;
}

int tree_cnt(node *p){	//ͳ�Ʋ������Խڵ�pΪ������Ҷ�ӽڵ�ĸ��� 
	int nc=p->son.size();
	if(nc==0){
		p->cnt=1;
		return 1;
	} 
	int sum=0;
	for(int i=0;i<nc;i++){
		sum+=tree_cnt(p->son[i]);
	}
	p->cnt=sum;
	return sum;
}
void print_tree(){	//���tree_map����Ϣ 
	for(int i=0;i<100;i++){
		for(int j=0;j<1000;j++){
			if(tree_map==0) fprintf(fout," ");
			else fprintf(fout,"%c",tree_map[i][j]);
		}
		fprintf(fout,"\n");
	}
}
int TESTparse(){
	int es=0;
//	scanf("%s",fileName);
//	fileName="out.txt";
	strcpy(yufa_in,cifa_out);
	if((fin=fopen(yufa_in,"r"))==NULL){
		printf("��%s�ļ�����\n",yufa_in);
		es=10;
	}
	strcpy(yufa_out,"out_yufa_");
	strcat(yufa_out,cifa_in);
	if((fout=fopen(yufa_out,"w"))==NULL){
		printf("��yufa_out�ļ�����\n");
		es=10;
	}
	if(es==0) es=program();
	printf("=====�﷨���������======\n");
	switch(es){
		case 0:printf("�﷨�����ɹ�\n");break;
		case 10:cout<<"�������ļ�ʧ��"<<endl;break;
		case 1:cout<<"ȱ��{!"<<endl;break;
		case 2:cout<<"ȱ��}!"<<endl;break;
		case 3:cout<<"ȱ�ٱ�ʶ��!"<<endl;break;
		case 4:cout<<"ȱ�ٷֺ�!"<<endl;break;
		case 5:cout<<"ȱ��(!" <<endl;break;
		case 6:cout<<"ȱ��)!"<<endl;break;
		case 7:cout<<"ȱ�ٲ�����!"<<endl;break; 
		case 8:cout<<"�ظ����壡"<<endl;break; 
		case 9:cout<<"ȱ��main����"<<endl;break;
		case 11:cout<<"�Ƿ�����,ȱ��fun/main"<<endl;break;
		case 12:cout<<"ʹ��δ����������"<<endl;break; 
		default: cout<<es<<endl; 
	}
	return es;
}

int program(){
	Root=new node();
	Root->st="<programe>";
//	shift(p);
//	fprintf(fout,"<program>\n");
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	if(strcmp(token,"function")&&strcmp(token,"main")){
		return es=11;
	}
	while(strcmp(token,"function")==0){
		
		es=fun_declaration(Root);
		if(es>0) return es;
	}
	if(strcmp(token,"main")){
		return es=9;
	}
	es=main_declaration(Root);
	if(es>0) return es;
	
	return es;
}
int fun_declaration(node* fa){
	node* p=fa->addSon("<fun_decl>");
	out(p);
//	cur->addSon(token1);
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"ID")) return es=3;
	out(p);
//	cur->addSon(token1);
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"(")) return es=5;
	out(p);
//	cur->addSon(token1);
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,")")) return es=5;
	out(p);
//	cur->addSon(token1);
	
	es=fun_body(p);
	if(es>0) return es;
	
	return es;
}
int main_declaration(node* fa){
	node* p=fa->addSon("<main_decl>");
	out(p);
//	cur->addSon(token1);
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"(")) return es=5;
	out(p);
//	cur->addSon(token1);
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,")")) return es=6;
	out(p);
//	cur->addSon(token1);
	es=fun_body(p);
	if(es>0) return es;
	fscanf(fin,"%s %s\n",token,token1);
	
	return es;
	
}
int fun_body(node* fa){
	node* p=fa->addSon("<fun_body>");
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"{")) return es=1;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
	es=declaration_list(p);
	if(es>0) return es;
	es=statement_list(p);
	if(es>0) return es;
	if(strcmp(token,"}")) return es=2;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
	se.clear();//���һ��ʶ����ɵĺ������ڵı��� 
	return es;
}
int declaration_list(node* fa){
	node* p=fa->addSon("<decl_list>");
	int es=0;
	while(strcmp(token,"int")==0){
		es=declaration_stat(p);
		if(es>0) return es;
	}
	return es;
}
int declaration_stat(node* fa){
	node* p=fa->addSon("<decl_stat>");
	int es=0;
	out(p);
	
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	
	if(strcmp(token,"ID")) return es=3;
	if(se.count(token1)) return es=8;
	se.insert(token1);
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	
	if(strcmp(token,";")) return es=4;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	return es; 
}
int statement_list(node* fa){
	node* p=fa->addSon("<stat_list>");
	int es=0;
	while(strcmp(token,"}")){
		es=statement(p);
		if(es>0) return es;
	}
	return es;
}
int statement(node* fa){
	node* p=fa->addSon("<statement>");
	int es=0;
	if(es==0&&strcmp(token,"if")==0) es=if_stat(p);
	if(es==0&&strcmp(token,"while")==0) es=while_stat(p);
	if(es==0&&strcmp(token,"for")==0) es=for_stat(p);
	if(es==0&&strcmp(token,"read")==0) es=read_stat(p);
	if(es==0&&strcmp(token,"write")==0) es=write_stat(p);
	if(es==0&&strcmp(token,"{")==0) es=compound_stat(p);
	if(es==0&&strcmp(token,"call")==0) es=call_stat(p);
	if(es==0&&(strcmp(token,"ID")==0||strcmp(token,"NUM")==0||strcmp(token,"(")==0)) es=expression_stat(p);
	
	return es;
}
int if_stat(node* fa){
	node* p=fa->addSon("<if_stat>");
	int es=0;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	if(strcmp(token,"(")) return es=5;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	es=expression(p);
	if(es>0) return es;
	if(strcmp(token,")")) return es=6;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	es=statement(p);
	if(es>0) return es;

	if(strcmp(token,"else")==0){
		out(p);
		fscanf(fin,"%s %s\n",token,token1);
//		printf("%s %s\n",token,token1);
		es=statement(p);
		return es;
	}
	return es;
}
int while_stat(node* fa){
	node* p=fa->addSon("<whil_stat>");
	int es=0;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	out(p);
	if(strcmp(token,"(")) return es=5;
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	es=expression(p);
	if(es>0) return es;
	out(p);
	if(strcmp(token,")")) return es=6;
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	es=statement(p);
	return es;
}
int for_stat(node* fa){
	node* p=fa->addSon("<for_stat>");
	out(p);
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	out(p);
	if(strcmp(token,"(")) return es=5;
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	es=expression(p);
	if(es>0) return es;
	if(strcmp(token,";")) return es=4;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1); 
	es=expression(p);
	if(es>0) return es;
	if(strcmp(token,";")) return es=4;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	es=expression(p);
	if(es>0) return es;
	if(strcmp(token,")")) return es=6;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	es=statement(p);
	return es;
}
int write_stat(node* fa){
	node* p=fa->addSon("<writ_stat>");
	out(p);
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	es=expression(p);
	if(es>0) return es;
	if(strcmp(token,";")) return es=4;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	return es;
}
int read_stat(node* fa){
	node* p=fa->addSon("<read_stat>");
	out(p);
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	if(strcmp(token,"ID")) return es=3;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	if(strcmp(token,";")) return es=4;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	return es;
}
int compound_stat(node* fa){
	node* p=fa->addSon("<comp_stat>");
	out(p);
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	es=statement_list(p);
	return es;
}
int expression_stat(node* fa){
	node* p=fa->addSon("<expr_stat>");
//	out(p);
	int es=0;
	if(strcmp(token,";")==0){
		out(p);
		fscanf(fin,"%s %s\n",token,token1);
//		printf("%s %s\n",token,token1);
		return es;
	}
	es=expression(p);
	if(es>0) return es;
	if(es==0&&strcmp(token,";")==0){
		out(p);
		fscanf(fin,"%s %s\n",token,token1);
//		printf("%s %s\n",token,token1);
		return es;
	}
	else{
		return es=4;
	}
}
int call_stat(node* fa){
	node* p=fa->addSon("<call_stat>");
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"ID")) return es=3;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"(")) return es=5;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,")")) return es=6;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
	
	return es; 
}
int expression(node* fa){
	node* p=fa->addSon("<expression>");
	int es=0,fileadd;
	char token2[20],token3[40];
	if(strcmp(token,"ID")==0){
		out(p); 
		if(!se.count(token1)) return es=12;
		fileadd=ftell(fin);
		fscanf(fin,"%s %s\n",token2,token3);
//		printf("%s %s\n",token2,token3);...
		if(strcmp(token2,"=")==0){
//			out(p);
//			shift(p+1);
//			fprintf(fout,"%s\n",token2);
			p->addSon(token2);
			
			fscanf(fin,"%s %s\n",token,token1);
			es=bool_expr(p);
			if(es>0) return es;
		}
		else{
			fseek(fin,fileadd,0);
			es=bool_expr(p);
			if(es>0) return es;
		}
	}
	else es=bool_expr(p+1);
	return es;
}
int bool_expr(node* fa){
	node* p=fa->addSon("<bool_expr>");
	int es=0;
	es=additive_expr(p);
	if(es>0) return es;
	if(strcmp(token,">")==0||strcmp(token,">=")==0||strcmp(token,"<")==0||strcmp(token,"<=")==0||strcmp(token,"==")==0||strcmp(token,"!=")==0){
			out(p);
			fscanf(fin,"%s %s\n",token,token1);
//			printf("%s %s\n",token,token1);
			es=additive_expr(p);
			if(es>0) return es;
	}
	return es;
}
int additive_expr(node* fa){
	node* p=fa->addSon("<addi_expr>");
	int es=0;
	es=term(p);
	if(es>0) return es;
	while(strcmp(token,"+")==0||strcmp(token,"-")==0){
		out(p);
		fscanf(fin,"%s %s",token,token1);
//		printf("%s %s\n",token,token1);
		es=term(p);
		if(es>0) return es;
	}
	return es;
}
int term(node*fa){
	node* p=fa->addSon("<term>");
	int es=0;
	es=factor(p);
	if(es>0) return es;
	while(strcmp(token,"*")==0||strcmp(token,"/")==0){
		out(p);
		fscanf(fin,"%s %s\n",token,token1);
//		printf("%s %s\n",token,token1);
		es=factor(p);
		if(es>0) return es;
	}
	return es;
}
int factor(node* fa){
	node* p=fa->addSon("<factor>");
	int es=0;

	if(strcmp(token,"(")==0){
		out(p);
		fscanf(fin,"%s %s\n",token,token1);
//		printf("%s %s\n",token,token1);
		es=expression(p);
		if(es>0) return es;
		if(strcmp(token,")")) return es=6;
		out(p);
		fscanf(fin,"%s %s\n",token,token1);
//		printf("%s %s\n",token,token1);
	}
	else{
		
		if(strcmp(token,"ID")==0||strcmp(token,"NUM")==0){
			out(p);
			fscanf(fin,"%s %s\n",token,token1);
//			printf("%s %s\n",token,token1);
			return es;
		}
		else{
			es=7;
			return es;
		}
	}
	return es;
}

int main()
{
	if(!init()){cout<<"�ʷ���������"<<endl;return 0;}
	int flag=scan();
	if(flag) cout<<"�ʷ������ɹ�"<<endl;
	else cout<<"�ʷ�����ʧ��"<<endl;
	
	int es=0;
	if(flag)  es=TESTparse();
	if(es==0&&flag){
		printf("�﷨�����ɹ�\n");
	}
	else if(flag&&es) printf("�﷨����ʧ��\n");
	memset(tree_map,0,sizeof(tree_map));
	if(es==0&&flag){
		tree_cnt(Root);
		tree_out(0,500,Root);
		print_tree();
	}
	fclose(fin);
	fclose(fout);
	return 0;
 }
