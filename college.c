#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int otp();
void design();
struct login
{
	char uname[20];
	char pass[20];
} a;
struct student
{
	int rollno;
	char name[20];
	struct marks
	{
		int a[5];
	} m;
	float perc;
} s[10];
struct record
{
	int roll_no;
	char name[30];
	struct mark
	{
		int marks[3];
	} m;
	float perc;
} r;
void create_account()
{
	system("cls");
	int temp, result;
	design();
	printf("\n\t\t\tCreate account\n");
	design();
	printf("\nEnter the username :");
	fflush(stdin);
	scanf("%s", a.uname);
	printf("\nEnter the password :");
	fflush(stdin);
	scanf("%s", a.pass);
	result = otp();
	printf("\nEnter the OTP : %d\n", result);
	fflush(stdin);
	scanf("%d", &temp);
	if (temp == result)
	{
		FILE *fp;
		fp = fopen("login.dat", "ab");
		fwrite(&a, sizeof(a), 1, fp);
		fclose(fp);
		system("cls");
		design();
		printf("\n\t\t\tThe account create successfully\n");
	}
	else
	{
		printf("\n\t\t\twrong otp\n");
	}
}
int otp()
{
	int result;
	srand(time(0));
	while (1)
	{
		result = rand() % 10000;
		if (result < 10000 && result > 999)
		{
			return result;
			break;
		}
	}
}
void login()
{
	system("cls");
	design();
	printf("\n\t\t\tLogin user\n");
	design();
	FILE *fp;
	int result1, result2, found1 = 0, found2 = 0, j = 1;
	fp = fopen("login.dat", "rb");
	char user[20], pass[20];
	printf("\nEnter the username :");
	fflush(stdin);
	scanf("%s", user);
	printf("\nEnter the password :");
	fflush(stdin);
	scanf("%s", pass);
	while (fread(&a, sizeof(a), 1, fp) > 0 && found1 == 0 && found2 == 0)
	{
		result1 = strcmp(user, a.uname);
		if (result1 == 0)
		{
			found1 = 1;
		}
		result2 = strcmp(pass, a.pass);
		if (result2 == 0)
		{
			found2 = 1;
		}
		if (found1 == 1 && found2 == 1)
		{
			system("cls");
			design();
			printf("\n\t\t\tlogin successfully\n");
		}
		else if (found1 == 1 && found2 != 1)
		{
			j = 0;
		}
	}
	fclose(fp);
	if (j == 0)
	{
		system("cls");
		design();
		printf("\n\t\t\tEnter the right password\n");
	}
}
void design()
{
	int i = 0;
	for (i = 0; i < 67; i++)
		printf("-");
}
void show_user()
{
	system("cls");
	FILE *fp;
	int i;
	fp = fopen("login.dat", "rb");
	design();
	printf("\n\t\t\t\tList\n");
	design();
	printf("No of user\tName\n");
	i = 1;
	while (fread(&a, sizeof(a), 1, fp) > 0)
	{
		printf("%d \t\t%-20s\n", i, a.uname);
		i++;
	}
	fclose(fp);
}
void remove1()
{
	system("cls");
	design();
	printf("\n\t\t\tRemove Account\n");
	design();
	FILE *fp, *fp1;
	char temp[20];
	int found = 0;
	fp = fopen("login.dat", "rb");
	fp1 = fopen("temp.dat", "wb");
	printf("Enter the Username to Remove\n");
	scanf("%s", temp);
	while (fread(&a, sizeof(a), 1, fp) > 0)
	{
		if (strcmp(temp, a.uname) == 0)
		{
			found = 1;
		}
		else
		{
			fwrite(&a, sizeof(a), 1, fp1);
		}
	}
	fclose(fp);
	fclose(fp1);
	if (found == 1)
	{
		fp = fopen("login.dat", "wb");
		fp1 = fopen("temp.dat", "rb");
		while (fread(&a, sizeof(a), 1, fp1) > 0)
		{
			fwrite(&a, sizeof(a), 1, fp);
		}
		fclose(fp);
		fclose(fp1);
		printf("Remove user name successfully\n");
	}
}
void record()
{
	system("cls");
	int n, i, j;
	design();
	printf("\n\t\t\t\tRecord\n");
	design();
	printf("Enter how many student record you want to Enter\n");
	scanf("%d", &n);
	for (j = 0; j < n; j++)
	{
		FILE *fp;
		fp = fopen("record1.dat", "ab");
		fflush(stdin);
		printf("\nEnter the Roll number :");
		scanf("%d", &r.roll_no);
		fflush(stdin);
		printf("\nEnter the Name :");
		scanf("%s", r.name);
		fflush(stdin);
		printf("\nEnter the 3 subject marks\n");
		for (i = 0; i < 3; i++)
		{
			scanf("%d", &r.m.marks[i]);
		}
		for (i = 0; i < 1; i++)
		{
			r.perc = (r.m.marks[i] + r.m.marks[i + 1] + r.m.marks[i + 2]) * 0.33333;
		}
		fwrite(&r, sizeof(r), 1, fp);
		design();
		printf("\n\t\t\t\tdata enter successful\n");
		fclose(fp);
	}
}
void show_data()
{
	system("cls");
	FILE *fp;
	fp = fopen("record1.dat", "rb");
	design();
	printf("\n\t\t\t\tShow user\n");
	design();
	printf("Roll_no\tName\tMaths\tScience\tEnglish\tperc\n");
	while (fread(&r, sizeof(r), 1, fp) > 0)
	{
		printf("%d\t%s\t%d\t%d\t%d\t%0.2f\n", r.roll_no, r.name, r.m.marks[0], r.m.marks[1], r.m.marks[2], r.perc);
	}
	fclose(fp);
}
void search_data()
{
	system("cls");
	design();
	printf("\n\t\t\t\tSearch user\n");
	design();
	char temp[30];
	printf("Enter the name :");
	scanf("%s", temp);
	FILE *fp;
	fp = fopen("record1.dat", "rb");
	printf("Roll_no\tName\tMaths\tScience\tEnglish\tperc\n");
	while (fread(&r, sizeof(r), 1, fp) > 0)
	{
		if (0 == strcmp(temp, r.name))
		{
			printf("%d\t%s\t%d\t%d\t%d\t%0.2f\n", r.roll_no, r.name, r.m.marks[0], r.m.marks[1], r.m.marks[2], r.perc);
		}
	}
	fclose(fp);
}
void remove_data()
{
	system("cls");
	design();
	printf("\n\t\t\tRemove details\n");
	design();
	FILE *fp, *fp1;
	char temp[20];
	int found = 0;
	fp = fopen("record1.dat", "rb");
	fp1 = fopen("temp.dat", "wb");
	printf("Enter the Username to Remove\n");
	scanf("%s", temp);
	while (fread(&r, sizeof(r), 1, fp) > 0)
	{
		if (strcmp(temp, r.name) == 0)
		{
			found = 1;
		}
		else
		{
			fwrite(&r, sizeof(r), 1, fp1);
		}
	}
	fclose(fp);
	fclose(fp1);
	if (found == 1)
	{
		fp = fopen("record1.dat", "wb");
		fp1 = fopen("temp.dat", "rb");
		while (fread(&r, sizeof(r), 1, fp1) > 0)
		{
			fwrite(&r, sizeof(r), 1, fp);
		}
		fclose(fp);
		fclose(fp1);
		printf("Remove user details successfully\n");
	}
}
int main()
{
		system("cls");
	int choice;
	design();
	printf("\n\t\t\tWelcome to Msg college\n");
	do
	{
		design();
	
		printf("\nEnter the choice\n\n");
		printf("1] Create account\n");
		printf("2] login\n");
		printf("3] Show user\n");
		printf("4] Remove account\n");
		printf("5] Add student\n");
		printf("6] Show all student\n");
		printf("7] Search by name\n");
		printf("8] Remove student details\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			create_account();
			break;
		case 2:
			login();
			break;
		case 3:
			show_user();
			break;
		case 4:
			remove1();
			break;
		case 5:
			record();
			break;
		case 6:
			show_data();
			break;
		case 7:
			search_data();
			break;
		case 8:
			remove_data();
			break;
		}

	} while (1);
} 
