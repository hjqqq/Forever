#ifndef _CSKILL_H_
#define _CSKILL_H_

#include "Common.h"

class CSkill
{
public:
    void                initSkill(tagSKILL_TYPE type, int level, std::string icomName, 
                                  std::string name, std::string desc, int actionID,
								  float castTime, float coolTime, float castRange,
								  AttackTarget target, AdvancedAttribute effectAttr,
								  FloatPrecentAttribute effectAttrPercent, int bufID,
								  int motionEffects,int triggerMotion,bool weapon,
                                  bool shield);   //��l�]�w
    tagSKILL_TYPE       getType();          //���o�ޯ����
    int                 getLevel();         //���o�ǲߵ���
    std::string         geticonName();      //���o�ϥ�
    std::string         getName();          //���o�W�r
    std::string         getDesc();          //���o����
	int					getActionID();		//���o�ޯ�ʧ@ID
    float               getCastTime();      //���o�I�k�ɶ�
    float               getCoolDown();      //���o�N�o�ɶ�
    float               getCastRange();     //���o�I�i�Z��
    AttackTarget        getTarget();        //���o�ؼ�
    AdvancedAttribute   getEffectAttr();    //���o�v�T�ݩ�
	FloatPrecentAttribute	getEffectAttrPercent();	//���o�ʤ���v�T�ݩ�
	int					getBuffID();		//���oBuffID
	int					getMotionEffects();	//���o���A�ĪG
	int					getTriggerMotion();	//���oĲ�o���A
    bool                getWeapon();        //�O�_�ݭn�Z��
    bool                getSield();         //�O�_�ݭn�޵P

    void                read(FILE* pFile);  //Ū��

    int                 getClassType();

protected:

private:
	tagSKILL_TYPE     m_type;       //�ޯ����
	int               m_iLevel;		//�ǲߵ���
	std::string       m_iconName;   //�ϥ�
	std::string       m_strName;	//�W�r
	std::string       m_strDesc;	//����
    int               m_iActionID;  //�ޯ�ʧ@ID
	float             m_fCastTime;	//�I�k�ɶ�	
	float             m_fCoolDown;	//�N�o�ɶ�
	float             m_fCastRange;	//�I�i�Z��
	AttackTarget      m_target;	    //�ؼ�
	AdvancedAttribute m_effectAttr; //�v�T���ݩ�
    FloatPrecentAttribute m_effectAttrPercent;	//�ʤ����ݩ�
    int               m_iBuffID;    //BuffID
	int				  m_iMotionEffects;	//���A�ĪG
	int				  m_iTriggerMotion;	//Ĳ�o���A
	bool              m_bWeapon;	//�ݭn�Z��
    bool              m_bShield;	//�ݭn�޵P    
    
};

#endif