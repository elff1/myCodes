#include "server.h"
#include <time.h> 
#include <io.h>

int server::login(char *buf){
	//LOGIN user_name password
	//LOGIN\n发件人\n日期\n信箱\主题
	//发件人\n日期\n信箱\n附件名\n主题（0未读，1已读，2垃圾） （邮件列表文件格式）

	char user_name[30],password[30],temp[30];
	sscanf(buf,"%s%s%s",temp,user_name,password);

	FILE *fp,*f;
	fp=fopen("user_info.ini","r");
	if (fp==NULL)
	{
		cout<<"File open error!"<<endl;
		exit(0);
	}//打开记录用户名密码的文件

	char tn[30];//文件中读取的用户名
	char tp[30];//文件中读取的密码
	char sendbuf[Max_buf];//待发送内容
	//strcpy_s(sendbuf,"LOGIN\n\0");
	sendbuf[0] = 0;

	while (!feof(fp))
	{
		fscanf(fp,"%s%s",tn,tp);
		if (strcmp(tn,user_name)==0)
			if (strcmp(tp,password)==0)//该用户存在，返回其邮件列表
			{
				fclose(fp);
				strcat_s(user_name,".txt");
				f=fopen(user_name,"r");
				if(f==NULL){
					cout<<"File open error!";
					exit(0);
				}//打开邮件列表文件

				int i=strlen(sendbuf);
				while(!feof(f)) sendbuf[i++]=fgetc(f);
				i--;
				sendbuf[i]='\0';

				this->senddata(sendbuf);
				cout<<sendbuf<<endl;
				fclose(f); 
				return 1;
			}
	}  

	strcpy_s(sendbuf,"FAIL");
	this->senddata(sendbuf);
	cout<<sendbuf<<endl; 
	fclose(fp);
	return 0;
}


int judge_username(char *buf){
	int i;
	for (i=0;i<strlen(buf);i++) 
		if(!(buf[i]<91&&buf[i]>64||buf[i]<123&&buf[i]>96||buf[i]<58&&buf[i]>47)) return 0;
	return 1;
}


int server::sign_in(char *buf){
	//SIGN_IN user_name password
	//SIGN_IN\nFAIL  或者SIGN_IN\nDONE
	//用户名 密码（用户信息表格式）
	char user_name[30],password[30],temp[Max_buf],sendbuf[Max_buf];
	sscanf(buf,"%s%s%s",temp,user_name,password);//得到用户名密码，下一步检测用户名是否可用

	if (judge_username(user_name)==0)
	{
		strcpy_s(sendbuf,"SIGN_IN\nFAIL\0");
		senddata(sendbuf);
		return 1;
	}//判断用户名是否合法

	FILE *fp;
	char tn[30],tp[30];
	fp=fopen("user_info.ini","r+");
	while (!feof(fp))
	{
		fscanf(fp,"%s%s",tn,tp);
		if(strcmp(tn,user_name)==0){
			strcpy_s(sendbuf,"SIGN_IN\nFAIL\0");
			senddata(sendbuf);
			return 1;
		}
	}//判断用户名是否已经存在
	fseek(fp,0,SEEK_END);
	fprintf(fp,"%s %s\n",user_name,password);//写入新的用户名 密码

	strcpy_s(sendbuf,"SIGN_IN\nDONE\0");
	senddata(sendbuf);
	fclose(fp);

	strcat_s(user_name,".txt");//为新用户建立文件
	fp=fopen(user_name,"w");
	fclose(fp);

	return 1;
}


