#include <stdio.h>
#include <algorithm>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int nd, nw, nk;
int nRet;
int nfilm[14][21];

int fnInspect()
{
	int result = 1;
	int pre_value = 0;
	int crt_value = 0;
	int count_k = 0;

	for (int i = 0; i < nw; i++){
		pre_value = nfilm[0][i];
		result = 1;
		count_k = 1;
		for (int j = 1; j < nd; j++){
			crt_value = nfilm[j][i];
			if (pre_value == crt_value){
				count_k++;
			}
			else{
				count_k = 1;
			}

			if (count_k == nk){
				result = 0;
				break;
			}
			pre_value = crt_value;
		}
		if (result)
			break;
	}

	return (result + 1) % 2; //성공하면 1반환
}

void fnInsert(int type, int layer)
{
	for (int i = 0; i < nw; i++){
		nfilm[layer][i] = type;
	}
}

void fnCopyFlim(int flim[21], int copy_flim[21])
{
	for (int i = 0; i < nw; i++){
		copy_flim[i] = flim[i];
	}
}

void dfs(int count_num, int layer)
{
	if (count_num >= nRet || layer == (nd + 1))
		return;
	
	if (layer == nd){
		if (fnInspect()){
			nRet = min(nRet, count_num);
			return;
		}
	}
	dfs(count_num, layer + 1); // 약품x

	int nCopy_Film[21];
	fnCopyFlim(nfilm[layer], nCopy_Film);
	fnInsert(0,layer); //빨간색 약품 투입.
	dfs(count_num + 1, layer + 1);

	fnInsert(1, layer); //파란색 약품 투입.
	dfs(count_num + 1, layer + 1);
	fnCopyFlim(nCopy_Film, nfilm[layer]);
}

int main()  //복잡도 3^13*13*20
{
	int t;
	int test_case;

	freopen("sample_input.txt", "r", stdin);

	scanf("%d", &t);

	for (test_case = 1; test_case <= t; ++test_case)
	{
		scanf("%d %d %d", &nd, &nw, &nk);

		for (int i = 0; i < nd; i++){
			for (int j = 0; j < nw; j++){
				scanf("%d", &nfilm[i][j]);
			}
		}
		nRet = 21;
		dfs(0,0);
		printf("#%d %d\n", test_case, nRet);

	}
}