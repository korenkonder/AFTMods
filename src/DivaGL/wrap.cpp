/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "wrap.hpp"
#include "../KKdLib/half_t.hpp"
#include "../KKdLib/mat.hpp"
#include "../KKdLib/vec.hpp"
#include "../AFTModsShared/uniform.hpp"
#include "print.hpp"
#include <Helpers.h>
#include <time.h>

struct func_struct {
    size_t address;
    size_t orig_func;
    size_t func;
};

#define GLDRAWBUFFERGLUT 0
#define GLENABLEGLUT 1
#define GLFINISHGLUT 2
#define GLGETERRORGLUT 3
#define GLGETINTEGERVGLUT 4
#define GLGETSTRINGGLUT 5
#define GLPIXELSTOREIGLUT 6
#define GLREADBUFFERGLUT 7
#define GLVIEWPORTGLUT 8
#define WGLCREATECONTEXTGLUT 9
#define WGLDELETECONTEXTGLUT 10
#define WGLGETCURRENTCONTEXTGLUT 11
#define WGLGETCURRENTDCGLUT 12
#define WGLGETPROCADDRESSGLUT 13
#define WGLMAKECURRENTGLUT 14

#define GLALPHAFUNCDLL 0
#define GLBEGINDLL 1
#define GLCOLOR3FDLL 2
#define GLCOLOR4FDLL 3
#define GLCOLOR4UBDLL 4
#define GLCOLOR4UBVDLL 5
#define GLCOLORPOINTERDLL 6
#define GLDISABLECLIENTSTATEDLL 7
#define GLENABLECLIENTSTATEDLL 8
#define GLENDDLL 9
#define GLFOGFDLL 10
#define GLFOGFVDLL 11
#define GLFOGIDLL 12
#define GLFRUSTUMDLL 13
#define GLGETMATERIALFVDLL 14
#define GLGETTEXLEVELPARAMETERIVDLL 15
#define GLGETTEXPARAMETERIVDLL 16
#define GLLIGHTFVDLL 17
#define GLLIGHTMODELFVDLL 18
#define GLLINEWIDTHDLL 19
#define GLLOADIDENTITYDLL 20
#define GLLOADMATRIXFDLL 21
#define GLMATERIALFDLL 22
#define GLMATERIALFVDLL 23
#define GLMATRIXMODEDLL 24
#define GLMULTMATRIXDDLL 25
#define GLNORMAL3FDLL 26
#define GLNORMALPOINTERDLL 27
#define GLORTHODLL 28
#define GLPOINTSIZEDLL 29
#define GLPOPATTRIBDLL 30
#define GLPOPCLIENTATTRIBDLL 31
#define GLPOPMATRIXDLL 32
#define GLPUSHATTRIBDLL 33
#define GLPUSHCLIENTATTRIBDLL 34
#define GLPUSHMATRIXDLL 35
#define GLROTATEFDLL 36
#define GLSCALEFDLL 37
#define GLSHADEMODELDLL 38
#define GLTEXCOORD2FDLL 39
#define GLTEXCOORDPOINTERDLL 40
#define GLTEXENVFDLL 41
#define GLTEXENVIDLL 42
#define GLTRANSLATEFDLL 43
#define GLVERTEX3FDLL 44
#define GLVERTEX3FVDLL 45
#define GLVERTEXPOINTERDLL 46

#define GLBINDBUFFERARB 0
#define GLBINDBUFFERBASENV 1
#define GLBINDFRAMEBUFFEREXT 2
#define GLBINDMULTITEXTUREEXT 3
#define GLBINDRENDERBUFFEREXT 4
#define GLBUFFERDATAARB 5
#define GLCLAMPCOLORARB 6
#define GLCLIENTACTIVETEXTURE 7
#define GLCOPYMULTITEXSUBIMAGE2DEXT 8
#define GLDELETEBUFFERSARB 9
#define GLDELETEFRAMEBUFFERSEXT 10
#define GLDELETERENDERBUFFERSEXT 11
#define GLDISABLEVERTEXATTRIBARRAYARB 12
#define GLENABLEVERTEXATTRIBARRAYARB 13
#define GLFRAMEBUFFERRENDERBUFFEREXT 14
#define GLFRAMEBUFFERTEXTURE2DEXT 15
#define GLGENFRAMEBUFFERSEXT 16
#define GLGENRENDERBUFFERSEXT 17
#define GLGETPROGRAMENVPARAMETERFVARB 18
#define GLGETPROGRAMIVARB 19
#define GLGETTEXTUREIMAGEEXT 20
#define GLISBUFFERARB 21
#define GLLOADTRANSPOSEMATRIXF 22
#define GLMAPNAMEDBUFFEREXT 23
#define GLMULTITEXCOORD2F 24
#define GLMULTITEXCOORD2FV 25
#define GLMULTTRANSPOSEMATRIXF 26
#define GLNAMEDBUFFERDATAEXT 27
#define GLNAMEDBUFFERSUBDATAEXT 28
#define GLPOINTPARAMETERF 29
#define GLPOINTPARAMETERFV 30
#define GLPOINTPARAMETERI 31
#define GLPRIMITIVERESTARTINDEXNV 32
#define GLPROGRAMBUFFERPARAMETERSFVNV 33
#define GLPROGRAMENVPARAMETER4FARB 34
#define GLPROGRAMENVPARAMETER4FVARB 35
#define GLPROGRAMENVPARAMETERS4FVEXT 36
#define GLPROGRAMLOCALPARAMETER4FARB 37
#define GLPROGRAMLOCALPARAMETER4FVARB 38
#define GLPROGRAMLOCALPARAMETERS4FVEXT 39
#define GLRENDERBUFFERSTORAGEEXT 40
#define GLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENV 41
#define GLUNMAPNAMEDBUFFEREXT 42
#define GLVERTEXATTRIBPOINTERARB 43

#define GLBEGINGLUT 0
#define GLBITMAPGLUT 1
#define GLENDGLUT 2
#define GLEVALMESH2GLUT 3
#define GLMAP2FGLUT 4
#define GLMAPGRID2FGLUT 5
#define GLNORMAL3FGLUT 6
#define GLNORMAL3FVGLUT 7
#define GLPOLYGONMODEGLUT 8
#define GLPOPATTRIBGLUT 9
#define GLPOPMATRIXGLUT 10
#define GLPUSHATTRIBGLUT 11
#define GLPUSHMATRIXGLUT 12
#define GLROTATEFGLUT 13
#define GLSCALEFGLUT 14
#define GLTRANSLATEFGLUT 15
#define GLVERTEX2FGLUT 16
#define GLVERTEX3FGLUT 17
#define GLVERTEX3FVGLUT 18

typedef void (GLAPIENTRY* PFNGLALPHAFUNCDLLPROC)(GLenum func, GLfloat ref);
typedef void (GLAPIENTRY* PFNGLBEGINDLLPROC)(GLenum mode);
typedef void (GLAPIENTRY* PFNGLCOLOR3FDLLPROC)(GLfloat red, GLfloat green, GLfloat blue);
typedef void (GLAPIENTRY* PFNGLCOLOR4FDLLPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (GLAPIENTRY* PFNGLCOLOR4UBDLLPROC)(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
typedef void (GLAPIENTRY* PFNGLCOLOR4UBVDLLPROC)(GLubyte const * v);
typedef void (GLAPIENTRY* PFNGLCOLORPOINTERDLLPROC)(GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (GLAPIENTRY* PFNGLDISABLECLIENTSTATEDLLPROC)(GLenum array);
typedef void (GLAPIENTRY* PFNGLENABLECLIENTSTATEDLLPROC)(GLenum array);
typedef void (GLAPIENTRY* PFNGLENDDLLPROC)();
typedef void (GLAPIENTRY* PFNGLFOGFDLLPROC)(GLenum pname, GLfloat param);
typedef void (GLAPIENTRY* PFNGLFOGFVDLLPROC)(GLenum pname, GLfloat const * params);
typedef void (GLAPIENTRY* PFNGLFOGIDLLPROC)(GLenum pname, GLint param);
typedef void (GLAPIENTRY* PFNGLFRUSTUMDLLPROC)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
typedef void (GLAPIENTRY* PFNGLGETMATERIALFVDLLPROC)(GLenum face, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY* PFNGLGETTEXLEVELPARAMETERIVDLLPROC)(GLenum target, GLint level, GLenum pname, GLint * params);
typedef void (GLAPIENTRY* PFNGLGETTEXPARAMETERIVDLLPROC)(GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY* PFNGLLIGHTFVDLLPROC)(GLenum light, GLenum pname, GLfloat const * params);
typedef void (GLAPIENTRY* PFNGLLIGHTMODELFVDLLPROC)(GLenum pname, GLfloat const * params);
typedef void (GLAPIENTRY* PFNGLLINEWIDTHDLLPROC)(GLfloat width);
typedef void (GLAPIENTRY* PFNGLLOADIDENTITYDLLPROC)();
typedef void (GLAPIENTRY* PFNGLLOADMATRIXFDLLPROC)(GLfloat const * m);
typedef void (GLAPIENTRY* PFNGLMATERIALFDLLPROC)(GLenum face, GLenum pname, GLfloat param);
typedef void (GLAPIENTRY* PFNGLMATERIALFVDLLPROC)(GLenum face, GLenum pname, GLfloat const * params);
typedef void (GLAPIENTRY* PFNGLMATRIXMODEDLLPROC)(GLenum mode);
typedef void (GLAPIENTRY* PFNGLMULTMATRIXDDLLPROC)(GLdouble const * m);
typedef void (GLAPIENTRY* PFNGLNORMAL3FDLLPROC)(GLfloat nx, GLfloat ny, GLfloat nz);
typedef void (GLAPIENTRY* PFNGLNORMALPOINTERDLLPROC)(GLenum type, GLsizei stride, const void * pointer);
typedef void (GLAPIENTRY* PFNGLORTHODLLPROC)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
typedef void (GLAPIENTRY* PFNGLPOINTSIZEDLLPROC)(GLfloat size);
typedef void (GLAPIENTRY* PFNGLPOPATTRIBDLLPROC)();
typedef void (GLAPIENTRY* PFNGLPOPCLIENTATTRIBDLLPROC)();
typedef void (GLAPIENTRY* PFNGLPOPMATRIXDLLPROC)();
typedef void (GLAPIENTRY* PFNGLPUSHATTRIBDLLPROC)(GLbitfield mask);
typedef void (GLAPIENTRY* PFNGLPUSHCLIENTATTRIBDLLPROC)(GLbitfield mask);
typedef void (GLAPIENTRY* PFNGLPUSHMATRIXDLLPROC)();
typedef void (GLAPIENTRY* PFNGLROTATEFDLLPROC)(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAPIENTRY* PFNGLSCALEFDLLPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAPIENTRY* PFNGLSHADEMODELDLLPROC)(GLenum mode);
typedef void (GLAPIENTRY* PFNGLTEXCOORD2FDLLPROC)(GLfloat s, GLfloat t);
typedef void (GLAPIENTRY* PFNGLTEXCOORDPOINTERDLLPROC)(GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (GLAPIENTRY* PFNGLTEXENVFDLLPROC)(GLenum target, GLenum pname, GLfloat param);
typedef void (GLAPIENTRY* PFNGLTEXENVIDLLPROC)(GLenum target, GLenum pname, GLint param);
typedef void (GLAPIENTRY* PFNGLTRANSLATEFDLLPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAPIENTRY* PFNGLVERTEX3FDLLPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAPIENTRY* PFNGLVERTEX3FVDLLPROC)(GLfloat const * v);
typedef void (GLAPIENTRY* PFNGLVERTEXPOINTERDLLPROC)(GLint size, GLenum type, GLsizei stride, const void * pointer);

typedef void (GLAPIENTRY* PFNGLBINDBUFFERARBPROC)(GLenum target, GLuint buffer);
typedef void (GLAPIENTRY* PFNGLBINDBUFFERBASENVPROC)(GLenum target, GLuint index, GLuint buffer);
typedef void (GLAPIENTRY* PFNGLBINDFRAMEBUFFEREXTPROC)(GLenum target, GLuint framebuffer);
typedef void (GLAPIENTRY* PFNGLBINDMULTITEXTUREEXTPROC)(GLenum texunit, GLenum target, GLuint texture);
typedef void (GLAPIENTRY* PFNGLBINDRENDERBUFFEREXTPROC)(GLenum target, GLuint renderbuffer);
typedef void (GLAPIENTRY* PFNGLBUFFERDATAARBPROC)(GLenum target, GLsizeiptrARB size, const void * data, GLenum usage);
typedef void (GLAPIENTRY* PFNGLCLAMPCOLORARBPROC)(GLenum target, GLenum clamp);
typedef void (GLAPIENTRY* PFNGLCLIENTACTIVETEXTUREPROC)(GLenum texture);
typedef void (GLAPIENTRY* PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC)(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY* PFNGLDELETEBUFFERSARBPROC)(GLsizei n, GLuint const * buffers);
typedef void (GLAPIENTRY* PFNGLDELETEFRAMEBUFFERSEXTPROC)(GLsizei n, GLuint const * framebuffers);
typedef void (GLAPIENTRY* PFNGLDELETERENDERBUFFERSEXTPROC)(GLsizei n, GLuint const * renderbuffers);
typedef void (GLAPIENTRY* PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)(GLuint index);
typedef void (GLAPIENTRY* PFNGLENABLEVERTEXATTRIBARRAYARBPROC)(GLuint index);
typedef void (GLAPIENTRY* PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (GLAPIENTRY* PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (GLAPIENTRY* PFNGLGENFRAMEBUFFERSEXTPROC)(GLsizei n, GLuint * framebuffers);
typedef void (GLAPIENTRY* PFNGLGENRENDERBUFFERSEXTPROC)(GLsizei n, GLuint * renderbuffers);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMENVPARAMETERFVARBPROC)(GLenum target, GLuint index, GLfloat * params);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMIVARBPROC)(GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY* PFNGLGETTEXTUREIMAGEEXTPROC)(GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, void * pixels);
typedef GLboolean (GLAPIENTRY* PFNGLISBUFFERARBPROC)(GLuint buffer);
typedef void (GLAPIENTRY* PFNGLLOADTRANSPOSEMATRIXFPROC)(GLfloat const * m);
typedef void * (GLAPIENTRY* PFNGLMAPNAMEDBUFFEREXTPROC)(GLuint buffer, GLenum access);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD2FPROC)(GLenum target, GLfloat s, GLfloat t);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD2FVPROC)(GLenum target, GLfloat const * v);
typedef void (GLAPIENTRY* PFNGLMULTTRANSPOSEMATRIXFPROC)(GLfloat const * m);
typedef void (GLAPIENTRY* PFNGLNAMEDBUFFERDATAEXTPROC)(GLuint buffer, GLsizeiptr size, const void * data, GLenum usage);
typedef void (GLAPIENTRY* PFNGLNAMEDBUFFERSUBDATAEXTPROC)(GLuint buffer, GLintptr offset, GLsizeiptr size, const void * data);
typedef void (GLAPIENTRY* PFNGLPOINTPARAMETERFPROC)(GLenum pname, GLfloat param);
typedef void (GLAPIENTRY* PFNGLPOINTPARAMETERFVPROC)(GLenum pname, GLfloat const * params);
typedef void (GLAPIENTRY* PFNGLPOINTPARAMETERIPROC)(GLenum pname, GLint param);
typedef void (GLAPIENTRY* PFNGLPRIMITIVERESTARTINDEXNVPROC)(GLuint index);
typedef void (GLAPIENTRY* PFNGLPROGRAMBUFFERPARAMETERSFVNVPROC)(GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, GLfloat const * params);
typedef void (GLAPIENTRY* PFNGLPROGRAMENVPARAMETER4FARBPROC)(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLAPIENTRY* PFNGLPROGRAMENVPARAMETER4FVARBPROC)(GLenum target, GLuint index, GLfloat const * params);
typedef void (GLAPIENTRY* PFNGLPROGRAMENVPARAMETERS4FVEXTPROC)(GLenum target, GLuint index, GLsizei count, GLfloat const * params);
typedef void (GLAPIENTRY* PFNGLPROGRAMLOCALPARAMETER4FARBPROC)(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLAPIENTRY* PFNGLPROGRAMLOCALPARAMETER4FVARBPROC)(GLenum target, GLuint index, GLfloat const * params);
typedef void (GLAPIENTRY* PFNGLPROGRAMLOCALPARAMETERS4FVEXTPROC)(GLenum target, GLuint index, GLsizei count, GLfloat const * params);
typedef void (GLAPIENTRY* PFNGLRENDERBUFFERSTORAGEEXTPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY* PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC)(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height);
typedef GLboolean (GLAPIENTRY* PFNGLUNMAPNAMEDBUFFEREXTPROC)(GLuint buffer);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBPOINTERARBPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);

typedef void (GLAPIENTRY* PFNGLBEGINGLUTPROC)(GLenum mode);
typedef void (GLAPIENTRY* PFNGLBITMAPGLUTPROC)(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, GLubyte const * bitmap);
typedef void (GLAPIENTRY* PFNGLENDGLUTPROC)();
typedef void (GLAPIENTRY* PFNGLEVALMESH2GLUTPROC)(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
typedef void (GLAPIENTRY* PFNGLMAP2FGLUTPROC)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, GLfloat const * points);
typedef void (GLAPIENTRY* PFNGLMAPGRID2FGLUTPROC)(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
typedef void (GLAPIENTRY* PFNGLNORMAL3FGLUTPROC)(GLfloat nx, GLfloat ny, GLfloat nz);
typedef void (GLAPIENTRY* PFNGLNORMAL3FVGLUTPROC)(GLfloat const * v);
typedef void (GLAPIENTRY* PFNGLPOLYGONMODEGLUTPROC)(GLenum face, GLenum mode);
typedef void (GLAPIENTRY* PFNGLPOPATTRIBGLUTPROC)();
typedef void (GLAPIENTRY* PFNGLPOPMATRIXGLUTPROC)();
typedef void (GLAPIENTRY* PFNGLPUSHATTRIBGLUTPROC)(GLbitfield mask);
typedef void (GLAPIENTRY* PFNGLPUSHMATRIXGLUTPROC)();
typedef void (GLAPIENTRY* PFNGLROTATEFGLUTPROC)(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAPIENTRY* PFNGLSCALEFGLUTPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAPIENTRY* PFNGLTRANSLATEFGLUTPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAPIENTRY* PFNGLVERTEX2FGLUTPROC)(GLfloat x, GLfloat y);
typedef void (GLAPIENTRY* PFNGLVERTEX3FGLUTPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAPIENTRY* PFNGLVERTEX3FVGLUTPROC)(GLfloat const * v);

extern size_t glut_handle;

func_struct wrap_addr_dll[47] = {
    { 0x0000000140965A00, 0, (size_t)&glAlphaFuncDLL, }, // glAlphaFunc
    { 0x0000000140965A70, 0, (size_t)&glBeginDLL, }, // glBegin
    { 0x0000000140965A88, 0, (size_t)&glColor3fDLL, }, // glColor3f
    { 0x0000000140965A90, 0, (size_t)&glColor4fDLL, }, // glColor4f
    { 0x0000000140965B88, 0, (size_t)&glColor4ubDLL, }, // glColor4ub
    { 0x0000000140965B90, 0, (size_t)&glColor4ubvDLL, }, // glColor4ubv
    { 0x0000000140965C30, 0, (size_t)&glColorPointerDLL, }, // glColorPointer
    { 0x0000000140965C28, 0, (size_t)&glDisableClientStateDLL, }, // glDisableClientState
    { 0x0000000140965BE8, 0, (size_t)&glEnableClientStateDLL, }, // glEnableClientState
    { 0x0000000140965A78, 0, (size_t)&glEndDLL, }, // glEnd
    { 0x0000000140965A58, 0, (size_t)&glFogfDLL, }, // glFogf
    { 0x0000000140965A60, 0, (size_t)&glFogfvDLL, }, // glFogfv
    { 0x0000000140965A68, 0, (size_t)&glFogiDLL, }, // glFogi
    { 0x0000000140965C98, 0, (size_t)&glFrustumDLL, }, // glFrustum
    { 0x0000000140965CB0, 0, (size_t)&glGetMaterialfvDLL, }, // glGetMaterialfv
    { 0x0000000140965AA0, 0, (size_t)&glGetTexLevelParameterivDLL, }, // glGetTexLevelParameteriv
    { 0x0000000140965AA8, 0, (size_t)&glGetTexParameterivDLL, }, // glGetTexParameteriv
    { 0x0000000140965AC8, 0, (size_t)&glLightfvDLL, }, // glLightfv
    { 0x0000000140965AC0, 0, (size_t)&glLightModelfvDLL, }, // glLightModelfv
    { 0x0000000140965B10, 0, (size_t)&glLineWidthDLL, }, // glLineWidth
    { 0x0000000140965C88, 0, (size_t)&glLoadIdentityDLL, }, // glLoadIdentity
    { 0x0000000140965A50, 0, (size_t)&glLoadMatrixfDLL, }, // glLoadMatrixf
    { 0x0000000140965A08, 0, (size_t)&glMaterialfDLL, }, // glMaterialf
    { 0x0000000140965A80, 0, (size_t)&glMaterialfvDLL, }, // glMaterialfv
    { 0x0000000140965C80, 0, (size_t)&glMatrixModeDLL, }, // glMatrixMode
    { 0x0000000140965B48, 0, (size_t)&glMultMatrixdDLL, }, // glMultMatrixd
    { 0x0000000140965B18, 0, (size_t)&glNormal3fDLL, }, // glNormal3f
    { 0x0000000140965B20, 0, (size_t)&glNormalPointerDLL, }, // glNormalPointer
    { 0x0000000140965B50, 0, (size_t)&glOrthoDLL, }, // glOrtho
    { 0x0000000140965BE0, 0, (size_t)&glPointSizeDLL, }, // glPointSize
    { 0x0000000140965BD8, 0, (size_t)&glPopAttribDLL, }, // glPopAttrib
    { 0x0000000140965BD0, 0, (size_t)&glPopClientAttribDLL, }, // glPopClientAttrib
    { 0x0000000140965CA8, 0, (size_t)&glPopMatrixDLL, }, // glPopMatrix
    { 0x0000000140965BC8, 0, (size_t)&glPushAttribDLL, }, // glPushAttrib
    { 0x0000000140965BC0, 0, (size_t)&glPushClientAttribDLL, }, // glPushClientAttrib
    { 0x0000000140965CA0, 0, (size_t)&glPushMatrixDLL, }, // glPushMatrix
    { 0x0000000140965C70, 0, (size_t)&glRotatefDLL, }, // glRotatef
    { 0x0000000140965C68, 0, (size_t)&glScalefDLL, }, // glScalef
    { 0x0000000140965C20, 0, (size_t)&glShadeModelDLL, }, // glShadeModel
    { 0x0000000140965B80, 0, (size_t)&glTexCoord2fDLL, }, // glTexCoord2f
    { 0x0000000140965A30, 0, (size_t)&glTexCoordPointerDLL, }, // glTexCoordPointer
    { 0x0000000140965B28, 0, (size_t)&glTexEnvfDLL, }, // glTexEnvf
    { 0x0000000140965BB8, 0, (size_t)&glTexEnviDLL, }, // glTexEnvi
    { 0x0000000140965C60, 0, (size_t)&glTranslatefDLL, }, // glTranslatef
    { 0x0000000140965AB8, 0, (size_t)&glVertex3fDLL, }, // glVertex3f
    { 0x0000000140965B30, 0, (size_t)&glVertex3fvDLL, }, // glVertex3fv
    { 0x0000000140965B00, 0, (size_t)&glVertexPointerDLL, }, // glVertexPointer
};

func_struct wrap_addr[44] = {
    { 0x00000001411A4B10, 0, (size_t)&glBindBufferARB, }, // glBindBufferARB
    { 0x00000001411A3578, 0, (size_t)&glBindBufferBaseNV, }, // glBindBufferBaseNV
    { 0x00000001411A54D8, 0, (size_t)&glBindFramebufferEXT, }, // glBindFramebufferEXT
    { 0x00000001411A3818, 0, (size_t)&glBindMultiTextureEXT, }, // glBindMultiTextureEXT
    { 0x00000001411A54A8, 0, (size_t)&glBindRenderbufferEXT, }, // glBindRenderbufferEXT
    { 0x00000001411A4B30, 0, (size_t)&glBufferDataARB, }, // glBufferDataARB
    { 0x00000001411A4D00, 0, (size_t)&glClampColorARB, }, // glClampColorARB
    { 0x00000001411A3DC8, 0, (size_t)&glClientActiveTexture, }, // glClientActiveTexture
    { 0x00000001411A37D0, 0, (size_t)&glCopyMultiTexSubImage2DEXT, }, // glCopyMultiTexSubImage2DEXT
    { 0x00000001411A4B18, 0, (size_t)&glDeleteBuffersARB, }, // glDeleteBuffersARB
    { 0x00000001411A54E0, 0, (size_t)&glDeleteFramebuffersEXT, }, // glDeleteFramebuffersEXT
    { 0x00000001411A54B0, 0, (size_t)&glDeleteRenderbuffersEXT, }, // glDeleteRenderbuffersEXT
    { 0x00000001411A4A50, 0, (size_t)&glDisableVertexAttribArrayARB, }, // glDisableVertexAttribArrayARB
    { 0x00000001411A4A48, 0, (size_t)&glEnableVertexAttribArrayARB, }, // glEnableVertexAttribArrayARB
    { 0x00000001411A5510, 0, (size_t)&glFramebufferRenderbufferEXT, }, // glFramebufferRenderbufferEXT
    { 0x00000001411A5500, 0, (size_t)&glFramebufferTexture2DEXT, }, // glFramebufferTexture2DEXT
    { 0x00000001411A54E8, 0, (size_t)&glGenFramebuffersEXT, }, // glGenFramebuffersEXT
    { 0x00000001411A54B8, 0, (size_t)&glGenRenderbuffersEXT, }, // glGenRenderbuffersEXT
    { 0x00000001411A4AC0, 0, (size_t)&glGetProgramEnvParameterfvARB, }, // glGetProgramEnvParameterfvARB
    { 0x00000001411A4AD8, 0, (size_t)&glGetProgramivARB, }, // glGetProgramivARB
    { 0x00000001411A3738, 0, (size_t)&glGetTextureImageEXT, }, // glGetTextureImageEXT
    { 0x00000001411A4B28, 0, (size_t)&glIsBufferARB, }, // glIsBufferARB
    { 0x00000001411A3FD8, 0, (size_t)&glLoadTransposeMatrixf, }, // glLoadTransposeMatrixf
    { 0x00000001411A3B20, 0, (size_t)&glMapNamedBufferEXT, }, // glMapNamedBufferEXT
    { 0x00000001411A3E78, 0, (size_t)&glMultiTexCoord2f, }, // glMultiTexCoord2f
    { 0x00000001411A3E88, 0, (size_t)&glMultiTexCoord2fv, }, // glMultiTexCoord2fv
    { 0x00000001411A3FE8, 0, (size_t)&glMultTransposeMatrixf, }, // glMultTransposeMatrixf
    { 0x00000001411A3B10, 0, (size_t)&glNamedBufferDataEXT, }, // glNamedBufferDataEXT
    { 0x00000001411A3B18, 0, (size_t)&glNamedBufferSubDataEXT, }, // glNamedBufferSubDataEXT
    { 0x00000001411A4078, 0, (size_t)&glPointParameterf, }, // glPointParameterf
    { 0x00000001411A4080, 0, (size_t)&glPointParameterfv, }, // glPointParameterfv
    { 0x00000001411A4088, 0, (size_t)&glPointParameteri, }, // glPointParameteri
    { 0x00000001411A5488, 0, (size_t)&glPrimitiveRestartIndexNV, }, // glPrimitiveRestartIndexNV
    { 0x00000001411A3508, 0, (size_t)&glProgramBufferParametersfvNV, }, // glProgramBufferParametersfvNV
    { 0x00000001411A4A88, 0, (size_t)&glProgramEnvParameter4fARB, }, // glProgramEnvParameter4fARB
    { 0x00000001411A4A90, 0, (size_t)&glProgramEnvParameter4fvARB, }, // glProgramEnvParameter4fvARB
    { 0x00000001411A5548, 0, (size_t)&glProgramEnvParameters4fvEXT, }, // glProgramEnvParameters4fvEXT
    { 0x00000001411A4AA8, 0, (size_t)&glProgramLocalParameter4fARB, }, // glProgramLocalParameter4fARB
    { 0x00000001411A4AB0, 0, (size_t)&glProgramLocalParameter4fvARB, }, // glProgramLocalParameter4fvARB
    { 0x00000001411A5550, 0, (size_t)&glProgramLocalParameters4fvEXT, }, // glProgramLocalParameters4fvEXT
    { 0x00000001411A54C0, 0, (size_t)&glRenderbufferStorageEXT, }, // glRenderbufferStorageEXT
    { 0x00000001411A3500, 0, (size_t)&glRenderbufferStorageMultisampleCoverageNV, }, // glRenderbufferStorageMultisampleCoverageNV
    { 0x00000001411A3B28, 0, (size_t)&glUnmapNamedBufferEXT, }, // glUnmapNamedBufferEXT
    { 0x00000001411A4A40, 0, (size_t)&glVertexAttribPointerARB, }, // glVertexAttribPointerARB
};

func_struct wrap_addr_glut[19] = {
    { 0x000000000002A380, 0, (size_t)&glBeginGLUT, }, // glBegin
    { 0x000000000002A348, 0, (size_t)&glBitmapGLUT, }, // glBitmap
    { 0x000000000002A388, 0, (size_t)&glEndGLUT, }, // glEnd
    { 0x000000000002A3E0, 0, (size_t)&glEvalMesh2GLUT, }, // glEvalMesh2
    { 0x000000000002A3E8, 0, (size_t)&glMap2fGLUT, }, // glMap2f
    { 0x000000000002A3F0, 0, (size_t)&glMapGrid2fGLUT, }, // glMapGrid2f
    { 0x000000000002A390, 0, (size_t)&glNormal3fGLUT, }, // glNormal3f
    { 0x000000000002A398, 0, (size_t)&glNormal3fvGLUT, }, // glNormal3fv
    { 0x000000000002A3A0, 0, (size_t)&glPolygonModeGLUT, }, // glPolygonMode
    { 0x000000000002A3A8, 0, (size_t)&glPopAttribGLUT, }, // glPopAttrib
    { 0x000000000002A3F8, 0, (size_t)&glPopMatrixGLUT, }, // glPopMatrix
    { 0x000000000002A3B0, 0, (size_t)&glPushAttribGLUT, }, // glPushAttrib
    { 0x000000000002A400, 0, (size_t)&glPushMatrixGLUT, }, // glPushMatrix
    { 0x000000000002A408, 0, (size_t)&glRotatefGLUT, }, // glRotatef
    { 0x000000000002A410, 0, (size_t)&glScalefGLUT, }, // glScalef
    { 0x000000000002A3C8, 0, (size_t)&glTranslatefGLUT, }, // glTranslatef
    { 0x000000000002A3D0, 0, (size_t)&glVertex2fGLUT, }, // glVertex2f
    { 0x000000000002A3B8, 0, (size_t)&glVertex3fGLUT, }, // glVertex3f
    { 0x000000000002A3C0, 0, (size_t)&glVertex3fvGLUT, }, // glVertex3fv
};

bool DIVA_GL_VERSION_4_1 = false;
bool DIVA_GL_VERSION_4_2 = false;
bool DIVA_GL_VERSION_4_3 = false;
bool DIVA_GL_VERSION_4_4 = false;
bool DIVA_GL_VERSION_4_5 = false;
bool DIVA_GL_VERSION_4_6 = false;

PFNGLBINDTEXTUREDLLPROC* divagl_glBindTextureDLL
    = (PFNGLBINDTEXTUREDLLPROC*)0x0000000140965BF8; // glBindTexture
PFNGLBLENDFUNCDLLPROC* divagl_glBlendFuncDLL
    = (PFNGLBLENDFUNCDLLPROC*)0x0000000140965A20; // glBlendFunc
PFNGLCLEARDLLPROC* divagl_glClearDLL
    = (PFNGLCLEARDLLPROC*)0x0000000140965C58; // glClear
PFNGLCLEARCOLORDLLPROC* divagl_glClearColorDLL
    = (PFNGLCLEARCOLORDLLPROC*)0x0000000140965C38; // glClearColor
PFNGLCLEARDEPTHDLLPROC* divagl_glClearDepthDLL
    = (PFNGLCLEARDEPTHDLLPROC*)0x0000000140965C08; // glClearDepth
PFNGLCLEARSTENCILDLLPROC* divagl_glClearStencilDLL
    = (PFNGLCLEARSTENCILDLLPROC*)0x0000000140965C10; // glClearStencil
PFNGLCOLORMASKDLLPROC* divagl_glColorMaskDLL
    = (PFNGLCOLORMASKDLLPROC*)0x0000000140965A38; // glColorMask
PFNGLCOPYTEXIMAGE2DDLLPROC* divagl_glCopyTexImage2DDLL
    = (PFNGLCOPYTEXIMAGE2DDLLPROC*)0x0000000140965B40; // glCopyTexImage2D
PFNGLCOPYTEXSUBIMAGE2DDLLPROC* divagl_glCopyTexSubImage2DDLL
    = (PFNGLCOPYTEXSUBIMAGE2DDLLPROC*)0x0000000140965A98; // glCopyTexSubImage2D
PFNGLCULLFACEDLLPROC* divagl_glCullFaceDLL
    = (PFNGLCULLFACEDLLPROC*)0x0000000140965C18; // glCullFace
PFNGLDELETETEXTURESDLLPROC* divagl_glDeleteTexturesDLL
    = (PFNGLDELETETEXTURESDLLPROC*)0x0000000140965AD0; // glDeleteTextures
PFNGLDEPTHFUNCDLLPROC* divagl_glDepthFuncDLL
    = (PFNGLDEPTHFUNCDLLPROC*)0x0000000140965C40; // glDepthFunc
PFNGLDEPTHMASKDLLPROC* divagl_glDepthMaskDLL
    = (PFNGLDEPTHMASKDLLPROC*)0x0000000140965A28; // glDepthMask
PFNGLDISABLEDLLPROC* divagl_glDisableDLL
    = (PFNGLDISABLEDLLPROC*)0x0000000140965C48; // glDisable
PFNGLDRAWARRAYSDLLPROC* divagl_glDrawArraysDLL
    = (PFNGLDRAWARRAYSDLLPROC*)0x0000000140965BF0; // glDrawArrays
PFNGLDRAWBUFFERDLLPROC* divagl_glDrawBufferDLL
    = (PFNGLDRAWBUFFERDLLPROC*)0x0000000140965B60; // glDrawBuffer
PFNGLDRAWELEMENTSDLLPROC* divagl_glDrawElementsDLL
    = (PFNGLDRAWELEMENTSDLLPROC*)0x0000000140965A48; // glDrawElements
PFNGLENABLEDLLPROC* divagl_glEnableDLL
    = (PFNGLENABLEDLLPROC*)0x0000000140965C50; // glEnable
PFNGLFINISHDLLPROC* divagl_glFinishDLL
    = (PFNGLFINISHDLLPROC*)0x0000000140965B68; // glFinish
PFNGLFRONTFACEDLLPROC* divagl_glFrontFaceDLL
    = (PFNGLFRONTFACEDLLPROC*)0x0000000140965BB0; // glFrontFace
PFNGLGENTEXTURESDLLPROC* divagl_glGenTexturesDLL
    = (PFNGLGENTEXTURESDLLPROC*)0x0000000140965AD8; // glGenTextures
PFNGLGETBOOLEANVDLLPROC* divagl_glGetBooleanvDLL
    = (PFNGLGETBOOLEANVDLLPROC*)0x0000000140965AF0; // glGetBooleanv
PFNGLGETERRORDLLPROC* divagl_glGetErrorDLL
    = (PFNGLGETERRORDLLPROC*)0x0000000140965BA8; // glGetError
PFNGLGETFLOATVDLLPROC* divagl_glGetFloatvDLL
    = (PFNGLGETFLOATVDLLPROC*)0x0000000140965C90; // glGetFloatv
PFNGLGETINTEGERVDLLPROC* divagl_glGetIntegervDLL
    = (PFNGLGETINTEGERVDLLPROC*)0x0000000140965AF8; // glGetIntegerv
PFNGLGETTEXIMAGEDLLPROC* divagl_glGetTexImageDLL
    = (PFNGLGETTEXIMAGEDLLPROC*)0x0000000140965C00; // glGetTexImage
PFNGLISENABLEDDLLPROC* divagl_glIsEnabledDLL
    = (PFNGLISENABLEDDLLPROC*)0x0000000140965B08; // glIsEnabled
PFNGLPIXELSTOREIDLLPROC* divagl_glPixelStoreiDLL
    = (PFNGLPIXELSTOREIDLLPROC*)0x0000000140965BA0; // glPixelStorei
PFNGLPOLYGONMODEDLLPROC* divagl_glPolygonModeDLL
    = (PFNGLPOLYGONMODEDLLPROC*)0x0000000140965B98; // glPolygonMode
PFNGLREADBUFFERDLLPROC* divagl_glReadBufferDLL
    = (PFNGLREADBUFFERDLLPROC*)0x0000000140965B70; // glReadBuffer
PFNGLREADPIXELSDLLPROC* divagl_glReadPixelsDLL
    = (PFNGLREADPIXELSDLLPROC*)0x0000000140965B78; // glReadPixels
PFNGLSCISSORDLLPROC* divagl_glScissorDLL
    = (PFNGLSCISSORDLLPROC*)0x0000000140965A40; // glScissor
PFNGLTEXIMAGE1DDLLPROC* divagl_glTexImage1DDLL
    = (PFNGLTEXIMAGE1DDLLPROC*)0x0000000140965B58; // glTexImage1D
PFNGLTEXIMAGE2DDLLPROC* divagl_glTexImage2DDLL
    = (PFNGLTEXIMAGE2DDLLPROC*)0x0000000140965AE0; // glTexImage2D
PFNGLTEXPARAMETERFDLLPROC* divagl_glTexParameterfDLL
    = (PFNGLTEXPARAMETERFDLLPROC*)0x0000000140965AE8; // glTexParameterf
PFNGLTEXPARAMETERFVDLLPROC* divagl_glTexParameterfvDLL
    = (PFNGLTEXPARAMETERFVDLLPROC*)0x0000000140965A10; // glTexParameterfv
PFNGLTEXPARAMETERIDLLPROC* divagl_glTexParameteriDLL
    = (PFNGLTEXPARAMETERIDLLPROC*)0x0000000140965A18; // glTexParameteri
PFNGLTEXSUBIMAGE2DDLLPROC* divagl_glTexSubImage2DDLL
    = (PFNGLTEXSUBIMAGE2DDLLPROC*)0x0000000140965AB0; // glTexSubImage2D
PFNGLVIEWPORTDLLPROC* divagl_glViewportDLL
    = (PFNGLVIEWPORTDLLPROC*)0x0000000140965C78; // glViewport
PFNWGLGETPROCADDRESSDLLPROC* divagl_wglGetProcAddressDLL
    = (PFNWGLGETPROCADDRESSDLLPROC*)0x0000000140965B38; // wglGetProcAddress

PFNGLACTIVESTENCILFACEEXTPROC* divagl_glActiveStencilFaceEXT
    = (PFNGLACTIVESTENCILFACEEXTPROC*)0x00000001411A52D0; // glActiveStencilFaceEXT
PFNGLACTIVETEXTUREPROC* divagl_glActiveTexture
    = (PFNGLACTIVETEXTUREPROC*)0x00000001411A3DB8; // glActiveTexture
PFNGLACTIVETEXTUREARBPROC* divagl_glActiveTextureARB
    = (PFNGLACTIVETEXTUREARBPROC*)0x00000001411A4720; // glActiveTextureARB
PFNGLACTIVEVARYINGNVPROC* divagl_glActiveVaryingNV
    = (PFNGLACTIVEVARYINGNVPROC*)0x00000001411A3588; // glActiveVaryingNV
PFNGLAREPROGRAMSRESIDENTNVPROC* divagl_glAreProgramsResidentNV
    = (PFNGLAREPROGRAMSRESIDENTNVPROC*)0x00000001411A5088; // glAreProgramsResidentNV
PFNGLARETEXTURESRESIDENTEXTPROC* divagl_glAreTexturesResidentEXT
    = (PFNGLARETEXTURESRESIDENTEXTPROC*)0x00000001411A4E30; // glAreTexturesResidentEXT
PFNGLARRAYELEMENTEXTPROC* divagl_glArrayElementEXT
    = (PFNGLARRAYELEMENTEXTPROC*)0x00000001411A4E60; // glArrayElementEXT
PFNGLATTACHOBJECTARBPROC* divagl_glAttachObjectARB
    = (PFNGLATTACHOBJECTARBPROC*)0x00000001411A4BE0; // glAttachObjectARB
PFNGLATTACHSHADERPROC* divagl_glAttachShader
    = (PFNGLATTACHSHADERPROC*)0x00000001411A4260; // glAttachShader
PFNGLBEGINCONDITIONALRENDERPROC* divagl_glBeginConditionalRender
    = (PFNGLBEGINCONDITIONALRENDERPROC*)0x00000001411A45B0; // glBeginConditionalRender
PFNGLBEGINCONDITIONALRENDERNVPROC* divagl_glBeginConditionalRenderNV
    = (PFNGLBEGINCONDITIONALRENDERNVPROC*)0x00000001411A35F0; // glBeginConditionalRenderNV
PFNGLBEGINOCCLUSIONQUERYNVPROC* divagl_glBeginOcclusionQueryNV
    = (PFNGLBEGINOCCLUSIONQUERYNVPROC*)0x00000001411A52A0; // glBeginOcclusionQueryNV
PFNGLBEGINQUERYPROC* divagl_glBeginQuery
    = (PFNGLBEGINQUERYPROC*)0x00000001411A41B8; // glBeginQuery
PFNGLBEGINQUERYARBPROC* divagl_glBeginQueryARB
    = (PFNGLBEGINQUERYARBPROC*)0x00000001411A4B80; // glBeginQueryARB
PFNGLBEGINTRANSFORMFEEDBACKPROC* divagl_glBeginTransformFeedback
    = (PFNGLBEGINTRANSFORMFEEDBACKPROC*)0x00000001411A4580; // glBeginTransformFeedback
PFNGLBEGINTRANSFORMFEEDBACKNVPROC* divagl_glBeginTransformFeedbackNV
    = (PFNGLBEGINTRANSFORMFEEDBACKNVPROC*)0x00000001411A3550; // glBeginTransformFeedbackNV
PFNGLBINDATTRIBLOCATIONPROC* divagl_glBindAttribLocation
    = (PFNGLBINDATTRIBLOCATIONPROC*)0x00000001411A4268; // glBindAttribLocation
PFNGLBINDATTRIBLOCATIONARBPROC* divagl_glBindAttribLocationARB
    = (PFNGLBINDATTRIBLOCATIONARBPROC*)0x00000001411A4CE0; // glBindAttribLocationARB
PFNGLBINDBUFFERPROC* divagl_glBindBuffer
    = (PFNGLBINDBUFFERPROC*)0x00000001411A41E0; // glBindBuffer
PFNGLBINDBUFFERBASEPROC* divagl_glBindBufferBase
    = (PFNGLBINDBUFFERBASEPROC*)0x00000001411A4598; // glBindBufferBase
PFNGLBINDBUFFEROFFSETNVPROC* divagl_glBindBufferOffsetNV
    = (PFNGLBINDBUFFEROFFSETNVPROC*)0x00000001411A3570; // glBindBufferOffsetNV
PFNGLBINDBUFFERRANGEPROC* divagl_glBindBufferRange
    = (PFNGLBINDBUFFERRANGEPROC*)0x00000001411A4590; // glBindBufferRange
PFNGLBINDBUFFERRANGENVPROC* divagl_glBindBufferRangeNV
    = (PFNGLBINDBUFFERRANGENVPROC*)0x00000001411A3568; // glBindBufferRangeNV
PFNGLBINDFRAGDATALOCATIONPROC* divagl_glBindFragDataLocation
    = (PFNGLBINDFRAGDATALOCATIONPROC*)0x00000001411A4680; // glBindFragDataLocation
PFNGLBINDFRAGDATALOCATIONEXTPROC* divagl_glBindFragDataLocationEXT
    = (PFNGLBINDFRAGDATALOCATIONEXTPROC*)0x00000001411A56C0; // glBindFragDataLocationEXT
PFNGLBINDFRAMEBUFFERPROC* divagl_glBindFramebuffer
    = (PFNGLBINDFRAMEBUFFERPROC*)0x00000001411A4D50; // glBindFramebuffer
PFNGLBINDPROGRAMARBPROC* divagl_glBindProgramARB
    = (PFNGLBINDPROGRAMARBPROC*)0x00000001411A4A60; // glBindProgramARB
PFNGLBINDPROGRAMNVPROC* divagl_glBindProgramNV
    = (PFNGLBINDPROGRAMNVPROC*)0x00000001411A5090; // glBindProgramNV
PFNGLBINDRENDERBUFFERPROC* divagl_glBindRenderbuffer
    = (PFNGLBINDRENDERBUFFERPROC*)0x00000001411A4D20; // glBindRenderbuffer
PFNGLBINDSAMPLERPROC* divagl_glBindSampler
    = (PFNGLBINDSAMPLERPROC*)0x00000001411A3FA0; // glBindSampler
PFNGLBINDTEXTUREEXTPROC* divagl_glBindTextureEXT
    = (PFNGLBINDTEXTUREEXTPROC*)0x00000001411A4E38; // glBindTextureEXT
PFNGLBINDVERTEXARRAYPROC* divagl_glBindVertexArray
    = (PFNGLBINDVERTEXARRAYPROC*)0x00000001411A4DF0; // glBindVertexArray
PFNGLBLENDCOLORPROC* divagl_glBlendColor
    = (PFNGLBLENDCOLORPROC*)0x00000001411A3B58; // glBlendColor
PFNGLBLENDCOLOREXTPROC* divagl_glBlendColorEXT
    = (PFNGLBLENDCOLOREXTPROC*)0x00000001411A4E10; // glBlendColorEXT
PFNGLBLENDEQUATIONPROC* divagl_glBlendEquation
    = (PFNGLBLENDEQUATIONPROC*)0x00000001411A3B68; // glBlendEquation
PFNGLBLENDEQUATIONEXTPROC* divagl_glBlendEquationEXT
    = (PFNGLBLENDEQUATIONEXTPROC*)0x00000001411A4EA8; // glBlendEquationEXT
PFNGLBLENDEQUATIONSEPARATEPROC* divagl_glBlendEquationSeparate
    = (PFNGLBLENDEQUATIONSEPARATEPROC*)0x00000001411A4238; // glBlendEquationSeparate
PFNGLBLENDEQUATIONSEPARATEEXTPROC* divagl_glBlendEquationSeparateEXT
    = (PFNGLBLENDEQUATIONSEPARATEEXTPROC*)0x00000001411A5498; // glBlendEquationSeparateEXT
PFNGLBLENDFUNCSEPARATEPROC* divagl_glBlendFuncSeparate
    = (PFNGLBLENDFUNCSEPARATEPROC*)0x00000001411A4038; // glBlendFuncSeparate
PFNGLBLENDFUNCSEPARATEEXTPROC* divagl_glBlendFuncSeparateEXT
    = (PFNGLBLENDFUNCSEPARATEEXTPROC*)0x00000001411A4FC0; // glBlendFuncSeparateEXT
PFNGLBLITFRAMEBUFFERPROC* divagl_glBlitFramebuffer
    = (PFNGLBLITFRAMEBUFFERPROC*)0x00000001411A4DA0; // glBlitFramebuffer
PFNGLBLITFRAMEBUFFEREXTPROC* divagl_glBlitFramebufferEXT
    = (PFNGLBLITFRAMEBUFFEREXTPROC*)0x00000001411A5528; // glBlitFramebufferEXT
PFNGLBUFFERDATAPROC* divagl_glBufferData
    = (PFNGLBUFFERDATAPROC*)0x00000001411A4200; // glBufferData
PFNGLBUFFERSUBDATAPROC* divagl_glBufferSubData
    = (PFNGLBUFFERSUBDATAPROC*)0x00000001411A4208; // glBufferSubData
PFNGLBUFFERSUBDATAARBPROC* divagl_glBufferSubDataARB
    = (PFNGLBUFFERSUBDATAARBPROC*)0x00000001411A4B38; // glBufferSubDataARB
PFNGLCHECKFRAMEBUFFERSTATUSPROC* divagl_glCheckFramebufferStatus
    = (PFNGLCHECKFRAMEBUFFERSTATUSPROC*)0x00000001411A4D68; // glCheckFramebufferStatus
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC* divagl_glCheckFramebufferStatusEXT
    = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC*)0x00000001411A54F0; // glCheckFramebufferStatusEXT
PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC* divagl_glCheckNamedFramebufferStatusEXT
    = (PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC*)0x00000001411A3B80; // glCheckNamedFramebufferStatusEXT
PFNGLCLEARBUFFERFIPROC* divagl_glClearBufferfi
    = (PFNGLCLEARBUFFERFIPROC*)0x00000001411A4708; // glClearBufferfi
PFNGLCLEARBUFFERFVPROC* divagl_glClearBufferfv
    = (PFNGLCLEARBUFFERFVPROC*)0x00000001411A4700; // glClearBufferfv
PFNGLCLEARBUFFERIVPROC* divagl_glClearBufferiv
    = (PFNGLCLEARBUFFERIVPROC*)0x00000001411A46F0; // glClearBufferiv
PFNGLCLEARBUFFERUIVPROC* divagl_glClearBufferuiv
    = (PFNGLCLEARBUFFERUIVPROC*)0x00000001411A46F8; // glClearBufferuiv
PFNGLCLEARCOLORIIEXTPROC* divagl_glClearColorIiEXT
    = (PFNGLCLEARCOLORIIEXTPROC*)0x00000001411A35E0; // glClearColorIiEXT
PFNGLCLEARCOLORIUIEXTPROC* divagl_glClearColorIuiEXT
    = (PFNGLCLEARCOLORIUIEXTPROC*)0x00000001411A35E8; // glClearColorIuiEXT
PFNGLCLEARDEPTHDNVPROC* divagl_glClearDepthdNV
    = (PFNGLCLEARDEPTHDNVPROC*)0x00000001411A34F0; // glClearDepthdNV
PFNGLCLIENTACTIVETEXTUREARBPROC* divagl_glClientActiveTextureARB
    = (PFNGLCLIENTACTIVETEXTUREARBPROC*)0x00000001411A4728; // glClientActiveTextureARB
PFNGLCLIENTATTRIBDEFAULTEXTPROC* divagl_glClientAttribDefaultEXT
    = (PFNGLCLIENTATTRIBDEFAULTEXTPROC*)0x00000001411A3630; // glClientAttribDefaultEXT
PFNGLCOLOR3HNVPROC* divagl_glColor3hNV
    = (PFNGLCOLOR3HNVPROC*)0x00000001411A5350; // glColor3hNV
PFNGLCOLOR3HVNVPROC* divagl_glColor3hvNV
    = (PFNGLCOLOR3HVNVPROC*)0x00000001411A5358; // glColor3hvNV
PFNGLCOLOR4HNVPROC* divagl_glColor4hNV
    = (PFNGLCOLOR4HNVPROC*)0x00000001411A5360; // glColor4hNV
PFNGLCOLOR4HVNVPROC* divagl_glColor4hvNV
    = (PFNGLCOLOR4HVNVPROC*)0x00000001411A5368; // glColor4hvNV
PFNGLCOLORMASKIPROC* divagl_glColorMaski
    = (PFNGLCOLORMASKIPROC*)0x00000001411A4550; // glColorMaski
PFNGLCOLORMASKINDEXEDEXTPROC* divagl_glColorMaskIndexedEXT
    = (PFNGLCOLORMASKINDEXEDEXTPROC*)0x00000001411A3520; // glColorMaskIndexedEXT
PFNGLCOLORPOINTEREXTPROC* divagl_glColorPointerEXT
    = (PFNGLCOLORPOINTEREXTPROC*)0x00000001411A4E68; // glColorPointerEXT
PFNGLCOLORSUBTABLEPROC* divagl_glColorSubTable
    = (PFNGLCOLORSUBTABLEPROC*)0x00000001411A3BF8; // glColorSubTable
PFNGLCOLORSUBTABLEEXTPROC* divagl_glColorSubTableEXT
    = (PFNGLCOLORSUBTABLEEXTPROC*)0x00000001411A4EC0; // glColorSubTableEXT
PFNGLCOLORTABLEPROC* divagl_glColorTable
    = (PFNGLCOLORTABLEPROC*)0x00000001411A3B88; // glColorTable
PFNGLCOLORTABLEEXTPROC* divagl_glColorTableEXT
    = (PFNGLCOLORTABLEEXTPROC*)0x00000001411A4EC8; // glColorTableEXT
PFNGLCOLORTABLEPARAMETERFVPROC* divagl_glColorTableParameterfv
    = (PFNGLCOLORTABLEPARAMETERFVPROC*)0x00000001411A3B98; // glColorTableParameterfv
PFNGLCOLORTABLEPARAMETERIVPROC* divagl_glColorTableParameteriv
    = (PFNGLCOLORTABLEPARAMETERIVPROC*)0x00000001411A3BA8; // glColorTableParameteriv
PFNGLCOMBINERINPUTNVPROC* divagl_glCombinerInputNV
    = (PFNGLCOMBINERINPUTNVPROC*)0x00000001411A4FF8; // glCombinerInputNV
PFNGLCOMBINEROUTPUTNVPROC* divagl_glCombinerOutputNV
    = (PFNGLCOMBINEROUTPUTNVPROC*)0x00000001411A5000; // glCombinerOutputNV
PFNGLCOMBINERPARAMETERFNVPROC* divagl_glCombinerParameterfNV
    = (PFNGLCOMBINERPARAMETERFNVPROC*)0x00000001411A4FE0; // glCombinerParameterfNV
PFNGLCOMBINERPARAMETERFVNVPROC* divagl_glCombinerParameterfvNV
    = (PFNGLCOMBINERPARAMETERFVNVPROC*)0x00000001411A4FD8; // glCombinerParameterfvNV
PFNGLCOMBINERPARAMETERINVPROC* divagl_glCombinerParameteriNV
    = (PFNGLCOMBINERPARAMETERINVPROC*)0x00000001411A4FF0; // glCombinerParameteriNV
PFNGLCOMBINERPARAMETERIVNVPROC* divagl_glCombinerParameterivNV
    = (PFNGLCOMBINERPARAMETERIVNVPROC*)0x00000001411A4FE8; // glCombinerParameterivNV
PFNGLCOMBINERSTAGEPARAMETERFVNVPROC* divagl_glCombinerStageParameterfvNV
    = (PFNGLCOMBINERSTAGEPARAMETERFVNVPROC*)0x00000001411A5078; // glCombinerStageParameterfvNV
PFNGLCOMPILESHADERPROC* divagl_glCompileShader
    = (PFNGLCOMPILESHADERPROC*)0x00000001411A4270; // glCompileShader
PFNGLCOMPILESHADERARBPROC* divagl_glCompileShaderARB
    = (PFNGLCOMPILESHADERARBPROC*)0x00000001411A4BD0; // glCompileShaderARB
PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC* divagl_glCompressedMultiTexImage1DEXT
    = (PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC*)0x00000001411A3910; // glCompressedMultiTexImage1DEXT
PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC* divagl_glCompressedMultiTexImage2DEXT
    = (PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC*)0x00000001411A3908; // glCompressedMultiTexImage2DEXT
PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC* divagl_glCompressedMultiTexImage3DEXT
    = (PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC*)0x00000001411A3900; // glCompressedMultiTexImage3DEXT
PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC* divagl_glCompressedMultiTexSubImage1DEXT
    = (PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC*)0x00000001411A3928; // glCompressedMultiTexSubImage1DEXT
PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC* divagl_glCompressedMultiTexSubImage2DEXT
    = (PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC*)0x00000001411A3920; // glCompressedMultiTexSubImage2DEXT
PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC* divagl_glCompressedMultiTexSubImage3DEXT
    = (PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC*)0x00000001411A3918; // glCompressedMultiTexSubImage3DEXT
PFNGLCOMPRESSEDTEXIMAGE1DPROC* divagl_glCompressedTexImage1D
    = (PFNGLCOMPRESSEDTEXIMAGE1DPROC*)0x00000001411A4010; // glCompressedTexImage1D
PFNGLCOMPRESSEDTEXIMAGE1DARBPROC* divagl_glCompressedTexImage1DARB
    = (PFNGLCOMPRESSEDTEXIMAGE1DARBPROC*)0x00000001411A4868; // glCompressedTexImage1DARB
PFNGLCOMPRESSEDTEXIMAGE2DPROC* divagl_glCompressedTexImage2D
    = (PFNGLCOMPRESSEDTEXIMAGE2DPROC*)0x00000001411A4008; // glCompressedTexImage2D
PFNGLCOMPRESSEDTEXIMAGE2DARBPROC* divagl_glCompressedTexImage2DARB
    = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC*)0x00000001411A4860; // glCompressedTexImage2DARB
