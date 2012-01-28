#include "server.h"

int main(){
	server s;
	char recvbuf[Max_buf];
	while(1){
		int i;
		for (i=0;i<Max_buf;i++)	recvbuf[i]='\0';
		s.AcceptConnect();
		s.recvdata(recvbuf);
		string st(recvbuf);
		cout<< "Client asking.... "<< recvbuf <<endl;
		if	   (st.find("LOGIN")==0) s.login(recvbuf);
		else if(st.find("MAIL")==0) s.mail(recvbuf);
		else if(st.find("CHECK")==0) s.check(recvbuf);
		else if(st.find("SIGN_IN")==0) s.sign_in(recvbuf);
		else if(st.find("DELETE")==0) s.delete_mail(recvbuf);
		else if(st.find("ATTACHMENT")==0) s.attachment(recvbuf);
		else if(st.find("DOWNLOAD")==0) s.download(recvbuf);
		else if(st.find("MODIFY")==0) s.modify(recvbuf);
		else cout<<"No such ask!!!"<<endl;
	}
	//strcpy_s(recvbuf,"CHECK 000 sender 2010");
	//s.attachment(recvbuf);
	//strcpy_s(recvbuf,"SIGN_IN\n000;222;\n111\natta;000000001\nfine weather?\n today i eat an apple\n i fell godd!!!\0");
	strcpy_s(recvbuf,"CHECK 000 222");
	//strcpy_s(recvbuf,"LONGIN 1 000 222 2010 000000001");
	//s.mail(recvbuf);
	//s.sign_in(recvbuf);
	s.login(recvbuf);
	system("pause");
	return 0;
}