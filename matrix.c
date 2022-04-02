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
    int** matrix_a = create_matrix(row, col); //matrix를 생성하여 이중포인터 matrix_a에 저장
	int** matrix_b = create_matrix(row, col); //matrix를 생성하여 이중포인터 matrix_b에 저장
    int** matrix_a_t = create_matrix(col, row); //matrix를 생성하여 이중포인터 matrix_a_t에 저장

	printf("Matrix Created.\n"); //matrix생성 완료하면 출력.

	if (matrix_a == NULL || matrix_b == NULL) {return -1;} //행렬 A나 B가 NULL일 경우 return -1 (후처리검사)

	do{
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
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return NULL;
	}

	int** matrix = (int**)malloc(sizeof(int*) * row);
	for (int r = 0; r < row; r++) {
		matrix[r] = (int*)malloc(sizeof(int) * col);
	}

	/* Check post conditions */
	if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return NULL;
	}

	return matrix;
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			printf("%3d ", matrix[matrix_row][matrix_col]);
		printf("\n");
	}
	printf("\n");
	/* Check post conditions */
	 if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return;
	}


	return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		free(matrix[matrix_row]);
	}

	free(matrix);
	return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++)
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix[matrix_row][matrix_col] = rand() % 20;
	/* Check post conditions */
    if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	return 1;
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row, col);
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	print_matrix(matrix_sum, row, col);
	free_matrix(matrix_sum, row, col);
	return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row, col);
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_sub, row, col);
	free_matrix(matrix_sub, row, col);

	return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row];
	}
	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int** matrix_axt = create_matrix(row, row);
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) {
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) {
			int temp = 0;
			for (int matrix_col = 0; matrix_col < col; matrix_col++)
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];
			matrix_axt[matrix_a_row][matrix_t_row] = temp;
		}
	}
	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_axt, row, row);
	free_matrix(matrix_axt, row, col);
	return 1;
}