PFNGLCOMPRESSEDTEXIMAGE3DPROC* divagl_glCompressedTexImage3D
    = (PFNGLCOMPRESSEDTEXIMAGE3DPROC*)0x00000001411A4000; // glCompressedTexImage3D
PFNGLCOMPRESSEDTEXIMAGE3DARBPROC* divagl_glCompressedTexImage3DARB
    = (PFNGLCOMPRESSEDTEXIMAGE3DARBPROC*)0x00000001411A4858; // glCompressedTexImage3DARB
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC* divagl_glCompressedTexSubImage1D
    = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC*)0x00000001411A4028; // glCompressedTexSubImage1D
PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC* divagl_glCompressedTexSubImage1DARB
    = (PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC*)0x00000001411A4880; // glCompressedTexSubImage1DARB
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC* divagl_glCompressedTexSubImage2D
    = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC*)0x00000001411A4020; // glCompressedTexSubImage2D
PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC* divagl_glCompressedTexSubImage2DARB
    = (PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC*)0x00000001411A4878; // glCompressedTexSubImage2DARB
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC* divagl_glCompressedTexSubImage3D
    = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC*)0x00000001411A4018; // glCompressedTexSubImage3D
PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC* divagl_glCompressedTexSubImage3DARB
    = (PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC*)0x00000001411A4870; // glCompressedTexSubImage3DARB
PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC* divagl_glCompressedTextureImage1DEXT
    = (PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC*)0x00000001411A38D8; // glCompressedTextureImage1DEXT
PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC* divagl_glCompressedTextureImage2DEXT
    = (PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC*)0x00000001411A38D0; // glCompressedTextureImage2DEXT
PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC* divagl_glCompressedTextureImage3DEXT
    = (PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC*)0x00000001411A38C8; // glCompressedTextureImage3DEXT
PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC* divagl_glCompressedTextureSubImage1DEXT
    = (PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC*)0x00000001411A38F0; // glCompressedTextureSubImage1DEXT
PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC* divagl_glCompressedTextureSubImage2DEXT
    = (PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC*)0x00000001411A38E8; // glCompressedTextureSubImage2DEXT
PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC* divagl_glCompressedTextureSubImage3DEXT
    = (PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC*)0x00000001411A38E0; // glCompressedTextureSubImage3DEXT
PFNGLCONVOLUTIONFILTER1DPROC* divagl_glConvolutionFilter1D
    = (PFNGLCONVOLUTIONFILTER1DPROC*)0x00000001411A3C18; // glConvolutionFilter1D
PFNGLCONVOLUTIONFILTER2DPROC* divagl_glConvolutionFilter2D
    = (PFNGLCONVOLUTIONFILTER2DPROC*)0x00000001411A3C28; // glConvolutionFilter2D
PFNGLCONVOLUTIONPARAMETERFPROC* divagl_glConvolutionParameterf
    = (PFNGLCONVOLUTIONPARAMETERFPROC*)0x00000001411A3C38; // glConvolutionParameterf
PFNGLCONVOLUTIONPARAMETERFVPROC* divagl_glConvolutionParameterfv
    = (PFNGLCONVOLUTIONPARAMETERFVPROC*)0x00000001411A3C48; // glConvolutionParameterfv
PFNGLCONVOLUTIONPARAMETERIPROC* divagl_glConvolutionParameteri
    = (PFNGLCONVOLUTIONPARAMETERIPROC*)0x00000001411A3C58; // glConvolutionParameteri
PFNGLCONVOLUTIONPARAMETERIVPROC* divagl_glConvolutionParameteriv
    = (PFNGLCONVOLUTIONPARAMETERIVPROC*)0x00000001411A3C68; // glConvolutionParameteriv
PFNGLCOPYCOLORSUBTABLEPROC* divagl_glCopyColorSubTable
    = (PFNGLCOPYCOLORSUBTABLEPROC*)0x00000001411A3C08; // glCopyColorSubTable
PFNGLCOPYCOLORTABLEPROC* divagl_glCopyColorTable
    = (PFNGLCOPYCOLORTABLEPROC*)0x00000001411A3BB8; // glCopyColorTable
PFNGLCOPYCONVOLUTIONFILTER1DPROC* divagl_glCopyConvolutionFilter1D
    = (PFNGLCOPYCONVOLUTIONFILTER1DPROC*)0x00000001411A3C78; // glCopyConvolutionFilter1D
PFNGLCOPYCONVOLUTIONFILTER2DPROC* divagl_glCopyConvolutionFilter2D
    = (PFNGLCOPYCONVOLUTIONFILTER2DPROC*)0x00000001411A3C88; // glCopyConvolutionFilter2D
PFNGLCOPYIMAGESUBDATAPROC* divagl_glCopyImageSubData
    = (PFNGLCOPYIMAGESUBDATAPROC*)0x00000001411A4718; // glCopyImageSubData
PFNGLCOPYMULTITEXIMAGE1DEXTPROC* divagl_glCopyMultiTexImage1DEXT
    = (PFNGLCOPYMULTITEXIMAGE1DEXTPROC*)0x00000001411A37B8; // glCopyMultiTexImage1DEXT
PFNGLCOPYMULTITEXIMAGE2DEXTPROC* divagl_glCopyMultiTexImage2DEXT
    = (PFNGLCOPYMULTITEXIMAGE2DEXTPROC*)0x00000001411A37C0; // glCopyMultiTexImage2DEXT
PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC* divagl_glCopyMultiTexSubImage1DEXT
    = (PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC*)0x00000001411A37C8; // glCopyMultiTexSubImage1DEXT
PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC* divagl_glCopyMultiTexSubImage3DEXT
    = (PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC*)0x00000001411A3810; // glCopyMultiTexSubImage3DEXT
PFNGLCOPYTEXSUBIMAGE3DPROC* divagl_glCopyTexSubImage3D
    = (PFNGLCOPYTEXSUBIMAGE3DPROC*)0x00000001411A3DA8; // glCopyTexSubImage3D
PFNGLCOPYTEXSUBIMAGE3DEXTPROC* divagl_glCopyTexSubImage3DEXT
    = (PFNGLCOPYTEXSUBIMAGE3DEXTPROC*)0x00000001411A4E28; // glCopyTexSubImage3DEXT
PFNGLCOPYTEXTUREIMAGE1DEXTPROC* divagl_glCopyTextureImage1DEXT
    = (PFNGLCOPYTEXTUREIMAGE1DEXTPROC*)0x00000001411A3718; // glCopyTextureImage1DEXT
PFNGLCOPYTEXTUREIMAGE2DEXTPROC* divagl_glCopyTextureImage2DEXT
    = (PFNGLCOPYTEXTUREIMAGE2DEXTPROC*)0x00000001411A3720; // glCopyTextureImage2DEXT
PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC* divagl_glCopyTextureSubImage1DEXT
    = (PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC*)0x00000001411A3728; // glCopyTextureSubImage1DEXT
PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC* divagl_glCopyTextureSubImage2DEXT
    = (PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC*)0x00000001411A3730; // glCopyTextureSubImage2DEXT
PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC* divagl_glCopyTextureSubImage3DEXT
    = (PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC*)0x00000001411A3770; // glCopyTextureSubImage3DEXT
PFNGLCREATEPROGRAMPROC* divagl_glCreateProgram
    = (PFNGLCREATEPROGRAMPROC*)0x00000001411A4278; // glCreateProgram
PFNGLCREATEPROGRAMOBJECTARBPROC* divagl_glCreateProgramObjectARB
    = (PFNGLCREATEPROGRAMOBJECTARBPROC*)0x00000001411A4BD8; // glCreateProgramObjectARB
PFNGLCREATESHADERPROC* divagl_glCreateShader
    = (PFNGLCREATESHADERPROC*)0x00000001411A4280; // glCreateShader
PFNGLCREATESHADEROBJECTARBPROC* divagl_glCreateShaderObjectARB
    = (PFNGLCREATESHADEROBJECTARBPROC*)0x00000001411A4BC0; // glCreateShaderObjectARB
PFNGLDELETEBUFFERSPROC* divagl_glDeleteBuffers
    = (PFNGLDELETEBUFFERSPROC*)0x00000001411A41E8; // glDeleteBuffers
PFNGLDELETEFENCESNVPROC* divagl_glDeleteFencesNV
    = (PFNGLDELETEFENCESNVPROC*)0x00000001411A5040; // glDeleteFencesNV
PFNGLDELETEFRAMEBUFFERSPROC* divagl_glDeleteFramebuffers
    = (PFNGLDELETEFRAMEBUFFERSPROC*)0x00000001411A4D58; // glDeleteFramebuffers
PFNGLDELETEOBJECTARBPROC* divagl_glDeleteObjectARB
    = (PFNGLDELETEOBJECTARBPROC*)0x00000001411A4BA8; // glDeleteObjectARB
PFNGLDELETEOCCLUSIONQUERIESNVPROC* divagl_glDeleteOcclusionQueriesNV
    = (PFNGLDELETEOCCLUSIONQUERIESNVPROC*)0x00000001411A5290; // glDeleteOcclusionQueriesNV
PFNGLDELETEPROGRAMPROC* divagl_glDeleteProgram
    = (PFNGLDELETEPROGRAMPROC*)0x00000001411A4288; // glDeleteProgram
PFNGLDELETEPROGRAMSARBPROC* divagl_glDeleteProgramsARB
    = (PFNGLDELETEPROGRAMSARBPROC*)0x00000001411A4A68; // glDeleteProgramsARB
PFNGLDELETEPROGRAMSNVPROC* divagl_glDeleteProgramsNV
    = (PFNGLDELETEPROGRAMSNVPROC*)0x00000001411A5098; // glDeleteProgramsNV
PFNGLDELETEQUERIESPROC* divagl_glDeleteQueries
    = (PFNGLDELETEQUERIESPROC*)0x00000001411A41A8; // glDeleteQueries
PFNGLDELETEQUERIESARBPROC* divagl_glDeleteQueriesARB
    = (PFNGLDELETEQUERIESARBPROC*)0x00000001411A4B70; // glDeleteQueriesARB
PFNGLDELETERENDERBUFFERSPROC* divagl_glDeleteRenderbuffers
    = (PFNGLDELETERENDERBUFFERSPROC*)0x00000001411A4D28; // glDeleteRenderbuffers
PFNGLDELETESAMPLERSPROC* divagl_glDeleteSamplers
    = (PFNGLDELETESAMPLERSPROC*)0x00000001411A3F90; // glDeleteSamplers
PFNGLDELETESHADERPROC* divagl_glDeleteShader
    = (PFNGLDELETESHADERPROC*)0x00000001411A4290; // glDeleteShader
PFNGLDELETETEXTURESPROC* divagl_glDeleteTextures
    = (PFNGLDELETETEXTURESPROC*)0x00000001411A1A30; // glDeleteTextures
PFNGLDELETETEXTURESEXTPROC* divagl_glDeleteTexturesEXT
    = (PFNGLDELETETEXTURESEXTPROC*)0x00000001411A4E40; // glDeleteTexturesEXT
PFNGLDELETEVERTEXARRAYSPROC* divagl_glDeleteVertexArrays
    = (PFNGLDELETEVERTEXARRAYSPROC*)0x00000001411A4DF8; // glDeleteVertexArrays
PFNGLDEPTHBOUNDSDNVPROC* divagl_glDepthBoundsdNV
    = (PFNGLDEPTHBOUNDSDNVPROC*)0x00000001411A34F8; // glDepthBoundsdNV
PFNGLDEPTHBOUNDSEXTPROC* divagl_glDepthBoundsEXT
    = (PFNGLDEPTHBOUNDSEXTPROC*)0x00000001411A5490; // glDepthBoundsEXT
PFNGLDEPTHRANGEDNVPROC* divagl_glDepthRangedNV
    = (PFNGLDEPTHRANGEDNVPROC*)0x00000001411A34E8; // glDepthRangedNV
PFNGLDETACHOBJECTARBPROC* divagl_glDetachObjectARB
    = (PFNGLDETACHOBJECTARBPROC*)0x00000001411A4BB8; // glDetachObjectARB
PFNGLDETACHSHADERPROC* divagl_glDetachShader
    = (PFNGLDETACHSHADERPROC*)0x00000001411A4298; // glDetachShader
PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC* divagl_glDisableClientStateIndexedEXT
    = (PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC*)0x00000001411A3828; // glDisableClientStateIndexedEXT
PFNGLDISABLEIPROC* divagl_glDisablei
    = (PFNGLDISABLEIPROC*)0x00000001411A4570; // glDisablei
PFNGLDISABLEINDEXEDEXTPROC* divagl_glDisableIndexedEXT
    = (PFNGLDISABLEINDEXEDEXTPROC*)0x00000001411A3540; // glDisableIndexedEXT
PFNGLDISABLEVERTEXATTRIBARRAYPROC* divagl_glDisableVertexAttribArray
    = (PFNGLDISABLEVERTEXATTRIBARRAYPROC*)0x00000001411A42A0; // glDisableVertexAttribArray
PFNGLDRAWARRAYSEXTPROC* divagl_glDrawArraysEXT
    = (PFNGLDRAWARRAYSEXTPROC*)0x00000001411A4E70; // glDrawArraysEXT
PFNGLDRAWARRAYSINSTANCEDARBPROC* divagl_glDrawArraysInstancedARB
    = (PFNGLDRAWARRAYSINSTANCEDARBPROC*)0x00000001411A4D08; // glDrawArraysInstancedARB
PFNGLDRAWARRAYSINSTANCEDEXTPROC* divagl_glDrawArraysInstancedEXT
    = (PFNGLDRAWARRAYSINSTANCEDEXTPROC*)0x00000001411A5710; // glDrawArraysInstancedEXT
PFNGLDRAWBUFFERSPROC* divagl_glDrawBuffers
    = (PFNGLDRAWBUFFERSPROC*)0x00000001411A4240; // glDrawBuffers
PFNGLDRAWBUFFERSARBPROC* divagl_glDrawBuffersARB
    = (PFNGLDRAWBUFFERSARBPROC*)0x00000001411A4CF8; // glDrawBuffersARB
PFNGLDRAWBUFFERSATIPROC* divagl_glDrawBuffersATI
    = (PFNGLDRAWBUFFERSATIPROC*)0x00000001411A52D8; // glDrawBuffersATI
PFNGLDRAWELEMENTSINSTANCEDARBPROC* divagl_glDrawElementsInstancedARB
    = (PFNGLDRAWELEMENTSINSTANCEDARBPROC*)0x00000001411A4D10; // glDrawElementsInstancedARB
PFNGLDRAWELEMENTSINSTANCEDEXTPROC* divagl_glDrawElementsInstancedEXT
    = (PFNGLDRAWELEMENTSINSTANCEDEXTPROC*)0x00000001411A5718; // glDrawElementsInstancedEXT
PFNGLDRAWRANGEELEMENTSPROC* divagl_glDrawRangeElements
    = (PFNGLDRAWRANGEELEMENTSPROC*)0x00000001411A3B78; // glDrawRangeElements
PFNGLDRAWRANGEELEMENTSEXTPROC* divagl_glDrawRangeElementsEXT
    = (PFNGLDRAWRANGEELEMENTSEXTPROC*)0x00000001411A4EF8; // glDrawRangeElementsEXT
PFNGLEDGEFLAGPOINTEREXTPROC* divagl_glEdgeFlagPointerEXT
    = (PFNGLEDGEFLAGPOINTEREXTPROC*)0x00000001411A4E78; // glEdgeFlagPointerEXT
PFNGLENABLECLIENTSTATEINDEXEDEXTPROC* divagl_glEnableClientStateIndexedEXT
    = (PFNGLENABLECLIENTSTATEINDEXEDEXTPROC*)0x00000001411A3820; // glEnableClientStateIndexedEXT
PFNGLENABLEIPROC* divagl_glEnablei
    = (PFNGLENABLEIPROC*)0x00000001411A4568; // glEnablei
PFNGLENABLEINDEXEDEXTPROC* divagl_glEnableIndexedEXT
    = (PFNGLENABLEINDEXEDEXTPROC*)0x00000001411A3538; // glEnableIndexedEXT
PFNGLENABLEVERTEXATTRIBARRAYPROC* divagl_glEnableVertexAttribArray
    = (PFNGLENABLEVERTEXATTRIBARRAYPROC*)0x00000001411A42A8; // glEnableVertexAttribArray
PFNGLENDCONDITIONALRENDERPROC* divagl_glEndConditionalRender
    = (PFNGLENDCONDITIONALRENDERPROC*)0x00000001411A45B8; // glEndConditionalRender
PFNGLENDCONDITIONALRENDERNVPROC* divagl_glEndConditionalRenderNV
    = (PFNGLENDCONDITIONALRENDERNVPROC*)0x00000001411A35F8; // glEndConditionalRenderNV
PFNGLENDOCCLUSIONQUERYNVPROC* divagl_glEndOcclusionQueryNV
    = (PFNGLENDOCCLUSIONQUERYNVPROC*)0x00000001411A52A8; // glEndOcclusionQueryNV
PFNGLENDQUERYPROC* divagl_glEndQuery
    = (PFNGLENDQUERYPROC*)0x00000001411A41C0; // glEndQuery
PFNGLENDQUERYARBPROC* divagl_glEndQueryARB
    = (PFNGLENDQUERYARBPROC*)0x00000001411A4B88; // glEndQueryARB
PFNGLENDTRANSFORMFEEDBACKPROC* divagl_glEndTransformFeedback
    = (PFNGLENDTRANSFORMFEEDBACKPROC*)0x00000001411A4588; // glEndTransformFeedback
PFNGLENDTRANSFORMFEEDBACKNVPROC* divagl_glEndTransformFeedbackNV
    = (PFNGLENDTRANSFORMFEEDBACKNVPROC*)0x00000001411A3558; // glEndTransformFeedbackNV
PFNGLEXECUTEPROGRAMNVPROC* divagl_glExecuteProgramNV
    = (PFNGLEXECUTEPROGRAMNVPROC*)0x00000001411A50A0; // glExecuteProgramNV
PFNGLFINALCOMBINERINPUTNVPROC* divagl_glFinalCombinerInputNV
    = (PFNGLFINALCOMBINERINPUTNVPROC*)0x00000001411A5008; // glFinalCombinerInputNV
PFNGLFINISHFENCENVPROC* divagl_glFinishFenceNV
    = (PFNGLFINISHFENCENVPROC*)0x00000001411A5068; // glFinishFenceNV
PFNGLFLUSHMAPPEDBUFFERRANGEPROC* divagl_glFlushMappedBufferRange
    = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC*)0x00000001411A4DE0; // glFlushMappedBufferRange
PFNGLFLUSHPIXELDATARANGENVPROC* divagl_glFlushPixelDataRangeNV
    = (PFNGLFLUSHPIXELDATARANGENVPROC*)0x00000001411A5478; // glFlushPixelDataRangeNV
PFNGLFLUSHVERTEXARRAYRANGENVPROC* divagl_glFlushVertexArrayRangeNV
    = (PFNGLFLUSHVERTEXARRAYRANGENVPROC*)0x00000001411A4FC8; // glFlushVertexArrayRangeNV
PFNGLFOGCOORDDPROC* divagl_glFogCoordd
    = (PFNGLFOGCOORDDPROC*)0x00000001411A4050; // glFogCoordd
PFNGLFOGCOORDDEXTPROC* divagl_glFogCoorddEXT
    = (PFNGLFOGCOORDDEXTPROC*)0x00000001411A4FA8; // glFogCoorddEXT
PFNGLFOGCOORDDVPROC* divagl_glFogCoorddv
    = (PFNGLFOGCOORDDVPROC*)0x00000001411A4058; // glFogCoorddv
PFNGLFOGCOORDDVEXTPROC* divagl_glFogCoorddvEXT
    = (PFNGLFOGCOORDDVEXTPROC*)0x00000001411A4FB0; // glFogCoorddvEXT
PFNGLFOGCOORDFPROC* divagl_glFogCoordf
    = (PFNGLFOGCOORDFPROC*)0x00000001411A4040; // glFogCoordf
PFNGLFOGCOORDFEXTPROC* divagl_glFogCoordfEXT
    = (PFNGLFOGCOORDFEXTPROC*)0x00000001411A4F98; // glFogCoordfEXT
PFNGLFOGCOORDFVPROC* divagl_glFogCoordfv
    = (PFNGLFOGCOORDFVPROC*)0x00000001411A4048; // glFogCoordfv
PFNGLFOGCOORDFVEXTPROC* divagl_glFogCoordfvEXT
    = (PFNGLFOGCOORDFVEXTPROC*)0x00000001411A4FA0; // glFogCoordfvEXT
PFNGLFOGCOORDHNVPROC* divagl_glFogCoordhNV
    = (PFNGLFOGCOORDHNVPROC*)0x00000001411A53F0; // glFogCoordhNV
PFNGLFOGCOORDHVNVPROC* divagl_glFogCoordhvNV
    = (PFNGLFOGCOORDHVNVPROC*)0x00000001411A53F8; // glFogCoordhvNV
PFNGLFOGCOORDPOINTERPROC* divagl_glFogCoordPointer
    = (PFNGLFOGCOORDPOINTERPROC*)0x00000001411A4060; // glFogCoordPointer
PFNGLFOGCOORDPOINTEREXTPROC* divagl_glFogCoordPointerEXT
    = (PFNGLFOGCOORDPOINTEREXTPROC*)0x00000001411A4FB8; // glFogCoordPointerEXT
PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC* divagl_glFramebufferDrawBufferEXT
    = (PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC*)0x00000001411A3C00; // glFramebufferDrawBufferEXT
PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC* divagl_glFramebufferDrawBuffersEXT
    = (PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC*)0x00000001411A3C10; // glFramebufferDrawBuffersEXT