int server::check(char *buf){
	//CHECK user_name +from +datatime
	char user_name[30],from[30],datatime[30],temp[Max_buf],sendbuf[Max_buf];
	int boxNum;
	sscanf(buf,"%s%d%s%s%s",temp,&boxNum,user_name,from,datatime);

	//次数\n正文
	FILE *fp;
	char file_name[60];
	strcpy_s(file_name,from);
	strcat_s(file_name,"+");
	strcat_s(file_name,datatime);
	strcat_s(file_name,".ini\0");//得到正文文件名

	fp=fopen(file_name,"r");
	if(fp==NULL){
		cout<<"Error: cannot open file!"<<endl;
		exit(0);
	}
	
	int i;
	fscanf(fp,"%d",&i);
	i=0;
	while(fgetc(fp)!='\n');
	while (!feof(fp)) temp[i++]=fgetc(fp);
	i--;
	temp[i]='\0';  
	strcpy_s(sendbuf,"CHECK\n\0");
	strcat_s(sendbuf,temp);
	senddata(sendbuf);
	cout<<"the content is: "<<endl<<sendbuf<<endl;
	fclose(fp);//读出邮件正文并发送

	if(boxNum != 0)
		return 1;
	
	//发件人\n日期\n信箱\n主题
	FILE *f;//以下修改未读邮件为已读
	char sender_data[60],box[2];
	strcpy_s(file_name,user_name);
	strcat_s(file_name,".txt\0");
	f=fopen(file_name,"r+");
	
	i=0;
	while (!feof(f)) temp[i++]=fgetc(fp);
	i--;
	temp[i]='\0';  
	
	strcpy_s(sender_data,from);
	strcat_s(sender_data,"\n\0");
	strcat_s(sender_data,datatime);
	
	char *p1,*p2;
	p1=strstr(temp,sender_data);
	p2=p1+strlen(sender_data);
	
	if(*(p2+1)=='0') *(p2+1)='1';//未读修改为已读,垃圾邮件不变
	
	rewind(f);
	for (i=0;i<strlen(temp);i++)
	{
		fputc(temp[i],f);
	}
	fclose(f);
	return 1;
}


char *getsubstr(char *p1, char *p2){
	
	if(p2<=p1) return 0;

	int i=1;
	char *temp;
	temp=new char[p2-p1];
	for(i;p1+i<p2;i++) temp[i-1]=*(p1+i);
	temp[i-1]='\0';
	return temp;
}


char *setchar(char * buf, char a, char b){
	for (int i=0;i<strlen(buf);i++)
		if(buf[i]==a)	buf[i]=b;
	return buf;
}


