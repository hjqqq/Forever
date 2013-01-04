/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CTerrain.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/28 */
#ifndef _CTERRAIN_H_
#define _CTERRAIN_H_
#include "Common.h"

#include <ETTerrainManager.h>
#include <ETTerrainInfo.h>
#include <ETBrush.h>
#include <ETSplattingManager.h>

#include <OgreStringConverter.h>
#include <OgreViewport.h>
#include <OgreTextureManager.h>
#include <OgreTexture.h>
#include <OgreCamera.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreMaterial.h>
#include <OgreMaterialManager.h>

/** @brief 3D�a�� */
class CTerrain
{
   public:
      CTerrain();
      ~CTerrain();

      /** @brief ��l��
        * @param pSceneManager �����޲z��
        * @param pCamera       ��v�� */
      void init(Ogre::SceneManager *pSceneManager, Ogre::Camera *pCamera);

      /** @brief ���o�g�u�g��a�Ϊ���m�y��
        * @param [in]  mouseRay �ƹ��I�a�O���g�u
        * @param [out] pos      ��m�y��
        * @return true - �Ӯg�u�O����a�O / false - �Ӯg�u�S������a�O */
      bool getRayPos(Ogre::Ray &mouseRay, Ogre::Vector3 &pos);

      /** @brief �a�έn������W�� (�a�νs�边��)
        * @param mouseRay        �ƹ��I�a�O���g�u
        * @param iChoseTexture   �έ��i����W��
        * @param editBrush       �Ψ��ӵ���Ӷ�
        * @param fBrushIntensity ���ꪺ�j��(�ΨӨM�w�s����W�⪺�`�L) */
      void paint(Ogre::Ray &mouseRay, int iChosenTexture, ET::Brush editBrush, float fBrushIntensity);

      /** @brief �a��԰�/���C (�a�νs�边��)
        * @param mouseRay        �ƹ��I�a�O���g�u
        * @param editBrush       �έ��ӵ���ө԰�/���C
        * @param fBrushIntensity ���ꪺ�j��(�ΨӨM�w�a��԰�/���C���`�L) */
      void deform(Ogre::Ray &mouseRay, ET::Brush editBrush, float fBrushIntensity);

      /** @brief �a���ͯu�곱�v */
      void updateLightmap();

      /** @brief �x�s�a��
        * @param id  ���ӳ��� */
      void saveTerrain(int id);

      /** @brief Ū���a��
        * @param id  ���ӳ��� */
      void loadTerrain(int id);

      /** @brief �O�������� */
      void release();

   private:
      ET::TerrainManager    *m_pTerrainMgr;
      ET::SplattingManager  *m_pSplatMgr;
	   const ET::TerrainInfo *m_pTerrainInfo;
};

#endif  // #ifndef _CTERRAIN_H_