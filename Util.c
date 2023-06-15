#include "Util.h"
//-----------------------------------------------------------------------------------------------//
//Q1
char* PairSortedArrays(char a[], char b[])
{
	int n1 = strlen(a);
	int n2 = strlen(b);
	char* pairedString = (char*)malloc(sizeof(char)*(n1 + n2 + 1));
	if (pairedString == NULL) {
		printf("FAILED TO ALLOCATE MEMORY FOR pairedString.");
		return NULL;
	}
	//If we got here, then it means that pairedString is NOT NULL.
	char* p1 = a;
	char* p1End = a + n1;
	char* p2 = b;
	char* p2End = b + n2;
	char* p3 = pairedString;
	while (p1 != p1End&& p2 != p2End) {
		*(p3++) = *p1 <= *p2 ? *(p1++) : *(p2++);
	}
	if (p1 != p1End) {
		while (p1 != p1End) {
			*(p3++) = *(p1++);
		}
	}
	if (p2 != p2End) {
		*(p3++) = *(p2++);
	}
	*p3 = '\0';
	return pairedString;
}
//-----------------------------------------------------------------------------------------------//
//Q2
char** LowerSTR(char* arr[], int size_arr, char* str, int* size_res)
{
	int counter = 0;
	for (int i = 0; i < size_arr; i++) {
		if (strcmp(arr[i], str) < 0) {
			counter++;
		}
	}
	char** lowerSTR = (char**)malloc(sizeof(char*) * counter);
	if (lowerSTR == NULL) {
		return NULL;
	}
	int index = 0;
	for (int i = 0; i < size_arr; i++) {
		if (strcmp(arr[i], str) < 0) {
			int size = strlen(arr[i])+1;
			lowerSTR[index] = (char*)malloc(sizeof(char) * size);
			if (lowerSTR[index] == NULL) {
				for (int j = 0; j < index; j++) {
					free(lowerSTR[j]);
				}
				free(lowerSTR);
				return NULL;
			}
			strcpy_s(lowerSTR[index],size*sizeof(char),arr[i]);
			index++;
			if (index == counter) {
				break;
			}
		}
	}
	*size_res = counter;
	return lowerSTR;
}
//-----------------------------------------------------------------------------------------------//
//Q3
char* AddNumbers(char* num1, char* num2)
{
	/*
	* OBSERVATION:
	* if num1 have n1 digits, num2 have n2 digits, and max({n1,n2}) = n1,
	* then the result of the addition of num1 and num2 has at most (n1)+1 digits.
	* Thus, I will initially allocate max({n1,n2}+1) memory, and if there are  enough
	* carry overs to justify an additional digit(Most Significant Bit), I will allocate new memory with 
	* (max({n1,n2})+1)+1 memory.
	*/
	int cmpRes = strlen(num1)-strlen(num2);
	char* maxStr = cmpRes >= 0 ? num1 : num2;
	char* minStr = cmpRes < 0 ? num1 : num2;
	int maximum = strlen(maxStr);
	int minimum = strlen(minStr);
	char* summationResult = (char*)malloc(((maximum + 1)) * sizeof(char));
	if (!summationResult) {
		return NULL;
	}
	summationResult[maximum] = '\0';
	int carryOver = 0;
	int i = minimum - 1;
	while (i >= 0) {
		int d1 = minStr[i] - '0';
		int d2 = maxStr[i + maximum - minimum] - '0';//maxStr may have more digits, thus an offset is required in order to compare correct digits
		int sumD1D2 = d1 + d2 + carryOver;
		int digit_i = sumD1D2;
		if (sumD1D2 > 9) {
			carryOver = 1;
			digit_i %= 10;
			
		}
		else {
			carryOver = 0;
		}
		summationResult[i + maximum - minimum] = '0' + digit_i;
		i--;
	}
	if (maximum == minimum && carryOver == 0) {
		return summationResult;
	}
	//if maximum>minimum, we need to continue and add any digits of maxStr plus whatever carries may propagate due to the per digit summation of
	//minStr and maxStr
	for (int j = maximum - minimum -1; j >= 0; j--) {
		int sumCarry = carryOver + (maxStr[j] - '0');
		int dig = sumCarry;
		if (sumCarry > 9) {
			carryOver = 1;
			dig %= 10;
		}
		else {
			carryOver = 0;
		}
		summationResult[j] = '0' + dig;
	}

	if (carryOver == 0) {
		return summationResult;
	}
	else {
		char* overFlowedStr = (char*)malloc(sizeof(char) * ((maximum + 1)+1));
		if (overFlowedStr == NULL) {
			free(summationResult);
			return NULL;
		}
		strcpy_s(overFlowedStr + 1, (maximum + 1) * sizeof(char), summationResult);
		overFlowedStr[0] = '1';
		free(summationResult);
		return overFlowedStr;
	}
}
//-----------------------------------------------------------------------------------------------//
//Q4
int* CreateRange(int start, int end, int jump, int* sizeRage)
{
	int counter = 0;
	int min = start;
	while (min <= end) {
		min += jump;
		counter++;
	}
	*sizeRage = counter;
	int* finiteSeqence = (int*)malloc(sizeof(int)*counter);
	if (finiteSeqence == NULL) {
		return NULL;
	}
	for (int i = 0; i < counter; i++) {
		finiteSeqence[i] = start + i * jump;
	}
	return finiteSeqence;
}
//-----------------------------------------------------------------------------------------------//
//Q5
int** GradeStat(int* Grades, int size_grades, int grd_range, int* count_grd, int* avg_grd)
{
	int amountOfSubArrays = (100 / grd_range) + 1;
	/*
	* Using calloc, since I want all counters to be set to 0
	*/
	count_grd = (int*)calloc(amountOfSubArrays,sizeof(int));
	if (count_grd == NULL) {
		return NULL;
	}
	/*
	* Using calloc, since I want all avgs to be set to 0
	*/
	avg_grd = (int*)calloc(amountOfSubArrays, sizeof(int));
	if (avg_grd == NULL) {
		free(count_grd);
		return NULL;
	}

	for(int i=0;i<size_grades;i++){
		count_grd[Grades[i] / grd_range]++;
		avg_grd[Grades[i] / grd_range] += Grades[i];
		//TODOremember to later go over again and divide by count_grd[Grades[i]/grd_range]
	}
	for (int i = 0; i < size_grades; i++) {
		if (count_grd[Grades[i] / grd_range]) {
			avg_grd[Grades[i] / grd_range] /= count_grd[i];
			//Here I set the avgs, since previously I summed the grades for the range,
			//And now I divide by their ammount, and it is ok, since counter!=0
		}
		
	}
	int** gradesGroupedByRange = (int**)malloc(sizeof(int*) * amountOfSubArrays);
	if (gradesGroupedByRange == NULL) {
		free(count_grd);
		free(avg_grd);
		return NULL;
	}
	for (int i = 0; i < size_grades; i++) {
		int j = Grades[i] / grd_range;
		if(count_grd[j]){
			int* p = (int*)malloc(sizeof(int) * count_grd[j]);
			if (p == NULL) {//Need to release all previously dynamicaly allocated memory
				for (int k = 0; k < amountOfSubArrays; k++) {
					if (gradesGroupedByRange[k] != NULL) {
						free(gradesGroupedByRange[k]);
					}
				}
				free(count_grd);
				free(avg_grd);
				return NULL;
			}
			gradesGroupedByRange[j] = p;
		}
		else {
			gradesGroupedByRange[j] = NULL;
		}
	}
	return gradesGroupedByRange;
}
//-----------------------------------------------------------------------------------------------//