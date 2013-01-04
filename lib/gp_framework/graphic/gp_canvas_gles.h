#ifndef _GP_CANVAS_GL_ES_H_
#define _GP_CANVAS_GL_ES_H_

#include "gp_canvas.h"
#include "gp_canvas_layer.h"

#include "gp_shader.h"
//�̨Τƪ���h

//1
//���copy��ƨ�vertex buffer
//�ɶq������vertex buffer

//2
//��h�i�K�ϦX�֤@�i
//�@���e�h�Ӫ���

//3
//�ܧ��I�榡
//��pos,normal,uv,pos,normal,uv
//�ܦ�pos,pos,normal,normal,uv,uv
//�bpower vr���U
//�Ĥ@�ؤ���n

//4
//����O����
//�B�I��(4 byte)�n�O�b4byte��align
//2 byte�n�� 2byte��align

//5
//�C���16 bit���B�I��
//���n��32 bi6��

//6
//�ɶq��triangle strip
//���O�i��|�W�[ø�Ϧ���
//�o�n�g�L����~���D
//�Ѧ�powerVR��sample code

//7
//�έ��Cø�ϰϼe�����覡
//�T�{�į઺�~�V�Opixel��R�٬Overtex��v/����

//8
//�����sĶ����compile for thumb�ﶵ

//9
//

//10
//���I�Ӧh
//�Ҽ{��DOT3�@normal map

//11
//��light map���N����

//12
//��K�������ոլ�fps���S������
//�p�G��
//��K���ܤp
//����`�K�Ϯe�q
//�����Y���K��
//�X�ֶK��
//�ϧθ�ƪ����s���{���X(�Ϊ̥��ন�̲ת��榡)

//13
//���z��nø�Ϫ�����

//14
//�]�k���ѭI��(�歱�K��)

//15
//�ϥ�clip planes
//�R���ݤ�����

//16
//��CPU�@octree�z��

//17
//shaer�����if else

//18
//����shader�i����Ӯɶ�
//�X�֦h��shader
//�o�ӭn���դ~���D

//19
//gpu��kill���O�i�H�����e�ϵ{��
//�n���լݬݤ~���D���S���ܧ�
//�i�H�ΨӰ�

//20
//���n�ΤӦh�h�K��

//21
//�V��skinning�t��k

//22
//��֧���opengl es�����A
//�@�Ǫ��A���禡�I�s
//�p�G�]�w���e�@��,���n���ƩI�s

//23
//���nlock(Ū�μg)buffer
//�]���o�|��opengl��ϧεe��
//���ӥ�����cpu��onengl�B�@

//24
//�Q��framework
//��UI��ø�s�P����,layer��ø�s
//���n���b�@�_
//�ভ�I���N���I��
//���nonWork���~�q�q�@�_��

//25
//���n��gpu discard���O

//26
//����fps
//�]�i�H�����ʬݰ_�Ӥ����

//27
//�ɶq��vertex buffer�X�b�@�_
//�ר�O����

//28
//���e���z����
//�A�ealpha blend

//29
//���ھ�shader�Ʃwø�϶���
//�A�ھ�ø�Ϫ��A�Ʃwø�϶���

//30
//alpha blending
//���ǭn�Ƨ�,���Ǥ���
//�]�����ǳq�`�ܧ󤣤j
//�ҥH�δ��J�ƧǪk

//31
//�bpower vr
//index triangle list
//�O�̦��Ĳv��

//32
//�n�ʺA�ק諸vertex buffer
//�����n�]�w���T
//STATIC_DRAW, DYNAMIC_DRAW, STREAM_DRAW

//33
//vertex shader���B�z�����I���
//�̦n���Ofloat
//��L�榡���ഫ�|��ɶ�
//���Obyte, word���j�p�v�T�W�e
//�n�ոլݤ~���D

//34
//�ɶq���4byte��vertex���
//�Y��byte�]�O
//�̦n�p��4byte����ƱƦb�̫�

//35
//���F�ù��j�p���K��(�@��s�S�ĥ�)
//��L���e�����n�O2������

//36
//normal map,�̦n��alpha�h
//���n�A�h�μh��
//power vr���u��i��

//37
//�V��K��pixel���榡
//RGBA8,RGBA5551,RGBA4444,RGB565...
//�ɶq��16bit

//38
//�ɶq�֥ίB�I�ƪ�pixel(�K��)

//39
//�ɶq�����Y���K�Ϯ榡
//���O�o�خ榡����۰ʲ���mipmap
//�������s�@�nmipmap
//�A�]�w��K��
//glCompressedTexImage2D.

//40
//�ɶq��mipmap
//glGenerateMipmap�i�H�۰ʲ���
//���O�L�k�w�����Y���榡�B�@
//���Y�榡���K�ϭn��power vr�u�㲣��

//41
//�ɶq�b�C����Ұ�
//�i�J���d�e���J�Ҧ����a��
//�]���ʺA���J�K�Ϸ|���B�~���ɶ�
//(�̦n�f�tcache����)

//42
//shader���ΰ��C��T�ת��ܼ�
//�A�C�C�խ�,�ݬݮĪG�O�_�X�A
//�����į�

//43
//shader����֤����n���y���ഫ

