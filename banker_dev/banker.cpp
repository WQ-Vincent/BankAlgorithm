#include<cstring>
#include <vector>
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
#define max 30

int Alloc[max][max];  //�ѷ������Դ 
int Avail[max];    //������Դ 
int resc[max];      //��Դ���� 
int Max[max][max];    //��������� 
int Need[max][max];   //����Ҫ��Դ�� 
int resc_size;   //��Դ���� 
int client_num;  //�û������̣������� 
bool isSecure;
bool SecureCheck();//ϵͳ�Ƿ�ȫ
bool SecureDFS(bool *security,int *temp,int k);    //�ݹ麯�� 
vector<int> ans;        //��ȫ����
int sum; //��ȫ���еĸ���
 
void initialize()  //��ʼ�������� 
{

	printf("��Դ������");     //�����Ҫ���� 
	scanf("%d",&resc_size);
	printf("\n������Դ��������\n");
	for (int i = 0; i < resc_size; i++)
	{
		printf("��Դ%d=", i); 
		scanf("%d", &resc[i]);
	}
	printf("\n�û�������");
	scanf("%d", &client_num);
	
	printf("ÿ���û�����Դ���������\n");
	for (int i = 0; i < client_num; i++)
	{
		for (int j = 0; j < resc_size; j++)
		{
			printf("�Ѷ��û�%d������Դ%d������=", i, j);
			scanf("%d", &Alloc[i][j]);
		}
		printf("\n");
	}
	
	printf("�����û�����Դ���������\n");
	for (int i = 0; i < client_num; i++)
	{
		for (int j = 0; j < resc_size; j++)
		{
			printf("�û�%d����Դ%d���������=", i, j);
			scanf("%d", &Max[i][j]);
		}
		printf("\n");
	}
	
	for (int i = 0; i < client_num; i++)   //������������ 
	{
		for (int j = 0; j < resc_size; j++)
		{
			Need[i][j] = Max[i][j] - Alloc[i][j]; 
		}
	}
	for (int j = 0; j < resc_size; j++)
	{
		Avail[j] = resc[j];  
		for (int i = 0; i < client_num; i++)
		{
			Avail[j] -= Alloc[i][j];
		}	
	}
}
bool SecureCheck()
{
	bool security[client_num];        //[i]��ʾ���û�i�ķ����Ƿ�ȫ
	int temp[resc_size];                  //��¼ԭAvail�����ֵ 
	for (int i = 0; i < resc_size; i++)
	{
		temp[i] = Avail[i];
	}
	int k = 0;     //��ȫ���̵ĸ��� 
	return SecureDFS(security,temp,k);    //�ݹ��� 
}
bool SecureDFS(bool *security,int *temp,int k)   //������ȵݹ�����������ӡ��ȫϵ�� 
{
    if(k == client_num){     //�ҵ���һ�ְ�ȫ�����У���ӡ���
	if(sum==0)printf("\n��ȫ��������:\n"); 
        printf("%d:",++sum);      //��ȫ��������һ 
        int i;
        printf("%d",ans[0]);
        for(i=1; i<ans.size(); i++)
        {
            printf("->%d",ans[i]);
        }
        printf("\n");
        return true;
    }   

    int i;
    for(i=0; i<client_num; i++){
        if(!security[i])
        {
            int j;
            bool client_ifsec = true;  
            for(j=0; j<resc_size; j++)
            {
                if(Need[i][j] > temp[j])
                {
                    client_ifsec = false;        //�ý��̲���ȫ 
                }
            }
            if(client_ifsec){        //��i����������Ҫ����ʱ���밲ȫ�Զ��� 
                for(j=0; j<resc_size; j++)
                {
                    temp[j] += Alloc[i][j];    //�黹��Դ 
                }
                security[i] = true;
                ans.push_back(i);
                SecureDFS(security,temp,k+1);     //������һ�� 

                ans.pop_back();       //���ݣ�����i�����������ĸı�ָ� 
                for(j=0; j<resc_size; j++)
                {
                    temp[j] -= Alloc[i][j];
                }
                security[i] = false;
            }
        }
    }
}
bool answerQuest()
{
	int Request[resc_size];
	printf("�����ĸ��û�����Դ����\n");
	int process;
	scanf("%d", &process);
	for (int j = 0; j < resc_size; j++)
	{
		printf("�����û�%d����Դ%d������=", process, j);
		scanf("%d", &Request[j]);
	}

	//����Դ������ܶ����������
	for (int j = 0; j < resc_size; j++)
	{
		if (Request[j] + Alloc[process][j] > Max[process][j]) {
			printf("�û�%d����Դ%d�����󲻺������������������ֵ��", process, j);
			return false;
		}
	}
	//û�д���������󣬵��ǵ�ǰϵͳ���ܻ�û����ô��Դ��������
	for (int j = 0; j < resc_size; j++)
	{
		if (Request[j] > Avail[j])
		{
			printf("ϵͳ��û���㹻����Դ%d�ṩ�û�%d������", j, process);
		}
	}
	//���Է���
	printf("���Է�����Դ\n");
	for (int j = 0; j < resc_size; j++)
	{
		Alloc[process][j] += Request[j];
		Need[process][j] -= Request[j];
	}
	for (int j = 0; j < resc_size; j++)
	{
		Avail[j] -= Request[j];
	}
	if (!SecureCheck()) {//���ϵͳ�����ڰ�ȫ״̬���򱾴η������ϣ��ָ�ԭ������Դ����״̬
		printf("�������ϣ��ָ�ԭ����״̬\n");
		for (int j = 0; j < resc_size; j++)
		{

			Alloc[process][j] -= Request[j];
			Need[process][j] += Request[j];
		}
		for (int j = 0; j < resc_size; j++)
		{
			Avail[j] += Request[j];
		}
		return false;
	}
	return true;

}
void look()     //��ʾĿǰ��Դ������� 
{
	printf("�����Դ����(Max)��\n");
	for (int i = 0; i < client_num; i++)
	{
		for (int j = 0; j < resc_size; j++)
		{
			printf("%d\t", Max[i][j]);
		}
		printf("\n");
	}
	printf("�ѷ�����Դ(Allocation)��\n");
	for (int i = 0; i < client_num; i++)
	{
		for (int j = 0; j < resc_size; j++)
		{
			printf("%d\t", Alloc[i][j]);
		}
		printf("\n");
	}
	printf("Ŀǰ��Դ����(Need)��\n");
	for (int i = 0; i < client_num; i++)
	{
		for (int j = 0; j < resc_size; j++)
		{
			printf("%d\t", Need[i][j]);
		}
		printf("\n");
	}
	printf("������Դ(Resources)��\n");
	for (int j = 0; j < resc_size; j++)
	{
		printf("%d\t", Avail[j]);
	}
	printf("\n");

}
void menu()
{
	printf("\n\n1.�������û�������Դ�ķ��䣿\n");
	printf("2.�鿴��Դ���\n");
	printf("3.�˳�\n");
}
int main()
{
	printf("\n��������м��㷨����Դ����ϵͳ��\n\n");
	printf("1.������ϵͳ�ĳ�ʼ״̬\n\n");
	initialize();
	SecureCheck();  
	if(sum==0) printf("��ǰϵͳ����ȫ��");   //û�в�����ȫ���У�������ǰ���䲻��ȫ 
	int choose;
	while (1)
	{
		menu();
		scanf("%d", &choose);
		switch (choose)
		{
		case 1:
			if (answerQuest())
				printf("����ɹ���");
			else
				printf("����ʧ�ܣ�");
			break;
		case 2:look(); break;
		case 3:
			exit(0);
		}
	}
	return 0;
}

