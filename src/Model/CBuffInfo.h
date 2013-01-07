#ifndef _CBUFFINFO_H_
#define _CBUFFINFO_H_

#include "Common.h"

class CBuffInfo
{
public:
    void initBuffInfo(std::string name, std::string desc, std::string iconName,
                    ComplexAttribute attr, FloatPrecentAttribute attrPercent,
                    float continued, bool harmful);		//��l
    std::string getName();				//���o�W��
    std::string getDesc();				//���o����
    std::string getIconName();			//���o�ϥܦW��
    ComplexAttribute getAttr();			//���o�ݩ�
    FloatPrecentAttribute getPercentAttr();	//���o�v�T�ʤ���
    float getContinued();				//���o�̤j����ɶ�
    bool isHarmful();					//���o�O�_���`

    CBuffInfo();
    ~CBuffInfo();

    void read(FILE* pFile);				//Ū��

	BuffClassType getClassType();

private:
    std::string m_strName;				//�W��
    std::string m_strDesc;				//����
    std::string m_iconName;				//�ϥܦW��
    ComplexAttribute m_Attr;			//�v�T�ݩ�
    FloatPrecentAttribute m_AttrPercent;		//�ʤ����ݩ�
    float m_fContinued;					//����ɶ�
    bool m_bHarmful;					//���`/�W�q

};

#endif