/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CGraphicsRender.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/04 */
#ifndef _CGRAPHICSRENDER_H_
#define _CGRAPHICSRENDER_H_
#include "IGameFlowListener.h"
#include "IMouseEventListener.h"
#include "IKeyEventListener.h"

#include <OgreSceneManager.h>
#include <OgreCamera.h>

/** @brief ø�Ϥ���(��H�ƪ���)
  *        ���ӹC���t�ΦӨ��u�|���D�o�Ӫ���,
  *        �Ҧ�3Dø�ϥu�n��o����ǤJ������T�Y�i�B�z,
  *        �ܩ�3D�Ӹ`�B�z��CGraphicsRender���l���O�Ӷ����B�z */
class CGraphicsRender
{
   public:
      virtual ~CGraphicsRender();

      /** @brief  ���oø�Ϥ����W��
        * @return ø�Ϥ����W�� */
      std::string getRenderName();

      /** @brief �n����ø�Ϥ�����X��IGameFlowListener�T��,
        *        �ݭn�Φ������禡�ӵ��U
        * @param listener �n�����T�������� */
      virtual void addGameFlowListener(IGameFlowListener *listener) = 0;

      /** @brief �n����ø�Ϥ�����X��IMouseEventListener�T��,
        *        �ݭn�Φ������禡�ӵ��U
        * @param listener �n�����T�������� */
      virtual void addMouseEventListener(IMouseEventListener *listener) = 0;

      /** @brief �n����ø�Ϥ�����X��IKeyEventListener�T��,
        *        �ݭn�Φ������禡�ӵ��U
        * @param listener �n�����T�������� */
      virtual void addKeyEventListener(IKeyEventListener *listener) = 0;

      /** @brief  ���orender����
        * @return render���� */
      virtual HWND getRenderHwnd() = 0;

      // Ogre object
      virtual Ogre::SceneManager* getSceneManager() = 0;
      virtual Ogre::Camera* getCamera() = 0;

   protected:
      /** @brief �]�wø�Ϥ����W��
        * @param renderName ø�Ϥ����W�� */
      void setRenderName(std::string renderName);

      /** @brief ø�Ϥ����e�� */
      virtual void run() = 0;

   private:
      friend class CGameClient3D;  // ���\CGameClient3D����Ӧs��private/protected
      std::string m_strRenderName; // ø�Ϥ����W��
};

#endif // #ifndef _CGRAPHICSRENDER_H_