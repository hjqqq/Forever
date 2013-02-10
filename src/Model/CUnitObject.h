#ifndef _CUNITOBJECT_H_
#define _CUNITOBJECT_H_

#include "Common.h"
#include "CSkill.h"
#include "CBuff.h"
// Add by Darren Chen on 2012/12/22 {
#include "CActionDispatch.h"
#include "CFightSystem.h"
#include "IAdvAttrEventListener.h"
#include "ISkillEventListener.h"
#include "IDrawWeaponNotifyListener.h"
#include "IPlaySoundNotifyListener.h"
// } Add by Darren Chen on 2012/12/22

class CUnitObject : public IPlaySoundNotifyListener
{
   public:
      CUnitObject(std::string machineName, std::string strName, long long uid, char level = 0); //�إߨ��� �ǤJ�W�r�B����(�w�]�إ߫ᬰ0��)
      virtual ~CUnitObject();  // Add by Darren Chen on 2013/01/12

      std::string getMachineName();

      long long getUID();	   //���o�ߤ@�s��
      std::string getName();	//���o����W�r
      char getLevel();	      //���o����

      void addHP(int hp);	//�W�[/���HP
      int getHP();	      //���oHP
      int getHPMax();	   //���o�̤jHP

      void addMP(int mp);	//�W�[/���MP
      int getMP();	      //���oMP
      int getMPMax();	   //���o�̤jMP

      void setAdvAttr(AdvancedAttribute advAttr);	//�]�w�ݩ�
      AdvancedAttribute getAdvAttr();	            //���o�ݩ�
      void setBasAttr(BasicAttribute basAttr);     //�]�w�򥻯���
      BasicAttribute getBasAttr();                 //���o��¦����

      std::list<CBuff> getBuff();      //���o���W��Buff��
      void addBuff(unsigned int id);   //�W�[Buff

      std::vector<CSkill *> getSkill();  //���o�Ƿ|���ޯ��
      CSkill* getSkill(int skillID);
      bool addSkill(int skillID);    //�ǧޯ�

      // Add by Darren Chen on 2012/12/22 {
      /** @brief �O�_�i�ϥΧޯ�
        * @param skillID       �ޯ�s��
        * @return true  - �i�H�ϥ�
        *         false - ���i�H�ϥ� */
      bool canUseSkill(int skillID);

      /** @brief �}�l�I�i�ޯ�
        * @param skillID       �ޯ�s�� */
      void startCastSkill(int skillID);

      /** @brief �ϥΧޯ�
        * @param skillID       �ޯ�s�� */
      void useSkill(int skillID);

      /** @brief �O�_�b�I�i�ޯ�
        * @return true  - �O
        *         false - �_ */
      bool isCastSkill();

      /** @brief �޿�ʧ@
        * @param timePass �@��frame�X�� */
      virtual void work(float timePass);

      /** @brief �[�@�Ӥ�V�����q�ӧ��ܨ����V
        * @param offsetDirection ��V�����q(����) */
      void addDirection(float offsetDirection);

      /** @brief �]�w�����V
        * @param direction ��V(����) */
      void setDirection(float direction);

      /** @brief ���o�����V
        * @return ��V(����) */
      float getDirection();

      /** @brief �]�w��m
        * @param x x�y��
        * @param y y�y�� */
      void setPosition(float x, float y);

      /** @brief ���o��m
        * @return ��m */
      const FPOS& getPosition();

      /** @brief �]�w�ؼ��I��m
        * @param x x�y��
        * @param y y�y�� */
      void setTargetPosition(float x, float y);

#ifdef _GAMEENGINE_2D_
      /** @brief �]�w�ؼ��I��m
        * @param x           x�y��
        * @param y           y�y��
        * @param bFaceTarget �O�_����ؼ� */
      void setTargetPosition(float x, float y, bool bFaceTarget);
#endif

      /** @brief ���o�ؼ��I��m
        * @return ��m */
      const FPOS& getTargetPosition();

      /** @brief �O�_��F�ؼ��I
        * @return true  - �O
        *         false - �_ */ 
      bool isReachTarget();

      /** @brief �O�_���ܰʧ@
        * @return true  - ����
        *         false - �S���� */
      bool isChangeAction();

      /** @brief ���o�ثe���ʧ@��T
        * @return �ʧ@��T */
      CAction* getCurAction();

      /** @brief �O�_�ಾ��
        * @return true  - �O
        *         false - �_ */
      bool isMove();

      /** @brief �]�w��L�����Ⲿ�ʼҦ� */
      void setKeyMoveEnabled(bool bEnable);

      /** @brief ���o�Ҧ��ʵe�W��
        * @return �Ҧ��ʵe�W�� */
      std::vector<std::string> getAllAnimationName();

      /** @brief �]�w�ؼЪ� (���a/�Ǫ�/NPC)
        * @param pUnitObject �ؼЪ� */
      void setTargetObject(CUnitObject *pUnitObject); 

      /** @brief ���o�ؼЪ� */
      CUnitObject* getTargetObject();

