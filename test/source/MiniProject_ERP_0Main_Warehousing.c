#include "local.h"
#include"MiniProject_ERP_1struct.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)



int main(void)
{
	result* _result;
	result* find;
	int result_count;
	warehouse WH;
	workuse	WU;

	time_t timer;
	struct tm* t;
	timer = time(NULL);
	t = localtime(&timer);

	int today_date = 0; 
	today_date = ((t->tm_year + 1900)*10000) + ((t->tm_mon + 1) * 100) + (t->tm_mday);	// 오늘 날짜( 20220304 꼴 )

	// printf("%d", today_date);

	//테이블생성 및 초기데이터 삽입
	Create_File();												// 파일생성함수 ( MiniProject_ERP_initSampleData 에 정의 - 선언은 헤더파일 )
	Init_SampleData();				// 파일내부에 샘플정보(초기정보)를 insert하는 함수 ( MiniProject_ERP_initSampleData 에 정의 - 선언은 헤더파일 )
	
	//========================================= 실행부 ===========================================



	while (1)
	{
		int Select_main_menu = 0;

		printf("\n ==== < 원하는 메뉴선택 > ====\n\n");
		printf("\t1. 생산\n\t2. 입고/발주\n\t3. 자재\n\t4.프로그램 종료\n");
		scanf("%d", &Select_main_menu);

		if (Select_main_menu == 1)
		{
			system("cls");
			int Select_make_menu = 0;
			printf("\n ==== < 원하는 메뉴선택 > ====\n\n");
			printf("\t1. 자재사용관리\n\t2. 생산실적 및 생산품입고\n\t3. 뒤로가기 \n");
			scanf("%d", &Select_make_menu);

			if (Select_make_menu == 1)
			{
				while (1)
				{
					system("cls");
					int memunum, menu = 0;

					printf("\n=======================================메뉴 선택===============================================\n");
					printf("                      (1)조회(2)사용현황등록(3)삭제(4)나가기\n");
					printf("\n==================================번호를 입력해주세요==========================================\n");
					scanf("%d", &menu);

					if (menu == 1)
					{
						system("cls");
						Print_use();
					}
					else if (menu == 2)
					{
						system("cls");
						printf("\n=======================================메뉴 선택===============================================\n");
						printf("                       (1)작업별자재사용현황(2)제품별자재사용현황\n");
						printf("\n==================================번호를 입력해주세요==========================================\n");
						scanf("%d", &memunum);

						if (memunum == 1)	// 작업지시부분 오픈
						{
							system("cls");
							By_work();
							system("pause");
						}

						else if (memunum == 2)
						{
							system("cls");
							Product();
							system("pause");

						}
					}
					else if (menu == 3)
					{
						system("cls");
						Del();
						system("pause");
					}
					else if (menu == 4)
					{
						break;
					}

				}
			}
			else if (Select_make_menu == 2)
			{
				int select;
				while (1) {
					printf("(1)작업실적등록 (2)생산품창고입고처리 : ");
					scanf("%d", &select);
					switch (select) {
					case 1:
						system("cls");
						Registration_work_performance();
						break;
					case 2: 
						system("cls");
						Production_warehousing();
						break;
					default:
						break;
					}
					break;
				}
			}

			else if (Select_make_menu == 3)
			{
				break;
			}

		}

		else if (Select_main_menu == 2)
		{


			int Select = 0;
			printf(" 원하는 메뉴선택\n");
			printf("1. 발주\t2. 입고\t3. 뒤로가기\n");
			scanf("%d", &Select);

			if (Select == 1) // 발주
			{
				while (1)
				{
					system("cls");
					int Select_balju = 0;
					printf(" 발주메뉴입니다.\n 원하는 메뉴를 선택해주세요\n");
					printf(" 1. 발주등록\t2. 발주조회\t3. 발주삭제\t4. 뒤로가기\n");
					scanf("%d", &Select_balju);

					if (Select_balju == 1) // 1-1.발주등록
					{
						system("cls");
						insertOrderData();
						system("pause");
					}
					else if (Select_balju == 2)// 1-2.발주조회
					{
						system("cls");
						orderList();
						system("pause");

					}
					else if (Select_balju == 3) // 1-3. 발주삭제
					{
						system("cls");
						deleteOrderData();
						system("pause");
					}
					else if (Select_balju == 4) // 1-4. 뒤로가기
					{
						system("cls");
						break;
					}
					else
					{
						printf(" 잘못된 입력값입니다.\n");
						while (getchar() != '\n');
					}
				}
			}

			else if (Select == 2)	// 입고
			{

				while (1)
				{
					system("cls");
					int Select_ibgo = 0;
					printf(" 입고메뉴입니다.\n 원하시는 메뉴를 선택해주세요 : \n\n");
					printf(" 1. 예외입고\t2. 발주입고\t3. 입고현황\t4. 뒤로가기\n");
					//printf(" 1. 예외입고\t2. 발주입고\t3. 입고현황\t4. 입고삭제\t5. 뒤로가기\n");
					scanf("%d", &Select_ibgo);

					if (Select_ibgo == 1)	// 2-1.예외입고
					{
						system("cls");
						Insert_WarehousingData();
						system("pause");
					}

					else if (Select_ibgo == 2)	// 2-2.발주입고
					{
						system("cls");
						Insert_WarehousingData_from_BuyingList();
						system("pause");
					}

					else if (Select_ibgo == 3)	// 2-3.입고현황
					{
						system("cls");
						print_Warehousing_state();
						system("pause");

					}

					else if (Select_ibgo == 4)	// 2-4.뒤로가기
					{
						system("cls");
						break;
					}
					/*
					else if (Select_ibgo == 4)	// 2-4.입고삭제
					{
						system("cls");
						delete_Warehousing();
					}

					else if (Select_ibgo == 5)	// 2-5.뒤로가기
					{
						system("cls");
						break;
					}
					*/
					else
					{
						printf(" 잘못된 값입니다.\n");
						while (getchar() != '\n');
					}
				}
			}
			else if (Select == 3)	// 뒤로가기
			{
				break;
			}

			else
			{
				printf(" 잘못된 입력값 입니다\n");
				while (getchar() != '\n');
			}
		}

		else if (Select_main_menu == 3)	// 자재
		{
			while (1)
			{
				int option1, option2, option3;

				system("cls");


				printf("\t재고관리\n");
				printf("1.현 재고 현황 2.재고 이동 \n");
				printf("======================================\n");

				scanf("%d", &option1);

				system("cls");

				switch (option1)
				{

				case 1:
					printf("\t현 재고 현황\n");
					printf("======================================\n");
					jaego_print();
					break;

				case 2:
					printf("\t재고 사용하기 \n");
					printf("======================================\n");
					//사용할 재고 입력 
					// (모든 조건 검색해서 하나라도 있으면 생산하러가고 갯수 하나씩 줄이기)
					//재고 0 이면 발주로 보내고 입고 받은 재고번호 받아서 update




					 //jogun();

					//if (jaego_item <= 0)
					//{
					//	printf("발주하러 가자이\n");
					//	printf("\n");

					//ibgo_jaego_print();

					//	printf("\n");
					//	printf("\n");
					//	break;
					//}

					int a = chulgo_jaego_print();
					if (a > 0)
					{
						printf("======================================\n");
						printf("생산하러가자이\n");
						printf("======================================\n");
						system("pause");

					}
					else
					{
						printf("======================================\n");
						printf("발주하러가자이\n");
						printf("======================================\n");
						insertOrderData();
					}
					//else
					//{
					//	printf("\n");
					//	printf("생산하러 가자이\n");
					//	printf("\n");

					break;

				default:
					break;
				}
				break;
			}
		}
		else if (Select_main_menu == 4)	// 종료
		{
		exit(-1);
		}

 
		
	}

	file_column_free();
	return 0;
}