int server::mail(char *buf){
	//  MAIL receiver sender (datatime) attachment topic text
	//拆分收件人
	char *reciever,*sender,*attachment,*topic,*text;
	char *p1,*p2,*p3,*p4,*p5,*p6;
	char tag[2],time[10],data[10],datatime[20];
	p1=strchr(buf,'\n');*p1=' ';
	p2=strchr(buf,'\n');*p2=' ';
	p3=strchr(buf,'\n');*p3=' ';
	p4=strchr(buf,'\n');*p4=' ';
	p5=strchr(buf,'\n');*p5=' ';
	p6=buf+strlen(buf);
	reciever=getsubstr(p1,p2);
	sender=getsubstr(p2,p3);
	attachment=getsubstr(p3,p4);
	topic=getsubstr(p4,p5);
	text=getsubstr(p5,p6);
	_strtime(time);
	_strdate(data);
	strcpy(datatime,data);
	strcat_s(datatime,"/\0");
	strcat_s(datatime,time);
	setchar(datatime,'/','-');
	setchar(datatime,':',';');
	strcpy_s(tag,"0\0");//得到收件人、发件人、日期、信箱、主题、正文


	FILE *fp;     
	char temp[30],file_name[40],buff[150],sendbuf[Max_buf];
	int i,j=0,NUM=0;

	strcpy(buff,sender);
	strcat_s(buff,"\n\0");
	strcat_s(buff,datatime);
	strcat_s(buff,"\n\0");
	strcat_s(buff,tag);
	strcat_s(buff,"\n\0");
	strcat_s(buff,attachment);
	strcat_s(buff,"\n\0");
	strcat_s(buff,topic);
	strcat_s(buff,"\n\0");//用户信箱中存放的数据，发件人、日期、tag、主题,用回车隔开

	strcpy_s(sendbuf,"SEND_MAIL\n\0");

	for (i=0;i<strlen(reciever);i++)//有多个收件人，分离收件人
	{
		if(reciever[i]==';'){
			temp[i-j]='\0';
			j=i+1;
			NUM++;//记录收件人个数，每得到一个收件人+1
			strcpy_s(file_name,temp);
			strcat_s(file_name,".txt");
			fp=fopen(file_name,"r+");
			if(fp==NULL){//收件人不存在
				strcat_s(sendbuf,"FAIL\0");
				senddata(sendbuf);
				return 0;
			}
			fseek(fp,0,SEEK_END);//文件指针移动到文件末尾
			for (int k=0;k<strlen(buff);k++)  fputc(buff[k],fp);//写入邮件内容文件中
			fclose(fp);
		}
		else temp[i-j]=reciever[i];
	}

	strcat_s(sendbuf,"DONE\0");
	senddata(sendbuf);

	//向正文文件中写数据
	strcpy_s(file_name,sender);
	strcat_s(file_name,"+");
	strcat_s(file_name,datatime);
	strcat_s(file_name,".ini");

	fp=fopen(file_name,"w");
	fprintf(fp,"%d\n",NUM);
	for (i=0;i<strlen(text);i++)  fputc(text[i],fp);//写入邮件内容文件中
	fclose(fp);//邮件列表中修改

	//修改附件引用次数
	if(attachment[0]!='0'){//有附件
		p1=strchr(attachment,';');
		p2=attachment+strlen(attachment);
		p3=getsubstr(p1,p2);//附件编号
		fp=fopen("att_info.ini","r+");
		int a,b,c;
		c=atoi(p3);
		while(!feof(fp)){
			fscanf(fp,"%d %d",&a,&b);
			if(a==c){
				fseek(fp,-2,SEEK_CUR);
				fputs("  ",fp);
				fseek(fp,-2,SEEK_CUR);
				fprintf(fp,"%d",NUM);
				fclose(fp);
				break;
			}
		}
	}
	//修改邮件列表中发件箱内容
	strcpy_s(file_name,sender);
	strcat_s(file_name,".txt\0");
	fp=fopen(file_name,"r+");
	fseek(fp,0,SEEK_END);
	fprintf(fp,"%s",reciever);
	fputc('\n',fp);
	fprintf(fp,"%s",datatime);
	fputc('\n',fp);
	fprintf(fp,"%s","4\0");
	fputc('\n',fp);
	fprintf(fp,"%s",attachment);
	fputc('\n',fp);
	fprintf(fp,"%s",topic);
	fputc('\n',fp);
	fclose(fp);
	return 0;
}


int digit_num(int a){
	int n=1;
	a/=10;
	while(a){
		n++;
		a/=10;
	}
	return n;
}


