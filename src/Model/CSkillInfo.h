#ifndef _CSKILLINFO_H_
#define _CSKILLINFO_H_

#include "Common.h"

class CSkillInfo
{
   public:
      void initSkillInfo(tagSKILL_TYPE type, int level, std::string icomName, 
                         std::string name, std::string desc, int actionID,
								 int castMP, float castTime, float coolTime,
                         float castRange, AttackTarget target,
                         AdvancedAttribute effectAttr,
                         FloatPrecentAttribute effectAttrPercent, int bufID,
                         int motionEffects, int triggerMotion, bool requireWeapon,
                         bool requireShield);   //��l�]�w

      tagSKILL_TYPE         getType();               //���o�ޯ����
      int                   getLevel();              //���o�ǲߵ���
      std::string           geticonName();           //���o�ϥ�
      std::string           getName();               //���o�W�r
      std::string           getDesc();               //���o����
      int					    getActionID();		     //���o�ޯ�ʧ@ID
      int                   getCastMP();             //���o����
      float                 getCastTime();           //���o�I�k�ɶ�
      float                 getCoolDown();           //���o�N�o�ɶ�
      float                 getCastRange();          //���o�I�i�Z��
      AttackTarget          getTarget();             //���o�ؼ�
      AdvancedAttribute     getEffectAttr();         //���o�v�T�ݩ�
      FloatPrecentAttribute getEffectAttrPercent();  //���o�ʤ���v�T�ݩ�
      int					    getBuffID();		        //���oBuffID
      int					    getMotionEffects();	     //���o���A�ĪG
      int					    getTriggerMotion();	     //���oĲ�o���A
      bool                  isRequireWeapon();       //�O�_�ݭn�Z��
      bool                  isRequireShield();       //�O�_�ݭn�޵P

      void                  read(FILE* pFile);  //Ū��
#ifdef _GAMEENGINE_2D_EDITOR_
    void                write(FILE* pFile); //�g��
#endif //#ifdef _GAMEENGINE_2D_EDITOR_

      SkillClassType        getClassType();
      ~CSkillInfo();

   protected:

   private:
      tagSKILL_TYPE         m_type;               //�ޯ����
      int                   m_iLevel;		        //�ǲߵ���
      std::string           m_iconName;           //�ϥ�
      std::string           m_strName;	           //�W�r
      std::string           m_strDesc;	           //����
      int                   m_iActionID;          //�ޯ�ʧ@ID
      int                   m_iCastMP;            //����
      float                 m_fCastTime;	        //�I�k�ɶ�	
      float                 m_fCoolDown;	        //�N�o�ɶ�
      float                 m_fCastRange;	        //�I�i�Z��
	   AttackTarget          m_target;	           //�ؼ�����
      AdvancedAttribute     m_effectAttr;         //�v�T���ݩ�
      FloatPrecentAttribute m_effectAttrPercent;  //�ʤ����ݩ�
      int                   m_iBuffID;            //BuffID
      int				       m_iMotionEffects;	  //���A�ĪG
      int				       m_iTriggerMotion;	  //�p�G���o���A�W�[Ĳ�o
      bool                  m_bRequireWeapon;	  //�ݭn�Z��
      bool                  m_bRequireShield;	  //�ݭn�޵P    
#ifdef _GAMEENGINE_2D_EDITOR_
    friend class DLGSkill;
#endif //#ifdef _GAMEENGINE_2D_EDITOR_
};

#endif