PFNGLFRAMEBUFFERREADBUFFEREXTPROC* divagl_glFramebufferReadBufferEXT
    = (PFNGLFRAMEBUFFERREADBUFFEREXTPROC*)0x00000001411A3C20; // glFramebufferReadBufferEXT
PFNGLFRAMEBUFFERRENDERBUFFERPROC* divagl_glFramebufferRenderbuffer
    = (PFNGLFRAMEBUFFERRENDERBUFFERPROC*)0x00000001411A4D88; // glFramebufferRenderbuffer
PFNGLFRAMEBUFFERTEXTUREPROC* divagl_glFramebufferTexture
    = (PFNGLFRAMEBUFFERTEXTUREPROC*)0x00000001411A3F50; // glFramebufferTexture
PFNGLFRAMEBUFFERTEXTURE1DPROC* divagl_glFramebufferTexture1D
    = (PFNGLFRAMEBUFFERTEXTURE1DPROC*)0x00000001411A4D70; // glFramebufferTexture1D
PFNGLFRAMEBUFFERTEXTURE1DEXTPROC* divagl_glFramebufferTexture1DEXT
    = (PFNGLFRAMEBUFFERTEXTURE1DEXTPROC*)0x00000001411A54F8; // glFramebufferTexture1DEXT
PFNGLFRAMEBUFFERTEXTURE2DPROC* divagl_glFramebufferTexture2D
    = (PFNGLFRAMEBUFFERTEXTURE2DPROC*)0x00000001411A4D78; // glFramebufferTexture2D
PFNGLFRAMEBUFFERTEXTURE3DPROC* divagl_glFramebufferTexture3D
    = (PFNGLFRAMEBUFFERTEXTURE3DPROC*)0x00000001411A4D80; // glFramebufferTexture3D
PFNGLFRAMEBUFFERTEXTURE3DEXTPROC* divagl_glFramebufferTexture3DEXT
    = (PFNGLFRAMEBUFFERTEXTURE3DEXTPROC*)0x00000001411A5508; // glFramebufferTexture3DEXT
PFNGLFRAMEBUFFERTEXTUREARBPROC* divagl_glFramebufferTextureARB
    = (PFNGLFRAMEBUFFERTEXTUREARBPROC*)0x00000001411A4DC0; // glFramebufferTextureARB
PFNGLFRAMEBUFFERTEXTUREEXTPROC* divagl_glFramebufferTextureEXT
    = (PFNGLFRAMEBUFFERTEXTUREEXTPROC*)0x00000001411A55E0; // glFramebufferTextureEXT
PFNGLFRAMEBUFFERTEXTUREFACEARBPROC* divagl_glFramebufferTextureFaceARB
    = (PFNGLFRAMEBUFFERTEXTUREFACEARBPROC*)0x00000001411A4DD0; // glFramebufferTextureFaceARB
PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC* divagl_glFramebufferTextureFaceEXT
    = (PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC*)0x00000001411A55F0; // glFramebufferTextureFaceEXT
PFNGLFRAMEBUFFERTEXTURELAYERPROC* divagl_glFramebufferTextureLayer
    = (PFNGLFRAMEBUFFERTEXTURELAYERPROC*)0x00000001411A4DB0; // glFramebufferTextureLayer
PFNGLFRAMEBUFFERTEXTURELAYERARBPROC* divagl_glFramebufferTextureLayerARB
    = (PFNGLFRAMEBUFFERTEXTURELAYERARBPROC*)0x00000001411A4DC8; // glFramebufferTextureLayerARB
PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC* divagl_glFramebufferTextureLayerEXT
    = (PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC*)0x00000001411A55E8; // glFramebufferTextureLayerEXT
PFNGLGENBUFFERSPROC* divagl_glGenBuffers
    = (PFNGLGENBUFFERSPROC*)0x00000001411A41F0; // glGenBuffers
PFNGLGENBUFFERSARBPROC* divagl_glGenBuffersARB
    = (PFNGLGENBUFFERSARBPROC*)0x00000001411A4B20; // glGenBuffersARB
PFNGLGENERATEMIPMAPPROC* divagl_glGenerateMipmap
    = (PFNGLGENERATEMIPMAPPROC*)0x00000001411A4D98; // glGenerateMipmap
PFNGLGENERATEMIPMAPEXTPROC* divagl_glGenerateMipmapEXT
    = (PFNGLGENERATEMIPMAPEXTPROC*)0x00000001411A5520; // glGenerateMipmapEXT
PFNGLGENERATEMULTITEXMIPMAPEXTPROC* divagl_glGenerateMultiTexMipmapEXT
    = (PFNGLGENERATEMULTITEXMIPMAPEXTPROC*)0x00000001411A3BF0; // glGenerateMultiTexMipmapEXT
PFNGLGENERATETEXTUREMIPMAPEXTPROC* divagl_glGenerateTextureMipmapEXT
    = (PFNGLGENERATETEXTUREMIPMAPEXTPROC*)0x00000001411A3BE0; // glGenerateTextureMipmapEXT
PFNGLGENFENCESNVPROC* divagl_glGenFencesNV
    = (PFNGLGENFENCESNVPROC*)0x00000001411A5048; // glGenFencesNV
PFNGLGENFRAMEBUFFERSPROC* divagl_glGenFramebuffers
    = (PFNGLGENFRAMEBUFFERSPROC*)0x00000001411A4D60; // glGenFramebuffers
PFNGLGENOCCLUSIONQUERIESNVPROC* divagl_glGenOcclusionQueriesNV
    = (PFNGLGENOCCLUSIONQUERIESNVPROC*)0x00000001411A5288; // glGenOcclusionQueriesNV
PFNGLGENPROGRAMSARBPROC* divagl_glGenProgramsARB
    = (PFNGLGENPROGRAMSARBPROC*)0x00000001411A4A70; // glGenProgramsARB
PFNGLGENPROGRAMSNVPROC* divagl_glGenProgramsNV
    = (PFNGLGENPROGRAMSNVPROC*)0x00000001411A50A8; // glGenProgramsNV
PFNGLGENQUERIESPROC* divagl_glGenQueries
    = (PFNGLGENQUERIESPROC*)0x00000001411A41A0; // glGenQueries
PFNGLGENQUERIESARBPROC* divagl_glGenQueriesARB
    = (PFNGLGENQUERIESARBPROC*)0x00000001411A4B68; // glGenQueriesARB
PFNGLGENRENDERBUFFERSPROC* divagl_glGenRenderbuffers
    = (PFNGLGENRENDERBUFFERSPROC*)0x00000001411A4D30; // glGenRenderbuffers
PFNGLGENSAMPLERSPROC* divagl_glGenSamplers
    = (PFNGLGENSAMPLERSPROC*)0x00000001411A3F80; // glGenSamplers
PFNGLGENTEXTURESPROC* divagl_glGenTextures
    = (PFNGLGENTEXTURESPROC*)0x00000001411A1A38; // glGenTextures
PFNGLGENTEXTURESEXTPROC* divagl_glGenTexturesEXT
    = (PFNGLGENTEXTURESEXTPROC*)0x00000001411A4E48; // glGenTexturesEXT
PFNGLGENVERTEXARRAYSPROC* divagl_glGenVertexArrays
    = (PFNGLGENVERTEXARRAYSPROC*)0x00000001411A4E00; // glGenVertexArrays
PFNGLGETACTIVEATTRIBPROC* divagl_glGetActiveAttrib
    = (PFNGLGETACTIVEATTRIBPROC*)0x00000001411A42B0; // glGetActiveAttrib
PFNGLGETACTIVEATTRIBARBPROC* divagl_glGetActiveAttribARB
    = (PFNGLGETACTIVEATTRIBARBPROC*)0x00000001411A4CE8; // glGetActiveAttribARB
PFNGLGETACTIVEUNIFORMPROC* divagl_glGetActiveUniform
    = (PFNGLGETACTIVEUNIFORMPROC*)0x00000001411A42B8; // glGetActiveUniform
PFNGLGETACTIVEUNIFORMARBPROC* divagl_glGetActiveUniformARB
    = (PFNGLGETACTIVEUNIFORMARBPROC*)0x00000001411A4CC0; // glGetActiveUniformARB
PFNGLGETACTIVEVARYINGNVPROC* divagl_glGetActiveVaryingNV
    = (PFNGLGETACTIVEVARYINGNVPROC*)0x00000001411A3598; // glGetActiveVaryingNV
PFNGLGETATTACHEDOBJECTSARBPROC* divagl_glGetAttachedObjectsARB
    = (PFNGLGETATTACHEDOBJECTSARBPROC*)0x00000001411A4CB0; // glGetAttachedObjectsARB
PFNGLGETATTACHEDSHADERSPROC* divagl_glGetAttachedShaders
    = (PFNGLGETATTACHEDSHADERSPROC*)0x00000001411A42C0; // glGetAttachedShaders
PFNGLGETATTRIBLOCATIONPROC* divagl_glGetAttribLocation
    = (PFNGLGETATTRIBLOCATIONPROC*)0x00000001411A42C8; // glGetAttribLocation
PFNGLGETATTRIBLOCATIONARBPROC* divagl_glGetAttribLocationARB
    = (PFNGLGETATTRIBLOCATIONARBPROC*)0x00000001411A4CF0; // glGetAttribLocationARB
PFNGLGETBOOLEANI_VPROC* divagl_glGetBooleani_v
    = (PFNGLGETBOOLEANI_VPROC*)0x00000001411A4558; // glGetBooleani_v
PFNGLGETBOOLEANINDEXEDVEXTPROC* divagl_glGetBooleanIndexedvEXT
    = (PFNGLGETBOOLEANINDEXEDVEXTPROC*)0x00000001411A3528; // glGetBooleanIndexedvEXT
PFNGLGETBUFFERPARAMETERIVPROC* divagl_glGetBufferParameteriv
    = (PFNGLGETBUFFERPARAMETERIVPROC*)0x00000001411A4228; // glGetBufferParameteriv
PFNGLGETBUFFERPARAMETERIVARBPROC* divagl_glGetBufferParameterivARB
    = (PFNGLGETBUFFERPARAMETERIVARBPROC*)0x00000001411A4B58; // glGetBufferParameterivARB
PFNGLGETBUFFERPOINTERVPROC* divagl_glGetBufferPointerv
    = (PFNGLGETBUFFERPOINTERVPROC*)0x00000001411A4230; // glGetBufferPointerv
PFNGLGETBUFFERPOINTERVARBPROC* divagl_glGetBufferPointervARB
    = (PFNGLGETBUFFERPOINTERVARBPROC*)0x00000001411A4B60; // glGetBufferPointervARB
PFNGLGETBUFFERSUBDATAPROC* divagl_glGetBufferSubData
    = (PFNGLGETBUFFERSUBDATAPROC*)0x00000001411A4210; // glGetBufferSubData
PFNGLGETBUFFERSUBDATAARBPROC* divagl_glGetBufferSubDataARB
    = (PFNGLGETBUFFERSUBDATAARBPROC*)0x00000001411A4B40; // glGetBufferSubDataARB
PFNGLGETCOLORTABLEPROC* divagl_glGetColorTable
    = (PFNGLGETCOLORTABLEPROC*)0x00000001411A3BC8; // glGetColorTable
PFNGLGETCOLORTABLEEXTPROC* divagl_glGetColorTableEXT
    = (PFNGLGETCOLORTABLEEXTPROC*)0x00000001411A4ED0; // glGetColorTableEXT
PFNGLGETCOLORTABLEPARAMETERFVPROC* divagl_glGetColorTableParameterfv
    = (PFNGLGETCOLORTABLEPARAMETERFVPROC*)0x00000001411A3BD8; // glGetColorTableParameterfv
PFNGLGETCOLORTABLEPARAMETERFVEXTPROC* divagl_glGetColorTableParameterfvEXT
    = (PFNGLGETCOLORTABLEPARAMETERFVEXTPROC*)0x00000001411A4EE0; // glGetColorTableParameterfvEXT
PFNGLGETCOLORTABLEPARAMETERIVPROC* divagl_glGetColorTableParameteriv
    = (PFNGLGETCOLORTABLEPARAMETERIVPROC*)0x00000001411A3BE8; // glGetColorTableParameteriv
PFNGLGETCOLORTABLEPARAMETERIVEXTPROC* divagl_glGetColorTableParameterivEXT
    = (PFNGLGETCOLORTABLEPARAMETERIVEXTPROC*)0x00000001411A4ED8; // glGetColorTableParameterivEXT
PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC* divagl_glGetCombinerInputParameterfvNV
    = (PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC*)0x00000001411A5010; // glGetCombinerInputParameterfvNV
PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC* divagl_glGetCombinerInputParameterivNV
    = (PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC*)0x00000001411A5018; // glGetCombinerInputParameterivNV
PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC* divagl_glGetCombinerOutputParameterfvNV
    = (PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC*)0x00000001411A5020; // glGetCombinerOutputParameterfvNV
PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC* divagl_glGetCombinerOutputParameterivNV
    = (PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC*)0x00000001411A5028; // glGetCombinerOutputParameterivNV
PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC* divagl_glGetCombinerStageParameterfvNV
    = (PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC*)0x00000001411A5080; // glGetCombinerStageParameterfvNV
PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC* divagl_glGetCompressedMultiTexImageEXT
    = (PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC*)0x00000001411A3930; // glGetCompressedMultiTexImageEXT
PFNGLGETCOMPRESSEDTEXIMAGEPROC* divagl_glGetCompressedTexImage
    = (PFNGLGETCOMPRESSEDTEXIMAGEPROC*)0x00000001411A4030; // glGetCompressedTexImage
PFNGLGETCOMPRESSEDTEXIMAGEARBPROC* divagl_glGetCompressedTexImageARB
    = (PFNGLGETCOMPRESSEDTEXIMAGEARBPROC*)0x00000001411A4888; // glGetCompressedTexImageARB
PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC* divagl_glGetCompressedTextureImageEXT
    = (PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC*)0x00000001411A38F8; // glGetCompressedTextureImageEXT
PFNGLGETCONVOLUTIONFILTERPROC* divagl_glGetConvolutionFilter
    = (PFNGLGETCONVOLUTIONFILTERPROC*)0x00000001411A3C98; // glGetConvolutionFilter
PFNGLGETCONVOLUTIONPARAMETERFVPROC* divagl_glGetConvolutionParameterfv
    = (PFNGLGETCONVOLUTIONPARAMETERFVPROC*)0x00000001411A3CA8; // glGetConvolutionParameterfv
PFNGLGETCONVOLUTIONPARAMETERIVPROC* divagl_glGetConvolutionParameteriv
    = (PFNGLGETCONVOLUTIONPARAMETERIVPROC*)0x00000001411A3CB8; // glGetConvolutionParameteriv
PFNGLGETDOUBLEINDEXEDVEXTPROC* divagl_glGetDoubleIndexedvEXT
    = (PFNGLGETDOUBLEINDEXEDVEXTPROC*)0x00000001411A38B8; // glGetDoubleIndexedvEXT
PFNGLGETFENCEIVNVPROC* divagl_glGetFenceivNV
    = (PFNGLGETFENCEIVNVPROC*)0x00000001411A5060; // glGetFenceivNV
PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC* divagl_glGetFinalCombinerInputParameterfvNV
    = (PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC*)0x00000001411A5030; // glGetFinalCombinerInputParameterfvNV
PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC* divagl_glGetFinalCombinerInputParameterivNV
    = (PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC*)0x00000001411A5038; // glGetFinalCombinerInputParameterivNV
PFNGLGETFLOATINDEXEDVEXTPROC* divagl_glGetFloatIndexedvEXT
    = (PFNGLGETFLOATINDEXEDVEXTPROC*)0x00000001411A38B0; // glGetFloatIndexedvEXT
PFNGLGETFRAGDATALOCATIONPROC* divagl_glGetFragDataLocation
    = (PFNGLGETFRAGDATALOCATIONPROC*)0x00000001411A4688; // glGetFragDataLocation
PFNGLGETFRAGDATALOCATIONEXTPROC* divagl_glGetFragDataLocationEXT
    = (PFNGLGETFRAGDATALOCATIONEXTPROC*)0x00000001411A56C8; // glGetFragDataLocationEXT
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC* divagl_glGetFramebufferAttachmentParameteriv
    = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC*)0x00000001411A4D90; // glGetFramebufferAttachmentParameteriv
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC* divagl_glGetFramebufferAttachmentParameterivEXT
    = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC*)0x00000001411A5518; // glGetFramebufferAttachmentParameterivEXT
PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC* divagl_glGetFramebufferParameterivEXT
    = (PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC*)0x00000001411A3C30; // glGetFramebufferParameterivEXT
PFNGLGETHANDLEARBPROC* divagl_glGetHandleARB
    = (PFNGLGETHANDLEARBPROC*)0x00000001411A4BB0; // glGetHandleARB
PFNGLGETHISTOGRAMPROC* divagl_glGetHistogram
    = (PFNGLGETHISTOGRAMPROC*)0x00000001411A3CE8; // glGetHistogram
PFNGLGETHISTOGRAMPARAMETERFVPROC* divagl_glGetHistogramParameterfv
    = (PFNGLGETHISTOGRAMPARAMETERFVPROC*)0x00000001411A3CF8; // glGetHistogramParameterfv
PFNGLGETHISTOGRAMPARAMETERIVPROC* divagl_glGetHistogramParameteriv
    = (PFNGLGETHISTOGRAMPARAMETERIVPROC*)0x00000001411A3D08; // glGetHistogramParameteriv
PFNGLGETINFOLOGARBPROC* divagl_glGetInfoLogARB
    = (PFNGLGETINFOLOGARBPROC*)0x00000001411A4CA8; // glGetInfoLogARB
PFNGLGETINTEGERI_VPROC* divagl_glGetIntegeri_v
    = (PFNGLGETINTEGERI_VPROC*)0x00000001411A4560; // glGetIntegeri_v
PFNGLGETINTEGERINDEXEDVEXTPROC* divagl_glGetIntegerIndexedvEXT
    = (PFNGLGETINTEGERINDEXEDVEXTPROC*)0x00000001411A3530; // glGetIntegerIndexedvEXT
PFNGLGETMINMAXPROC* divagl_glGetMinmax
    = (PFNGLGETMINMAXPROC*)0x00000001411A3D18; // glGetMinmax
PFNGLGETMINMAXPARAMETERFVPROC* divagl_glGetMinmaxParameterfv
    = (PFNGLGETMINMAXPARAMETERFVPROC*)0x00000001411A3D28; // glGetMinmaxParameterfv
PFNGLGETMINMAXPARAMETERIVPROC* divagl_glGetMinmaxParameteriv
    = (PFNGLGETMINMAXPARAMETERIVPROC*)0x00000001411A3D38; // glGetMinmaxParameteriv
PFNGLGETMULTISAMPLEFVNVPROC* divagl_glGetMultisamplefvNV
    = (PFNGLGETMULTISAMPLEFVNVPROC*)0x00000001411A3CB0; // glGetMultisamplefvNV
PFNGLGETMULTITEXENVFVEXTPROC* divagl_glGetMultiTexEnvfvEXT
    = (PFNGLGETMULTITEXENVFVEXTPROC*)0x00000001411A3888; // glGetMultiTexEnvfvEXT
PFNGLGETMULTITEXENVIVEXTPROC* divagl_glGetMultiTexEnvivEXT
    = (PFNGLGETMULTITEXENVIVEXTPROC*)0x00000001411A3890; // glGetMultiTexEnvivEXT
PFNGLGETMULTITEXGENDVEXTPROC* divagl_glGetMultiTexGendvEXT
    = (PFNGLGETMULTITEXGENDVEXTPROC*)0x00000001411A3898; // glGetMultiTexGendvEXT
PFNGLGETMULTITEXGENFVEXTPROC* divagl_glGetMultiTexGenfvEXT
    = (PFNGLGETMULTITEXGENFVEXTPROC*)0x00000001411A38A0; // glGetMultiTexGenfvEXT
PFNGLGETMULTITEXGENIVEXTPROC* divagl_glGetMultiTexGenivEXT
    = (PFNGLGETMULTITEXGENIVEXTPROC*)0x00000001411A38A8; // glGetMultiTexGenivEXT
PFNGLGETMULTITEXIMAGEEXTPROC* divagl_glGetMultiTexImageEXT
    = (PFNGLGETMULTITEXIMAGEEXTPROC*)0x00000001411A37D8; // glGetMultiTexImageEXT
PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC* divagl_glGetMultiTexLevelParameterfvEXT
    = (PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC*)0x00000001411A37F0; // glGetMultiTexLevelParameterfvEXT
PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC* divagl_glGetMultiTexLevelParameterivEXT
    = (PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC*)0x00000001411A37F8; // glGetMultiTexLevelParameterivEXT
PFNGLGETMULTITEXPARAMETERFVEXTPROC* divagl_glGetMultiTexParameterfvEXT
    = (PFNGLGETMULTITEXPARAMETERFVEXTPROC*)0x00000001411A37E0; // glGetMultiTexParameterfvEXT
PFNGLGETMULTITEXPARAMETERIIVEXTPROC* divagl_glGetMultiTexParameterIivEXT
    = (PFNGLGETMULTITEXPARAMETERIIVEXTPROC*)0x00000001411A39F8; // glGetMultiTexParameterIivEXT
PFNGLGETMULTITEXPARAMETERIUIVEXTPROC* divagl_glGetMultiTexParameterIuivEXT
    = (PFNGLGETMULTITEXPARAMETERIUIVEXTPROC*)0x00000001411A3A00; // glGetMultiTexParameterIuivEXT
PFNGLGETMULTITEXPARAMETERIVEXTPROC* divagl_glGetMultiTexParameterivEXT
    = (PFNGLGETMULTITEXPARAMETERIVEXTPROC*)0x00000001411A37E8; // glGetMultiTexParameterivEXT
PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC* divagl_glGetNamedBufferParameterivEXT
    = (PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC*)0x00000001411A3B30; // glGetNamedBufferParameterivEXT
PFNGLGETNAMEDBUFFERPOINTERVEXTPROC* divagl_glGetNamedBufferPointervEXT
    = (PFNGLGETNAMEDBUFFERPOINTERVEXTPROC*)0x00000001411A3B38; // glGetNamedBufferPointervEXT
PFNGLGETNAMEDBUFFERSUBDATAEXTPROC* divagl_glGetNamedBufferSubDataEXT
    = (PFNGLGETNAMEDBUFFERSUBDATAEXTPROC*)0x00000001411A3B40; // glGetNamedBufferSubDataEXT
PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC* divagl_glGetNamedFramebufferAttachmentParameterivEXT
    = (PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC*)0x00000001411A3BD0; // glGetNamedFramebufferAttachmentParameterivEXT
PFNGLGETNAMEDPROGRAMIVEXTPROC* divagl_glGetNamedProgramivEXT
    = (PFNGLGETNAMEDPROGRAMIVEXTPROC*)0x00000001411A3970; // glGetNamedProgramivEXT
PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC* divagl_glGetNamedProgramLocalParameterdvEXT
    = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC*)0x00000001411A3960; // glGetNamedProgramLocalParameterdvEXT
PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC* divagl_glGetNamedProgramLocalParameterfvEXT
    = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC*)0x00000001411A3968; // glGetNamedProgramLocalParameterfvEXT
PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC* divagl_glGetNamedProgramLocalParameterIivEXT
    = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC*)0x00000001411A39B8; // glGetNamedProgramLocalParameterIivEXT
PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC* divagl_glGetNamedProgramLocalParameterIuivEXT
    = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC*)0x00000001411A39C0; // glGetNamedProgramLocalParameterIuivEXT
PFNGLGETNAMEDPROGRAMSTRINGEXTPROC* divagl_glGetNamedProgramStringEXT
    = (PFNGLGETNAMEDPROGRAMSTRINGEXTPROC*)0x00000001411A3978; // glGetNamedProgramStringEXT
PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC* divagl_glGetNamedRenderbufferParameterivEXT
    = (PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC*)0x00000001411A3B70; // glGetNamedRenderbufferParameterivEXT
PFNGLGETOBJECTPARAMETERFVARBPROC* divagl_glGetObjectParameterfvARB
    = (PFNGLGETOBJECTPARAMETERFVARBPROC*)0x00000001411A4C98; // glGetObjectParameterfvARB
PFNGLGETOBJECTPARAMETERIVARBPROC* divagl_glGetObjectParameterivARB
    = (PFNGLGETOBJECTPARAMETERIVARBPROC*)0x00000001411A4CA0; // glGetObjectParameterivARB
PFNGLGETOCCLUSIONQUERYIVNVPROC* divagl_glGetOcclusionQueryivNV
    = (PFNGLGETOCCLUSIONQUERYIVNVPROC*)0x00000001411A52B0; // glGetOcclusionQueryivNV
PFNGLGETOCCLUSIONQUERYUIVNVPROC* divagl_glGetOcclusionQueryuivNV
    = (PFNGLGETOCCLUSIONQUERYUIVNVPROC*)0x00000001411A52B8; // glGetOcclusionQueryuivNV
PFNGLGETPOINTERINDEXEDVEXTPROC* divagl_glGetPointerIndexedvEXT
    = (PFNGLGETPOINTERINDEXEDVEXTPROC*)0x00000001411A38C0; // glGetPointerIndexedvEXT
PFNGLGETPOINTERVEXTPROC* divagl_glGetPointervEXT
    = (PFNGLGETPOINTERVEXTPROC*)0x00000001411A4E80; // glGetPointervEXT
PFNGLGETPROGRAMENVPARAMETERDVARBPROC* divagl_glGetProgramEnvParameterdvARB
    = (PFNGLGETPROGRAMENVPARAMETERDVARBPROC*)0x00000001411A4AB8; // glGetProgramEnvParameterdvARB
PFNGLGETPROGRAMENVPARAMETERIIVNVPROC* divagl_glGetProgramEnvParameterIivNV
    = (PFNGLGETPROGRAMENVPARAMETERIIVNVPROC*)0x00000001411A55C8; // glGetProgramEnvParameterIivNV
PFNGLGETPROGRAMENVPARAMETERIUIVNVPROC* divagl_glGetProgramEnvParameterIuivNV
    = (PFNGLGETPROGRAMENVPARAMETERIUIVNVPROC*)0x00000001411A55D0; // glGetProgramEnvParameterIuivNV
PFNGLGETPROGRAMINFOLOGPROC* divagl_glGetProgramInfoLog
    = (PFNGLGETPROGRAMINFOLOGPROC*)0x00000001411A42D8; // glGetProgramInfoLog
PFNGLGETPROGRAMIVPROC* divagl_glGetProgramiv
    = (PFNGLGETPROGRAMIVPROC*)0x00000001411A42D0; // glGetProgramiv
PFNGLGETPROGRAMIVNVPROC* divagl_glGetProgramivNV
    = (PFNGLGETPROGRAMIVNVPROC*)0x00000001411A50C0; // glGetProgramivNV
PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC* divagl_glGetProgramLocalParameterdvARB
    = (PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC*)0x00000001411A4AC8; // glGetProgramLocalParameterdvARB
PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC* divagl_glGetProgramLocalParameterfvARB
    = (PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC*)0x00000001411A4AD0; // glGetProgramLocalParameterfvARB
PFNGLGETPROGRAMLOCALPARAMETERIIVNVPROC* divagl_glGetProgramLocalParameterIivNV
    = (PFNGLGETPROGRAMLOCALPARAMETERIIVNVPROC*)0x00000001411A55B8; // glGetProgramLocalParameterIivNV
PFNGLGETPROGRAMLOCALPARAMETERIUIVNVPROC* divagl_glGetProgramLocalParameterIuivNV
    = (PFNGLGETPROGRAMLOCALPARAMETERIUIVNVPROC*)0x00000001411A55C0; // glGetProgramLocalParameterIuivNV
PFNGLGETPROGRAMNAMEDPARAMETERDVNVPROC* divagl_glGetProgramNamedParameterdvNV
    = (PFNGLGETPROGRAMNAMEDPARAMETERDVNVPROC*)0x00000001411A5308; // glGetProgramNamedParameterdvNV
PFNGLGETPROGRAMNAMEDPARAMETERFVNVPROC* divagl_glGetProgramNamedParameterfvNV
    = (PFNGLGETPROGRAMNAMEDPARAMETERFVNVPROC*)0x00000001411A5300; // glGetProgramNamedParameterfvNV
PFNGLGETPROGRAMPARAMETERDVNVPROC* divagl_glGetProgramParameterdvNV
    = (PFNGLGETPROGRAMPARAMETERDVNVPROC*)0x00000001411A50B0; // glGetProgramParameterdvNV
PFNGLGETPROGRAMPARAMETERFVNVPROC* divagl_glGetProgramParameterfvNV
    = (PFNGLGETPROGRAMPARAMETERFVNVPROC*)0x00000001411A50B8; // glGetProgramParameterfvNV
PFNGLGETPROGRAMSTRINGARBPROC* divagl_glGetProgramStringARB
    = (PFNGLGETPROGRAMSTRINGARBPROC*)0x00000001411A4AE0; // glGetProgramStringARB
PFNGLGETPROGRAMSTRINGNVPROC* divagl_glGetProgramStringNV
    = (PFNGLGETPROGRAMSTRINGNVPROC*)0x00000001411A50C8; // glGetProgramStringNV
PFNGLGETQUERYIVPROC* divagl_glGetQueryiv
    = (PFNGLGETQUERYIVPROC*)0x00000001411A41C8; // glGetQueryiv
PFNGLGETQUERYIVARBPROC* divagl_glGetQueryivARB
    = (PFNGLGETQUERYIVARBPROC*)0x00000001411A4B90; // glGetQueryivARB
PFNGLGETQUERYOBJECTI64VEXTPROC* divagl_glGetQueryObjecti64vEXT
    = (PFNGLGETQUERYOBJECTI64VEXTPROC*)0x00000001411A5538; // glGetQueryObjecti64vEXT
PFNGLGETQUERYOBJECTIVPROC* divagl_glGetQueryObjectiv
    = (PFNGLGETQUERYOBJECTIVPROC*)0x00000001411A41D0; // glGetQueryObjectiv
PFNGLGETQUERYOBJECTIVARBPROC* divagl_glGetQueryObjectivARB
    = (PFNGLGETQUERYOBJECTIVARBPROC*)0x00000001411A4B98; // glGetQueryObjectivARB
PFNGLGETQUERYOBJECTUI64VPROC* divagl_glGetQueryObjectui64v
    = (PFNGLGETQUERYOBJECTUI64VPROC*)0x00000001411A3F40; // glGetQueryObjectui64v
PFNGLGETQUERYOBJECTUI64VEXTPROC* divagl_glGetQueryObjectui64vEXT
    = (PFNGLGETQUERYOBJECTUI64VEXTPROC*)0x00000001411A5540; // glGetQueryObjectui64vEXT
PFNGLGETQUERYOBJECTUIVPROC* divagl_glGetQueryObjectuiv
    = (PFNGLGETQUERYOBJECTUIVPROC*)0x00000001411A41D8; // glGetQueryObjectuiv
PFNGLGETQUERYOBJECTUIVARBPROC* divagl_glGetQueryObjectuivARB
    = (PFNGLGETQUERYOBJECTUIVARBPROC*)0x00000001411A4BA0; // glGetQueryObjectuivARB
PFNGLGETRENDERBUFFERPARAMETERIVPROC* divagl_glGetRenderbufferParameteriv
    = (PFNGLGETRENDERBUFFERPARAMETERIVPROC*)0x00000001411A4D40; // glGetRenderbufferParameteriv
PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC* divagl_glGetRenderbufferParameterivEXT
    = (PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC*)0x00000001411A54C8; // glGetRenderbufferParameterivEXT
PFNGLGETSEPARABLEFILTERPROC* divagl_glGetSeparableFilter
    = (PFNGLGETSEPARABLEFILTERPROC*)0x00000001411A3CC8; // glGetSeparableFilter
PFNGLGETSHADERINFOLOGPROC* divagl_glGetShaderInfoLog
    = (PFNGLGETSHADERINFOLOGPROC*)0x00000001411A42E8; // glGetShaderInfoLog
PFNGLGETSHADERIVPROC* divagl_glGetShaderiv
    = (PFNGLGETSHADERIVPROC*)0x00000001411A42E0; // glGetShaderiv
PFNGLGETSHADERSOURCEPROC* divagl_glGetShaderSource
    = (PFNGLGETSHADERSOURCEPROC*)0x00000001411A42F0; // glGetShaderSource
PFNGLGETSHADERSOURCEARBPROC* divagl_glGetShaderSourceARB
    = (PFNGLGETSHADERSOURCEARBPROC*)0x00000001411A4CD8; // glGetShaderSourceARB
PFNGLGETSTRINGIPROC* divagl_glGetStringi
    = (PFNGLGETSTRINGIPROC*)0x00000001411A4710; // glGetStringi
PFNGLGETTEXPARAMETERIIVPROC* divagl_glGetTexParameterIiv
    = (PFNGLGETTEXPARAMETERIIVPROC*)0x00000001411A46E0; // glGetTexParameterIiv
PFNGLGETTEXPARAMETERIIVEXTPROC* divagl_glGetTexParameterIivEXT
    = (PFNGLGETTEXPARAMETERIIVEXTPROC*)0x00000001411A35D0; // glGetTexParameterIivEXT
PFNGLGETTEXPARAMETERIUIVPROC* divagl_glGetTexParameterIuiv
    = (PFNGLGETTEXPARAMETERIUIVPROC*)0x00000001411A46E8; // glGetTexParameterIuiv
PFNGLGETTEXPARAMETERIUIVEXTPROC* divagl_glGetTexParameterIuivEXT
    = (PFNGLGETTEXPARAMETERIUIVEXTPROC*)0x00000001411A35D8; // glGetTexParameterIuivEXT
PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC* divagl_glGetTextureLevelParameterfvEXT
    = (PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC*)0x00000001411A3750; // glGetTextureLevelParameterfvEXT
PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC* divagl_glGetTextureLevelParameterivEXT
    = (PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC*)0x00000001411A3758; // glGetTextureLevelParameterivEXT
PFNGLGETTEXTUREPARAMETERFVEXTPROC* divagl_glGetTextureParameterfvEXT
    = (PFNGLGETTEXTUREPARAMETERFVEXTPROC*)0x00000001411A3740; // glGetTextureParameterfvEXT
PFNGLGETTEXTUREPARAMETERIIVEXTPROC* divagl_glGetTextureParameterIivEXT
    = (PFNGLGETTEXTUREPARAMETERIIVEXTPROC*)0x00000001411A39D8; // glGetTextureParameterIivEXT
PFNGLGETTEXTUREPARAMETERIUIVEXTPROC* divagl_glGetTextureParameterIuivEXT
    = (PFNGLGETTEXTUREPARAMETERIUIVEXTPROC*)0x00000001411A39E0; // glGetTextureParameterIuivEXT
PFNGLGETTEXTUREPARAMETERIVEXTPROC* divagl_glGetTextureParameterivEXT
    = (PFNGLGETTEXTUREPARAMETERIVEXTPROC*)0x00000001411A3748; // glGetTextureParameterivEXT
PFNGLGETTRACKMATRIXIVNVPROC* divagl_glGetTrackMatrixivNV
    = (PFNGLGETTRACKMATRIXIVNVPROC*)0x00000001411A50D0; // glGetTrackMatrixivNV
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC* divagl_glGetTransformFeedbackVarying
    = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC*)0x00000001411A45A8; // glGetTransformFeedbackVarying
PFNGLGETTRANSFORMFEEDBACKVARYINGNVPROC* divagl_glGetTransformFeedbackVaryingNV
    = (PFNGLGETTRANSFORMFEEDBACKVARYINGNVPROC*)0x00000001411A35A0; // glGetTransformFeedbackVaryingNV
PFNGLGETUNIFORMBUFFERSIZEEXTPROC* divagl_glGetUniformBufferSizeEXT
    = (PFNGLGETUNIFORMBUFFERSIZEEXTPROC*)0x00000001411A35B0; // glGetUniformBufferSizeEXT
PFNGLGETUNIFORMFVPROC* divagl_glGetUniformfv
    = (PFNGLGETUNIFORMFVPROC*)0x00000001411A4300; // glGetUniformfv
PFNGLGETUNIFORMFVARBPROC* divagl_glGetUniformfvARB
    = (PFNGLGETUNIFORMFVARBPROC*)0x00000001411A4CC8; // glGetUniformfvARB
PFNGLGETUNIFORMIVPROC* divagl_glGetUniformiv
    = (PFNGLGETUNIFORMIVPROC*)0x00000001411A4308; // glGetUniformiv
PFNGLGETUNIFORMIVARBPROC* divagl_glGetUniformivARB
    = (PFNGLGETUNIFORMIVARBPROC*)0x00000001411A4CD0; // glGetUniformivARB
PFNGLGETUNIFORMLOCATIONPROC* divagl_glGetUniformLocation
    = (PFNGLGETUNIFORMLOCATIONPROC*)0x00000001411A42F8; // glGetUniformLocation
PFNGLGETUNIFORMLOCATIONARBPROC* divagl_glGetUniformLocationARB
    = (PFNGLGETUNIFORMLOCATIONARBPROC*)0x00000001411A4CB8; // glGetUniformLocationARB
PFNGLGETUNIFORMOFFSETEXTPROC* divagl_glGetUniformOffsetEXT
    = (PFNGLGETUNIFORMOFFSETEXTPROC*)0x00000001411A35B8; // glGetUniformOffsetEXT
PFNGLGETUNIFORMUIVPROC* divagl_glGetUniformuiv
    = (PFNGLGETUNIFORMUIVPROC*)0x00000001411A4678; // glGetUniformuiv
PFNGLGETUNIFORMUIVEXTPROC* divagl_glGetUniformuivEXT
    = (PFNGLGETUNIFORMUIVEXTPROC*)0x00000001411A56B8; // glGetUniformuivEXT
PFNGLGETVARYINGLOCATIONNVPROC* divagl_glGetVaryingLocationNV
    = (PFNGLGETVARYINGLOCATIONNVPROC*)0x00000001411A3590; // glGetVaryingLocationNV
PFNGLGETVERTEXATTRIBDVPROC* divagl_glGetVertexAttribdv
    = (PFNGLGETVERTEXATTRIBDVPROC*)0x00000001411A4310; // glGetVertexAttribdv
PFNGLGETVERTEXATTRIBDVARBPROC* divagl_glGetVertexAttribdvARB
    = (PFNGLGETVERTEXATTRIBDVARBPROC*)0x00000001411A4AE8; // glGetVertexAttribdvARB
PFNGLGETVERTEXATTRIBDVNVPROC* divagl_glGetVertexAttribdvNV
    = (PFNGLGETVERTEXATTRIBDVNVPROC*)0x00000001411A50D8; // glGetVertexAttribdvNV
PFNGLGETVERTEXATTRIBFVPROC* divagl_glGetVertexAttribfv
    = (PFNGLGETVERTEXATTRIBFVPROC*)0x00000001411A4318; // glGetVertexAttribfv
PFNGLGETVERTEXATTRIBFVARBPROC* divagl_glGetVertexAttribfvARB
    = (PFNGLGETVERTEXATTRIBFVARBPROC*)0x00000001411A4AF0; // glGetVertexAttribfvARB
PFNGLGETVERTEXATTRIBFVNVPROC* divagl_glGetVertexAttribfvNV
    = (PFNGLGETVERTEXATTRIBFVNVPROC*)0x00000001411A50E0; // glGetVertexAttribfvNV
PFNGLGETVERTEXATTRIBIIVPROC* divagl_glGetVertexAttribIiv
    = (PFNGLGETVERTEXATTRIBIIVPROC*)0x00000001411A4668; // glGetVertexAttribIiv
