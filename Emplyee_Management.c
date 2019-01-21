#include <stdio.h>
#include <stdlib.h>

int number;

typedef struct employee {
	char name[10];
	int age;
	int salary;
	char department[20];
} Employee;

void insert(Employee *people, char *word) {
	int i;
	for (i = 0;i < number;i++)
		if (strcmp(people[i].name, "") == 0) break;
	if (i == number)
		printf("Not enough space\n");
	word = strtok(NULL, " ");
	strcpy(people[i].name, word);
	word = strtok(NULL, " ");
	people[i].age = atoi(word);
	word = strtok(NULL, " ");
	people[i].salary = atoi(word);
	word = strtok(NULL, " ");
	strcpy(people[i].department, word);
}

void delete_one(Employee *people, char *word) {
	int i;
	word = strtok(NULL, " ");
	for (i = 0;i < number;i++)
		if (!strcmp(people[i].name, word))
			break;
	if (i == number)
		printf("Nothing to erase\n");
	people[i].name[0] = '\0';
	people[i].age = 0;
	people[i].salary = 0;
	people[i].department[0] = '\0';
}

int find(Employee *people, char *word) {
	int i;
	word = strtok(NULL, " ");
	for (i = 0;i < number;i++)
		if (!strcmp(people[i].name,word))
			return i;
	if (i == number)
		return -1;
}

void inform(Employee *people, char *word) {
	int i;
	int flag = 1;
	word = strtok(NULL, " ");
	for (i = 0;i < number;i++) {
		if (!strcmp(people[i].name, word)) {
			printf("%s ", people[i].name);
			printf("%d ", people[i].age);
			printf("%d ", people[i].salary);
			printf("%s ", people[i].department);
			printf("\n");
			flag = 0;
		}
	}
	if (flag)
		printf("No people found\n");//에러 표시
}

int avgBenefit(Employee *people, char *word) {
	int i;
	int tmp = 0;
	int num = 0;
	word = strtok(NULL, " ");
	for (i = 0;i < number;i++) {
		if (!strcmp(people[i].department, word)) {
			tmp += people[i].salary;
			num++;
		}
	}
	if (num == 0)
		return 0;
	return tmp / num;
}


int main() {
	char input[100];
	char *word;
	Employee *people;
	int flag = 0, i;

	gets(input);
	word = strtok(input, " ");
	if (word == NULL)
		return 0;
	if (strcmp(word, "set") == 0) {
		word = strtok(NULL, " ");
		number = atoi(word);
		people = (Employee*)malloc(sizeof(Employee)*number);
		flag = 1;
	}
	if (!flag)
		return 0;
	for (i = 0;i < number;i++) {
		people[i].name[0]='\0';
		people[i].age = 0;
		people[i].salary = 0;
		people[i].department[0] = '\0';
	}

	while (1) {
		gets(input);
		word = strtok(input, " ");
		if (word == NULL)
			break;
		if (strcmp(word, "insert") == 0)
			insert(people, word);
		else if (strcmp(word, "delete") == 0)
			delete_one(people, word);
		else if (strcmp(word, "find") == 0)
			printf("%d\n", find(people, word));
		else if (strcmp(word, "inform") == 0)
			inform(people, word);
		else if (strcmp(word, "avg") == 0)
			printf("%d\n", avgBenefit(people, word));
	}

	free(people);
	return 0;
}