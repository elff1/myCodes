#include "FastFourier.h"
//#include <Magick++.h>
//using namespace Magick;
FastFourier::FastFourier(){
	
}

FastFourier::~FastFourier(){
	
}
sound_sequence* FastFourier::transform(string filename,int * size, int* index){
	FILE *fp;
	BYTE ID[16];
	if((fp=fopen(filename.c_str(),"rb"))==NULL) {
		cout<<"No file found..."<<endl;
		return NULL;
	}
	fseek(fp,16,SEEK_SET);
	fread(size,1,4,fp);
	//////�ж�format ����16����18�ֽ�
	if(*size==16) fseek(fp,16,SEEK_CUR);
	else if(*size==18) fseek(fp,18,SEEK_CUR);
	cout<<"size =="<<*size<<endl;
	fread(ID,1,4,fp);
	//cout<<"ID== "<<ID<<endl;
	if(ID[0]=='f') fread(ID,12,1,fp);
	fread(size,1,4,fp);
	*size=*size-(*size)%400;
	printf("data size=%d\n",*size);                                           
	//system("pause");           
	
	double time=(*size)*1.0/8000;	
	printf("time=%lf\n",time);
	////////////////////////////////
	BYTE *data=new BYTE[*size];
	/////////////��ȡ���ݵ�data��
	memset(data,0,*size);
	fread(data,1,*size,fp);
	fclose(fp); 
	int i_i=0;//��¼��ǰ����������ݣ�ÿ400������һ�θ���Ҷ�任����һ��
	sound_sequence *outGraph=new sound_sequence[(*size/400) *8];  
	int o_count=0;
	float curr_amplitude[201];
	float pre_amplitude[201]; 
	memset(pre_amplitude,0,sizeof(float)*201);
	memset(curr_amplitude,0,sizeof(float)*201);
	 
	(*index)=0;
	for(int j=0;j<*size/400;j++){//ÿ400������һ�α任  
		fftw_plan p;
		double *in=(double *) fftw_malloc(sizeof(double)*400);
		fftw_complex *out=(fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 201);
		p=fftw_plan_dft_r2c_1d(400,in, out,  FFTW_ESTIMATE);

		for(int i=0;i<400;i++){
			in[i]= (double)data[i_i++];
		}
		////////////////////// 
		fftw_execute(p); // repeat as needed//
		fftw_destroy_plan(p); 
		//////////////////////
		float maxa=0,max=0,maxf_inc=0,max_inc=0;
		int maxf=0;

		int flag; 
		int point;
		for (int len=0;len<8;len++)
		{ 
			//��¼��ǰƬ�����������
			int max_am=0;
			outGraph[*index].time=j*1.0*400/8000;
			for(int i=0;i<25;i++){ 
				point = len*25+i;  
				//�������Ƶ��
				if (point<6)
				{
					continue;
				}
				curr_amplitude[point]=sqrt(abs(out[point][0])*abs(out[point][0])+abs(out[point][1])*abs(out[point][1]));
				if (curr_amplitude[point]> curr_amplitude[max_am])
				{
					max_am = point ; 
				}	
			}
			//��������̫�͵ĵ�
			if (curr_amplitude[max_am]<60)
			{
				continue;
			}

			//���˵������ǰһ֡��ͬƵ�ʵ�����û�д�������������Ǽ����Ըõ�
			if (curr_amplitude[max_am]<pre_amplitude[max_am])
			{
				continue;
			}
			if (curr_amplitude[max_am]<curr_amplitude[max_am-1]*2||curr_amplitude[max_am]<curr_amplitude[max_am+1]*2)
			{
				continue;
			}
			float sum_am=0;
			for(int k=0;k<200;k++){
				sum_am +=pre_amplitude[k];
			}
			if (sum_am/200>curr_amplitude[max_am])
			{
				continue;
			}
 
			outGraph[(*index)].frequance=max_am;//���Ƶ��
			outGraph[(*index)++].amplitude=curr_amplitude[max_am];

		}
		memcpy(pre_amplitude,curr_amplitude,sizeof(float)*201);
		
		fftw_free(in);
		fftw_free(out);
	}
 
	*size=*size/400;
	delete []data; 
	return outGraph;
}