PFNGLGETVERTEXATTRIBIIVEXTPROC* divagl_glGetVertexAttribIivEXT
    = (PFNGLGETVERTEXATTRIBIIVEXTPROC*)0x00000001411A56A8; // glGetVertexAttribIivEXT
PFNGLGETVERTEXATTRIBIUIVPROC* divagl_glGetVertexAttribIuiv
    = (PFNGLGETVERTEXATTRIBIUIVPROC*)0x00000001411A4670; // glGetVertexAttribIuiv
PFNGLGETVERTEXATTRIBIUIVEXTPROC* divagl_glGetVertexAttribIuivEXT
    = (PFNGLGETVERTEXATTRIBIUIVEXTPROC*)0x00000001411A56B0; // glGetVertexAttribIuivEXT
PFNGLGETVERTEXATTRIBIVPROC* divagl_glGetVertexAttribiv
    = (PFNGLGETVERTEXATTRIBIVPROC*)0x00000001411A4320; // glGetVertexAttribiv
PFNGLGETVERTEXATTRIBIVARBPROC* divagl_glGetVertexAttribivARB
    = (PFNGLGETVERTEXATTRIBIVARBPROC*)0x00000001411A4AF8; // glGetVertexAttribivARB
PFNGLGETVERTEXATTRIBIVNVPROC* divagl_glGetVertexAttribivNV
    = (PFNGLGETVERTEXATTRIBIVNVPROC*)0x00000001411A50E8; // glGetVertexAttribivNV
PFNGLGETVERTEXATTRIBPOINTERVPROC* divagl_glGetVertexAttribPointerv
    = (PFNGLGETVERTEXATTRIBPOINTERVPROC*)0x00000001411A4328; // glGetVertexAttribPointerv
PFNGLGETVERTEXATTRIBPOINTERVARBPROC* divagl_glGetVertexAttribPointervARB
    = (PFNGLGETVERTEXATTRIBPOINTERVARBPROC*)0x00000001411A4B00; // glGetVertexAttribPointervARB
PFNGLGETVERTEXATTRIBPOINTERVNVPROC* divagl_glGetVertexAttribPointervNV
    = (PFNGLGETVERTEXATTRIBPOINTERVNVPROC*)0x00000001411A50F0; // glGetVertexAttribPointervNV
PFNGLGETVIDEOI64VNVPROC* divagl_glGetVideoi64vNV
    = (PFNGLGETVIDEOI64VNVPROC*)0x00000001411A3620; // glGetVideoi64vNV
PFNGLGETVIDEOIVNVPROC* divagl_glGetVideoivNV
    = (PFNGLGETVIDEOIVNVPROC*)0x00000001411A3610; // glGetVideoivNV
PFNGLGETVIDEOUI64VNVPROC* divagl_glGetVideoui64vNV
    = (PFNGLGETVIDEOUI64VNVPROC*)0x00000001411A3628; // glGetVideoui64vNV
PFNGLGETVIDEOUIVNVPROC* divagl_glGetVideouivNV
    = (PFNGLGETVIDEOUIVNVPROC*)0x00000001411A3618; // glGetVideouivNV
PFNGLHISTOGRAMPROC* divagl_glHistogram
    = (PFNGLHISTOGRAMPROC*)0x00000001411A3D48; // glHistogram
PFNGLINDEXPOINTEREXTPROC* divagl_glIndexPointerEXT
    = (PFNGLINDEXPOINTEREXTPROC*)0x00000001411A4E88; // glIndexPointerEXT
PFNGLISBUFFERPROC* divagl_glIsBuffer
    = (PFNGLISBUFFERPROC*)0x00000001411A41F8; // glIsBuffer
PFNGLISENABLEDIPROC* divagl_glIsEnabledi
    = (PFNGLISENABLEDIPROC*)0x00000001411A4578; // glIsEnabledi
PFNGLISENABLEDINDEXEDEXTPROC* divagl_glIsEnabledIndexedEXT
    = (PFNGLISENABLEDINDEXEDEXTPROC*)0x00000001411A3548; // glIsEnabledIndexedEXT
PFNGLISFENCENVPROC* divagl_glIsFenceNV
    = (PFNGLISFENCENVPROC*)0x00000001411A5050; // glIsFenceNV
PFNGLISFRAMEBUFFERPROC* divagl_glIsFramebuffer
    = (PFNGLISFRAMEBUFFERPROC*)0x00000001411A4D48; // glIsFramebuffer
PFNGLISFRAMEBUFFEREXTPROC* divagl_glIsFramebufferEXT
    = (PFNGLISFRAMEBUFFEREXTPROC*)0x00000001411A54D0; // glIsFramebufferEXT
PFNGLISOCCLUSIONQUERYNVPROC* divagl_glIsOcclusionQueryNV
    = (PFNGLISOCCLUSIONQUERYNVPROC*)0x00000001411A5298; // glIsOcclusionQueryNV
PFNGLISPROGRAMPROC* divagl_glIsProgram
    = (PFNGLISPROGRAMPROC*)0x00000001411A4330; // glIsProgram
PFNGLISPROGRAMARBPROC* divagl_glIsProgramARB
    = (PFNGLISPROGRAMARBPROC*)0x00000001411A4B08; // glIsProgramARB
PFNGLISPROGRAMNVPROC* divagl_glIsProgramNV
    = (PFNGLISPROGRAMNVPROC*)0x00000001411A50F8; // glIsProgramNV
PFNGLISQUERYPROC* divagl_glIsQuery
    = (PFNGLISQUERYPROC*)0x00000001411A41B0; // glIsQuery
PFNGLISQUERYARBPROC* divagl_glIsQueryARB
    = (PFNGLISQUERYARBPROC*)0x00000001411A4B78; // glIsQueryARB
PFNGLISRENDERBUFFERPROC* divagl_glIsRenderbuffer
    = (PFNGLISRENDERBUFFERPROC*)0x00000001411A4D18; // glIsRenderbuffer
PFNGLISRENDERBUFFEREXTPROC* divagl_glIsRenderbufferEXT
    = (PFNGLISRENDERBUFFEREXTPROC*)0x00000001411A54A0; // glIsRenderbufferEXT
PFNGLISSHADERPROC* divagl_glIsShader
    = (PFNGLISSHADERPROC*)0x00000001411A4338; // glIsShader
PFNGLISTEXTUREEXTPROC* divagl_glIsTextureEXT
    = (PFNGLISTEXTUREEXTPROC*)0x00000001411A4E50; // glIsTextureEXT
PFNGLISVERTEXARRAYPROC* divagl_glIsVertexArray
    = (PFNGLISVERTEXARRAYPROC*)0x00000001411A4E08; // glIsVertexArray
PFNGLLINKPROGRAMPROC* divagl_glLinkProgram
    = (PFNGLLINKPROGRAMPROC*)0x00000001411A4340; // glLinkProgram
PFNGLLINKPROGRAMARBPROC* divagl_glLinkProgramARB
    = (PFNGLLINKPROGRAMARBPROC*)0x00000001411A4BE8; // glLinkProgramARB
PFNGLLOADPROGRAMNVPROC* divagl_glLoadProgramNV
    = (PFNGLLOADPROGRAMNVPROC*)0x00000001411A5100; // glLoadProgramNV
PFNGLLOADTRANSPOSEMATRIXDPROC* divagl_glLoadTransposeMatrixd
    = (PFNGLLOADTRANSPOSEMATRIXDPROC*)0x00000001411A3FE0; // glLoadTransposeMatrixd
PFNGLLOADTRANSPOSEMATRIXDARBPROC* divagl_glLoadTransposeMatrixdARB
    = (PFNGLLOADTRANSPOSEMATRIXDARBPROC*)0x00000001411A4838; // glLoadTransposeMatrixdARB
PFNGLLOADTRANSPOSEMATRIXFARBPROC* divagl_glLoadTransposeMatrixfARB
    = (PFNGLLOADTRANSPOSEMATRIXFARBPROC*)0x00000001411A4830; // glLoadTransposeMatrixfARB
PFNGLLOCKARRAYSEXTPROC* divagl_glLockArraysEXT
    = (PFNGLLOCKARRAYSEXTPROC*)0x00000001411A4EE8; // glLockArraysEXT
PFNGLMAPBUFFERPROC* divagl_glMapBuffer
    = (PFNGLMAPBUFFERPROC*)0x00000001411A4218; // glMapBuffer
PFNGLMAPBUFFERARBPROC* divagl_glMapBufferARB
    = (PFNGLMAPBUFFERARBPROC*)0x00000001411A4B48; // glMapBufferARB
PFNGLMAPBUFFERRANGEPROC* divagl_glMapBufferRange
    = (PFNGLMAPBUFFERRANGEPROC*)0x00000001411A4DD8; // glMapBufferRange
PFNGLMATRIXFRUSTUMEXTPROC* divagl_glMatrixFrustumEXT
    = (PFNGLMATRIXFRUSTUMEXTPROC*)0x00000001411A3698; // glMatrixFrustumEXT
PFNGLMATRIXLOADDEXTPROC* divagl_glMatrixLoaddEXT
    = (PFNGLMATRIXLOADDEXTPROC*)0x00000001411A3648; // glMatrixLoaddEXT
PFNGLMATRIXLOADFEXTPROC* divagl_glMatrixLoadfEXT
    = (PFNGLMATRIXLOADFEXTPROC*)0x00000001411A3640; // glMatrixLoadfEXT
PFNGLMATRIXLOADIDENTITYEXTPROC* divagl_glMatrixLoadIdentityEXT
    = (PFNGLMATRIXLOADIDENTITYEXTPROC*)0x00000001411A3660; // glMatrixLoadIdentityEXT
PFNGLMATRIXLOADTRANSPOSEDEXTPROC* divagl_glMatrixLoadTransposedEXT
    = (PFNGLMATRIXLOADTRANSPOSEDEXTPROC*)0x00000001411A36C0; // glMatrixLoadTransposedEXT
PFNGLMATRIXLOADTRANSPOSEFEXTPROC* divagl_glMatrixLoadTransposefEXT
    = (PFNGLMATRIXLOADTRANSPOSEFEXTPROC*)0x00000001411A36B8; // glMatrixLoadTransposefEXT
PFNGLMATRIXMULTDEXTPROC* divagl_glMatrixMultdEXT
    = (PFNGLMATRIXMULTDEXTPROC*)0x00000001411A3658; // glMatrixMultdEXT
PFNGLMATRIXMULTFEXTPROC* divagl_glMatrixMultfEXT
    = (PFNGLMATRIXMULTFEXTPROC*)0x00000001411A3650; // glMatrixMultfEXT
PFNGLMATRIXMULTTRANSPOSEDEXTPROC* divagl_glMatrixMultTransposedEXT
    = (PFNGLMATRIXMULTTRANSPOSEDEXTPROC*)0x00000001411A36D0; // glMatrixMultTransposedEXT
PFNGLMATRIXMULTTRANSPOSEFEXTPROC* divagl_glMatrixMultTransposefEXT
    = (PFNGLMATRIXMULTTRANSPOSEFEXTPROC*)0x00000001411A36C8; // glMatrixMultTransposefEXT
PFNGLMATRIXORTHOEXTPROC* divagl_glMatrixOrthoEXT
    = (PFNGLMATRIXORTHOEXTPROC*)0x00000001411A36A0; // glMatrixOrthoEXT
PFNGLMATRIXPOPEXTPROC* divagl_glMatrixPopEXT
    = (PFNGLMATRIXPOPEXTPROC*)0x00000001411A36A8; // glMatrixPopEXT
PFNGLMATRIXPUSHEXTPROC* divagl_glMatrixPushEXT
    = (PFNGLMATRIXPUSHEXTPROC*)0x00000001411A36B0; // glMatrixPushEXT
PFNGLMATRIXROTATEDEXTPROC* divagl_glMatrixRotatedEXT
    = (PFNGLMATRIXROTATEDEXTPROC*)0x00000001411A3670; // glMatrixRotatedEXT
PFNGLMATRIXROTATEFEXTPROC* divagl_glMatrixRotatefEXT
    = (PFNGLMATRIXROTATEFEXTPROC*)0x00000001411A3668; // glMatrixRotatefEXT
PFNGLMATRIXSCALEDEXTPROC* divagl_glMatrixScaledEXT
    = (PFNGLMATRIXSCALEDEXTPROC*)0x00000001411A3680; // glMatrixScaledEXT
PFNGLMATRIXSCALEFEXTPROC* divagl_glMatrixScalefEXT
    = (PFNGLMATRIXSCALEFEXTPROC*)0x00000001411A3678; // glMatrixScalefEXT
PFNGLMATRIXTRANSLATEDEXTPROC* divagl_glMatrixTranslatedEXT
    = (PFNGLMATRIXTRANSLATEDEXTPROC*)0x00000001411A3690; // glMatrixTranslatedEXT
PFNGLMATRIXTRANSLATEFEXTPROC* divagl_glMatrixTranslatefEXT
    = (PFNGLMATRIXTRANSLATEFEXTPROC*)0x00000001411A3688; // glMatrixTranslatefEXT
PFNGLMINMAXPROC* divagl_glMinmax
    = (PFNGLMINMAXPROC*)0x00000001411A3D58; // glMinmax
PFNGLMULTIDRAWARRAYSPROC* divagl_glMultiDrawArrays
    = (PFNGLMULTIDRAWARRAYSPROC*)0x00000001411A4068; // glMultiDrawArrays
PFNGLMULTIDRAWARRAYSEXTPROC* divagl_glMultiDrawArraysEXT
    = (PFNGLMULTIDRAWARRAYSEXTPROC*)0x00000001411A4F88; // glMultiDrawArraysEXT
PFNGLMULTIDRAWELEMENTSPROC* divagl_glMultiDrawElements
    = (PFNGLMULTIDRAWELEMENTSPROC*)0x00000001411A4070; // glMultiDrawElements
PFNGLMULTIDRAWELEMENTSEXTPROC* divagl_glMultiDrawElementsEXT
    = (PFNGLMULTIDRAWELEMENTSEXTPROC*)0x00000001411A4F90; // glMultiDrawElementsEXT
PFNGLMULTITEXBUFFEREXTPROC* divagl_glMultiTexBufferEXT
    = (PFNGLMULTITEXBUFFEREXTPROC*)0x00000001411A3B50; // glMultiTexBufferEXT
PFNGLMULTITEXCOORD1DPROC* divagl_glMultiTexCoord1d
    = (PFNGLMULTITEXCOORD1DPROC*)0x00000001411A3DD8; // glMultiTexCoord1d
PFNGLMULTITEXCOORD1DARBPROC* divagl_glMultiTexCoord1dARB
    = (PFNGLMULTITEXCOORD1DARBPROC*)0x00000001411A4730; // glMultiTexCoord1dARB
PFNGLMULTITEXCOORD1DVPROC* divagl_glMultiTexCoord1dv
    = (PFNGLMULTITEXCOORD1DVPROC*)0x00000001411A3DE8; // glMultiTexCoord1dv
PFNGLMULTITEXCOORD1DVARBPROC* divagl_glMultiTexCoord1dvARB
    = (PFNGLMULTITEXCOORD1DVARBPROC*)0x00000001411A4738; // glMultiTexCoord1dvARB
PFNGLMULTITEXCOORD1FPROC* divagl_glMultiTexCoord1f
    = (PFNGLMULTITEXCOORD1FPROC*)0x00000001411A3DF8; // glMultiTexCoord1f
PFNGLMULTITEXCOORD1FARBPROC* divagl_glMultiTexCoord1fARB
    = (PFNGLMULTITEXCOORD1FARBPROC*)0x00000001411A4740; // glMultiTexCoord1fARB
PFNGLMULTITEXCOORD1FVPROC* divagl_glMultiTexCoord1fv
    = (PFNGLMULTITEXCOORD1FVPROC*)0x00000001411A3E08; // glMultiTexCoord1fv
PFNGLMULTITEXCOORD1FVARBPROC* divagl_glMultiTexCoord1fvARB
    = (PFNGLMULTITEXCOORD1FVARBPROC*)0x00000001411A4748; // glMultiTexCoord1fvARB
PFNGLMULTITEXCOORD1HNVPROC* divagl_glMultiTexCoord1hNV
    = (PFNGLMULTITEXCOORD1HNVPROC*)0x00000001411A53B0; // glMultiTexCoord1hNV
PFNGLMULTITEXCOORD1HVNVPROC* divagl_glMultiTexCoord1hvNV
    = (PFNGLMULTITEXCOORD1HVNVPROC*)0x00000001411A53B8; // glMultiTexCoord1hvNV
PFNGLMULTITEXCOORD1IPROC* divagl_glMultiTexCoord1i
    = (PFNGLMULTITEXCOORD1IPROC*)0x00000001411A3E18; // glMultiTexCoord1i
PFNGLMULTITEXCOORD1IARBPROC* divagl_glMultiTexCoord1iARB
    = (PFNGLMULTITEXCOORD1IARBPROC*)0x00000001411A4750; // glMultiTexCoord1iARB
PFNGLMULTITEXCOORD1IVPROC* divagl_glMultiTexCoord1iv
    = (PFNGLMULTITEXCOORD1IVPROC*)0x00000001411A3E28; // glMultiTexCoord1iv
PFNGLMULTITEXCOORD1IVARBPROC* divagl_glMultiTexCoord1ivARB
    = (PFNGLMULTITEXCOORD1IVARBPROC*)0x00000001411A4758; // glMultiTexCoord1ivARB
PFNGLMULTITEXCOORD1SPROC* divagl_glMultiTexCoord1s
    = (PFNGLMULTITEXCOORD1SPROC*)0x00000001411A3E38; // glMultiTexCoord1s
PFNGLMULTITEXCOORD1SARBPROC* divagl_glMultiTexCoord1sARB
    = (PFNGLMULTITEXCOORD1SARBPROC*)0x00000001411A4760; // glMultiTexCoord1sARB
PFNGLMULTITEXCOORD1SVPROC* divagl_glMultiTexCoord1sv
    = (PFNGLMULTITEXCOORD1SVPROC*)0x00000001411A3E48; // glMultiTexCoord1sv
PFNGLMULTITEXCOORD1SVARBPROC* divagl_glMultiTexCoord1svARB
    = (PFNGLMULTITEXCOORD1SVARBPROC*)0x00000001411A4768; // glMultiTexCoord1svARB
PFNGLMULTITEXCOORD2DPROC* divagl_glMultiTexCoord2d
    = (PFNGLMULTITEXCOORD2DPROC*)0x00000001411A3E58; // glMultiTexCoord2d
PFNGLMULTITEXCOORD2DARBPROC* divagl_glMultiTexCoord2dARB
    = (PFNGLMULTITEXCOORD2DARBPROC*)0x00000001411A4770; // glMultiTexCoord2dARB
PFNGLMULTITEXCOORD2DVPROC* divagl_glMultiTexCoord2dv
    = (PFNGLMULTITEXCOORD2DVPROC*)0x00000001411A3E68; // glMultiTexCoord2dv
PFNGLMULTITEXCOORD2DVARBPROC* divagl_glMultiTexCoord2dvARB
    = (PFNGLMULTITEXCOORD2DVARBPROC*)0x00000001411A4778; // glMultiTexCoord2dvARB
PFNGLMULTITEXCOORD2FARBPROC* divagl_glMultiTexCoord2fARB
    = (PFNGLMULTITEXCOORD2FARBPROC*)0x00000001411A4780; // glMultiTexCoord2fARB
PFNGLMULTITEXCOORD2FVARBPROC* divagl_glMultiTexCoord2fvARB
    = (PFNGLMULTITEXCOORD2FVARBPROC*)0x00000001411A4788; // glMultiTexCoord2fvARB
PFNGLMULTITEXCOORD2HNVPROC* divagl_glMultiTexCoord2hNV
    = (PFNGLMULTITEXCOORD2HNVPROC*)0x00000001411A53C0; // glMultiTexCoord2hNV
PFNGLMULTITEXCOORD2HVNVPROC* divagl_glMultiTexCoord2hvNV
    = (PFNGLMULTITEXCOORD2HVNVPROC*)0x00000001411A53C8; // glMultiTexCoord2hvNV
PFNGLMULTITEXCOORD2IPROC* divagl_glMultiTexCoord2i
    = (PFNGLMULTITEXCOORD2IPROC*)0x00000001411A3E98; // glMultiTexCoord2i
PFNGLMULTITEXCOORD2IARBPROC* divagl_glMultiTexCoord2iARB
    = (PFNGLMULTITEXCOORD2IARBPROC*)0x00000001411A4790; // glMultiTexCoord2iARB
PFNGLMULTITEXCOORD2IVPROC* divagl_glMultiTexCoord2iv
    = (PFNGLMULTITEXCOORD2IVPROC*)0x00000001411A3EA8; // glMultiTexCoord2iv
PFNGLMULTITEXCOORD2IVARBPROC* divagl_glMultiTexCoord2ivARB
    = (PFNGLMULTITEXCOORD2IVARBPROC*)0x00000001411A4798; // glMultiTexCoord2ivARB
PFNGLMULTITEXCOORD2SPROC* divagl_glMultiTexCoord2s
    = (PFNGLMULTITEXCOORD2SPROC*)0x00000001411A3EB8; // glMultiTexCoord2s
PFNGLMULTITEXCOORD2SARBPROC* divagl_glMultiTexCoord2sARB
    = (PFNGLMULTITEXCOORD2SARBPROC*)0x00000001411A47A0; // glMultiTexCoord2sARB
PFNGLMULTITEXCOORD2SVPROC* divagl_glMultiTexCoord2sv
    = (PFNGLMULTITEXCOORD2SVPROC*)0x00000001411A3EC8; // glMultiTexCoord2sv
PFNGLMULTITEXCOORD2SVARBPROC* divagl_glMultiTexCoord2svARB
    = (PFNGLMULTITEXCOORD2SVARBPROC*)0x00000001411A47A8; // glMultiTexCoord2svARB
PFNGLMULTITEXCOORD3DPROC* divagl_glMultiTexCoord3d
    = (PFNGLMULTITEXCOORD3DPROC*)0x00000001411A3ED8; // glMultiTexCoord3d
PFNGLMULTITEXCOORD3DARBPROC* divagl_glMultiTexCoord3dARB
    = (PFNGLMULTITEXCOORD3DARBPROC*)0x00000001411A47B0; // glMultiTexCoord3dARB
PFNGLMULTITEXCOORD3DVPROC* divagl_glMultiTexCoord3dv
    = (PFNGLMULTITEXCOORD3DVPROC*)0x00000001411A3EE8; // glMultiTexCoord3dv
PFNGLMULTITEXCOORD3DVARBPROC* divagl_glMultiTexCoord3dvARB
    = (PFNGLMULTITEXCOORD3DVARBPROC*)0x00000001411A47B8; // glMultiTexCoord3dvARB
PFNGLMULTITEXCOORD3FPROC* divagl_glMultiTexCoord3f
    = (PFNGLMULTITEXCOORD3FPROC*)0x00000001411A3EF8; // glMultiTexCoord3f
PFNGLMULTITEXCOORD3FARBPROC* divagl_glMultiTexCoord3fARB
    = (PFNGLMULTITEXCOORD3FARBPROC*)0x00000001411A47C0; // glMultiTexCoord3fARB
PFNGLMULTITEXCOORD3FVPROC* divagl_glMultiTexCoord3fv
    = (PFNGLMULTITEXCOORD3FVPROC*)0x00000001411A3F08; // glMultiTexCoord3fv
PFNGLMULTITEXCOORD3FVARBPROC* divagl_glMultiTexCoord3fvARB
    = (PFNGLMULTITEXCOORD3FVARBPROC*)0x00000001411A47C8; // glMultiTexCoord3fvARB
PFNGLMULTITEXCOORD3HNVPROC* divagl_glMultiTexCoord3hNV
    = (PFNGLMULTITEXCOORD3HNVPROC*)0x00000001411A53D0; // glMultiTexCoord3hNV
PFNGLMULTITEXCOORD3HVNVPROC* divagl_glMultiTexCoord3hvNV
    = (PFNGLMULTITEXCOORD3HVNVPROC*)0x00000001411A53D8; // glMultiTexCoord3hvNV
PFNGLMULTITEXCOORD3IPROC* divagl_glMultiTexCoord3i
    = (PFNGLMULTITEXCOORD3IPROC*)0x00000001411A3F18; // glMultiTexCoord3i
PFNGLMULTITEXCOORD3IARBPROC* divagl_glMultiTexCoord3iARB
    = (PFNGLMULTITEXCOORD3IARBPROC*)0x00000001411A47D0; // glMultiTexCoord3iARB
PFNGLMULTITEXCOORD3IVPROC* divagl_glMultiTexCoord3iv
    = (PFNGLMULTITEXCOORD3IVPROC*)0x00000001411A3F28; // glMultiTexCoord3iv
PFNGLMULTITEXCOORD3IVARBPROC* divagl_glMultiTexCoord3ivARB
    = (PFNGLMULTITEXCOORD3IVARBPROC*)0x00000001411A47D8; // glMultiTexCoord3ivARB
PFNGLMULTITEXCOORD3SPROC* divagl_glMultiTexCoord3s
    = (PFNGLMULTITEXCOORD3SPROC*)0x00000001411A3F38; // glMultiTexCoord3s
PFNGLMULTITEXCOORD3SARBPROC* divagl_glMultiTexCoord3sARB
    = (PFNGLMULTITEXCOORD3SARBPROC*)0x00000001411A47E0; // glMultiTexCoord3sARB
PFNGLMULTITEXCOORD3SVPROC* divagl_glMultiTexCoord3sv
    = (PFNGLMULTITEXCOORD3SVPROC*)0x00000001411A3F48; // glMultiTexCoord3sv
PFNGLMULTITEXCOORD3SVARBPROC* divagl_glMultiTexCoord3svARB
    = (PFNGLMULTITEXCOORD3SVARBPROC*)0x00000001411A47E8; // glMultiTexCoord3svARB
PFNGLMULTITEXCOORD4DPROC* divagl_glMultiTexCoord4d
    = (PFNGLMULTITEXCOORD4DPROC*)0x00000001411A3F58; // glMultiTexCoord4d
PFNGLMULTITEXCOORD4DARBPROC* divagl_glMultiTexCoord4dARB
    = (PFNGLMULTITEXCOORD4DARBPROC*)0x00000001411A47F0; // glMultiTexCoord4dARB
PFNGLMULTITEXCOORD4DVPROC* divagl_glMultiTexCoord4dv
    = (PFNGLMULTITEXCOORD4DVPROC*)0x00000001411A3F68; // glMultiTexCoord4dv
PFNGLMULTITEXCOORD4DVARBPROC* divagl_glMultiTexCoord4dvARB
    = (PFNGLMULTITEXCOORD4DVARBPROC*)0x00000001411A47F8; // glMultiTexCoord4dvARB
PFNGLMULTITEXCOORD4FPROC* divagl_glMultiTexCoord4f
    = (PFNGLMULTITEXCOORD4FPROC*)0x00000001411A3F78; // glMultiTexCoord4f
PFNGLMULTITEXCOORD4FARBPROC* divagl_glMultiTexCoord4fARB
    = (PFNGLMULTITEXCOORD4FARBPROC*)0x00000001411A4800; // glMultiTexCoord4fARB
PFNGLMULTITEXCOORD4FVPROC* divagl_glMultiTexCoord4fv
    = (PFNGLMULTITEXCOORD4FVPROC*)0x00000001411A3F88; // glMultiTexCoord4fv
PFNGLMULTITEXCOORD4FVARBPROC* divagl_glMultiTexCoord4fvARB
    = (PFNGLMULTITEXCOORD4FVARBPROC*)0x00000001411A4808; // glMultiTexCoord4fvARB
PFNGLMULTITEXCOORD4HNVPROC* divagl_glMultiTexCoord4hNV
    = (PFNGLMULTITEXCOORD4HNVPROC*)0x00000001411A53E0; // glMultiTexCoord4hNV
PFNGLMULTITEXCOORD4HVNVPROC* divagl_glMultiTexCoord4hvNV
    = (PFNGLMULTITEXCOORD4HVNVPROC*)0x00000001411A53E8; // glMultiTexCoord4hvNV
PFNGLMULTITEXCOORD4IPROC* divagl_glMultiTexCoord4i
    = (PFNGLMULTITEXCOORD4IPROC*)0x00000001411A3F98; // glMultiTexCoord4i
PFNGLMULTITEXCOORD4IARBPROC* divagl_glMultiTexCoord4iARB
    = (PFNGLMULTITEXCOORD4IARBPROC*)0x00000001411A4810; // glMultiTexCoord4iARB
PFNGLMULTITEXCOORD4IVPROC* divagl_glMultiTexCoord4iv
    = (PFNGLMULTITEXCOORD4IVPROC*)0x00000001411A3FA8; // glMultiTexCoord4iv
PFNGLMULTITEXCOORD4IVARBPROC* divagl_glMultiTexCoord4ivARB
    = (PFNGLMULTITEXCOORD4IVARBPROC*)0x00000001411A4818; // glMultiTexCoord4ivARB
PFNGLMULTITEXCOORD4SPROC* divagl_glMultiTexCoord4s
    = (PFNGLMULTITEXCOORD4SPROC*)0x00000001411A3FB8; // glMultiTexCoord4s
PFNGLMULTITEXCOORD4SARBPROC* divagl_glMultiTexCoord4sARB
    = (PFNGLMULTITEXCOORD4SARBPROC*)0x00000001411A4820; // glMultiTexCoord4sARB
PFNGLMULTITEXCOORD4SVPROC* divagl_glMultiTexCoord4sv
    = (PFNGLMULTITEXCOORD4SVPROC*)0x00000001411A3FC8; // glMultiTexCoord4sv
PFNGLMULTITEXCOORD4SVARBPROC* divagl_glMultiTexCoord4svARB
    = (PFNGLMULTITEXCOORD4SVARBPROC*)0x00000001411A4828; // glMultiTexCoord4svARB
PFNGLMULTITEXCOORDPOINTEREXTPROC* divagl_glMultiTexCoordPointerEXT
    = (PFNGLMULTITEXCOORDPOINTEREXTPROC*)0x00000001411A3830; // glMultiTexCoordPointerEXT
PFNGLMULTITEXENVFEXTPROC* divagl_glMultiTexEnvfEXT
    = (PFNGLMULTITEXENVFEXTPROC*)0x00000001411A3838; // glMultiTexEnvfEXT
PFNGLMULTITEXENVFVEXTPROC* divagl_glMultiTexEnvfvEXT
    = (PFNGLMULTITEXENVFVEXTPROC*)0x00000001411A3840; // glMultiTexEnvfvEXT
PFNGLMULTITEXENVIEXTPROC* divagl_glMultiTexEnviEXT
    = (PFNGLMULTITEXENVIEXTPROC*)0x00000001411A3848; // glMultiTexEnviEXT
PFNGLMULTITEXENVIVEXTPROC* divagl_glMultiTexEnvivEXT
    = (PFNGLMULTITEXENVIVEXTPROC*)0x00000001411A3850; // glMultiTexEnvivEXT
PFNGLMULTITEXGENDEXTPROC* divagl_glMultiTexGendEXT
    = (PFNGLMULTITEXGENDEXTPROC*)0x00000001411A3858; // glMultiTexGendEXT
PFNGLMULTITEXGENDVEXTPROC* divagl_glMultiTexGendvEXT
    = (PFNGLMULTITEXGENDVEXTPROC*)0x00000001411A3860; // glMultiTexGendvEXT
PFNGLMULTITEXGENFEXTPROC* divagl_glMultiTexGenfEXT
    = (PFNGLMULTITEXGENFEXTPROC*)0x00000001411A3868; // glMultiTexGenfEXT
PFNGLMULTITEXGENFVEXTPROC* divagl_glMultiTexGenfvEXT
    = (PFNGLMULTITEXGENFVEXTPROC*)0x00000001411A3870; // glMultiTexGenfvEXT
PFNGLMULTITEXGENIEXTPROC* divagl_glMultiTexGeniEXT
    = (PFNGLMULTITEXGENIEXTPROC*)0x00000001411A3878; // glMultiTexGeniEXT
PFNGLMULTITEXGENIVEXTPROC* divagl_glMultiTexGenivEXT
    = (PFNGLMULTITEXGENIVEXTPROC*)0x00000001411A3880; // glMultiTexGenivEXT
PFNGLMULTITEXIMAGE1DEXTPROC* divagl_glMultiTexImage1DEXT
    = (PFNGLMULTITEXIMAGE1DEXTPROC*)0x00000001411A3798; // glMultiTexImage1DEXT
PFNGLMULTITEXIMAGE2DEXTPROC* divagl_glMultiTexImage2DEXT
    = (PFNGLMULTITEXIMAGE2DEXTPROC*)0x00000001411A37A0; // glMultiTexImage2DEXT
PFNGLMULTITEXIMAGE3DEXTPROC* divagl_glMultiTexImage3DEXT
    = (PFNGLMULTITEXIMAGE3DEXTPROC*)0x00000001411A3800; // glMultiTexImage3DEXT
PFNGLMULTITEXPARAMETERFEXTPROC* divagl_glMultiTexParameterfEXT
    = (PFNGLMULTITEXPARAMETERFEXTPROC*)0x00000001411A3778; // glMultiTexParameterfEXT
PFNGLMULTITEXPARAMETERFVEXTPROC* divagl_glMultiTexParameterfvEXT
    = (PFNGLMULTITEXPARAMETERFVEXTPROC*)0x00000001411A3780; // glMultiTexParameterfvEXT
PFNGLMULTITEXPARAMETERIEXTPROC* divagl_glMultiTexParameteriEXT
    = (PFNGLMULTITEXPARAMETERIEXTPROC*)0x00000001411A3788; // glMultiTexParameteriEXT
PFNGLMULTITEXPARAMETERIIVEXTPROC* divagl_glMultiTexParameterIivEXT
    = (PFNGLMULTITEXPARAMETERIIVEXTPROC*)0x00000001411A39E8; // glMultiTexParameterIivEXT
PFNGLMULTITEXPARAMETERIUIVEXTPROC* divagl_glMultiTexParameterIuivEXT
    = (PFNGLMULTITEXPARAMETERIUIVEXTPROC*)0x00000001411A39F0; // glMultiTexParameterIuivEXT
PFNGLMULTITEXPARAMETERIVEXTPROC* divagl_glMultiTexParameterivEXT
    = (PFNGLMULTITEXPARAMETERIVEXTPROC*)0x00000001411A3790; // glMultiTexParameterivEXT
PFNGLMULTITEXRENDERBUFFEREXTPROC* divagl_glMultiTexRenderbufferEXT
    = (PFNGLMULTITEXRENDERBUFFEREXTPROC*)0x00000001411A3CA0; // glMultiTexRenderbufferEXT
PFNGLMULTITEXSUBIMAGE1DEXTPROC* divagl_glMultiTexSubImage1DEXT
    = (PFNGLMULTITEXSUBIMAGE1DEXTPROC*)0x00000001411A37A8; // glMultiTexSubImage1DEXT
PFNGLMULTITEXSUBIMAGE2DEXTPROC* divagl_glMultiTexSubImage2DEXT
    = (PFNGLMULTITEXSUBIMAGE2DEXTPROC*)0x00000001411A37B0; // glMultiTexSubImage2DEXT
PFNGLMULTITEXSUBIMAGE3DEXTPROC* divagl_glMultiTexSubImage3DEXT
    = (PFNGLMULTITEXSUBIMAGE3DEXTPROC*)0x00000001411A3808; // glMultiTexSubImage3DEXT
PFNGLMULTTRANSPOSEMATRIXDPROC* divagl_glMultTransposeMatrixd
    = (PFNGLMULTTRANSPOSEMATRIXDPROC*)0x00000001411A3FF0; // glMultTransposeMatrixd
PFNGLMULTTRANSPOSEMATRIXDARBPROC* divagl_glMultTransposeMatrixdARB
    = (PFNGLMULTTRANSPOSEMATRIXDARBPROC*)0x00000001411A4848; // glMultTransposeMatrixdARB
PFNGLMULTTRANSPOSEMATRIXFARBPROC* divagl_glMultTransposeMatrixfARB
    = (PFNGLMULTTRANSPOSEMATRIXFARBPROC*)0x00000001411A4840; // glMultTransposeMatrixfARB
PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC* divagl_glNamedFramebufferRenderbufferEXT
    = (PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC*)0x00000001411A3BC0; // glNamedFramebufferRenderbufferEXT
PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC* divagl_glNamedFramebufferTexture1DEXT
    = (PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC*)0x00000001411A3B90; // glNamedFramebufferTexture1DEXT
PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC* divagl_glNamedFramebufferTexture2DEXT
    = (PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC*)0x00000001411A3BA0; // glNamedFramebufferTexture2DEXT
PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC* divagl_glNamedFramebufferTexture3DEXT
    = (PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC*)0x00000001411A3BB0; // glNamedFramebufferTexture3DEXT
PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC* divagl_glNamedFramebufferTextureEXT
    = (PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC*)0x00000001411A3C60; // glNamedFramebufferTextureEXT
PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC* divagl_glNamedFramebufferTextureFaceEXT
    = (PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC*)0x00000001411A3C80; // glNamedFramebufferTextureFaceEXT
PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC* divagl_glNamedFramebufferTextureLayerEXT
    = (PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC*)0x00000001411A3C70; // glNamedFramebufferTextureLayerEXT
PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC* divagl_glNamedProgramLocalParameter4dEXT
    = (PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC*)0x00000001411A3940; // glNamedProgramLocalParameter4dEXT
PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC* divagl_glNamedProgramLocalParameter4dvEXT
    = (PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC*)0x00000001411A3948; // glNamedProgramLocalParameter4dvEXT
PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC* divagl_glNamedProgramLocalParameter4fEXT
    = (PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC*)0x00000001411A3950; // glNamedProgramLocalParameter4fEXT
PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC* divagl_glNamedProgramLocalParameter4fvEXT
    = (PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC*)0x00000001411A3958; // glNamedProgramLocalParameter4fvEXT
PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC* divagl_glNamedProgramLocalParameterI4iEXT
    = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC*)0x00000001411A3988; // glNamedProgramLocalParameterI4iEXT
PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC* divagl_glNamedProgramLocalParameterI4ivEXT
    = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC*)0x00000001411A3990; // glNamedProgramLocalParameterI4ivEXT
PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC* divagl_glNamedProgramLocalParameterI4uiEXT
    = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC*)0x00000001411A39A0; // glNamedProgramLocalParameterI4uiEXT
PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC* divagl_glNamedProgramLocalParameterI4uivEXT
    = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC*)0x00000001411A39A8; // glNamedProgramLocalParameterI4uivEXT
PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC* divagl_glNamedProgramLocalParameters4fvEXT
    = (PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC*)0x00000001411A3980; // glNamedProgramLocalParameters4fvEXT
PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC* divagl_glNamedProgramLocalParametersI4ivEXT
    = (PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC*)0x00000001411A3998; // glNamedProgramLocalParametersI4ivEXT
PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC* divagl_glNamedProgramLocalParametersI4uivEXT
    = (PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC*)0x00000001411A39B0; // glNamedProgramLocalParametersI4uivEXT
PFNGLNAMEDPROGRAMSTRINGEXTPROC* divagl_glNamedProgramStringEXT
    = (PFNGLNAMEDPROGRAMSTRINGEXTPROC*)0x00000001411A3938; // glNamedProgramStringEXT
PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC* divagl_glNamedRenderbufferStorageEXT
    = (PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC*)0x00000001411A3B60; // glNamedRenderbufferStorageEXT
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC* divagl_glNamedRenderbufferStorageMultisampleCoverageEXT
    = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC*)0x00000001411A3C50; // glNamedRenderbufferStorageMultisampleCoverageEXT
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC* divagl_glNamedRenderbufferStorageMultisampleEXT
    = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC*)0x00000001411A3C40; // glNamedRenderbufferStorageMultisampleEXT
PFNGLNORMAL3HNVPROC* divagl_glNormal3hNV
    = (PFNGLNORMAL3HNVPROC*)0x00000001411A5340; // glNormal3hNV
PFNGLNORMAL3HVNVPROC* divagl_glNormal3hvNV
    = (PFNGLNORMAL3HVNVPROC*)0x00000001411A5348; // glNormal3hvNV
PFNGLNORMALPOINTEREXTPROC* divagl_glNormalPointerEXT
    = (PFNGLNORMALPOINTEREXTPROC*)0x00000001411A4E90; // glNormalPointerEXT
PFNGLPIXELDATARANGENVPROC* divagl_glPixelDataRangeNV
    = (PFNGLPIXELDATARANGENVPROC*)0x00000001411A5470; // glPixelDataRangeNV
PFNGLPOINTPARAMETERFARBPROC* divagl_glPointParameterfARB
    = (PFNGLPOINTPARAMETERFARBPROC*)0x00000001411A4890; // glPointParameterfARB
PFNGLPOINTPARAMETERFEXTPROC* divagl_glPointParameterfEXT
    = (PFNGLPOINTPARAMETERFEXTPROC*)0x00000001411A4EB0; // glPointParameterfEXT
PFNGLPOINTPARAMETERFVARBPROC* divagl_glPointParameterfvARB
    = (PFNGLPOINTPARAMETERFVARBPROC*)0x00000001411A4898; // glPointParameterfvARB
PFNGLPOINTPARAMETERFVEXTPROC* divagl_glPointParameterfvEXT
    = (PFNGLPOINTPARAMETERFVEXTPROC*)0x00000001411A4EB8; // glPointParameterfvEXT
PFNGLPOINTPARAMETERINVPROC* divagl_glPointParameteriNV
    = (PFNGLPOINTPARAMETERINVPROC*)0x00000001411A52C0; // glPointParameteriNV
PFNGLPOINTPARAMETERIVPROC* divagl_glPointParameteriv
    = (PFNGLPOINTPARAMETERIVPROC*)0x00000001411A4090; // glPointParameteriv
PFNGLPOINTPARAMETERIVNVPROC* divagl_glPointParameterivNV
    = (PFNGLPOINTPARAMETERIVNVPROC*)0x00000001411A52C8; // glPointParameterivNV
PFNGLPRESENTFRAMEDUALFILLNVPROC* divagl_glPresentFrameDualFillNV
    = (PFNGLPRESENTFRAMEDUALFILLNVPROC*)0x00000001411A3608; // glPresentFrameDualFillNV
PFNGLPRESENTFRAMEKEYEDNVPROC* divagl_glPresentFrameKeyedNV
    = (PFNGLPRESENTFRAMEKEYEDNVPROC*)0x00000001411A3600; // glPresentFrameKeyedNV
PFNGLPRIMITIVERESTARTNVPROC* divagl_glPrimitiveRestartNV
    = (PFNGLPRIMITIVERESTARTNVPROC*)0x00000001411A5480; // glPrimitiveRestartNV
PFNGLPRIORITIZETEXTURESEXTPROC* divagl_glPrioritizeTexturesEXT
    = (PFNGLPRIORITIZETEXTURESEXTPROC*)0x00000001411A4E58; // glPrioritizeTexturesEXT
PFNGLPROGRAMBUFFERPARAMETERSIIVNVPROC* divagl_glProgramBufferParametersIivNV
    = (PFNGLPROGRAMBUFFERPARAMETERSIIVNVPROC*)0x00000001411A3510; // glProgramBufferParametersIivNV
PFNGLPROGRAMBUFFERPARAMETERSIUIVNVPROC* divagl_glProgramBufferParametersIuivNV
    = (PFNGLPROGRAMBUFFERPARAMETERSIUIVNVPROC*)0x00000001411A3518; // glProgramBufferParametersIuivNV
PFNGLPROGRAMENVPARAMETER4DARBPROC* divagl_glProgramEnvParameter4dARB
    = (PFNGLPROGRAMENVPARAMETER4DARBPROC*)0x00000001411A4A78; // glProgramEnvParameter4dARB
PFNGLPROGRAMENVPARAMETER4DVARBPROC* divagl_glProgramEnvParameter4dvARB
    = (PFNGLPROGRAMENVPARAMETER4DVARBPROC*)0x00000001411A4A80; // glProgramEnvParameter4dvARB
PFNGLPROGRAMENVPARAMETERI4INVPROC* divagl_glProgramEnvParameterI4iNV
    = (PFNGLPROGRAMENVPARAMETERI4INVPROC*)0x00000001411A5588; // glProgramEnvParameterI4iNV
PFNGLPROGRAMENVPARAMETERI4IVNVPROC* divagl_glProgramEnvParameterI4ivNV
    = (PFNGLPROGRAMENVPARAMETERI4IVNVPROC*)0x00000001411A5590; // glProgramEnvParameterI4ivNV
PFNGLPROGRAMENVPARAMETERI4UINVPROC* divagl_glProgramEnvParameterI4uiNV
    = (PFNGLPROGRAMENVPARAMETERI4UINVPROC*)0x00000001411A55A0; // glProgramEnvParameterI4uiNV
PFNGLPROGRAMENVPARAMETERI4UIVNVPROC* divagl_glProgramEnvParameterI4uivNV
    = (PFNGLPROGRAMENVPARAMETERI4UIVNVPROC*)0x00000001411A55A8; // glProgramEnvParameterI4uivNV
PFNGLPROGRAMENVPARAMETERSI4IVNVPROC* divagl_glProgramEnvParametersI4ivNV
    = (PFNGLPROGRAMENVPARAMETERSI4IVNVPROC*)0x00000001411A5598; // glProgramEnvParametersI4ivNV
PFNGLPROGRAMENVPARAMETERSI4UIVNVPROC* divagl_glProgramEnvParametersI4uivNV
    = (PFNGLPROGRAMENVPARAMETERSI4UIVNVPROC*)0x00000001411A55B0; // glProgramEnvParametersI4uivNV
PFNGLPROGRAMLOCALPARAMETER4DARBPROC* divagl_glProgramLocalParameter4dARB
    = (PFNGLPROGRAMLOCALPARAMETER4DARBPROC*)0x00000001411A4A98; // glProgramLocalParameter4dARB
PFNGLPROGRAMLOCALPARAMETER4DVARBPROC* divagl_glProgramLocalParameter4dvARB
    = (PFNGLPROGRAMLOCALPARAMETER4DVARBPROC*)0x00000001411A4AA0; // glProgramLocalParameter4dvARB
PFNGLPROGRAMLOCALPARAMETERI4INVPROC* divagl_glProgramLocalParameterI4iNV
    = (PFNGLPROGRAMLOCALPARAMETERI4INVPROC*)0x00000001411A5558; // glProgramLocalParameterI4iNV
PFNGLPROGRAMLOCALPARAMETERI4IVNVPROC* divagl_glProgramLocalParameterI4ivNV
    = (PFNGLPROGRAMLOCALPARAMETERI4IVNVPROC*)0x00000001411A5560; // glProgramLocalParameterI4ivNV
PFNGLPROGRAMLOCALPARAMETERI4UINVPROC* divagl_glProgramLocalParameterI4uiNV
    = (PFNGLPROGRAMLOCALPARAMETERI4UINVPROC*)0x00000001411A5570; // glProgramLocalParameterI4uiNV
PFNGLPROGRAMLOCALPARAMETERI4UIVNVPROC* divagl_glProgramLocalParameterI4uivNV
    = (PFNGLPROGRAMLOCALPARAMETERI4UIVNVPROC*)0x00000001411A5578; // glProgramLocalParameterI4uivNV
PFNGLPROGRAMLOCALPARAMETERSI4IVNVPROC* divagl_glProgramLocalParametersI4ivNV
    = (PFNGLPROGRAMLOCALPARAMETERSI4IVNVPROC*)0x00000001411A5568; // glProgramLocalParametersI4ivNV
PFNGLPROGRAMLOCALPARAMETERSI4UIVNVPROC* divagl_glProgramLocalParametersI4uivNV
    = (PFNGLPROGRAMLOCALPARAMETERSI4UIVNVPROC*)0x00000001411A5580; // glProgramLocalParametersI4uivNV
PFNGLPROGRAMNAMEDPARAMETER4DNVPROC* divagl_glProgramNamedParameter4dNV
    = (PFNGLPROGRAMNAMEDPARAMETER4DNVPROC*)0x00000001411A52E8; // glProgramNamedParameter4dNV
PFNGLPROGRAMNAMEDPARAMETER4DVNVPROC* divagl_glProgramNamedParameter4dvNV
    = (PFNGLPROGRAMNAMEDPARAMETER4DVNVPROC*)0x00000001411A52F8; // glProgramNamedParameter4dvNV
PFNGLPROGRAMNAMEDPARAMETER4FNVPROC* divagl_glProgramNamedParameter4fNV
    = (PFNGLPROGRAMNAMEDPARAMETER4FNVPROC*)0x00000001411A52E0; // glProgramNamedParameter4fNV
PFNGLPROGRAMNAMEDPARAMETER4FVNVPROC* divagl_glProgramNamedParameter4fvNV
    = (PFNGLPROGRAMNAMEDPARAMETER4FVNVPROC*)0x00000001411A52F0; // glProgramNamedParameter4fvNV
PFNGLPROGRAMPARAMETER4DNVPROC* divagl_glProgramParameter4dNV
    = (PFNGLPROGRAMPARAMETER4DNVPROC*)0x00000001411A5108; // glProgramParameter4dNV
PFNGLPROGRAMPARAMETER4DVNVPROC* divagl_glProgramParameter4dvNV
    = (PFNGLPROGRAMPARAMETER4DVNVPROC*)0x00000001411A5110; // glProgramParameter4dvNV
PFNGLPROGRAMPARAMETER4FNVPROC* divagl_glProgramParameter4fNV
    = (PFNGLPROGRAMPARAMETER4FNVPROC*)0x00000001411A5118; // glProgramParameter4fNV
PFNGLPROGRAMPARAMETER4FVNVPROC* divagl_glProgramParameter4fvNV
    = (PFNGLPROGRAMPARAMETER4FVNVPROC*)0x00000001411A5120; // glProgramParameter4fvNV
PFNGLPROGRAMPARAMETERIARBPROC* divagl_glProgramParameteriARB
    = (PFNGLPROGRAMPARAMETERIARBPROC*)0x00000001411A4DB8; // glProgramParameteriARB
PFNGLPROGRAMPARAMETERIEXTPROC* divagl_glProgramParameteriEXT
    = (PFNGLPROGRAMPARAMETERIEXTPROC*)0x00000001411A55F8; // glProgramParameteriEXT
PFNGLPROGRAMPARAMETERS4DVNVPROC* divagl_glProgramParameters4dvNV
    = (PFNGLPROGRAMPARAMETERS4DVNVPROC*)0x00000001411A5128; // glProgramParameters4dvNV
PFNGLPROGRAMPARAMETERS4FVNVPROC* divagl_glProgramParameters4fvNV
    = (PFNGLPROGRAMPARAMETERS4FVNVPROC*)0x00000001411A5130; // glProgramParameters4fvNV
PFNGLPROGRAMSTRINGARBPROC* divagl_glProgramStringARB
    = (PFNGLPROGRAMSTRINGARBPROC*)0x00000001411A4A58; // glProgramStringARB
PFNGLPROGRAMUNIFORM1FEXTPROC* divagl_glProgramUniform1fEXT
    = (PFNGLPROGRAMUNIFORM1FEXTPROC*)0x00000001411A3A08; // glProgramUniform1fEXT
PFNGLPROGRAMUNIFORM1FVEXTPROC* divagl_glProgramUniform1fvEXT
    = (PFNGLPROGRAMUNIFORM1FVEXTPROC*)0x00000001411A3A48; // glProgramUniform1fvEXT
PFNGLPROGRAMUNIFORM1IEXTPROC* divagl_glProgramUniform1iEXT
    = (PFNGLPROGRAMUNIFORM1IEXTPROC*)0x00000001411A3A28; // glProgramUniform1iEXT
PFNGLPROGRAMUNIFORM1IVEXTPROC* divagl_glProgramUniform1ivEXT
    = (PFNGLPROGRAMUNIFORM1IVEXTPROC*)0x00000001411A3A68; // glProgramUniform1ivEXT
PFNGLPROGRAMUNIFORM1UIEXTPROC* divagl_glProgramUniform1uiEXT
    = (PFNGLPROGRAMUNIFORM1UIEXTPROC*)0x00000001411A3AD0; // glProgramUniform1uiEXT
PFNGLPROGRAMUNIFORM1UIVEXTPROC* divagl_glProgramUniform1uivEXT
    = (PFNGLPROGRAMUNIFORM1UIVEXTPROC*)0x00000001411A3AF0; // glProgramUniform1uivEXT
PFNGLPROGRAMUNIFORM2FEXTPROC* divagl_glProgramUniform2fEXT
    = (PFNGLPROGRAMUNIFORM2FEXTPROC*)0x00000001411A3A10; // glProgramUniform2fEXT
PFNGLPROGRAMUNIFORM2FVEXTPROC* divagl_glProgramUniform2fvEXT
    = (PFNGLPROGRAMUNIFORM2FVEXTPROC*)0x00000001411A3A50; // glProgramUniform2fvEXT
PFNGLPROGRAMUNIFORM2IEXTPROC* divagl_glProgramUniform2iEXT
    = (PFNGLPROGRAMUNIFORM2IEXTPROC*)0x00000001411A3A30; // glProgramUniform2iEXT
PFNGLPROGRAMUNIFORM2IVEXTPROC* divagl_glProgramUniform2ivEXT
    = (PFNGLPROGRAMUNIFORM2IVEXTPROC*)0x00000001411A3A70; // glProgramUniform2ivEXT
PFNGLPROGRAMUNIFORM2UIEXTPROC* divagl_glProgramUniform2uiEXT
    = (PFNGLPROGRAMUNIFORM2UIEXTPROC*)0x00000001411A3AD8; // glProgramUniform2uiEXT
PFNGLPROGRAMUNIFORM2UIVEXTPROC* divagl_glProgramUniform2uivEXT
    = (PFNGLPROGRAMUNIFORM2UIVEXTPROC*)0x00000001411A3AF8; // glProgramUniform2uivEXT
PFNGLPROGRAMUNIFORM3FEXTPROC* divagl_glProgramUniform3fEXT
    = (PFNGLPROGRAMUNIFORM3FEXTPROC*)0x00000001411A3A18; // glProgramUniform3fEXT
PFNGLPROGRAMUNIFORM3FVEXTPROC* divagl_glProgramUniform3fvEXT
    = (PFNGLPROGRAMUNIFORM3FVEXTPROC*)0x00000001411A3A58; // glProgramUniform3fvEXT
PFNGLPROGRAMUNIFORM3IEXTPROC* divagl_glProgramUniform3iEXT
    = (PFNGLPROGRAMUNIFORM3IEXTPROC*)0x00000001411A3A38; // glProgramUniform3iEXT
PFNGLPROGRAMUNIFORM3IVEXTPROC* divagl_glProgramUniform3ivEXT
    = (PFNGLPROGRAMUNIFORM3IVEXTPROC*)0x00000001411A3A78; // glProgramUniform3ivEXT
PFNGLPROGRAMUNIFORM3UIEXTPROC* divagl_glProgramUniform3uiEXT
    = (PFNGLPROGRAMUNIFORM3UIEXTPROC*)0x00000001411A3AE0; // glProgramUniform3uiEXT
PFNGLPROGRAMUNIFORM3UIVEXTPROC* divagl_glProgramUniform3uivEXT
    = (PFNGLPROGRAMUNIFORM3UIVEXTPROC*)0x00000001411A3B00; // glProgramUniform3uivEXT
PFNGLPROGRAMUNIFORM4FEXTPROC* divagl_glProgramUniform4fEXT
    = (PFNGLPROGRAMUNIFORM4FEXTPROC*)0x00000001411A3A20; // glProgramUniform4fEXT
PFNGLPROGRAMUNIFORM4FVEXTPROC* divagl_glProgramUniform4fvEXT
    = (PFNGLPROGRAMUNIFORM4FVEXTPROC*)0x00000001411A3A60; // glProgramUniform4fvEXT
PFNGLPROGRAMUNIFORM4IEXTPROC* divagl_glProgramUniform4iEXT
    = (PFNGLPROGRAMUNIFORM4IEXTPROC*)0x00000001411A3A40; // glProgramUniform4iEXT
PFNGLPROGRAMUNIFORM4IVEXTPROC* divagl_glProgramUniform4ivEXT
    = (PFNGLPROGRAMUNIFORM4IVEXTPROC*)0x00000001411A3A80; // glProgramUniform4ivEXT
PFNGLPROGRAMUNIFORM4UIEXTPROC* divagl_glProgramUniform4uiEXT
    = (PFNGLPROGRAMUNIFORM4UIEXTPROC*)0x00000001411A3AE8; // glProgramUniform4uiEXT
PFNGLPROGRAMUNIFORM4UIVEXTPROC* divagl_glProgramUniform4uivEXT
    = (PFNGLPROGRAMUNIFORM4UIVEXTPROC*)0x00000001411A3B08; // glProgramUniform4uivEXT
PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC* divagl_glProgramUniformMatrix2fvEXT
    = (PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC*)0x00000001411A3A88; // glProgramUniformMatrix2fvEXT
PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC* divagl_glProgramUniformMatrix2x3fvEXT
    = (PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC*)0x00000001411A3AA0; // glProgramUniformMatrix2x3fvEXT
PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC* divagl_glProgramUniformMatrix2x4fvEXT
    = (PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC*)0x00000001411A3AB0; // glProgramUniformMatrix2x4fvEXT
PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC* divagl_glProgramUniformMatrix3fvEXT
    = (PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC*)0x00000001411A3A90; // glProgramUniformMatrix3fvEXT
PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC* divagl_glProgramUniformMatrix3x2fvEXT
    = (PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC*)0x00000001411A3AA8; // glProgramUniformMatrix3x2fvEXT
PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC* divagl_glProgramUniformMatrix3x4fvEXT
    = (PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC*)0x00000001411A3AC0; // glProgramUniformMatrix3x4fvEXT
PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC* divagl_glProgramUniformMatrix4fvEXT
    = (PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC*)0x00000001411A3A98; // glProgramUniformMatrix4fvEXT
PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC* divagl_glProgramUniformMatrix4x2fvEXT
    = (PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC*)0x00000001411A3AB8; // glProgramUniformMatrix4x2fvEXT
PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC* divagl_glProgramUniformMatrix4x3fvEXT
    = (PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC*)0x00000001411A3AC8; // glProgramUniformMatrix4x3fvEXT
PFNGLPROGRAMVERTEXLIMITNVPROC* divagl_glProgramVertexLimitNV
    = (PFNGLPROGRAMVERTEXLIMITNVPROC*)0x00000001411A55D8; // glProgramVertexLimitNV
PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC* divagl_glPushClientAttribDefaultEXT
    = (PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC*)0x00000001411A3638; // glPushClientAttribDefaultEXT
PFNGLQUERYCOUNTERPROC* divagl_glQueryCounter
    = (PFNGLQUERYCOUNTERPROC*)0x00000001411A3F30; // glQueryCounter
PFNGLRENDERBUFFERSTORAGEPROC* divagl_glRenderbufferStorage
    = (PFNGLRENDERBUFFERSTORAGEPROC*)0x00000001411A4D38; // glRenderbufferStorage
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC* divagl_glRenderbufferStorageMultisample
    = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC*)0x00000001411A4DA8; // glRenderbufferStorageMultisample
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC* divagl_glRenderbufferStorageMultisampleEXT
    = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC*)0x00000001411A5530; // glRenderbufferStorageMultisampleEXT
PFNGLREQUESTRESIDENTPROGRAMSNVPROC* divagl_glRequestResidentProgramsNV
    = (PFNGLREQUESTRESIDENTPROGRAMSNVPROC*)0x00000001411A5138; // glRequestResidentProgramsNV
PFNGLRESETHISTOGRAMPROC* divagl_glResetHistogram
    = (PFNGLRESETHISTOGRAMPROC*)0x00000001411A3D68; // glResetHistogram
PFNGLRESETMINMAXPROC* divagl_glResetMinmax
    = (PFNGLRESETMINMAXPROC*)0x00000001411A3D78; // glResetMinmax
PFNGLSAMPLECOVERAGEPROC* divagl_glSampleCoverage
    = (PFNGLSAMPLECOVERAGEPROC*)0x00000001411A3FF8; // glSampleCoverage
PFNGLSAMPLECOVERAGEARBPROC* divagl_glSampleCoverageARB
    = (PFNGLSAMPLECOVERAGEARBPROC*)0x00000001411A4850; // glSampleCoverageARB
PFNGLSAMPLEMASKINDEXEDNVPROC* divagl_glSampleMaskIndexedNV
    = (PFNGLSAMPLEMASKINDEXEDNVPROC*)0x00000001411A3CC0; // glSampleMaskIndexedNV
PFNGLSAMPLERPARAMETERFPROC* divagl_glSamplerParameterf
    = (PFNGLSAMPLERPARAMETERFPROC*)0x00000001411A3FC0; // glSamplerParameterf
PFNGLSAMPLERPARAMETERFVPROC* divagl_glSamplerParameterfv
    = (PFNGLSAMPLERPARAMETERFVPROC*)0x00000001411A3FD0; // glSamplerParameterfv
PFNGLSAMPLERPARAMETERIPROC* divagl_glSamplerParameteri
    = (PFNGLSAMPLERPARAMETERIPROC*)0x00000001411A3FB0; // glSamplerParameteri
PFNGLSECONDARYCOLOR3BPROC* divagl_glSecondaryColor3b
    = (PFNGLSECONDARYCOLOR3BPROC*)0x00000001411A4098; // glSecondaryColor3b
PFNGLSECONDARYCOLOR3BEXTPROC* divagl_glSecondaryColor3bEXT
    = (PFNGLSECONDARYCOLOR3BEXTPROC*)0x00000001411A4F00; // glSecondaryColor3bEXT
PFNGLSECONDARYCOLOR3BVPROC* divagl_glSecondaryColor3bv
    = (PFNGLSECONDARYCOLOR3BVPROC*)0x00000001411A40A0; // glSecondaryColor3bv
PFNGLSECONDARYCOLOR3BVEXTPROC* divagl_glSecondaryColor3bvEXT
    = (PFNGLSECONDARYCOLOR3BVEXTPROC*)0x00000001411A4F08; // glSecondaryColor3bvEXT
PFNGLSECONDARYCOLOR3DPROC* divagl_glSecondaryColor3d
    = (PFNGLSECONDARYCOLOR3DPROC*)0x00000001411A40A8; // glSecondaryColor3d
PFNGLSECONDARYCOLOR3DEXTPROC* divagl_glSecondaryColor3dEXT
    = (PFNGLSECONDARYCOLOR3DEXTPROC*)0x00000001411A4F10; // glSecondaryColor3dEXT
PFNGLSECONDARYCOLOR3DVPROC* divagl_glSecondaryColor3dv
    = (PFNGLSECONDARYCOLOR3DVPROC*)0x00000001411A40B0; // glSecondaryColor3dv
PFNGLSECONDARYCOLOR3DVEXTPROC* divagl_glSecondaryColor3dvEXT
    = (PFNGLSECONDARYCOLOR3DVEXTPROC*)0x00000001411A4F18; // glSecondaryColor3dvEXT
PFNGLSECONDARYCOLOR3FPROC* divagl_glSecondaryColor3f
    = (PFNGLSECONDARYCOLOR3FPROC*)0x00000001411A40B8; // glSecondaryColor3f
PFNGLSECONDARYCOLOR3FEXTPROC* divagl_glSecondaryColor3fEXT
    = (PFNGLSECONDARYCOLOR3FEXTPROC*)0x00000001411A4F20; // glSecondaryColor3fEXT
PFNGLSECONDARYCOLOR3FVPROC* divagl_glSecondaryColor3fv
    = (PFNGLSECONDARYCOLOR3FVPROC*)0x00000001411A40C0; // glSecondaryColor3fv
PFNGLSECONDARYCOLOR3FVEXTPROC* divagl_glSecondaryColor3fvEXT
    = (PFNGLSECONDARYCOLOR3FVEXTPROC*)0x00000001411A4F28; // glSecondaryColor3fvEXT
PFNGLSECONDARYCOLOR3HNVPROC* divagl_glSecondaryColor3hNV
    = (PFNGLSECONDARYCOLOR3HNVPROC*)0x00000001411A5400; // glSecondaryColor3hNV
PFNGLSECONDARYCOLOR3HVNVPROC* divagl_glSecondaryColor3hvNV
    = (PFNGLSECONDARYCOLOR3HVNVPROC*)0x00000001411A5408; // glSecondaryColor3hvNV
PFNGLSECONDARYCOLOR3IPROC* divagl_glSecondaryColor3i
    = (PFNGLSECONDARYCOLOR3IPROC*)0x00000001411A40C8; // glSecondaryColor3i
PFNGLSECONDARYCOLOR3IEXTPROC* divagl_glSecondaryColor3iEXT
    = (PFNGLSECONDARYCOLOR3IEXTPROC*)0x00000001411A4F30; // glSecondaryColor3iEXT
PFNGLSECONDARYCOLOR3IVPROC* divagl_glSecondaryColor3iv
    = (PFNGLSECONDARYCOLOR3IVPROC*)0x00000001411A40D0; // glSecondaryColor3iv
PFNGLSECONDARYCOLOR3IVEXTPROC* divagl_glSecondaryColor3ivEXT
    = (PFNGLSECONDARYCOLOR3IVEXTPROC*)0x00000001411A4F38; // glSecondaryColor3ivEXT
PFNGLSECONDARYCOLOR3SPROC* divagl_glSecondaryColor3s
    = (PFNGLSECONDARYCOLOR3SPROC*)0x00000001411A40D8; // glSecondaryColor3s
PFNGLSECONDARYCOLOR3SEXTPROC* divagl_glSecondaryColor3sEXT
    = (PFNGLSECONDARYCOLOR3SEXTPROC*)0x00000001411A4F40; // glSecondaryColor3sEXT
PFNGLSECONDARYCOLOR3SVPROC* divagl_glSecondaryColor3sv
    = (PFNGLSECONDARYCOLOR3SVPROC*)0x00000001411A40E0; // glSecondaryColor3sv
PFNGLSECONDARYCOLOR3SVEXTPROC* divagl_glSecondaryColor3svEXT
    = (PFNGLSECONDARYCOLOR3SVEXTPROC*)0x00000001411A4F48; // glSecondaryColor3svEXT
PFNGLSECONDARYCOLOR3UBPROC* divagl_glSecondaryColor3ub
    = (PFNGLSECONDARYCOLOR3UBPROC*)0x00000001411A40E8; // glSecondaryColor3ub
PFNGLSECONDARYCOLOR3UBEXTPROC* divagl_glSecondaryColor3ubEXT
    = (PFNGLSECONDARYCOLOR3UBEXTPROC*)0x00000001411A4F50; // glSecondaryColor3ubEXT
PFNGLSECONDARYCOLOR3UBVPROC* divagl_glSecondaryColor3ubv
    = (PFNGLSECONDARYCOLOR3UBVPROC*)0x00000001411A40F0; // glSecondaryColor3ubv
PFNGLSECONDARYCOLOR3UBVEXTPROC* divagl_glSecondaryColor3ubvEXT
    = (PFNGLSECONDARYCOLOR3UBVEXTPROC*)0x00000001411A4F58; // glSecondaryColor3ubvEXT
PFNGLSECONDARYCOLOR3UIPROC* divagl_glSecondaryColor3ui
    = (PFNGLSECONDARYCOLOR3UIPROC*)0x00000001411A40F8; // glSecondaryColor3ui
PFNGLSECONDARYCOLOR3UIEXTPROC* divagl_glSecondaryColor3uiEXT
    = (PFNGLSECONDARYCOLOR3UIEXTPROC*)0x00000001411A4F60; // glSecondaryColor3uiEXT
PFNGLSECONDARYCOLOR3UIVPROC* divagl_glSecondaryColor3uiv
    = (PFNGLSECONDARYCOLOR3UIVPROC*)0x00000001411A4100; // glSecondaryColor3uiv
PFNGLSECONDARYCOLOR3UIVEXTPROC* divagl_glSecondaryColor3uivEXT
    = (PFNGLSECONDARYCOLOR3UIVEXTPROC*)0x00000001411A4F68; // glSecondaryColor3uivEXT
PFNGLSECONDARYCOLOR3USPROC* divagl_glSecondaryColor3us
    = (PFNGLSECONDARYCOLOR3USPROC*)0x00000001411A4108; // glSecondaryColor3us
PFNGLSECONDARYCOLOR3USEXTPROC* divagl_glSecondaryColor3usEXT
    = (PFNGLSECONDARYCOLOR3USEXTPROC*)0x00000001411A4F70; // glSecondaryColor3usEXT
PFNGLSECONDARYCOLOR3USVPROC* divagl_glSecondaryColor3usv
    = (PFNGLSECONDARYCOLOR3USVPROC*)0x00000001411A4110; // glSecondaryColor3usv
PFNGLSECONDARYCOLOR3USVEXTPROC* divagl_glSecondaryColor3usvEXT
    = (PFNGLSECONDARYCOLOR3USVEXTPROC*)0x00000001411A4F78; // glSecondaryColor3usvEXT
PFNGLSECONDARYCOLORPOINTERPROC* divagl_glSecondaryColorPointer
    = (PFNGLSECONDARYCOLORPOINTERPROC*)0x00000001411A4118; // glSecondaryColorPointer
PFNGLSECONDARYCOLORPOINTEREXTPROC* divagl_glSecondaryColorPointerEXT
    = (PFNGLSECONDARYCOLORPOINTEREXTPROC*)0x00000001411A4F80; // glSecondaryColorPointerEXT
PFNGLSEPARABLEFILTER2DPROC* divagl_glSeparableFilter2D
    = (PFNGLSEPARABLEFILTER2DPROC*)0x00000001411A3CD8; // glSeparableFilter2D
PFNGLSETFENCENVPROC* divagl_glSetFenceNV
    = (PFNGLSETFENCENVPROC*)0x00000001411A5070; // glSetFenceNV
PFNGLSHADERSOURCEPROC* divagl_glShaderSource
    = (PFNGLSHADERSOURCEPROC*)0x00000001411A4348; // glShaderSource
PFNGLSHADERSOURCEARBPROC* divagl_glShaderSourceARB
    = (PFNGLSHADERSOURCEARBPROC*)0x00000001411A4BC8; // glShaderSourceARB
PFNGLSTENCILFUNCSEPARATEPROC* divagl_glStencilFuncSeparate
    = (PFNGLSTENCILFUNCSEPARATEPROC*)0x00000001411A4250; // glStencilFuncSeparate
PFNGLSTENCILMASKSEPARATEPROC* divagl_glStencilMaskSeparate
    = (PFNGLSTENCILMASKSEPARATEPROC*)0x00000001411A4258; // glStencilMaskSeparate
PFNGLSTENCILOPSEPARATEPROC* divagl_glStencilOpSeparate
    = (PFNGLSTENCILOPSEPARATEPROC*)0x00000001411A4248; // glStencilOpSeparate
PFNGLTESTFENCENVPROC* divagl_glTestFenceNV
    = (PFNGLTESTFENCENVPROC*)0x00000001411A5058; // glTestFenceNV
PFNGLTEXBUFFERARBPROC* divagl_glTexBufferARB
    = (PFNGLTEXBUFFERARBPROC*)0x00000001411A4DE8; // glTexBufferARB
PFNGLTEXBUFFEREXTPROC* divagl_glTexBufferEXT
    = (PFNGLTEXBUFFEREXTPROC*)0x00000001411A34E0; // glTexBufferEXT
PFNGLTEXCOORD1HNVPROC* divagl_glTexCoord1hNV
    = (PFNGLTEXCOORD1HNVPROC*)0x00000001411A5370; // glTexCoord1hNV
PFNGLTEXCOORD1HVNVPROC* divagl_glTexCoord1hvNV
    = (PFNGLTEXCOORD1HVNVPROC*)0x00000001411A5378; // glTexCoord1hvNV
PFNGLTEXCOORD2HNVPROC* divagl_glTexCoord2hNV
    = (PFNGLTEXCOORD2HNVPROC*)0x00000001411A5380; // glTexCoord2hNV
PFNGLTEXCOORD2HVNVPROC* divagl_glTexCoord2hvNV
    = (PFNGLTEXCOORD2HVNVPROC*)0x00000001411A5388; // glTexCoord2hvNV
PFNGLTEXCOORD3HNVPROC* divagl_glTexCoord3hNV
    = (PFNGLTEXCOORD3HNVPROC*)0x00000001411A5390; // glTexCoord3hNV
PFNGLTEXCOORD3HVNVPROC* divagl_glTexCoord3hvNV
    = (PFNGLTEXCOORD3HVNVPROC*)0x00000001411A5398; // glTexCoord3hvNV
PFNGLTEXCOORD4HNVPROC* divagl_glTexCoord4hNV
    = (PFNGLTEXCOORD4HNVPROC*)0x00000001411A53A0; // glTexCoord4hNV
PFNGLTEXCOORD4HVNVPROC* divagl_glTexCoord4hvNV
    = (PFNGLTEXCOORD4HVNVPROC*)0x00000001411A53A8; // glTexCoord4hvNV
PFNGLTEXCOORDPOINTEREXTPROC* divagl_glTexCoordPointerEXT
    = (PFNGLTEXCOORDPOINTEREXTPROC*)0x00000001411A4E98; // glTexCoordPointerEXT
PFNGLTEXIMAGE3DPROC* divagl_glTexImage3D
    = (PFNGLTEXIMAGE3DPROC*)0x00000001411A3D88; // glTexImage3D
PFNGLTEXIMAGE3DEXTPROC* divagl_glTexImage3DEXT
    = (PFNGLTEXIMAGE3DEXTPROC*)0x00000001411A4E18; // glTexImage3DEXT
PFNGLTEXPARAMETERIIVPROC* divagl_glTexParameterIiv
    = (PFNGLTEXPARAMETERIIVPROC*)0x00000001411A46D0; // glTexParameterIiv
PFNGLTEXPARAMETERIIVEXTPROC* divagl_glTexParameterIivEXT
    = (PFNGLTEXPARAMETERIIVEXTPROC*)0x00000001411A35C0; // glTexParameterIivEXT
PFNGLTEXPARAMETERIUIVPROC* divagl_glTexParameterIuiv
    = (PFNGLTEXPARAMETERIUIVPROC*)0x00000001411A46D8; // glTexParameterIuiv
PFNGLTEXPARAMETERIUIVEXTPROC* divagl_glTexParameterIuivEXT
    = (PFNGLTEXPARAMETERIUIVEXTPROC*)0x00000001411A35C8; // glTexParameterIuivEXT
PFNGLTEXRENDERBUFFERNVPROC* divagl_glTexRenderbufferNV
    = (PFNGLTEXRENDERBUFFERNVPROC*)0x00000001411A3CD0; // glTexRenderbufferNV
PFNGLTEXSTORAGE2DPROC* divagl_glTexStorage2D
    = (PFNGLTEXSTORAGE2DPROC*)0x00000001411A3F60; // glTexStorage2D
PFNGLTEXSUBIMAGE3DPROC* divagl_glTexSubImage3D
    = (PFNGLTEXSUBIMAGE3DPROC*)0x00000001411A3D98; // glTexSubImage3D
PFNGLTEXSUBIMAGE3DEXTPROC* divagl_glTexSubImage3DEXT
    = (PFNGLTEXSUBIMAGE3DEXTPROC*)0x00000001411A4E20; // glTexSubImage3DEXT
PFNGLTEXTUREBARRIERNVPROC* divagl_glTextureBarrierNV
    = (PFNGLTEXTUREBARRIERNVPROC*)0x00000001411A3CE0; // glTextureBarrierNV
PFNGLTEXTUREBUFFEREXTPROC* divagl_glTextureBufferEXT
    = (PFNGLTEXTUREBUFFEREXTPROC*)0x00000001411A3B48; // glTextureBufferEXT
PFNGLTEXTUREIMAGE1DEXTPROC* divagl_glTextureImage1DEXT
    = (PFNGLTEXTUREIMAGE1DEXTPROC*)0x00000001411A36F8; // glTextureImage1DEXT
PFNGLTEXTUREIMAGE2DEXTPROC* divagl_glTextureImage2DEXT
    = (PFNGLTEXTUREIMAGE2DEXTPROC*)0x00000001411A3700; // glTextureImage2DEXT
PFNGLTEXTUREIMAGE3DEXTPROC* divagl_glTextureImage3DEXT
    = (PFNGLTEXTUREIMAGE3DEXTPROC*)0x00000001411A3760; // glTextureImage3DEXT
PFNGLTEXTUREPARAMETERFEXTPROC* divagl_glTextureParameterfEXT
    = (PFNGLTEXTUREPARAMETERFEXTPROC*)0x00000001411A36D8; // glTextureParameterfEXT
PFNGLTEXTUREPARAMETERFVEXTPROC* divagl_glTextureParameterfvEXT
    = (PFNGLTEXTUREPARAMETERFVEXTPROC*)0x00000001411A36E0; // glTextureParameterfvEXT
PFNGLTEXTUREPARAMETERIEXTPROC* divagl_glTextureParameteriEXT
    = (PFNGLTEXTUREPARAMETERIEXTPROC*)0x00000001411A36E8; // glTextureParameteriEXT
PFNGLTEXTUREPARAMETERIIVEXTPROC* divagl_glTextureParameterIivEXT
    = (PFNGLTEXTUREPARAMETERIIVEXTPROC*)0x00000001411A39C8; // glTextureParameterIivEXT
PFNGLTEXTUREPARAMETERIUIVEXTPROC* divagl_glTextureParameterIuivEXT
    = (PFNGLTEXTUREPARAMETERIUIVEXTPROC*)0x00000001411A39D0; // glTextureParameterIuivEXT
PFNGLTEXTUREPARAMETERIVEXTPROC* divagl_glTextureParameterivEXT
    = (PFNGLTEXTUREPARAMETERIVEXTPROC*)0x00000001411A36F0; // glTextureParameterivEXT
PFNGLTEXTURERENDERBUFFEREXTPROC* divagl_glTextureRenderbufferEXT
    = (PFNGLTEXTURERENDERBUFFEREXTPROC*)0x00000001411A3C90; // glTextureRenderbufferEXT
PFNGLTEXTURESTORAGE2DEXTPROC* divagl_glTextureStorage2DEXT
    = (PFNGLTEXTURESTORAGE2DEXTPROC*)0x00000001411A3F70; // glTextureStorage2DEXT
PFNGLTEXTURESUBIMAGE1DEXTPROC* divagl_glTextureSubImage1DEXT
    = (PFNGLTEXTURESUBIMAGE1DEXTPROC*)0x00000001411A3708; // glTextureSubImage1DEXT
PFNGLTEXTURESUBIMAGE2DEXTPROC* divagl_glTextureSubImage2DEXT
    = (PFNGLTEXTURESUBIMAGE2DEXTPROC*)0x00000001411A3710; // glTextureSubImage2DEXT
