// DS exp1.cpp: 定义控制台应用程序的入口点。
//

#include<stdio.h>
#include<stdlib.h>
#define listSize 100

//学生信息结构体
typedef struct student {
	long num;//学号
	char name[20];//姓名
	char gender[10];//性别
	int age;//年龄
	char subject[20];//专业
}STUDENT;

//顺序表结构体
typedef struct list {
	STUDENT stu[listSize];
	int length;
}LIST;

//展示系统菜单
void showMenu() {
	printf("___________________________________________\n");
	printf("  实验一：一个简易的学生信息管理系统\n\n");
	printf("\t【1】建立项目\n");
	printf("\t【2】查询项目\n");
	printf("\t【3】删除项目\n");
	printf("\t【4】增加项目\n");
	printf("\t【5】输入文件\n");
	printf("\t【6】输出文件\n");
	printf("\t【7】退出程序\n");
	printf("                     林诗雨 222017321102082\n");
	printf("___________________________________________\n");
	return;
}

//初始化顺序表
void initList(LIST * L) {
	L->length = 0;
}

//完成学生信息的输入
void  inputInfor(LIST * L, int index) {
	printf("学号(long)：");
	scanf("%d", &L->stu[index].num);
	printf("姓名(char[20])：");
	scanf("%s", L->stu[index].name);
	printf("性别(char[10])：");
	scanf("%s", L->stu[index].gender);
	printf("年龄(int)：");
	scanf("%d", &L->stu[index].age);
	printf("专业(char[20])：");
	scanf("%s", L->stu[index].subject);
}

//创建班级学生信息
void createList(LIST * L, int len) {
	int i;
	for (i = 0;i< len;i++) {
		printf("%d号学生的信息:\n", i + 1);
		inputInfor(L, i);
		L->length++;
	}
}

//向顺序表中插入元素
int  insertList(LIST * L, int pos, STUDENT * stu) {
	int i;
	if (L->length == listSize) {
		printf("顺序表已满,不能插入元素!\n");
		return -1;
	}
	else if (pos<1 || pos>L->length + 1) {
		printf("位置输入错误\n");
		return 0;
	}
	else {
		for (i = L->length;i >= pos;i--) {
			L->stu[i] = L->stu[i - 1];
		}
		L->stu[pos - 1] = *stu;
		L->length++;
		return 1;
	}
}

//在顺序表中删除元素
int  deleteList(LIST * L, int pos, STUDENT * stu) {
	int i;
	if (L->length == 0) {
		printf("顺序表已空,不能删除元素!\n");
		return -1;
	}
	else if (pos<1 || pos>L->length) {
		printf("位置输入错误\n");
		return 0;
	}
	else {
		*stu = L->stu[pos - 1];
		for (i = pos;i<L->length;i++) {
			L->stu[i - 1] = L->stu[i];
		}
		L->length--;
		return 1;
	}
}

//遍历输入顺序表中元素
void traverseList(LIST * L) {
	int i;
	if (0 == L->length) {    //检查顺序表是否为空,不空才能遍历
		printf("顺序表为空!\n");
	}
	else {
		printf("             学号   姓名   性别   年龄   专业 \n");
		for (i = 0;i<L->length;i++) {
			printf("第%d个学生     ", i + 1);
			printf("%-7d%-7s%-7s%-7d%-7s\n", L->stu[i].num, L->stu[i].name, L->stu[i].gender, L->stu[i].age, L->stu[i].subject);
		}
	}
}

//从文件中读取数据
void file_read(LIST * L) {
	FILE * fp0 = fopen("file.txt", "r+");
	int file_len;
	fscanf(fp0, "%d", &file_len);
	for (int i = 0;i < file_len;i++) {
		fscanf(fp0, "%d %s %s %d %s\n", &L->stu[i].num, &L->stu[i].name, &L->stu[i].gender, &L->stu[i].age, &L->stu[i].subject);
		L->length++;
	}
	printf("完成\n");
	fclose(fp0);
}

//写入数据到文件
void file_write(LIST * L) {
	FILE * fp1 = fopen("file.txt", "w+");
	fprintf(fp1, "%d\n", L->length);
	for (int i = 0;i < L->length;i++) {
		fprintf(fp1, "%d %s %s %d %s\n", L->stu[i].num, L->stu[i].name, L->stu[i].gender, L->stu[i].age, L->stu[i].subject);
	}
	printf("完成\n");
	fclose(fp1);
}

//主函数
int main(void)
{
	int choice, len, pos;
	LIST stu_info;
	STUDENT insertElem;
	initList(&stu_info);
	while (true) {
		showMenu();
		printf("输入数字1-7选择功能:");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			printf("输入学生数:");
			scanf("%d", &len);
			createList(&stu_info, len);
			printf("完成\n");
			break;
		case 2:
			printf("___________________________________________\n");
			traverseList(&stu_info);
			printf("___________________________________________\n\n");
			break;
		case 3:
			printf("输入需要删除学生信息位置:");
			scanf("%d", &pos);
			deleteList(&stu_info, pos, &insertElem);
			printf("完成\n");
			break;
		case 4:
			printf("输入需要插入学生信息位置:");
			scanf("%d", &pos);
			printf("输入待插入学生信息:\n");
			printf("学号(long)：");
			scanf("%d", &insertElem.num);
			printf("姓名(char[20])：");
			scanf("%s", insertElem.name);
			printf("性别(char[10])：");
			scanf("%s", &insertElem.gender);
			printf("年龄(int)：");
			scanf("%d", &insertElem.age);
			printf("专业(char[20])：");
			scanf("%s", insertElem.subject);
			insertList(&stu_info, pos, &insertElem);
			printf("完成\n");
			break;
		case 5:
			file_read(&stu_info);
			break;
		case 6:
			file_write(&stu_info);
			break;
		case 7:
			exit(0);
		}
	}
	return 0;
}
