#include "gp_canvas_gles.h"
#include "gp_canvas_layer.h"
#include "gp_matrix.h"
#include <math.h>

#include <assert.h>

namespace GP
{

//###############################

CanvasGLES::CanvasGLES (HWND hwnd):hWnd(hwnd),hDC(NULL)
{
	hDC = GetDC (hWnd) ;

	RECT cliRect ;
	GetClientRect (hWnd, &cliRect) ;
	w = (float32)cliRect.right ;
	h = (float32)cliRect.bottom ;

	eglDisplay = NULL ;
	eglConfig = NULL ;
	eglSurface = NULL ;
	eglContext = NULL ;
	eglWindow = hWnd ;

	ui32VboRect = NULL ;
	ui32VboLine = NULL ;
	ui32VboText = NULL ;
	ui32VboImage = NULL ;

	initContext () ;

	//default shader
	loadShader () ;

	//
	initDafaultVertexBuffer () ;
}

CanvasGLES::~CanvasGLES ()
{
	// Frees the OpenGL handles for the program and the 2 shaders

	// Delete the VBO as it is no longer needed
	if (ui32VboRect != NULL)
		glDeleteBuffers(1, &ui32VboRect);
	if (ui32VboLine != NULL)
		glDeleteBuffers(1, &ui32VboLine);
	if (ui32VboText != NULL)
		glDeleteBuffers(1, &ui32VboText);
	if (ui32VboImage != NULL)
		glDeleteBuffers(1, &ui32VboImage);

	if (eglDisplay != NULL)
		eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	if (eglDisplay != NULL)
		eglTerminate(eglDisplay);

	if (hDC != NULL)
	{
		ReleaseDC (hWnd, hDC) ;
	}
}

void CanvasGLES::initContext ()
{
	globalLight.set (1, 1, 1, 1) ;

	assert (eglDisplay == NULL) ;
	eglDisplay = eglGetDisplay(hDC);
    if(eglDisplay == EGL_NO_DISPLAY)
         eglDisplay = eglGetDisplay((EGLNativeDisplayType) EGL_DEFAULT_DISPLAY);

	EGLint iMajorVersion, iMinorVersion;
	if (!eglInitialize(eglDisplay, &iMajorVersion, &iMinorVersion))
	{
		assert (0 && "CanvasGLES::initContext eglInitialize") ;
		return ;
	}

	eglBindAPI(EGL_OPENGL_ES_API);
	if (eglGetError() != EGL_SUCCESS)
	{
		assert (0 && "CanvasGLES::initContext eglBindAPI") ;
		return ;
	}

	const EGLint pi32ConfigAttribs[] =
	{
		EGL_LEVEL,				0,
		EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
		EGL_NATIVE_RENDERABLE,	EGL_FALSE,
		EGL_DEPTH_SIZE,			EGL_DONT_CARE,
		EGL_NONE
	};

	int iConfigs;
	assert (eglConfig  == NULL) ;
	if (!eglChooseConfig(eglDisplay, pi32ConfigAttribs, &eglConfig, 1, &iConfigs) || (iConfigs != 1))
	{
		assert (0 && "CanvasGLES::initContext eglChooseConfig") ;
		return ;
	}

	assert (eglSurface == NULL) ;
	eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, eglWindow, NULL);
    if(eglSurface == EGL_NO_SURFACE)
    {
        eglGetError(); // Clear error
        eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, NULL, NULL);
	}

	if (eglGetError() != EGL_SUCCESS)
	{
		assert (0 && "CanvasGLES::initContext eglCreateWindowSurface") ;
		return ;
	}

	//7 context
	assert (eglContext == NULL) ;
	EGLint ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
	eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, ai32ContextAttribs);
	if (eglGetError() != EGL_SUCCESS)
	{
		assert (0 && "CanvasGLES::initContext eglCreateContext") ;
		return ;
	}

	//8
	assert (eglDisplay != NULL) ;
	eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
	if (eglGetError() != EGL_SUCCESS)
	{
		assert (0 && "CanvasGLES::initContext eglMakeCurrent") ;
		return ;
	}

	//texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}

void CanvasGLES::loadShader ()
{
	vShader[SHADER_DEFAULT].loadDeafault () ;
	vShader[SHADER_TEXT].loadText () ;
	vShader[SHADER_LINE].loadLine () ;
	vShader[SHADER_RECT].loadRect () ;
}

