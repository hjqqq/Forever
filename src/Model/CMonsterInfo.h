#ifndef _CMONSTERINFO_H_
#define _CMONSTERINFO_H_

#include "Common.h"
#include "CSkill.h"

class CMonsterInfo
{
   public:
      CMonsterInfo();
      ~CMonsterInfo();//�[delet skill

      std::string           getName();          //���o�W��
      std::string           getDesc();          //���o����
      std::string           getMeshName();      //���o�ҫ��W��
      char                  getWistom();        //���oAI����
      unsigned int          getxp();            //���o�����g��
      MonsterType           getATKtype();       //���o��������
      MonsterGrade          getLevelGrade();    //���o��������
      float                 getAlert();         //���oĵ�ٽd��
      float                 getRegress();       //���o�l���d��
      AdvancedAttribute     getAdvAttr();       //���o�򥻯���

      //---1/19--add-
      std::string           getActionSystemFile();    //���o�ʧ@�ɮצW��
      char                  getLevel();         //���o����
      long long             getMoney();         //���o��������
      std::vector<int>      getReware();        //���o�������~ID
      std::vector<int>      getSkill();         //���o�֦����ޯ�ID

      //--1/19
      void initMonsterInfo(std::string name, std::string desc,
                           std::string meshName, std::string actionSystem,
                           char level, char wistom, unsigned int xp, MonsterType atkType,
                           MonsterGrade levelGrade, float alert, float regress, AdvancedAttribute advAttr,
                           long long money, std::vector<int> reware, std::vector<int> skill);  //��l�]�w

      void                  read(FILE* pFile);  //Ū��
      void                  write(FILE* pFile); //�g��
      MonsterClass          getClassType();     //���o���A���O

   private:
      std::string           m_strName;          //�W��
      std::string           m_strDesc;          //����
      std::string           m_strMeshName;      //�ҫ��W��
      std::string           m_strActionSystemFile;    //�ʧ@�ɮצW��
      char                  m_Level;            //����
      char                  m_Wistom;           //AI����
      unsigned int          m_ixp;              //�����g��
      MonsterType           m_ATKtype;          //�D�ʡB�Q�ʧ���
      MonsterGrade          m_LevelGrade;       //����
      float                 m_fAlert;           //ĵ�ٽd��
      float                 m_fRegress;         //�l���d��
      AdvancedAttribute     m_advAttr;          //�򥻯���
      long long             m_Money;            //��������
      std::vector<int>      m_vReware;          //�������~ID
      std::vector<int>      m_vSkill;           //�ޯ�ID
};

#endif