PFNGLTEXTURESUBIMAGE3DEXTPROC* divagl_glTextureSubImage3DEXT
    = (PFNGLTEXTURESUBIMAGE3DEXTPROC*)0x00000001411A3768; // glTextureSubImage3DEXT
PFNGLTRACKMATRIXNVPROC* divagl_glTrackMatrixNV
    = (PFNGLTRACKMATRIXNVPROC*)0x00000001411A5140; // glTrackMatrixNV
PFNGLTRANSFORMFEEDBACKATTRIBSNVPROC* divagl_glTransformFeedbackAttribsNV
    = (PFNGLTRANSFORMFEEDBACKATTRIBSNVPROC*)0x00000001411A3560; // glTransformFeedbackAttribsNV
PFNGLTRANSFORMFEEDBACKVARYINGSPROC* divagl_glTransformFeedbackVaryings
    = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC*)0x00000001411A45A0; // glTransformFeedbackVaryings
PFNGLTRANSFORMFEEDBACKVARYINGSNVPROC* divagl_glTransformFeedbackVaryingsNV
    = (PFNGLTRANSFORMFEEDBACKVARYINGSNVPROC*)0x00000001411A3580; // glTransformFeedbackVaryingsNV
PFNGLUNIFORM1FPROC* divagl_glUniform1f
    = (PFNGLUNIFORM1FPROC*)0x00000001411A4358; // glUniform1f
PFNGLUNIFORM1FARBPROC* divagl_glUniform1fARB
    = (PFNGLUNIFORM1FARBPROC*)0x00000001411A4C00; // glUniform1fARB
PFNGLUNIFORM1FVPROC* divagl_glUniform1fv
    = (PFNGLUNIFORM1FVPROC*)0x00000001411A4398; // glUniform1fv
PFNGLUNIFORM1FVARBPROC* divagl_glUniform1fvARB
    = (PFNGLUNIFORM1FVARBPROC*)0x00000001411A4C40; // glUniform1fvARB
PFNGLUNIFORM1IPROC* divagl_glUniform1i
    = (PFNGLUNIFORM1IPROC*)0x00000001411A4378; // glUniform1i
PFNGLUNIFORM1IARBPROC* divagl_glUniform1iARB
    = (PFNGLUNIFORM1IARBPROC*)0x00000001411A4C20; // glUniform1iARB
PFNGLUNIFORM1IVPROC* divagl_glUniform1iv
    = (PFNGLUNIFORM1IVPROC*)0x00000001411A43B8; // glUniform1iv
PFNGLUNIFORM1IVARBPROC* divagl_glUniform1ivARB
    = (PFNGLUNIFORM1IVARBPROC*)0x00000001411A4C60; // glUniform1ivARB
PFNGLUNIFORM1UIPROC* divagl_glUniform1ui
    = (PFNGLUNIFORM1UIPROC*)0x00000001411A4690; // glUniform1ui
PFNGLUNIFORM1UIEXTPROC* divagl_glUniform1uiEXT
    = (PFNGLUNIFORM1UIEXTPROC*)0x00000001411A56D0; // glUniform1uiEXT
PFNGLUNIFORM1UIVPROC* divagl_glUniform1uiv
    = (PFNGLUNIFORM1UIVPROC*)0x00000001411A46B0; // glUniform1uiv
PFNGLUNIFORM1UIVEXTPROC* divagl_glUniform1uivEXT
    = (PFNGLUNIFORM1UIVEXTPROC*)0x00000001411A56F0; // glUniform1uivEXT
PFNGLUNIFORM2FPROC* divagl_glUniform2f
    = (PFNGLUNIFORM2FPROC*)0x00000001411A4360; // glUniform2f
PFNGLUNIFORM2FARBPROC* divagl_glUniform2fARB
    = (PFNGLUNIFORM2FARBPROC*)0x00000001411A4C08; // glUniform2fARB
PFNGLUNIFORM2FVPROC* divagl_glUniform2fv
    = (PFNGLUNIFORM2FVPROC*)0x00000001411A43A0; // glUniform2fv
PFNGLUNIFORM2FVARBPROC* divagl_glUniform2fvARB
    = (PFNGLUNIFORM2FVARBPROC*)0x00000001411A4C48; // glUniform2fvARB
PFNGLUNIFORM2IPROC* divagl_glUniform2i
    = (PFNGLUNIFORM2IPROC*)0x00000001411A4380; // glUniform2i
PFNGLUNIFORM2IARBPROC* divagl_glUniform2iARB
    = (PFNGLUNIFORM2IARBPROC*)0x00000001411A4C28; // glUniform2iARB
PFNGLUNIFORM2IVPROC* divagl_glUniform2iv
    = (PFNGLUNIFORM2IVPROC*)0x00000001411A43C0; // glUniform2iv
PFNGLUNIFORM2IVARBPROC* divagl_glUniform2ivARB
    = (PFNGLUNIFORM2IVARBPROC*)0x00000001411A4C68; // glUniform2ivARB
PFNGLUNIFORM2UIPROC* divagl_glUniform2ui
    = (PFNGLUNIFORM2UIPROC*)0x00000001411A4698; // glUniform2ui
PFNGLUNIFORM2UIEXTPROC* divagl_glUniform2uiEXT
    = (PFNGLUNIFORM2UIEXTPROC*)0x00000001411A56D8; // glUniform2uiEXT
PFNGLUNIFORM2UIVPROC* divagl_glUniform2uiv
    = (PFNGLUNIFORM2UIVPROC*)0x00000001411A46B8; // glUniform2uiv
PFNGLUNIFORM2UIVEXTPROC* divagl_glUniform2uivEXT
    = (PFNGLUNIFORM2UIVEXTPROC*)0x00000001411A56F8; // glUniform2uivEXT
PFNGLUNIFORM3FPROC* divagl_glUniform3f
    = (PFNGLUNIFORM3FPROC*)0x00000001411A4368; // glUniform3f
PFNGLUNIFORM3FARBPROC* divagl_glUniform3fARB
    = (PFNGLUNIFORM3FARBPROC*)0x00000001411A4C10; // glUniform3fARB
PFNGLUNIFORM3FVPROC* divagl_glUniform3fv
    = (PFNGLUNIFORM3FVPROC*)0x00000001411A43A8; // glUniform3fv
PFNGLUNIFORM3FVARBPROC* divagl_glUniform3fvARB
    = (PFNGLUNIFORM3FVARBPROC*)0x00000001411A4C50; // glUniform3fvARB
PFNGLUNIFORM3IPROC* divagl_glUniform3i
    = (PFNGLUNIFORM3IPROC*)0x00000001411A4388; // glUniform3i
PFNGLUNIFORM3IARBPROC* divagl_glUniform3iARB
    = (PFNGLUNIFORM3IARBPROC*)0x00000001411A4C30; // glUniform3iARB
PFNGLUNIFORM3IVPROC* divagl_glUniform3iv
    = (PFNGLUNIFORM3IVPROC*)0x00000001411A43C8; // glUniform3iv
PFNGLUNIFORM3IVARBPROC* divagl_glUniform3ivARB
    = (PFNGLUNIFORM3IVARBPROC*)0x00000001411A4C70; // glUniform3ivARB
PFNGLUNIFORM3UIPROC* divagl_glUniform3ui
    = (PFNGLUNIFORM3UIPROC*)0x00000001411A46A0; // glUniform3ui
PFNGLUNIFORM3UIEXTPROC* divagl_glUniform3uiEXT
    = (PFNGLUNIFORM3UIEXTPROC*)0x00000001411A56E0; // glUniform3uiEXT
PFNGLUNIFORM3UIVPROC* divagl_glUniform3uiv
    = (PFNGLUNIFORM3UIVPROC*)0x00000001411A46C0; // glUniform3uiv
PFNGLUNIFORM3UIVEXTPROC* divagl_glUniform3uivEXT
    = (PFNGLUNIFORM3UIVEXTPROC*)0x00000001411A5700; // glUniform3uivEXT
PFNGLUNIFORM4FPROC* divagl_glUniform4f
    = (PFNGLUNIFORM4FPROC*)0x00000001411A4370; // glUniform4f
PFNGLUNIFORM4FARBPROC* divagl_glUniform4fARB
    = (PFNGLUNIFORM4FARBPROC*)0x00000001411A4C18; // glUniform4fARB
PFNGLUNIFORM4FVPROC* divagl_glUniform4fv
    = (PFNGLUNIFORM4FVPROC*)0x00000001411A43B0; // glUniform4fv
PFNGLUNIFORM4FVARBPROC* divagl_glUniform4fvARB
    = (PFNGLUNIFORM4FVARBPROC*)0x00000001411A4C58; // glUniform4fvARB
PFNGLUNIFORM4IPROC* divagl_glUniform4i
    = (PFNGLUNIFORM4IPROC*)0x00000001411A4390; // glUniform4i
PFNGLUNIFORM4IARBPROC* divagl_glUniform4iARB
    = (PFNGLUNIFORM4IARBPROC*)0x00000001411A4C38; // glUniform4iARB
PFNGLUNIFORM4IVPROC* divagl_glUniform4iv
    = (PFNGLUNIFORM4IVPROC*)0x00000001411A43D0; // glUniform4iv
PFNGLUNIFORM4IVARBPROC* divagl_glUniform4ivARB
    = (PFNGLUNIFORM4IVARBPROC*)0x00000001411A4C78; // glUniform4ivARB
PFNGLUNIFORM4UIPROC* divagl_glUniform4ui
    = (PFNGLUNIFORM4UIPROC*)0x00000001411A46A8; // glUniform4ui
PFNGLUNIFORM4UIEXTPROC* divagl_glUniform4uiEXT
    = (PFNGLUNIFORM4UIEXTPROC*)0x00000001411A56E8; // glUniform4uiEXT
PFNGLUNIFORM4UIVPROC* divagl_glUniform4uiv
    = (PFNGLUNIFORM4UIVPROC*)0x00000001411A46C8; // glUniform4uiv
PFNGLUNIFORM4UIVEXTPROC* divagl_glUniform4uivEXT
    = (PFNGLUNIFORM4UIVEXTPROC*)0x00000001411A5708; // glUniform4uivEXT
PFNGLUNIFORMBUFFEREXTPROC* divagl_glUniformBufferEXT
    = (PFNGLUNIFORMBUFFEREXTPROC*)0x00000001411A35A8; // glUniformBufferEXT
PFNGLUNIFORMMATRIX2FVPROC* divagl_glUniformMatrix2fv
    = (PFNGLUNIFORMMATRIX2FVPROC*)0x00000001411A43D8; // glUniformMatrix2fv
PFNGLUNIFORMMATRIX2FVARBPROC* divagl_glUniformMatrix2fvARB
    = (PFNGLUNIFORMMATRIX2FVARBPROC*)0x00000001411A4C80; // glUniformMatrix2fvARB
PFNGLUNIFORMMATRIX2X3FVPROC* divagl_glUniformMatrix2x3fv
    = (PFNGLUNIFORMMATRIX2X3FVPROC*)0x00000001411A4520; // glUniformMatrix2x3fv
PFNGLUNIFORMMATRIX2X4FVPROC* divagl_glUniformMatrix2x4fv
    = (PFNGLUNIFORMMATRIX2X4FVPROC*)0x00000001411A4530; // glUniformMatrix2x4fv
PFNGLUNIFORMMATRIX3FVPROC* divagl_glUniformMatrix3fv
    = (PFNGLUNIFORMMATRIX3FVPROC*)0x00000001411A43E0; // glUniformMatrix3fv
PFNGLUNIFORMMATRIX3FVARBPROC* divagl_glUniformMatrix3fvARB
    = (PFNGLUNIFORMMATRIX3FVARBPROC*)0x00000001411A4C88; // glUniformMatrix3fvARB
PFNGLUNIFORMMATRIX3X2FVPROC* divagl_glUniformMatrix3x2fv
    = (PFNGLUNIFORMMATRIX3X2FVPROC*)0x00000001411A4528; // glUniformMatrix3x2fv
PFNGLUNIFORMMATRIX3X4FVPROC* divagl_glUniformMatrix3x4fv
    = (PFNGLUNIFORMMATRIX3X4FVPROC*)0x00000001411A4540; // glUniformMatrix3x4fv
PFNGLUNIFORMMATRIX4FVPROC* divagl_glUniformMatrix4fv
    = (PFNGLUNIFORMMATRIX4FVPROC*)0x00000001411A43E8; // glUniformMatrix4fv
PFNGLUNIFORMMATRIX4FVARBPROC* divagl_glUniformMatrix4fvARB
    = (PFNGLUNIFORMMATRIX4FVARBPROC*)0x00000001411A4C90; // glUniformMatrix4fvARB
PFNGLUNIFORMMATRIX4X2FVPROC* divagl_glUniformMatrix4x2fv
    = (PFNGLUNIFORMMATRIX4X2FVPROC*)0x00000001411A4538; // glUniformMatrix4x2fv
PFNGLUNIFORMMATRIX4X3FVPROC* divagl_glUniformMatrix4x3fv
    = (PFNGLUNIFORMMATRIX4X3FVPROC*)0x00000001411A4548; // glUniformMatrix4x3fv
PFNGLUNLOCKARRAYSEXTPROC* divagl_glUnlockArraysEXT
    = (PFNGLUNLOCKARRAYSEXTPROC*)0x00000001411A4EF0; // glUnlockArraysEXT
PFNGLUNMAPBUFFERPROC* divagl_glUnmapBuffer
    = (PFNGLUNMAPBUFFERPROC*)0x00000001411A4220; // glUnmapBuffer
PFNGLUNMAPBUFFERARBPROC* divagl_glUnmapBufferARB
    = (PFNGLUNMAPBUFFERARBPROC*)0x00000001411A4B50; // glUnmapBufferARB
PFNGLUSEPROGRAMPROC* divagl_glUseProgram
    = (PFNGLUSEPROGRAMPROC*)0x00000001411A4350; // glUseProgram
PFNGLUSEPROGRAMOBJECTARBPROC* divagl_glUseProgramObjectARB
    = (PFNGLUSEPROGRAMOBJECTARBPROC*)0x00000001411A4BF0; // glUseProgramObjectARB
PFNGLVALIDATEPROGRAMPROC* divagl_glValidateProgram
    = (PFNGLVALIDATEPROGRAMPROC*)0x00000001411A43F0; // glValidateProgram
PFNGLVALIDATEPROGRAMARBPROC* divagl_glValidateProgramARB
    = (PFNGLVALIDATEPROGRAMARBPROC*)0x00000001411A4BF8; // glValidateProgramARB
PFNGLVERTEX2HNVPROC* divagl_glVertex2hNV
    = (PFNGLVERTEX2HNVPROC*)0x00000001411A5310; // glVertex2hNV
PFNGLVERTEX2HVNVPROC* divagl_glVertex2hvNV
    = (PFNGLVERTEX2HVNVPROC*)0x00000001411A5318; // glVertex2hvNV
PFNGLVERTEX3HNVPROC* divagl_glVertex3hNV
    = (PFNGLVERTEX3HNVPROC*)0x00000001411A5320; // glVertex3hNV
PFNGLVERTEX3HVNVPROC* divagl_glVertex3hvNV
    = (PFNGLVERTEX3HVNVPROC*)0x00000001411A5328; // glVertex3hvNV
PFNGLVERTEX4HNVPROC* divagl_glVertex4hNV
    = (PFNGLVERTEX4HNVPROC*)0x00000001411A5330; // glVertex4hNV
PFNGLVERTEX4HVNVPROC* divagl_glVertex4hvNV
    = (PFNGLVERTEX4HVNVPROC*)0x00000001411A5338; // glVertex4hvNV
PFNGLVERTEXARRAYRANGENVPROC* divagl_glVertexArrayRangeNV
    = (PFNGLVERTEXARRAYRANGENVPROC*)0x00000001411A4FD0; // glVertexArrayRangeNV
PFNGLVERTEXATTRIB1DPROC* divagl_glVertexAttrib1d
    = (PFNGLVERTEXATTRIB1DPROC*)0x00000001411A43F8; // glVertexAttrib1d
PFNGLVERTEXATTRIB1DARBPROC* divagl_glVertexAttrib1dARB
    = (PFNGLVERTEXATTRIB1DARBPROC*)0x00000001411A4920; // glVertexAttrib1dARB
PFNGLVERTEXATTRIB1DNVPROC* divagl_glVertexAttrib1dNV
    = (PFNGLVERTEXATTRIB1DNVPROC*)0x00000001411A5150; // glVertexAttrib1dNV
PFNGLVERTEXATTRIB1DVPROC* divagl_glVertexAttrib1dv
    = (PFNGLVERTEXATTRIB1DVPROC*)0x00000001411A4400; // glVertexAttrib1dv
PFNGLVERTEXATTRIB1DVARBPROC* divagl_glVertexAttrib1dvARB
    = (PFNGLVERTEXATTRIB1DVARBPROC*)0x00000001411A4928; // glVertexAttrib1dvARB
PFNGLVERTEXATTRIB1DVNVPROC* divagl_glVertexAttrib1dvNV
    = (PFNGLVERTEXATTRIB1DVNVPROC*)0x00000001411A5158; // glVertexAttrib1dvNV
PFNGLVERTEXATTRIB1FPROC* divagl_glVertexAttrib1f
    = (PFNGLVERTEXATTRIB1FPROC*)0x00000001411A4408; // glVertexAttrib1f
PFNGLVERTEXATTRIB1FARBPROC* divagl_glVertexAttrib1fARB
    = (PFNGLVERTEXATTRIB1FARBPROC*)0x00000001411A4930; // glVertexAttrib1fARB
PFNGLVERTEXATTRIB1FNVPROC* divagl_glVertexAttrib1fNV
    = (PFNGLVERTEXATTRIB1FNVPROC*)0x00000001411A5160; // glVertexAttrib1fNV
PFNGLVERTEXATTRIB1FVPROC* divagl_glVertexAttrib1fv
    = (PFNGLVERTEXATTRIB1FVPROC*)0x00000001411A4410; // glVertexAttrib1fv
PFNGLVERTEXATTRIB1FVARBPROC* divagl_glVertexAttrib1fvARB
    = (PFNGLVERTEXATTRIB1FVARBPROC*)0x00000001411A4938; // glVertexAttrib1fvARB
PFNGLVERTEXATTRIB1FVNVPROC* divagl_glVertexAttrib1fvNV
    = (PFNGLVERTEXATTRIB1FVNVPROC*)0x00000001411A5168; // glVertexAttrib1fvNV
PFNGLVERTEXATTRIB1HNVPROC* divagl_glVertexAttrib1hNV
    = (PFNGLVERTEXATTRIB1HNVPROC*)0x00000001411A5410; // glVertexAttrib1hNV
PFNGLVERTEXATTRIB1HVNVPROC* divagl_glVertexAttrib1hvNV
    = (PFNGLVERTEXATTRIB1HVNVPROC*)0x00000001411A5418; // glVertexAttrib1hvNV
PFNGLVERTEXATTRIB1SPROC* divagl_glVertexAttrib1s
    = (PFNGLVERTEXATTRIB1SPROC*)0x00000001411A4418; // glVertexAttrib1s
PFNGLVERTEXATTRIB1SARBPROC* divagl_glVertexAttrib1sARB
    = (PFNGLVERTEXATTRIB1SARBPROC*)0x00000001411A4940; // glVertexAttrib1sARB
PFNGLVERTEXATTRIB1SNVPROC* divagl_glVertexAttrib1sNV
    = (PFNGLVERTEXATTRIB1SNVPROC*)0x00000001411A5170; // glVertexAttrib1sNV
PFNGLVERTEXATTRIB1SVPROC* divagl_glVertexAttrib1sv
    = (PFNGLVERTEXATTRIB1SVPROC*)0x00000001411A4420; // glVertexAttrib1sv
PFNGLVERTEXATTRIB1SVARBPROC* divagl_glVertexAttrib1svARB
    = (PFNGLVERTEXATTRIB1SVARBPROC*)0x00000001411A4948; // glVertexAttrib1svARB
PFNGLVERTEXATTRIB1SVNVPROC* divagl_glVertexAttrib1svNV
    = (PFNGLVERTEXATTRIB1SVNVPROC*)0x00000001411A5178; // glVertexAttrib1svNV
PFNGLVERTEXATTRIB2DPROC* divagl_glVertexAttrib2d
    = (PFNGLVERTEXATTRIB2DPROC*)0x00000001411A4428; // glVertexAttrib2d
PFNGLVERTEXATTRIB2DARBPROC* divagl_glVertexAttrib2dARB
    = (PFNGLVERTEXATTRIB2DARBPROC*)0x00000001411A4950; // glVertexAttrib2dARB
PFNGLVERTEXATTRIB2DNVPROC* divagl_glVertexAttrib2dNV
    = (PFNGLVERTEXATTRIB2DNVPROC*)0x00000001411A5180; // glVertexAttrib2dNV
PFNGLVERTEXATTRIB2DVPROC* divagl_glVertexAttrib2dv
    = (PFNGLVERTEXATTRIB2DVPROC*)0x00000001411A4430; // glVertexAttrib2dv
PFNGLVERTEXATTRIB2DVARBPROC* divagl_glVertexAttrib2dvARB
    = (PFNGLVERTEXATTRIB2DVARBPROC*)0x00000001411A4958; // glVertexAttrib2dvARB
PFNGLVERTEXATTRIB2DVNVPROC* divagl_glVertexAttrib2dvNV
    = (PFNGLVERTEXATTRIB2DVNVPROC*)0x00000001411A5188; // glVertexAttrib2dvNV
PFNGLVERTEXATTRIB2FPROC* divagl_glVertexAttrib2f
    = (PFNGLVERTEXATTRIB2FPROC*)0x00000001411A4438; // glVertexAttrib2f
PFNGLVERTEXATTRIB2FARBPROC* divagl_glVertexAttrib2fARB
    = (PFNGLVERTEXATTRIB2FARBPROC*)0x00000001411A4960; // glVertexAttrib2fARB
PFNGLVERTEXATTRIB2FNVPROC* divagl_glVertexAttrib2fNV
    = (PFNGLVERTEXATTRIB2FNVPROC*)0x00000001411A5190; // glVertexAttrib2fNV
PFNGLVERTEXATTRIB2FVPROC* divagl_glVertexAttrib2fv
    = (PFNGLVERTEXATTRIB2FVPROC*)0x00000001411A4440; // glVertexAttrib2fv
PFNGLVERTEXATTRIB2FVARBPROC* divagl_glVertexAttrib2fvARB
    = (PFNGLVERTEXATTRIB2FVARBPROC*)0x00000001411A4968; // glVertexAttrib2fvARB
PFNGLVERTEXATTRIB2FVNVPROC* divagl_glVertexAttrib2fvNV
    = (PFNGLVERTEXATTRIB2FVNVPROC*)0x00000001411A5198; // glVertexAttrib2fvNV
PFNGLVERTEXATTRIB2HNVPROC* divagl_glVertexAttrib2hNV
    = (PFNGLVERTEXATTRIB2HNVPROC*)0x00000001411A5420; // glVertexAttrib2hNV
PFNGLVERTEXATTRIB2HVNVPROC* divagl_glVertexAttrib2hvNV
    = (PFNGLVERTEXATTRIB2HVNVPROC*)0x00000001411A5428; // glVertexAttrib2hvNV
PFNGLVERTEXATTRIB2SPROC* divagl_glVertexAttrib2s
    = (PFNGLVERTEXATTRIB2SPROC*)0x00000001411A4448; // glVertexAttrib2s
PFNGLVERTEXATTRIB2SARBPROC* divagl_glVertexAttrib2sARB
    = (PFNGLVERTEXATTRIB2SARBPROC*)0x00000001411A4970; // glVertexAttrib2sARB
PFNGLVERTEXATTRIB2SNVPROC* divagl_glVertexAttrib2sNV
    = (PFNGLVERTEXATTRIB2SNVPROC*)0x00000001411A51A0; // glVertexAttrib2sNV
PFNGLVERTEXATTRIB2SVPROC* divagl_glVertexAttrib2sv
    = (PFNGLVERTEXATTRIB2SVPROC*)0x00000001411A4450; // glVertexAttrib2sv
PFNGLVERTEXATTRIB2SVARBPROC* divagl_glVertexAttrib2svARB
    = (PFNGLVERTEXATTRIB2SVARBPROC*)0x00000001411A4978; // glVertexAttrib2svARB
PFNGLVERTEXATTRIB2SVNVPROC* divagl_glVertexAttrib2svNV
    = (PFNGLVERTEXATTRIB2SVNVPROC*)0x00000001411A51A8; // glVertexAttrib2svNV
PFNGLVERTEXATTRIB3DPROC* divagl_glVertexAttrib3d
    = (PFNGLVERTEXATTRIB3DPROC*)0x00000001411A4458; // glVertexAttrib3d
PFNGLVERTEXATTRIB3DARBPROC* divagl_glVertexAttrib3dARB
    = (PFNGLVERTEXATTRIB3DARBPROC*)0x00000001411A4980; // glVertexAttrib3dARB
PFNGLVERTEXATTRIB3DNVPROC* divagl_glVertexAttrib3dNV
    = (PFNGLVERTEXATTRIB3DNVPROC*)0x00000001411A51B0; // glVertexAttrib3dNV
PFNGLVERTEXATTRIB3DVPROC* divagl_glVertexAttrib3dv
    = (PFNGLVERTEXATTRIB3DVPROC*)0x00000001411A4460; // glVertexAttrib3dv
PFNGLVERTEXATTRIB3DVARBPROC* divagl_glVertexAttrib3dvARB
    = (PFNGLVERTEXATTRIB3DVARBPROC*)0x00000001411A4988; // glVertexAttrib3dvARB
PFNGLVERTEXATTRIB3DVNVPROC* divagl_glVertexAttrib3dvNV
    = (PFNGLVERTEXATTRIB3DVNVPROC*)0x00000001411A51B8; // glVertexAttrib3dvNV
PFNGLVERTEXATTRIB3FPROC* divagl_glVertexAttrib3f
    = (PFNGLVERTEXATTRIB3FPROC*)0x00000001411A4468; // glVertexAttrib3f
PFNGLVERTEXATTRIB3FARBPROC* divagl_glVertexAttrib3fARB
    = (PFNGLVERTEXATTRIB3FARBPROC*)0x00000001411A4990; // glVertexAttrib3fARB
PFNGLVERTEXATTRIB3FNVPROC* divagl_glVertexAttrib3fNV
    = (PFNGLVERTEXATTRIB3FNVPROC*)0x00000001411A51C0; // glVertexAttrib3fNV
PFNGLVERTEXATTRIB3FVPROC* divagl_glVertexAttrib3fv
    = (PFNGLVERTEXATTRIB3FVPROC*)0x00000001411A4470; // glVertexAttrib3fv
PFNGLVERTEXATTRIB3FVARBPROC* divagl_glVertexAttrib3fvARB
    = (PFNGLVERTEXATTRIB3FVARBPROC*)0x00000001411A4998; // glVertexAttrib3fvARB
PFNGLVERTEXATTRIB3FVNVPROC* divagl_glVertexAttrib3fvNV
    = (PFNGLVERTEXATTRIB3FVNVPROC*)0x00000001411A51C8; // glVertexAttrib3fvNV
PFNGLVERTEXATTRIB3HNVPROC* divagl_glVertexAttrib3hNV
    = (PFNGLVERTEXATTRIB3HNVPROC*)0x00000001411A5430; // glVertexAttrib3hNV
PFNGLVERTEXATTRIB3HVNVPROC* divagl_glVertexAttrib3hvNV
    = (PFNGLVERTEXATTRIB3HVNVPROC*)0x00000001411A5438; // glVertexAttrib3hvNV
PFNGLVERTEXATTRIB3SPROC* divagl_glVertexAttrib3s
    = (PFNGLVERTEXATTRIB3SPROC*)0x00000001411A4478; // glVertexAttrib3s
PFNGLVERTEXATTRIB3SARBPROC* divagl_glVertexAttrib3sARB
    = (PFNGLVERTEXATTRIB3SARBPROC*)0x00000001411A49A0; // glVertexAttrib3sARB
PFNGLVERTEXATTRIB3SNVPROC* divagl_glVertexAttrib3sNV
    = (PFNGLVERTEXATTRIB3SNVPROC*)0x00000001411A51D0; // glVertexAttrib3sNV
PFNGLVERTEXATTRIB3SVPROC* divagl_glVertexAttrib3sv
    = (PFNGLVERTEXATTRIB3SVPROC*)0x00000001411A4480; // glVertexAttrib3sv
PFNGLVERTEXATTRIB3SVARBPROC* divagl_glVertexAttrib3svARB
    = (PFNGLVERTEXATTRIB3SVARBPROC*)0x00000001411A49A8; // glVertexAttrib3svARB
PFNGLVERTEXATTRIB3SVNVPROC* divagl_glVertexAttrib3svNV
    = (PFNGLVERTEXATTRIB3SVNVPROC*)0x00000001411A51D8; // glVertexAttrib3svNV
PFNGLVERTEXATTRIB4BVPROC* divagl_glVertexAttrib4bv
    = (PFNGLVERTEXATTRIB4BVPROC*)0x00000001411A44C0; // glVertexAttrib4bv
PFNGLVERTEXATTRIB4BVARBPROC* divagl_glVertexAttrib4bvARB
    = (PFNGLVERTEXATTRIB4BVARBPROC*)0x00000001411A49E8; // glVertexAttrib4bvARB
PFNGLVERTEXATTRIB4DPROC* divagl_glVertexAttrib4d
    = (PFNGLVERTEXATTRIB4DPROC*)0x00000001411A44C8; // glVertexAttrib4d
PFNGLVERTEXATTRIB4DARBPROC* divagl_glVertexAttrib4dARB
    = (PFNGLVERTEXATTRIB4DARBPROC*)0x00000001411A49F0; // glVertexAttrib4dARB
PFNGLVERTEXATTRIB4DNVPROC* divagl_glVertexAttrib4dNV
    = (PFNGLVERTEXATTRIB4DNVPROC*)0x00000001411A51E0; // glVertexAttrib4dNV
PFNGLVERTEXATTRIB4DVPROC* divagl_glVertexAttrib4dv
    = (PFNGLVERTEXATTRIB4DVPROC*)0x00000001411A44D0; // glVertexAttrib4dv
PFNGLVERTEXATTRIB4DVARBPROC* divagl_glVertexAttrib4dvARB
    = (PFNGLVERTEXATTRIB4DVARBPROC*)0x00000001411A49F8; // glVertexAttrib4dvARB
PFNGLVERTEXATTRIB4DVNVPROC* divagl_glVertexAttrib4dvNV
    = (PFNGLVERTEXATTRIB4DVNVPROC*)0x00000001411A51E8; // glVertexAttrib4dvNV
PFNGLVERTEXATTRIB4FPROC* divagl_glVertexAttrib4f
    = (PFNGLVERTEXATTRIB4FPROC*)0x00000001411A44D8; // glVertexAttrib4f
PFNGLVERTEXATTRIB4FARBPROC* divagl_glVertexAttrib4fARB
    = (PFNGLVERTEXATTRIB4FARBPROC*)0x00000001411A4A00; // glVertexAttrib4fARB
PFNGLVERTEXATTRIB4FNVPROC* divagl_glVertexAttrib4fNV
    = (PFNGLVERTEXATTRIB4FNVPROC*)0x00000001411A51F0; // glVertexAttrib4fNV
PFNGLVERTEXATTRIB4FVPROC* divagl_glVertexAttrib4fv
    = (PFNGLVERTEXATTRIB4FVPROC*)0x00000001411A44E0; // glVertexAttrib4fv
PFNGLVERTEXATTRIB4FVARBPROC* divagl_glVertexAttrib4fvARB
    = (PFNGLVERTEXATTRIB4FVARBPROC*)0x00000001411A4A08; // glVertexAttrib4fvARB
PFNGLVERTEXATTRIB4FVNVPROC* divagl_glVertexAttrib4fvNV
    = (PFNGLVERTEXATTRIB4FVNVPROC*)0x00000001411A51F8; // glVertexAttrib4fvNV
PFNGLVERTEXATTRIB4HNVPROC* divagl_glVertexAttrib4hNV
    = (PFNGLVERTEXATTRIB4HNVPROC*)0x00000001411A5440; // glVertexAttrib4hNV
PFNGLVERTEXATTRIB4HVNVPROC* divagl_glVertexAttrib4hvNV
    = (PFNGLVERTEXATTRIB4HVNVPROC*)0x00000001411A5448; // glVertexAttrib4hvNV
PFNGLVERTEXATTRIB4IVPROC* divagl_glVertexAttrib4iv
    = (PFNGLVERTEXATTRIB4IVPROC*)0x00000001411A44E8; // glVertexAttrib4iv
PFNGLVERTEXATTRIB4IVARBPROC* divagl_glVertexAttrib4ivARB
    = (PFNGLVERTEXATTRIB4IVARBPROC*)0x00000001411A4A10; // glVertexAttrib4ivARB
PFNGLVERTEXATTRIB4NBVPROC* divagl_glVertexAttrib4Nbv
    = (PFNGLVERTEXATTRIB4NBVPROC*)0x00000001411A4488; // glVertexAttrib4Nbv
PFNGLVERTEXATTRIB4NBVARBPROC* divagl_glVertexAttrib4NbvARB
    = (PFNGLVERTEXATTRIB4NBVARBPROC*)0x00000001411A49B0; // glVertexAttrib4NbvARB
PFNGLVERTEXATTRIB4NIVPROC* divagl_glVertexAttrib4Niv
    = (PFNGLVERTEXATTRIB4NIVPROC*)0x00000001411A4490; // glVertexAttrib4Niv
PFNGLVERTEXATTRIB4NIVARBPROC* divagl_glVertexAttrib4NivARB
    = (PFNGLVERTEXATTRIB4NIVARBPROC*)0x00000001411A49B8; // glVertexAttrib4NivARB
PFNGLVERTEXATTRIB4NSVPROC* divagl_glVertexAttrib4Nsv
    = (PFNGLVERTEXATTRIB4NSVPROC*)0x00000001411A4498; // glVertexAttrib4Nsv
PFNGLVERTEXATTRIB4NSVARBPROC* divagl_glVertexAttrib4NsvARB
    = (PFNGLVERTEXATTRIB4NSVARBPROC*)0x00000001411A49C0; // glVertexAttrib4NsvARB
PFNGLVERTEXATTRIB4NUBPROC* divagl_glVertexAttrib4Nub
    = (PFNGLVERTEXATTRIB4NUBPROC*)0x00000001411A44A0; // glVertexAttrib4Nub
PFNGLVERTEXATTRIB4NUBARBPROC* divagl_glVertexAttrib4NubARB
    = (PFNGLVERTEXATTRIB4NUBARBPROC*)0x00000001411A49C8; // glVertexAttrib4NubARB
PFNGLVERTEXATTRIB4NUBVPROC* divagl_glVertexAttrib4Nubv
    = (PFNGLVERTEXATTRIB4NUBVPROC*)0x00000001411A44A8; // glVertexAttrib4Nubv
PFNGLVERTEXATTRIB4NUBVARBPROC* divagl_glVertexAttrib4NubvARB
    = (PFNGLVERTEXATTRIB4NUBVARBPROC*)0x00000001411A49D0; // glVertexAttrib4NubvARB
PFNGLVERTEXATTRIB4NUIVPROC* divagl_glVertexAttrib4Nuiv
    = (PFNGLVERTEXATTRIB4NUIVPROC*)0x00000001411A44B0; // glVertexAttrib4Nuiv
PFNGLVERTEXATTRIB4NUIVARBPROC* divagl_glVertexAttrib4NuivARB
    = (PFNGLVERTEXATTRIB4NUIVARBPROC*)0x00000001411A49D8; // glVertexAttrib4NuivARB
PFNGLVERTEXATTRIB4NUSVPROC* divagl_glVertexAttrib4Nusv
    = (PFNGLVERTEXATTRIB4NUSVPROC*)0x00000001411A44B8; // glVertexAttrib4Nusv
PFNGLVERTEXATTRIB4NUSVARBPROC* divagl_glVertexAttrib4NusvARB
    = (PFNGLVERTEXATTRIB4NUSVARBPROC*)0x00000001411A49E0; // glVertexAttrib4NusvARB
PFNGLVERTEXATTRIB4SPROC* divagl_glVertexAttrib4s
    = (PFNGLVERTEXATTRIB4SPROC*)0x00000001411A44F0; // glVertexAttrib4s
PFNGLVERTEXATTRIB4SARBPROC* divagl_glVertexAttrib4sARB
    = (PFNGLVERTEXATTRIB4SARBPROC*)0x00000001411A4A18; // glVertexAttrib4sARB
PFNGLVERTEXATTRIB4SNVPROC* divagl_glVertexAttrib4sNV
    = (PFNGLVERTEXATTRIB4SNVPROC*)0x00000001411A5200; // glVertexAttrib4sNV
PFNGLVERTEXATTRIB4SVPROC* divagl_glVertexAttrib4sv
    = (PFNGLVERTEXATTRIB4SVPROC*)0x00000001411A44F8; // glVertexAttrib4sv
PFNGLVERTEXATTRIB4SVARBPROC* divagl_glVertexAttrib4svARB
    = (PFNGLVERTEXATTRIB4SVARBPROC*)0x00000001411A4A20; // glVertexAttrib4svARB
PFNGLVERTEXATTRIB4SVNVPROC* divagl_glVertexAttrib4svNV
    = (PFNGLVERTEXATTRIB4SVNVPROC*)0x00000001411A5208; // glVertexAttrib4svNV
PFNGLVERTEXATTRIB4UBNVPROC* divagl_glVertexAttrib4ubNV
    = (PFNGLVERTEXATTRIB4UBNVPROC*)0x00000001411A5210; // glVertexAttrib4ubNV
PFNGLVERTEXATTRIB4UBVPROC* divagl_glVertexAttrib4ubv
    = (PFNGLVERTEXATTRIB4UBVPROC*)0x00000001411A4500; // glVertexAttrib4ubv
PFNGLVERTEXATTRIB4UBVARBPROC* divagl_glVertexAttrib4ubvARB
    = (PFNGLVERTEXATTRIB4UBVARBPROC*)0x00000001411A4A28; // glVertexAttrib4ubvARB
PFNGLVERTEXATTRIB4UBVNVPROC* divagl_glVertexAttrib4ubvNV
    = (PFNGLVERTEXATTRIB4UBVNVPROC*)0x00000001411A5218; // glVertexAttrib4ubvNV
PFNGLVERTEXATTRIB4UIVPROC* divagl_glVertexAttrib4uiv
    = (PFNGLVERTEXATTRIB4UIVPROC*)0x00000001411A4508; // glVertexAttrib4uiv
PFNGLVERTEXATTRIB4UIVARBPROC* divagl_glVertexAttrib4uivARB
    = (PFNGLVERTEXATTRIB4UIVARBPROC*)0x00000001411A4A30; // glVertexAttrib4uivARB
PFNGLVERTEXATTRIB4USVPROC* divagl_glVertexAttrib4usv
    = (PFNGLVERTEXATTRIB4USVPROC*)0x00000001411A4510; // glVertexAttrib4usv
PFNGLVERTEXATTRIB4USVARBPROC* divagl_glVertexAttrib4usvARB
    = (PFNGLVERTEXATTRIB4USVARBPROC*)0x00000001411A4A38; // glVertexAttrib4usvARB