void CanvasGLES::initDafaultVertexBuffer ()
{
	//init 
	// Generate the vertex buffer object (VBO)
	assert (ui32VboRect == NULL) ;
	glGenBuffers(1, &ui32VboRect);

	assert (ui32VboLine == NULL) ;
	glGenBuffers(1, &ui32VboLine);

	assert (ui32VboText == NULL) ;
	glGenBuffers(1, &ui32VboText);

	//�x�ΥΪ�
	assert (ui32VboImage == NULL) ;
	glGenBuffers(1, &ui32VboImage);

	//���ͳ��IUV��T
	VtxU vVtxU[4] ;
	VertexU p0, p1, p2, p3 ;
	//�k�W
//	p0.pos.set (1, 1, 0) ;	p0.uv.set (1, 0) ;	vVtxU[0] = p0 ;
	p0.pos.set (1, -1, 0) ;	p0.uv.set (1, 0) ;	vVtxU[0] = p0 ;

	//���W
//	p1.pos.set (-1, 1, 0) ;	p1.uv.set (0, 0) ;	vVtxU[1] = p1 ;
	p1.pos.set (-1, -1, 0) ;	p1.uv.set (0, 0) ;	vVtxU[1] = p1 ;

	//�k�U
//	p2.pos.set (1, -1, 0) ;	p2.uv.set (1, 1) ;	vVtxU[2] = p2 ;
	p2.pos.set (1, 1, 0) ;	p2.uv.set (1, 1) ;	vVtxU[2] = p2 ;

	//���U
//	p3.pos.set (-1, -1, 0) ;	p3.uv.set (0, 1) ;	vVtxU[3] = p3 ;
	p3.pos.set (-1, 1, 0) ;	p3.uv.set (0, 1) ;	vVtxU[3] = p3 ;

	// Bind the VBO so we can fill it with data
	assert (ui32VboRect != NULL) ;
	setVertexBuffer (ui32VboImage) ;

	// Set the buffer's data
	unsigned int dataSize = sizeof (vVtxU); // Calc afVertices size (3 vertices * stride (3 GLfloats per vertex))
	glBufferData(GL_ARRAY_BUFFER, dataSize, (GLfloat*)vVtxU, GL_DYNAMIC_DRAW);
}

void CanvasGLES::setShaderDefault (const Matrix4& mat, bool bTxr)
{
	vShader[SHADER_DEFAULT].applyParamDefault (mat, globalLight, bTxr) ;
}

void CanvasGLES::setShaderText (const Matrix4& mat, const Color& textColor, bool bTxr)
{
	vShader[SHADER_TEXT].applyParamText (mat, textColor, bTxr) ;
}

void CanvasGLES::setShaderLine (const Matrix4& mat, const Color& lineColor)
{
	vShader[SHADER_LINE].applyParamLine (mat, lineColor) ;
}

void CanvasGLES::setShaderRect (const Matrix4& mat, const Color& lineColor, bool bUseTxr)
{
	vShader[SHADER_RECT].applyParamRect (mat, lineColor, bUseTxr) ;
}

void CanvasGLES::setMode (int)//��ܼҦ�
{
}

/*
void CanvasGLES::set2DPixelMode ()//�]�w��pixel�Ҧ�,�Ψ�
{
	//��x�}�]�w���åd��y��
	//�e�����U���O(0,0)
	//�k�W���O(�e,��0)
}
*/
void CanvasGLES::setBrushColor (const Color&)
{
}

