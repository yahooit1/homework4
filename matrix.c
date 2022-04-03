#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); //matrix 생성 함수 선언
void print_matrix(int** matrix, int row, int col); //matrix A matrix B 출력 함수 선언
int free_matrix(int** matrix, int row, int col); //할당했던 메모리 해제 함수 선언
int fill_data(int** matrix, int row, int col); //행렬 A,B의 성분값 채우기 함수 선언
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); //matrix A + B 함수 선언
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); //matrix A-B 함수 선언 
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); //matrix A의 전치행렬 T 구하기 함수 선언
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);// matrix A * T 함수 선언

int main()
{
    char command; //메뉴선택저장변수선언
    printf("[----- [Gahyun]  [2020045070] -----]\n");

	int row, col;
	srand(time(NULL)); //난수생성을 위한 함수

	printf("Input row and col : ");
	scanf("%d %d", &row, &col); //행과 열 입력 받기 
    int** matrix_a = create_matrix(row, col); //matrix를 생성하여 matrix_a에 저장
	int** matrix_b = create_matrix(row, col); //matrix를 생성하여 matrix_b에 저장
    int** matrix_a_t = create_matrix(col, row); //matrix를 생성하여 matrix_a_t에 저장

	printf("Matrix Created.\n"); //matrix생성 완료하면 출력.

	if (matrix_a == NULL || matrix_b == NULL) {return -1;} //행렬 A나 B가 NULL일 경우 return -1 (후처리검사)

	do{ //while 이 아닐 경우 반복
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = "); 
		scanf(" %c", &command); //메뉴선택입력받기

		switch(command) { //switch 함수를 통해 조건문 구현
		case 'z': case 'Z': //case z일 경우 (대문자.소문자 모두 가능하도록 구현함)
		    printf("Matrix Initialized\n"); 
			fill_data(matrix_a, row, col); //행렬 A에 성분값 채우기(fill_data함수 호출)
			fill_data(matrix_b, row, col); //행렬 B에 성분값 채우기(fill_data함수 호출)
			break;
        case 'p': case 'P': //case p일 경우 (대문자.소문자 모두 가능하도록 구현함)
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col); //matrix A 출력 print_matrix함수 호출
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col); //matrix B 출력 print_matrix함수 호출
			break;
        case 'a': case 'A': //case a일 경우 (대문자.소문자 모두 가능하도록 구현함)
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col); //matrix A + matrix B구하기 (addition_matrix함수 호출)
			break;
        case 's': case 'S': //case s일 경우 (대문자.소문자 모두 가능하도록 구현함)
			printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col); //matrix A-matrix B (subtraction_matrix함수 호출)
			break;
        case 't': case 'T': //case t일 경우 (대문자.소문자 모두 가능하도록 구현함)
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //행렬 A의 전치행렬 구하기(transpose_matrix 함수 호출)
            print_matrix(matrix_a_t, col, row); //위에서 구한 전치행렬 출력(print_matrix함수 호출)
			break;
        case 'm': case 'M': //case m일 경우 (대문자.소문자 모두 가능하도록 구현함)
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row); //행렬 A의 전치행렬 구하기(transpose_matrix 함수 호출)
            multiply_matrix(matrix_a, matrix_a_t, row, col); //행렬 A와 전치행렬 T의 행렬 곱 구하기(multiply_matrix함수 호출)
			break;
        case 'q': case 'Q': //case q일 경우 (대문자.소문자 모두 가능하도록 구현함)
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row); //전치행렬 T에 할당된 메모리 해제
            free_matrix(matrix_a, row, col); //행렬 A에 할당된 메모리 해제
            free_matrix(matrix_b, row, col); //행렬 B에 할당된 메모리 해제
			break;
		default: //case에 없는 알파벳을 입력했을 경우 
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q나 Q일 경우 종료

	return 1; //종료 후 1 반환
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col) //배열 생성 함수 (반환되는 값이 정수형 이중포인터)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //입력받은 행이나 열이 0이거나 0보다 작을 경우 
		printf("Check the size of row and col!\n");
		return NULL; //NULL반환
	}

	int** matrix = (int**)malloc(sizeof(int*) * row); //matrix에 각 행의 포인터수 만큼 동적 메모리 할당
	for (int r = 0; r < row; r++) { //행의 수 만큼 반복
		matrix[r] = (int*)malloc(sizeof(int) * col); //matrix의 각 원소에 열의 포인터수만큼 동적 메모리 할당
	}

	/* Check post conditions */
	if (matrix == NULL) { //matrix가 NULL값 이라면 (입력받은 행이나 열이 0이하라면)
		printf("Memory Allocation Failed.\n");
		return NULL; //NULL반환
	}

	return matrix; //matrix 반환
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col) //이중포인터 matrix를 통해 행렬 출력
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //행이나 열이 0이하일 경우
		printf("Check the size of row and col!\n");
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) { //row번 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++) //col번 반복
			printf("%3d ", matrix[matrix_row][matrix_col]); //각 원소의 값 출력
		printf("\n");
	}
	printf("\n");
	/* Check post conditions */
	 if (matrix == NULL) { //matrix가 NULL일 경우 (행이나 열의 크기가 0이하일때)
		printf("Memory Allocation Failed.\n");
		return;
	}


	return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)  //할당된 메모리 해제하는 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {  //행이나 열의 크기가 0이하일 경우
		printf("Check the size of row and col!\n");
		return -1; //-1반환
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) { //row번 반복
		free(matrix[matrix_row]); //matrix[matrix_row]에 할당한 메모리 해제
	}

	free(matrix); //matrix에 할당된 메모리 해제
	return 1; //1 반환
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col) //matrix에 원소값 입력하기
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //행이나 열의 크기가 0이하일 경우
		printf("Check the size of row and col!\n");
		return -1; //-1 반환
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) //row번 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++) //col번 반복
			matrix[matrix_row][matrix_col] = rand() % 20; //2차원 배열 matrix의 각 원소에 랜덤하게 원소값 생성하기
	/* Check post conditions */
    if (matrix == NULL) { //matrix가 NULL일 경우 (행이나 열의 크기가 0이하일때)
		printf("Memory Allocation Failed.\n");
		return -1; //-1반환
	}
	return 1; //-1반환
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col) //이중포인터 matrix_a와 matrix_b를 통해 행렬 A와 행렬 B의 합 구하기
{
    int** matrix_sum = create_matrix(row, col); //이중포인터 matrix_sum에 create_matrix를 통해 생성한 배열 대입
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //행이나 열의 크기가 0이하일때
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { //row 만큼 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++) //col만큼 반복
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col]; 
            //배열 A의 각 원소와 배열 B의 각 원소를 더하여 matrix_sum의 각 원소에 대입
	}
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {
        //matrix_a나 matrix_b나 matrix_sum중 하나라도 NULL일 경우 (행이나 열의 크기가 0이하일때)
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	print_matrix(matrix_sum, row, col); //matrix_sum출력 (print_matrix함수 호출)
	free_matrix(matrix_sum, row, col); //matrix_sum에 할당된 메모리 해제(free_matrix함수 호출)
	return 1; //1반환
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)//이중포인터 matrix_a와 matrix_b를 통해 행렬 A와 행렬 B의 합 구하기
{
    int** matrix_sub = create_matrix(row, col); //이중포인터 matrix_sub에 create_matrix를 통해 생성한 배열 대입
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {  //행이나 열의 크기가 0이하일 경우
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {//row만큼 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++) //col만큼 반복
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
            //배열 A의 각 원소와 배열 B의 각 원소를 빼서 matrix_sub의 각 원소에 대입
	}
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {
        //matrix_a나 matrix_b나 matrix_sum중 하나라도 NULL일 경우 (행이나 열의 크기가 0이하일때)
		printf("Memory Allocation Failed.\n");
		return -1; //-1 반환
	}
	print_matrix(matrix_sub, row, col); //matrix_sub출력(print_matrix 함수 호출)
	free_matrix(matrix_sub, row, col); //matrix_sub에 할당된 메모리 해제(free_matrix함수 호출)

	return 1; //1 반환 
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) 
//이중포인터 matrix와 matrix_t를 매개변수로 하여 전치행렬 구하는 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //행이나 열의 크기가 0이하일 경우
		printf("Check the size of row and col!\n");
		return -1; //-1반환
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { //row번 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++) //col 번 반복 
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row];
			 //matrix_t의 각 원소에 matrix의 원소를 열 우선으로 대입
	}
	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) { //matrix나 matrix_t중 하나라도 NULL일 경우 (행이나 열의 크기가 0이하일때)
		printf("Memory Allocation Failed.\n");
		return -1; //-1반환
	}

	return 1; //1 반환
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col) //이중포인터 matrix_a와 matrix_t를 통해 행렬 곱 구하기
{
    int** matrix_axt = create_matrix(row, row); //이중포인터 matrix_axt에 create_matrix함수를 이용해 생성한 배열을 대입(단,행과열의 크기가 같아야 하므로 매개변수는 row,row)
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //행이나 열의 크기가 0이하일 경우
		printf("Check the size of row and col!\n");
		return -1; //-1 반환
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) { //row번 반복 (행만큼 반복)
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) { //row번 (열만큼 반복)
			int temp = 0; //곱한 값 저장할 변수
			for (int matrix_col = 0; matrix_col < col; matrix_col++) //matrix a의 열만큼 반복
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row]; 
				//temp에 행렬 A[matrix_a_row][matrix_col] * 전치행렬 T[matrix_col][matrix_t_row]의 원소를 곱한 값을 더한다.
			matrix_axt[matrix_a_row][matrix_t_row] = temp; //matrix_axt에 temp에 저장된 값 대입
		}
	}
	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) { //matrix_t나 matrix_axt 둘 중 하나라도 NULL일 경우
		printf("Memory Allocation Failed.\n");
		return -1; //-1 반환
	}
	print_matrix(matrix_axt, row, row); //matrix_axt 출력(print_matrix 함수 호출)
	free_matrix(matrix_axt, row, col); //matrix_axt에 할당된 메모리 해제
	return 1; //1 반환
}
