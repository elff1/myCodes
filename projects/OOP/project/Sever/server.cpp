#include "server.h"
#include <time.h> 
#include <io.h>

int server::login(char *buf){
	//LOGIN user_name password
	//LOGIN\n������\n����\n����\����
	//������\n����\n����\n������\n���⣨0δ����1�Ѷ���2������ ���ʼ��б��ļ���ʽ��

	char user_name[30],password[30],temp[30];
	sscanf(buf,"%s%s%s",temp,user_name,password);

	FILE *fp,*f;
	fp=fopen("user_info.ini","r");
	if (fp==NULL)
	{
		cout<<"File open error!"<<endl;
		exit(0);
	}//�򿪼�¼�û���������ļ�

	char tn[30];//�ļ��ж�ȡ���û���
	char tp[30];//�ļ��ж�ȡ������
	char sendbuf[Max_buf];//����������
	//strcpy_s(sendbuf,"LOGIN\n\0");
	sendbuf[0] = 0;

	while (!feof(fp))
	{
		fscanf(fp,"%s%s",tn,tp);
		if (strcmp(tn,user_name)==0)
			if (strcmp(tp,password)==0)//���û����ڣ��������ʼ��б�
			{
				fclose(fp);
				strcat_s(user_name,".txt");
				f=fopen(user_name,"r");
				if(f==NULL){
					cout<<"File open error!";
					exit(0);
				}//���ʼ��б��ļ�

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
	//SIGN_IN\nFAIL  ����SIGN_IN\nDONE
	//�û��� ���루�û���Ϣ���ʽ��
	char user_name[30],password[30],temp[Max_buf],sendbuf[Max_buf];
	sscanf(buf,"%s%s%s",temp,user_name,password);//�õ��û������룬��һ������û����Ƿ����

	if (judge_username(user_name)==0)
	{
		strcpy_s(sendbuf,"SIGN_IN\nFAIL\0");
		senddata(sendbuf);
		return 1;
	}//�ж��û����Ƿ�Ϸ�

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
	}//�ж��û����Ƿ��Ѿ�����
	fseek(fp,0,SEEK_END);
	fprintf(fp,"%s %s\n",user_name,password);//д���µ��û��� ����

	strcpy_s(sendbuf,"SIGN_IN\nDONE\0");
	senddata(sendbuf);
	fclose(fp);

	strcat_s(user_name,".txt");//Ϊ���û������ļ�
	fp=fopen(user_name,"w");
	fclose(fp);

	return 1;
}


int server::check(char *buf){
	//CHECK user_name +from +datatime
	char user_name[30],from[30],datatime[30],temp[Max_buf],sendbuf[Max_buf];
	int boxNum;
	sscanf(buf,"%s%d%s%s%s",temp,&boxNum,user_name,from,datatime);

	//����\n����
	FILE *fp;
	char file_name[60];
	strcpy_s(file_name,from);
	strcat_s(file_name,"+");
	strcat_s(file_name,datatime);
	strcat_s(file_name,".ini\0");//�õ������ļ���

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
	fclose(fp);//�����ʼ����Ĳ�����

	if(boxNum != 0)
		return 1;
	
	//������\n����\n����\n����
	FILE *f;//�����޸�δ���ʼ�Ϊ�Ѷ�
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
	
	if(*(p2+1)=='0') *(p2+1)='1';//δ���޸�Ϊ�Ѷ�,�����ʼ�����
	
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
	//����ռ���
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
	strcpy_s(tag,"0\0");//�õ��ռ��ˡ������ˡ����ڡ����䡢���⡢����


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
	strcat_s(buff,"\n\0");//�û������д�ŵ����ݣ������ˡ����ڡ�tag������,�ûس�����

	strcpy_s(sendbuf,"SEND_MAIL\n\0");

	for (i=0;i<strlen(reciever);i++)//�ж���ռ��ˣ������ռ���
	{
		if(reciever[i]==';'){
			temp[i-j]='\0';
			j=i+1;
			NUM++;//��¼�ռ��˸�����ÿ�õ�һ���ռ���+1
			strcpy_s(file_name,temp);
			strcat_s(file_name,".txt");
			fp=fopen(file_name,"r+");
			if(fp==NULL){//�ռ��˲�����
				strcat_s(sendbuf,"FAIL\0");
				senddata(sendbuf);
				return 0;
			}
			fseek(fp,0,SEEK_END);//�ļ�ָ���ƶ����ļ�ĩβ
			for (int k=0;k<strlen(buff);k++)  fputc(buff[k],fp);//д���ʼ������ļ���
			fclose(fp);
		}
		else temp[i-j]=reciever[i];
	}

	strcat_s(sendbuf,"DONE\0");
	senddata(sendbuf);

	//�������ļ���д����
	strcpy_s(file_name,sender);
	strcat_s(file_name,"+");
	strcat_s(file_name,datatime);
	strcat_s(file_name,".ini");

	fp=fopen(file_name,"w");
	fprintf(fp,"%d\n",NUM);
	for (i=0;i<strlen(text);i++)  fputc(text[i],fp);//д���ʼ������ļ���
	fclose(fp);//�ʼ��б����޸�

	//�޸ĸ������ô���
	if(attachment[0]!='0'){//�и���
		p1=strchr(attachment,';');
		p2=attachment+strlen(attachment);
		p3=getsubstr(p1,p2);//�������
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
	//�޸��ʼ��б��з���������
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
	//�޸�����
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

	////�޸����ô���,����ɾ��ʱ���޸�
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
	//���½���ɾ������
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
				else if(flag){//����ɾ���ı����ô���
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
	//�ж��ļ��Ƿ����
	return (access(filename, 0) == 0); //1����
}


int server::attachment(char *buf){
	//���͸���
	int attid=0;//��ʼ������id
	FILE *fat,*fatt;
	char *buff;
	char attname[15];
	char sendbuf[Max_buf];//����������
	int eattid,eattnum,mattid,ininum;
	ininum=-1;//�ʼ�δ����ʱ�����ô���Ϊ-1
	if(file_exists("att_info.ini")){
		//�ǵ�һ�η�����
		fat=fopen("att_info.ini","r+");//��¼����ID�����ô���
		mattid=0;//����󸽼�id
		while(!feof(fat)){
			fscanf(fat,"%d %d",&eattid,&eattnum);
			if(mattid<=eattid)
				mattid=eattid;//�ҵ��Ѵ��ڵ����id
		}
		attid=mattid+1;//���õ�ǰ����id
		while(!feof(fat)) fgetc(fat);
		fprintf(fat,"%d %d\n",attid,ininum);//���븽���б�
		fclose(fat);
	}
	else{
		//ȫ����һ�η�����
		fat=fopen("att_info.ini","w");
		fprintf(fat,"%d %d\n",attid,ininum);//д���һ��������
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
	//����IDת��Ϊ�ַ���
	fatt=fopen(attname,"w");//�洢����
	buff=getsubstr(buf+10,buf+strlen(buf));
	fprintf(fatt,buff);
	fclose(fatt);
	//strcpy_s(sendbuf,"ATTID\n\0");
	strcpy_s(sendbuf,attname);//�����ļ�ID���ַ�����ʽ
	senddata(sendbuf);
	
	return 0;
}


int server::download(char *buf){
	char attnam[10],temp[10];
	char data[Max_buf-40];//��ȡ����
	char sendbuf[Max_buf];//����������
	int i;
	FILE *fatta;
	i=0;
	sscanf(buf,"%s%s",temp,attnam);//��ȡ������
	fatta=fopen(attnam,"r");
	if(fatta==NULL){
		//����δ�ҵ�
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
	//��ȡ��������
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
	ft=fopen("user_info_temp.txt","w");//׼���滻���û���Ϣ
	if (fp==NULL)
	{
		cout<<"File open error!"<<endl;
		exit(0);
	}//�򿪼�¼�û���������ļ�

	int flag;
	char tn[30];//�ļ��ж�ȡ���û���
	char tp[30];//�ļ��ж�ȡ������
	char sendbuf[Max_buf];//����������
	strcpy_s(sendbuf,"LOGIN\n\0");

	if (strcmp(newpass,newpass1)==0){//����ȷ��������һ��
		fscanf(fp,"%s%s",tn,tp);
		while (!feof(fp))//Ѱ��ԭ������Ϣ
		{
			flag=0;
			if (strcmp(tn,user_name)==0){
				if (strcmp(tp,password)==0)
				{	//���û������Ҿ�������ȷ
					fprintf(ft,user_name);
					fprintf(ft," ");
					fprintf(ft,newpass);
					fprintf(ft,"\n");
					//д������Ϣ
					flag=1;
				}
				else{
					//��������������
					fclose(fp);
					fclose(ft);
					cout<<"wrong password!"<<endl;
					unlink("user_info_temp.txt");//ȡ������Ϣ��
					return 0;
				}
			}
			if(flag==0){
				fprintf(ft,tn);
				fprintf(ft," ");
				fprintf(ft,tp);
				fprintf(ft,"\n");
			}//�ճ�����Ϣ���±���
			fscanf(fp,"%s%s",tn,tp);
		}
		fclose(ft);
		fclose(fp);
		unlink("user_info.ini");//ɾ������Ϣ
		rename("user_info_temp.txt","user_info.ini");//�滻Ϊ�µ��û���Ϣ��
		strcpy_s(sendbuf,"SUCCESS\n\0");
		senddata(sendbuf);
		return 1;
	}  
	else{
		cout<<"please check the new password!"<<endl;//�������벻һ��
	}
	strcpy_s(sendbuf,"FAIL\n\0");
	this->senddata(sendbuf);
	cout<<sendbuf<<endl; 
	fclose(fp);
	fclose(ft);
	unlink("user_info_temp.txt");//ȡ���޸�
	senddata(sendbuf);

	return 0;
}