PFNGLVERTEXATTRIBI1IPROC* divagl_glVertexAttribI1i
    = (PFNGLVERTEXATTRIBI1IPROC*)0x00000001411A45C0; // glVertexAttribI1i
PFNGLVERTEXATTRIBI1IEXTPROC* divagl_glVertexAttribI1iEXT
    = (PFNGLVERTEXATTRIBI1IEXTPROC*)0x00000001411A5600; // glVertexAttribI1iEXT
PFNGLVERTEXATTRIBI1IVPROC* divagl_glVertexAttribI1iv
    = (PFNGLVERTEXATTRIBI1IVPROC*)0x00000001411A4600; // glVertexAttribI1iv
PFNGLVERTEXATTRIBI1IVEXTPROC* divagl_glVertexAttribI1ivEXT
    = (PFNGLVERTEXATTRIBI1IVEXTPROC*)0x00000001411A5640; // glVertexAttribI1ivEXT
PFNGLVERTEXATTRIBI1UIPROC* divagl_glVertexAttribI1ui
    = (PFNGLVERTEXATTRIBI1UIPROC*)0x00000001411A45E0; // glVertexAttribI1ui
PFNGLVERTEXATTRIBI1UIEXTPROC* divagl_glVertexAttribI1uiEXT
    = (PFNGLVERTEXATTRIBI1UIEXTPROC*)0x00000001411A5620; // glVertexAttribI1uiEXT
PFNGLVERTEXATTRIBI1UIVPROC* divagl_glVertexAttribI1uiv
    = (PFNGLVERTEXATTRIBI1UIVPROC*)0x00000001411A4620; // glVertexAttribI1uiv
PFNGLVERTEXATTRIBI1UIVEXTPROC* divagl_glVertexAttribI1uivEXT
    = (PFNGLVERTEXATTRIBI1UIVEXTPROC*)0x00000001411A5660; // glVertexAttribI1uivEXT
PFNGLVERTEXATTRIBI2IPROC* divagl_glVertexAttribI2i
    = (PFNGLVERTEXATTRIBI2IPROC*)0x00000001411A45C8; // glVertexAttribI2i
PFNGLVERTEXATTRIBI2IEXTPROC* divagl_glVertexAttribI2iEXT
    = (PFNGLVERTEXATTRIBI2IEXTPROC*)0x00000001411A5608; // glVertexAttribI2iEXT
PFNGLVERTEXATTRIBI2IVPROC* divagl_glVertexAttribI2iv
    = (PFNGLVERTEXATTRIBI2IVPROC*)0x00000001411A4608; // glVertexAttribI2iv
PFNGLVERTEXATTRIBI2IVEXTPROC* divagl_glVertexAttribI2ivEXT
    = (PFNGLVERTEXATTRIBI2IVEXTPROC*)0x00000001411A5648; // glVertexAttribI2ivEXT
PFNGLVERTEXATTRIBI2UIPROC* divagl_glVertexAttribI2ui
    = (PFNGLVERTEXATTRIBI2UIPROC*)0x00000001411A45E8; // glVertexAttribI2ui
PFNGLVERTEXATTRIBI2UIEXTPROC* divagl_glVertexAttribI2uiEXT
    = (PFNGLVERTEXATTRIBI2UIEXTPROC*)0x00000001411A5628; // glVertexAttribI2uiEXT
PFNGLVERTEXATTRIBI2UIVPROC* divagl_glVertexAttribI2uiv
    = (PFNGLVERTEXATTRIBI2UIVPROC*)0x00000001411A4628; // glVertexAttribI2uiv
PFNGLVERTEXATTRIBI2UIVEXTPROC* divagl_glVertexAttribI2uivEXT
    = (PFNGLVERTEXATTRIBI2UIVEXTPROC*)0x00000001411A5668; // glVertexAttribI2uivEXT
PFNGLVERTEXATTRIBI3IPROC* divagl_glVertexAttribI3i
    = (PFNGLVERTEXATTRIBI3IPROC*)0x00000001411A45D0; // glVertexAttribI3i
PFNGLVERTEXATTRIBI3IEXTPROC* divagl_glVertexAttribI3iEXT
    = (PFNGLVERTEXATTRIBI3IEXTPROC*)0x00000001411A5610; // glVertexAttribI3iEXT
PFNGLVERTEXATTRIBI3IVPROC* divagl_glVertexAttribI3iv
    = (PFNGLVERTEXATTRIBI3IVPROC*)0x00000001411A4610; // glVertexAttribI3iv
PFNGLVERTEXATTRIBI3IVEXTPROC* divagl_glVertexAttribI3ivEXT
    = (PFNGLVERTEXATTRIBI3IVEXTPROC*)0x00000001411A5650; // glVertexAttribI3ivEXT
PFNGLVERTEXATTRIBI3UIPROC* divagl_glVertexAttribI3ui
    = (PFNGLVERTEXATTRIBI3UIPROC*)0x00000001411A45F0; // glVertexAttribI3ui
PFNGLVERTEXATTRIBI3UIEXTPROC* divagl_glVertexAttribI3uiEXT
    = (PFNGLVERTEXATTRIBI3UIEXTPROC*)0x00000001411A5630; // glVertexAttribI3uiEXT
PFNGLVERTEXATTRIBI3UIVPROC* divagl_glVertexAttribI3uiv
    = (PFNGLVERTEXATTRIBI3UIVPROC*)0x00000001411A4630; // glVertexAttribI3uiv
PFNGLVERTEXATTRIBI3UIVEXTPROC* divagl_glVertexAttribI3uivEXT
    = (PFNGLVERTEXATTRIBI3UIVEXTPROC*)0x00000001411A5670; // glVertexAttribI3uivEXT
PFNGLVERTEXATTRIBI4BVPROC* divagl_glVertexAttribI4bv
    = (PFNGLVERTEXATTRIBI4BVPROC*)0x00000001411A4640; // glVertexAttribI4bv
PFNGLVERTEXATTRIBI4BVEXTPROC* divagl_glVertexAttribI4bvEXT
    = (PFNGLVERTEXATTRIBI4BVEXTPROC*)0x00000001411A5680; // glVertexAttribI4bvEXT
PFNGLVERTEXATTRIBI4IPROC* divagl_glVertexAttribI4i
    = (PFNGLVERTEXATTRIBI4IPROC*)0x00000001411A45D8; // glVertexAttribI4i
PFNGLVERTEXATTRIBI4IEXTPROC* divagl_glVertexAttribI4iEXT
    = (PFNGLVERTEXATTRIBI4IEXTPROC*)0x00000001411A5618; // glVertexAttribI4iEXT
PFNGLVERTEXATTRIBI4IVPROC* divagl_glVertexAttribI4iv
    = (PFNGLVERTEXATTRIBI4IVPROC*)0x00000001411A4618; // glVertexAttribI4iv
PFNGLVERTEXATTRIBI4IVEXTPROC* divagl_glVertexAttribI4ivEXT
    = (PFNGLVERTEXATTRIBI4IVEXTPROC*)0x00000001411A5658; // glVertexAttribI4ivEXT
PFNGLVERTEXATTRIBI4SVPROC* divagl_glVertexAttribI4sv
    = (PFNGLVERTEXATTRIBI4SVPROC*)0x00000001411A4648; // glVertexAttribI4sv
PFNGLVERTEXATTRIBI4SVEXTPROC* divagl_glVertexAttribI4svEXT
    = (PFNGLVERTEXATTRIBI4SVEXTPROC*)0x00000001411A5688; // glVertexAttribI4svEXT
PFNGLVERTEXATTRIBI4UBVPROC* divagl_glVertexAttribI4ubv
    = (PFNGLVERTEXATTRIBI4UBVPROC*)0x00000001411A4650; // glVertexAttribI4ubv
PFNGLVERTEXATTRIBI4UBVEXTPROC* divagl_glVertexAttribI4ubvEXT
    = (PFNGLVERTEXATTRIBI4UBVEXTPROC*)0x00000001411A5690; // glVertexAttribI4ubvEXT
PFNGLVERTEXATTRIBI4UIPROC* divagl_glVertexAttribI4ui
    = (PFNGLVERTEXATTRIBI4UIPROC*)0x00000001411A45F8; // glVertexAttribI4ui
PFNGLVERTEXATTRIBI4UIEXTPROC* divagl_glVertexAttribI4uiEXT
    = (PFNGLVERTEXATTRIBI4UIEXTPROC*)0x00000001411A5638; // glVertexAttribI4uiEXT
PFNGLVERTEXATTRIBI4UIVPROC* divagl_glVertexAttribI4uiv
    = (PFNGLVERTEXATTRIBI4UIVPROC*)0x00000001411A4638; // glVertexAttribI4uiv
PFNGLVERTEXATTRIBI4UIVEXTPROC* divagl_glVertexAttribI4uivEXT
    = (PFNGLVERTEXATTRIBI4UIVEXTPROC*)0x00000001411A5678; // glVertexAttribI4uivEXT
PFNGLVERTEXATTRIBI4USVPROC* divagl_glVertexAttribI4usv
    = (PFNGLVERTEXATTRIBI4USVPROC*)0x00000001411A4658; // glVertexAttribI4usv
PFNGLVERTEXATTRIBI4USVEXTPROC* divagl_glVertexAttribI4usvEXT
    = (PFNGLVERTEXATTRIBI4USVEXTPROC*)0x00000001411A5698; // glVertexAttribI4usvEXT
PFNGLVERTEXATTRIBIPOINTERPROC* divagl_glVertexAttribIPointer
    = (PFNGLVERTEXATTRIBIPOINTERPROC*)0x00000001411A4660; // glVertexAttribIPointer
PFNGLVERTEXATTRIBIPOINTEREXTPROC* divagl_glVertexAttribIPointerEXT
    = (PFNGLVERTEXATTRIBIPOINTEREXTPROC*)0x00000001411A56A0; // glVertexAttribIPointerEXT
PFNGLVERTEXATTRIBPOINTERPROC* divagl_glVertexAttribPointer
    = (PFNGLVERTEXATTRIBPOINTERPROC*)0x00000001411A4518; // glVertexAttribPointer
PFNGLVERTEXATTRIBPOINTERNVPROC* divagl_glVertexAttribPointerNV
    = (PFNGLVERTEXATTRIBPOINTERNVPROC*)0x00000001411A5148; // glVertexAttribPointerNV
PFNGLVERTEXATTRIBS1DVNVPROC* divagl_glVertexAttribs1dvNV
    = (PFNGLVERTEXATTRIBS1DVNVPROC*)0x00000001411A5220; // glVertexAttribs1dvNV
PFNGLVERTEXATTRIBS1FVNVPROC* divagl_glVertexAttribs1fvNV
    = (PFNGLVERTEXATTRIBS1FVNVPROC*)0x00000001411A5228; // glVertexAttribs1fvNV
PFNGLVERTEXATTRIBS1HVNVPROC* divagl_glVertexAttribs1hvNV
    = (PFNGLVERTEXATTRIBS1HVNVPROC*)0x00000001411A5450; // glVertexAttribs1hvNV
PFNGLVERTEXATTRIBS1SVNVPROC* divagl_glVertexAttribs1svNV
    = (PFNGLVERTEXATTRIBS1SVNVPROC*)0x00000001411A5230; // glVertexAttribs1svNV
PFNGLVERTEXATTRIBS2DVNVPROC* divagl_glVertexAttribs2dvNV
    = (PFNGLVERTEXATTRIBS2DVNVPROC*)0x00000001411A5238; // glVertexAttribs2dvNV
PFNGLVERTEXATTRIBS2FVNVPROC* divagl_glVertexAttribs2fvNV
    = (PFNGLVERTEXATTRIBS2FVNVPROC*)0x00000001411A5240; // glVertexAttribs2fvNV
PFNGLVERTEXATTRIBS2HVNVPROC* divagl_glVertexAttribs2hvNV
    = (PFNGLVERTEXATTRIBS2HVNVPROC*)0x00000001411A5458; // glVertexAttribs2hvNV
PFNGLVERTEXATTRIBS2SVNVPROC* divagl_glVertexAttribs2svNV
    = (PFNGLVERTEXATTRIBS2SVNVPROC*)0x00000001411A5248; // glVertexAttribs2svNV
PFNGLVERTEXATTRIBS3DVNVPROC* divagl_glVertexAttribs3dvNV
    = (PFNGLVERTEXATTRIBS3DVNVPROC*)0x00000001411A5250; // glVertexAttribs3dvNV
PFNGLVERTEXATTRIBS3FVNVPROC* divagl_glVertexAttribs3fvNV
    = (PFNGLVERTEXATTRIBS3FVNVPROC*)0x00000001411A5258; // glVertexAttribs3fvNV
PFNGLVERTEXATTRIBS3HVNVPROC* divagl_glVertexAttribs3hvNV
    = (PFNGLVERTEXATTRIBS3HVNVPROC*)0x00000001411A5460; // glVertexAttribs3hvNV
PFNGLVERTEXATTRIBS3SVNVPROC* divagl_glVertexAttribs3svNV
    = (PFNGLVERTEXATTRIBS3SVNVPROC*)0x00000001411A5260; // glVertexAttribs3svNV
PFNGLVERTEXATTRIBS4DVNVPROC* divagl_glVertexAttribs4dvNV
    = (PFNGLVERTEXATTRIBS4DVNVPROC*)0x00000001411A5268; // glVertexAttribs4dvNV
PFNGLVERTEXATTRIBS4FVNVPROC* divagl_glVertexAttribs4fvNV
    = (PFNGLVERTEXATTRIBS4FVNVPROC*)0x00000001411A5270; // glVertexAttribs4fvNV
PFNGLVERTEXATTRIBS4HVNVPROC* divagl_glVertexAttribs4hvNV
    = (PFNGLVERTEXATTRIBS4HVNVPROC*)0x00000001411A5468; // glVertexAttribs4hvNV
PFNGLVERTEXATTRIBS4SVNVPROC* divagl_glVertexAttribs4svNV
    = (PFNGLVERTEXATTRIBS4SVNVPROC*)0x00000001411A5278; // glVertexAttribs4svNV
PFNGLVERTEXATTRIBS4UBVNVPROC* divagl_glVertexAttribs4ubvNV
    = (PFNGLVERTEXATTRIBS4UBVNVPROC*)0x00000001411A5280; // glVertexAttribs4ubvNV
PFNGLVERTEXPOINTEREXTPROC* divagl_glVertexPointerEXT
    = (PFNGLVERTEXPOINTEREXTPROC*)0x00000001411A4EA0; // glVertexPointerEXT
PFNGLWINDOWPOS2DPROC* divagl_glWindowPos2d
    = (PFNGLWINDOWPOS2DPROC*)0x00000001411A4120; // glWindowPos2d
PFNGLWINDOWPOS2DARBPROC* divagl_glWindowPos2dARB
    = (PFNGLWINDOWPOS2DARBPROC*)0x00000001411A48A0; // glWindowPos2dARB
PFNGLWINDOWPOS2DVPROC* divagl_glWindowPos2dv
    = (PFNGLWINDOWPOS2DVPROC*)0x00000001411A4128; // glWindowPos2dv
PFNGLWINDOWPOS2DVARBPROC* divagl_glWindowPos2dvARB
    = (PFNGLWINDOWPOS2DVARBPROC*)0x00000001411A48A8; // glWindowPos2dvARB
PFNGLWINDOWPOS2FPROC* divagl_glWindowPos2f
    = (PFNGLWINDOWPOS2FPROC*)0x00000001411A4130; // glWindowPos2f
PFNGLWINDOWPOS2FARBPROC* divagl_glWindowPos2fARB
    = (PFNGLWINDOWPOS2FARBPROC*)0x00000001411A48B0; // glWindowPos2fARB
PFNGLWINDOWPOS2FVPROC* divagl_glWindowPos2fv
    = (PFNGLWINDOWPOS2FVPROC*)0x00000001411A4138; // glWindowPos2fv
PFNGLWINDOWPOS2FVARBPROC* divagl_glWindowPos2fvARB
    = (PFNGLWINDOWPOS2FVARBPROC*)0x00000001411A48B8; // glWindowPos2fvARB
PFNGLWINDOWPOS2IPROC* divagl_glWindowPos2i
    = (PFNGLWINDOWPOS2IPROC*)0x00000001411A4140; // glWindowPos2i
PFNGLWINDOWPOS2IARBPROC* divagl_glWindowPos2iARB
    = (PFNGLWINDOWPOS2IARBPROC*)0x00000001411A48C0; // glWindowPos2iARB
PFNGLWINDOWPOS2IVPROC* divagl_glWindowPos2iv
    = (PFNGLWINDOWPOS2IVPROC*)0x00000001411A4148; // glWindowPos2iv
PFNGLWINDOWPOS2IVARBPROC* divagl_glWindowPos2ivARB
    = (PFNGLWINDOWPOS2IVARBPROC*)0x00000001411A48C8; // glWindowPos2ivARB
PFNGLWINDOWPOS2SPROC* divagl_glWindowPos2s
    = (PFNGLWINDOWPOS2SPROC*)0x00000001411A4150; // glWindowPos2s
PFNGLWINDOWPOS2SARBPROC* divagl_glWindowPos2sARB
    = (PFNGLWINDOWPOS2SARBPROC*)0x00000001411A48D0; // glWindowPos2sARB
PFNGLWINDOWPOS2SVPROC* divagl_glWindowPos2sv
    = (PFNGLWINDOWPOS2SVPROC*)0x00000001411A4158; // glWindowPos2sv
PFNGLWINDOWPOS2SVARBPROC* divagl_glWindowPos2svARB
    = (PFNGLWINDOWPOS2SVARBPROC*)0x00000001411A48D8; // glWindowPos2svARB
PFNGLWINDOWPOS3DPROC* divagl_glWindowPos3d
    = (PFNGLWINDOWPOS3DPROC*)0x00000001411A4160; // glWindowPos3d
PFNGLWINDOWPOS3DARBPROC* divagl_glWindowPos3dARB
    = (PFNGLWINDOWPOS3DARBPROC*)0x00000001411A48E0; // glWindowPos3dARB
PFNGLWINDOWPOS3DVPROC* divagl_glWindowPos3dv
    = (PFNGLWINDOWPOS3DVPROC*)0x00000001411A4168; // glWindowPos3dv
PFNGLWINDOWPOS3DVARBPROC* divagl_glWindowPos3dvARB
    = (PFNGLWINDOWPOS3DVARBPROC*)0x00000001411A48E8; // glWindowPos3dvARB
PFNGLWINDOWPOS3FPROC* divagl_glWindowPos3f
    = (PFNGLWINDOWPOS3FPROC*)0x00000001411A4170; // glWindowPos3f
PFNGLWINDOWPOS3FARBPROC* divagl_glWindowPos3fARB
    = (PFNGLWINDOWPOS3FARBPROC*)0x00000001411A48F0; // glWindowPos3fARB
PFNGLWINDOWPOS3FVPROC* divagl_glWindowPos3fv
    = (PFNGLWINDOWPOS3FVPROC*)0x00000001411A4178; // glWindowPos3fv
PFNGLWINDOWPOS3FVARBPROC* divagl_glWindowPos3fvARB
    = (PFNGLWINDOWPOS3FVARBPROC*)0x00000001411A48F8; // glWindowPos3fvARB
PFNGLWINDOWPOS3IPROC* divagl_glWindowPos3i
    = (PFNGLWINDOWPOS3IPROC*)0x00000001411A4180; // glWindowPos3i
PFNGLWINDOWPOS3IARBPROC* divagl_glWindowPos3iARB
    = (PFNGLWINDOWPOS3IARBPROC*)0x00000001411A4900; // glWindowPos3iARB
PFNGLWINDOWPOS3IVPROC* divagl_glWindowPos3iv
    = (PFNGLWINDOWPOS3IVPROC*)0x00000001411A4188; // glWindowPos3iv
PFNGLWINDOWPOS3IVARBPROC* divagl_glWindowPos3ivARB
    = (PFNGLWINDOWPOS3IVARBPROC*)0x00000001411A4908; // glWindowPos3ivARB
PFNGLWINDOWPOS3SPROC* divagl_glWindowPos3s
    = (PFNGLWINDOWPOS3SPROC*)0x00000001411A4190; // glWindowPos3s
PFNGLWINDOWPOS3SARBPROC* divagl_glWindowPos3sARB
    = (PFNGLWINDOWPOS3SARBPROC*)0x00000001411A4910; // glWindowPos3sARB
PFNGLWINDOWPOS3SVPROC* divagl_glWindowPos3sv
    = (PFNGLWINDOWPOS3SVPROC*)0x00000001411A4198; // glWindowPos3sv
PFNGLWINDOWPOS3SVARBPROC* divagl_glWindowPos3svARB
    = (PFNGLWINDOWPOS3SVARBPROC*)0x00000001411A4918; // glWindowPos3svARB
PFNWGLALLOCATEMEMORYNVPROC* divagl_wglAllocateMemoryNV
    = (PFNWGLALLOCATEMEMORYNVPROC*)0x00000001411A3E50; // wglAllocateMemoryNV
PFNWGLBINDSWAPBARRIERNVPROC* divagl_wglBindSwapBarrierNV
    = (PFNWGLBINDSWAPBARRIERNVPROC*)0x00000001411A3EE0; // wglBindSwapBarrierNV
PFNWGLBINDTEXIMAGEARBPROC* divagl_wglBindTexImageARB
    = (PFNWGLBINDTEXIMAGEARBPROC*)0x00000001411A3DE0; // wglBindTexImageARB
PFNWGLBINDVIDEOIMAGENVPROC* divagl_wglBindVideoImageNV
    = (PFNWGLBINDVIDEOIMAGENVPROC*)0x00000001411A3E90; // wglBindVideoImageNV
PFNWGLCHOOSEPIXELFORMATARBPROC* divagl_wglChoosePixelFormatARB
    = (PFNWGLCHOOSEPIXELFORMATARBPROC*)0x00000001411A3D60; // wglChoosePixelFormatARB
PFNWGLCREATEBUFFERREGIONARBPROC* divagl_wglCreateBufferRegionARB
    = (PFNWGLCREATEBUFFERREGIONARBPROC*)0x00000001411A3CF0; // wglCreateBufferRegionARB
PFNWGLCREATECONTEXTATTRIBSARBPROC* divagl_wglCreateContextAttribsARB
    = (PFNWGLCREATECONTEXTATTRIBSARBPROC*)0x00000001411A3E10; // wglCreateContextAttribsARB
PFNWGLCREATEPBUFFERARBPROC* divagl_wglCreatePbufferARB
    = (PFNWGLCREATEPBUFFERARBPROC*)0x00000001411A3D90; // wglCreatePbufferARB
PFNWGLDELETEBUFFERREGIONARBPROC* divagl_wglDeleteBufferRegionARB
    = (PFNWGLDELETEBUFFERREGIONARBPROC*)0x00000001411A3D00; // wglDeleteBufferRegionARB
PFNWGLDESTROYPBUFFERARBPROC* divagl_wglDestroyPbufferARB
    = (PFNWGLDESTROYPBUFFERARBPROC*)0x00000001411A3DC0; // wglDestroyPbufferARB
PFNWGLDXCLOSEDEVICENVPROC* divagl_wglDXCloseDeviceNV
    = (PFNWGLDXCLOSEDEVICENVPROC*)0x00000001411A1A48; // wglDXCloseDeviceNV
PFNWGLDXLOCKOBJECTSNVPROC* divagl_wglDXLockObjectsNV
    = (PFNWGLDXLOCKOBJECTSNVPROC*)0x00000001411A1A68; // wglDXLockObjectsNV
PFNWGLDXOPENDEVICENVPROC* divagl_wglDXOpenDeviceNV
    = (PFNWGLDXOPENDEVICENVPROC*)0x00000001411A1A40; // wglDXOpenDeviceNV
PFNWGLDXREGISTEROBJECTNVPROC* divagl_wglDXRegisterObjectNV
    = (PFNWGLDXREGISTEROBJECTNVPROC*)0x00000001411A1A58; // wglDXRegisterObjectNV
PFNWGLDXSETRESOURCESHAREHANDLENVPROC* divagl_wglDXSetResourceShareHandleNV
    = (PFNWGLDXSETRESOURCESHAREHANDLENVPROC*)0x00000001411A1A50; // wglDXSetResourceShareHandleNV
PFNWGLDXUNLOCKOBJECTSNVPROC* divagl_wglDXUnlockObjectsNV
    = (PFNWGLDXUNLOCKOBJECTSNVPROC*)0x00000001411A1A70; // wglDXUnlockObjectsNV
PFNWGLDXUNREGISTEROBJECTNVPROC* divagl_wglDXUnregisterObjectNV
    = (PFNWGLDXUNREGISTEROBJECTNVPROC*)0x00000001411A1A60; // wglDXUnregisterObjectNV
PFNWGLFREEMEMORYNVPROC* divagl_wglFreeMemoryNV
    = (PFNWGLFREEMEMORYNVPROC*)0x00000001411A3E60; // wglFreeMemoryNV
PFNWGLGETCURRENTCONTEXTPROC* divagl_wglGetCurrentContext
    = (PFNWGLGETCURRENTCONTEXTPROC*)0x00000001411A1A28; // wglGetCurrentContext
PFNWGLGETCURRENTREADDCARBPROC* divagl_wglGetCurrentReadDCARB
    = (PFNWGLGETCURRENTREADDCARBPROC*)0x00000001411A3D80; // wglGetCurrentReadDCARB
PFNWGLGETEXTENSIONSSTRINGARBPROC* divagl_wglGetExtensionsStringARB
    = (PFNWGLGETEXTENSIONSSTRINGARBPROC*)0x00000001411A3D30; // wglGetExtensionsStringARB
PFNWGLGETEXTENSIONSSTRINGEXTPROC* divagl_wglGetExtensionsStringEXT
    = (PFNWGLGETEXTENSIONSSTRINGEXTPROC*)0x00000001411A3E20; // wglGetExtensionsStringEXT
PFNWGLGETPBUFFERDCARBPROC* divagl_wglGetPbufferDCARB
    = (PFNWGLGETPBUFFERDCARBPROC*)0x00000001411A3DA0; // wglGetPbufferDCARB
PFNWGLGETPIXELFORMATATTRIBFVARBPROC* divagl_wglGetPixelFormatAttribfvARB
    = (PFNWGLGETPIXELFORMATATTRIBFVARBPROC*)0x00000001411A3D50; // wglGetPixelFormatAttribfvARB
PFNWGLGETPIXELFORMATATTRIBIVARBPROC* divagl_wglGetPixelFormatAttribivARB
    = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC*)0x00000001411A3D40; // wglGetPixelFormatAttribivARB
PFNWGLGETPROCADDRESSPROC* divagl_wglGetProcAddress
    = (PFNWGLGETPROCADDRESSPROC*)0x00000001411A1A20; // wglGetProcAddress
PFNWGLGETSWAPINTERVALEXTPROC* divagl_wglGetSwapIntervalEXT
    = (PFNWGLGETSWAPINTERVALEXTPROC*)0x00000001411A3E40; // wglGetSwapIntervalEXT
PFNWGLGETVIDEODEVICENVPROC* divagl_wglGetVideoDeviceNV
    = (PFNWGLGETVIDEODEVICENVPROC*)0x00000001411A3E70; // wglGetVideoDeviceNV
PFNWGLGETVIDEOINFONVPROC* divagl_wglGetVideoInfoNV
    = (PFNWGLGETVIDEOINFONVPROC*)0x00000001411A3EC0; // wglGetVideoInfoNV
PFNWGLJOINSWAPGROUPNVPROC* divagl_wglJoinSwapGroupNV
    = (PFNWGLJOINSWAPGROUPNVPROC*)0x00000001411A3ED0; // wglJoinSwapGroupNV
PFNWGLMAKECONTEXTCURRENTARBPROC* divagl_wglMakeContextCurrentARB
    = (PFNWGLMAKECONTEXTCURRENTARBPROC*)0x00000001411A3D70; // wglMakeContextCurrentARB
PFNWGLQUERYFRAMECOUNTNVPROC* divagl_wglQueryFrameCountNV
    = (PFNWGLQUERYFRAMECOUNTNVPROC*)0x00000001411A3F10; // wglQueryFrameCountNV
PFNWGLQUERYMAXSWAPGROUPSNVPROC* divagl_wglQueryMaxSwapGroupsNV
    = (PFNWGLQUERYMAXSWAPGROUPSNVPROC*)0x00000001411A3F00; // wglQueryMaxSwapGroupsNV
PFNWGLQUERYPBUFFERARBPROC* divagl_wglQueryPbufferARB
    = (PFNWGLQUERYPBUFFERARBPROC*)0x00000001411A3DD0; // wglQueryPbufferARB
PFNWGLQUERYSWAPGROUPNVPROC* divagl_wglQuerySwapGroupNV
    = (PFNWGLQUERYSWAPGROUPNVPROC*)0x00000001411A3EF0; // wglQuerySwapGroupNV
PFNWGLRELEASEPBUFFERDCARBPROC* divagl_wglReleasePbufferDCARB
    = (PFNWGLRELEASEPBUFFERDCARBPROC*)0x00000001411A3DB0; // wglReleasePbufferDCARB
PFNWGLRELEASETEXIMAGEARBPROC* divagl_wglReleaseTexImageARB
    = (PFNWGLRELEASETEXIMAGEARBPROC*)0x00000001411A3DF0; // wglReleaseTexImageARB
PFNWGLRELEASEVIDEODEVICENVPROC* divagl_wglReleaseVideoDeviceNV
    = (PFNWGLRELEASEVIDEODEVICENVPROC*)0x00000001411A3E80; // wglReleaseVideoDeviceNV
PFNWGLRELEASEVIDEOIMAGENVPROC* divagl_wglReleaseVideoImageNV
    = (PFNWGLRELEASEVIDEOIMAGENVPROC*)0x00000001411A3EA0; // wglReleaseVideoImageNV
PFNWGLRESETFRAMECOUNTNVPROC* divagl_wglResetFrameCountNV
    = (PFNWGLRESETFRAMECOUNTNVPROC*)0x00000001411A3F20; // wglResetFrameCountNV
PFNWGLRESTOREBUFFERREGIONARBPROC* divagl_wglRestoreBufferRegionARB
    = (PFNWGLRESTOREBUFFERREGIONARBPROC*)0x00000001411A3D20; // wglRestoreBufferRegionARB
PFNWGLSAVEBUFFERREGIONARBPROC* divagl_wglSaveBufferRegionARB
    = (PFNWGLSAVEBUFFERREGIONARBPROC*)0x00000001411A3D10; // wglSaveBufferRegionARB
PFNWGLSENDPBUFFERTOVIDEONVPROC* divagl_wglSendPbufferToVideoNV
    = (PFNWGLSENDPBUFFERTOVIDEONVPROC*)0x00000001411A3EB0; // wglSendPbufferToVideoNV
PFNWGLSETPBUFFERATTRIBARBPROC* divagl_wglSetPbufferAttribARB
    = (PFNWGLSETPBUFFERATTRIBARBPROC*)0x00000001411A3E00; // wglSetPbufferAttribARB
PFNWGLSWAPINTERVALEXTPROC* divagl_wglSwapIntervalEXT
    = (PFNWGLSWAPINTERVALEXTPROC*)0x00000001411A3E30; // wglSwapIntervalEXT

PFNGLDRAWBUFFERGLUTPROC* divagl_glDrawBufferGLUT = 0;
PFNGLENABLEGLUTPROC* divagl_glEnableGLUT = 0;
PFNGLFINISHGLUTPROC* divagl_glFinishGLUT = 0;
PFNGLGETERRORGLUTPROC* divagl_glGetErrorGLUT = 0;
PFNGLGETINTEGERVGLUTPROC* divagl_glGetIntegervGLUT = 0;
PFNGLGETSTRINGGLUTPROC* divagl_glGetStringGLUT = 0;
PFNGLPIXELSTOREIGLUTPROC* divagl_glPixelStoreiGLUT = 0;
PFNGLREADBUFFERGLUTPROC* divagl_glReadBufferGLUT = 0;
PFNGLVIEWPORTGLUTPROC* divagl_glViewportGLUT = 0;
PFNWGLCREATECONTEXTGLUTPROC* divagl_wglCreateContextGLUT = 0;
PFNWGLDELETECONTEXTGLUTPROC* divagl_wglDeleteContextGLUT = 0;
PFNWGLGETCURRENTCONTEXTGLUTPROC* divagl_wglGetCurrentContextGLUT = 0;
PFNWGLGETCURRENTDCGLUTPROC* divagl_wglGetCurrentDCGLUT = 0;
PFNWGLGETPROCADDRESSGLUTPROC* divagl_wglGetProcAddressGLUT = 0;
PFNWGLMAKECURRENTGLUTPROC* divagl_wglMakeCurrentGLUT = 0;

PFNGLTEXPARAMETERIVPROC divagl_glTexParameteriv = 0;
PFNGLSTENCILMASKPROC diva_glStencilMask = 0;
PFNGLSTENCILFUNCPROC diva_glStencilFunc = 0;
PFNGLSTENCILOPPROC diva_glStencilOp = 0;
PFNGLDRAWARRAYSINSTANCEDPROC divagl_glDrawArraysInstanced = 0;
PFNGLPRIMITIVERESTARTINDEXPROC divagl_glPrimitiveRestartIndex = 0;
PFNGLGETUNIFORMBLOCKINDEXPROC divagl_glGetUniformBlockIndex = 0;
PFNGLUNIFORMBLOCKBINDINGPROC divagl_glUniformBlockBinding = 0;
PFNGLGETINTEGER64I_VPROC divagl_glGetInteger64i_v = 0;
PFNGLVERTEXATTRIBDIVISORPROC divagl_glVertexAttribDivisor = 0;
PFNGLCLEARDEPTHFPROC divagl_glClearDepthf = 0;
PFNGLGETPROGRAMBINARYPROC divagl_glGetProgramBinary = 0;
PFNGLPROGRAMBINARYPROC divagl_glProgramBinary = 0;
PFNGLPUSHDEBUGGROUPPROC divagl_glPushDebugGroup = 0;
PFNGLPOPDEBUGGROUPPROC divagl_glPopDebugGroup = 0;
PFNGLBUFFERSTORAGEPROC divagl_glBufferStorage = 0;
PFNGLCREATEBUFFERSPROC divagl_glCreateBuffers = 0;
PFNGLNAMEDBUFFERSTORAGEPROC divagl_glNamedBufferStorage = 0;
PFNGLNAMEDBUFFERSUBDATAPROC divagl_glNamedBufferSubData = 0;
PFNGLMAPNAMEDBUFFERPROC divagl_glMapNamedBuffer = 0;
PFNGLMAPNAMEDBUFFERRANGEPROC divagl_glMapNamedBufferRange = 0;
PFNGLUNMAPNAMEDBUFFERPROC divagl_glUnmapNamedBuffer = 0;
PFNGLTEXTURESUBIMAGE2DPROC divagl_glTextureSubImage2D = 0;
PFNGLGENERATETEXTUREMIPMAPPROC divagl_glGenerateTextureMipmap = 0;
PFNGLBINDTEXTUREUNITPROC divagl_glBindTextureUnit = 0;

PFNGLGETBOOLEANVDLLPROC divagl_glGetBooleanvDLL_orig = 0;
PFNGLTEXIMAGE1DDLLPROC divagl_glTexImage1DDLL_orig = 0;
PFNGLTEXIMAGE2DDLLPROC divagl_glTexImage2DDLL_orig = 0;

PFNGLPUSHDEBUGGROUPPROC divagl_glPushDebugGroup_orig = 0;
PFNGLPOPDEBUGGROUPPROC divagl_glPopDebugGroup_orig = 0;

extern size_t opengl32_handle;

static void GLAPIENTRY divagl_glGetBooleanvDLL_impl(GLenum pname, GLboolean* data);
static void GLAPIENTRY divagl_glTexImage1DDLL_impl(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels);
static void GLAPIENTRY divagl_glTexImage2DDLL_impl(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);

static void GLAPIENTRY divagl_glPushDebugGroup_impl(GLenum source, GLuint id, GLsizei length, const GLchar* message);
static void GLAPIENTRY divagl_glPopDebugGroup_impl();

#ifdef DEBUG
static void print_debug_error_old(const char* c, const char* e) {
    if (e)
        printf("DivaGL Deprecated: Debug: %s Error: %s; Time %li\n", c, e, clock());
    else
        printf("DivaGL Deprecated: Debug: %s; Time %li\n", c, clock());
}
#endif

#ifdef DEBUG
static void print_debug_error(const char* c, const char* e) {
    if (e)
        printf("DivaGL: Debug: %s Error: %s; Time %li\n", c, e, clock());
#ifdef PRINT_DEBUG
    else
        printf("DivaGL: Debug: %s; Time %li\n", c, clock());
#endif
}
#endif

void wrap_addresses() {
#ifdef DEBUG
    print_debug_error("Patching tables", 0);
#endif

    for (int i = 0; i < 47; i++)
        if (wrap_addr_dll[i].func != *(size_t*)wrap_addr_dll[i].address) {
            wrap_addr_dll[i].orig_func = *(size_t*)wrap_addr_dll[i].address;
            WRITE_MEMORY(wrap_addr_dll[i].address, uint64_t, wrap_addr_dll[i].func);
        }

#ifdef DEBUG
    print_debug_error("DLL include table patched", 0);
#endif

    for (int i = 0; i < 19; i++)
        if (wrap_addr_glut[i].func != *(size_t*)(glut_handle + wrap_addr_glut[i].address)) {
            wrap_addr_glut[i].orig_func = *(size_t*)(glut_handle + wrap_addr_glut[i].address);
            WRITE_MEMORY(glut_handle + wrap_addr_glut[i].address, uint64_t, wrap_addr_glut[i].func);
        }

    divagl_glDrawBufferGLUT = (PFNGLDRAWBUFFERGLUTPROC*)
        (glut_handle + 0x0002A370); // glDrawBuffer
    divagl_glEnableGLUT = (PFNGLENABLEGLUTPROC*)
        (glut_handle + 0x0002A3D8); // glEnable
    divagl_glFinishGLUT = (PFNGLFINISHGLUTPROC*)
        (glut_handle + 0x0002A358); // glFinish
    divagl_glGetErrorGLUT = (PFNGLGETERRORGLUTPROC*)
        (glut_handle + 0x0002A418); // glGetError
    divagl_glGetIntegervGLUT = (PFNGLGETINTEGERVGLUTPROC*)
        (glut_handle + 0x0002A450); // glGetIntegerv
    divagl_glGetStringGLUT = (PFNGLGETSTRINGGLUTPROC*)
        (glut_handle + 0x0002A360); // glGetString
    divagl_glPixelStoreiGLUT = (PFNGLPIXELSTOREIGLUTPROC*)
        (glut_handle + 0x0002A350); // glPixelStorei
    divagl_glReadBufferGLUT = (PFNGLREADBUFFERGLUTPROC*)
        (glut_handle + 0x0002A378); // glReadBuffer
    divagl_glViewportGLUT = (PFNGLVIEWPORTGLUTPROC*)
        (glut_handle + 0x0002A438); // glViewport
    divagl_wglCreateContextGLUT = (PFNWGLCREATECONTEXTGLUTPROC*)
        (glut_handle + 0x0002A440); // wglCreateContext
    divagl_wglDeleteContextGLUT = (PFNWGLDELETECONTEXTGLUTPROC*)
        (glut_handle + 0x0002A368); // wglDeleteContext
    divagl_wglGetCurrentContextGLUT = (PFNWGLGETCURRENTCONTEXTGLUTPROC*)
        (glut_handle + 0x0002A420); // wglGetCurrentContext
    divagl_wglGetCurrentDCGLUT = (PFNWGLGETCURRENTDCGLUTPROC*)
        (glut_handle + 0x0002A428); // wglGetCurrentDC
    divagl_wglGetProcAddressGLUT = (PFNWGLGETPROCADDRESSGLUTPROC*)
        (glut_handle + 0x0002A448); // wglGetProcAddress
    divagl_wglMakeCurrentGLUT = (PFNWGLMAKECURRENTGLUTPROC*)
        (glut_handle + 0x0002A430); // wglMakeCurrent

#ifdef DEBUG
    print_debug_error("GLUT DLL include table patched", 0);
#endif

    for (int i = 0; i < 44; i++)
        if (wrap_addr[i].func != *(size_t*)wrap_addr[i].address) {
            wrap_addr[i].orig_func = *(size_t*)wrap_addr[i].address;
            WRITE_MEMORY(wrap_addr[i].address, uint64_t, wrap_addr[i].func);
        }

#ifdef DEBUG
    print_debug_error("wglGetProcAddresses table patched", 0);
#endif

}

