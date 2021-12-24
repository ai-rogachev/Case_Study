#include <iostream>

void RemoveDups(char* str)
{
	int i = 0;
	int replace_i = 0;

	char unique_char = str[i];
	while (str[i] != '\0')
	{
		if (unique_char != str[++i])
		{
			++replace_i;
			unique_char = str[replace_i] = str[i];
		}
	}
	str[replace_i] = '\0';
}

int main()
{
	char data[] = "AAA BBB AAA";
	RemoveDups(data);
	printf("%s\n", data); // �A B A�

	char data1[] = "ABA BBBAAABAB A";
	RemoveDups(data1);
	printf("%s\n", data1); // �A B A�

	char data2[] = "";
	RemoveDups(data2);
	printf("%s\n", data2); // �A B A�

	char data3[] = "AAA";
	RemoveDups(data3);
	printf("%s\n", data3); // �A B A�

	char data4[] = "BBB AAA";
	RemoveDups(data4);
	printf("%s\n", data4); // �A B A�

	char data5[] = "AAA BCBCB CCC";
	RemoveDups(data5);
	printf("%s\n", data5); // �A B A�

	char data6[] = "ABBBBAA BBB AAA";
	RemoveDups(data6);
	printf("%s\n", data6); // �A B A�

	char data7[] = "ABBBAAA";
	RemoveDups(data7);
	printf("%s\n", data7); // �A B A�

	char data8[] = "AAAAAAAAAAAAAAAAAAA";
	RemoveDups(data8);
	printf("%s\n", data8); // �A B A�

	char data9[] = "\0";
	RemoveDups(data9);
	printf("%s\n", data9); // �A B A�

	return 0;
}