//44
//pixel shader�U�p�U�n

//45
//�x�}�B���highp
//texture coordinates��highp��mediump
//normal���C���lowp
//���sampler��pixel�榡�X�A

//46
//��u�ʲ��ʥ�shder�@

//47
//shader�����n�Ϊ��p��
//��if else���L


namespace GP
{

//opengl es
class LayerNode ;
typedef std::list <CanvasLayer> V_CANVAS_LAYER ;
class CanvasGLES:public Canvas
{
	HWND hWnd ;
	HDC hDC ;

	EGLDisplay			eglDisplay ;
	EGLConfig			eglConfig ;
	EGLSurface			eglSurface ;
	EGLContext			eglContext ;
	EGLNativeWindowType	eglWindow ;

	Color globalLight ;

	enum {SHADER_DEFAULT, SHADER_TEXT, SHADER_LINE, 
			SHADER_RECT, SHADER_COUNT} ;
	Shader vShader[SHADER_COUNT] ;
	enum {NO_SHADER_ID = 0} ;
	GLuint	ui32VboRect, ui32VboLine, ui32VboText,
			ui32VboImage; //�̰򥻪�vertex buffer,�Ψӵe²�檺�F��

	//�Ҧ���layer
	V_CANVAS_LAYER vCanvasLayer ;

public:
	CanvasGLES (const CanvasGLES&) {} //no copy construct
	CanvasGLES (HWND) ;
	~CanvasGLES () ;

private:
	void initContext () ;//�_�l�]�w
	void loadShader () ;//�]�w�w�]��shader
	void initDafaultVertexBuffer () ;

//	void setShader (GLuint) ;
	void setShaderDefault (const Matrix4&, bool) ;

	//��ܤ�r�Ϊ�shader
	void setShaderText (const Matrix4&, const Color&, bool) ;

	//�u���Ϊ�
	void setShaderLine (const Matrix4&, const Color&) ;

	void setShaderRect (const Matrix4&, const Color&, bool) ;

protected:

public:
	void setMode (int) ;//��ܼҦ�
//	void set2DPixelMode () ;//�]�w��pixel�Ҧ�,�Ψ�
	void setBrushColor (const Color&) ;

	void clear (const Color&) ;

	enum {AUTO_LEN = -1} ;
//	void drawText (const char*, float, float, int = AUTO_LEN) ;//��ܤ�r

private:
	void setTexture (Image*) ;//�]�w�K��
	void setVertexBuffer (GLuint) ;//�]�wvertex buffer

	//�]�w���I�榡(�o�]�P�ɦ۰ʨϥι�����shader)
	void setVertexFormat (const VtxU&) ;//
	void setVertexFormat (const VtxC&) ;//

	//###########################
	//�����ݨD���R
	//���� : light map + ���� + ��V
	//�a�Ϫ��� : ���� + ��V
	//���� : normal map + ���� + ��V
	//�S�� : �u�n���|��N�n,���ݥ���

	//###########################
	//���I�����p�� = ���ҥ� + ��V�� + �������� + �ʺA�B�~����x3
	void setGlobalLight (const Color&) ;//�]�w���ҥ�(�@��])
	void setGlobalDirectionLight (const Color&) ;//�]�w���Ҥ�V��(�@�Ӷ�������)

	void setObjectLight (const Color&) ;//��������,�|��global�ۥ[
	//�[�b���󨭤W���ʺA�B�~����(�ثe�T��),�y�Фw�g���⦨����y��
	void setDynamicLight (const VtxC*, const VtxC*, const VtxC*) ;

public:
	void drawEllipse (const RectF&) ;
	void drawRect (const RectF&, Image*) ;

private:
	void getMatrixScreen (Matrix4&) ;//���o�x�}
	void getMatrix2D (Matrix4&) ;//���o�x�}
	void getMatrix (Matrix4&) ;//���o�x�}

	void getImageMatrixScreen (const Point3F&, const Point2F&, 
							float, Matrix4&) ;//���o�x�},���Ϥ��Ϊ�
	void getImageMatrix2D (const Point3F&, const Point2F&, 
							float, Matrix4&) ;//���o�x�},���Ϥ��Ϊ�
	void getImageMatrix (const Point3F&, const Point2F&, 
							float, Matrix4&) ;//���o�x�},���Ϥ��Ϊ�

public:
	void drawImage (const Point3F&, const Point2F&, Image* = NULL, float = 0) ;
	void drawRect (const VertexC&, const Point2F&, float = 0) ;

//	void drawLine (const VertexC&, const VertexC&) ;
private:
	void drawLine (const VertexC&, const VertexC&) ;
public:
	void drawLine (const Point3F&, const Point3F&, const Color&) ;
	void drawCircle (const VertexC&, float) ;
	void drawGridLine (const Point3F&, const Point2F&, const Point2I&, const Color&) ;

private:

public:

	void drawText (const char*, const VertexC&, const Point2F&, int) ;

	CanvasLayer* queryLayer () ;
	void releaseLayer (CanvasLayer*) ;

	void drawNode (LayerNode&) ;
	void drawLayer (CanvasLayer&) ;
	void drawAllLayer ()  ;

	void update () ;//��I������s������οù�
} ;

}

#endif