      /** @brief �[�J��ť�i���ݩʨƥ󪺪���
        * @param pListener ��ť�� */
      void addAdvAttrEventListener(IAdvAttrEventListener *pListener);

      /** @brief ������ť�i���ݩʨƥ󪺪���
        * @param pListener ��ť�� */
      void removeAdvAttrEventListener(IAdvAttrEventListener *pListener);

      /** @brief �[�J��ť�ޯ�ƥ󪺪���
        * @param pListener ��ť�� */
      void addSkillEventListener(ISkillEventListener *pListener);

      /** @brief ������ť�ޯ�ƥ󪺪���
           * @param pListener ��ť�� */
      void removeSkillEventListener(ISkillEventListener *pListener);

      void addDrawWeaponNotifyListener(IDrawWeaponNotifyListener *pListener);
      void removeDrawWeaponNotifyListener(IDrawWeaponNotifyListener *pListener);

      void addPutinWeaponNotifyListener(IPutinWeaponNotifyListener *pListener);
      void removePutinWeaponNotifyListener(IPutinWeaponNotifyListener *pListener);

#ifdef _GAMEENGINE_2D_
      /** @brief �O�_�Q�I��
        * @param x �ƹ���X�y��
        * @param y �ƹ���Y�y��
        * @return ture - �Q�I��
        *         false - �S���Q�I�� */
      bool isClick(float x, float y);

      /** @brief Client��ø�ϰʧ@ 
        * @param hdc ø�ϸ˸m */
      virtual void draw(HDC hdc);
#endif
      // } Add by Darren Chen on 2012/12/22

      virtual void skillDamage(AdvancedAttribute targetAttr);

   protected:
      std::vector<CSkill *>  m_vSkill;          //�֦����ޯ�

      // Add by Darren Chen on 2012/12/27 {
      CActionSystem         *m_pActionSystem;   // �ʧ@�t��
      CFightSystem          *m_pFightSystem;    // �԰��t��         
      // } Add by Darren Chen on 2012/12/27

   private:
      friend class CPacketPlayerDataWG;  // ���\CPacketPlayerDataWG���󪽱���private/protected�������s��
      friend class CPacketPlayerInit;    // ���\CPacketPlayerInit���󪽱���private/protected�������s��
      friend class CPacketPlayerData;

      int getHPR();   //���o�^�_���ͩR�O�I
      int getMPR();   //���o�^�_���믫�O�I

      void updateBuff(float timepass);    //��s�Ҧ�Buff���ɶ�
      void SkillCoolDown(float timepass); //��s�Ҧ��ޯ઺�N�o

      /** @brief �q��AdvAttr����s */
      void notifyAdvAttrUpdate();

      /** @brief �q���ޯ঳��s */
      void notifySkillUpdate();

      // IPlaySoundNotifyListener
      /* virtual */ void notifyPlaySound(std::string soundFile);

      void setUID(long long uid);

#ifdef _GAMEENGINE_2D_
      /** @brief 2D��������
        * @param timePass �@��frame�X��
        * @param targetX  �ؼ��IX�y��
        * @param targetY  �ؼ��IY�y��
        * @param bFaceTarget �O�_����ؼ��I */
      void move(float timePass, float targetX, float targetY, bool bFaceTarget);

      bool          m_bFaceTarget;     // �O�_����ؼ�
#endif

      std::string            m_machineName;     // �����W�� (�Ψ��ѧO�O���P����, ex: Client1 / Client2 / Client3 / GameServer1 / GameServer2 / WorldServer1)
      long long              m_uid;	            //�ߤ@�s��
      char                   m_level;	         //����
      std::string            m_strName;         //�W�r
      BasicAttribute         m_basAttr;         //�򥻼ƭ�
      AdvancedAttribute      m_advAttr;         //�ݩ�
      ObscureAttribute       m_obsAttr;         //���üƭ�
      ComplexAttribute       m_comAttr;         //���A�y���ݩ��ܤƼȦs
      FloatPrecentAttribute  m_preAttr;         //���A�y���ݩʯB�I��(�ʤ���)
                                                //�ܤƼȦs
      std::list<CBuff>       m_lBuff;	         //���W��Buff
      FPOS                   m_position;        // ����X,Y�y�� (2D)
      FPOS                   m_targetPosition;  // �ؼ��IX,Y�y�� (2D)
      float                  m_fDirection;      // �����V(���: ����), �f�ɰw��V���ର+, ���ɰw��V���ର-, ��V��0�O�¤U
      CUnitObject           *m_pTargetObject;   // �ؼЪ�
      bool                   m_bKeyMoveEnabled; // ��L���ʼҦ�

      std::set<IAdvAttrEventListener *>  m_advAttrEventListeners;  // ��ťAdvancedAttribute���ܪ���ť�̦C��
      std::set<ISkillEventListener *>    m_skillEventListeners;    // ��ť�ޯ���ܪ���ť�̦C��
      // } Add by Darren Chen on 2012/12/22
};

#endif