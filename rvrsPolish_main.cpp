//Reverse polish notation for singke digit
//逆ポーランド記法
//日本語コメント後はから加えたモノです

#include <iostream> 
#include <stack> 
#include <string>
#include<vector>
#include<sstream>
#include <cstdlib>


//演算記号ならtrueを返却する
bool op(char b) {
	return b == '+' || b == '-' || b == '*' || b == '/';
}

//aが+か-だったらtrueを返却
bool prio(char a, char b) {
	if (a == '+' || a == '-') {
		return true;
	}
	if (b == '+' || b == '-') {
		return false;
	}
	return true;
}

double posfix(const std::string& expression) {

	double fst, scd, ans;
	std::stringstream postfString(expression);
	std::vector<double> temp;
	std::string schar;

	while (postfString >> schar) {
		if (op(schar[0])) {
			fst = temp.back();
			temp.pop_back();
			scd = temp.back();
			temp.pop_back();

			switch (schar[0]) {
			case '+': ans = scd + fst; break;
			case '-': ans = scd - fst; break;
			case '*': ans = scd * fst; break;
			case '/': ans = scd / fst; break; // check if fat !=0
			}

			temp.push_back(ans);
		}
		else {
			temp.push_back(std::stod(schar));
		}
	}
	return temp[0]; //last element is the answer
}

int main() {

	std::string siki;	//計算式
	std::string rpoli;	//逆ポーランドで格納
	std::stack<char> que;	//計算式内の演算記号を格納
	double ans;
	int cnt = 0;

	std::cout << "Please input one-digit formula" << "\n";
	std::cin >> siki;

	//計算式の長さ分ループ
	for (int i = 0; i<siki.size(); i++) {
		//演算記号じゃなかったら(数字だったら)
		if (op(siki[i]) == false) {
			//数字の数+1
			cnt++;
			//1つ目だったらそのまま入れる
			if (cnt == 1) {
				rpoli = siki[i];
			}
			//2つ目以降はスペースを入れてから入れる
			else {
				rpoli = rpoli + " " + siki[i];
			}
		}

		//演算記号だったら
		if (op(siki[i]) == true) {
			//演算記号格納用スタックが空、または、空でないかつそのスタックのトップが+か-だったら
			//そのスタックに演算記号を入れるだけ
			if (que.empty() || (que.empty() == false && prio(que.top(), siki[i]))) {
				que.push(siki[i]);
			}
			//それ以外なら
			else {
				//演算記号格納用スタックが空でない、かつ、そのトップが+またか-以外の記号の間だけループ
				while (que.empty() == false && prio(que.top(), siki[i]) == false) {
					//演算記号格納用スタックのトップの値を格納
					rpoli = rpoli + " " + que.top();
					//演算記号格納用スタックのトップの値(今格納した奴)を破棄
					que.pop();
				}
				//演算記号を入れる
				que.push(siki[i]);
			}
		}
	}

	while (que.empty() == false) {
		rpoli = rpoli + " " + que.top();
		que.pop();
	}

	std::cout << rpoli << std::endl;
	ans = posfix(rpoli);
	
	system( "PAUSE" );

	return 0;
}
