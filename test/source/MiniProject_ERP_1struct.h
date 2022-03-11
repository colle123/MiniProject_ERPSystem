#ifndef __STRUCT_H__
#define __STRUCT_H__

// ERP 시스템 입고처리에 사용될 구조체와 입고구조 원리

void Create_File(void);
void Init_SampleData(void);
void Insert_WarehousingData(void);
void Insert_WarehousingData_from_BuyingList(void);
void print_Warehousing_state(void);
void delete_Warehousing(void);
void Insert(void);
void edit_minus_table(void);		////생산 넘겨주며 수량 하나씩 빼고 넘겨주기
void edit_plus_table(void);			////입고한 수량만큼 더해주기
void jaego_print1(void);			////최종 재고 수량 출력해서 조회
void initCreate();
void initSampledata();

typedef struct In_WareHouse					// 입고구조체
{
	int num_In_WareHouse;			// 입고순번
	char name_warehouse[20];		// 창고이름
	int num_warehouse;				// 창고번호
	char name_item[20];				// 품목이름
	char num_item[20];					// 품목번호
	char LOT_number[20];			// 품목 루트넘버
	int date;						// 입고날짜
	char name_responsible[20];		// 담당자이름
	int num_responsible;			// 담당자번호
	int num_in;						// 입고수량
	int bill;						// 단가
	int pay_in;						// 공급가액 = 입고수량 * 단가
	int tax;						// 부가세 = 공급가액 * 0.1
	int pay_sum;					// 합계액 = 공급가액 + 부가세;
}warehouse;

typedef struct jaego					// 재고 조회 구조체
{
	int num_Jaego;					// 재고순번
	char name_item[20];				// 품목이름
	char num_item[20];				// 품목번호
	char name_warehouse[20];		// 창고이름
	int num_warehouse;				// 창고번호
	char LOT_number[20];			// 품목 루트넘버
	int date;						// 입고날짜
	int num_chogi_item;				// 초기수량
	int num_in;						// 입고수량
	int num_chulgo_item;			// 출고수량
	int num_jaego_item;				// 최종 재고 수량


}Jaego;

struct Buy_item						// 발주 구조체
{
	int num_buyList;				// 발주번호
	char name_item[20];				// 발주품명
	int num_item;					// 발주품번
	int date;						// 발주날짜
	char name_responsible[20];		// 담당자이름
	int num_responsible;			// 담당자번호
	int num_buy;					// 발주수량
	int bill;						// 단가
	int pay_in;						// 공급가액 = 발주수량 * 단가
	int tax;						// 부가세 = 공급가액 * 0.1
	int pay_sum;					// 합계액 = 공급가액 + 부가세;
	int rest_num_in;				// 남은발주수량(분할 입고될시 남은 입고수량계산을 위함)
};

struct Buy_company					// 거래처구조체
{
	char name_buy_company[20];		// 거래처 이름
	int num_buy_company;			// 거래처 번호
};

struct Person_responsibe			// 담당자구조체
{
	char name_responsible[20];		// 담당자이름
	int num_responsible;			// 담당자번호
};

struct item							// 품목구조체
{
	char name_item[20];				// 품목 품명
	int num_item;					// 품목 품번
	char State[20];					// 계정구분  - 원자재)RawMaterial, 부제품Subsidiary, 상품Product
	int Daily_Output;				// 일일 생산량
	char LOT_number[20];			// RA = 원자재, SU =	부제품, PR = 상품
									// ex) 
};

typedef struct Work_Use			// 자재 사용(작업별) 구조체
{
	char work_order_num[20];	//작업지시번호
	char Product_num[20];		// 품목번호
	char Product_name[20];		// 품목이름
	int Amountused;				//사용수량
	int Performanced_number;	//실적번호
	char LOT[20];				//lot넘버

}workuse;


typedef struct Work_process			// 작업지시 부분 
{
	char work_order_num[20];	//작업지시번호
	char Product_name[20];		//품명
	char Product_num;			//품번
	char client[10];			//이름
	int indicated_quantity;		//지시수량
	int performance_quantity;	//실적수량
	int performance_num;		//실적번호
	char LOT[20];				//실적lot넘버

};

typedef struct Work_Productwork		// 자재사용현황(제품별)
{
	int work_order_num;	//작업지시번호(작업지시부분)
	int Product_num;		//품목번호(작업지시부분)
	char Product_name[20];	//품목이름(작업지시부분)
	int LOT;				//lot번호(작업지시부분)
	int indicated_quantity;	//지시수량=실적수량(작업지시부분)
	char item_NUMBER[20];	//물품번호(제품등록부분)
	char item_NAME[20];		//물품명
	char item_LOT[20];		//물품 lot번호
	int Amountused;			//사용수량(입력)

};

typedef struct ITEM			// 물품등록
{
	char item_NAME[20];		//물품명
	char item_NUMBER[20];	//물품번호
	char item_TYPE[20];
	int item_GOAL;
	char item_LOT[20];
	char tem_SirealNUMBER[20];
};


/* 생산품 청구등록 -> 작업지시
   사용일자(입력)
   품번,품명,규격,단위 LOT넘버-> 서버 품목구조체리스트에서받음
   사용수량 (입력)
   공정, 작업장 입력 , 실적번호*/


	// < 입고처리 >
		/*
		
		선택 - 1. 예외입고 2. 발주입고

		1. 예외입고
		(예외입고는 전화발주등으로 발주한 품목의 입고를 입력하는 것)

		입고일자(입력)
		거래처(선택 - 서버로부터 거래처구조체리스트를 받아옴)
		담당자(선택 - 서버로부터 담당자 구조체리스트 받아옴)
		품목(선택 - 서버로부터 품목구조체리스트 받아옴)
		발주수량(입력)
		단가(입력)

		------------까지 입력받고,

		공급가액(자동계산 : 발주수량 * 단가)
		부가세(자동계산 : 공급가 * 0.1)
		합계액(자동계산 : 부가세 + 공급가액)

		------------을 계산해서 여기까지의 입력 / 계산 내용을 양식에 맞게 출력후
		사용자로부터 입력내용이 맞으면 입력(1), 틀리면(2)입력받음

		맞다(1)->입고구조체에 이 내용을 삽입(서버)

		2. 발주입고

		1) 발주현황을 출력(서버로부터 발주구조체를 받아옴)하고 여기서 어떤 발주사항에 대해서 입고할지 선택
		2) 선택한 발주사항중 어떤 품목을 입고할지 입력
		3) 입고수량을 입력(이때, 입고수량이 남은발주수량을 넘는지 확인)
		4) 여기까지 내용을 출력후 맞는지 사용자확인후 발주구조체(서버)의 남은발주수량을계산(초기값은 발주수량, 입고될때마다 입고수량을 뺀다)
		5) 입고구조체에 내용삽입(서버)

		*/

#endif