HOOK(void, FASTCALL, wglGetProcAddresses, 0x0000000140461B50) {
    originalwglGetProcAddresses();

    const char* version = (const char*)glGetStringGLUT(GL_VERSION);
    if (version) {
        int32_t major;
        int32_t minor;
        sscanf_s(version, "%d.%d", &major, &minor);

        DIVA_GL_VERSION_4_1 = (major == 4 && minor >= 1) || major > 4;
        DIVA_GL_VERSION_4_2 = (major == 4 && minor >= 2) || major > 4;
        DIVA_GL_VERSION_4_3 = (major == 4 && minor >= 3) || major > 4;
        DIVA_GL_VERSION_4_4 = (major == 4 && minor >= 4) || major > 4;
        DIVA_GL_VERSION_4_5 = (major == 4 && minor >= 5) || major > 4;
        DIVA_GL_VERSION_4_6 = (major == 4 && minor >= 6) || major > 4;
    }

#define REPLACE_FUNC(name) \
    divagl_##name##_orig = name; \
    WRITE_MEMORY((size_t)&name, intptr_t, (intptr_t)divagl_##name##_impl)

    // 1.0
    glDeleteTextures = glDeleteTexturesDLL;
    glGenTextures = glGenTexturesDLL;

    REPLACE_FUNC(glGetBooleanvDLL);
    REPLACE_FUNC(glTexImage1DDLL);
    REPLACE_FUNC(glTexImage2DDLL);

    glTexParameteriv = (PFNGLTEXPARAMETERIVPROC)GetProcAddress((HMODULE)opengl32_handle, "glTexParameteriv");
    glStencilMask = (PFNGLSTENCILMASKPROC)GetProcAddress((HMODULE)opengl32_handle, "glStencilMask");
    glStencilFunc = (PFNGLSTENCILFUNCPROC)GetProcAddress((HMODULE)opengl32_handle, "glStencilFunc");
    glStencilOp = (PFNGLSTENCILOPPROC)GetProcAddress((HMODULE)opengl32_handle, "glStencilOp");

    // 3.1
    glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)wglGetProcAddressDLL("glDrawArraysInstanced");
    glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC)wglGetProcAddressDLL("glPrimitiveRestartIndex");
    glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)wglGetProcAddressDLL("glGetUniformBlockIndex");
    glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)wglGetProcAddressDLL("glUniformBlockBinding");

    // 3.2
    glGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC)wglGetProcAddressDLL("glGetInteger64i_v");

    // 3.3
    glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC)wglGetProcAddressDLL("glVertexAttribDivisor");

    // 4.1
    if (DIVA_GL_VERSION_4_1) {
        glClearDepthf = (PFNGLCLEARDEPTHFPROC)wglGetProcAddressDLL("glClearDepthf");
        glGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC)wglGetProcAddressDLL("glGetProgramBinary");
        glProgramBinary = (PFNGLPROGRAMBINARYPROC)wglGetProcAddressDLL("glProgramBinary");
    }

    // 4.3
    if (DIVA_GL_VERSION_4_3) {
        divagl_glPushDebugGroup_orig = (PFNGLPUSHDEBUGGROUPPROC)wglGetProcAddressDLL("glPushDebugGroup");
        divagl_glPopDebugGroup_orig = (PFNGLPOPDEBUGGROUPPROC)wglGetProcAddressDLL("glPopDebugGroup");
    }

    glPushDebugGroup = divagl_glPushDebugGroup_impl;
    glPopDebugGroup = divagl_glPopDebugGroup_impl;

    // 4.4
    if (DIVA_GL_VERSION_4_4)
        glBufferStorage = (PFNGLBUFFERSTORAGEPROC)wglGetProcAddressDLL("glBufferStorage");

    // 4.5
    if (DIVA_GL_VERSION_4_5) {
        glCreateBuffers = (PFNGLCREATEBUFFERSPROC)wglGetProcAddressDLL("glCreateBuffers");
        glNamedBufferStorage = (PFNGLNAMEDBUFFERSTORAGEPROC)wglGetProcAddressDLL("glNamedBufferStorage");
        glNamedBufferSubData = (PFNGLNAMEDBUFFERSUBDATAPROC)wglGetProcAddressDLL("glNamedBufferSubData");
        glMapNamedBuffer = (PFNGLMAPNAMEDBUFFERPROC)wglGetProcAddressDLL("glMapNamedBuffer");
        glMapNamedBufferRange = (PFNGLMAPNAMEDBUFFERRANGEPROC)wglGetProcAddressDLL("glMapNamedBufferRange");
        glUnmapNamedBuffer = (PFNGLUNMAPNAMEDBUFFERPROC)wglGetProcAddressDLL("glUnmapNamedBuffer");
        glTextureSubImage2D = (PFNGLTEXTURESUBIMAGE2DPROC)wglGetProcAddressDLL("glTextureSubImage2D");
        glGenerateTextureMipmap = (PFNGLGENERATETEXTUREMIPMAPPROC)wglGetProcAddressDLL("glGenerateTextureMipmap");
        glBindTextureUnit = (PFNGLBINDTEXTUREUNITPROC)wglGetProcAddressDLL("glBindTextureUnit");
    }

#undef REPLACE_FUNC
}

void wrap_patch() {
    // glShadeModel(GL_SMOOTH);
    //WRITE_NOP_11(0x00000001401948CA);

    // glClampColorARB(GL_CLAMP_VERTEX_COLOR_ARB, GL_ZERO);
    // glClampColorARB(GL_CLAMP_FRAGMENT_COLOR_ARB, GL_FIXED_ONLY_ARB);
    // glClampColorARB(GL_CLAMP_READ_COLOR_ARB, GL_FIXED_ONLY_ARB);
    //WRITE_JUMP(0x0000000140194932, 0x000000014019495B);

    INSTALL_HOOK(wglGetProcAddresses);
}

void GLAPIENTRY glAlphaFuncDLL(GLenum func, GLfloat ref) {
    ((PFNGLALPHAFUNCDLLPROC)wrap_addr_dll[GLALPHAFUNCDLL].orig_func)(func, ref);
}

void GLAPIENTRY glBeginDLL(GLenum mode) {
    ((PFNGLBEGINDLLPROC)wrap_addr_dll[GLBEGINDLL].orig_func)(mode);
}

void GLAPIENTRY glColor3fDLL(GLfloat red, GLfloat green, GLfloat blue) {
    ((PFNGLCOLOR3FDLLPROC)wrap_addr_dll[GLCOLOR3FDLL].orig_func)(red, green, blue);
}

void GLAPIENTRY glColor4fDLL(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    ((PFNGLCOLOR4FDLLPROC)wrap_addr_dll[GLCOLOR4FDLL].orig_func)(red, green, blue, alpha);
}

void GLAPIENTRY glColor4ubDLL(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) {
    ((PFNGLCOLOR4UBDLLPROC)wrap_addr_dll[GLCOLOR4UBDLL].orig_func)(red, green, blue, alpha);
}

void GLAPIENTRY glColor4ubvDLL(GLubyte const * v) {
    ((PFNGLCOLOR4UBVDLLPROC)wrap_addr_dll[GLCOLOR4UBVDLL].orig_func)(v);
}

void GLAPIENTRY glColorPointerDLL(GLint size, GLenum type, GLsizei stride, const void * pointer) {
    ((PFNGLCOLORPOINTERDLLPROC)wrap_addr_dll[GLCOLORPOINTERDLL].orig_func)(size, type, stride, pointer);
}

void GLAPIENTRY glDisableClientStateDLL(GLenum array) {
    ((PFNGLDISABLECLIENTSTATEDLLPROC)wrap_addr_dll[GLDISABLECLIENTSTATEDLL].orig_func)(array);
}

void GLAPIENTRY glEnableClientStateDLL(GLenum array) {
    ((PFNGLENABLECLIENTSTATEDLLPROC)wrap_addr_dll[GLENABLECLIENTSTATEDLL].orig_func)(array);
}

void GLAPIENTRY glEndDLL() {
    ((PFNGLENDDLLPROC)wrap_addr_dll[GLENDDLL].orig_func)();
}

void GLAPIENTRY glFogfDLL(GLenum pname, GLfloat param) {
    ((PFNGLFOGFDLLPROC)wrap_addr_dll[GLFOGFDLL].orig_func)(pname, param);
}

void GLAPIENTRY glFogfvDLL(GLenum pname, GLfloat const * params) {
    ((PFNGLFOGFVDLLPROC)wrap_addr_dll[GLFOGFVDLL].orig_func)(pname, params);
}

void GLAPIENTRY glFogiDLL(GLenum pname, GLint param) {
    ((PFNGLFOGIDLLPROC)wrap_addr_dll[GLFOGIDLL].orig_func)(pname, param);
}

void GLAPIENTRY glFrustumDLL(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) {
    mat4 mat;
    mat4_frustrum((float_t)left, (float_t)right, (float_t)bottom, (float_t)top, (float_t)zNear, (float_t)zFar, &mat);
    mat4_transpose(&mat, &mat);
    glMultTransposeMatrixf((const GLfloat*)&mat);
    //((PFNGLFRUSTUMDLLPROC)wrap_addr_dll[GLFRUSTUMDLL].orig_func)(left, right, bottom, top, zNear, zFar);
}

void GLAPIENTRY glGetMaterialfvDLL(GLenum face, GLenum pname, GLfloat * params) {
    ((PFNGLGETMATERIALFVDLLPROC)wrap_addr_dll[GLGETMATERIALFVDLL].orig_func)(face, pname, params);
}

void GLAPIENTRY glGetTexLevelParameterivDLL(GLenum target, GLint level, GLenum pname, GLint * params) {
    ((PFNGLGETTEXLEVELPARAMETERIVDLLPROC)wrap_addr_dll[GLGETTEXLEVELPARAMETERIVDLL].orig_func)(target, level, pname, params);
}

void GLAPIENTRY glGetTexParameterivDLL(GLenum target, GLenum pname, GLint * params) {
    ((PFNGLGETTEXPARAMETERIVDLLPROC)wrap_addr_dll[GLGETTEXPARAMETERIVDLL].orig_func)(target, pname, params);
}

void GLAPIENTRY glLightfvDLL(GLenum light, GLenum pname, GLfloat const * params) {
    ((PFNGLLIGHTFVDLLPROC)wrap_addr_dll[GLLIGHTFVDLL].orig_func)(light, pname, params);
}

void GLAPIENTRY glLightModelfvDLL(GLenum pname, GLfloat const * params) {
    ((PFNGLLIGHTMODELFVDLLPROC)wrap_addr_dll[GLLIGHTMODELFVDLL].orig_func)(pname, params);
}

void GLAPIENTRY glLineWidthDLL(GLfloat width) {
    ((PFNGLLINEWIDTHDLLPROC)wrap_addr_dll[GLLINEWIDTHDLL].orig_func)(width);
}

void GLAPIENTRY glLoadIdentityDLL() {
    ((PFNGLLOADIDENTITYDLLPROC)wrap_addr_dll[GLLOADIDENTITYDLL].orig_func)();
}

void GLAPIENTRY glLoadMatrixfDLL(GLfloat const * m) {
    ((PFNGLLOADMATRIXFDLLPROC)wrap_addr_dll[GLLOADMATRIXFDLL].orig_func)(m);
}

void GLAPIENTRY glMaterialfDLL(GLenum face, GLenum pname, GLfloat param) {
    ((PFNGLMATERIALFDLLPROC)wrap_addr_dll[GLMATERIALFDLL].orig_func)(face, pname, param);
}

void GLAPIENTRY glMaterialfvDLL(GLenum face, GLenum pname, GLfloat const * params) {
    ((PFNGLMATERIALFVDLLPROC)wrap_addr_dll[GLMATERIALFVDLL].orig_func)(face, pname, params);
}

void GLAPIENTRY glMatrixModeDLL(GLenum mode) {
    ((PFNGLMATRIXMODEDLLPROC)wrap_addr_dll[GLMATRIXMODEDLL].orig_func)(mode);
}

void GLAPIENTRY glMultMatrixdDLL(GLdouble const * m) {
    ((PFNGLMULTMATRIXDDLLPROC)wrap_addr_dll[GLMULTMATRIXDDLL].orig_func)(m);
}

void GLAPIENTRY glNormal3fDLL(GLfloat nx, GLfloat ny, GLfloat nz) {
    ((PFNGLNORMAL3FDLLPROC)wrap_addr_dll[GLNORMAL3FDLL].orig_func)(nx, ny, nz);
}

void GLAPIENTRY glNormalPointerDLL(GLenum type, GLsizei stride, const void * pointer) {
    ((PFNGLNORMALPOINTERDLLPROC)wrap_addr_dll[GLNORMALPOINTERDLL].orig_func)(type, stride, pointer);
}

void GLAPIENTRY glOrthoDLL(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) {
    mat4 mat;
    mat4_ortho((float_t)left, (float_t)right, (float_t)bottom, (float_t)top, (float_t)zNear, (float_t)zFar, &mat);
    mat4_transpose(&mat, &mat);
    glMultTransposeMatrixf((const GLfloat*)&mat);
    //((PFNGLORTHODLLPROC)wrap_addr_dll[GLORTHODLL].orig_func)(left, right, bottom, top, zNear, zFar);
}

void GLAPIENTRY glPointSizeDLL(GLfloat size) {
    ((PFNGLPOINTSIZEDLLPROC)wrap_addr_dll[GLPOINTSIZEDLL].orig_func)(size);
}

void GLAPIENTRY glPopAttribDLL() {
    ((PFNGLPOPATTRIBDLLPROC)wrap_addr_dll[GLPOPATTRIBDLL].orig_func)();
}

void GLAPIENTRY glPopClientAttribDLL() {
    ((PFNGLPOPCLIENTATTRIBDLLPROC)wrap_addr_dll[GLPOPCLIENTATTRIBDLL].orig_func)();
}

void GLAPIENTRY glPopMatrixDLL() {
    ((PFNGLPOPMATRIXDLLPROC)wrap_addr_dll[GLPOPMATRIXDLL].orig_func)();
}

void GLAPIENTRY glPushAttribDLL(GLbitfield mask) {
    ((PFNGLPUSHATTRIBDLLPROC)wrap_addr_dll[GLPUSHATTRIBDLL].orig_func)(mask);
}

void GLAPIENTRY glPushClientAttribDLL(GLbitfield mask) {
    ((PFNGLPUSHCLIENTATTRIBDLLPROC)wrap_addr_dll[GLPUSHCLIENTATTRIBDLL].orig_func)(mask);
}

void GLAPIENTRY glPushMatrixDLL() {
    ((PFNGLPUSHMATRIXDLLPROC)wrap_addr_dll[GLPUSHMATRIXDLL].orig_func)();
}

void GLAPIENTRY glRotatefDLL(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
    float_t c = cosf(angle * DEG_TO_RAD_FLOAT);
    float_t s = sinf(angle * DEG_TO_RAD_FLOAT);
    float_t t = 1.0f - c;

    mat4 mat;
    mat.row0 = { t * x * x + c, t * x * y + z * s, t * x * z - y * s, 0.0f };
    mat.row1 = { t * y * x - z * s, t * y * y + c, t * y * z + x * s, 0.0f };
    mat.row2 = { t * z * x + y * s, t * z * y - x * s, t * z * z + c, 0.0f };
    mat.row3 = { 0.0f, 0.0f, 0.0f, 1.0f };
    mat4_transpose(&mat, &mat);
    glMultTransposeMatrixf((const GLfloat*)&mat);
    //((PFNGLROTATEFDLLPROC)wrap_addr_dll[GLROTATEFDLL].orig_func)(angle, x, y, z);
}

void GLAPIENTRY glScalefDLL(GLfloat x, GLfloat y, GLfloat z) {
    mat4 mat;
    mat4_scale(x, y, z, &mat);
    mat4_transpose(&mat, &mat);
    glMultTransposeMatrixf((const GLfloat*)&mat);
    //((PFNGLSCALEFDLLPROC)wrap_addr_dll[GLSCALEFDLL].orig_func)(x, y, z);
}

void GLAPIENTRY glShadeModelDLL(GLenum mode) {
    ((PFNGLSHADEMODELDLLPROC)wrap_addr_dll[GLSHADEMODELDLL].orig_func)(mode);
}

void GLAPIENTRY glTexCoord2fDLL(GLfloat s, GLfloat t) {
    ((PFNGLTEXCOORD2FDLLPROC)wrap_addr_dll[GLTEXCOORD2FDLL].orig_func)(s, t);
}

void GLAPIENTRY glTexCoordPointerDLL(GLint size, GLenum type, GLsizei stride, const void * pointer) {
    ((PFNGLTEXCOORDPOINTERDLLPROC)wrap_addr_dll[GLTEXCOORDPOINTERDLL].orig_func)(size, type, stride, pointer);
}

void GLAPIENTRY glTexEnvfDLL(GLenum target, GLenum pname, GLfloat param) {
    ((PFNGLTEXENVFDLLPROC)wrap_addr_dll[GLTEXENVFDLL].orig_func)(target, pname, param);
}

void GLAPIENTRY glTexEnviDLL(GLenum target, GLenum pname, GLint param) {
    ((PFNGLTEXENVIDLLPROC)wrap_addr_dll[GLTEXENVIDLL].orig_func)(target, pname, param);
}

void GLAPIENTRY glTranslatefDLL(GLfloat x, GLfloat y, GLfloat z) {
    mat4 mat;
    mat4_translate(x, y, z, &mat);
    mat4_transpose(&mat, &mat);
    glMultTransposeMatrixf((const GLfloat*)&mat);
    //((PFNGLTRANSLATEFDLLPROC)wrap_addr_dll[GLTRANSLATEFDLL].orig_func)(x, y, z);
}

void GLAPIENTRY glVertex3fDLL(GLfloat x, GLfloat y, GLfloat z) {
    ((PFNGLVERTEX3FDLLPROC)wrap_addr_dll[GLVERTEX3FDLL].orig_func)(x, y, z);
}

void GLAPIENTRY glVertex3fvDLL(GLfloat const * v) {
    ((PFNGLVERTEX3FVDLLPROC)wrap_addr_dll[GLVERTEX3FVDLL].orig_func)(v);
}

void GLAPIENTRY glVertexPointerDLL(GLint size, GLenum type, GLsizei stride, const void * pointer) {
    ((PFNGLVERTEXPOINTERDLLPROC)wrap_addr_dll[GLVERTEXPOINTERDLL].orig_func)(size, type, stride, pointer);
}

void GLAPIENTRY glBindBufferARB(GLenum target, GLuint buffer) {
    ((PFNGLBINDBUFFERARBPROC)wrap_addr[GLBINDBUFFERARB].orig_func)(target, buffer);
}

void GLAPIENTRY glBindBufferBaseNV(GLenum target, GLuint index, GLuint buffer) {
    ((PFNGLBINDBUFFERBASENVPROC)wrap_addr[GLBINDBUFFERBASENV].orig_func)(target, index, buffer);
}

void GLAPIENTRY glBindFramebufferEXT(GLenum target, GLuint framebuffer) {
    ((PFNGLBINDFRAMEBUFFEREXTPROC)wrap_addr[GLBINDFRAMEBUFFEREXT].orig_func)(target, framebuffer);
}

void GLAPIENTRY glBindMultiTextureEXT(GLenum texunit, GLenum target, GLuint texture) {
    ((PFNGLBINDMULTITEXTUREEXTPROC)wrap_addr[GLBINDMULTITEXTUREEXT].orig_func)(texunit, target, texture);
}

void GLAPIENTRY glBindRenderbufferEXT(GLenum target, GLuint renderbuffer) {
    ((PFNGLBINDRENDERBUFFEREXTPROC)wrap_addr[GLBINDRENDERBUFFEREXT].orig_func)(target, renderbuffer);
}

void GLAPIENTRY glBufferDataARB(GLenum target, GLsizeiptrARB size, const void * data, GLenum usage) {
    ((PFNGLBUFFERDATAARBPROC)wrap_addr[GLBUFFERDATAARB].orig_func)(target, size, data, usage);
}

void GLAPIENTRY glClampColorARB(GLenum target, GLenum clamp) {
    ((PFNGLCLAMPCOLORARBPROC)wrap_addr[GLCLAMPCOLORARB].orig_func)(target, clamp);
}

void GLAPIENTRY glClientActiveTexture(GLenum texture) {
    ((PFNGLCLIENTACTIVETEXTUREPROC)wrap_addr[GLCLIENTACTIVETEXTURE].orig_func)(texture);
}

void GLAPIENTRY glCopyMultiTexSubImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    ((PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC)wrap_addr[GLCOPYMULTITEXSUBIMAGE2DEXT].orig_func)(texunit, target, level, xoffset, yoffset, x, y, width, height);
}

void GLAPIENTRY glDeleteBuffersARB(GLsizei n, GLuint const * buffers) {
    ((PFNGLDELETEBUFFERSARBPROC)wrap_addr[GLDELETEBUFFERSARB].orig_func)(n, buffers);
}

void GLAPIENTRY glDeleteFramebuffersEXT(GLsizei n, GLuint const * framebuffers) {
    ((PFNGLDELETEFRAMEBUFFERSEXTPROC)wrap_addr[GLDELETEFRAMEBUFFERSEXT].orig_func)(n, framebuffers);
}

void GLAPIENTRY glDeleteRenderbuffersEXT(GLsizei n, GLuint const * renderbuffers) {
    ((PFNGLDELETERENDERBUFFERSEXTPROC)wrap_addr[GLDELETERENDERBUFFERSEXT].orig_func)(n, renderbuffers);
}

void GLAPIENTRY glDisableVertexAttribArrayARB(GLuint index) {
    ((PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)wrap_addr[GLDISABLEVERTEXATTRIBARRAYARB].orig_func)(index);
}

void GLAPIENTRY glEnableVertexAttribArrayARB(GLuint index) {
    ((PFNGLENABLEVERTEXATTRIBARRAYARBPROC)wrap_addr[GLENABLEVERTEXATTRIBARRAYARB].orig_func)(index);
}

void GLAPIENTRY glFramebufferRenderbufferEXT(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {
    ((PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)wrap_addr[GLFRAMEBUFFERRENDERBUFFEREXT].orig_func)(target, attachment, renderbuffertarget, renderbuffer);
}

void GLAPIENTRY glFramebufferTexture2DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    ((PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)wrap_addr[GLFRAMEBUFFERTEXTURE2DEXT].orig_func)(target, attachment, textarget, texture, level);
}

void GLAPIENTRY glGenFramebuffersEXT(GLsizei n, GLuint * framebuffers) {
    ((PFNGLGENFRAMEBUFFERSEXTPROC)wrap_addr[GLGENFRAMEBUFFERSEXT].orig_func)(n, framebuffers);
}

void GLAPIENTRY glGenRenderbuffersEXT(GLsizei n, GLuint * renderbuffers) {
    ((PFNGLGENRENDERBUFFERSEXTPROC)wrap_addr[GLGENRENDERBUFFERSEXT].orig_func)(n, renderbuffers);
}

void GLAPIENTRY glGetProgramEnvParameterfvARB(GLenum target, GLuint index, GLfloat * params) {
    ((PFNGLGETPROGRAMENVPARAMETERFVARBPROC)wrap_addr[GLGETPROGRAMENVPARAMETERFVARB].orig_func)(target, index, params);
}

void GLAPIENTRY glGetProgramivARB(GLenum target, GLenum pname, GLint * params) {
    switch (pname) {
    case GL_VERTEX_PROGRAM_ARB:
    case GL_FRAGMENT_PROGRAM_ARB:
        if (params)
            *params = 0;
        return;
    }
    ((PFNGLGETPROGRAMIVARBPROC)wrap_addr[GLGETPROGRAMIVARB].orig_func)(target, pname, params);
}

void GLAPIENTRY glGetTextureImageEXT(GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, void * pixels) {
    ((PFNGLGETTEXTUREIMAGEEXTPROC)wrap_addr[GLGETTEXTUREIMAGEEXT].orig_func)(texture, target, level, format, type, pixels);
}

GLboolean GLAPIENTRY glIsBufferARB(GLuint buffer) {
    return ((PFNGLISBUFFERARBPROC)wrap_addr[GLISBUFFERARB].orig_func)(buffer);
}

void GLAPIENTRY glLoadTransposeMatrixf(GLfloat const * m) {
    ((PFNGLLOADTRANSPOSEMATRIXFPROC)wrap_addr[GLLOADTRANSPOSEMATRIXF].orig_func)(m);
}

void * GLAPIENTRY glMapNamedBufferEXT(GLuint buffer, GLenum access) {
    return ((PFNGLMAPNAMEDBUFFEREXTPROC)wrap_addr[GLMAPNAMEDBUFFEREXT].orig_func)(buffer, access);
}

void GLAPIENTRY glMultiTexCoord2f(GLenum target, GLfloat s, GLfloat t) {
    ((PFNGLMULTITEXCOORD2FPROC)wrap_addr[GLMULTITEXCOORD2F].orig_func)(target, s, t);
}

void GLAPIENTRY glMultiTexCoord2fv(GLenum target, GLfloat const * v) {
    ((PFNGLMULTITEXCOORD2FVPROC)wrap_addr[GLMULTITEXCOORD2FV].orig_func)(target, v);
}

void GLAPIENTRY glMultTransposeMatrixf(GLfloat const * m) {
    ((PFNGLMULTTRANSPOSEMATRIXFPROC)wrap_addr[GLMULTTRANSPOSEMATRIXF].orig_func)(m);
}

void GLAPIENTRY glNamedBufferDataEXT(GLuint buffer, GLsizeiptr size, const void * data, GLenum usage) {
    ((PFNGLNAMEDBUFFERDATAEXTPROC)wrap_addr[GLNAMEDBUFFERDATAEXT].orig_func)(buffer, size, data, usage);
}

void GLAPIENTRY glNamedBufferSubDataEXT(GLuint buffer, GLintptr offset, GLsizeiptr size, const void * data) {
    ((PFNGLNAMEDBUFFERSUBDATAEXTPROC)wrap_addr[GLNAMEDBUFFERSUBDATAEXT].orig_func)(buffer, offset, size, data);
}

void GLAPIENTRY glPointParameterf(GLenum pname, GLfloat param) {
    ((PFNGLPOINTPARAMETERFPROC)wrap_addr[GLPOINTPARAMETERF].orig_func)(pname, param);
}

void GLAPIENTRY glPointParameterfv(GLenum pname, GLfloat const * params) {
    ((PFNGLPOINTPARAMETERFVPROC)wrap_addr[GLPOINTPARAMETERFV].orig_func)(pname, params);
}

void GLAPIENTRY glPointParameteri(GLenum pname, GLint param) {
    ((PFNGLPOINTPARAMETERIPROC)wrap_addr[GLPOINTPARAMETERI].orig_func)(pname, param);
}

void GLAPIENTRY glPrimitiveRestartIndexNV(GLuint index) {
    glPrimitiveRestartIndex(index);
    //((PFNGLPRIMITIVERESTARTINDEXNVPROC)wrap_addr[GLPRIMITIVERESTARTINDEXNV].orig_func)(index);
}

void GLAPIENTRY glProgramBufferParametersfvNV(GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, GLfloat const * params) {
    ((PFNGLPROGRAMBUFFERPARAMETERSFVNVPROC)wrap_addr[GLPROGRAMBUFFERPARAMETERSFVNV].orig_func)(target, bindingIndex, wordIndex, count, params);
}

void GLAPIENTRY glProgramEnvParameter4fARB(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    ((PFNGLPROGRAMENVPARAMETER4FARBPROC)wrap_addr[GLPROGRAMENVPARAMETER4FARB].orig_func)(target, index, x, y, z, w);
}

void GLAPIENTRY glProgramEnvParameter4fvARB(GLenum target, GLuint index, GLfloat const * params) {
    ((PFNGLPROGRAMENVPARAMETER4FVARBPROC)wrap_addr[GLPROGRAMENVPARAMETER4FVARB].orig_func)(target, index, params);
}

void GLAPIENTRY glProgramEnvParameters4fvEXT(GLenum target, GLuint index, GLsizei count, GLfloat const * params) {
    ((PFNGLPROGRAMENVPARAMETERS4FVEXTPROC)wrap_addr[GLPROGRAMENVPARAMETERS4FVEXT].orig_func)(target, index, count, params);
}

void GLAPIENTRY glProgramLocalParameter4fARB(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    ((PFNGLPROGRAMLOCALPARAMETER4FARBPROC)wrap_addr[GLPROGRAMLOCALPARAMETER4FARB].orig_func)(target, index, x, y, z, w);
}

void GLAPIENTRY glProgramLocalParameter4fvARB(GLenum target, GLuint index, GLfloat const * params) {
    ((PFNGLPROGRAMLOCALPARAMETER4FVARBPROC)wrap_addr[GLPROGRAMLOCALPARAMETER4FVARB].orig_func)(target, index, params);
}

void GLAPIENTRY glProgramLocalParameters4fvEXT(GLenum target, GLuint index, GLsizei count, GLfloat const * params) {
    ((PFNGLPROGRAMLOCALPARAMETERS4FVEXTPROC)wrap_addr[GLPROGRAMLOCALPARAMETERS4FVEXT].orig_func)(target, index, count, params);
}

void GLAPIENTRY glRenderbufferStorageEXT(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {
    ((PFNGLRENDERBUFFERSTORAGEEXTPROC)wrap_addr[GLRENDERBUFFERSTORAGEEXT].orig_func)(target, internalformat, width, height);
}

void GLAPIENTRY glRenderbufferStorageMultisampleCoverageNV(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height) {
    ((PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC)wrap_addr[GLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENV].orig_func)(target, coverageSamples, colorSamples, internalformat, width, height);
}

GLboolean GLAPIENTRY glUnmapNamedBufferEXT(GLuint buffer) {
    return ((PFNGLUNMAPNAMEDBUFFEREXTPROC)wrap_addr[GLUNMAPNAMEDBUFFEREXT].orig_func)(buffer);
}

void GLAPIENTRY glVertexAttribPointerARB(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer) {
    ((PFNGLVERTEXATTRIBPOINTERARBPROC)wrap_addr[GLVERTEXATTRIBPOINTERARB].orig_func)(index, size, type, normalized, stride, pointer);
}

void GLAPIENTRY glBeginGLUT(GLenum mode) {
    ((PFNGLBEGINGLUTPROC)wrap_addr_glut[GLBEGINGLUT].orig_func)(mode);
}

void GLAPIENTRY glBitmapGLUT(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, GLubyte const * bitmap) {
    ((PFNGLBITMAPGLUTPROC)wrap_addr_glut[GLBITMAPGLUT].orig_func)(width, height, xorig, yorig, xmove, ymove, bitmap);
}

void GLAPIENTRY glEndGLUT() {
    ((PFNGLENDGLUTPROC)wrap_addr_glut[GLENDGLUT].orig_func)();
}

void GLAPIENTRY glEvalMesh2GLUT(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2) {
    ((PFNGLEVALMESH2GLUTPROC)wrap_addr_glut[GLEVALMESH2GLUT].orig_func)(mode, i1, i2, j1, j2);
}

void GLAPIENTRY glMap2fGLUT(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, GLfloat const * points) {
    ((PFNGLMAP2FGLUTPROC)wrap_addr_glut[GLMAP2FGLUT].orig_func)(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

void GLAPIENTRY glMapGrid2fGLUT(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2) {
    ((PFNGLMAPGRID2FGLUTPROC)wrap_addr_glut[GLMAPGRID2FGLUT].orig_func)(un, u1, u2, vn, v1, v2);
}

void GLAPIENTRY glNormal3fGLUT(GLfloat nx, GLfloat ny, GLfloat nz) {
    ((PFNGLNORMAL3FGLUTPROC)wrap_addr_glut[GLNORMAL3FGLUT].orig_func)(nx, ny, nz);
}

void GLAPIENTRY glNormal3fvGLUT(GLfloat const * v) {
    ((PFNGLNORMAL3FVGLUTPROC)wrap_addr_glut[GLNORMAL3FVGLUT].orig_func)(v);
}

void GLAPIENTRY glPolygonModeGLUT(GLenum face, GLenum mode) {
    ((PFNGLPOLYGONMODEGLUTPROC)wrap_addr_glut[GLPOLYGONMODEGLUT].orig_func)(face, mode);
}

void GLAPIENTRY glPopAttribGLUT() {
    ((PFNGLPOPATTRIBGLUTPROC)wrap_addr_glut[GLPOPATTRIBGLUT].orig_func)();
}

void GLAPIENTRY glPopMatrixGLUT() {
    ((PFNGLPOPMATRIXGLUTPROC)wrap_addr_glut[GLPOPMATRIXGLUT].orig_func)();
}

void GLAPIENTRY glPushAttribGLUT(GLbitfield mask) {
    ((PFNGLPUSHATTRIBGLUTPROC)wrap_addr_glut[GLPUSHATTRIBGLUT].orig_func)(mask);
}

void GLAPIENTRY glPushMatrixGLUT() {
    ((PFNGLPUSHMATRIXGLUTPROC)wrap_addr_glut[GLPUSHMATRIXGLUT].orig_func)();
}

void GLAPIENTRY glRotatefGLUT(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
    float_t c = cosf(angle * DEG_TO_RAD_FLOAT);
    float_t s = sinf(angle * DEG_TO_RAD_FLOAT);
    float_t t = 1.0f - c;

    mat4 mat;
    mat.row0 = { t * x * x + c, t * x * y + z * s, t * x * z - y * s, 0.0f };
    mat.row1 = { t * y * x - z * s, t * y * y + c, t * y * z + x * s, 0.0f };
    mat.row2 = { t * z * x + y * s, t * z * y - x * s, t * z * z + c, 0.0f };
    mat.row3 = { 0.0f, 0.0f, 0.0f, 1.0f };
    mat4_transpose(&mat, &mat);
    glMultTransposeMatrixf((const GLfloat*)&mat);
    //((PFNGLROTATEFGLUTPROC)wrap_addr_glut[GLROTATEFGLUT].orig_func)(angle, x, y, z);
}

void GLAPIENTRY glScalefGLUT(GLfloat x, GLfloat y, GLfloat z) {
    mat4 mat;
    mat4_scale(x, y, z, &mat);
    mat4_transpose(&mat, &mat);
    glMultTransposeMatrixf((const GLfloat*)&mat);
    //((PFNGLSCALEFGLUTPROC)wrap_addr_glut[GLSCALEFGLUT].orig_func)(x, y, z);
}

void GLAPIENTRY glTranslatefGLUT(GLfloat x, GLfloat y, GLfloat z) {
    mat4 mat;
    mat4_translate(x, y, z, &mat);
    mat4_transpose(&mat, &mat);
    glMultTransposeMatrixf((const GLfloat*)&mat);
    //((PFNGLTRANSLATEFGLUTPROC)wrap_addr_glut[GLTRANSLATEFGLUT].orig_func)(x, y, z);
}

void GLAPIENTRY glVertex2fGLUT(GLfloat x, GLfloat y) {
    ((PFNGLVERTEX2FGLUTPROC)wrap_addr_glut[GLVERTEX2FGLUT].orig_func)(x, y);
}

void GLAPIENTRY glVertex3fGLUT(GLfloat x, GLfloat y, GLfloat z) {
    ((PFNGLVERTEX3FGLUTPROC)wrap_addr_glut[GLVERTEX3FGLUT].orig_func)(x, y, z);
}

void GLAPIENTRY glVertex3fvGLUT(GLfloat const * v) {
    ((PFNGLVERTEX3FVGLUTPROC)wrap_addr_glut[GLVERTEX3FVGLUT].orig_func)(v);
}

static void GLAPIENTRY divagl_glGetBooleanvDLL_impl(GLenum pname, GLboolean* data) {
    switch (pname) {
    case GL_VERTEX_PROGRAM_ARB:
    case GL_FRAGMENT_PROGRAM_ARB:
        if (data)
            *data = GL_TRUE;
        return;
    }
    divagl_glGetBooleanvDLL_orig(pname, data);
}

static void GLAPIENTRY divagl_glTexImage1DDLL_impl(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels) {
    GLint _internalformat;
    GLint _format;
    switch (internalformat) {
    case GL_LUMINANCE_ALPHA16F_ARB:
        _internalformat = GL_RG16F;
        _format = GL_RG;
        break;
    default:
        _internalformat = internalformat;
        _format = format;
        break;
    }

    divagl_glTexImage1DDLL_orig(target, level, _internalformat, width, border, _format, type, pixels);

    switch (internalformat) {
    case GL_LUMINANCE_ALPHA16F_ARB:
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_R, GL_RED);
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_G, GL_RED);
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_B, GL_RED);
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_A, GL_GREEN);
        break;
    }
}

static void GLAPIENTRY divagl_glTexImage2DDLL_impl(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels) {
    GLint _internalformat;
    switch (internalformat) {
    case GL_ALPHA8:
        _internalformat = GL_R8;
        break;
    case GL_LUMINANCE8:
        _internalformat = GL_R8;
        break;
    case GL_LUMINANCE8_ALPHA8:
        _internalformat = GL_RG8;
        break;
    case GL_INTENSITY8:
        _internalformat = GL_R8;
        break;
    default:
        _internalformat = internalformat;
        break;
    }

    divagl_glTexImage2DDLL_orig(target, level, _internalformat, width, height, border, format, type, pixels);

    switch (internalformat) {
    case GL_ALPHA8:
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_R, GL_ZERO);
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_G, GL_ZERO);
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_B, GL_ZERO);
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_A, GL_RED);
        break;
    case GL_LUMINANCE8:
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_R, GL_RED);
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_G, GL_RED);
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_B, GL_RED);
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_A, GL_ONE);
        break;
    case GL_LUMINANCE8_ALPHA8:
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_R, GL_RED);
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_G, GL_RED);
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_B, GL_RED);
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_A, GL_GREEN);
        break;
    case GL_INTENSITY8:
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_R, GL_RED);
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_G, GL_RED);
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_B, GL_RED);
        glTexParameteriDLL(target, GL_TEXTURE_SWIZZLE_A, GL_RED);
        break;
    }
}

static void GLAPIENTRY divagl_glPushDebugGroup_impl(GLenum source, GLuint id, GLsizei length, const GLchar* message) {
    if (DIVA_GL_VERSION_4_3)
        return divagl_glPushDebugGroup_orig(source, id, length, message);
}

static void GLAPIENTRY divagl_glPopDebugGroup_impl() {
    if (DIVA_GL_VERSION_4_3)
        return divagl_glPopDebugGroup_orig();
}