int server::delete_mail(char *buf){
	//DELETE flag username from datatime attachment_code
	//from time box attachment topic
	//number text

	char temp[Max_buf],username[30],from[30],datatime[30],atta[30],ff[2];
	int boxNo;
	int flag;//flag ==1  totally delete

	for(int i = 0; i < 30; i++) atta[i] = '\0';
	sscanf(buf,"%s%s%s%d%s%s",temp,ff,username,&boxNo,datatime,atta);
	flag=ff[0]-'0';
	setchar(datatime,'/','-');
	setchar(datatime,':',';');
	//修改信箱
	char file_name[50];
	FILE *fp;
	int i=0;
	strcpy_s(file_name,username);
	strcat_s(file_name,".txt");
	fp=fopen(file_name,"r+");
	while(!feof(fp)) temp[i++]=fgetc(fp);
	i--;
	temp[i]='\0';
	char *p1,*p2;
	p1=strstr(temp,datatime);
	p2=p1+strlen(datatime);
	if(flag) *(p2+1)='3';
	else *(p2+1)='2';

	rewind(fp);
	for (i=0;i<strlen(temp);i++) fputc(temp[i],fp);
	fclose(fp);

	////修改引用次数,彻底删除时才修改
	//if(flag){
	//	strcpy_s(file_name,from);
	//	strcat_s(file_name,"+");
	//	strcat_s(file_name,datatime);
	//	strcat_s(file_name,".ini");
	//	fp=fopen(file_name,"r+");

	//	int num,digit_n;
	//	fscanf(fp,"%d",&num);
	//	digit_n=digit_num(num);
	//	rewind(fp);
	//	num--;
	//	if(!num)	{
	//		fclose(fp);
	//		strcpy_s(temp,file_name);
	//		strcpy_s(file_name,"del ");
	//		strcat_s(file_name,temp);
	//		system(file_name);
	//	}
	//	else {
	//		for(i=0;i<digit_n;i++) fputc(' ',fp);
	//		rewind(fp);
	//		fprintf(fp,"%d",num);
	//		fclose(fp);
	//	}
	//}
	//以下进行删除附件
	if(atta != ""){
		int attid,innum,tmp=0;
		FILE *f;
		for(i=0;i<9;i++) tmp=tmp*10+atta[i]-'0';
		fp=fopen("att_info.ini","r+");
		while (!feof(fp))
		{
			int n=1;
			fscanf(fp,"%d%d",&attid,&innum);
			n+=digit_num(attid);
			n+=digit_num(innum);
			if(attid==tmp){
				innum--;
				if(innum==0){
					fseek(fp,0-n,SEEK_CUR);
					for(i=0;i<n;i++) fputc(' ',fp);
					fclose(fp);
					strcpy_s(file_name,"del ");
					strcat_s(file_name,atta);
					system(file_name);
				}
				else if(flag){//彻底删除改变引用次数
					fseek(fp,0-n,SEEK_CUR);
					for(i=0;i<n;i++) fputc(' ',fp);
					fseek(fp,0-n,SEEK_CUR);
					fprintf(fp,"%d %d",attid,innum);
					fclose(fp);
					break;
				}
			}
		}
	}
	char sendbuf[Max_buf];
	strcpy_s(sendbuf,"DELETE DONE");
	senddata(sendbuf);
	return 0;

}


int file_exists(char *filename) 
{
	//判断文件是否存在
	return (access(filename, 0) == 0); //1存在
}


int server::attachment(char *buf){
	//发送附件
	int attid=0;//初始化附件id
	FILE *fat,*fatt;
	char *buff;
	char attname[15];
	char sendbuf[Max_buf];//待发送内容
	int eattid,eattnum,mattid,ininum;
	ininum=-1;//邮件未发送时，引用次数为-1
	if(file_exists("att_info.ini")){
		//非第一次发附件
		fat=fopen("att_info.ini","r+");//记录附件ID与引用次数
		mattid=0;//存最大附件id
		while(!feof(fat)){
			fscanf(fat,"%d %d",&eattid,&eattnum);
			if(mattid<=eattid)
				mattid=eattid;//找到已存在的最大id
		}
		attid=mattid+1;//设置当前附件id
		while(!feof(fat)) fgetc(fat);
		fprintf(fat,"%d %d\n",attid,ininum);//加入附件列表
		fclose(fat);
	}
	else{
		//全服第一次发附件
		fat=fopen("att_info.ini","w");
		fprintf(fat,"%d %d\n",attid,ininum);//写入第一个附件名
		fclose(fat);
	}
	attname[0]=(char)(attid/100000000)%10+48;
	attname[1]=(char)(attid/10000000)%10+48;
	attname[2]=(char)(attid/1000000)%10+48;
	attname[3]=(char)(attid/100000)%10+48;
	attname[4]=(char)(attid/10000)%10+48;
	attname[5]=(char)(attid/1000)%10+48;
	attname[6]=(char)(attid/100)%10+48;
	attname[7]=(char)(attid/10)%10+48;
	attname[8]=(char)attid%10+48;
	attname[9]='\0';
	//附件ID转换为字符串
	fatt=fopen(attname,"w");//存储附件
	buff=getsubstr(buf+10,buf+strlen(buf));
	fprintf(fatt,buff);
	fclose(fatt);
	//strcpy_s(sendbuf,"ATTID\n\0");
	strcpy_s(sendbuf,attname);//返回文件ID的字符串格式
	senddata(sendbuf);
	
	return 0;
}