void CanvasGLES::clear (const Color& color)
{
	glClearColor(color.r, color.g, color.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void CanvasGLES::setTexture (Image* pImg)
{
	int curTextureID ;
	if (pImg != NULL)
		curTextureID = pImg->getTextureID () ;
	else
		curTextureID = Image::NO_TEXTURE_ID ;

	static GLuint preTexture = Image::NO_TEXTURE_ID;
	if (curTextureID != preTexture)
	{
		glBindTexture(GL_TEXTURE_2D, curTextureID);

		//�K�ϴ��F
		preTexture = curTextureID ;
	}
}

void CanvasGLES::setVertexBuffer (GLuint newVBID)
{
	enum {NO_VERTEX_BUFFER_ID = 0} ;
	static GLuint preVertexBuffer = NO_VERTEX_BUFFER_ID ;

	if (newVBID != preVertexBuffer)
	{
		glBindBuffer(GL_ARRAY_BUFFER, newVBID);
		preVertexBuffer = newVBID ;
	}
}

void CanvasGLES::setVertexFormat (const VtxU& vtx)
{
	//�]�w���I�榡
	glEnableVertexAttribArray(VERTEX_ARRAY);
	glVertexAttribPointer(VERTEX_ARRAY, 3, GL_FLOAT, GL_FALSE, 
								sizeof (VtxU), 0);

	//�]�wUV�榡
	glEnableVertexAttribArray(TEXCOORD_ARRAY);
	glVertexAttribPointer(TEXCOORD_ARRAY, 2, GL_FLOAT, GL_FALSE, 
									sizeof (VtxU), 
									(void*) (VtxU::fnGetMemOffsetUV ()));
}

void CanvasGLES::setVertexFormat (const VtxC& vtx)
{
	glEnableVertexAttribArray(VERTEX_ARRAY);
	glVertexAttribPointer(VERTEX_ARRAY, 3, GL_FLOAT, GL_FALSE, 
								sizeof (VtxC), 0);

	//���n�K�Ϯy��
	glDisableVertexAttribArray (TEXCOORD_ARRAY) ;

	//�]�w�C��榡
	/*
	glEnableVertexAttribArray(TEXCOORD_ARRAY);
	glVertexAttribPointer(TEXCOORD_ARRAY, 4, GL_UNSIGNED_BYTE, GL_FALSE, 
									strideSize, 
									(void*) (VtxC::fnGetMemOffsetColor ()));
	*/
}

void CanvasGLES::setGlobalLight (const Color& color)//�]�w���ҥ�(�@��])
{
	globalLight = color ;
}

void CanvasGLES::drawEllipse (const RectF&)
{
}

void CanvasGLES::drawRect (const RectF& rect, Image* pImg)
{
	//�]�w�K��
	setTexture (pImg) ;

	//�@�y���ഫ
	Matrix4 mat ;
	getMatrix (mat) ;
//	mat.setScale (2.0f/w, 2.0f/h, 1) ;

	Color tmpColor (1, 1, 1, 1);
	//�]�wshader�x�}
	setShaderDefault (mat, pImg != NULL) ;

	VtxU vVtxU[4] ;
	//�u���@��

		//���ͳ��IUV��T
		VertexU p0, p1, p2, p3 ;
		//�k�W
		p0.pos.set (rect.right, rect.top, 0) ;
		p0.uv.set (1, 0) ;
		vVtxU[0] = p0 ;

		//���W
		p1.pos.set (rect.left, rect.top, 0) ;
		p1.uv.set (0, 0) ;
		vVtxU[1] = p1 ;

		//�k�U
		p2.pos.set (rect.right, rect.bottom, 0) ;
		p2.uv.set (1, 1) ;
		vVtxU[2] = p2 ;

		//���U
		p3.pos.set (rect.left, rect.bottom, 0) ;
		p3.uv.set (0, 1) ;
		vVtxU[3] = p3 ;

		// Bind the VBO so we can fill it with data
		assert (ui32VboRect != NULL) ;
		setVertexBuffer (ui32VboRect) ;

		// Set the buffer's data
		unsigned int dataSize = sizeof (vVtxU); // Calc afVertices size (3 vertices * stride (3 GLfloats per vertex))
		glBufferData(GL_ARRAY_BUFFER, dataSize, (GLfloat*)vVtxU, GL_DYNAMIC_DRAW);

	setVertexFormat (vVtxU[0]) ;

	//�e�X
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	if (eglGetError() != EGL_SUCCESS)
		assert (0 && "CanvasGLES::renderDefault glDrawArrays") ;

	//����buffer
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CanvasGLES::getMatrixScreen (Matrix4& mat)
{
	mat.setScale (2.0f/w, 2.0f/h, 1) ;
}

void CanvasGLES::getMatrix2D (Matrix4& mat)
{
	mat.setScale (2.0f/w, 2.0f/h, 1) ;
}

void CanvasGLES::getMatrix (Matrix4& mat)
{
	if (coordinateSystem == COORDINATE_SCREEN)
	{
		//�ù��y��
		getMatrixScreen (mat) ;
	}else
	{
		getMatrix2D (mat) ;
	}
}

void CanvasGLES::getImageMatrixScreen (const Point3F& pos, const Point2F& size, 
							float rz, Matrix4& mat)
{
		mat.setScale (size.x, size.y, 1) ;//���Y��
		mat.addRotateZ (rz) ;//����
		mat.addTranslate (pos.x*2.0f, pos.y*2.0f, pos.z) ;//�A�첾

		//�̫�~�Y��ù������
		mat.addScale (1/w, 1/h, 1) ;
}

void CanvasGLES::getImageMatrix2D (const Point3F& pos, const Point2F& size, 
							float rz, Matrix4& mat)
{
		mat.setScale (size.x, size.y, 1) ;//���Y��
		mat.addRotateZ (rz) ;//����
		mat.addTranslate (pos.x*2.0f, pos.y*2.0f, pos.z) ;//�A�첾

		//�̫�~�Y��ù������
		mat.addScale (1/w, 1/h, 1) ;
}

void CanvasGLES::getImageMatrix (const Point3F& pos, const Point2F& size, 
							float rz, Matrix4& mat)
{
	if (coordinateSystem == COORDINATE_SCREEN)
	{
		//�ù��y��
		getImageMatrixScreen (pos, size, rz, mat) ;
	}else
	{
		getImageMatrix2D (pos, size, rz, mat) ;
	}
}

void CanvasGLES::drawImage (const Point3F& pos, const Point2F& size, Image* pImg,
					float rz)
{
	//�]�w�K��
	setTexture (pImg) ;

	//�@�y���ഫ
	Matrix4 mat ;
	getImageMatrix (pos, size, rz, mat) ;

	Color tmpColor (1, 1, 1, 1);
	//�]�wshader�x�}
	setShaderRect (mat, tmpColor, pImg != NULL) ;

	assert (ui32VboImage != NULL) ;
	setVertexBuffer (ui32VboImage) ;

	VtxU vVtxU[1] ;//���F�]�w�榡�� 
	setVertexFormat (vVtxU[0]) ;

	//�e�X
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	if (eglGetError() != EGL_SUCCESS)
		assert (0 && "CanvasGLES::renderDefault glDrawArrays") ;

	//����buffer
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CanvasGLES::drawRect (const VertexC& pos, const Point2F& size, float rz)
{
	//�]�w�K��
	setTexture (NULL) ;

	//�@�y���ഫ
	Matrix4 mat ;
	getImageMatrix (pos.pos, size, rz, mat) ;

//	Color tmpColor (1, 1, 1, 1);
	//�]�wshader�x�}
	setShaderRect (mat, pos.color, false) ;

	assert (ui32VboImage != NULL) ;
	setVertexBuffer (ui32VboImage) ;

	VtxU vVtxU[1] ;//���F�]�w�榡�� 
	setVertexFormat (vVtxU[0]) ;

	//�e�X
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	if (eglGetError() != EGL_SUCCESS)
		assert (0 && "CanvasGLES::renderDefault glDrawArrays") ;

	//����buffer
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CanvasGLES::drawLine (const VertexC& p0, const VertexC& p1)
{
	//�]�w�K��
	setTexture (NULL) ;

	//�@�y���ഫ
	Matrix4 mat ;
	getMatrix (mat) ;
//	mat.setScale (2.0f/w, 2.0f/h, 1) ;

	//�]�wshader�x�}
	setShaderLine (mat, p0.color) ;
//	setShaderDefault (mat, false) ;

	//���ͳ��IUV��T
	VtxC vVtxC[2] ;
	vVtxC[0] = p0 ;
	vVtxC[1] = p1 ;

	// Bind the VBO so we can fill it with data
	assert (ui32VboLine != NULL) ;
	setVertexBuffer (ui32VboLine) ;

	// Set the buffer's data
	unsigned int dataSize = sizeof (vVtxC); // Calc afVertices size (3 vertices * stride (3 GLfloats per vertex))
	glBufferData(GL_ARRAY_BUFFER, dataSize, (GLfloat*)vVtxC, GL_DYNAMIC_DRAW);

	//�]�w���I�榡
	setVertexFormat (vVtxC[0]) ;

	//�e�X
	glDrawArrays(GL_LINE_STRIP, 0, 2);

	if (eglGetError() != EGL_SUCCESS)
		assert (0 && "CanvasGLES::renderDefault glDrawArrays") ;

	//����buffer
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CanvasGLES::drawLine (const Point3F& p0, const Point3F& p1, const Color& color)
{
	VertexC v0, v1 ;
	v0.pos = p0 ;
	v0.color = color ;

	v1.pos = p1 ;
	v1.color = color ;

	drawLine (v0, v1) ;
}

void CanvasGLES::drawCircle (const VertexC& vtxC, float hl)
{
	if (hl <= 0.0)//�S�b�|
		return ;

	//����²�檺��k�e
	enum {MAX_VERTEX = 30, MIN_VERTEX = 15} ;
	VtxC vVtx[MAX_VERTEX] ;

	//�p���I���ƶq
	float needSegLength = 17 ;//�̵u�u�q
	float rLen = hl*2*GP_PI ;///��P
	int pointCount = int (rLen/needSegLength) ;
	if (pointCount > MAX_VERTEX)
		pointCount = MAX_VERTEX ;
	if (pointCount < MIN_VERTEX)
		pointCount = MIN_VERTEX ;

	float rad  = GP_PI*2.0f/(float (pointCount-1));
	float curRad = 0 ;
	for (int i = 0; i<pointCount-1; i++)
	{
		//�p��y��
		vVtx[i].pos.set (vtxC.pos.x+hl*cos (curRad), vtxC.pos.y+hl*sin (curRad), 0) ;
		curRad += rad ;
	}
	vVtx[pointCount-1] = vVtx[0] ;//�̫�@�I

	//�]�w�K��
	setTexture (NULL) ;

	//�@�y���ഫ
	Matrix4 mat ;
	getMatrix (mat) ;
//	mat.setScale (2.0f/w, 2.0f/h, 1) ;

	//�]�wshader�x�}
	setShaderLine (mat, vtxC.color) ;

	// Bind the VBO so we can fill it with data
	assert (ui32VboLine != NULL) ;
	setVertexBuffer (ui32VboLine) ;

	// Set the buffer's data
	unsigned int dataSize = pointCount*sizeof (VtxC); // Calc afVertices size (3 vertices * stride (3 GLfloats per vertex))
	glBufferData(GL_ARRAY_BUFFER, dataSize, (GLfloat*)vVtx, GL_DYNAMIC_DRAW);

	//�]�w���I�榡
	setVertexFormat (vVtx[0]) ;

	//�e�X
	glDrawArrays(GL_LINE_STRIP, 0, pointCount);

	if (eglGetError() != EGL_SUCCESS)
		assert (0 && "CanvasGLES::renderDefault glDrawArrays") ;

}

void CanvasGLES::drawGridLine (const Point3F& pos, const Point2F& size, 
						const Point2I& count, const Color& color)
{
	//���B�z�_��
	Point3F p0, p1 ;

	float32 dx = -size.x*(count.x/2)-size.x/2 ;
	float32 dy = size.y*(count.y/2)+size.y ;

	float32 initx = pos.x-(size.x*count.x)/2 ;
	float32 inity = pos.y+(size.y*count.y)/2 ; ;

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//�n�d�N�Φ첾�i��|���ͤp�Ʀ�~�t
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//��u
	p0.set (initx, inity, 0) ;
	p1.set (initx+size.x*count.x, inity, 0) ;
	for (int i = 0; i<(count.y+count.y%2); i++)
	{
		drawLine (p0, p1, color) ;
		p0.shift (0, -size.y, 0) ;
		p1.shift (0, -size.y, 0) ;
	}

	//���u
	p0.set (initx, inity, 0) ;
	p1.set (initx, inity-size.y*count.y, 0) ;
	for (int i = 0; i<(count.x+count.x%2); i++)
	{
		drawLine (p0, p1, color) ;
		p0.shift (size.x, 0, 0) ;
		p1.shift (size.x, 0, 0) ;
	}

	/*
	//���եΪ��׽u
	p0.set (0, 0, 0) ;
	p1.set (100, 100, 0) ;
	drawLine (p0, p1, color) ;
	*/
}

void CanvasGLES::drawText (const char* str, const VertexC& vertexC, 
							const Point2F&, int align)
{
//	static TextImage2 textImage ;
	static TextImage textImage ;

	Point2F fontSize (26, 26) ;
	Point2F textSize (200, 20) ;
	UV uv ;

	textSize = textImage.buildText (str, fontSize, uv) ;
//		textSize = textImage.buildText ("124asdlfj0892345jldkfgj", fontSize, uv) ;

	//�]�w�K��
//	setTexture (&(textImage.getCurImage ())) ;
	setTexture (&textImage) ;

	//�@�y���ഫ
	Matrix4 mat ;
	getMatrix (mat) ;
//	mat.setScale (2.0f/w, 2.0f/h, 1) ;

	setShaderText (mat, vertexC.color, false) ;

	//���ͳ��IUV��T
	VertexU p0, p1, p2, p3 ;
	VtxU vVtxU[4] ;

	float32 dif = (1-uv.v) ;

	//�k�W
	p0.pos.set (vertexC.pos.x+textSize.x, vertexC.pos.y, 0) ;
	p0.uv.set (uv.u, 1) ;
	vVtxU[0] = p0 ;

	//���W
	p1.pos.set (vertexC.pos.x, vertexC.pos.y, 0) ;
	p1.uv.set (0, 1) ;
	vVtxU[1] = p1 ;

	//�k�U
	p2.pos.set (vertexC.pos.x+textSize.x, vertexC.pos.y-textSize.y, 0) ;
	p2.uv.set (uv.u, 0+dif) ;
	vVtxU[2] = p2 ;

	//���U
	p3.pos.set (vertexC.pos.x, vertexC.pos.y-textSize.y, 0) ;
	p3.uv.set (0, 0+dif) ;
	vVtxU[3] = p3 ;

	// Bind the VBO so we can fill it with data
	assert (ui32VboText != NULL) ;
	setVertexBuffer (ui32VboText) ;

	// Set the buffer's data
	unsigned int dataSize = sizeof (vVtxU); // Calc afVertices size (3 vertices * stride (3 GLfloats per vertex))
	glBufferData(GL_ARRAY_BUFFER, dataSize, (GLfloat*)vVtxU, GL_DYNAMIC_DRAW);

	setVertexFormat (vVtxU[0]) ;

	//�e�X
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	if (eglGetError() != EGL_SUCCESS)
		assert (0 && "CanvasGLES::renderDefault glDrawArrays") ;

	//����buffer
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CanvasGLES::drawNode (LayerNode& node)
{
	//�]�w�K��,�õe�X
	Point2F size (node.size.x, node.size.y) ;
	drawImage (node, size, node.getImage ()) ;

	//�]�wvertex buffer

	//�]�w�x�}

	//�]�wvertex shader

	//�}�lø��
}

void CanvasGLES::drawLayer (CanvasLayer& layer)
{
	//���Ƨ�

	V_LAYER_NODE& vLayerNode = layer.getAllNode () ;
	V_LAYER_NODE::iterator pi = vLayerNode.begin () ;
	while (pi != vLayerNode.end ())
	{
		//�]�w���ҥ�
		setGlobalLight (layer.getGlobalLight ()) ;

		//�@�Ӥ@�өI�sø��
		drawNode (*pi) ;

		++ pi ;
	}
}

//�Ҧ���layer
void CanvasGLES::drawAllLayer ()
{

	V_CANVAS_LAYER::iterator pi = vCanvasLayer.begin () ;
	while (pi != vCanvasLayer.end ())
	{
		drawLayer (*pi) ;

		++ pi ;
	}
}

CanvasLayer* CanvasGLES::queryLayer ()
{
	vCanvasLayer.push_back (CanvasLayer ()) ;
	return &(vCanvasLayer.back ()) ;
}

void CanvasGLES::releaseLayer (CanvasLayer* pc)
{
	V_CANVAS_LAYER::iterator pi = vCanvasLayer.begin () ;
	while (pi != vCanvasLayer.end ())
	{
		if (&(*pi) == pc)
		{
			vCanvasLayer.erase (pi) ;
			return ;
		}

		++ pi ;
	}

	assert (0) ;
}

void CanvasGLES::update ()
{
	eglSwapBuffers(eglDisplay, eglSurface);
	if (eglGetError() != EGL_SUCCESS)
		assert (0 && "CanvasGLES::CanvasGLES eglSwapBuffers") ;
}

}