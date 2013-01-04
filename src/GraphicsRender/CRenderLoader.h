/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CRenderLoader.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/03 */
#ifndef _CRENDERLOADER_H_
#define _CRENDERLOADER_H_
#include "CGraphicsRender.h"

/** @brief �Ψӥi�H���J���P��ø�Ϥ���(CGraphicsRender),
  *        �Ӹ�ø�Ϥ�����Өt�Τ��]�O�ߤ@����,
  *        ���ƨ��o���|�O�@�˪�ø�Ϥ���,
  *        ���|���O�O����Ŷ�. */
class CRenderLoader
{
   public:
      /** @brief  ���oCGraphicsRender��@����
        * @return CRenderLoader���� */
      static CRenderLoader* getInstance();

      /** @brief ����CRenderLoader���󪺰O����Ŷ� */
      static void releaseInstance();

      /** @brief  ���oø�Ϥ���
        *         �Ĥ@�����T���oø�Ϥ�����, 
        *         �Y�ĤG���n���o��Lø�Ϥ����h�O�����\���~����, �̵M�^�ǲĤ@����ø�Ϥ���
        * @param  renderName ø�Ϥ����W��
        * @return ø�Ϥ������� */
      CGraphicsRender* getGraphicsRender(const std::string &renderName);

   private:
      CRenderLoader();
      ~CRenderLoader();

      /** @brief ���U������ø�Ϥ���
        * @param render ø�Ϥ������� */
      void registerGraphicsRender(CGraphicsRender *pRender);

      static CRenderLoader *m_pInstance;  // CRenderLoader���骫��
      CGraphicsRender *m_pRenderCore;     // ø�Ϥ���
      std::map<std::string, CGraphicsRender*> *m_pEngineTable; // ø�Ϥ����C��
};
#endif // #ifndef _CRENDERLOADER_H_