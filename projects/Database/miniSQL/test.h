#ifndef _TEST_H
#define _TEST_H

#include "Index.h"

// ���뵱ǰ��ţ�����ÿ鼰���¸�������
void PrintIndex(int blockId);

// �����Ҷ�ӿ�ָ�룬����ÿ�����
void PrintNonleaf(BaseNode *p);

// ����Ҷ�ӿ�ָ�룬����ÿ�����
void PrintLeaf(BaseNode *p);

// ���뵱ǰ��ָ�룬�Ӹÿ鿪ʼ��˳���������
void PrintData(BaseNode *p);

// ���뵱ǰ��ָ�뼰tuple�׵�ַ�����tuple�и�����ֵ
void PrintTuple(BaseNode *p, char *tuple);

#endif // _TEST_H