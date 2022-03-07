#include <stdio.h>
#include "local.h"
#include <time.h>

#include"MiniProject_ERP_struct_warehousing.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

void Create_File(void)
{
	// 입고테이블 서버에 생성
	_create("In_WareHouse", "name_warehouse VARCHAR(20) num_warehouse INT name_item VARCHAR(20) num_item INT date INT name_responsible VARCHAR(20) num_responsible INT num_in INT bill INT pay_in INT tax INT pay_sum INT");

	// 발주테이블 서버에 생성
	_create("Buy_item", "num_BuyList INT name_item VARCHAR(20) num_item INT date INT name_responsible VARCHAR(20) num_responsible INT num_buy INT bill INT pay_in INT tax INT pay_sum INT rest_num_in INT");
	
	// 거래처테이블 서버에 생성
	_create("Buy_company", "name_buy_company VARCHAR(20) num_buy_company INT");
	
	// 담당자테이블 서버에 생성
	_create("Person_responsibe", "name_responsible VARCHAR(20) num_responsible INT");
	
	// 품목테이블 서버에 생성
	_create("item", "name_item VARCHAR(20) num_item INT");
	
	// 참고테이블 서버에 생성
	_create("WareHouse", "name_warehouse VARCHAR(30) num_warehouse INT");
}

void Init_SampleData(void)
{
	// 입고테이블 샘플데이터 삽입
	if (initalizing("D:\\1_IoT\\Server_test\\test\\In_WareHouse") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'Warehouse1', 1999, 'SampleItem1', 19999, 20220304, 'SamplePerson1', 199, 99, 100, 0, 0, 0") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	/*print_data();
	printf("\n");
	*/
	file_column_free();


	// 발주테이블 샘플데이터 삽입
	if (initalizing("D:\\1_IoT\\Server_test\\test\\Buy_item") == -1) 
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("1, 'SampleItem1', 19999, 20220304, 'SamplePerson1', 199, 100, 1000, 10000, 1000, 11000, 100") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	if (_insert("2, 'SampleItem2', 29999, 20220304, 'SamplePerson2', 299, 200, 2000, 40000, 4000, 44000, 100") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	if (_insert("3, 'SampleItem3', 39999, 20220304, 'SamplePerson1', 199, 300, 3000, 90000, 9000, 99000, 100") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	/*print_data();
	printf("\n");
	file_column_free();
	*/
	file_column_free();


	// 거래처테이블 샘플데이터 삽입
	if (initalizing("D:\\1_IoT\\Server_test\\test\\Buy_company") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'Buyer1', 199999") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	//print_data();
	//printf("\n");
	file_column_free();



	// 담당자테이블 샘플데이터 삽입
	if (initalizing("D:\\1_IoT\\Server_test\\test\\Person_responsibe") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'SamplePerson1', 199") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'SamplePerson2', 299") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	/*print_data();
	printf("\n");
	*/
	file_column_free();
	

	// 품목테이블 샘플데이터 삽입
	if (initalizing("D:\\1_IoT\\Server_test\\test\\item") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'SampleItem1', 19999") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'SampleItem2', 29999") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'SampleItem3', 39999") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	/*print_data();
	printf("\n");
	*/
	file_column_free();

	// 창고테이블 샘플데이터 삽입
	if (initalizing("D:\\1_IoT\\Server_test\\test\\WareHouse") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'Warehouse1', 1999 ") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'Warehouse2', 2999 ") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'Warehouse3', 3999 ") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	//print_data();
	//printf("\n");
	file_column_free();
}