int server::download(char *buf){
	char attnam[10],temp[10];
	char data[Max_buf-40];//读取附件
	char sendbuf[Max_buf];//待发送内容
	int i;
	FILE *fatta;
	i=0;
	sscanf(buf,"%s%s",temp,attnam);//获取附件名
	fatta=fopen(attnam,"r");
	if(fatta==NULL){
		//处理未找到
		strcpy_s(sendbuf,"Attach\n\0");
		strcat_s(sendbuf,"Not found!!!\n\0");
		senddata(sendbuf);
		return 0;
	}
	strcpy_s(sendbuf,"Contents\n\0");
	//strcat_s(sendbuf,attnam);
	//strcat_s(sendbuf,"\n\0");
	while (!feof(fatta))
		data[i++]=fgetc(fatta);
	//读取附件内容
	i--;
	data[i]='\0';
	fclose(fatta);
	strcat_s(sendbuf,data);
	senddata(sendbuf);

	return 0;
}


int server::modify(char *buf){
	char user_name[30],password[30],newpass[30],newpass1[30],temp[30];
	sscanf(buf,"%s%s%s%s%s",temp,user_name,password,newpass,newpass1);

	FILE *fp,*f,*ft;
	fp=fopen("user_info.ini","r");
	ft=fopen("user_info_temp.txt","w");//准备替换的用户信息
	if (fp==NULL)
	{
		cout<<"File open error!"<<endl;
		exit(0);
	}//打开记录用户名密码的文件

	int flag;
	char tn[30];//文件中读取的用户名
	char tp[30];//文件中读取的密码
	char sendbuf[Max_buf];//待发送内容
	strcpy_s(sendbuf,"LOGIN\n\0");

	if (strcmp(newpass,newpass1)==0){//两次确认新密码一致
		fscanf(fp,"%s%s",tn,tp);
		while (!feof(fp))//寻找原来的信息
		{
			flag=0;
			if (strcmp(tn,user_name)==0){
				if (strcmp(tp,password)==0)
				{	//该用户存在且旧密码正确
					fprintf(ft,user_name);
					fprintf(ft," ");
					fprintf(ft,newpass);
					fprintf(ft,"\n");
					//写入新信息
					flag=1;
				}
				else{
					//旧密码输入有误
					fclose(fp);
					fclose(ft);
					cout<<"wrong password!"<<endl;
					unlink("user_info_temp.txt");//取消新信息表
					return 0;
				}
			}
			if(flag==0){
				fprintf(ft,tn);
				fprintf(ft," ");
				fprintf(ft,tp);
				fprintf(ft,"\n");
			}//照抄旧信息到新表中
			fscanf(fp,"%s%s",tn,tp);
		}
		fclose(ft);
		fclose(fp);
		unlink("user_info.ini");//删除旧信息
		rename("user_info_temp.txt","user_info.ini");//替换为新的用户信息表
		strcpy_s(sendbuf,"SUCCESS\n\0");
		senddata(sendbuf);
		return 1;
	}  
	else{
		cout<<"please check the new password!"<<endl;//两次密码不一致
	}
	strcpy_s(sendbuf,"FAIL\n\0");
	this->senddata(sendbuf);
	cout<<sendbuf<<endl; 
	fclose(fp);
	fclose(ft);
	unlink("user_info_temp.txt");//取消修改
	senddata(sendbuf);

	return 0;
}

