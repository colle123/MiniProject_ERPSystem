#include "local.h"


int main() {
	char* values = "NULL, 800, 'q', 69.11212 , 4215.134555666777";
	char* conditional = "TP='c'";
	char* set = "TP='c'";
	char* select_column = "code, number, TP, FLT, DBL";

	result* _result;
	result* find;
	int result_count;

	_create("abcd", "code VARCHAR(20) number INT TP CHAR FLT FLOAT DBL DOUBLE");

	if (initalizing("D:\\1_IoT\\Server_test\\test\\samplec") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	
	print_data();
	printf("\n");
	file_column_free();
	

	
	//if (_insert(values) == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}
	//print_data();
	//printf("\n");
	////file_column_free();
	

	/*
	if (_delete(conditional) == -1) {		// conditional 에는 조건을 넣어야함 (""로 묶어서) - 기본인 conditional은 "TP=q"이 입력되어있음
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	print_data();
	printf("\n");
	file_column_free();
	*/

	
	//if (_update("TP='c'", "code='kor'") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//print_data();
	//printf("\n");
	
	
	//if (_select(conditional, select_column, &select_result_str) == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}
	//else {
	//	printf("%s\n\n", select_result_str);
	//}

	//if ((result_count = recv_result(&_result, select_result_str)) == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}
	//result_print(_result, result_count);
	//printf("\n\n");

	/*
	if ((find = find_result(_result, "FLdf")) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		result_free(_result, result_count);
		return -1;
	}
	printf("     %s\n", find->name);
	printf("=============\n");
	for (int i = 0; i < result_count; i++) {
		switch (find->type) {
		case INT:
			if (int_is_null(find->_int_data[i]))
				printf("     (null)\n");
			else
				printf("     %d\n", find->_int_data[i]);
			break;
		case FLOAT:
			if (float_is_null(find->_float_data[i]))
				printf("     (null)\n");
			else
				printf("     %.5f\n", find->_float_data[i]);
			break;
		case DOUBLE:
			if (double_is_null(find->_double_data[i]))
				printf("     (null)\n");
			else
				printf("     %.12lf\n", find->_double_data[i]);
			break;
		case CHAR:
			if (char_is_null(find->_char_data[i]))
				printf("     (null)\n");
			else
				printf("     %c\n", find->_char_data[i]);
			break;
		case VARCHAR:
			if (string_is_null(find->_string_data[i]))
				printf("     (null)\n");
			else
				printf("     %s\n", find->_string_data[i]);
			break;
		}
	}
	
	file_column_free();
	result_free(_result, result_count);
	*/
	
}