#ifndef _CMONSTERINFO_H_
#define _CMONSTERINFO_H_

#include "Common.h"

class CMonsterInfo
{
public:
    CMonsterInfo();
    ~CMonsterInfo();
    std::string         getName();          //���o�W��
    std::string         getDesc();          //���o����
    std::string         getMeshName();      //���o�ҫ��W��
    std::string         getMeshTexture();   //���o�ҫ��K��
    char                getWistom();        //���oAI����
    unsigned int        getxp();            //���o�򥻸g��
    MonsterType         getATKtype();       //���o��������
    MonsterGrade        getLevelGrade();    //���o��������
    float               getAlert();         //���oĵ�ٽd��
    float               getRegress();       //���o�l���d��
    BasicAttribute      getBasAttr();       //���o�򥻯���
    void initMonsterInfo(std::string name, std::string desc,
                         std::string meshName, std::string meshTexture, char wistom,
                         unsigned int xp, MonsterType atkType, MonsterGrade levelGrade, float alert,
		                   float regress, BasicAttribute basAttr);  //��l�]�w

    void                read(FILE* pFile);  //Ū��
    void                write(FILE* pFile); //�g��
    MonsterClass        getClassType();     //���o���A���O

private:
    std::string         m_strName;          //�W��
    std::string         m_strDesc;          //����
    std::string         m_strMeshName;      //�ҫ��W��
    std::string         m_strMeshTexture;   //�ҫ��K��
    char                m_Wistom;           //AI����
    unsigned int        m_ixp;              //1���ɪ��򥻸g��
                                            //(������o�g��:�򥻸g�筼�W�Ǫ�����)
    MonsterType         m_ATKtype;          //�D�ʡB�Q�ʧ���
    MonsterGrade        m_LevelGrade;       //����
    float               m_fAlert;           //ĵ�ٽd��
    float               m_fRegress;         //�l���d��
    BasicAttribute      m_basAttr;          //�򥻯���
};

#endif