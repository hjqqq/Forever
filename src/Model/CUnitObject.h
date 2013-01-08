#ifndef _CUNITOBJECT_H_
#define _CUNITOBJECT_H_

#include "Common.h"
#include "CSkill.h"
#include "CBuff.h"
// Add by Darren Chen on 2012/12/22 {
#include "CActionDispatch.h"

typedef struct tagPOSITION {
   float fX;
   float fY;
} POSITION;
// } Add by Darren Chen on 2012/12/22

class CUnitObject
{
   public:
      CUnitObject(std::string strName, long long uid, char level = 0); //�إߨ��� �ǤJ�W�r�B����(�w�]�إ߫ᬰ0��)

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
      BasisAttribute getBasAttr();                 //���o��¦�ݩ�

      std::list<CBuff> getBuff();      //���o���W��Buff��
      void addBuff(unsigned int id);   //�W�[Buff

      std::vector<CSkill> getSkill();  //���o�Ƿ|���ޯ��
      bool addSkill(unsigned int id);  //�ǧޯ�

      // Add by Darren Chen on 2012/12/22 {
      virtual ~CUnitObject();

      /** @brief �޿�ʧ@
        * @param timePass �@��frame�X�� */
      void work(float timePass);

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
      const POSITION& getPosition();

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
      const POSITION& getTargetPosition();

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

#ifdef _GAMEENGINE_2D_
      /** @brief Client��ø�ϰʧ@ 
        * @param hdc ø�ϸ˸m */
      void draw(HDC hdc);
#endif
      // } Add by Darren Chen on 2012/12/22

   protected:
      std::vector<CSkill>  m_vSkill;         //�֦����ޯ�

      // Add by Darren Chen on 2012/12/27 {
      CActionSystem       *m_pActionSystem;  // �ʧ@�t��
      // } Add by Darren Chen on 2012/12/27

   private:
      long long             m_uid;	   //�ߤ@�s��
      char                  m_level;	//����
      std::string           m_strName;	//�W�r
      BasisAttribute        m_basAttr;	//�򥻼ƭ�
      AdvancedAttribute     m_advAttr;	//�ݩ�
      ObscureAttribute      m_obsAttr;	//���üƭ�
      ComplexAttribute      m_comAttr;	//���A�ݩ�
      FloatPrecentAttribute m_preAttr; //�B�I�Ʀʤ����ݩ�
      std::list<CBuff>      m_lBuff;	//���W��Buff

      int getHPR();   //���o�^�_���ͩR�O�I
      int getMPR();   //���o�^�_���믫�O�I

      void updateBuff(float timepass);    //��s�Ҧ�Buff���ɶ�
      void SkillCoolDown(float timepass); //��s�Ҧ��ޯ઺�N�o

      // Add by Darren Chen on 2012/12/22 {
      //friend class CPacketPlayerData;  // ���\CPacketPlayerData���󪽱���private/protected�������s��
      //friend class CPacketPlayerInit;  // ���\CPacketPlayerInit���󪽱���private/protected�������s��

#ifdef _GAMEENGINE_2D_
      /** @brief 2D��������
        * @param timePass �@��frame�X��
        * @param targetX  �ؼ��IX�y��
        * @param targetY  �ؼ��IY�y��
        * @param bFaceTarget �O�_����ؼ��I */
      void move(float timePass, float targetX, float targetY, bool bFaceTarget);

      bool     m_bFaceTarget;     // �O�_����ؼ�
#endif

      POSITION m_position;        // ����X,Y�y�� (2D)
      POSITION m_targetPosition;  // �ؼ��IX,Y�y�� (2D)
      float    m_fDirection;      // �����V(���: ����), �f�ɰw��V���ର+, ���ɰw��V���ର-, ��V��0�O�¤U
      // } Add by Darren Chen on 2012/12/22
};

#endif