#include <stdio.h>
#define bool int
#define false 0
#define true 1
//�洢�������ݵĽṹ��
struct Data {
	double x;   				//�������
	double y;   				//���ݼ۸�
};
struct Data data[50];    	//�洢�������ݼ�
int dataNum;             	//������Ŀ
double a, b;             	//���y = a + bx���̵���������
double sumXY;             	//x * y�����
double sumX;              	//x�����
double sumY;              	//y�����
double sumXX;            	//x * x�����

//���ݶ���
bool Inputs() {
	char fname[256];                         //�洢�ļ���
	printf("�����������ݵ��ļ�����");
	scanf("%s", fname);
	printf("\n������ĿdataNum��\n");
	scanf("%d", &dataNum);
	FILE *fp = fopen(fname, "rb");
	if (fp == NULL) {
		printf("���ܴ�������ļ�\n");
		return false;
	}
	for (int i = 0; i < dataNum; i++) {
		fscanf(fp, "%lf,%lf", &data[i].x, &data[i].y);
	}
	fclose(fp);
	return true;
}

//��ʼ��
void Init() {
	a = b = sumXY = sumX = sumY = sumXX = 0;
}

//���Իع�
void LineReg() {
	for (int i = 0; i < dataNum; i++) {
		sumXY += data[i].x*data[i].y;
		sumX += data[i].x;
		sumY += data[i].y;
		sumXX += data[i].x*data[i].x;
	}
	b = (sumXY * dataNum - sumX * sumY) / (sumXX * dataNum - sumX * sumX);
	a = sumY / dataNum - b * sumX / dataNum;
	printf("Y=%.2lfX+%.2lf\n", b, a);
}

//���
void Outputs() {
	double x;
	double y;
	printf("�����뷿�ݵ��������λ��ƽ���ף���");
	scanf("%lf", &x);
	y = a + b * x;
	printf("Ԥ�Ʒ���Ϊ��%.2lfԪ\n", y);
}

int main() {
	if (Inputs() == false) {    //�ж��������������Ƿ�ɹ�
		return 0;
	}
	Init();
	LineReg();
	Outputs();
	system("pause");
	return 0;
}