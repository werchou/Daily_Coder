#include<iostream>
#include<algorithm>
#include<set>
#include<vector>

using namespace std;

//索引数组
static vector< vector<int> > SNum = { {}, {2,3,5,6,7,8,9,0},{4,5,6,8,9,0},{1,2,3,7,8,9,0},{2,3,4,5,6,8,9},
{2,6,8,0},{1,3,4,5,6,7,8,9,0},{2,3,5,6,8,9,0} };

class group {
public:
	int K, N;
	vector< vector<int> > data;

	group(int k, int n);
	void Adddata();
};

group::group(int k, int n) {
	K = k;
	N = n;
}
//给测试组添加数据
void group::Adddata() {
	for (int i = 0; i < K; i++)
	{
		vector<int> temp;
		int tempnum;
		char c;
		while ((cin >> tempnum).get(c))
		{
			//添加的数字不能重复，在1-7之间
			if (find(temp.begin(), temp.end(), tempnum) == temp.end()&&tempnum>0&&tempnum<8) {
				temp.push_back(tempnum);
			}
			else
			{
				cout << "错误" << endl;
				return;
			}
			if (c == '\n')
			{
				break;
				
			}
		}
		sort(temp.begin(), temp.end());
		//吧每个数码管的点亮二极管数据存起来
		data.push_back(temp);
	}
	
}

//求每个数码管可能表示的数字
vector<int> Unite_Data(vector<int> d) {
	vector<int> temp_unite=SNum[d[0]];
	vector<int>::iterator it;
	int s = d.size();
	//对于每一个数码管内已经点亮的二极管，求每个二极管编号对应索引数组的交集，就是该数码管可以表示的数字
	for (auto i = 0; i < s; i++)
	{
		sort(SNum[d[i]].begin(), SNum[d[i]].end());
		sort(temp_unite.begin(), temp_unite.end());
		
		
		it=set_intersection(temp_unite.begin(), temp_unite.end(), SNum[d[i]].begin(), SNum[d[i]].end(), temp_unite.begin());

		temp_unite.resize(it - temp_unite.begin());
	}
	return temp_unite;
}

//问题求解，<N 的个数
int func(group g) {
	int count=0;
	vector< vector<int> > V_unite;
	int sum_c = 1;

	//计算每个数码管可以表示的数字，存在V_unite中
	for (int i = 0; i < g.K; i++)
	{
		vector<int> te = Unite_Data(g.data[i]);
		V_unite.push_back(te);
	}
	//求第二个数码管中每个数字对应的可能数，从第三个数码管开始求
	for (int s = 2; s < V_unite.size(); s++)
	{
		sum_c *= V_unite[s].size();

	}
	//如果第一个数码管不能表示0
	if (find(V_unite[0].begin(), V_unite[0].end(), 0)==V_unite[0].end())
	{
		count = 0;
		return count;
	}
	else
		//如果只有一个数码管，那么只对该数码管内的数字进行求解
		if (V_unite.size() == 1)
		{
			for (auto c: V_unite[0])
			{
				if (c<g.N)
				{
					count++;
				}
			}
			return count;
		}
		//若数码管个数大于2，第二个数码管内数字*对应的阶数，判断和N的关系
		else
		{
			for (int j=0;j<V_unite[1].size(); j++)
			{
				int pj = pow(10, g.K - 2);
				int nj = pj*V_unite[1][j];
				if (nj<g.N)
				{
					count += sum_c;
				}
			}
		}
	return count;
}


int main() {
	vector<group> g;
	int num;
	cin >> num;
	int i = 1;
	while (num--)
	{
		int k, n;
		cin >> k >> n;
		group gtemp(k, n);
		gtemp.Adddata();
		cout << func(gtemp) << endl;
		
	}
	system("pause");
	return 0;
}


