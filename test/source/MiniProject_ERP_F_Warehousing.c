#include <stdio.h>
#include "local.h"
#include <time.h>
#include"MiniProject_ERP_struct_warehousing.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

void Insert_WarehousingData_from_BuyingList(void)	// 발주입고 - 발주정보를 불러와서 입력
{
	result* _result;
	result* find;
	int result_count;
	char Select_WH[10];

	time_t timer;
	struct tm* t;
	timer = time(NULL);
	t = localtime(&timer);

	int today_date = 0;
	today_date = ((t->tm_year + 1900) * 10000) + ((t->tm_mon + 1) * 100) + (t->tm_mday);	// 오늘 날짜( 20220304 꼴 )

	
	char Parameter_Insert[1000] = { NULL };				// 최종으로 _insert함수로 넣어줄 문자열 (sample.c에서의 value와 같다)
	char temp_int[20] = { 0 };							// int값을 문자열로 바꿀때 쓸 임시 문자열
	char Select_BuyingList_num[20] = { 0 };				// 발주번호 입력받을 임시 문자열변수

	// 창고선택
	if (initalizing("D:\\1_IoT\\Server_test\\test\\WareHouse") == -1) {		// 창고파일 오픈
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();							// 창고목록 출력
	printf("\n");

	printf("\n창고를 선택해주세요 : ");		// 출력된 창고목록에서 원하는 창고번호를 보고 입력
	scanf("%s", Select_WH);					// 창고번호를 입력받아 저장
											// ex) 1999를 입력함 = [Select_WH = 1999](문자열임을 주의)
	
	char select_num_warehouse[100] = "num_warehouse=";
	strcat(select_num_warehouse, Select_WH);	// select함수에 조건으로 입력하기 위한 양식만들기
												// ex) 여기까지 [select_num_warehouse = num_warehouse=1999]
	if (_select(select_num_warehouse, "name_warehouse, num_warehouse", &select_result_str) == -1) {	// 만든 양식을 토대로 창고목록에서 내부 칼럼정보를 선택해 받아옴
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	if ((result_count = recv_result(&_result, select_result_str)) == -1) {		// select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	strcat(Parameter_Insert, "\'");							// 문자열의 경우 앞뒤로 작은따옴표 필요
	strcat(Parameter_Insert, *(_result->_string_data));		// 받아온 결과를 저장
	strcat(Parameter_Insert, "\', ");						// 문자열의 경우 앞뒤로 작은따옴표 필요 + 끝났음을 의미하는 띄어쓰기

															// ex) 여기까지 [Parameter_Insert = 'warehouse1', ]

	itoa(*(_result->next->_int_data), temp_int, 10);		// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// 끝났음을 의미하는 띄어쓰기

															// ex) 여기까지 [Parameter_Insert = 'warehouse1', 1999, ]

	printf("\n\n");
	result_free(_result, result_count);
	file_column_free();

	// 발주리스트 출력 및 정보 받아오기
	if (initalizing("D:\\1_IoT\\Server_test\\test\\Buy_item") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	print_data();
	printf("\n");

	printf("\n발주번호를 선택해주세요 : ");			// 출력된 창고목록에서 원하는 창고번호를 보고 입력
	scanf("%s", Select_BuyingList_num);				// 창고번호를 입력받아 저장

	char select_num_BuyList[100] = "num_BuyList=";
	strcat(select_num_BuyList, Select_BuyingList_num);

	if (_select(select_num_BuyList, "name_item, num_item, date, name_responsible, num_responsible, num_buy, bill, pay_in, tax, pay_sum, rest_num_in", &select_result_str) == -1) {	// 만든 양식을 토대로 창고목록에서 내부 칼럼정보를 선택해 받아옴
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if ((result_count = recv_result(&_result, select_result_str)) == -1) {		// select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	

	// name_item
	strcat(Parameter_Insert, "\'");							// 문자열의 경우 앞뒤로 작은따옴표 필요
	strcat(Parameter_Insert, *(_result->_string_data));		// 받아온 결과를 저장
	strcat(Parameter_Insert, "\', ");						// 문자열의 경우 앞뒤로 작은따옴표 필요 + 끝났음을 의미하는 띄어쓰기

	//num_item
	itoa(*(_result->next->_int_data), temp_int, 10);		// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// 끝났음을 의미하는 띄어쓰기

	//date
	itoa(*(_result->next->next->_int_data), temp_int, 10);		// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// 끝났음을 의미하는 띄어쓰기


	//name_responsible
	strcat(Parameter_Insert, "\'");							// 문자열의 경우 앞뒤로 작은따옴표 필요
	strcat(Parameter_Insert, *(_result->next->next->next->_string_data));		// 받아온 결과를 저장
	strcat(Parameter_Insert, "\', ");						// 문자열의 경우 앞뒤로 작은따옴표 필요 + 끝났음을 의미하는 띄어쓰기

	//num_responsible
	itoa(*(_result->next->next->next->next->_int_data), temp_int, 10);		// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");

	// 입고수량 입력
	int num_InWarehouse = 0;
	printf("입고수량을 입력하세요 : ");
	scanf("%d", &num_InWarehouse);

	itoa(num_InWarehouse, temp_int, 10);					// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");
	
	// bill = 단가
	int bill = *(_result->next->next->next->next->next->next->_int_data);
	itoa(bill, temp_int, 10);		// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");
	
	// pay_in = 공급가
	int pay_in = num_InWarehouse * bill;
	itoa(pay_in, temp_int, 10);		// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");
	
	// tax = 세금
	int tax = pay_in / 10;
	itoa(tax, temp_int, 10);		// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");
	
	// pay_sum = 세금 + 공급가
	int pay_sum = pay_in + tax;
	itoa(pay_sum, temp_int, 10);		// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	

	// rest_num_in (입고이전 값)
	int rest_num_for_Warehousing_after;
	int rest_num_for_Warehousing_before = *(_result->next->next->next->next->next->next->next->next->next->next->_int_data);
	
	// rest_num_in (입고이후 값)
	rest_num_for_Warehousing_after = rest_num_for_Warehousing_before - num_InWarehouse;


	
	printf("\n\n");
	file_column_free();
	result_free(_result, result_count);
	

	if (initalizing("D:\\1_IoT\\Server_test\\test\\In_WareHouse") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert(Parameter_Insert) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n\n");
	file_column_free();

	if (initalizing("D:\\1_IoT\\Server_test\\test\\Buy_item") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	char update_rest_num_BuyList_before[100] = "rest_num_in=";
	char update_rest_num_BuyList_after[100] = "rest_num_in=";

	itoa(rest_num_for_Warehousing_before, temp_int, 10);		// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(update_rest_num_BuyList_before, temp_int);				// 변환한 문자열을 Parameter_Insert에 붙임

	itoa(rest_num_for_Warehousing_after, temp_int, 10);		// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(update_rest_num_BuyList_after, temp_int);				// 변환한 문자열을 Parameter_Insert에 붙임

	if (_update(select_num_BuyList, update_rest_num_BuyList_after) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n 입고되지 않은 남은 발주 수량은 %d개입니다.\n", rest_num_for_Warehousing_after);
	file_column_free();

	// name_item, num_item, date, name_responsible, num_responsible, num_buy, bill, pay_in, tax, pay_sum, rest_num_in
	
}

// rest_num_in
//itoa(*(_result->next->next->next->next->next->next->next->next->next->next->_int_data), temp_int, 10);		// 받아온 정보가 int형이므로 문자열로 형변환수행
//strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
// 
// 
//if (_insert("1, 'SampleItem1', 19999, 20220304, 'SamplePerson1', 199, 10, 1000, 10000, 1000, 11000, 100") == -1)
//{
//	printf("%s\n", err_msg);
//
//	file_column_free();
//	return -1;
//}

void Insert_WarehousingData(void)		// 예외입고 - 정보를 하나하나 입력
{
	result* _result;
	result* find;
	int result_count;

	time_t timer;
	struct tm* t;
	timer = time(NULL);
	t = localtime(&timer);

	int today_date = 0;
	today_date = ((t->tm_year + 1900) * 10000) + ((t->tm_mon + 1) * 100) + (t->tm_mday);	// 오늘 날짜( 20220304 꼴 )

	char Select_WH[10];
	char Select_Item[100];
	char Select_Person[100];
	char Parameter_Insert[1000] = { NULL };
	char temp_int[20] = { 0 };


	// 창고선택
	if (initalizing("D:\\1_IoT\\Server_test\\test\\WareHouse") == -1) {		// 창고파일 오픈
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();				// 창고목록 출력
	printf("\n");

	printf("\n창고를 선택해주세요 : ");		// 출력된 창고목록에서 원하는 창고번호를 보고 입력
	scanf("%s", Select_WH);				// 창고번호를 입력받아 저장
											// ex) 1999를 입력함 = [Select_WH = 1999](문자열임을 주의)

	char select_num_warehouse[100] = "num_warehouse=";
	strcat(select_num_warehouse, Select_WH);	// select함수에 조건으로 입력하기 위한 양식만들기
												// ex) 여기까지 [select_num_warehouse = num_warehouse=1999]
	if (_select(select_num_warehouse, "name_warehouse, num_warehouse", &select_result_str) == -1) {	// 만든 양식을 토대로 창고목록에서 내부 칼럼정보를 선택해 받아옴
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	if ((result_count = recv_result(&_result, select_result_str)) == -1) {		// select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	strcat(Parameter_Insert, "\'");							// 문자열의 경우 앞뒤로 작은따옴표 필요
	strcat(Parameter_Insert, *(_result->_string_data));		// 받아온 결과를 저장
	strcat(Parameter_Insert, "\', ");						// 문자열의 경우 앞뒤로 작은따옴표 필요 + 끝났음을 의미하는 띄어쓰기

															// ex) 여기까지 [Parameter_Insert = 'warehouse1', ]

	itoa(*(_result->next->_int_data), temp_int, 10);		// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// 끝났음을 의미하는 띄어쓰기

															// ex) 여기까지 [Parameter_Insert = 'warehouse1', 1999, ]

	printf("\n\n");
	result_free(_result, result_count);
	file_column_free();


	//품목선택
	if (initalizing("D:\\1_IoT\\Server_test\\test\\item") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();		// 품목목록 출력
	printf("\n");

	printf("\n품목을 선택해주세요 : ");		// 출력된 창고목록에서 원하는 창고번호를 보고 입력
	scanf("%s", Select_Item);				// 창고번호를 입력받아 저장

	char select_num_item[100] = "num_item=";
	strcat(select_num_item, Select_Item);

	if (_select(select_num_item, "name_item, num_item", &select_result_str) == -1) {	// 만든 양식을 토대로 창고목록에서 내부 칼럼정보를 선택해 받아옴
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	if ((result_count = recv_result(&_result, select_result_str)) == -1) {		// select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	strcat(Parameter_Insert, "\'");							// 문자열의 경우 앞뒤로 작은따옴표 필요
	strcat(Parameter_Insert, *(_result->_string_data));		// 받아온 결과를 저장
	strcat(Parameter_Insert, "\', ");						// 문자열의 경우 앞뒤로 작은따옴표 필요 + 끝났음을 의미하는 띄어쓰기

															// ex) 여기까지 [Parameter_Insert = 'warehouse1', 1999, 'SampleItem1', ]

	itoa(*(_result->next->_int_data), temp_int, 10);		// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// 끝났음을 의미하는 띄어쓰기

															// // ex) 여기까지 [Parameter_Insert = 'warehouse1', 1999, 'SampleItem1', 19999, ]
	// printf("%s", Parameter_Insert);

	printf("\n\n");
	result_free(_result, result_count);
	file_column_free();


	// 날짜입력
	itoa(today_date, temp_int, 10);		// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// 끝났음을 의미하는 띄어쓰기
	//printf("%s", Parameter_Insert);


	// 담당자입력
	if (initalizing("D:\\1_IoT\\Server_test\\test\\Person_responsibe") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();		// 담당자목록 출력
	printf("\n");

	printf("\n담당자를 선택해주세요 : ");		// 출력된 창고목록에서 원하는 창고번호를 보고 입력
	scanf("%s", Select_Person);				// 창고번호를 입력받아 저장

	char select_num_person[100] = "num_responsible=";
	strcat(select_num_person, Select_Person);

	if (_select(select_num_person, "name_responsible, num_responsible", &select_result_str) == -1) {	// 만든 양식을 토대로 창고목록에서 내부 칼럼정보를 선택해 받아옴
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	if ((result_count = recv_result(&_result, select_result_str)) == -1) {		// select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	strcat(Parameter_Insert, "\'");							// 문자열의 경우 앞뒤로 작은따옴표 필요
	strcat(Parameter_Insert, *(_result->_string_data));		// 받아온 결과를 저장
	strcat(Parameter_Insert, "\', ");						// 문자열의 경우 앞뒤로 작은따옴표 필요 + 끝났음을 의미하는 띄어쓰기

															// ex) 여기까지 [Parameter_Insert = 'warehouse1' ]

	itoa(*(_result->next->_int_data), temp_int, 10);		// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// 끝났음을 의미하는 띄어쓰기

	// printf("%s", Parameter_Insert);

	printf("\n\n");
	result_free(_result, result_count);
	file_column_free();



	// 입고수량,단가입력 및 계산값 입력
	int num_InWarehouse = 0;
	printf("입고수량을 입력하세요 : ");
	scanf("%d", &num_InWarehouse);

	itoa(num_InWarehouse, temp_int, 10);					// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// 끝났음을 의미하는 띄어쓰기

	int bill = 0;
	printf("단가를 입력하세요 : ");
	scanf("%d", &bill);

	itoa(bill, temp_int, 10);					// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// 끝났음을 의미하는 띄어쓰기

	int pay_in = bill * num_InWarehouse;

	itoa(pay_in, temp_int, 10);					// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// 끝났음을 의미하는 띄어쓰기

	int tax = pay_in / 10;

	itoa(tax, temp_int, 10);					// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// 끝났음을 의미하는 띄어쓰기

	int pay_sum = pay_in + tax;

	itoa(pay_sum, temp_int, 10);					// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임

	// printf("%s", Parameter_Insert);
	printf("\n\n");

	// 입고테이블에 완성된 파라미터 입력
	if (initalizing("D:\\1_IoT\\Server_test\\test\\In_WareHouse") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert(Parameter_Insert) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	
	printf("\n\n");
	file_column_free();
}