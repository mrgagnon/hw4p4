/* Maylee Gagnon
 * HW4P4 gemsquare
 * 11.16.19
 */
#include <iostream>
using namespace std;

int main() {
	int boardActual[8][8] =
			{{89, 70, 73, 83, 90, 22, 44, 92},
			{46, 23, 99, 77, 10, 42, 1, 72},
			{85, 52, 27, 5, 94, 91, 82, 62},
			{22, 93, 68, 11, 56, 63, 49, 35},
			{13, 78, 48, 19, 78, 11, 90, 94},
			{31, 5, 63, 10, 32, 40, 14, 13},
			{73, 38, 24, 49, 18, 6, 40, 74},
			{79, 71, 18, 20, 34, 51, 93, 65}}; //board with actual values of each square
	int boardMax[8][8] =
		{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}};; //keep track of dynamic max values
	int total = 0;
	int vaultNum = 0;
	int path[7] = {}; //keeps track of the path, array stores column, index stores row

	int sizeBound = 7;
	for (int i = sizeBound; i>=0; i--){
		for (int j = 0; j<=sizeBound; j++){
			int diagLeft = -1;
			int straight = -1;
			int diagRight = -1;

			int r = i+1;
			if (r > sizeBound){ // in first row
				boardMax[i][j] = boardActual[i][j];
				continue;
			}

			int c = j-1;
			if (c >= 0){
				diagLeft = boardMax[r][c];
			}

			straight = boardMax[r][j];

			int c1 = j+1;
			if (c1 <= sizeBound){
				diagRight = boardMax[r][c1];
			}

			//getting max value, if equal it will take diagLeft first then straight then diagRight
			int tempMaxValue = diagLeft;
			if (straight > tempMaxValue) {
				tempMaxValue = straight;
			}
			if (diagRight > tempMaxValue){
				tempMaxValue = diagRight;
			}

			boardMax[i][j] = tempMaxValue + boardActual[i][j];
		}// end inner for loop
	} // end outer for loop


	// check the row with vaults for the largest total & setting results
	int tempMax = boardMax[0][0];
	int num = 1;
	for (int i = 1; i <= sizeBound; i++){
		if (boardMax[0][i] > tempMax) {
			tempMax = boardMax[0][i];
			num = i+1;
		}
	}
	total = tempMax;
	vaultNum = num;
	path[0] = vaultNum-1;
	cout << "total gems: " << total << endl;
	cout << "vault number: " << num << endl;

	//backtracking: finding path & starting square
	int backTrackCount = total;
	int column = vaultNum - 1;
	for (int i = 0; i <= sizeBound; i++){
		backTrackCount = backTrackCount - boardActual[i][column];

		if (column-1 >= 0){
			if (backTrackCount == boardMax[i+1][column-1]){
				column--;
			}
		}
		if (column+1 <= sizeBound){
			if (backTrackCount == boardMax[i+1][column+1]){
				column++;
			}
		}
		path[i+1] = column;
	}

	//printing results
	cout << "starting square: " << boardActual[7][path[7]] << endl;
	cout << "path: ";
	for (int i = 7; i >=0; i--) {
		int temp = boardActual[i][path[i]];
		cout << temp << " ";
	}
	cout << endl;

	return 0;
}
