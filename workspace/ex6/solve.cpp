#include"ecc.cpp"
E_Point P, Q, R;

int main(void){
	INT64 a[2],b[2];
	INT64 dA,dB,ans,inv_dB;

	Prime=75223; Order=74929; Constant_B=7;
	P.x=4036; P.y=44304; P.flag=0;
	Q.x=5324; Q.y=7468; Q.flag=0;

	a[0]=47866; b[0]=35197;
	a[1]=14567; b[1]=33845;

	dA=(Order+a[0]-a[1]) % Order;
	dB=(Order+b[1]-b[0]) % Order;
	inv_dB=Invert(dB,Order);
	ans=(dA*inv_dB) % Order;
	printf("s=%lld\n",ans);
	SCM(&R,ans,P);
	printf("[s]P=%lld,%lld,%d\n",R.x,R.y,R.flag);

	dA=(Order+a[0]+a[1]) % Order;
	dB=(2*Order-b[1]-b[0]) % Order;
	inv_dB=Invert(dB,Order);
	ans=(dA*inv_dB) % Order;
	printf("s=%lld\n",ans);
	SCM(&R,ans,P);
	printf("[s]P=%lld,%lld,%d\n",R.x,R.y,R.flag);
}
