﻿#include"ecc.cpp"

// テーブルサイズ
#define Table_Num 100

// 事前計算用の配列
E_Point P,Q;
E_Point pre_R[Table_Num];
INT64 pre_A[Table_Num], pre_B[Table_Num];

//データベースを検索し、無ければ挿入する関数
bool FindThenSetData(std::string x,std::string a,std::string b,CMysql *mysql){
	string ret_a, ret_b;
	mysql->GetData(ret_a,ret_b,x);

	if(ret_a.empty() || ret_b.empty()){
		mysql->SetData(x,a,b);	// 見つからなかったらデータを登録
		return false;		// 検索できず
	}else return true;		// すでに登録されているなら攻撃成功
}

//事前計算テーブル作成関数
int Precomputation(CMysql *con){
	E_Point tmp, tmp_P, tmp_Q;
	INT64 A, B;
	int i=0;
	char str[MAX];
	string ret_a, ret_b, ret_x;
	srand((INT64)time(NULL));

	while(i<Table_Num){
		/*=====課題ex6_1 (start)===============*/

		//(1)AとBにランダムな数を代入しよう！
		A = (INT64)rand() % Order;
		B = (INT64)rand() % Order;

		//(2)R=[A]P+[B]Qを求めよう！
		SCM(&tmp_P,A,P);
		SCM(&tmp_Q,B,Q);
		ECA(&tmp,tmp_P,tmp_Q);

		//(3)配列（pre_R[],pre_A[],pre_B[]）に登録しよう！
		//注意　pre_R[]の型はE_Pointである
		pre_A[i] = A;
		pre_B[i] = B;
		pre_R[i].x = tmp.x;
		pre_R[i].y = tmp.y;
		pre_R[i].flag = tmp.flag;

		/*=====課題ex6_1 (finish)===============*/
		i++;
	}
	return 1;
}

//ランダムウォーク関数
int Random_Walk(CMysql *con){
	E_Point R, _R, tmp, tmp_P, tmp_Q;
	INT64 A, B, _A, _B;// _X, _A, _Bは一つ前のデータ
	char str[MAX];
	string ret_a, ret_b, ret_x;
	string col_a, col_b;

	srand((INT64)time(NULL));

	/*=====課題ex6_2 (start)===============*/

	//(1)初期点用に_A,_Bにランダムな数をセットし,_Rを計算しよう！(flagも忘れないように注意！)
	_A = (INT64)rand() % Order;
	_B = (INT64)rand() % Order;
	SCM(&tmp_P,_A,P);
	SCM(&tmp_Q,_B,Q);
	ECA(&tmp,tmp_P,tmp_Q);
	_R.x = tmp.x;
	_R.y = tmp.y;
	_R.flag = tmp.flag;

	//(2)生成した座標をmySQLに登録をしよう！
	sprintf(str,"%lld",_A); ret_a = str;
	sprintf(str,"%lld",_B); ret_b = str;
	sprintf(str,"%lld",_R.x); ret_x = str;

	con -> SetData(ret_x,ret_a,ret_b);
	printf("(X,A,B)=(%lld,%lld,%lld)\n",_R.x,_A,_B);

	//(3)衝突するまで_Aとpre_A[]から次のAを求めよう!　同様にB,Rを求めよう！
	//HINT AとBは通常の加算、Rは楕円加算
	while(1){
		A = (_A + pre_A[_R.x % Table_Num]) % Order;
		B = (_B + pre_B[_R.x % Table_Num]) % Order;
		ECA(&R,_R,pre_R[_R.x % Table_Num]);

		sprintf(str,"%lld",A); ret_a = str;
		sprintf(str,"%lld",B); ret_b = str;
		sprintf(str,"%lld",R.x); ret_x = str;

		if(FindThenSetData(ret_x,ret_a,ret_b,con)){
			printf("collision occur\n");
			printf("(X,A,B)=(%lld,%lld,%lld)\n",R.x,A,B);
			break;
		}else{
			printf("(X,A,B)=(%lld,%lld,%lld)\n",R.x,A,B);
		}
		_A = A;
		_B = B;
		_R.x = R.x;
		_R.y = R.y;
		_R.flag = R.flag;
	}

	/*=====課題ex6_2 (finish)===============*/
	return 1;
}

int main(int argc,char *argv[]){
	CMysql mysql=new CMysql(1);

	// Problem();

	Prime=75223; Order=74929; Constant_B=7;
	P.x=4036; P.y=44304; P.flag=0;
	Q.x=5324; Q.y=7468; Q.flag=0;

	Precomputation(&mysql);
	Random_Walk(&mysql);      //ランダムウォーク
}

/*example
Prime=75223, Order=74929, Constant_B=7
P(4036,44304)
Q(5324,7468)
(Secret scalar d is 64070)

Prime=1706311, Order=1704961, Constant_B=3
P(452031,899373)
Q(1640115,849217)
(Secret scalar d is 682772)
*/
