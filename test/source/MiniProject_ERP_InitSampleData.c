#include "local.h"
#include"MiniProject_ERP_struct_warehousing.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

void Create_File(void)
{
	// 입고테이블 서버에 생성
	_create("In_WareHouse", "num_In_WareHouse INT name_warehouse VARCHAR(20) num_warehouse INT name_item VARCHAR(20) num_item VARCHAR(20) LOT_number VARCHAR(20)  date INT name_responsible VARCHAR(20) num_responsible INT num_in INT bill INT pay_in INT tax INT pay_sum INT");
							// 입고순번				창고이름						창고번호			품목명					품번			품목로트넘버				날짜		담당자명							담당자번호		입고수량		단가		공급가		세금		합계액
	
	// 발주테이블 서버에 생성
	_create("Buy_item", "num_BuyList INT name_item VARCHAR(20) num_item VARCHAR(20) LOT_number VARCHAR(20) date INT name_responsible VARCHAR(20) num_responsible INT num_buy INT bill INT pay_in INT tax INT pay_sum INT rest_num_in INT");
	//						발주번호			품목명				품번					품목로트넘버				날짜			담당자명						담당자번호		발주수량		단가		공급가액		세금			합계액			남은발주수량
	
	// 거래처테이블 서버에 생성
	_create("Buy_company", "name_buy_company VARCHAR(20) num_buy_company INT");
	//							거래처명						거래처번호
	
	// 담당자테이블 서버에 생성
	_create("Person_responsibe", "name_responsible VARCHAR(20) num_responsible INT");
	//								담당자명							담당자번호
	
	// 품목테이블 서버에 생성
	_create("ITEM", "item_NAME VARCHAR(20) item_NUMBER VARCHAR(20) item_TYPE VARCHAR(20) item_GOAL INT item_LOT VARCHAR(20) item_SirealNUMBER VARCHAR(20)");
	//				품목명					품번						계정상태				일일생산량		폼목로트넘버				시리얼넘버
	
	// 창고고테이블 서버에 생성
	_create("WareHouse", "name_warehouse VARCHAR(30) num_warehouse INT");
	//						창고이름						창고번호
}

void Init_SampleData(void)
{
	// 입고테이블 샘플데이터 삽입
	if (initalizing("In_WareHouse") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("1, 'Warehouse1', 1999, 'CPU','CP10', 'CP20220308', 20220305, 'SamplePerson1', 199, 100, 990, 99000, 9900, 108900") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("2, 'Warehouse2', 2999, 'HARD', 'HR10', 'HR20220308', 20220307,  'SamplePerson1', 199, 20, 1000, 20000, 2000, 22000") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("3, 'Warehouse1', 1999, 'MAINBORAD', 'MB10', 'MB20220308', 20220301, 'SamplePerson1', 199, 100, 100, 10000, 1000, 11000") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	int num_Warehousing_List = 3;
	//print_data();
	//printf("\n");
	
	file_column_free();


	// 발주테이블 샘플데이터 삽입
	if (initalizing("Buy_item") == -1) 
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("1, 'CPU','CP10','CP20220308', 20220304, 'SamplePerson1', 199, 100, 1000, 10000, 1000, 11000, 100") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	if (_insert("2, 'MONITOR', 'MO10', 'MO20220308', 20220304, 'SamplePerson2', 299, 200, 2000, 40000, 4000, 44000, 100") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	if (_insert("3, 'CASE', 'CA10','CA20220308', 20220304, 'SamplePerson1', 199, 300, 3000, 90000, 9000, 99000, 100") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	//print_data();
	//printf("\n");
	
	
	file_column_free();


	// 거래처테이블 샘플데이터 삽입
	if (initalizing("Buy_company") == -1) {
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
	if (initalizing("Person_responsibe") == -1) {
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

	//print_data();
	//printf("\n");
	
	file_column_free();
	

	// 품목테이블 샘플데이터 삽입
	if (initalizing("item") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'CPU','CP10','meterial',100,'CP20220308','C19999P19'") == -1) {
		//1.물품명 cpu 2.물품번호 cp10 3.물품계정구분 meterial 4.일생산량 100 5.LOT번호 cp20220308 6.시리얼 번호 c19999p19
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'HARD','HR10','meterial',100,'HR20220308','H1999R19'") == -1) {
		//1.물품명 hard 2.물품번호 hr10 3.물품계정구분 meterial 4.일생산량 100 5.LOT번호 hr20220308 6.시리얼 번호 h1999r19
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'KEYBORAD','KE10','submeterial',100,'KE20220308','K1999E19'") == -1) {
		//1.물품명 keyborad 2.물품번호 ke10 3.물품계정구분 submeterial 4.일생산량 100 5.LOT번호 ke20220308 6.시리얼 번호 k1999e19
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'MAINBORAD','MB10','meterial',100,'MB20220308','M1999B19'") == -1) {
		//1.물품명 mainborad 2.물품번호 mb10 3.물품계정구분 meterial 4.일생산량 100 5.LOT번호 mb20220308 6.시리얼 번호 m1999b19
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'MONITOR','MO10','submeterial',100,'MO20220308','M1999O19'") == -1) {
		//1.물품명 monitor 2.물품번호 mo10 3.물품계정구분 submeterial 4.일생산량 100 5.LOT번호 mo20220308 6.시리얼 번호 m1999o19
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'CASE','CA10','meterial',100,'CA20220308','C1999A19'") == -1) {
		//1.물품명 case 2.물품번호 ca10 3.물품계정구분 meterial 4.일생산량 100 5.LOT번호 ca20220308 6.시리얼 번호 c1999a19
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	//print_data();
	//printf("\n");
	
	file_column_free();

	// 창고테이블 샘플데이터 삽입
	if (initalizing("WareHouse") == -1) {
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