#include <stdio.h>
#include "local.h"
#include <time.h>
#include"MiniProject_ERP_struct_warehousing.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)



int main(void)
{
	char* values = "NULL, 800, 'q', 69.11212 , 4215.134555666777";
	char* conditional = "TP='c'";
	char* set = "TP='c'";
	char* select_column = "code, number, TP, FLT, DBL";

	result* _result;
	result* find;
	int result_count;
	warehouse WH;

	time_t timer;
	struct tm* t;
	timer = time(NULL);
	t = localtime(&timer);

	int today_date = 0; 
	today_date = ((t->tm_year + 1900)*10000) + ((t->tm_mon + 1) * 100) + (t->tm_mday);	// 오늘 날짜( 20220304 꼴 )

	// printf("%d", today_date);

	//테이블생성 및 초기데이터 삽입
	Create_File();					// 파일생성함수 ( MiniProject_ERP_initSampleData 에 정의 - 선언은 헤더파일 )
	Init_SampleData();				// 파일내부에 샘플정보(초기정보)를 insert하는 함수 ( MiniProject_ERP_initSampleData 에 정의 - 선언은 헤더파일 )

	//========================================= 실행부 ===========================================


	while (1)
	{
		char temp_insert[100];
		int Select = 0;


		printf("입고유형을 선택해주세요 : \n\n");
		printf("1. 예외입고\t2. 발주입고\t3. 뒤로가기\n");
		scanf("%d", &Select);
		//getchar();

		if (Select == 1)	// 1.예외입고
		{
			char Select_WH[100];
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
			scanf("%s", &Select_WH);				// 창고번호를 입력받아 저장
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
			scanf("%s", &Select_Item);				// 창고번호를 입력받아 저장

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
			printf("%s", Parameter_Insert);


			// 담당자입력
			if (initalizing("D:\\1_IoT\\Server_test\\test\\Person_responsibe") == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}
			
			print_data();		// 담당자목록 출력
			printf("\n");

			printf("\n담당자를 선택해주세요 : ");		// 출력된 창고목록에서 원하는 창고번호를 보고 입력
			scanf("%s", &Select_Person);				// 창고번호를 입력받아 저장

			char select_num_person[100] = "num_responsible=";
			strcat(select_num_person, Select_Person);
			
			if (_select(select_num_item, "name_responsible, num_responsible", &select_result_str) == -1) {	// 만든 양식을 토대로 창고목록에서 내부 칼럼정보를 선택해 받아옴
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

			printf("%s", Parameter_Insert);

			printf("\n\n");
			result_free(_result, result_count);
			file_column_free();
		}

		else if (Select == 2)	// 2.발주입고
		{

		}

		else if (Select == 3)	// 3.뒤로가기
		{
			printf("이전 메뉴로 돌아갑니다.");
			break;
		}

		else
		{
			printf("잘못된 값입니다.\n");
		}
	}


	// file_column_free();

	return 0;
}

//if (_insert("'Warehouse1', 1999, 'SampleItem1', 19999, 20220304, 'SamplePerson1', 199, 99, 100, 0, 0, 0") == -1)
//{
//	printf("%s\n", err_msg);
//
//	file_column_free();
//	return -1;
//}