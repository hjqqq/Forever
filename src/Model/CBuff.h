#ifndef _CBUFF_H_
#define _CBUFF_H_

#include "Common.h"

class CBuff
{
public:
    void initBuff(std::string name, std::string desc, std::string iconName,
                    ComplexAttribute attr, ComplexAttribute attrPercent,
                    float continued, bool harmful);		//��l
    std::string getName();				//���o�W��
    std::string getDesc();				//���o����
    std::string getIconName();			//���o�ϥܦW��
    ComplexAttribute getAttr();			//���o�ݩ�
    ComplexAttribute getPercentAttr();	//���o�v�T�ʤ���
    float getContinued();				//���o�̤j����ɶ�
    bool isHarmful();					//���o�O�_���`

    CBuff();
    ~CBuff();

    void read(FILE* pFile);				//Ū��

	int getClassType();

private:
    std::string m_strName;				//�W��
    std::string m_strDesc;				//����
    std::string m_iconName;				//�ϥܦW��
    ComplexAttribute m_Attr;			//�v�T�ݩ�
    ComplexAttribute m_AttrPercent;		//�ʤ����ݩ�
    float m_fContinued;					//����ɶ�
    bool m_bHarmful;					//���`/�W�q

};

#endif