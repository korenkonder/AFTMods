/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "gl.hpp"
#include <Windows.h>

typedef void (GLAPIENTRY * PFNGLBINDTEXTUREDLLPROC) (GLenum target, GLuint texture);
typedef void (GLAPIENTRY * PFNGLBLENDFUNCDLLPROC) (GLenum sfactor, GLenum dfactor);
typedef void (GLAPIENTRY * PFNGLCLEARDLLPROC) (GLbitfield mask);
typedef void (GLAPIENTRY * PFNGLCLEARCOLORDLLPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (GLAPIENTRY * PFNGLCLEARDEPTHDLLPROC) (GLdouble depth);
typedef void (GLAPIENTRY * PFNGLCLEARSTENCILDLLPROC) (GLint s);
typedef void (GLAPIENTRY * PFNGLCOLORMASKDLLPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef void (GLAPIENTRY * PFNGLCOPYTEXIMAGE2DDLLPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (GLAPIENTRY * PFNGLCOPYTEXSUBIMAGE2DDLLPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY * PFNGLCULLFACEDLLPROC) (GLenum mode);
typedef void (GLAPIENTRY * PFNGLDELETETEXTURESDLLPROC) (GLsizei n, GLuint const * textures);
typedef void (GLAPIENTRY * PFNGLDEPTHFUNCDLLPROC) (GLenum func);
typedef void (GLAPIENTRY * PFNGLDEPTHMASKDLLPROC) (GLboolean flag);
typedef void (GLAPIENTRY * PFNGLDISABLEDLLPROC) (GLenum cap);
typedef void (GLAPIENTRY * PFNGLDRAWARRAYSDLLPROC) (GLenum mode, GLint first, GLsizei count);
typedef void (GLAPIENTRY * PFNGLDRAWBUFFERDLLPROC) (GLenum buf);
typedef void (GLAPIENTRY * PFNGLDRAWELEMENTSDLLPROC) (GLenum mode, GLsizei count, GLenum type, const void * indices);
typedef void (GLAPIENTRY * PFNGLENABLEDLLPROC) (GLenum cap);
typedef void (GLAPIENTRY * PFNGLFINISHDLLPROC) ();
typedef void (GLAPIENTRY * PFNGLFRONTFACEDLLPROC) (GLenum mode);
typedef void (GLAPIENTRY * PFNGLGENTEXTURESDLLPROC) (GLsizei n, GLuint * textures);
typedef void (GLAPIENTRY * PFNGLGETBOOLEANVDLLPROC) (GLenum pname, GLboolean * data);
typedef GLenum (GLAPIENTRY * PFNGLGETERRORDLLPROC) ();
typedef void (GLAPIENTRY * PFNGLGETFLOATVDLLPROC) (GLenum pname, GLfloat * data);
typedef void (GLAPIENTRY * PFNGLGETINTEGERVDLLPROC) (GLenum pname, GLint * data);
typedef void (GLAPIENTRY * PFNGLGETTEXIMAGEDLLPROC) (GLenum target, GLint level, GLenum format, GLenum type, void * pixels);
typedef GLboolean (GLAPIENTRY * PFNGLISENABLEDDLLPROC) (GLenum cap);
typedef void (GLAPIENTRY * PFNGLPIXELSTOREIDLLPROC) (GLenum pname, GLint param);
typedef void (GLAPIENTRY * PFNGLPOLYGONMODEDLLPROC) (GLenum face, GLenum mode);
typedef void (GLAPIENTRY * PFNGLREADBUFFERDLLPROC) (GLenum src);
typedef void (GLAPIENTRY * PFNGLREADPIXELSDLLPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels);
typedef void (GLAPIENTRY * PFNGLSCISSORDLLPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY * PFNGLTEXIMAGE1DDLLPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLTEXIMAGE2DDLLPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLTEXPARAMETERFDLLPROC) (GLenum target, GLenum pname, GLfloat param);
typedef void (GLAPIENTRY * PFNGLTEXPARAMETERFVDLLPROC) (GLenum target, GLenum pname, GLfloat const * params);
typedef void (GLAPIENTRY * PFNGLTEXPARAMETERIDLLPROC) (GLenum target, GLenum pname, GLint param);
typedef void (GLAPIENTRY * PFNGLTEXSUBIMAGE2DDLLPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLVIEWPORTDLLPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
typedef PROC (GLAPIENTRY * PFNWGLGETPROCADDRESSDLLPROC) (LPCSTR lpszProc);

typedef void (GLAPIENTRY * PFNGLACTIVESTENCILFACEEXTPROC) (GLenum face);
typedef void (GLAPIENTRY * PFNGLACTIVETEXTUREPROC) (GLenum texture);
typedef void (GLAPIENTRY * PFNGLACTIVETEXTUREARBPROC) (GLenum texture);
typedef void (GLAPIENTRY * PFNGLACTIVEVARYINGNVPROC) (GLuint program, GLchar const * name);
typedef GLboolean (GLAPIENTRY * PFNGLAREPROGRAMSRESIDENTNVPROC) (GLsizei n, GLuint const * programs, GLboolean * residences);
typedef GLboolean (GLAPIENTRY * PFNGLARETEXTURESRESIDENTEXTPROC) (GLsizei n, GLuint const * textures, GLboolean * residences);
typedef void (GLAPIENTRY * PFNGLARRAYELEMENTEXTPROC) (GLint i);
typedef void (GLAPIENTRY * PFNGLATTACHOBJECTARBPROC) (GLhandleARB containerObj, GLhandleARB obj);
typedef void (GLAPIENTRY * PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (GLAPIENTRY * PFNGLBEGINCONDITIONALRENDERPROC) (GLuint id, GLenum mode);
typedef void (GLAPIENTRY * PFNGLBEGINCONDITIONALRENDERNVPROC) (GLuint id, GLenum mode);
typedef void (GLAPIENTRY * PFNGLBEGINOCCLUSIONQUERYNVPROC) (GLuint id);
typedef void (GLAPIENTRY * PFNGLBEGINQUERYPROC) (GLenum target, GLuint id);
typedef void (GLAPIENTRY * PFNGLBEGINQUERYARBPROC) (GLenum target, GLuint id);
typedef void (GLAPIENTRY * PFNGLBEGINTRANSFORMFEEDBACKPROC) (GLenum primitiveMode);
typedef void (GLAPIENTRY * PFNGLBEGINTRANSFORMFEEDBACKNVPROC) (GLenum primitiveMode);
typedef void (GLAPIENTRY * PFNGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint index, GLchar const * name);
typedef void (GLAPIENTRY * PFNGLBINDATTRIBLOCATIONARBPROC) (GLhandleARB programObj, GLuint index, GLcharARB const * name);
typedef void (GLAPIENTRY * PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (GLAPIENTRY * PFNGLBINDBUFFERBASEPROC) (GLenum target, GLuint index, GLuint buffer);
typedef void (GLAPIENTRY * PFNGLBINDBUFFEROFFSETNVPROC) (GLenum target, GLuint index, GLuint buffer, GLintptr offset);
typedef void (GLAPIENTRY * PFNGLBINDBUFFERRANGEPROC) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (GLAPIENTRY * PFNGLBINDBUFFERRANGENVPROC) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (GLAPIENTRY * PFNGLBINDFRAGDATALOCATIONPROC) (GLuint program, GLuint color, GLchar const * name);
typedef void (GLAPIENTRY * PFNGLBINDFRAGDATALOCATIONEXTPROC) (GLuint program, GLuint color, GLchar const * name);
typedef void (GLAPIENTRY * PFNGLBINDFRAMEBUFFERPROC) (GLenum target, GLuint framebuffer);
typedef void (GLAPIENTRY * PFNGLBINDPROGRAMARBPROC) (GLenum target, GLuint program);
typedef void (GLAPIENTRY * PFNGLBINDPROGRAMNVPROC) (GLenum target, GLuint id);
typedef void (GLAPIENTRY * PFNGLBINDRENDERBUFFERPROC) (GLenum target, GLuint renderbuffer);
typedef void (GLAPIENTRY * PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
typedef void (GLAPIENTRY * PFNGLBINDTEXTUREEXTPROC) (GLenum target, GLuint texture);
typedef void (GLAPIENTRY * PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void (GLAPIENTRY * PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (GLAPIENTRY * PFNGLBLENDCOLOREXTPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (GLAPIENTRY * PFNGLBLENDEQUATIONPROC) (GLenum mode);
typedef void (GLAPIENTRY * PFNGLBLENDEQUATIONEXTPROC) (GLenum mode);
typedef void (GLAPIENTRY * PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum modeRGB, GLenum modeAlpha);
typedef void (GLAPIENTRY * PFNGLBLENDEQUATIONSEPARATEEXTPROC) (GLenum modeRGB, GLenum modeAlpha);
typedef void (GLAPIENTRY * PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void (GLAPIENTRY * PFNGLBLENDFUNCSEPARATEEXTPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void (GLAPIENTRY * PFNGLBLITFRAMEBUFFERPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void (GLAPIENTRY * PFNGLBLITFRAMEBUFFEREXTPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void (GLAPIENTRY * PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void * data, GLenum usage);
typedef void (GLAPIENTRY * PFNGLBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, const void * data);
typedef void (GLAPIENTRY * PFNGLBUFFERSUBDATAARBPROC) (GLenum target, GLintptrARB offset, GLsizeiptrARB size, const void * data);
typedef GLenum (GLAPIENTRY * PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum target);
typedef GLenum (GLAPIENTRY * PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC) (GLenum target);
typedef GLenum (GLAPIENTRY * PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC) (GLuint framebuffer, GLenum target);
typedef void (GLAPIENTRY * PFNGLCLEARBUFFERFIPROC) (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef void (GLAPIENTRY * PFNGLCLEARBUFFERFVPROC) (GLenum buffer, GLint drawbuffer, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLCLEARBUFFERIVPROC) (GLenum buffer, GLint drawbuffer, GLint const * value);
typedef void (GLAPIENTRY * PFNGLCLEARBUFFERUIVPROC) (GLenum buffer, GLint drawbuffer, GLuint const * value);
typedef void (GLAPIENTRY * PFNGLCLEARCOLORIIEXTPROC) (GLint red, GLint green, GLint blue, GLint alpha);
typedef void (GLAPIENTRY * PFNGLCLEARCOLORIUIEXTPROC) (GLuint red, GLuint green, GLuint blue, GLuint alpha);
typedef void (GLAPIENTRY * PFNGLCLEARDEPTHDNVPROC) (GLdouble depth);
typedef void (GLAPIENTRY * PFNGLCLIENTACTIVETEXTUREARBPROC) (GLenum texture);
typedef void (GLAPIENTRY * PFNGLCLIENTATTRIBDEFAULTEXTPROC) (GLbitfield mask);
typedef void (GLAPIENTRY * PFNGLCOLOR3HNVPROC) (GLhalfNV red, GLhalfNV green, GLhalfNV blue);
typedef void (GLAPIENTRY * PFNGLCOLOR3HVNVPROC) (GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLCOLOR4HNVPROC) (GLhalfNV red, GLhalfNV green, GLhalfNV blue, GLhalfNV alpha);
typedef void (GLAPIENTRY * PFNGLCOLOR4HVNVPROC) (GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLCOLORMASKIPROC) (GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
typedef void (GLAPIENTRY * PFNGLCOLORMASKINDEXEDEXTPROC) (GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
typedef void (GLAPIENTRY * PFNGLCOLORPOINTEREXTPROC) (GLint size, GLenum type, GLsizei stride, GLsizei count, const void * pointer);
typedef void (GLAPIENTRY * PFNGLCOLORSUBTABLEPROC) (GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const void * data);
typedef void (GLAPIENTRY * PFNGLCOLORSUBTABLEEXTPROC) (GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const void * data);
typedef void (GLAPIENTRY * PFNGLCOLORTABLEPROC) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void * table);
typedef void (GLAPIENTRY * PFNGLCOLORTABLEEXTPROC) (GLenum target, GLenum internalFormat, GLsizei width, GLenum format, GLenum type, const void * table);
typedef void (GLAPIENTRY * PFNGLCOLORTABLEPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat const * params);
typedef void (GLAPIENTRY * PFNGLCOLORTABLEPARAMETERIVPROC) (GLenum target, GLenum pname, GLint const * params);
typedef void (GLAPIENTRY * PFNGLCOMBINERINPUTNVPROC) (GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
typedef void (GLAPIENTRY * PFNGLCOMBINEROUTPUTNVPROC) (GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum);
typedef void (GLAPIENTRY * PFNGLCOMBINERPARAMETERFNVPROC) (GLenum pname, GLfloat param);
typedef void (GLAPIENTRY * PFNGLCOMBINERPARAMETERFVNVPROC) (GLenum pname, GLfloat const * params);
typedef void (GLAPIENTRY * PFNGLCOMBINERPARAMETERINVPROC) (GLenum pname, GLint param);
typedef void (GLAPIENTRY * PFNGLCOMBINERPARAMETERIVNVPROC) (GLenum pname, GLint const * params);
typedef void (GLAPIENTRY * PFNGLCOMBINERSTAGEPARAMETERFVNVPROC) (GLenum stage, GLenum pname, GLfloat const * params);
typedef void (GLAPIENTRY * PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef void (GLAPIENTRY * PFNGLCOMPILESHADERARBPROC) (GLhandleARB shaderObj);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * bits);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * bits);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * bits);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * bits);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * bits);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * bits);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDTEXIMAGE1DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDTEXIMAGE1DARBPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDTEXIMAGE2DARBPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDTEXIMAGE3DARBPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * bits);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * bits);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * bits);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * bits);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * bits);
typedef void (GLAPIENTRY * PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * bits);
typedef void (GLAPIENTRY * PFNGLCONVOLUTIONFILTER1DPROC) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void * image);
typedef void (GLAPIENTRY * PFNGLCONVOLUTIONFILTER2DPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * image);
typedef void (GLAPIENTRY * PFNGLCONVOLUTIONPARAMETERFPROC) (GLenum target, GLenum pname, GLfloat params);
typedef void (GLAPIENTRY * PFNGLCONVOLUTIONPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat const * params);
typedef void (GLAPIENTRY * PFNGLCONVOLUTIONPARAMETERIPROC) (GLenum target, GLenum pname, GLint params);
typedef void (GLAPIENTRY * PFNGLCONVOLUTIONPARAMETERIVPROC) (GLenum target, GLenum pname, GLint const * params);
typedef void (GLAPIENTRY * PFNGLCOPYCOLORSUBTABLEPROC) (GLenum target, GLsizei start, GLint x, GLint y, GLsizei width);
typedef void (GLAPIENTRY * PFNGLCOPYCOLORTABLEPROC) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
typedef void (GLAPIENTRY * PFNGLCOPYCONVOLUTIONFILTER1DPROC) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
typedef void (GLAPIENTRY * PFNGLCOPYCONVOLUTIONFILTER2DPROC) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY * PFNGLCOPYIMAGESUBDATAPROC) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
typedef void (GLAPIENTRY * PFNGLCOPYMULTITEXIMAGE1DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (GLAPIENTRY * PFNGLCOPYMULTITEXIMAGE2DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (GLAPIENTRY * PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (GLAPIENTRY * PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY * PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY * PFNGLCOPYTEXSUBIMAGE3DEXTPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY * PFNGLCOPYTEXTUREIMAGE1DEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (GLAPIENTRY * PFNGLCOPYTEXTUREIMAGE2DEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (GLAPIENTRY * PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (GLAPIENTRY * PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY * PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef GLuint (GLAPIENTRY * PFNGLCREATEPROGRAMPROC) ();
typedef GLhandleARB (GLAPIENTRY * PFNGLCREATEPROGRAMOBJECTARBPROC) ();
typedef GLuint (GLAPIENTRY * PFNGLCREATESHADERPROC) (GLenum type);
typedef GLhandleARB (GLAPIENTRY * PFNGLCREATESHADEROBJECTARBPROC) (GLenum shaderType);
typedef void (GLAPIENTRY * PFNGLDELETEBUFFERSPROC) (GLsizei n, GLuint const * buffers);
typedef void (GLAPIENTRY * PFNGLDELETEFENCESNVPROC) (GLsizei n, GLuint const * fences);
typedef void (GLAPIENTRY * PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, GLuint const * framebuffers);
typedef void (GLAPIENTRY * PFNGLDELETEOBJECTARBPROC) (GLhandleARB obj);
typedef void (GLAPIENTRY * PFNGLDELETEOCCLUSIONQUERIESNVPROC) (GLsizei n, GLuint const * ids);
typedef void (GLAPIENTRY * PFNGLDELETEPROGRAMPROC) (GLuint program);
typedef void (GLAPIENTRY * PFNGLDELETEPROGRAMSARBPROC) (GLsizei n, GLuint const * programs);
typedef void (GLAPIENTRY * PFNGLDELETEPROGRAMSNVPROC) (GLsizei n, GLuint const * programs);
typedef void (GLAPIENTRY * PFNGLDELETEQUERIESPROC) (GLsizei n, GLuint const * ids);
typedef void (GLAPIENTRY * PFNGLDELETEQUERIESARBPROC) (GLsizei n, GLuint const * ids);
typedef void (GLAPIENTRY * PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, GLuint const * renderbuffers);
typedef void (GLAPIENTRY * PFNGLDELETESAMPLERSPROC) (GLsizei count, GLuint const * samplers);
typedef void (GLAPIENTRY * PFNGLDELETESHADERPROC) (GLuint shader);
typedef void (GLAPIENTRY * PFNGLDELETETEXTURESPROC) (GLsizei n, GLuint const * textures);
typedef void (GLAPIENTRY * PFNGLDELETETEXTURESEXTPROC) (GLsizei n, GLuint const * textures);
typedef void (GLAPIENTRY * PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, GLuint const * arrays);
typedef void (GLAPIENTRY * PFNGLDEPTHBOUNDSDNVPROC) (GLdouble zmin, GLdouble zmax);
typedef void (GLAPIENTRY * PFNGLDEPTHBOUNDSEXTPROC) (GLclampd zmin, GLclampd zmax);
typedef void (GLAPIENTRY * PFNGLDEPTHRANGEDNVPROC) (GLdouble zNear, GLdouble zFar);
typedef void (GLAPIENTRY * PFNGLDETACHOBJECTARBPROC) (GLhandleARB containerObj, GLhandleARB attachedObj);
typedef void (GLAPIENTRY * PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (GLAPIENTRY * PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC) (GLenum array, GLuint index);
typedef void (GLAPIENTRY * PFNGLDISABLEIPROC) (GLenum target, GLuint index);
typedef void (GLAPIENTRY * PFNGLDISABLEINDEXEDEXTPROC) (GLenum target, GLuint index);
typedef void (GLAPIENTRY * PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (GLAPIENTRY * PFNGLDRAWARRAYSEXTPROC) (GLenum mode, GLint first, GLsizei count);
typedef void (GLAPIENTRY * PFNGLDRAWARRAYSINSTANCEDARBPROC) (GLenum mode, GLint first, GLsizei count, GLsizei primcount);
typedef void (GLAPIENTRY * PFNGLDRAWARRAYSINSTANCEDEXTPROC) (GLenum mode, GLint start, GLsizei count, GLsizei primcount);
typedef void (GLAPIENTRY * PFNGLDRAWBUFFERSPROC) (GLsizei n, GLenum const * bufs);
typedef void (GLAPIENTRY * PFNGLDRAWBUFFERSARBPROC) (GLsizei n, GLenum const * bufs);
typedef void (GLAPIENTRY * PFNGLDRAWBUFFERSATIPROC) (GLsizei n, GLenum const * bufs);
typedef void (GLAPIENTRY * PFNGLDRAWELEMENTSINSTANCEDARBPROC) (GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei primcount);
typedef void (GLAPIENTRY * PFNGLDRAWELEMENTSINSTANCEDEXTPROC) (GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei primcount);
typedef void (GLAPIENTRY * PFNGLDRAWRANGEELEMENTSPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices);
typedef void (GLAPIENTRY * PFNGLDRAWRANGEELEMENTSEXTPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices);
typedef void (GLAPIENTRY * PFNGLEDGEFLAGPOINTEREXTPROC) (GLsizei stride, GLsizei count, GLboolean const * pointer);
typedef void (GLAPIENTRY * PFNGLENABLECLIENTSTATEINDEXEDEXTPROC) (GLenum array, GLuint index);
typedef void (GLAPIENTRY * PFNGLENABLEIPROC) (GLenum target, GLuint index);
typedef void (GLAPIENTRY * PFNGLENABLEINDEXEDEXTPROC) (GLenum target, GLuint index);
typedef void (GLAPIENTRY * PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (GLAPIENTRY * PFNGLENDCONDITIONALRENDERPROC) ();
typedef void (GLAPIENTRY * PFNGLENDCONDITIONALRENDERNVPROC) ();
typedef void (GLAPIENTRY * PFNGLENDOCCLUSIONQUERYNVPROC) ();
typedef void (GLAPIENTRY * PFNGLENDQUERYPROC) (GLenum target);
typedef void (GLAPIENTRY * PFNGLENDQUERYARBPROC) (GLenum target);
typedef void (GLAPIENTRY * PFNGLENDTRANSFORMFEEDBACKPROC) ();
typedef void (GLAPIENTRY * PFNGLENDTRANSFORMFEEDBACKNVPROC) ();
typedef void (GLAPIENTRY * PFNGLEXECUTEPROGRAMNVPROC) (GLenum target, GLuint id, GLfloat const * params);
typedef void (GLAPIENTRY * PFNGLFINALCOMBINERINPUTNVPROC) (GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
typedef void (GLAPIENTRY * PFNGLFINISHFENCENVPROC) (GLuint fence);
typedef void (GLAPIENTRY * PFNGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum target, GLintptr offset, GLsizeiptr length);
typedef void (GLAPIENTRY * PFNGLFLUSHPIXELDATARANGENVPROC) (GLenum target);
typedef void (GLAPIENTRY * PFNGLFLUSHVERTEXARRAYRANGENVPROC) ();
typedef void (GLAPIENTRY * PFNGLFOGCOORDDPROC) (GLdouble coord);
typedef void (GLAPIENTRY * PFNGLFOGCOORDDEXTPROC) (GLdouble coord);
typedef void (GLAPIENTRY * PFNGLFOGCOORDDVPROC) (GLdouble const * coord);
typedef void (GLAPIENTRY * PFNGLFOGCOORDDVEXTPROC) (GLdouble const * coord);
typedef void (GLAPIENTRY * PFNGLFOGCOORDFPROC) (GLfloat coord);
typedef void (GLAPIENTRY * PFNGLFOGCOORDFEXTPROC) (GLfloat coord);
typedef void (GLAPIENTRY * PFNGLFOGCOORDFVPROC) (GLfloat const * coord);
typedef void (GLAPIENTRY * PFNGLFOGCOORDFVEXTPROC) (GLfloat const * coord);
typedef void (GLAPIENTRY * PFNGLFOGCOORDHNVPROC) (GLhalfNV fog);
typedef void (GLAPIENTRY * PFNGLFOGCOORDHVNVPROC) (GLhalfNV const * fog);
typedef void (GLAPIENTRY * PFNGLFOGCOORDPOINTERPROC) (GLenum type, GLsizei stride, const void * pointer);
typedef void (GLAPIENTRY * PFNGLFOGCOORDPOINTEREXTPROC) (GLenum type, GLsizei stride, const void * pointer);
typedef void (GLAPIENTRY * PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC) (GLuint framebuffer, GLenum mode);
typedef void (GLAPIENTRY * PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC) (GLuint framebuffer, GLsizei n, GLenum const * bufs);
typedef void (GLAPIENTRY * PFNGLFRAMEBUFFERREADBUFFEREXTPROC) (GLuint framebuffer, GLenum mode);
typedef void (GLAPIENTRY * PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (GLAPIENTRY * PFNGLFRAMEBUFFERTEXTUREPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (GLAPIENTRY * PFNGLFRAMEBUFFERTEXTURE1DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (GLAPIENTRY * PFNGLFRAMEBUFFERTEXTURE1DEXTPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (GLAPIENTRY * PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (GLAPIENTRY * PFNGLFRAMEBUFFERTEXTURE3DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (GLAPIENTRY * PFNGLFRAMEBUFFERTEXTURE3DEXTPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (GLAPIENTRY * PFNGLFRAMEBUFFERTEXTUREARBPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (GLAPIENTRY * PFNGLFRAMEBUFFERTEXTUREEXTPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (GLAPIENTRY * PFNGLFRAMEBUFFERTEXTUREFACEARBPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face);
typedef void (GLAPIENTRY * PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face);
typedef void (GLAPIENTRY * PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (GLAPIENTRY * PFNGLFRAMEBUFFERTEXTURELAYERARBPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (GLAPIENTRY * PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (GLAPIENTRY * PFNGLGENBUFFERSPROC) (GLsizei n, GLuint * buffers);
typedef void (GLAPIENTRY * PFNGLGENBUFFERSARBPROC) (GLsizei n, GLuint * buffers);
typedef void (GLAPIENTRY * PFNGLGENERATEMIPMAPPROC) (GLenum target);
typedef void (GLAPIENTRY * PFNGLGENERATEMIPMAPEXTPROC) (GLenum target);
typedef void (GLAPIENTRY * PFNGLGENERATEMULTITEXMIPMAPEXTPROC) (GLenum texunit, GLenum target);
typedef void (GLAPIENTRY * PFNGLGENERATETEXTUREMIPMAPEXTPROC) (GLuint texture, GLenum target);
typedef void (GLAPIENTRY * PFNGLGENFENCESNVPROC) (GLsizei n, GLuint * fences);
typedef void (GLAPIENTRY * PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint * framebuffers);
typedef void (GLAPIENTRY * PFNGLGENOCCLUSIONQUERIESNVPROC) (GLsizei n, GLuint * ids);
typedef void (GLAPIENTRY * PFNGLGENPROGRAMSARBPROC) (GLsizei n, GLuint * programs);
typedef void (GLAPIENTRY * PFNGLGENPROGRAMSNVPROC) (GLsizei n, GLuint * programs);
typedef void (GLAPIENTRY * PFNGLGENQUERIESPROC) (GLsizei n, GLuint * ids);
typedef void (GLAPIENTRY * PFNGLGENQUERIESARBPROC) (GLsizei n, GLuint * ids);
typedef void (GLAPIENTRY * PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint * renderbuffers);
typedef void (GLAPIENTRY * PFNGLGENSAMPLERSPROC) (GLsizei count, GLuint * samplers);
typedef void (GLAPIENTRY * PFNGLGENTEXTURESPROC) (GLsizei n, GLuint * textures);
typedef void (GLAPIENTRY * PFNGLGENTEXTURESEXTPROC) (GLsizei n, GLuint * textures);
typedef void (GLAPIENTRY * PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint * arrays);
typedef void (GLAPIENTRY * PFNGLGETACTIVEATTRIBPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
typedef void (GLAPIENTRY * PFNGLGETACTIVEATTRIBARBPROC) (GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei * length, GLint * size, GLenum * type, GLcharARB * name);
typedef void (GLAPIENTRY * PFNGLGETACTIVEUNIFORMPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
typedef void (GLAPIENTRY * PFNGLGETACTIVEUNIFORMARBPROC) (GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei * length, GLint * size, GLenum * type, GLcharARB * name);
typedef void (GLAPIENTRY * PFNGLGETACTIVEVARYINGNVPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name);
typedef void (GLAPIENTRY * PFNGLGETATTACHEDOBJECTSARBPROC) (GLhandleARB containerObj, GLsizei maxCount, GLsizei * count, GLhandleARB * obj);
typedef void (GLAPIENTRY * PFNGLGETATTACHEDSHADERSPROC) (GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders);
typedef GLint (GLAPIENTRY * PFNGLGETATTRIBLOCATIONPROC) (GLuint program, GLchar const * name);
typedef GLint (GLAPIENTRY * PFNGLGETATTRIBLOCATIONARBPROC) (GLhandleARB programObj, GLcharARB const * name);
typedef void (GLAPIENTRY * PFNGLGETBOOLEANI_VPROC) (GLenum target, GLuint index, GLboolean * data);
typedef void (GLAPIENTRY * PFNGLGETBOOLEANINDEXEDVEXTPROC) (GLenum target, GLuint index, GLboolean * data);
typedef void (GLAPIENTRY * PFNGLGETBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETBUFFERPARAMETERIVARBPROC) (GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETBUFFERPOINTERVPROC) (GLenum target, GLenum pname, void ** params);
typedef void (GLAPIENTRY * PFNGLGETBUFFERPOINTERVARBPROC) (GLenum target, GLenum pname, void ** params);
typedef void (GLAPIENTRY * PFNGLGETBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, void * data);
typedef void (GLAPIENTRY * PFNGLGETBUFFERSUBDATAARBPROC) (GLenum target, GLintptrARB offset, GLsizeiptrARB size, void * data);
typedef void (GLAPIENTRY * PFNGLGETCOLORTABLEPROC) (GLenum target, GLenum format, GLenum type, void * table);
typedef void (GLAPIENTRY * PFNGLGETCOLORTABLEEXTPROC) (GLenum target, GLenum format, GLenum type, void * data);
typedef void (GLAPIENTRY * PFNGLGETCOLORTABLEPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETCOLORTABLEPARAMETERFVEXTPROC) (GLenum target, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETCOLORTABLEPARAMETERIVPROC) (GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETCOLORTABLEPARAMETERIVEXTPROC) (GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC) (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC) (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC) (GLenum stage, GLenum portion, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC) (GLenum stage, GLenum portion, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC) (GLenum stage, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC) (GLenum texunit, GLenum target, GLint lod, void * img);
typedef void (GLAPIENTRY * PFNGLGETCOMPRESSEDTEXIMAGEPROC) (GLenum target, GLint level, void * img);
typedef void (GLAPIENTRY * PFNGLGETCOMPRESSEDTEXIMAGEARBPROC) (GLenum target, GLint level, void * img);
typedef void (GLAPIENTRY * PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC) (GLuint texture, GLenum target, GLint lod, void * img);
typedef void (GLAPIENTRY * PFNGLGETCONVOLUTIONFILTERPROC) (GLenum target, GLenum format, GLenum type, void * image);
typedef void (GLAPIENTRY * PFNGLGETCONVOLUTIONPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETCONVOLUTIONPARAMETERIVPROC) (GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETDOUBLEINDEXEDVEXTPROC) (GLenum target, GLuint index, GLdouble * data);
typedef void (GLAPIENTRY * PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC) (GLenum variable, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC) (GLenum variable, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETFLOATINDEXEDVEXTPROC) (GLenum target, GLuint index, GLfloat * data);
typedef GLint (GLAPIENTRY * PFNGLGETFRAGDATALOCATIONPROC) (GLuint program, GLchar const * name);
typedef GLint (GLAPIENTRY * PFNGLGETFRAGDATALOCATIONEXTPROC) (GLuint program, GLchar const * name);
typedef void (GLAPIENTRY * PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum target, GLenum attachment, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC) (GLenum target, GLenum attachment, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC) (GLuint framebuffer, GLenum pname, GLint * params);
typedef GLhandleARB (GLAPIENTRY * PFNGLGETHANDLEARBPROC) (GLenum pname);
typedef void (GLAPIENTRY * PFNGLGETHISTOGRAMPROC) (GLenum target, GLboolean reset, GLenum format, GLenum type, void * values);
typedef void (GLAPIENTRY * PFNGLGETHISTOGRAMPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETHISTOGRAMPARAMETERIVPROC) (GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETINFOLOGARBPROC) (GLhandleARB obj, GLsizei maxLength, GLsizei * length, GLcharARB * infoLog);
typedef void (GLAPIENTRY * PFNGLGETINTEGERI_VPROC) (GLenum target, GLuint index, GLint * data);
typedef void (GLAPIENTRY * PFNGLGETINTEGERINDEXEDVEXTPROC) (GLenum target, GLuint index, GLint * data);
typedef void (GLAPIENTRY * PFNGLGETMINMAXPROC) (GLenum target, GLboolean reset, GLenum format, GLenum type, void * values);
typedef void (GLAPIENTRY * PFNGLGETMINMAXPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETMINMAXPARAMETERIVPROC) (GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETMULTISAMPLEFVNVPROC) (GLenum pname, GLuint index, GLfloat * val);
typedef void (GLAPIENTRY * PFNGLGETMULTITEXENVFVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETMULTITEXENVIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETMULTITEXGENDVEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLdouble * params);
typedef void (GLAPIENTRY * PFNGLGETMULTITEXGENFVEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETMULTITEXGENIVEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETMULTITEXIMAGEEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum format, GLenum type, void * pixels);
typedef void (GLAPIENTRY * PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETMULTITEXPARAMETERFVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETMULTITEXPARAMETERIIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETMULTITEXPARAMETERIUIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLuint * params);
typedef void (GLAPIENTRY * PFNGLGETMULTITEXPARAMETERIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC) (GLuint buffer, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETNAMEDBUFFERPOINTERVEXTPROC) (GLuint buffer, GLenum pname, void ** params);
typedef void (GLAPIENTRY * PFNGLGETNAMEDBUFFERSUBDATAEXTPROC) (GLuint buffer, GLintptr offset, GLsizeiptr size, void * data);
typedef void (GLAPIENTRY * PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC) (GLuint framebuffer, GLenum attachment, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETNAMEDPROGRAMIVEXTPROC) (GLuint program, GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC) (GLuint program, GLenum target, GLuint index, GLdouble * params);
typedef void (GLAPIENTRY * PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC) (GLuint program, GLenum target, GLuint index, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC) (GLuint program, GLenum target, GLuint index, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC) (GLuint program, GLenum target, GLuint index, GLuint * params);
typedef void (GLAPIENTRY * PFNGLGETNAMEDPROGRAMSTRINGEXTPROC) (GLuint program, GLenum target, GLenum pname, void * string);
typedef void (GLAPIENTRY * PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC) (GLuint renderbuffer, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETOBJECTPARAMETERFVARBPROC) (GLhandleARB obj, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETOBJECTPARAMETERIVARBPROC) (GLhandleARB obj, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETOCCLUSIONQUERYIVNVPROC) (GLuint id, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETOCCLUSIONQUERYUIVNVPROC) (GLuint id, GLenum pname, GLuint * params);
typedef void (GLAPIENTRY * PFNGLGETPOINTERINDEXEDVEXTPROC) (GLenum target, GLuint index, void ** data);
typedef void (GLAPIENTRY * PFNGLGETPOINTERVEXTPROC) (GLenum pname, void ** params);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMENVPARAMETERDVARBPROC) (GLenum target, GLuint index, GLdouble * params);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMENVPARAMETERIIVNVPROC) (GLenum target, GLuint index, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMENVPARAMETERIUIVNVPROC) (GLenum target, GLuint index, GLuint * params);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMIVNVPROC) (GLuint id, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC) (GLenum target, GLuint index, GLdouble * params);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC) (GLenum target, GLuint index, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMLOCALPARAMETERIIVNVPROC) (GLenum target, GLuint index, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMLOCALPARAMETERIUIVNVPROC) (GLenum target, GLuint index, GLuint * params);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMNAMEDPARAMETERDVNVPROC) (GLuint id, GLsizei len, GLubyte const * name, GLdouble * params);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMNAMEDPARAMETERFVNVPROC) (GLuint id, GLsizei len, GLubyte const * name, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMPARAMETERDVNVPROC) (GLenum target, GLuint index, GLenum pname, GLdouble * params);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMPARAMETERFVNVPROC) (GLenum target, GLuint index, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMSTRINGARBPROC) (GLenum target, GLenum pname, void * string);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMSTRINGNVPROC) (GLuint id, GLenum pname, GLubyte * program);
typedef void (GLAPIENTRY * PFNGLGETQUERYIVPROC) (GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETQUERYIVARBPROC) (GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETQUERYOBJECTI64VEXTPROC) (GLuint id, GLenum pname, GLint64 * params);
typedef void (GLAPIENTRY * PFNGLGETQUERYOBJECTIVPROC) (GLuint id, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETQUERYOBJECTIVARBPROC) (GLuint id, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETQUERYOBJECTUI64VPROC) (GLuint id, GLenum pname, GLuint64 * params);
typedef void (GLAPIENTRY * PFNGLGETQUERYOBJECTUI64VEXTPROC) (GLuint id, GLenum pname, GLuint64 * params);
typedef void (GLAPIENTRY * PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint * params);
typedef void (GLAPIENTRY * PFNGLGETQUERYOBJECTUIVARBPROC) (GLuint id, GLenum pname, GLuint * params);
typedef void (GLAPIENTRY * PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC) (GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETSEPARABLEFILTERPROC) (GLenum target, GLenum format, GLenum type, void * row, void * column, void * span);
typedef void (GLAPIENTRY * PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
typedef void (GLAPIENTRY * PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source);
typedef void (GLAPIENTRY * PFNGLGETSHADERSOURCEARBPROC) (GLhandleARB obj, GLsizei maxLength, GLsizei * length, GLcharARB * source);
typedef GLubyte const *  (GLAPIENTRY * PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
typedef void (GLAPIENTRY * PFNGLGETTEXPARAMETERIIVPROC) (GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETTEXPARAMETERIIVEXTPROC) (GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETTEXPARAMETERIUIVPROC) (GLenum target, GLenum pname, GLuint * params);
typedef void (GLAPIENTRY * PFNGLGETTEXPARAMETERIUIVEXTPROC) (GLenum target, GLenum pname, GLuint * params);
typedef void (GLAPIENTRY * PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETTEXTUREPARAMETERFVEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETTEXTUREPARAMETERIIVEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETTEXTUREPARAMETERIUIVEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLuint * params);
typedef void (GLAPIENTRY * PFNGLGETTEXTUREPARAMETERIVEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETTRACKMATRIXIVNVPROC) (GLenum target, GLuint address, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name);
typedef void (GLAPIENTRY * PFNGLGETTRANSFORMFEEDBACKVARYINGNVPROC) (GLuint program, GLuint index, GLint * location);
typedef GLint (GLAPIENTRY * PFNGLGETUNIFORMBUFFERSIZEEXTPROC) (GLuint program, GLint location);
typedef void (GLAPIENTRY * PFNGLGETUNIFORMFVPROC) (GLuint program, GLint location, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETUNIFORMFVARBPROC) (GLhandleARB programObj, GLint location, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETUNIFORMIVPROC) (GLuint program, GLint location, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETUNIFORMIVARBPROC) (GLhandleARB programObj, GLint location, GLint * params);
typedef GLint (GLAPIENTRY * PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, GLchar const * name);
typedef GLint (GLAPIENTRY * PFNGLGETUNIFORMLOCATIONARBPROC) (GLhandleARB programObj, GLcharARB const * name);
typedef GLintptr (GLAPIENTRY * PFNGLGETUNIFORMOFFSETEXTPROC) (GLuint program, GLint location);
typedef void (GLAPIENTRY * PFNGLGETUNIFORMUIVPROC) (GLuint program, GLint location, GLuint * params);
typedef void (GLAPIENTRY * PFNGLGETUNIFORMUIVEXTPROC) (GLuint program, GLint location, GLuint * params);
typedef GLint (GLAPIENTRY * PFNGLGETVARYINGLOCATIONNVPROC) (GLuint program, GLchar const * name);
typedef void (GLAPIENTRY * PFNGLGETVERTEXATTRIBDVPROC) (GLuint index, GLenum pname, GLdouble * params);
typedef void (GLAPIENTRY * PFNGLGETVERTEXATTRIBDVARBPROC) (GLuint index, GLenum pname, GLdouble * params);
typedef void (GLAPIENTRY * PFNGLGETVERTEXATTRIBDVNVPROC) (GLuint index, GLenum pname, GLdouble * params);
typedef void (GLAPIENTRY * PFNGLGETVERTEXATTRIBFVPROC) (GLuint index, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETVERTEXATTRIBFVARBPROC) (GLuint index, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETVERTEXATTRIBFVNVPROC) (GLuint index, GLenum pname, GLfloat * params);
typedef void (GLAPIENTRY * PFNGLGETVERTEXATTRIBIIVPROC) (GLuint index, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETVERTEXATTRIBIIVEXTPROC) (GLuint index, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETVERTEXATTRIBIUIVPROC) (GLuint index, GLenum pname, GLuint * params);
typedef void (GLAPIENTRY * PFNGLGETVERTEXATTRIBIUIVEXTPROC) (GLuint index, GLenum pname, GLuint * params);
typedef void (GLAPIENTRY * PFNGLGETVERTEXATTRIBIVPROC) (GLuint index, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETVERTEXATTRIBIVARBPROC) (GLuint index, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETVERTEXATTRIBIVNVPROC) (GLuint index, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint index, GLenum pname, void ** pointer);
typedef void (GLAPIENTRY * PFNGLGETVERTEXATTRIBPOINTERVARBPROC) (GLuint index, GLenum pname, void ** pointer);
typedef void (GLAPIENTRY * PFNGLGETVERTEXATTRIBPOINTERVNVPROC) (GLuint index, GLenum pname, void ** pointer);
typedef void (GLAPIENTRY * PFNGLGETVIDEOI64VNVPROC) (GLuint video_slot, GLenum pname, GLint64EXT * params);
typedef void (GLAPIENTRY * PFNGLGETVIDEOIVNVPROC) (GLuint video_slot, GLenum pname, GLint * params);
typedef void (GLAPIENTRY * PFNGLGETVIDEOUI64VNVPROC) (GLuint video_slot, GLenum pname, GLuint64EXT * params);
typedef void (GLAPIENTRY * PFNGLGETVIDEOUIVNVPROC) (GLuint video_slot, GLenum pname, GLuint * params);
typedef void (GLAPIENTRY * PFNGLHISTOGRAMPROC) (GLenum target, GLsizei width, GLenum internalformat, GLboolean sink);
typedef void (GLAPIENTRY * PFNGLINDEXPOINTEREXTPROC) (GLenum type, GLsizei stride, GLsizei count, const void * pointer);
typedef GLboolean (GLAPIENTRY * PFNGLISBUFFERPROC) (GLuint buffer);
typedef GLboolean (GLAPIENTRY * PFNGLISENABLEDIPROC) (GLenum target, GLuint index);
typedef GLboolean (GLAPIENTRY * PFNGLISENABLEDINDEXEDEXTPROC) (GLenum target, GLuint index);
typedef GLboolean (GLAPIENTRY * PFNGLISFENCENVPROC) (GLuint fence);
typedef GLboolean (GLAPIENTRY * PFNGLISFRAMEBUFFERPROC) (GLuint framebuffer);
typedef GLboolean (GLAPIENTRY * PFNGLISFRAMEBUFFEREXTPROC) (GLuint framebuffer);
typedef GLboolean (GLAPIENTRY * PFNGLISOCCLUSIONQUERYNVPROC) (GLuint id);
typedef GLboolean (GLAPIENTRY * PFNGLISPROGRAMPROC) (GLuint program);
typedef GLboolean (GLAPIENTRY * PFNGLISPROGRAMARBPROC) (GLuint program);
typedef GLboolean (GLAPIENTRY * PFNGLISPROGRAMNVPROC) (GLuint id);
typedef GLboolean (GLAPIENTRY * PFNGLISQUERYPROC) (GLuint id);
typedef GLboolean (GLAPIENTRY * PFNGLISQUERYARBPROC) (GLuint id);
typedef GLboolean (GLAPIENTRY * PFNGLISRENDERBUFFERPROC) (GLuint renderbuffer);
typedef GLboolean (GLAPIENTRY * PFNGLISRENDERBUFFEREXTPROC) (GLuint renderbuffer);
typedef GLboolean (GLAPIENTRY * PFNGLISSHADERPROC) (GLuint shader);
typedef GLboolean (GLAPIENTRY * PFNGLISTEXTUREEXTPROC) (GLuint texture);
typedef GLboolean (GLAPIENTRY * PFNGLISVERTEXARRAYPROC) (GLuint array);
typedef void (GLAPIENTRY * PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (GLAPIENTRY * PFNGLLINKPROGRAMARBPROC) (GLhandleARB programObj);
typedef void (GLAPIENTRY * PFNGLLOADPROGRAMNVPROC) (GLenum target, GLuint id, GLsizei len, GLubyte const * program);
typedef void (GLAPIENTRY * PFNGLLOADTRANSPOSEMATRIXDPROC) (GLdouble const * m);
typedef void (GLAPIENTRY * PFNGLLOADTRANSPOSEMATRIXDARBPROC) (GLdouble const * m);
typedef void (GLAPIENTRY * PFNGLLOADTRANSPOSEMATRIXFARBPROC) (GLfloat const * m);
typedef void (GLAPIENTRY * PFNGLLOCKARRAYSEXTPROC) (GLint first, GLsizei count);
typedef void * (GLAPIENTRY * PFNGLMAPBUFFERPROC) (GLenum target, GLenum access);
typedef void * (GLAPIENTRY * PFNGLMAPBUFFERARBPROC) (GLenum target, GLenum access);
typedef void * (GLAPIENTRY * PFNGLMAPBUFFERRANGEPROC) (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (GLAPIENTRY * PFNGLMATRIXFRUSTUMEXTPROC) (GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
typedef void (GLAPIENTRY * PFNGLMATRIXLOADDEXTPROC) (GLenum mode, GLdouble const * m);
typedef void (GLAPIENTRY * PFNGLMATRIXLOADFEXTPROC) (GLenum mode, GLfloat const * m);
typedef void (GLAPIENTRY * PFNGLMATRIXLOADIDENTITYEXTPROC) (GLenum mode);
typedef void (GLAPIENTRY * PFNGLMATRIXLOADTRANSPOSEDEXTPROC) (GLenum mode, GLdouble const * m);
typedef void (GLAPIENTRY * PFNGLMATRIXLOADTRANSPOSEFEXTPROC) (GLenum mode, GLfloat const * m);
typedef void (GLAPIENTRY * PFNGLMATRIXMULTDEXTPROC) (GLenum mode, GLdouble const * m);
typedef void (GLAPIENTRY * PFNGLMATRIXMULTFEXTPROC) (GLenum mode, GLfloat const * m);
typedef void (GLAPIENTRY * PFNGLMATRIXMULTTRANSPOSEDEXTPROC) (GLenum mode, GLdouble const * m);
typedef void (GLAPIENTRY * PFNGLMATRIXMULTTRANSPOSEFEXTPROC) (GLenum mode, GLfloat const * m);
typedef void (GLAPIENTRY * PFNGLMATRIXORTHOEXTPROC) (GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
typedef void (GLAPIENTRY * PFNGLMATRIXPOPEXTPROC) (GLenum mode);
typedef void (GLAPIENTRY * PFNGLMATRIXPUSHEXTPROC) (GLenum mode);
typedef void (GLAPIENTRY * PFNGLMATRIXROTATEDEXTPROC) (GLenum mode, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLAPIENTRY * PFNGLMATRIXROTATEFEXTPROC) (GLenum mode, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAPIENTRY * PFNGLMATRIXSCALEDEXTPROC) (GLenum mode, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLAPIENTRY * PFNGLMATRIXSCALEFEXTPROC) (GLenum mode, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAPIENTRY * PFNGLMATRIXTRANSLATEDEXTPROC) (GLenum mode, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLAPIENTRY * PFNGLMATRIXTRANSLATEFEXTPROC) (GLenum mode, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAPIENTRY * PFNGLMINMAXPROC) (GLenum target, GLenum internalformat, GLboolean sink);
typedef void (GLAPIENTRY * PFNGLMULTIDRAWARRAYSPROC) (GLenum mode, GLint const * first, GLsizei const * count, GLsizei drawcount);
typedef void (GLAPIENTRY * PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum mode, GLint const * first, GLsizei const * count, GLsizei primcount);
typedef void (GLAPIENTRY * PFNGLMULTIDRAWELEMENTSPROC) (GLenum mode, GLsizei const * count, GLenum type, const void *const* indices, GLsizei drawcount);
typedef void (GLAPIENTRY * PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum mode, GLsizei const * count, GLenum type, const void *const* indices, GLsizei primcount);
typedef void (GLAPIENTRY * PFNGLMULTITEXBUFFEREXTPROC) (GLenum texunit, GLenum target, GLenum internalformat, GLuint buffer);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD1DPROC) (GLenum target, GLdouble s);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD1DARBPROC) (GLenum target, GLdouble s);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD1DVPROC) (GLenum target, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD1DVARBPROC) (GLenum target, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD1FPROC) (GLenum target, GLfloat s);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD1FARBPROC) (GLenum target, GLfloat s);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD1FVPROC) (GLenum target, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD1FVARBPROC) (GLenum target, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD1HNVPROC) (GLenum target, GLhalfNV s);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD1HVNVPROC) (GLenum target, GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD1IPROC) (GLenum target, GLint s);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD1IARBPROC) (GLenum target, GLint s);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD1IVPROC) (GLenum target, GLint const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD1IVARBPROC) (GLenum target, GLint const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD1SPROC) (GLenum target, GLshort s);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD1SARBPROC) (GLenum target, GLshort s);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD1SVPROC) (GLenum target, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD1SVARBPROC) (GLenum target, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD2DPROC) (GLenum target, GLdouble s, GLdouble t);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD2DARBPROC) (GLenum target, GLdouble s, GLdouble t);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD2DVPROC) (GLenum target, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD2DVARBPROC) (GLenum target, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD2FARBPROC) (GLenum target, GLfloat s, GLfloat t);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD2FVARBPROC) (GLenum target, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD2HNVPROC) (GLenum target, GLhalfNV s, GLhalfNV t);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD2HVNVPROC) (GLenum target, GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD2IPROC) (GLenum target, GLint s, GLint t);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD2IARBPROC) (GLenum target, GLint s, GLint t);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD2IVPROC) (GLenum target, GLint const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD2IVARBPROC) (GLenum target, GLint const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD2SPROC) (GLenum target, GLshort s, GLshort t);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD2SARBPROC) (GLenum target, GLshort s, GLshort t);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD2SVPROC) (GLenum target, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD2SVARBPROC) (GLenum target, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD3DPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD3DARBPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD3DVPROC) (GLenum target, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD3DVARBPROC) (GLenum target, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD3FPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD3FARBPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD3FVPROC) (GLenum target, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD3FVARBPROC) (GLenum target, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD3HNVPROC) (GLenum target, GLhalfNV s, GLhalfNV t, GLhalfNV r);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD3HVNVPROC) (GLenum target, GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD3IPROC) (GLenum target, GLint s, GLint t, GLint r);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD3IARBPROC) (GLenum target, GLint s, GLint t, GLint r);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD3IVPROC) (GLenum target, GLint const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD3IVARBPROC) (GLenum target, GLint const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD3SPROC) (GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD3SARBPROC) (GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD3SVPROC) (GLenum target, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD3SVARBPROC) (GLenum target, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD4DPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD4DARBPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD4DVPROC) (GLenum target, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD4DVARBPROC) (GLenum target, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD4FPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD4FARBPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD4FVPROC) (GLenum target, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD4FVARBPROC) (GLenum target, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD4HNVPROC) (GLenum target, GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD4HVNVPROC) (GLenum target, GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD4IPROC) (GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD4IARBPROC) (GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD4IVPROC) (GLenum target, GLint const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD4IVARBPROC) (GLenum target, GLint const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD4SPROC) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD4SARBPROC) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD4SVPROC) (GLenum target, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORD4SVARBPROC) (GLenum target, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLMULTITEXCOORDPOINTEREXTPROC) (GLenum texunit, GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (GLAPIENTRY * PFNGLMULTITEXENVFEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLfloat param);
typedef void (GLAPIENTRY * PFNGLMULTITEXENVFVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLfloat const * params);
typedef void (GLAPIENTRY * PFNGLMULTITEXENVIEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLint param);
typedef void (GLAPIENTRY * PFNGLMULTITEXENVIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLint const * params);
typedef void (GLAPIENTRY * PFNGLMULTITEXGENDEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLdouble param);
typedef void (GLAPIENTRY * PFNGLMULTITEXGENDVEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLdouble const * params);
typedef void (GLAPIENTRY * PFNGLMULTITEXGENFEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLfloat param);
typedef void (GLAPIENTRY * PFNGLMULTITEXGENFVEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLfloat const * params);
typedef void (GLAPIENTRY * PFNGLMULTITEXGENIEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLint param);
typedef void (GLAPIENTRY * PFNGLMULTITEXGENIVEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLint const * params);
typedef void (GLAPIENTRY * PFNGLMULTITEXIMAGE1DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLMULTITEXIMAGE2DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLMULTITEXIMAGE3DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLMULTITEXPARAMETERFEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLfloat param);
typedef void (GLAPIENTRY * PFNGLMULTITEXPARAMETERFVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLfloat const * params);
typedef void (GLAPIENTRY * PFNGLMULTITEXPARAMETERIEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLint param);
typedef void (GLAPIENTRY * PFNGLMULTITEXPARAMETERIIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLint const * params);
typedef void (GLAPIENTRY * PFNGLMULTITEXPARAMETERIUIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLuint const * params);
typedef void (GLAPIENTRY * PFNGLMULTITEXPARAMETERIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLint const * params);
typedef void (GLAPIENTRY * PFNGLMULTITEXRENDERBUFFEREXTPROC) (GLenum texunit, GLenum target, GLuint renderbuffer);
typedef void (GLAPIENTRY * PFNGLMULTITEXSUBIMAGE1DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLMULTITEXSUBIMAGE2DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLMULTITEXSUBIMAGE3DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLMULTTRANSPOSEMATRIXDPROC) (GLdouble const * m);
typedef void (GLAPIENTRY * PFNGLMULTTRANSPOSEMATRIXDARBPROC) (GLdouble const * m);
typedef void (GLAPIENTRY * PFNGLMULTTRANSPOSEMATRIXFARBPROC) (GLfloat const * m);
typedef void (GLAPIENTRY * PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC) (GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (GLAPIENTRY * PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC) (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (GLAPIENTRY * PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC) (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (GLAPIENTRY * PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC) (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (GLAPIENTRY * PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
typedef void (GLAPIENTRY * PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLenum face);
typedef void (GLAPIENTRY * PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (GLAPIENTRY * PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC) (GLuint program, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLAPIENTRY * PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC) (GLuint program, GLenum target, GLuint index, GLdouble const * params);
typedef void (GLAPIENTRY * PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC) (GLuint program, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLAPIENTRY * PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC) (GLuint program, GLenum target, GLuint index, GLfloat const * params);
typedef void (GLAPIENTRY * PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC) (GLuint program, GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (GLAPIENTRY * PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC) (GLuint program, GLenum target, GLuint index, GLint const * params);
typedef void (GLAPIENTRY * PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC) (GLuint program, GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (GLAPIENTRY * PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC) (GLuint program, GLenum target, GLuint index, GLuint const * params);
typedef void (GLAPIENTRY * PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC) (GLuint program, GLenum target, GLuint index, GLsizei count, GLfloat const * params);
typedef void (GLAPIENTRY * PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC) (GLuint program, GLenum target, GLuint index, GLsizei count, GLint const * params);
typedef void (GLAPIENTRY * PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC) (GLuint program, GLenum target, GLuint index, GLsizei count, GLuint const * params);
typedef void (GLAPIENTRY * PFNGLNAMEDPROGRAMSTRINGEXTPROC) (GLuint program, GLenum target, GLenum format, GLsizei len, const void * string);
typedef void (GLAPIENTRY * PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC) (GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY * PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC) (GLuint renderbuffer, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY * PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY * PFNGLNORMAL3HNVPROC) (GLhalfNV nx, GLhalfNV ny, GLhalfNV nz);
typedef void (GLAPIENTRY * PFNGLNORMAL3HVNVPROC) (GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLNORMALPOINTEREXTPROC) (GLenum type, GLsizei stride, GLsizei count, const void * pointer);
typedef void (GLAPIENTRY * PFNGLPIXELDATARANGENVPROC) (GLenum target, GLsizei length, const void * pointer);
typedef void (GLAPIENTRY * PFNGLPOINTPARAMETERFARBPROC) (GLenum pname, GLfloat param);
typedef void (GLAPIENTRY * PFNGLPOINTPARAMETERFEXTPROC) (GLenum pname, GLfloat param);
typedef void (GLAPIENTRY * PFNGLPOINTPARAMETERFVARBPROC) (GLenum pname, GLfloat const * params);
typedef void (GLAPIENTRY * PFNGLPOINTPARAMETERFVEXTPROC) (GLenum pname, GLfloat const * params);
typedef void (GLAPIENTRY * PFNGLPOINTPARAMETERINVPROC) (GLenum pname, GLint param);
typedef void (GLAPIENTRY * PFNGLPOINTPARAMETERIVPROC) (GLenum pname, GLint const * params);
typedef void (GLAPIENTRY * PFNGLPOINTPARAMETERIVNVPROC) (GLenum pname, GLint const * params);
typedef void (GLAPIENTRY * PFNGLPRESENTFRAMEDUALFILLNVPROC) (GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLenum target1, GLuint fill1, GLenum target2, GLuint fill2, GLenum target3, GLuint fill3);
typedef void (GLAPIENTRY * PFNGLPRESENTFRAMEKEYEDNVPROC) (GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLuint key0, GLenum target1, GLuint fill1, GLuint key1);
typedef void (GLAPIENTRY * PFNGLPRIMITIVERESTARTNVPROC) ();
typedef void (GLAPIENTRY * PFNGLPRIORITIZETEXTURESEXTPROC) (GLsizei n, GLuint const * textures, GLclampf const * priorities);
typedef void (GLAPIENTRY * PFNGLPROGRAMBUFFERPARAMETERSIIVNVPROC) (GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, GLint const * params);
typedef void (GLAPIENTRY * PFNGLPROGRAMBUFFERPARAMETERSIUIVNVPROC) (GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, GLuint const * params);
typedef void (GLAPIENTRY * PFNGLPROGRAMENVPARAMETER4DARBPROC) (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLAPIENTRY * PFNGLPROGRAMENVPARAMETER4DVARBPROC) (GLenum target, GLuint index, GLdouble const * params);
typedef void (GLAPIENTRY * PFNGLPROGRAMENVPARAMETERI4INVPROC) (GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (GLAPIENTRY * PFNGLPROGRAMENVPARAMETERI4IVNVPROC) (GLenum target, GLuint index, GLint const * params);
typedef void (GLAPIENTRY * PFNGLPROGRAMENVPARAMETERI4UINVPROC) (GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (GLAPIENTRY * PFNGLPROGRAMENVPARAMETERI4UIVNVPROC) (GLenum target, GLuint index, GLuint const * params);
typedef void (GLAPIENTRY * PFNGLPROGRAMENVPARAMETERSI4IVNVPROC) (GLenum target, GLuint index, GLsizei count, GLint const * params);
typedef void (GLAPIENTRY * PFNGLPROGRAMENVPARAMETERSI4UIVNVPROC) (GLenum target, GLuint index, GLsizei count, GLuint const * params);
typedef void (GLAPIENTRY * PFNGLPROGRAMLOCALPARAMETER4DARBPROC) (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLAPIENTRY * PFNGLPROGRAMLOCALPARAMETER4DVARBPROC) (GLenum target, GLuint index, GLdouble const * params);
typedef void (GLAPIENTRY * PFNGLPROGRAMLOCALPARAMETERI4INVPROC) (GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (GLAPIENTRY * PFNGLPROGRAMLOCALPARAMETERI4IVNVPROC) (GLenum target, GLuint index, GLint const * params);
typedef void (GLAPIENTRY * PFNGLPROGRAMLOCALPARAMETERI4UINVPROC) (GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (GLAPIENTRY * PFNGLPROGRAMLOCALPARAMETERI4UIVNVPROC) (GLenum target, GLuint index, GLuint const * params);
typedef void (GLAPIENTRY * PFNGLPROGRAMLOCALPARAMETERSI4IVNVPROC) (GLenum target, GLuint index, GLsizei count, GLint const * params);
typedef void (GLAPIENTRY * PFNGLPROGRAMLOCALPARAMETERSI4UIVNVPROC) (GLenum target, GLuint index, GLsizei count, GLuint const * params);
typedef void (GLAPIENTRY * PFNGLPROGRAMNAMEDPARAMETER4DNVPROC) (GLuint id, GLsizei len, GLubyte const * name, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLAPIENTRY * PFNGLPROGRAMNAMEDPARAMETER4DVNVPROC) (GLuint id, GLsizei len, GLubyte const * name, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLPROGRAMNAMEDPARAMETER4FNVPROC) (GLuint id, GLsizei len, GLubyte const * name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLAPIENTRY * PFNGLPROGRAMNAMEDPARAMETER4FVNVPROC) (GLuint id, GLsizei len, GLubyte const * name, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLPROGRAMPARAMETER4DNVPROC) (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLAPIENTRY * PFNGLPROGRAMPARAMETER4DVNVPROC) (GLenum target, GLuint index, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLPROGRAMPARAMETER4FNVPROC) (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLAPIENTRY * PFNGLPROGRAMPARAMETER4FVNVPROC) (GLenum target, GLuint index, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLPROGRAMPARAMETERIARBPROC) (GLuint program, GLenum pname, GLint value);
typedef void (GLAPIENTRY * PFNGLPROGRAMPARAMETERIEXTPROC) (GLuint program, GLenum pname, GLint value);
typedef void (GLAPIENTRY * PFNGLPROGRAMPARAMETERS4DVNVPROC) (GLenum target, GLuint index, GLsizei count, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLPROGRAMPARAMETERS4FVNVPROC) (GLenum target, GLuint index, GLsizei count, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLPROGRAMSTRINGARBPROC) (GLenum target, GLenum format, GLsizei len, const void * string);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM1FEXTPROC) (GLuint program, GLint location, GLfloat v0);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM1FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM1IEXTPROC) (GLuint program, GLint location, GLint v0);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM1IVEXTPROC) (GLuint program, GLint location, GLsizei count, GLint const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM1UIEXTPROC) (GLuint program, GLint location, GLuint v0);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM1UIVEXTPROC) (GLuint program, GLint location, GLsizei count, GLuint const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM2FEXTPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM2FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM2IEXTPROC) (GLuint program, GLint location, GLint v0, GLint v1);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM2IVEXTPROC) (GLuint program, GLint location, GLsizei count, GLint const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM2UIEXTPROC) (GLuint program, GLint location, GLuint v0, GLuint v1);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM2UIVEXTPROC) (GLuint program, GLint location, GLsizei count, GLuint const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM3FEXTPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM3FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM3IEXTPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM3IVEXTPROC) (GLuint program, GLint location, GLsizei count, GLint const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM3UIEXTPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM3UIVEXTPROC) (GLuint program, GLint location, GLsizei count, GLuint const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM4FEXTPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM4FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM4IEXTPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM4IVEXTPROC) (GLuint program, GLint location, GLsizei count, GLint const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM4UIEXTPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM4UIVEXTPROC) (GLuint program, GLint location, GLsizei count, GLuint const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLPROGRAMVERTEXLIMITNVPROC) (GLenum target, GLint limit);
typedef void (GLAPIENTRY * PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC) (GLbitfield mask);
typedef void (GLAPIENTRY * PFNGLQUERYCOUNTERPROC) (GLuint id, GLenum target);
typedef void (GLAPIENTRY * PFNGLRENDERBUFFERSTORAGEPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY * PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY * PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY * PFNGLREQUESTRESIDENTPROGRAMSNVPROC) (GLsizei n, GLuint const * programs);
typedef void (GLAPIENTRY * PFNGLRESETHISTOGRAMPROC) (GLenum target);
typedef void (GLAPIENTRY * PFNGLRESETMINMAXPROC) (GLenum target);
typedef void (GLAPIENTRY * PFNGLSAMPLECOVERAGEPROC) (GLfloat value, GLboolean invert);
typedef void (GLAPIENTRY * PFNGLSAMPLECOVERAGEARBPROC) (GLfloat value, GLboolean invert);
typedef void (GLAPIENTRY * PFNGLSAMPLEMASKINDEXEDNVPROC) (GLuint index, GLbitfield mask);
typedef void (GLAPIENTRY * PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
typedef void (GLAPIENTRY * PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat const * param);
typedef void (GLAPIENTRY * PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3BPROC) (GLbyte red, GLbyte green, GLbyte blue);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3BEXTPROC) (GLbyte red, GLbyte green, GLbyte blue);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3BVPROC) (GLbyte const * v);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3BVEXTPROC) (GLbyte const * v);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3DPROC) (GLdouble red, GLdouble green, GLdouble blue);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3DEXTPROC) (GLdouble red, GLdouble green, GLdouble blue);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3DVPROC) (GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3DVEXTPROC) (GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3FPROC) (GLfloat red, GLfloat green, GLfloat blue);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3FEXTPROC) (GLfloat red, GLfloat green, GLfloat blue);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3FVPROC) (GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3FVEXTPROC) (GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3HNVPROC) (GLhalfNV red, GLhalfNV green, GLhalfNV blue);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3HVNVPROC) (GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3IPROC) (GLint red, GLint green, GLint blue);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3IEXTPROC) (GLint red, GLint green, GLint blue);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3IVPROC) (GLint const * v);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3IVEXTPROC) (GLint const * v);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3SPROC) (GLshort red, GLshort green, GLshort blue);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3SEXTPROC) (GLshort red, GLshort green, GLshort blue);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3SVPROC) (GLshort const * v);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3SVEXTPROC) (GLshort const * v);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3UBPROC) (GLubyte red, GLubyte green, GLubyte blue);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3UBEXTPROC) (GLubyte red, GLubyte green, GLubyte blue);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3UBVPROC) (GLubyte const * v);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3UBVEXTPROC) (GLubyte const * v);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3UIPROC) (GLuint red, GLuint green, GLuint blue);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3UIEXTPROC) (GLuint red, GLuint green, GLuint blue);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3UIVPROC) (GLuint const * v);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3UIVEXTPROC) (GLuint const * v);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3USPROC) (GLushort red, GLushort green, GLushort blue);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3USEXTPROC) (GLushort red, GLushort green, GLushort blue);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3USVPROC) (GLushort const * v);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLOR3USVEXTPROC) (GLushort const * v);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLORPOINTERPROC) (GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (GLAPIENTRY * PFNGLSECONDARYCOLORPOINTEREXTPROC) (GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (GLAPIENTRY * PFNGLSEPARABLEFILTER2DPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * row, const void * column);
typedef void (GLAPIENTRY * PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
typedef void (GLAPIENTRY * PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, GLchar const *const* string, GLint const * length);
typedef void (GLAPIENTRY * PFNGLSHADERSOURCEARBPROC) (GLhandleARB shaderObj, GLsizei count, GLcharARB const ** string, GLint const * length);
typedef void (GLAPIENTRY * PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint mask);
typedef void (GLAPIENTRY * PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint mask);
typedef void (GLAPIENTRY * PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef GLboolean (GLAPIENTRY * PFNGLTESTFENCENVPROC) (GLuint fence);
typedef void (GLAPIENTRY * PFNGLTEXBUFFERARBPROC) (GLenum target, GLenum internalformat, GLuint buffer);
typedef void (GLAPIENTRY * PFNGLTEXBUFFEREXTPROC) (GLenum target, GLenum internalformat, GLuint buffer);
typedef void (GLAPIENTRY * PFNGLTEXCOORD1HNVPROC) (GLhalfNV s);
typedef void (GLAPIENTRY * PFNGLTEXCOORD1HVNVPROC) (GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLTEXCOORD2HNVPROC) (GLhalfNV s, GLhalfNV t);
typedef void (GLAPIENTRY * PFNGLTEXCOORD2HVNVPROC) (GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLTEXCOORD3HNVPROC) (GLhalfNV s, GLhalfNV t, GLhalfNV r);
typedef void (GLAPIENTRY * PFNGLTEXCOORD3HVNVPROC) (GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLTEXCOORD4HNVPROC) (GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q);
typedef void (GLAPIENTRY * PFNGLTEXCOORD4HVNVPROC) (GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLTEXCOORDPOINTEREXTPROC) (GLint size, GLenum type, GLsizei stride, GLsizei count, const void * pointer);
typedef void (GLAPIENTRY * PFNGLTEXIMAGE3DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLTEXIMAGE3DEXTPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLTEXPARAMETERIIVPROC) (GLenum target, GLenum pname, GLint const * params);
typedef void (GLAPIENTRY * PFNGLTEXPARAMETERIIVEXTPROC) (GLenum target, GLenum pname, GLint const * params);
typedef void (GLAPIENTRY * PFNGLTEXPARAMETERIUIVPROC) (GLenum target, GLenum pname, GLuint const * params);
typedef void (GLAPIENTRY * PFNGLTEXPARAMETERIUIVEXTPROC) (GLenum target, GLenum pname, GLuint const * params);
typedef void (GLAPIENTRY * PFNGLTEXRENDERBUFFERNVPROC) (GLenum target, GLuint renderbuffer);
typedef void (GLAPIENTRY * PFNGLTEXSTORAGE2DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY * PFNGLTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLTEXSUBIMAGE3DEXTPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLTEXTUREBARRIERNVPROC) ();
typedef void (GLAPIENTRY * PFNGLTEXTUREBUFFEREXTPROC) (GLuint texture, GLenum target, GLenum internalformat, GLuint buffer);
typedef void (GLAPIENTRY * PFNGLTEXTUREIMAGE1DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLTEXTUREIMAGE2DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLTEXTUREIMAGE3DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLTEXTUREPARAMETERFEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLfloat param);
typedef void (GLAPIENTRY * PFNGLTEXTUREPARAMETERFVEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLfloat const * params);
typedef void (GLAPIENTRY * PFNGLTEXTUREPARAMETERIEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLint param);
typedef void (GLAPIENTRY * PFNGLTEXTUREPARAMETERIIVEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLint const * params);
typedef void (GLAPIENTRY * PFNGLTEXTUREPARAMETERIUIVEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLuint const * params);
typedef void (GLAPIENTRY * PFNGLTEXTUREPARAMETERIVEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLint const * params);
typedef void (GLAPIENTRY * PFNGLTEXTURERENDERBUFFEREXTPROC) (GLuint texture, GLenum target, GLuint renderbuffer);
typedef void (GLAPIENTRY * PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY * PFNGLTEXTURESUBIMAGE1DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLTEXTURESUBIMAGE2DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLTEXTURESUBIMAGE3DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels);
typedef void (GLAPIENTRY * PFNGLTRACKMATRIXNVPROC) (GLenum target, GLuint address, GLenum matrix, GLenum transform);
typedef void (GLAPIENTRY * PFNGLTRANSFORMFEEDBACKATTRIBSNVPROC) (GLsizei count, GLint const * attribs, GLenum bufferMode);
typedef void (GLAPIENTRY * PFNGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint program, GLsizei count, GLchar const *const* varyings, GLenum bufferMode);
typedef void (GLAPIENTRY * PFNGLTRANSFORMFEEDBACKVARYINGSNVPROC) (GLuint program, GLsizei count, GLint const * locations, GLenum bufferMode);
typedef void (GLAPIENTRY * PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
typedef void (GLAPIENTRY * PFNGLUNIFORM1FARBPROC) (GLint location, GLfloat v0);
typedef void (GLAPIENTRY * PFNGLUNIFORM1FVPROC) (GLint location, GLsizei count, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM1FVARBPROC) (GLint location, GLsizei count, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
typedef void (GLAPIENTRY * PFNGLUNIFORM1IARBPROC) (GLint location, GLint v0);
typedef void (GLAPIENTRY * PFNGLUNIFORM1IVPROC) (GLint location, GLsizei count, GLint const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM1IVARBPROC) (GLint location, GLsizei count, GLint const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM1UIPROC) (GLint location, GLuint v0);
typedef void (GLAPIENTRY * PFNGLUNIFORM1UIEXTPROC) (GLint location, GLuint v0);
typedef void (GLAPIENTRY * PFNGLUNIFORM1UIVPROC) (GLint location, GLsizei count, GLuint const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM1UIVEXTPROC) (GLint location, GLsizei count, GLuint const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
typedef void (GLAPIENTRY * PFNGLUNIFORM2FARBPROC) (GLint location, GLfloat v0, GLfloat v1);
typedef void (GLAPIENTRY * PFNGLUNIFORM2FVPROC) (GLint location, GLsizei count, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM2FVARBPROC) (GLint location, GLsizei count, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
typedef void (GLAPIENTRY * PFNGLUNIFORM2IARBPROC) (GLint location, GLint v0, GLint v1);
typedef void (GLAPIENTRY * PFNGLUNIFORM2IVPROC) (GLint location, GLsizei count, GLint const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM2IVARBPROC) (GLint location, GLsizei count, GLint const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM2UIPROC) (GLint location, GLuint v0, GLuint v1);
typedef void (GLAPIENTRY * PFNGLUNIFORM2UIEXTPROC) (GLint location, GLuint v0, GLuint v1);
typedef void (GLAPIENTRY * PFNGLUNIFORM2UIVPROC) (GLint location, GLsizei count, GLuint const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM2UIVEXTPROC) (GLint location, GLsizei count, GLuint const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (GLAPIENTRY * PFNGLUNIFORM3FARBPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (GLAPIENTRY * PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM3FVARBPROC) (GLint location, GLsizei count, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
typedef void (GLAPIENTRY * PFNGLUNIFORM3IARBPROC) (GLint location, GLint v0, GLint v1, GLint v2);
typedef void (GLAPIENTRY * PFNGLUNIFORM3IVPROC) (GLint location, GLsizei count, GLint const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM3IVARBPROC) (GLint location, GLsizei count, GLint const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM3UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (GLAPIENTRY * PFNGLUNIFORM3UIEXTPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (GLAPIENTRY * PFNGLUNIFORM3UIVPROC) (GLint location, GLsizei count, GLuint const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM3UIVEXTPROC) (GLint location, GLsizei count, GLuint const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (GLAPIENTRY * PFNGLUNIFORM4FARBPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (GLAPIENTRY * PFNGLUNIFORM4FVPROC) (GLint location, GLsizei count, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM4FVARBPROC) (GLint location, GLsizei count, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (GLAPIENTRY * PFNGLUNIFORM4IARBPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (GLAPIENTRY * PFNGLUNIFORM4IVPROC) (GLint location, GLsizei count, GLint const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM4IVARBPROC) (GLint location, GLsizei count, GLint const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM4UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (GLAPIENTRY * PFNGLUNIFORM4UIEXTPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (GLAPIENTRY * PFNGLUNIFORM4UIVPROC) (GLint location, GLsizei count, GLuint const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORM4UIVEXTPROC) (GLint location, GLsizei count, GLuint const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORMBUFFEREXTPROC) (GLuint program, GLint location, GLuint buffer);
typedef void (GLAPIENTRY * PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORMMATRIX2FVARBPROC) (GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORMMATRIX2X3FVPROC) (GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORMMATRIX2X4FVPROC) (GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORMMATRIX3FVARBPROC) (GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORMMATRIX3X2FVPROC) (GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORMMATRIX3X4FVPROC) (GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORMMATRIX4FVARBPROC) (GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORMMATRIX4X2FVPROC) (GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNIFORMMATRIX4X3FVPROC) (GLint location, GLsizei count, GLboolean transpose, GLfloat const * value);
typedef void (GLAPIENTRY * PFNGLUNLOCKARRAYSEXTPROC) ();
typedef GLboolean (GLAPIENTRY * PFNGLUNMAPBUFFERPROC) (GLenum target);
typedef GLboolean (GLAPIENTRY * PFNGLUNMAPBUFFERARBPROC) (GLenum target);
typedef void (GLAPIENTRY * PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void (GLAPIENTRY * PFNGLUSEPROGRAMOBJECTARBPROC) (GLhandleARB programObj);
typedef void (GLAPIENTRY * PFNGLVALIDATEPROGRAMPROC) (GLuint program);
typedef void (GLAPIENTRY * PFNGLVALIDATEPROGRAMARBPROC) (GLhandleARB programObj);
typedef void (GLAPIENTRY * PFNGLVERTEX2HNVPROC) (GLhalfNV x, GLhalfNV y);
typedef void (GLAPIENTRY * PFNGLVERTEX2HVNVPROC) (GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLVERTEX3HNVPROC) (GLhalfNV x, GLhalfNV y, GLhalfNV z);
typedef void (GLAPIENTRY * PFNGLVERTEX3HVNVPROC) (GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLVERTEX4HNVPROC) (GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w);
typedef void (GLAPIENTRY * PFNGLVERTEX4HVNVPROC) (GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXARRAYRANGENVPROC) (GLsizei length, const void * pointer);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1DPROC) (GLuint index, GLdouble x);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1DARBPROC) (GLuint index, GLdouble x);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1DNVPROC) (GLuint index, GLdouble x);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1DVPROC) (GLuint index, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1DVARBPROC) (GLuint index, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1DVNVPROC) (GLuint index, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1FPROC) (GLuint index, GLfloat x);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1FARBPROC) (GLuint index, GLfloat x);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1FNVPROC) (GLuint index, GLfloat x);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1FVPROC) (GLuint index, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1FVARBPROC) (GLuint index, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1FVNVPROC) (GLuint index, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1HNVPROC) (GLuint index, GLhalfNV x);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1HVNVPROC) (GLuint index, GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1SPROC) (GLuint index, GLshort x);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1SARBPROC) (GLuint index, GLshort x);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1SNVPROC) (GLuint index, GLshort x);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1SVPROC) (GLuint index, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1SVARBPROC) (GLuint index, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB1SVNVPROC) (GLuint index, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2DPROC) (GLuint index, GLdouble x, GLdouble y);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2DARBPROC) (GLuint index, GLdouble x, GLdouble y);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2DNVPROC) (GLuint index, GLdouble x, GLdouble y);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2DVPROC) (GLuint index, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2DVARBPROC) (GLuint index, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2DVNVPROC) (GLuint index, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2FPROC) (GLuint index, GLfloat x, GLfloat y);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2FARBPROC) (GLuint index, GLfloat x, GLfloat y);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2FNVPROC) (GLuint index, GLfloat x, GLfloat y);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2FVPROC) (GLuint index, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2FVARBPROC) (GLuint index, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2FVNVPROC) (GLuint index, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2HNVPROC) (GLuint index, GLhalfNV x, GLhalfNV y);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2HVNVPROC) (GLuint index, GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2SPROC) (GLuint index, GLshort x, GLshort y);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2SARBPROC) (GLuint index, GLshort x, GLshort y);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2SNVPROC) (GLuint index, GLshort x, GLshort y);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2SVPROC) (GLuint index, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2SVARBPROC) (GLuint index, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB2SVNVPROC) (GLuint index, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3DARBPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3DNVPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3DVPROC) (GLuint index, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3DVARBPROC) (GLuint index, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3DVNVPROC) (GLuint index, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3FARBPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3FNVPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3FVPROC) (GLuint index, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3FVARBPROC) (GLuint index, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3FVNVPROC) (GLuint index, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3HNVPROC) (GLuint index, GLhalfNV x, GLhalfNV y, GLhalfNV z);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3HVNVPROC) (GLuint index, GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3SPROC) (GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3SARBPROC) (GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3SNVPROC) (GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3SVPROC) (GLuint index, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3SVARBPROC) (GLuint index, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB3SVNVPROC) (GLuint index, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4BVPROC) (GLuint index, GLbyte const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4BVARBPROC) (GLuint index, GLbyte const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4DARBPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4DNVPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4DVPROC) (GLuint index, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4DVARBPROC) (GLuint index, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4DVNVPROC) (GLuint index, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4FARBPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4FNVPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4FVPROC) (GLuint index, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4FVARBPROC) (GLuint index, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4FVNVPROC) (GLuint index, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4HNVPROC) (GLuint index, GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4HVNVPROC) (GLuint index, GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4IVPROC) (GLuint index, GLint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4IVARBPROC) (GLuint index, GLint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4NBVPROC) (GLuint index, GLbyte const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4NBVARBPROC) (GLuint index, GLbyte const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4NIVPROC) (GLuint index, GLint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4NIVARBPROC) (GLuint index, GLint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4NSVPROC) (GLuint index, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4NSVARBPROC) (GLuint index, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4NUBPROC) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4NUBARBPROC) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4NUBVPROC) (GLuint index, GLubyte const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4NUBVARBPROC) (GLuint index, GLubyte const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4NUIVPROC) (GLuint index, GLuint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4NUIVARBPROC) (GLuint index, GLuint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4NUSVPROC) (GLuint index, GLushort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4NUSVARBPROC) (GLuint index, GLushort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4SPROC) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4SARBPROC) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4SNVPROC) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4SVPROC) (GLuint index, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4SVARBPROC) (GLuint index, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4SVNVPROC) (GLuint index, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4UBNVPROC) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4UBVPROC) (GLuint index, GLubyte const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4UBVARBPROC) (GLuint index, GLubyte const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4UBVNVPROC) (GLuint index, GLubyte const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4UIVPROC) (GLuint index, GLuint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4UIVARBPROC) (GLuint index, GLuint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4USVPROC) (GLuint index, GLushort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIB4USVARBPROC) (GLuint index, GLushort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI1IPROC) (GLuint index, GLint x);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI1IEXTPROC) (GLuint index, GLint x);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI1IVPROC) (GLuint index, GLint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI1IVEXTPROC) (GLuint index, GLint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI1UIPROC) (GLuint index, GLuint x);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI1UIEXTPROC) (GLuint index, GLuint x);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI1UIVPROC) (GLuint index, GLuint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI1UIVEXTPROC) (GLuint index, GLuint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI2IPROC) (GLuint index, GLint x, GLint y);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI2IEXTPROC) (GLuint index, GLint x, GLint y);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI2IVPROC) (GLuint index, GLint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI2IVEXTPROC) (GLuint index, GLint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI2UIPROC) (GLuint index, GLuint x, GLuint y);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI2UIEXTPROC) (GLuint index, GLuint x, GLuint y);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI2UIVPROC) (GLuint index, GLuint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI2UIVEXTPROC) (GLuint index, GLuint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI3IPROC) (GLuint index, GLint x, GLint y, GLint z);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI3IEXTPROC) (GLuint index, GLint x, GLint y, GLint z);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI3IVPROC) (GLuint index, GLint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI3IVEXTPROC) (GLuint index, GLint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI3UIPROC) (GLuint index, GLuint x, GLuint y, GLuint z);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI3UIEXTPROC) (GLuint index, GLuint x, GLuint y, GLuint z);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI3UIVPROC) (GLuint index, GLuint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI3UIVEXTPROC) (GLuint index, GLuint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI4BVPROC) (GLuint index, GLbyte const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI4BVEXTPROC) (GLuint index, GLbyte const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI4IPROC) (GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI4IEXTPROC) (GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI4IVPROC) (GLuint index, GLint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI4IVEXTPROC) (GLuint index, GLint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI4SVPROC) (GLuint index, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI4SVEXTPROC) (GLuint index, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI4UBVPROC) (GLuint index, GLubyte const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI4UBVEXTPROC) (GLuint index, GLubyte const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI4UIPROC) (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI4UIEXTPROC) (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI4UIVPROC) (GLuint index, GLuint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI4UIVEXTPROC) (GLuint index, GLuint const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI4USVPROC) (GLuint index, GLushort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBI4USVEXTPROC) (GLuint index, GLushort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBIPOINTEREXTPROC) (GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBPOINTERNVPROC) (GLuint index, GLint fsize, GLenum type, GLsizei stride, const void * pointer);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBS1DVNVPROC) (GLuint index, GLsizei count, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBS1FVNVPROC) (GLuint index, GLsizei count, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBS1HVNVPROC) (GLuint index, GLsizei n, GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBS1SVNVPROC) (GLuint index, GLsizei count, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBS2DVNVPROC) (GLuint index, GLsizei count, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBS2FVNVPROC) (GLuint index, GLsizei count, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBS2HVNVPROC) (GLuint index, GLsizei n, GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBS2SVNVPROC) (GLuint index, GLsizei count, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBS3DVNVPROC) (GLuint index, GLsizei count, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBS3FVNVPROC) (GLuint index, GLsizei count, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBS3HVNVPROC) (GLuint index, GLsizei n, GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBS3SVNVPROC) (GLuint index, GLsizei count, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBS4DVNVPROC) (GLuint index, GLsizei count, GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBS4FVNVPROC) (GLuint index, GLsizei count, GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBS4HVNVPROC) (GLuint index, GLsizei n, GLhalfNV const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBS4SVNVPROC) (GLuint index, GLsizei count, GLshort const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBS4UBVNVPROC) (GLuint index, GLsizei count, GLubyte const * v);
typedef void (GLAPIENTRY * PFNGLVERTEXPOINTEREXTPROC) (GLint size, GLenum type, GLsizei stride, GLsizei count, const void * pointer);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS2DPROC) (GLdouble x, GLdouble y);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS2DARBPROC) (GLdouble x, GLdouble y);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS2DVPROC) (GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS2DVARBPROC) (GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS2FPROC) (GLfloat x, GLfloat y);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS2FARBPROC) (GLfloat x, GLfloat y);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS2FVPROC) (GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS2FVARBPROC) (GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS2IPROC) (GLint x, GLint y);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS2IARBPROC) (GLint x, GLint y);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS2IVPROC) (GLint const * v);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS2IVARBPROC) (GLint const * v);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS2SPROC) (GLshort x, GLshort y);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS2SARBPROC) (GLshort x, GLshort y);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS2SVPROC) (GLshort const * v);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS2SVARBPROC) (GLshort const * v);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS3DPROC) (GLdouble x, GLdouble y, GLdouble z);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS3DARBPROC) (GLdouble x, GLdouble y, GLdouble z);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS3DVPROC) (GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS3DVARBPROC) (GLdouble const * v);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS3FPROC) (GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS3FARBPROC) (GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS3FVPROC) (GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS3FVARBPROC) (GLfloat const * v);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS3IPROC) (GLint x, GLint y, GLint z);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS3IARBPROC) (GLint x, GLint y, GLint z);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS3IVPROC) (GLint const * v);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS3IVARBPROC) (GLint const * v);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS3SPROC) (GLshort x, GLshort y, GLshort z);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS3SARBPROC) (GLshort x, GLshort y, GLshort z);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS3SVPROC) (GLshort const * v);
typedef void (GLAPIENTRY * PFNGLWINDOWPOS3SVARBPROC) (GLshort const * v);
typedef void * (GLAPIENTRY * PFNWGLALLOCATEMEMORYNVPROC) (GLsizei size, GLfloat readfreq, GLfloat writefreq, GLfloat priority);
typedef BOOL (GLAPIENTRY * PFNWGLBINDSWAPBARRIERNVPROC) (GLuint group, GLuint barrier);
typedef BOOL (GLAPIENTRY * PFNWGLBINDTEXIMAGEARBPROC) (HPBUFFERARB hPbuffer, int iBuffer);
typedef BOOL (GLAPIENTRY * PFNWGLBINDVIDEOIMAGENVPROC) (HPVIDEODEV hVideoDevice, HPBUFFERARB hPbuffer, int iVideoBuffer);
typedef BOOL (GLAPIENTRY * PFNWGLCHOOSEPIXELFORMATARBPROC) (HDC hdc, const int * piAttribIList, FLOAT const * pfAttribFList, UINT nMaxFormats, int * piFormats, UINT * nNumFormats);
typedef HANDLE (GLAPIENTRY * PFNWGLCREATEBUFFERREGIONARBPROC) (HDC hDC, int iLayerPlane, UINT uType);
typedef HGLRC (GLAPIENTRY * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int * attribList);
typedef HPBUFFERARB (GLAPIENTRY * PFNWGLCREATEPBUFFERARBPROC) (HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int * piAttribList);
typedef VOID (GLAPIENTRY * PFNWGLDELETEBUFFERREGIONARBPROC) (HANDLE hRegion);
typedef BOOL (GLAPIENTRY * PFNWGLDESTROYPBUFFERARBPROC) (HPBUFFERARB hPbuffer);
typedef BOOL (GLAPIENTRY * PFNWGLDXCLOSEDEVICENVPROC) (HANDLE hDevice);
typedef BOOL (GLAPIENTRY * PFNWGLDXLOCKOBJECTSNVPROC) (HANDLE hDevice, GLint count, HANDLE * hObjects);
typedef HANDLE (GLAPIENTRY * PFNWGLDXOPENDEVICENVPROC) (void * dxDevice);
typedef HANDLE (GLAPIENTRY * PFNWGLDXREGISTEROBJECTNVPROC) (HANDLE hDevice, void * dxObject, GLuint name, GLenum type, GLenum access);
typedef BOOL (GLAPIENTRY * PFNWGLDXSETRESOURCESHAREHANDLENVPROC) (void * dxObject, HANDLE shareHandle);
typedef BOOL (GLAPIENTRY * PFNWGLDXUNLOCKOBJECTSNVPROC) (HANDLE hDevice, GLint count, HANDLE * hObjects);
typedef BOOL (GLAPIENTRY * PFNWGLDXUNREGISTEROBJECTNVPROC) (HANDLE hDevice, HANDLE hObject);
typedef void (GLAPIENTRY * PFNWGLFREEMEMORYNVPROC) (void * pointer);
typedef HGLRC (GLAPIENTRY * PFNWGLGETCURRENTCONTEXTPROC) ();
typedef HDC (GLAPIENTRY * PFNWGLGETCURRENTREADDCARBPROC) ();
typedef const char * (GLAPIENTRY * PFNWGLGETEXTENSIONSSTRINGARBPROC) (HDC hdc);
typedef const char * (GLAPIENTRY * PFNWGLGETEXTENSIONSSTRINGEXTPROC) ();
typedef HDC (GLAPIENTRY * PFNWGLGETPBUFFERDCARBPROC) (HPBUFFERARB hPbuffer);
typedef BOOL (GLAPIENTRY * PFNWGLGETPIXELFORMATATTRIBFVARBPROC) (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int * piAttributes, FLOAT * pfValues);
typedef BOOL (GLAPIENTRY * PFNWGLGETPIXELFORMATATTRIBIVARBPROC) (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int * piAttributes, int * piValues);
typedef PROC (GLAPIENTRY * PFNWGLGETPROCADDRESSPROC) (LPCSTR lpszProc);
typedef int (GLAPIENTRY * PFNWGLGETSWAPINTERVALEXTPROC) ();
typedef BOOL (GLAPIENTRY * PFNWGLGETVIDEODEVICENVPROC) (HDC hDC, int numDevices, HPVIDEODEV * hVideoDevice);
typedef BOOL (GLAPIENTRY * PFNWGLGETVIDEOINFONVPROC) (HPVIDEODEV hpVideoDevice, unsigned long * pulCounterOutputPbuffer, unsigned long * pulCounterOutputVideo);
typedef BOOL (GLAPIENTRY * PFNWGLJOINSWAPGROUPNVPROC) (HDC hDC, GLuint group);
typedef BOOL (GLAPIENTRY * PFNWGLMAKECONTEXTCURRENTARBPROC) (HDC hDrawDC, HDC hReadDC, HGLRC hglrc);
typedef BOOL (GLAPIENTRY * PFNWGLQUERYFRAMECOUNTNVPROC) (HDC hDC, GLuint * count);
typedef BOOL (GLAPIENTRY * PFNWGLQUERYMAXSWAPGROUPSNVPROC) (HDC hDC, GLuint * maxGroups, GLuint * maxBarriers);
typedef BOOL (GLAPIENTRY * PFNWGLQUERYPBUFFERARBPROC) (HPBUFFERARB hPbuffer, int iAttribute, int * piValue);
typedef BOOL (GLAPIENTRY * PFNWGLQUERYSWAPGROUPNVPROC) (HDC hDC, GLuint * group, GLuint * barrier);
typedef int (GLAPIENTRY * PFNWGLRELEASEPBUFFERDCARBPROC) (HPBUFFERARB hPbuffer, HDC hDC);
typedef BOOL (GLAPIENTRY * PFNWGLRELEASETEXIMAGEARBPROC) (HPBUFFERARB hPbuffer, int iBuffer);
typedef BOOL (GLAPIENTRY * PFNWGLRELEASEVIDEODEVICENVPROC) (HPVIDEODEV hVideoDevice);
typedef BOOL (GLAPIENTRY * PFNWGLRELEASEVIDEOIMAGENVPROC) (HPBUFFERARB hPbuffer, int iVideoBuffer);
typedef BOOL (GLAPIENTRY * PFNWGLRESETFRAMECOUNTNVPROC) (HDC hDC);
typedef BOOL (GLAPIENTRY * PFNWGLRESTOREBUFFERREGIONARBPROC) (HANDLE hRegion, int x, int y, int width, int height, int xSrc, int ySrc);
typedef BOOL (GLAPIENTRY * PFNWGLSAVEBUFFERREGIONARBPROC) (HANDLE hRegion, int x, int y, int width, int height);
typedef BOOL (GLAPIENTRY * PFNWGLSENDPBUFFERTOVIDEONVPROC) (HPBUFFERARB hPbuffer, int iBufferType, unsigned long * pulCounterPbuffer, BOOL bBlock);
typedef BOOL (GLAPIENTRY * PFNWGLSETPBUFFERATTRIBARBPROC) (HPBUFFERARB hPbuffer, const int * piAttribList);
typedef BOOL (GLAPIENTRY * PFNWGLSWAPINTERVALEXTPROC) (int interval);

typedef void (GLAPIENTRY * PFNGLDRAWBUFFERGLUTPROC) (GLenum buf);
typedef void (GLAPIENTRY * PFNGLENABLEGLUTPROC) (GLenum cap);
typedef void (GLAPIENTRY * PFNGLFINISHGLUTPROC) ();
typedef GLenum (GLAPIENTRY * PFNGLGETERRORGLUTPROC) ();
typedef void (GLAPIENTRY * PFNGLGETINTEGERVGLUTPROC) (GLenum pname, GLint * data);
typedef GLubyte const *  (GLAPIENTRY * PFNGLGETSTRINGGLUTPROC) (GLenum name);
typedef void (GLAPIENTRY * PFNGLPIXELSTOREIGLUTPROC) (GLenum pname, GLint param);
typedef void (GLAPIENTRY * PFNGLREADBUFFERGLUTPROC) (GLenum src);
typedef void (GLAPIENTRY * PFNGLVIEWPORTGLUTPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
typedef HGLRC (GLAPIENTRY * PFNWGLCREATECONTEXTGLUTPROC) (HDC hDc);
typedef BOOL (GLAPIENTRY * PFNWGLDELETECONTEXTGLUTPROC) (HGLRC oldContext);
typedef HGLRC (GLAPIENTRY * PFNWGLGETCURRENTCONTEXTGLUTPROC) ();
typedef HDC (GLAPIENTRY * PFNWGLGETCURRENTDCGLUTPROC) ();
typedef PROC (GLAPIENTRY * PFNWGLGETPROCADDRESSGLUTPROC) (LPCSTR lpszProc);
typedef BOOL (GLAPIENTRY * PFNWGLMAKECURRENTGLUTPROC) (HDC hDc, HGLRC newContext);

typedef void (GLAPIENTRY* PFNGLTEXPARAMETERIVPROC)(GLenum target, GLenum pname, const GLint* params);
typedef void (GLAPIENTRY* PFNGLDRAWARRAYSINSTANCEDPROC)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
typedef void (GLAPIENTRY* PFNGLPRIMITIVERESTARTINDEXPROC)(GLuint index);
typedef GLuint (GLAPIENTRY* PFNGLGETUNIFORMBLOCKINDEXPROC)(GLuint program, const GLchar* uniformBlockName);
typedef void (GLAPIENTRY* PFNGLUNIFORMBLOCKBINDINGPROC)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
typedef void (GLAPIENTRY* PFNGLGETINTEGER64I_VPROC)(GLenum target, GLuint index, GLint64* data);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBDIVISORPROC)(GLuint index, GLuint divisor);
typedef void (GLAPIENTRY* PFNGLCLEARDEPTHFPROC)(GLfloat d);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMBINARYPROC)(GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary);
typedef void (GLAPIENTRY* PFNGLPROGRAMBINARYPROC)(GLuint program, GLenum binaryFormat, const void* binary, GLsizei length);
typedef void (GLAPIENTRY* PFNGLPUSHDEBUGGROUPPROC)(GLenum source, GLuint id, GLsizei length, const GLchar* message);
typedef void (GLAPIENTRY* PFNGLPOPDEBUGGROUPPROC)();
typedef void (GLAPIENTRY* PFNGLBUFFERSTORAGEPROC)(GLenum target, GLsizeiptr size, const void* data, GLbitfield flags);
typedef void (GLAPIENTRY* PFNGLCREATEBUFFERSPROC)(GLsizei n, GLuint* buffers);
typedef void (GLAPIENTRY* PFNGLNAMEDBUFFERSTORAGEPROC)(GLuint buffer, GLsizeiptr size, const void* data, GLbitfield flags);
typedef void (GLAPIENTRY* PFNGLNAMEDBUFFERSUBDATAPROC)(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data);
typedef void* (GLAPIENTRY* PFNGLMAPNAMEDBUFFERPROC)(GLuint buffer, GLenum access);
typedef void* (GLAPIENTRY* PFNGLMAPNAMEDBUFFERRANGEPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef GLboolean (GLAPIENTRY* PFNGLUNMAPNAMEDBUFFERPROC)(GLuint buffer);
typedef void (GLAPIENTRY* PFNGLTEXTURESUBIMAGE2DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);

extern PFNGLBINDTEXTUREDLLPROC* divagl_glBindTextureDLL;
extern PFNGLBLENDFUNCDLLPROC* divagl_glBlendFuncDLL;
extern PFNGLCLEARDLLPROC* divagl_glClearDLL;
extern PFNGLCLEARCOLORDLLPROC* divagl_glClearColorDLL;
extern PFNGLCLEARDEPTHDLLPROC* divagl_glClearDepthDLL;
extern PFNGLCLEARSTENCILDLLPROC* divagl_glClearStencilDLL;
extern PFNGLCOLORMASKDLLPROC* divagl_glColorMaskDLL;
extern PFNGLCOPYTEXIMAGE2DDLLPROC* divagl_glCopyTexImage2DDLL;
extern PFNGLCOPYTEXSUBIMAGE2DDLLPROC* divagl_glCopyTexSubImage2DDLL;
extern PFNGLCULLFACEDLLPROC* divagl_glCullFaceDLL;
extern PFNGLDELETETEXTURESDLLPROC* divagl_glDeleteTexturesDLL;
extern PFNGLDEPTHFUNCDLLPROC* divagl_glDepthFuncDLL;
extern PFNGLDEPTHMASKDLLPROC* divagl_glDepthMaskDLL;
extern PFNGLDISABLEDLLPROC* divagl_glDisableDLL;
extern PFNGLDRAWARRAYSDLLPROC* divagl_glDrawArraysDLL;
extern PFNGLDRAWBUFFERDLLPROC* divagl_glDrawBufferDLL;
extern PFNGLDRAWELEMENTSDLLPROC* divagl_glDrawElementsDLL;
extern PFNGLENABLEDLLPROC* divagl_glEnableDLL;
extern PFNGLFINISHDLLPROC* divagl_glFinishDLL;
extern PFNGLFRONTFACEDLLPROC* divagl_glFrontFaceDLL;
extern PFNGLGENTEXTURESDLLPROC* divagl_glGenTexturesDLL;
extern PFNGLGETBOOLEANVDLLPROC* divagl_glGetBooleanvDLL;
extern PFNGLGETERRORDLLPROC* divagl_glGetErrorDLL;
extern PFNGLGETFLOATVDLLPROC* divagl_glGetFloatvDLL;
extern PFNGLGETINTEGERVDLLPROC* divagl_glGetIntegervDLL;
extern PFNGLGETTEXIMAGEDLLPROC* divagl_glGetTexImageDLL;
extern PFNGLISENABLEDDLLPROC* divagl_glIsEnabledDLL;
extern PFNGLPIXELSTOREIDLLPROC* divagl_glPixelStoreiDLL;
extern PFNGLPOLYGONMODEDLLPROC* divagl_glPolygonModeDLL;
extern PFNGLREADBUFFERDLLPROC* divagl_glReadBufferDLL;
extern PFNGLREADPIXELSDLLPROC* divagl_glReadPixelsDLL;
extern PFNGLSCISSORDLLPROC* divagl_glScissorDLL;
extern PFNGLTEXIMAGE1DDLLPROC* divagl_glTexImage1DDLL;
extern PFNGLTEXIMAGE2DDLLPROC* divagl_glTexImage2DDLL;
extern PFNGLTEXPARAMETERFDLLPROC* divagl_glTexParameterfDLL;
extern PFNGLTEXPARAMETERFVDLLPROC* divagl_glTexParameterfvDLL;
extern PFNGLTEXPARAMETERIDLLPROC* divagl_glTexParameteriDLL;
extern PFNGLTEXSUBIMAGE2DDLLPROC* divagl_glTexSubImage2DDLL;
extern PFNGLVIEWPORTDLLPROC* divagl_glViewportDLL;
extern PFNWGLGETPROCADDRESSDLLPROC* divagl_wglGetProcAddressDLL;

extern PFNGLACTIVESTENCILFACEEXTPROC* divagl_glActiveStencilFaceEXT;
extern PFNGLACTIVETEXTUREPROC* divagl_glActiveTexture;
extern PFNGLACTIVETEXTUREARBPROC* divagl_glActiveTextureARB;
extern PFNGLACTIVEVARYINGNVPROC* divagl_glActiveVaryingNV;
extern PFNGLAREPROGRAMSRESIDENTNVPROC* divagl_glAreProgramsResidentNV;
extern PFNGLARETEXTURESRESIDENTEXTPROC* divagl_glAreTexturesResidentEXT;
extern PFNGLARRAYELEMENTEXTPROC* divagl_glArrayElementEXT;
extern PFNGLATTACHOBJECTARBPROC* divagl_glAttachObjectARB;
extern PFNGLATTACHSHADERPROC* divagl_glAttachShader;
extern PFNGLBEGINCONDITIONALRENDERPROC* divagl_glBeginConditionalRender;
extern PFNGLBEGINCONDITIONALRENDERNVPROC* divagl_glBeginConditionalRenderNV;
extern PFNGLBEGINOCCLUSIONQUERYNVPROC* divagl_glBeginOcclusionQueryNV;
extern PFNGLBEGINQUERYPROC* divagl_glBeginQuery;
extern PFNGLBEGINQUERYARBPROC* divagl_glBeginQueryARB;
extern PFNGLBEGINTRANSFORMFEEDBACKPROC* divagl_glBeginTransformFeedback;
extern PFNGLBEGINTRANSFORMFEEDBACKNVPROC* divagl_glBeginTransformFeedbackNV;
extern PFNGLBINDATTRIBLOCATIONPROC* divagl_glBindAttribLocation;
extern PFNGLBINDATTRIBLOCATIONARBPROC* divagl_glBindAttribLocationARB;
extern PFNGLBINDBUFFERPROC* divagl_glBindBuffer;
extern PFNGLBINDBUFFERBASEPROC* divagl_glBindBufferBase;
extern PFNGLBINDBUFFEROFFSETNVPROC* divagl_glBindBufferOffsetNV;
extern PFNGLBINDBUFFERRANGEPROC* divagl_glBindBufferRange;
extern PFNGLBINDBUFFERRANGENVPROC* divagl_glBindBufferRangeNV;
extern PFNGLBINDFRAGDATALOCATIONPROC* divagl_glBindFragDataLocation;
extern PFNGLBINDFRAGDATALOCATIONEXTPROC* divagl_glBindFragDataLocationEXT;
extern PFNGLBINDFRAMEBUFFERPROC* divagl_glBindFramebuffer;
extern PFNGLBINDPROGRAMARBPROC* divagl_glBindProgramARB;
extern PFNGLBINDPROGRAMNVPROC* divagl_glBindProgramNV;
extern PFNGLBINDRENDERBUFFERPROC* divagl_glBindRenderbuffer;
extern PFNGLBINDSAMPLERPROC* divagl_glBindSampler;
extern PFNGLBINDTEXTUREEXTPROC* divagl_glBindTextureEXT;
extern PFNGLBINDVERTEXARRAYPROC* divagl_glBindVertexArray;
extern PFNGLBLENDCOLORPROC* divagl_glBlendColor;
extern PFNGLBLENDCOLOREXTPROC* divagl_glBlendColorEXT;
extern PFNGLBLENDEQUATIONPROC* divagl_glBlendEquation;
extern PFNGLBLENDEQUATIONEXTPROC* divagl_glBlendEquationEXT;
extern PFNGLBLENDEQUATIONSEPARATEPROC* divagl_glBlendEquationSeparate;
extern PFNGLBLENDEQUATIONSEPARATEEXTPROC* divagl_glBlendEquationSeparateEXT;
extern PFNGLBLENDFUNCSEPARATEPROC* divagl_glBlendFuncSeparate;
extern PFNGLBLENDFUNCSEPARATEEXTPROC* divagl_glBlendFuncSeparateEXT;
extern PFNGLBLITFRAMEBUFFERPROC* divagl_glBlitFramebuffer;
extern PFNGLBLITFRAMEBUFFEREXTPROC* divagl_glBlitFramebufferEXT;
extern PFNGLBUFFERDATAPROC* divagl_glBufferData;
extern PFNGLBUFFERSUBDATAPROC* divagl_glBufferSubData;
extern PFNGLBUFFERSUBDATAARBPROC* divagl_glBufferSubDataARB;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC* divagl_glCheckFramebufferStatus;
extern PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC* divagl_glCheckFramebufferStatusEXT;
extern PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC* divagl_glCheckNamedFramebufferStatusEXT;
extern PFNGLCLEARBUFFERFIPROC* divagl_glClearBufferfi;
extern PFNGLCLEARBUFFERFVPROC* divagl_glClearBufferfv;
extern PFNGLCLEARBUFFERIVPROC* divagl_glClearBufferiv;
extern PFNGLCLEARBUFFERUIVPROC* divagl_glClearBufferuiv;
extern PFNGLCLEARCOLORIIEXTPROC* divagl_glClearColorIiEXT;
extern PFNGLCLEARCOLORIUIEXTPROC* divagl_glClearColorIuiEXT;
extern PFNGLCLEARDEPTHDNVPROC* divagl_glClearDepthdNV;
extern PFNGLCLIENTACTIVETEXTUREARBPROC* divagl_glClientActiveTextureARB;
extern PFNGLCLIENTATTRIBDEFAULTEXTPROC* divagl_glClientAttribDefaultEXT;
extern PFNGLCOLOR3HNVPROC* divagl_glColor3hNV;
extern PFNGLCOLOR3HVNVPROC* divagl_glColor3hvNV;
extern PFNGLCOLOR4HNVPROC* divagl_glColor4hNV;
extern PFNGLCOLOR4HVNVPROC* divagl_glColor4hvNV;
extern PFNGLCOLORMASKIPROC* divagl_glColorMaski;
extern PFNGLCOLORMASKINDEXEDEXTPROC* divagl_glColorMaskIndexedEXT;
extern PFNGLCOLORPOINTEREXTPROC* divagl_glColorPointerEXT;
extern PFNGLCOLORSUBTABLEPROC* divagl_glColorSubTable;
extern PFNGLCOLORSUBTABLEEXTPROC* divagl_glColorSubTableEXT;
extern PFNGLCOLORTABLEPROC* divagl_glColorTable;
extern PFNGLCOLORTABLEEXTPROC* divagl_glColorTableEXT;
extern PFNGLCOLORTABLEPARAMETERFVPROC* divagl_glColorTableParameterfv;
extern PFNGLCOLORTABLEPARAMETERIVPROC* divagl_glColorTableParameteriv;
extern PFNGLCOMBINERINPUTNVPROC* divagl_glCombinerInputNV;
extern PFNGLCOMBINEROUTPUTNVPROC* divagl_glCombinerOutputNV;
extern PFNGLCOMBINERPARAMETERFNVPROC* divagl_glCombinerParameterfNV;
extern PFNGLCOMBINERPARAMETERFVNVPROC* divagl_glCombinerParameterfvNV;
extern PFNGLCOMBINERPARAMETERINVPROC* divagl_glCombinerParameteriNV;
extern PFNGLCOMBINERPARAMETERIVNVPROC* divagl_glCombinerParameterivNV;
extern PFNGLCOMBINERSTAGEPARAMETERFVNVPROC* divagl_glCombinerStageParameterfvNV;
extern PFNGLCOMPILESHADERPROC* divagl_glCompileShader;
extern PFNGLCOMPILESHADERARBPROC* divagl_glCompileShaderARB;
extern PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC* divagl_glCompressedMultiTexImage1DEXT;
extern PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC* divagl_glCompressedMultiTexImage2DEXT;
extern PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC* divagl_glCompressedMultiTexImage3DEXT;
extern PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC* divagl_glCompressedMultiTexSubImage1DEXT;
extern PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC* divagl_glCompressedMultiTexSubImage2DEXT;
extern PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC* divagl_glCompressedMultiTexSubImage3DEXT;
extern PFNGLCOMPRESSEDTEXIMAGE1DPROC* divagl_glCompressedTexImage1D;
extern PFNGLCOMPRESSEDTEXIMAGE1DARBPROC* divagl_glCompressedTexImage1DARB;
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC* divagl_glCompressedTexImage2D;
extern PFNGLCOMPRESSEDTEXIMAGE2DARBPROC* divagl_glCompressedTexImage2DARB;
extern PFNGLCOMPRESSEDTEXIMAGE3DPROC* divagl_glCompressedTexImage3D;
extern PFNGLCOMPRESSEDTEXIMAGE3DARBPROC* divagl_glCompressedTexImage3DARB;
extern PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC* divagl_glCompressedTexSubImage1D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC* divagl_glCompressedTexSubImage1DARB;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC* divagl_glCompressedTexSubImage2D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC* divagl_glCompressedTexSubImage2DARB;
extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC* divagl_glCompressedTexSubImage3D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC* divagl_glCompressedTexSubImage3DARB;
extern PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC* divagl_glCompressedTextureImage1DEXT;
extern PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC* divagl_glCompressedTextureImage2DEXT;
extern PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC* divagl_glCompressedTextureImage3DEXT;
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC* divagl_glCompressedTextureSubImage1DEXT;
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC* divagl_glCompressedTextureSubImage2DEXT;
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC* divagl_glCompressedTextureSubImage3DEXT;
extern PFNGLCONVOLUTIONFILTER1DPROC* divagl_glConvolutionFilter1D;
extern PFNGLCONVOLUTIONFILTER2DPROC* divagl_glConvolutionFilter2D;
extern PFNGLCONVOLUTIONPARAMETERFPROC* divagl_glConvolutionParameterf;
extern PFNGLCONVOLUTIONPARAMETERFVPROC* divagl_glConvolutionParameterfv;
extern PFNGLCONVOLUTIONPARAMETERIPROC* divagl_glConvolutionParameteri;
extern PFNGLCONVOLUTIONPARAMETERIVPROC* divagl_glConvolutionParameteriv;
extern PFNGLCOPYCOLORSUBTABLEPROC* divagl_glCopyColorSubTable;
extern PFNGLCOPYCOLORTABLEPROC* divagl_glCopyColorTable;
extern PFNGLCOPYCONVOLUTIONFILTER1DPROC* divagl_glCopyConvolutionFilter1D;
extern PFNGLCOPYCONVOLUTIONFILTER2DPROC* divagl_glCopyConvolutionFilter2D;
extern PFNGLCOPYIMAGESUBDATAPROC* divagl_glCopyImageSubData;
extern PFNGLCOPYMULTITEXIMAGE1DEXTPROC* divagl_glCopyMultiTexImage1DEXT;
extern PFNGLCOPYMULTITEXIMAGE2DEXTPROC* divagl_glCopyMultiTexImage2DEXT;
extern PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC* divagl_glCopyMultiTexSubImage1DEXT;
extern PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC* divagl_glCopyMultiTexSubImage3DEXT;
extern PFNGLCOPYTEXSUBIMAGE3DPROC* divagl_glCopyTexSubImage3D;
extern PFNGLCOPYTEXSUBIMAGE3DEXTPROC* divagl_glCopyTexSubImage3DEXT;
extern PFNGLCOPYTEXTUREIMAGE1DEXTPROC* divagl_glCopyTextureImage1DEXT;
extern PFNGLCOPYTEXTUREIMAGE2DEXTPROC* divagl_glCopyTextureImage2DEXT;
extern PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC* divagl_glCopyTextureSubImage1DEXT;
extern PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC* divagl_glCopyTextureSubImage2DEXT;
extern PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC* divagl_glCopyTextureSubImage3DEXT;
extern PFNGLCREATEPROGRAMPROC* divagl_glCreateProgram;
extern PFNGLCREATEPROGRAMOBJECTARBPROC* divagl_glCreateProgramObjectARB;
extern PFNGLCREATESHADERPROC* divagl_glCreateShader;
extern PFNGLCREATESHADEROBJECTARBPROC* divagl_glCreateShaderObjectARB;
extern PFNGLDELETEBUFFERSPROC* divagl_glDeleteBuffers;
extern PFNGLDELETEFENCESNVPROC* divagl_glDeleteFencesNV;
extern PFNGLDELETEFRAMEBUFFERSPROC* divagl_glDeleteFramebuffers;
extern PFNGLDELETEOBJECTARBPROC* divagl_glDeleteObjectARB;
extern PFNGLDELETEOCCLUSIONQUERIESNVPROC* divagl_glDeleteOcclusionQueriesNV;
extern PFNGLDELETEPROGRAMPROC* divagl_glDeleteProgram;
extern PFNGLDELETEPROGRAMSARBPROC* divagl_glDeleteProgramsARB;
extern PFNGLDELETEPROGRAMSNVPROC* divagl_glDeleteProgramsNV;
extern PFNGLDELETEQUERIESPROC* divagl_glDeleteQueries;
extern PFNGLDELETEQUERIESARBPROC* divagl_glDeleteQueriesARB;
extern PFNGLDELETERENDERBUFFERSPROC* divagl_glDeleteRenderbuffers;
extern PFNGLDELETESAMPLERSPROC* divagl_glDeleteSamplers;
extern PFNGLDELETESHADERPROC* divagl_glDeleteShader;
extern PFNGLDELETETEXTURESPROC* divagl_glDeleteTextures;
extern PFNGLDELETETEXTURESEXTPROC* divagl_glDeleteTexturesEXT;
extern PFNGLDELETEVERTEXARRAYSPROC* divagl_glDeleteVertexArrays;
extern PFNGLDEPTHBOUNDSDNVPROC* divagl_glDepthBoundsdNV;
extern PFNGLDEPTHBOUNDSEXTPROC* divagl_glDepthBoundsEXT;
extern PFNGLDEPTHRANGEDNVPROC* divagl_glDepthRangedNV;
extern PFNGLDETACHOBJECTARBPROC* divagl_glDetachObjectARB;
extern PFNGLDETACHSHADERPROC* divagl_glDetachShader;
extern PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC* divagl_glDisableClientStateIndexedEXT;
extern PFNGLDISABLEIPROC* divagl_glDisablei;
extern PFNGLDISABLEINDEXEDEXTPROC* divagl_glDisableIndexedEXT;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC* divagl_glDisableVertexAttribArray;
extern PFNGLDRAWARRAYSEXTPROC* divagl_glDrawArraysEXT;
extern PFNGLDRAWARRAYSINSTANCEDARBPROC* divagl_glDrawArraysInstancedARB;
extern PFNGLDRAWARRAYSINSTANCEDEXTPROC* divagl_glDrawArraysInstancedEXT;
extern PFNGLDRAWBUFFERSPROC* divagl_glDrawBuffers;
extern PFNGLDRAWBUFFERSARBPROC* divagl_glDrawBuffersARB;
extern PFNGLDRAWBUFFERSATIPROC* divagl_glDrawBuffersATI;
extern PFNGLDRAWELEMENTSINSTANCEDARBPROC* divagl_glDrawElementsInstancedARB;
extern PFNGLDRAWELEMENTSINSTANCEDEXTPROC* divagl_glDrawElementsInstancedEXT;
extern PFNGLDRAWRANGEELEMENTSPROC* divagl_glDrawRangeElements;
extern PFNGLDRAWRANGEELEMENTSEXTPROC* divagl_glDrawRangeElementsEXT;
extern PFNGLEDGEFLAGPOINTEREXTPROC* divagl_glEdgeFlagPointerEXT;
extern PFNGLENABLECLIENTSTATEINDEXEDEXTPROC* divagl_glEnableClientStateIndexedEXT;
extern PFNGLENABLEIPROC* divagl_glEnablei;
extern PFNGLENABLEINDEXEDEXTPROC* divagl_glEnableIndexedEXT;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC* divagl_glEnableVertexAttribArray;
extern PFNGLENDCONDITIONALRENDERPROC* divagl_glEndConditionalRender;
extern PFNGLENDCONDITIONALRENDERNVPROC* divagl_glEndConditionalRenderNV;
extern PFNGLENDOCCLUSIONQUERYNVPROC* divagl_glEndOcclusionQueryNV;
extern PFNGLENDQUERYPROC* divagl_glEndQuery;
extern PFNGLENDQUERYARBPROC* divagl_glEndQueryARB;
extern PFNGLENDTRANSFORMFEEDBACKPROC* divagl_glEndTransformFeedback;
extern PFNGLENDTRANSFORMFEEDBACKNVPROC* divagl_glEndTransformFeedbackNV;
extern PFNGLEXECUTEPROGRAMNVPROC* divagl_glExecuteProgramNV;
extern PFNGLFINALCOMBINERINPUTNVPROC* divagl_glFinalCombinerInputNV;
extern PFNGLFINISHFENCENVPROC* divagl_glFinishFenceNV;
extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC* divagl_glFlushMappedBufferRange;
extern PFNGLFLUSHPIXELDATARANGENVPROC* divagl_glFlushPixelDataRangeNV;
extern PFNGLFLUSHVERTEXARRAYRANGENVPROC* divagl_glFlushVertexArrayRangeNV;
extern PFNGLFOGCOORDDPROC* divagl_glFogCoordd;
extern PFNGLFOGCOORDDEXTPROC* divagl_glFogCoorddEXT;
extern PFNGLFOGCOORDDVPROC* divagl_glFogCoorddv;
extern PFNGLFOGCOORDDVEXTPROC* divagl_glFogCoorddvEXT;
extern PFNGLFOGCOORDFPROC* divagl_glFogCoordf;
extern PFNGLFOGCOORDFEXTPROC* divagl_glFogCoordfEXT;
extern PFNGLFOGCOORDFVPROC* divagl_glFogCoordfv;
extern PFNGLFOGCOORDFVEXTPROC* divagl_glFogCoordfvEXT;
extern PFNGLFOGCOORDHNVPROC* divagl_glFogCoordhNV;
extern PFNGLFOGCOORDHVNVPROC* divagl_glFogCoordhvNV;
extern PFNGLFOGCOORDPOINTERPROC* divagl_glFogCoordPointer;
extern PFNGLFOGCOORDPOINTEREXTPROC* divagl_glFogCoordPointerEXT;
extern PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC* divagl_glFramebufferDrawBufferEXT;
extern PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC* divagl_glFramebufferDrawBuffersEXT;
extern PFNGLFRAMEBUFFERREADBUFFEREXTPROC* divagl_glFramebufferReadBufferEXT;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC* divagl_glFramebufferRenderbuffer;
extern PFNGLFRAMEBUFFERTEXTUREPROC* divagl_glFramebufferTexture;
extern PFNGLFRAMEBUFFERTEXTURE1DPROC* divagl_glFramebufferTexture1D;
extern PFNGLFRAMEBUFFERTEXTURE1DEXTPROC* divagl_glFramebufferTexture1DEXT;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC* divagl_glFramebufferTexture2D;
extern PFNGLFRAMEBUFFERTEXTURE3DPROC* divagl_glFramebufferTexture3D;
extern PFNGLFRAMEBUFFERTEXTURE3DEXTPROC* divagl_glFramebufferTexture3DEXT;
extern PFNGLFRAMEBUFFERTEXTUREARBPROC* divagl_glFramebufferTextureARB;
extern PFNGLFRAMEBUFFERTEXTUREEXTPROC* divagl_glFramebufferTextureEXT;
extern PFNGLFRAMEBUFFERTEXTUREFACEARBPROC* divagl_glFramebufferTextureFaceARB;
extern PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC* divagl_glFramebufferTextureFaceEXT;
extern PFNGLFRAMEBUFFERTEXTURELAYERPROC* divagl_glFramebufferTextureLayer;
extern PFNGLFRAMEBUFFERTEXTURELAYERARBPROC* divagl_glFramebufferTextureLayerARB;
extern PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC* divagl_glFramebufferTextureLayerEXT;
extern PFNGLGENBUFFERSPROC* divagl_glGenBuffers;
extern PFNGLGENBUFFERSARBPROC* divagl_glGenBuffersARB;
extern PFNGLGENERATEMIPMAPPROC* divagl_glGenerateMipmap;
extern PFNGLGENERATEMIPMAPEXTPROC* divagl_glGenerateMipmapEXT;
extern PFNGLGENERATEMULTITEXMIPMAPEXTPROC* divagl_glGenerateMultiTexMipmapEXT;
extern PFNGLGENERATETEXTUREMIPMAPEXTPROC* divagl_glGenerateTextureMipmapEXT;
extern PFNGLGENFENCESNVPROC* divagl_glGenFencesNV;
extern PFNGLGENFRAMEBUFFERSPROC* divagl_glGenFramebuffers;
extern PFNGLGENOCCLUSIONQUERIESNVPROC* divagl_glGenOcclusionQueriesNV;
extern PFNGLGENPROGRAMSARBPROC* divagl_glGenProgramsARB;
extern PFNGLGENPROGRAMSNVPROC* divagl_glGenProgramsNV;
extern PFNGLGENQUERIESPROC* divagl_glGenQueries;
extern PFNGLGENQUERIESARBPROC* divagl_glGenQueriesARB;
extern PFNGLGENRENDERBUFFERSPROC* divagl_glGenRenderbuffers;
extern PFNGLGENSAMPLERSPROC* divagl_glGenSamplers;
extern PFNGLGENTEXTURESPROC* divagl_glGenTextures;
extern PFNGLGENTEXTURESEXTPROC* divagl_glGenTexturesEXT;
extern PFNGLGENVERTEXARRAYSPROC* divagl_glGenVertexArrays;
extern PFNGLGETACTIVEATTRIBPROC* divagl_glGetActiveAttrib;
extern PFNGLGETACTIVEATTRIBARBPROC* divagl_glGetActiveAttribARB;
extern PFNGLGETACTIVEUNIFORMPROC* divagl_glGetActiveUniform;
extern PFNGLGETACTIVEUNIFORMARBPROC* divagl_glGetActiveUniformARB;
extern PFNGLGETACTIVEVARYINGNVPROC* divagl_glGetActiveVaryingNV;
extern PFNGLGETATTACHEDOBJECTSARBPROC* divagl_glGetAttachedObjectsARB;
extern PFNGLGETATTACHEDSHADERSPROC* divagl_glGetAttachedShaders;
extern PFNGLGETATTRIBLOCATIONPROC* divagl_glGetAttribLocation;
extern PFNGLGETATTRIBLOCATIONARBPROC* divagl_glGetAttribLocationARB;
extern PFNGLGETBOOLEANI_VPROC* divagl_glGetBooleani_v;
extern PFNGLGETBOOLEANINDEXEDVEXTPROC* divagl_glGetBooleanIndexedvEXT;
extern PFNGLGETBUFFERPARAMETERIVPROC* divagl_glGetBufferParameteriv;
extern PFNGLGETBUFFERPARAMETERIVARBPROC* divagl_glGetBufferParameterivARB;
extern PFNGLGETBUFFERPOINTERVPROC* divagl_glGetBufferPointerv;
extern PFNGLGETBUFFERPOINTERVARBPROC* divagl_glGetBufferPointervARB;
extern PFNGLGETBUFFERSUBDATAPROC* divagl_glGetBufferSubData;
extern PFNGLGETBUFFERSUBDATAARBPROC* divagl_glGetBufferSubDataARB;
extern PFNGLGETCOLORTABLEPROC* divagl_glGetColorTable;
extern PFNGLGETCOLORTABLEEXTPROC* divagl_glGetColorTableEXT;
extern PFNGLGETCOLORTABLEPARAMETERFVPROC* divagl_glGetColorTableParameterfv;
extern PFNGLGETCOLORTABLEPARAMETERFVEXTPROC* divagl_glGetColorTableParameterfvEXT;
extern PFNGLGETCOLORTABLEPARAMETERIVPROC* divagl_glGetColorTableParameteriv;
extern PFNGLGETCOLORTABLEPARAMETERIVEXTPROC* divagl_glGetColorTableParameterivEXT;
extern PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC* divagl_glGetCombinerInputParameterfvNV;
extern PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC* divagl_glGetCombinerInputParameterivNV;
extern PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC* divagl_glGetCombinerOutputParameterfvNV;
extern PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC* divagl_glGetCombinerOutputParameterivNV;
extern PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC* divagl_glGetCombinerStageParameterfvNV;
extern PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC* divagl_glGetCompressedMultiTexImageEXT;
extern PFNGLGETCOMPRESSEDTEXIMAGEPROC* divagl_glGetCompressedTexImage;
extern PFNGLGETCOMPRESSEDTEXIMAGEARBPROC* divagl_glGetCompressedTexImageARB;
extern PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC* divagl_glGetCompressedTextureImageEXT;
extern PFNGLGETCONVOLUTIONFILTERPROC* divagl_glGetConvolutionFilter;
extern PFNGLGETCONVOLUTIONPARAMETERFVPROC* divagl_glGetConvolutionParameterfv;
extern PFNGLGETCONVOLUTIONPARAMETERIVPROC* divagl_glGetConvolutionParameteriv;
extern PFNGLGETDOUBLEINDEXEDVEXTPROC* divagl_glGetDoubleIndexedvEXT;
extern PFNGLGETFENCEIVNVPROC* divagl_glGetFenceivNV;
extern PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC* divagl_glGetFinalCombinerInputParameterfvNV;
extern PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC* divagl_glGetFinalCombinerInputParameterivNV;
extern PFNGLGETFLOATINDEXEDVEXTPROC* divagl_glGetFloatIndexedvEXT;
extern PFNGLGETFRAGDATALOCATIONPROC* divagl_glGetFragDataLocation;
extern PFNGLGETFRAGDATALOCATIONEXTPROC* divagl_glGetFragDataLocationEXT;
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC* divagl_glGetFramebufferAttachmentParameteriv;
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC* divagl_glGetFramebufferAttachmentParameterivEXT;
extern PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC* divagl_glGetFramebufferParameterivEXT;
extern PFNGLGETHANDLEARBPROC* divagl_glGetHandleARB;
extern PFNGLGETHISTOGRAMPROC* divagl_glGetHistogram;
extern PFNGLGETHISTOGRAMPARAMETERFVPROC* divagl_glGetHistogramParameterfv;
extern PFNGLGETHISTOGRAMPARAMETERIVPROC* divagl_glGetHistogramParameteriv;
extern PFNGLGETINFOLOGARBPROC* divagl_glGetInfoLogARB;
extern PFNGLGETINTEGERI_VPROC* divagl_glGetIntegeri_v;
extern PFNGLGETINTEGERINDEXEDVEXTPROC* divagl_glGetIntegerIndexedvEXT;
extern PFNGLGETMINMAXPROC* divagl_glGetMinmax;
extern PFNGLGETMINMAXPARAMETERFVPROC* divagl_glGetMinmaxParameterfv;
extern PFNGLGETMINMAXPARAMETERIVPROC* divagl_glGetMinmaxParameteriv;
extern PFNGLGETMULTISAMPLEFVNVPROC* divagl_glGetMultisamplefvNV;
extern PFNGLGETMULTITEXENVFVEXTPROC* divagl_glGetMultiTexEnvfvEXT;
extern PFNGLGETMULTITEXENVIVEXTPROC* divagl_glGetMultiTexEnvivEXT;
extern PFNGLGETMULTITEXGENDVEXTPROC* divagl_glGetMultiTexGendvEXT;
extern PFNGLGETMULTITEXGENFVEXTPROC* divagl_glGetMultiTexGenfvEXT;
extern PFNGLGETMULTITEXGENIVEXTPROC* divagl_glGetMultiTexGenivEXT;
extern PFNGLGETMULTITEXIMAGEEXTPROC* divagl_glGetMultiTexImageEXT;
extern PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC* divagl_glGetMultiTexLevelParameterfvEXT;
extern PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC* divagl_glGetMultiTexLevelParameterivEXT;
extern PFNGLGETMULTITEXPARAMETERFVEXTPROC* divagl_glGetMultiTexParameterfvEXT;
extern PFNGLGETMULTITEXPARAMETERIIVEXTPROC* divagl_glGetMultiTexParameterIivEXT;
extern PFNGLGETMULTITEXPARAMETERIUIVEXTPROC* divagl_glGetMultiTexParameterIuivEXT;
extern PFNGLGETMULTITEXPARAMETERIVEXTPROC* divagl_glGetMultiTexParameterivEXT;
extern PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC* divagl_glGetNamedBufferParameterivEXT;
extern PFNGLGETNAMEDBUFFERPOINTERVEXTPROC* divagl_glGetNamedBufferPointervEXT;
extern PFNGLGETNAMEDBUFFERSUBDATAEXTPROC* divagl_glGetNamedBufferSubDataEXT;
extern PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC* divagl_glGetNamedFramebufferAttachmentParameterivEXT;
extern PFNGLGETNAMEDPROGRAMIVEXTPROC* divagl_glGetNamedProgramivEXT;
extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC* divagl_glGetNamedProgramLocalParameterdvEXT;
extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC* divagl_glGetNamedProgramLocalParameterfvEXT;
extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC* divagl_glGetNamedProgramLocalParameterIivEXT;
extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC* divagl_glGetNamedProgramLocalParameterIuivEXT;
extern PFNGLGETNAMEDPROGRAMSTRINGEXTPROC* divagl_glGetNamedProgramStringEXT;
extern PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC* divagl_glGetNamedRenderbufferParameterivEXT;
extern PFNGLGETOBJECTPARAMETERFVARBPROC* divagl_glGetObjectParameterfvARB;
extern PFNGLGETOBJECTPARAMETERIVARBPROC* divagl_glGetObjectParameterivARB;
extern PFNGLGETOCCLUSIONQUERYIVNVPROC* divagl_glGetOcclusionQueryivNV;
extern PFNGLGETOCCLUSIONQUERYUIVNVPROC* divagl_glGetOcclusionQueryuivNV;
extern PFNGLGETPOINTERINDEXEDVEXTPROC* divagl_glGetPointerIndexedvEXT;
extern PFNGLGETPOINTERVEXTPROC* divagl_glGetPointervEXT;
extern PFNGLGETPROGRAMENVPARAMETERDVARBPROC* divagl_glGetProgramEnvParameterdvARB;
extern PFNGLGETPROGRAMENVPARAMETERIIVNVPROC* divagl_glGetProgramEnvParameterIivNV;
extern PFNGLGETPROGRAMENVPARAMETERIUIVNVPROC* divagl_glGetProgramEnvParameterIuivNV;
extern PFNGLGETPROGRAMINFOLOGPROC* divagl_glGetProgramInfoLog;
extern PFNGLGETPROGRAMIVPROC* divagl_glGetProgramiv;
extern PFNGLGETPROGRAMIVNVPROC* divagl_glGetProgramivNV;
extern PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC* divagl_glGetProgramLocalParameterdvARB;
extern PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC* divagl_glGetProgramLocalParameterfvARB;
extern PFNGLGETPROGRAMLOCALPARAMETERIIVNVPROC* divagl_glGetProgramLocalParameterIivNV;
extern PFNGLGETPROGRAMLOCALPARAMETERIUIVNVPROC* divagl_glGetProgramLocalParameterIuivNV;
extern PFNGLGETPROGRAMNAMEDPARAMETERDVNVPROC* divagl_glGetProgramNamedParameterdvNV;
extern PFNGLGETPROGRAMNAMEDPARAMETERFVNVPROC* divagl_glGetProgramNamedParameterfvNV;
extern PFNGLGETPROGRAMPARAMETERDVNVPROC* divagl_glGetProgramParameterdvNV;
extern PFNGLGETPROGRAMPARAMETERFVNVPROC* divagl_glGetProgramParameterfvNV;
extern PFNGLGETPROGRAMSTRINGARBPROC* divagl_glGetProgramStringARB;
extern PFNGLGETPROGRAMSTRINGNVPROC* divagl_glGetProgramStringNV;
extern PFNGLGETQUERYIVPROC* divagl_glGetQueryiv;
extern PFNGLGETQUERYIVARBPROC* divagl_glGetQueryivARB;
extern PFNGLGETQUERYOBJECTI64VEXTPROC* divagl_glGetQueryObjecti64vEXT;
extern PFNGLGETQUERYOBJECTIVPROC* divagl_glGetQueryObjectiv;
extern PFNGLGETQUERYOBJECTIVARBPROC* divagl_glGetQueryObjectivARB;
extern PFNGLGETQUERYOBJECTUI64VPROC* divagl_glGetQueryObjectui64v;
extern PFNGLGETQUERYOBJECTUI64VEXTPROC* divagl_glGetQueryObjectui64vEXT;
extern PFNGLGETQUERYOBJECTUIVPROC* divagl_glGetQueryObjectuiv;
extern PFNGLGETQUERYOBJECTUIVARBPROC* divagl_glGetQueryObjectuivARB;
extern PFNGLGETRENDERBUFFERPARAMETERIVPROC* divagl_glGetRenderbufferParameteriv;
extern PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC* divagl_glGetRenderbufferParameterivEXT;
extern PFNGLGETSEPARABLEFILTERPROC* divagl_glGetSeparableFilter;
extern PFNGLGETSHADERINFOLOGPROC* divagl_glGetShaderInfoLog;
extern PFNGLGETSHADERIVPROC* divagl_glGetShaderiv;
extern PFNGLGETSHADERSOURCEPROC* divagl_glGetShaderSource;
extern PFNGLGETSHADERSOURCEARBPROC* divagl_glGetShaderSourceARB;
extern PFNGLGETSTRINGIPROC* divagl_glGetStringi;
extern PFNGLGETTEXPARAMETERIIVPROC* divagl_glGetTexParameterIiv;
extern PFNGLGETTEXPARAMETERIIVEXTPROC* divagl_glGetTexParameterIivEXT;
extern PFNGLGETTEXPARAMETERIUIVPROC* divagl_glGetTexParameterIuiv;
extern PFNGLGETTEXPARAMETERIUIVEXTPROC* divagl_glGetTexParameterIuivEXT;
extern PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC* divagl_glGetTextureLevelParameterfvEXT;
extern PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC* divagl_glGetTextureLevelParameterivEXT;
extern PFNGLGETTEXTUREPARAMETERFVEXTPROC* divagl_glGetTextureParameterfvEXT;
extern PFNGLGETTEXTUREPARAMETERIIVEXTPROC* divagl_glGetTextureParameterIivEXT;
extern PFNGLGETTEXTUREPARAMETERIUIVEXTPROC* divagl_glGetTextureParameterIuivEXT;
extern PFNGLGETTEXTUREPARAMETERIVEXTPROC* divagl_glGetTextureParameterivEXT;
extern PFNGLGETTRACKMATRIXIVNVPROC* divagl_glGetTrackMatrixivNV;
extern PFNGLGETTRANSFORMFEEDBACKVARYINGPROC* divagl_glGetTransformFeedbackVarying;
extern PFNGLGETTRANSFORMFEEDBACKVARYINGNVPROC* divagl_glGetTransformFeedbackVaryingNV;
extern PFNGLGETUNIFORMBUFFERSIZEEXTPROC* divagl_glGetUniformBufferSizeEXT;
extern PFNGLGETUNIFORMFVPROC* divagl_glGetUniformfv;
extern PFNGLGETUNIFORMFVARBPROC* divagl_glGetUniformfvARB;
extern PFNGLGETUNIFORMIVPROC* divagl_glGetUniformiv;
extern PFNGLGETUNIFORMIVARBPROC* divagl_glGetUniformivARB;
extern PFNGLGETUNIFORMLOCATIONPROC* divagl_glGetUniformLocation;
extern PFNGLGETUNIFORMLOCATIONARBPROC* divagl_glGetUniformLocationARB;
extern PFNGLGETUNIFORMOFFSETEXTPROC* divagl_glGetUniformOffsetEXT;
extern PFNGLGETUNIFORMUIVPROC* divagl_glGetUniformuiv;
extern PFNGLGETUNIFORMUIVEXTPROC* divagl_glGetUniformuivEXT;
extern PFNGLGETVARYINGLOCATIONNVPROC* divagl_glGetVaryingLocationNV;
extern PFNGLGETVERTEXATTRIBDVPROC* divagl_glGetVertexAttribdv;
extern PFNGLGETVERTEXATTRIBDVARBPROC* divagl_glGetVertexAttribdvARB;
extern PFNGLGETVERTEXATTRIBDVNVPROC* divagl_glGetVertexAttribdvNV;
extern PFNGLGETVERTEXATTRIBFVPROC* divagl_glGetVertexAttribfv;
extern PFNGLGETVERTEXATTRIBFVARBPROC* divagl_glGetVertexAttribfvARB;
extern PFNGLGETVERTEXATTRIBFVNVPROC* divagl_glGetVertexAttribfvNV;
extern PFNGLGETVERTEXATTRIBIIVPROC* divagl_glGetVertexAttribIiv;
extern PFNGLGETVERTEXATTRIBIIVEXTPROC* divagl_glGetVertexAttribIivEXT;
extern PFNGLGETVERTEXATTRIBIUIVPROC* divagl_glGetVertexAttribIuiv;
extern PFNGLGETVERTEXATTRIBIUIVEXTPROC* divagl_glGetVertexAttribIuivEXT;
extern PFNGLGETVERTEXATTRIBIVPROC* divagl_glGetVertexAttribiv;
extern PFNGLGETVERTEXATTRIBIVARBPROC* divagl_glGetVertexAttribivARB;
extern PFNGLGETVERTEXATTRIBIVNVPROC* divagl_glGetVertexAttribivNV;
extern PFNGLGETVERTEXATTRIBPOINTERVPROC* divagl_glGetVertexAttribPointerv;
extern PFNGLGETVERTEXATTRIBPOINTERVARBPROC* divagl_glGetVertexAttribPointervARB;
extern PFNGLGETVERTEXATTRIBPOINTERVNVPROC* divagl_glGetVertexAttribPointervNV;
extern PFNGLGETVIDEOI64VNVPROC* divagl_glGetVideoi64vNV;
extern PFNGLGETVIDEOIVNVPROC* divagl_glGetVideoivNV;
extern PFNGLGETVIDEOUI64VNVPROC* divagl_glGetVideoui64vNV;
extern PFNGLGETVIDEOUIVNVPROC* divagl_glGetVideouivNV;
extern PFNGLHISTOGRAMPROC* divagl_glHistogram;
extern PFNGLINDEXPOINTEREXTPROC* divagl_glIndexPointerEXT;
extern PFNGLISBUFFERPROC* divagl_glIsBuffer;
extern PFNGLISENABLEDIPROC* divagl_glIsEnabledi;
extern PFNGLISENABLEDINDEXEDEXTPROC* divagl_glIsEnabledIndexedEXT;
extern PFNGLISFENCENVPROC* divagl_glIsFenceNV;
extern PFNGLISFRAMEBUFFERPROC* divagl_glIsFramebuffer;
extern PFNGLISFRAMEBUFFEREXTPROC* divagl_glIsFramebufferEXT;
extern PFNGLISOCCLUSIONQUERYNVPROC* divagl_glIsOcclusionQueryNV;
extern PFNGLISPROGRAMPROC* divagl_glIsProgram;
extern PFNGLISPROGRAMARBPROC* divagl_glIsProgramARB;
extern PFNGLISPROGRAMNVPROC* divagl_glIsProgramNV;
extern PFNGLISQUERYPROC* divagl_glIsQuery;
extern PFNGLISQUERYARBPROC* divagl_glIsQueryARB;
extern PFNGLISRENDERBUFFERPROC* divagl_glIsRenderbuffer;
extern PFNGLISRENDERBUFFEREXTPROC* divagl_glIsRenderbufferEXT;
extern PFNGLISSHADERPROC* divagl_glIsShader;
extern PFNGLISTEXTUREEXTPROC* divagl_glIsTextureEXT;
extern PFNGLISVERTEXARRAYPROC* divagl_glIsVertexArray;
extern PFNGLLINKPROGRAMPROC* divagl_glLinkProgram;
extern PFNGLLINKPROGRAMARBPROC* divagl_glLinkProgramARB;
extern PFNGLLOADPROGRAMNVPROC* divagl_glLoadProgramNV;
extern PFNGLLOADTRANSPOSEMATRIXDPROC* divagl_glLoadTransposeMatrixd;
extern PFNGLLOADTRANSPOSEMATRIXDARBPROC* divagl_glLoadTransposeMatrixdARB;
extern PFNGLLOADTRANSPOSEMATRIXFARBPROC* divagl_glLoadTransposeMatrixfARB;
extern PFNGLLOCKARRAYSEXTPROC* divagl_glLockArraysEXT;
extern PFNGLMAPBUFFERPROC* divagl_glMapBuffer;
extern PFNGLMAPBUFFERARBPROC* divagl_glMapBufferARB;
extern PFNGLMAPBUFFERRANGEPROC* divagl_glMapBufferRange;
extern PFNGLMATRIXFRUSTUMEXTPROC* divagl_glMatrixFrustumEXT;
extern PFNGLMATRIXLOADDEXTPROC* divagl_glMatrixLoaddEXT;
extern PFNGLMATRIXLOADFEXTPROC* divagl_glMatrixLoadfEXT;
extern PFNGLMATRIXLOADIDENTITYEXTPROC* divagl_glMatrixLoadIdentityEXT;
extern PFNGLMATRIXLOADTRANSPOSEDEXTPROC* divagl_glMatrixLoadTransposedEXT;
extern PFNGLMATRIXLOADTRANSPOSEFEXTPROC* divagl_glMatrixLoadTransposefEXT;
extern PFNGLMATRIXMULTDEXTPROC* divagl_glMatrixMultdEXT;
extern PFNGLMATRIXMULTFEXTPROC* divagl_glMatrixMultfEXT;
extern PFNGLMATRIXMULTTRANSPOSEDEXTPROC* divagl_glMatrixMultTransposedEXT;
extern PFNGLMATRIXMULTTRANSPOSEFEXTPROC* divagl_glMatrixMultTransposefEXT;
extern PFNGLMATRIXORTHOEXTPROC* divagl_glMatrixOrthoEXT;
extern PFNGLMATRIXPOPEXTPROC* divagl_glMatrixPopEXT;
extern PFNGLMATRIXPUSHEXTPROC* divagl_glMatrixPushEXT;
extern PFNGLMATRIXROTATEDEXTPROC* divagl_glMatrixRotatedEXT;
extern PFNGLMATRIXROTATEFEXTPROC* divagl_glMatrixRotatefEXT;
extern PFNGLMATRIXSCALEDEXTPROC* divagl_glMatrixScaledEXT;
extern PFNGLMATRIXSCALEFEXTPROC* divagl_glMatrixScalefEXT;
extern PFNGLMATRIXTRANSLATEDEXTPROC* divagl_glMatrixTranslatedEXT;
extern PFNGLMATRIXTRANSLATEFEXTPROC* divagl_glMatrixTranslatefEXT;
extern PFNGLMINMAXPROC* divagl_glMinmax;
extern PFNGLMULTIDRAWARRAYSPROC* divagl_glMultiDrawArrays;
extern PFNGLMULTIDRAWARRAYSEXTPROC* divagl_glMultiDrawArraysEXT;
extern PFNGLMULTIDRAWELEMENTSPROC* divagl_glMultiDrawElements;
extern PFNGLMULTIDRAWELEMENTSEXTPROC* divagl_glMultiDrawElementsEXT;
extern PFNGLMULTITEXBUFFEREXTPROC* divagl_glMultiTexBufferEXT;
extern PFNGLMULTITEXCOORD1DPROC* divagl_glMultiTexCoord1d;
extern PFNGLMULTITEXCOORD1DARBPROC* divagl_glMultiTexCoord1dARB;
extern PFNGLMULTITEXCOORD1DVPROC* divagl_glMultiTexCoord1dv;
extern PFNGLMULTITEXCOORD1DVARBPROC* divagl_glMultiTexCoord1dvARB;
extern PFNGLMULTITEXCOORD1FPROC* divagl_glMultiTexCoord1f;
extern PFNGLMULTITEXCOORD1FARBPROC* divagl_glMultiTexCoord1fARB;
extern PFNGLMULTITEXCOORD1FVPROC* divagl_glMultiTexCoord1fv;
extern PFNGLMULTITEXCOORD1FVARBPROC* divagl_glMultiTexCoord1fvARB;
extern PFNGLMULTITEXCOORD1HNVPROC* divagl_glMultiTexCoord1hNV;
extern PFNGLMULTITEXCOORD1HVNVPROC* divagl_glMultiTexCoord1hvNV;
extern PFNGLMULTITEXCOORD1IPROC* divagl_glMultiTexCoord1i;
extern PFNGLMULTITEXCOORD1IARBPROC* divagl_glMultiTexCoord1iARB;
extern PFNGLMULTITEXCOORD1IVPROC* divagl_glMultiTexCoord1iv;
extern PFNGLMULTITEXCOORD1IVARBPROC* divagl_glMultiTexCoord1ivARB;
extern PFNGLMULTITEXCOORD1SPROC* divagl_glMultiTexCoord1s;
extern PFNGLMULTITEXCOORD1SARBPROC* divagl_glMultiTexCoord1sARB;
extern PFNGLMULTITEXCOORD1SVPROC* divagl_glMultiTexCoord1sv;
extern PFNGLMULTITEXCOORD1SVARBPROC* divagl_glMultiTexCoord1svARB;
extern PFNGLMULTITEXCOORD2DPROC* divagl_glMultiTexCoord2d;
extern PFNGLMULTITEXCOORD2DARBPROC* divagl_glMultiTexCoord2dARB;
extern PFNGLMULTITEXCOORD2DVPROC* divagl_glMultiTexCoord2dv;
extern PFNGLMULTITEXCOORD2DVARBPROC* divagl_glMultiTexCoord2dvARB;
extern PFNGLMULTITEXCOORD2FARBPROC* divagl_glMultiTexCoord2fARB;
extern PFNGLMULTITEXCOORD2FVARBPROC* divagl_glMultiTexCoord2fvARB;
extern PFNGLMULTITEXCOORD2HNVPROC* divagl_glMultiTexCoord2hNV;
extern PFNGLMULTITEXCOORD2HVNVPROC* divagl_glMultiTexCoord2hvNV;
extern PFNGLMULTITEXCOORD2IPROC* divagl_glMultiTexCoord2i;
extern PFNGLMULTITEXCOORD2IARBPROC* divagl_glMultiTexCoord2iARB;
extern PFNGLMULTITEXCOORD2IVPROC* divagl_glMultiTexCoord2iv;
extern PFNGLMULTITEXCOORD2IVARBPROC* divagl_glMultiTexCoord2ivARB;
extern PFNGLMULTITEXCOORD2SPROC* divagl_glMultiTexCoord2s;
extern PFNGLMULTITEXCOORD2SARBPROC* divagl_glMultiTexCoord2sARB;
extern PFNGLMULTITEXCOORD2SVPROC* divagl_glMultiTexCoord2sv;
extern PFNGLMULTITEXCOORD2SVARBPROC* divagl_glMultiTexCoord2svARB;
extern PFNGLMULTITEXCOORD3DPROC* divagl_glMultiTexCoord3d;
extern PFNGLMULTITEXCOORD3DARBPROC* divagl_glMultiTexCoord3dARB;
extern PFNGLMULTITEXCOORD3DVPROC* divagl_glMultiTexCoord3dv;
extern PFNGLMULTITEXCOORD3DVARBPROC* divagl_glMultiTexCoord3dvARB;
extern PFNGLMULTITEXCOORD3FPROC* divagl_glMultiTexCoord3f;
extern PFNGLMULTITEXCOORD3FARBPROC* divagl_glMultiTexCoord3fARB;
extern PFNGLMULTITEXCOORD3FVPROC* divagl_glMultiTexCoord3fv;
extern PFNGLMULTITEXCOORD3FVARBPROC* divagl_glMultiTexCoord3fvARB;
extern PFNGLMULTITEXCOORD3HNVPROC* divagl_glMultiTexCoord3hNV;
extern PFNGLMULTITEXCOORD3HVNVPROC* divagl_glMultiTexCoord3hvNV;
extern PFNGLMULTITEXCOORD3IPROC* divagl_glMultiTexCoord3i;
extern PFNGLMULTITEXCOORD3IARBPROC* divagl_glMultiTexCoord3iARB;
extern PFNGLMULTITEXCOORD3IVPROC* divagl_glMultiTexCoord3iv;
extern PFNGLMULTITEXCOORD3IVARBPROC* divagl_glMultiTexCoord3ivARB;
extern PFNGLMULTITEXCOORD3SPROC* divagl_glMultiTexCoord3s;
extern PFNGLMULTITEXCOORD3SARBPROC* divagl_glMultiTexCoord3sARB;
extern PFNGLMULTITEXCOORD3SVPROC* divagl_glMultiTexCoord3sv;
extern PFNGLMULTITEXCOORD3SVARBPROC* divagl_glMultiTexCoord3svARB;
extern PFNGLMULTITEXCOORD4DPROC* divagl_glMultiTexCoord4d;
extern PFNGLMULTITEXCOORD4DARBPROC* divagl_glMultiTexCoord4dARB;
extern PFNGLMULTITEXCOORD4DVPROC* divagl_glMultiTexCoord4dv;
extern PFNGLMULTITEXCOORD4DVARBPROC* divagl_glMultiTexCoord4dvARB;
extern PFNGLMULTITEXCOORD4FPROC* divagl_glMultiTexCoord4f;
extern PFNGLMULTITEXCOORD4FARBPROC* divagl_glMultiTexCoord4fARB;
extern PFNGLMULTITEXCOORD4FVPROC* divagl_glMultiTexCoord4fv;
extern PFNGLMULTITEXCOORD4FVARBPROC* divagl_glMultiTexCoord4fvARB;
extern PFNGLMULTITEXCOORD4HNVPROC* divagl_glMultiTexCoord4hNV;
extern PFNGLMULTITEXCOORD4HVNVPROC* divagl_glMultiTexCoord4hvNV;
extern PFNGLMULTITEXCOORD4IPROC* divagl_glMultiTexCoord4i;
extern PFNGLMULTITEXCOORD4IARBPROC* divagl_glMultiTexCoord4iARB;
extern PFNGLMULTITEXCOORD4IVPROC* divagl_glMultiTexCoord4iv;
extern PFNGLMULTITEXCOORD4IVARBPROC* divagl_glMultiTexCoord4ivARB;
extern PFNGLMULTITEXCOORD4SPROC* divagl_glMultiTexCoord4s;
extern PFNGLMULTITEXCOORD4SARBPROC* divagl_glMultiTexCoord4sARB;
extern PFNGLMULTITEXCOORD4SVPROC* divagl_glMultiTexCoord4sv;
extern PFNGLMULTITEXCOORD4SVARBPROC* divagl_glMultiTexCoord4svARB;
extern PFNGLMULTITEXCOORDPOINTEREXTPROC* divagl_glMultiTexCoordPointerEXT;
extern PFNGLMULTITEXENVFEXTPROC* divagl_glMultiTexEnvfEXT;
extern PFNGLMULTITEXENVFVEXTPROC* divagl_glMultiTexEnvfvEXT;
extern PFNGLMULTITEXENVIEXTPROC* divagl_glMultiTexEnviEXT;
extern PFNGLMULTITEXENVIVEXTPROC* divagl_glMultiTexEnvivEXT;
extern PFNGLMULTITEXGENDEXTPROC* divagl_glMultiTexGendEXT;
extern PFNGLMULTITEXGENDVEXTPROC* divagl_glMultiTexGendvEXT;
extern PFNGLMULTITEXGENFEXTPROC* divagl_glMultiTexGenfEXT;
extern PFNGLMULTITEXGENFVEXTPROC* divagl_glMultiTexGenfvEXT;
extern PFNGLMULTITEXGENIEXTPROC* divagl_glMultiTexGeniEXT;
extern PFNGLMULTITEXGENIVEXTPROC* divagl_glMultiTexGenivEXT;
extern PFNGLMULTITEXIMAGE1DEXTPROC* divagl_glMultiTexImage1DEXT;
extern PFNGLMULTITEXIMAGE2DEXTPROC* divagl_glMultiTexImage2DEXT;
extern PFNGLMULTITEXIMAGE3DEXTPROC* divagl_glMultiTexImage3DEXT;
extern PFNGLMULTITEXPARAMETERFEXTPROC* divagl_glMultiTexParameterfEXT;
extern PFNGLMULTITEXPARAMETERFVEXTPROC* divagl_glMultiTexParameterfvEXT;
extern PFNGLMULTITEXPARAMETERIEXTPROC* divagl_glMultiTexParameteriEXT;
extern PFNGLMULTITEXPARAMETERIIVEXTPROC* divagl_glMultiTexParameterIivEXT;
extern PFNGLMULTITEXPARAMETERIUIVEXTPROC* divagl_glMultiTexParameterIuivEXT;
extern PFNGLMULTITEXPARAMETERIVEXTPROC* divagl_glMultiTexParameterivEXT;
extern PFNGLMULTITEXRENDERBUFFEREXTPROC* divagl_glMultiTexRenderbufferEXT;
extern PFNGLMULTITEXSUBIMAGE1DEXTPROC* divagl_glMultiTexSubImage1DEXT;
extern PFNGLMULTITEXSUBIMAGE2DEXTPROC* divagl_glMultiTexSubImage2DEXT;
extern PFNGLMULTITEXSUBIMAGE3DEXTPROC* divagl_glMultiTexSubImage3DEXT;
extern PFNGLMULTTRANSPOSEMATRIXDPROC* divagl_glMultTransposeMatrixd;
extern PFNGLMULTTRANSPOSEMATRIXDARBPROC* divagl_glMultTransposeMatrixdARB;
extern PFNGLMULTTRANSPOSEMATRIXFARBPROC* divagl_glMultTransposeMatrixfARB;
extern PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC* divagl_glNamedFramebufferRenderbufferEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC* divagl_glNamedFramebufferTexture1DEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC* divagl_glNamedFramebufferTexture2DEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC* divagl_glNamedFramebufferTexture3DEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC* divagl_glNamedFramebufferTextureEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC* divagl_glNamedFramebufferTextureFaceEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC* divagl_glNamedFramebufferTextureLayerEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC* divagl_glNamedProgramLocalParameter4dEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC* divagl_glNamedProgramLocalParameter4dvEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC* divagl_glNamedProgramLocalParameter4fEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC* divagl_glNamedProgramLocalParameter4fvEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC* divagl_glNamedProgramLocalParameterI4iEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC* divagl_glNamedProgramLocalParameterI4ivEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC* divagl_glNamedProgramLocalParameterI4uiEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC* divagl_glNamedProgramLocalParameterI4uivEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC* divagl_glNamedProgramLocalParameters4fvEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC* divagl_glNamedProgramLocalParametersI4ivEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC* divagl_glNamedProgramLocalParametersI4uivEXT;
extern PFNGLNAMEDPROGRAMSTRINGEXTPROC* divagl_glNamedProgramStringEXT;
extern PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC* divagl_glNamedRenderbufferStorageEXT;
extern PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC* divagl_glNamedRenderbufferStorageMultisampleCoverageEXT;
extern PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC* divagl_glNamedRenderbufferStorageMultisampleEXT;
extern PFNGLNORMAL3HNVPROC* divagl_glNormal3hNV;
extern PFNGLNORMAL3HVNVPROC* divagl_glNormal3hvNV;
extern PFNGLNORMALPOINTEREXTPROC* divagl_glNormalPointerEXT;
extern PFNGLPIXELDATARANGENVPROC* divagl_glPixelDataRangeNV;
extern PFNGLPOINTPARAMETERFARBPROC* divagl_glPointParameterfARB;
extern PFNGLPOINTPARAMETERFEXTPROC* divagl_glPointParameterfEXT;
extern PFNGLPOINTPARAMETERFVARBPROC* divagl_glPointParameterfvARB;
extern PFNGLPOINTPARAMETERFVEXTPROC* divagl_glPointParameterfvEXT;
extern PFNGLPOINTPARAMETERINVPROC* divagl_glPointParameteriNV;
extern PFNGLPOINTPARAMETERIVPROC* divagl_glPointParameteriv;
extern PFNGLPOINTPARAMETERIVNVPROC* divagl_glPointParameterivNV;
extern PFNGLPRESENTFRAMEDUALFILLNVPROC* divagl_glPresentFrameDualFillNV;
extern PFNGLPRESENTFRAMEKEYEDNVPROC* divagl_glPresentFrameKeyedNV;
extern PFNGLPRIMITIVERESTARTNVPROC* divagl_glPrimitiveRestartNV;
extern PFNGLPRIORITIZETEXTURESEXTPROC* divagl_glPrioritizeTexturesEXT;
extern PFNGLPROGRAMBUFFERPARAMETERSIIVNVPROC* divagl_glProgramBufferParametersIivNV;
extern PFNGLPROGRAMBUFFERPARAMETERSIUIVNVPROC* divagl_glProgramBufferParametersIuivNV;
extern PFNGLPROGRAMENVPARAMETER4DARBPROC* divagl_glProgramEnvParameter4dARB;
extern PFNGLPROGRAMENVPARAMETER4DVARBPROC* divagl_glProgramEnvParameter4dvARB;
extern PFNGLPROGRAMENVPARAMETERI4INVPROC* divagl_glProgramEnvParameterI4iNV;
extern PFNGLPROGRAMENVPARAMETERI4IVNVPROC* divagl_glProgramEnvParameterI4ivNV;
extern PFNGLPROGRAMENVPARAMETERI4UINVPROC* divagl_glProgramEnvParameterI4uiNV;
extern PFNGLPROGRAMENVPARAMETERI4UIVNVPROC* divagl_glProgramEnvParameterI4uivNV;
extern PFNGLPROGRAMENVPARAMETERSI4IVNVPROC* divagl_glProgramEnvParametersI4ivNV;
extern PFNGLPROGRAMENVPARAMETERSI4UIVNVPROC* divagl_glProgramEnvParametersI4uivNV;
extern PFNGLPROGRAMLOCALPARAMETER4DARBPROC* divagl_glProgramLocalParameter4dARB;
extern PFNGLPROGRAMLOCALPARAMETER4DVARBPROC* divagl_glProgramLocalParameter4dvARB;
extern PFNGLPROGRAMLOCALPARAMETERI4INVPROC* divagl_glProgramLocalParameterI4iNV;
extern PFNGLPROGRAMLOCALPARAMETERI4IVNVPROC* divagl_glProgramLocalParameterI4ivNV;
extern PFNGLPROGRAMLOCALPARAMETERI4UINVPROC* divagl_glProgramLocalParameterI4uiNV;
extern PFNGLPROGRAMLOCALPARAMETERI4UIVNVPROC* divagl_glProgramLocalParameterI4uivNV;
extern PFNGLPROGRAMLOCALPARAMETERSI4IVNVPROC* divagl_glProgramLocalParametersI4ivNV;
extern PFNGLPROGRAMLOCALPARAMETERSI4UIVNVPROC* divagl_glProgramLocalParametersI4uivNV;
extern PFNGLPROGRAMNAMEDPARAMETER4DNVPROC* divagl_glProgramNamedParameter4dNV;
extern PFNGLPROGRAMNAMEDPARAMETER4DVNVPROC* divagl_glProgramNamedParameter4dvNV;
extern PFNGLPROGRAMNAMEDPARAMETER4FNVPROC* divagl_glProgramNamedParameter4fNV;
extern PFNGLPROGRAMNAMEDPARAMETER4FVNVPROC* divagl_glProgramNamedParameter4fvNV;
extern PFNGLPROGRAMPARAMETER4DNVPROC* divagl_glProgramParameter4dNV;
extern PFNGLPROGRAMPARAMETER4DVNVPROC* divagl_glProgramParameter4dvNV;
extern PFNGLPROGRAMPARAMETER4FNVPROC* divagl_glProgramParameter4fNV;
extern PFNGLPROGRAMPARAMETER4FVNVPROC* divagl_glProgramParameter4fvNV;
extern PFNGLPROGRAMPARAMETERIARBPROC* divagl_glProgramParameteriARB;
extern PFNGLPROGRAMPARAMETERIEXTPROC* divagl_glProgramParameteriEXT;
extern PFNGLPROGRAMPARAMETERS4DVNVPROC* divagl_glProgramParameters4dvNV;
extern PFNGLPROGRAMPARAMETERS4FVNVPROC* divagl_glProgramParameters4fvNV;
extern PFNGLPROGRAMSTRINGARBPROC* divagl_glProgramStringARB;
extern PFNGLPROGRAMUNIFORM1FEXTPROC* divagl_glProgramUniform1fEXT;
extern PFNGLPROGRAMUNIFORM1FVEXTPROC* divagl_glProgramUniform1fvEXT;
extern PFNGLPROGRAMUNIFORM1IEXTPROC* divagl_glProgramUniform1iEXT;
extern PFNGLPROGRAMUNIFORM1IVEXTPROC* divagl_glProgramUniform1ivEXT;
extern PFNGLPROGRAMUNIFORM1UIEXTPROC* divagl_glProgramUniform1uiEXT;
extern PFNGLPROGRAMUNIFORM1UIVEXTPROC* divagl_glProgramUniform1uivEXT;
extern PFNGLPROGRAMUNIFORM2FEXTPROC* divagl_glProgramUniform2fEXT;
extern PFNGLPROGRAMUNIFORM2FVEXTPROC* divagl_glProgramUniform2fvEXT;
extern PFNGLPROGRAMUNIFORM2IEXTPROC* divagl_glProgramUniform2iEXT;
extern PFNGLPROGRAMUNIFORM2IVEXTPROC* divagl_glProgramUniform2ivEXT;
extern PFNGLPROGRAMUNIFORM2UIEXTPROC* divagl_glProgramUniform2uiEXT;
extern PFNGLPROGRAMUNIFORM2UIVEXTPROC* divagl_glProgramUniform2uivEXT;
extern PFNGLPROGRAMUNIFORM3FEXTPROC* divagl_glProgramUniform3fEXT;
extern PFNGLPROGRAMUNIFORM3FVEXTPROC* divagl_glProgramUniform3fvEXT;
extern PFNGLPROGRAMUNIFORM3IEXTPROC* divagl_glProgramUniform3iEXT;
extern PFNGLPROGRAMUNIFORM3IVEXTPROC* divagl_glProgramUniform3ivEXT;
extern PFNGLPROGRAMUNIFORM3UIEXTPROC* divagl_glProgramUniform3uiEXT;
extern PFNGLPROGRAMUNIFORM3UIVEXTPROC* divagl_glProgramUniform3uivEXT;
extern PFNGLPROGRAMUNIFORM4FEXTPROC* divagl_glProgramUniform4fEXT;
extern PFNGLPROGRAMUNIFORM4FVEXTPROC* divagl_glProgramUniform4fvEXT;
extern PFNGLPROGRAMUNIFORM4IEXTPROC* divagl_glProgramUniform4iEXT;
extern PFNGLPROGRAMUNIFORM4IVEXTPROC* divagl_glProgramUniform4ivEXT;
extern PFNGLPROGRAMUNIFORM4UIEXTPROC* divagl_glProgramUniform4uiEXT;
extern PFNGLPROGRAMUNIFORM4UIVEXTPROC* divagl_glProgramUniform4uivEXT;
extern PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC* divagl_glProgramUniformMatrix2fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC* divagl_glProgramUniformMatrix2x3fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC* divagl_glProgramUniformMatrix2x4fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC* divagl_glProgramUniformMatrix3fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC* divagl_glProgramUniformMatrix3x2fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC* divagl_glProgramUniformMatrix3x4fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC* divagl_glProgramUniformMatrix4fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC* divagl_glProgramUniformMatrix4x2fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC* divagl_glProgramUniformMatrix4x3fvEXT;
extern PFNGLPROGRAMVERTEXLIMITNVPROC* divagl_glProgramVertexLimitNV;
extern PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC* divagl_glPushClientAttribDefaultEXT;
extern PFNGLQUERYCOUNTERPROC* divagl_glQueryCounter;
extern PFNGLRENDERBUFFERSTORAGEPROC* divagl_glRenderbufferStorage;
extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC* divagl_glRenderbufferStorageMultisample;
extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC* divagl_glRenderbufferStorageMultisampleEXT;
extern PFNGLREQUESTRESIDENTPROGRAMSNVPROC* divagl_glRequestResidentProgramsNV;
extern PFNGLRESETHISTOGRAMPROC* divagl_glResetHistogram;
extern PFNGLRESETMINMAXPROC* divagl_glResetMinmax;
extern PFNGLSAMPLECOVERAGEPROC* divagl_glSampleCoverage;
extern PFNGLSAMPLECOVERAGEARBPROC* divagl_glSampleCoverageARB;
extern PFNGLSAMPLEMASKINDEXEDNVPROC* divagl_glSampleMaskIndexedNV;
extern PFNGLSAMPLERPARAMETERFPROC* divagl_glSamplerParameterf;
extern PFNGLSAMPLERPARAMETERFVPROC* divagl_glSamplerParameterfv;
extern PFNGLSAMPLERPARAMETERIPROC* divagl_glSamplerParameteri;
extern PFNGLSECONDARYCOLOR3BPROC* divagl_glSecondaryColor3b;
extern PFNGLSECONDARYCOLOR3BEXTPROC* divagl_glSecondaryColor3bEXT;
extern PFNGLSECONDARYCOLOR3BVPROC* divagl_glSecondaryColor3bv;
extern PFNGLSECONDARYCOLOR3BVEXTPROC* divagl_glSecondaryColor3bvEXT;
extern PFNGLSECONDARYCOLOR3DPROC* divagl_glSecondaryColor3d;
extern PFNGLSECONDARYCOLOR3DEXTPROC* divagl_glSecondaryColor3dEXT;
extern PFNGLSECONDARYCOLOR3DVPROC* divagl_glSecondaryColor3dv;
extern PFNGLSECONDARYCOLOR3DVEXTPROC* divagl_glSecondaryColor3dvEXT;
extern PFNGLSECONDARYCOLOR3FPROC* divagl_glSecondaryColor3f;
extern PFNGLSECONDARYCOLOR3FEXTPROC* divagl_glSecondaryColor3fEXT;
extern PFNGLSECONDARYCOLOR3FVPROC* divagl_glSecondaryColor3fv;
extern PFNGLSECONDARYCOLOR3FVEXTPROC* divagl_glSecondaryColor3fvEXT;
extern PFNGLSECONDARYCOLOR3HNVPROC* divagl_glSecondaryColor3hNV;
extern PFNGLSECONDARYCOLOR3HVNVPROC* divagl_glSecondaryColor3hvNV;
extern PFNGLSECONDARYCOLOR3IPROC* divagl_glSecondaryColor3i;
extern PFNGLSECONDARYCOLOR3IEXTPROC* divagl_glSecondaryColor3iEXT;
extern PFNGLSECONDARYCOLOR3IVPROC* divagl_glSecondaryColor3iv;
extern PFNGLSECONDARYCOLOR3IVEXTPROC* divagl_glSecondaryColor3ivEXT;
extern PFNGLSECONDARYCOLOR3SPROC* divagl_glSecondaryColor3s;
extern PFNGLSECONDARYCOLOR3SEXTPROC* divagl_glSecondaryColor3sEXT;
extern PFNGLSECONDARYCOLOR3SVPROC* divagl_glSecondaryColor3sv;
extern PFNGLSECONDARYCOLOR3SVEXTPROC* divagl_glSecondaryColor3svEXT;
extern PFNGLSECONDARYCOLOR3UBPROC* divagl_glSecondaryColor3ub;
extern PFNGLSECONDARYCOLOR3UBEXTPROC* divagl_glSecondaryColor3ubEXT;
extern PFNGLSECONDARYCOLOR3UBVPROC* divagl_glSecondaryColor3ubv;
extern PFNGLSECONDARYCOLOR3UBVEXTPROC* divagl_glSecondaryColor3ubvEXT;
extern PFNGLSECONDARYCOLOR3UIPROC* divagl_glSecondaryColor3ui;
extern PFNGLSECONDARYCOLOR3UIEXTPROC* divagl_glSecondaryColor3uiEXT;
extern PFNGLSECONDARYCOLOR3UIVPROC* divagl_glSecondaryColor3uiv;
extern PFNGLSECONDARYCOLOR3UIVEXTPROC* divagl_glSecondaryColor3uivEXT;
extern PFNGLSECONDARYCOLOR3USPROC* divagl_glSecondaryColor3us;
extern PFNGLSECONDARYCOLOR3USEXTPROC* divagl_glSecondaryColor3usEXT;
extern PFNGLSECONDARYCOLOR3USVPROC* divagl_glSecondaryColor3usv;
extern PFNGLSECONDARYCOLOR3USVEXTPROC* divagl_glSecondaryColor3usvEXT;
extern PFNGLSECONDARYCOLORPOINTERPROC* divagl_glSecondaryColorPointer;
extern PFNGLSECONDARYCOLORPOINTEREXTPROC* divagl_glSecondaryColorPointerEXT;
extern PFNGLSEPARABLEFILTER2DPROC* divagl_glSeparableFilter2D;
extern PFNGLSETFENCENVPROC* divagl_glSetFenceNV;
extern PFNGLSHADERSOURCEPROC* divagl_glShaderSource;
extern PFNGLSHADERSOURCEARBPROC* divagl_glShaderSourceARB;
extern PFNGLSTENCILFUNCSEPARATEPROC* divagl_glStencilFuncSeparate;
extern PFNGLSTENCILMASKSEPARATEPROC* divagl_glStencilMaskSeparate;
extern PFNGLSTENCILOPSEPARATEPROC* divagl_glStencilOpSeparate;
extern PFNGLTESTFENCENVPROC* divagl_glTestFenceNV;
extern PFNGLTEXBUFFERARBPROC* divagl_glTexBufferARB;
extern PFNGLTEXBUFFEREXTPROC* divagl_glTexBufferEXT;
extern PFNGLTEXCOORD1HNVPROC* divagl_glTexCoord1hNV;
extern PFNGLTEXCOORD1HVNVPROC* divagl_glTexCoord1hvNV;
extern PFNGLTEXCOORD2HNVPROC* divagl_glTexCoord2hNV;
extern PFNGLTEXCOORD2HVNVPROC* divagl_glTexCoord2hvNV;
extern PFNGLTEXCOORD3HNVPROC* divagl_glTexCoord3hNV;
extern PFNGLTEXCOORD3HVNVPROC* divagl_glTexCoord3hvNV;
extern PFNGLTEXCOORD4HNVPROC* divagl_glTexCoord4hNV;
extern PFNGLTEXCOORD4HVNVPROC* divagl_glTexCoord4hvNV;
extern PFNGLTEXCOORDPOINTEREXTPROC* divagl_glTexCoordPointerEXT;
extern PFNGLTEXIMAGE3DPROC* divagl_glTexImage3D;
extern PFNGLTEXIMAGE3DEXTPROC* divagl_glTexImage3DEXT;
extern PFNGLTEXPARAMETERIIVPROC* divagl_glTexParameterIiv;
extern PFNGLTEXPARAMETERIIVEXTPROC* divagl_glTexParameterIivEXT;
extern PFNGLTEXPARAMETERIUIVPROC* divagl_glTexParameterIuiv;
extern PFNGLTEXPARAMETERIUIVEXTPROC* divagl_glTexParameterIuivEXT;
extern PFNGLTEXRENDERBUFFERNVPROC* divagl_glTexRenderbufferNV;
extern PFNGLTEXSTORAGE2DPROC* divagl_glTexStorage2D;
extern PFNGLTEXSUBIMAGE3DPROC* divagl_glTexSubImage3D;
extern PFNGLTEXSUBIMAGE3DEXTPROC* divagl_glTexSubImage3DEXT;
extern PFNGLTEXTUREBARRIERNVPROC* divagl_glTextureBarrierNV;
extern PFNGLTEXTUREBUFFEREXTPROC* divagl_glTextureBufferEXT;
extern PFNGLTEXTUREIMAGE1DEXTPROC* divagl_glTextureImage1DEXT;
extern PFNGLTEXTUREIMAGE2DEXTPROC* divagl_glTextureImage2DEXT;
extern PFNGLTEXTUREIMAGE3DEXTPROC* divagl_glTextureImage3DEXT;
extern PFNGLTEXTUREPARAMETERFEXTPROC* divagl_glTextureParameterfEXT;
extern PFNGLTEXTUREPARAMETERFVEXTPROC* divagl_glTextureParameterfvEXT;
extern PFNGLTEXTUREPARAMETERIEXTPROC* divagl_glTextureParameteriEXT;
extern PFNGLTEXTUREPARAMETERIIVEXTPROC* divagl_glTextureParameterIivEXT;
extern PFNGLTEXTUREPARAMETERIUIVEXTPROC* divagl_glTextureParameterIuivEXT;
extern PFNGLTEXTUREPARAMETERIVEXTPROC* divagl_glTextureParameterivEXT;
extern PFNGLTEXTURERENDERBUFFEREXTPROC* divagl_glTextureRenderbufferEXT;
extern PFNGLTEXTURESTORAGE2DEXTPROC* divagl_glTextureStorage2DEXT;
extern PFNGLTEXTURESUBIMAGE1DEXTPROC* divagl_glTextureSubImage1DEXT;
extern PFNGLTEXTURESUBIMAGE2DEXTPROC* divagl_glTextureSubImage2DEXT;
extern PFNGLTEXTURESUBIMAGE3DEXTPROC* divagl_glTextureSubImage3DEXT;
extern PFNGLTRACKMATRIXNVPROC* divagl_glTrackMatrixNV;
extern PFNGLTRANSFORMFEEDBACKATTRIBSNVPROC* divagl_glTransformFeedbackAttribsNV;
extern PFNGLTRANSFORMFEEDBACKVARYINGSPROC* divagl_glTransformFeedbackVaryings;
extern PFNGLTRANSFORMFEEDBACKVARYINGSNVPROC* divagl_glTransformFeedbackVaryingsNV;
extern PFNGLUNIFORM1FPROC* divagl_glUniform1f;
extern PFNGLUNIFORM1FARBPROC* divagl_glUniform1fARB;
extern PFNGLUNIFORM1FVPROC* divagl_glUniform1fv;
extern PFNGLUNIFORM1FVARBPROC* divagl_glUniform1fvARB;
extern PFNGLUNIFORM1IPROC* divagl_glUniform1i;
extern PFNGLUNIFORM1IARBPROC* divagl_glUniform1iARB;
extern PFNGLUNIFORM1IVPROC* divagl_glUniform1iv;
extern PFNGLUNIFORM1IVARBPROC* divagl_glUniform1ivARB;
extern PFNGLUNIFORM1UIPROC* divagl_glUniform1ui;
extern PFNGLUNIFORM1UIEXTPROC* divagl_glUniform1uiEXT;
extern PFNGLUNIFORM1UIVPROC* divagl_glUniform1uiv;
extern PFNGLUNIFORM1UIVEXTPROC* divagl_glUniform1uivEXT;
extern PFNGLUNIFORM2FPROC* divagl_glUniform2f;
extern PFNGLUNIFORM2FARBPROC* divagl_glUniform2fARB;
extern PFNGLUNIFORM2FVPROC* divagl_glUniform2fv;
extern PFNGLUNIFORM2FVARBPROC* divagl_glUniform2fvARB;
extern PFNGLUNIFORM2IPROC* divagl_glUniform2i;
extern PFNGLUNIFORM2IARBPROC* divagl_glUniform2iARB;
extern PFNGLUNIFORM2IVPROC* divagl_glUniform2iv;
extern PFNGLUNIFORM2IVARBPROC* divagl_glUniform2ivARB;
extern PFNGLUNIFORM2UIPROC* divagl_glUniform2ui;
extern PFNGLUNIFORM2UIEXTPROC* divagl_glUniform2uiEXT;
extern PFNGLUNIFORM2UIVPROC* divagl_glUniform2uiv;
extern PFNGLUNIFORM2UIVEXTPROC* divagl_glUniform2uivEXT;
extern PFNGLUNIFORM3FPROC* divagl_glUniform3f;
extern PFNGLUNIFORM3FARBPROC* divagl_glUniform3fARB;
extern PFNGLUNIFORM3FVPROC* divagl_glUniform3fv;
extern PFNGLUNIFORM3FVARBPROC* divagl_glUniform3fvARB;
extern PFNGLUNIFORM3IPROC* divagl_glUniform3i;
extern PFNGLUNIFORM3IARBPROC* divagl_glUniform3iARB;
extern PFNGLUNIFORM3IVPROC* divagl_glUniform3iv;
extern PFNGLUNIFORM3IVARBPROC* divagl_glUniform3ivARB;
extern PFNGLUNIFORM3UIPROC* divagl_glUniform3ui;
extern PFNGLUNIFORM3UIEXTPROC* divagl_glUniform3uiEXT;
extern PFNGLUNIFORM3UIVPROC* divagl_glUniform3uiv;
extern PFNGLUNIFORM3UIVEXTPROC* divagl_glUniform3uivEXT;
extern PFNGLUNIFORM4FPROC* divagl_glUniform4f;
extern PFNGLUNIFORM4FARBPROC* divagl_glUniform4fARB;
extern PFNGLUNIFORM4FVPROC* divagl_glUniform4fv;
extern PFNGLUNIFORM4FVARBPROC* divagl_glUniform4fvARB;
extern PFNGLUNIFORM4IPROC* divagl_glUniform4i;
extern PFNGLUNIFORM4IARBPROC* divagl_glUniform4iARB;
extern PFNGLUNIFORM4IVPROC* divagl_glUniform4iv;
extern PFNGLUNIFORM4IVARBPROC* divagl_glUniform4ivARB;
extern PFNGLUNIFORM4UIPROC* divagl_glUniform4ui;
extern PFNGLUNIFORM4UIEXTPROC* divagl_glUniform4uiEXT;
extern PFNGLUNIFORM4UIVPROC* divagl_glUniform4uiv;
extern PFNGLUNIFORM4UIVEXTPROC* divagl_glUniform4uivEXT;
extern PFNGLUNIFORMBUFFEREXTPROC* divagl_glUniformBufferEXT;
extern PFNGLUNIFORMMATRIX2FVPROC* divagl_glUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX2FVARBPROC* divagl_glUniformMatrix2fvARB;
extern PFNGLUNIFORMMATRIX2X3FVPROC* divagl_glUniformMatrix2x3fv;
extern PFNGLUNIFORMMATRIX2X4FVPROC* divagl_glUniformMatrix2x4fv;
extern PFNGLUNIFORMMATRIX3FVPROC* divagl_glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX3FVARBPROC* divagl_glUniformMatrix3fvARB;
extern PFNGLUNIFORMMATRIX3X2FVPROC* divagl_glUniformMatrix3x2fv;
extern PFNGLUNIFORMMATRIX3X4FVPROC* divagl_glUniformMatrix3x4fv;
extern PFNGLUNIFORMMATRIX4FVPROC* divagl_glUniformMatrix4fv;
extern PFNGLUNIFORMMATRIX4FVARBPROC* divagl_glUniformMatrix4fvARB;
extern PFNGLUNIFORMMATRIX4X2FVPROC* divagl_glUniformMatrix4x2fv;
extern PFNGLUNIFORMMATRIX4X3FVPROC* divagl_glUniformMatrix4x3fv;
extern PFNGLUNLOCKARRAYSEXTPROC* divagl_glUnlockArraysEXT;
extern PFNGLUNMAPBUFFERPROC* divagl_glUnmapBuffer;
extern PFNGLUNMAPBUFFERARBPROC* divagl_glUnmapBufferARB;
extern PFNGLUSEPROGRAMPROC* divagl_glUseProgram;
extern PFNGLUSEPROGRAMOBJECTARBPROC* divagl_glUseProgramObjectARB;
extern PFNGLVALIDATEPROGRAMPROC* divagl_glValidateProgram;
extern PFNGLVALIDATEPROGRAMARBPROC* divagl_glValidateProgramARB;
extern PFNGLVERTEX2HNVPROC* divagl_glVertex2hNV;
extern PFNGLVERTEX2HVNVPROC* divagl_glVertex2hvNV;
extern PFNGLVERTEX3HNVPROC* divagl_glVertex3hNV;
extern PFNGLVERTEX3HVNVPROC* divagl_glVertex3hvNV;
extern PFNGLVERTEX4HNVPROC* divagl_glVertex4hNV;
extern PFNGLVERTEX4HVNVPROC* divagl_glVertex4hvNV;
extern PFNGLVERTEXARRAYRANGENVPROC* divagl_glVertexArrayRangeNV;
extern PFNGLVERTEXATTRIB1DPROC* divagl_glVertexAttrib1d;
extern PFNGLVERTEXATTRIB1DARBPROC* divagl_glVertexAttrib1dARB;
extern PFNGLVERTEXATTRIB1DNVPROC* divagl_glVertexAttrib1dNV;
extern PFNGLVERTEXATTRIB1DVPROC* divagl_glVertexAttrib1dv;
extern PFNGLVERTEXATTRIB1DVARBPROC* divagl_glVertexAttrib1dvARB;
extern PFNGLVERTEXATTRIB1DVNVPROC* divagl_glVertexAttrib1dvNV;
extern PFNGLVERTEXATTRIB1FPROC* divagl_glVertexAttrib1f;
extern PFNGLVERTEXATTRIB1FARBPROC* divagl_glVertexAttrib1fARB;
extern PFNGLVERTEXATTRIB1FNVPROC* divagl_glVertexAttrib1fNV;
extern PFNGLVERTEXATTRIB1FVPROC* divagl_glVertexAttrib1fv;
extern PFNGLVERTEXATTRIB1FVARBPROC* divagl_glVertexAttrib1fvARB;
extern PFNGLVERTEXATTRIB1FVNVPROC* divagl_glVertexAttrib1fvNV;
extern PFNGLVERTEXATTRIB1HNVPROC* divagl_glVertexAttrib1hNV;
extern PFNGLVERTEXATTRIB1HVNVPROC* divagl_glVertexAttrib1hvNV;
extern PFNGLVERTEXATTRIB1SPROC* divagl_glVertexAttrib1s;
extern PFNGLVERTEXATTRIB1SARBPROC* divagl_glVertexAttrib1sARB;
extern PFNGLVERTEXATTRIB1SNVPROC* divagl_glVertexAttrib1sNV;
extern PFNGLVERTEXATTRIB1SVPROC* divagl_glVertexAttrib1sv;
extern PFNGLVERTEXATTRIB1SVARBPROC* divagl_glVertexAttrib1svARB;
extern PFNGLVERTEXATTRIB1SVNVPROC* divagl_glVertexAttrib1svNV;
extern PFNGLVERTEXATTRIB2DPROC* divagl_glVertexAttrib2d;
extern PFNGLVERTEXATTRIB2DARBPROC* divagl_glVertexAttrib2dARB;
extern PFNGLVERTEXATTRIB2DNVPROC* divagl_glVertexAttrib2dNV;
extern PFNGLVERTEXATTRIB2DVPROC* divagl_glVertexAttrib2dv;
extern PFNGLVERTEXATTRIB2DVARBPROC* divagl_glVertexAttrib2dvARB;
extern PFNGLVERTEXATTRIB2DVNVPROC* divagl_glVertexAttrib2dvNV;
extern PFNGLVERTEXATTRIB2FPROC* divagl_glVertexAttrib2f;
extern PFNGLVERTEXATTRIB2FARBPROC* divagl_glVertexAttrib2fARB;
extern PFNGLVERTEXATTRIB2FNVPROC* divagl_glVertexAttrib2fNV;
extern PFNGLVERTEXATTRIB2FVPROC* divagl_glVertexAttrib2fv;
extern PFNGLVERTEXATTRIB2FVARBPROC* divagl_glVertexAttrib2fvARB;
extern PFNGLVERTEXATTRIB2FVNVPROC* divagl_glVertexAttrib2fvNV;
extern PFNGLVERTEXATTRIB2HNVPROC* divagl_glVertexAttrib2hNV;
extern PFNGLVERTEXATTRIB2HVNVPROC* divagl_glVertexAttrib2hvNV;
extern PFNGLVERTEXATTRIB2SPROC* divagl_glVertexAttrib2s;
extern PFNGLVERTEXATTRIB2SARBPROC* divagl_glVertexAttrib2sARB;
extern PFNGLVERTEXATTRIB2SNVPROC* divagl_glVertexAttrib2sNV;
extern PFNGLVERTEXATTRIB2SVPROC* divagl_glVertexAttrib2sv;
extern PFNGLVERTEXATTRIB2SVARBPROC* divagl_glVertexAttrib2svARB;
extern PFNGLVERTEXATTRIB2SVNVPROC* divagl_glVertexAttrib2svNV;
extern PFNGLVERTEXATTRIB3DPROC* divagl_glVertexAttrib3d;
extern PFNGLVERTEXATTRIB3DARBPROC* divagl_glVertexAttrib3dARB;
extern PFNGLVERTEXATTRIB3DNVPROC* divagl_glVertexAttrib3dNV;
extern PFNGLVERTEXATTRIB3DVPROC* divagl_glVertexAttrib3dv;
extern PFNGLVERTEXATTRIB3DVARBPROC* divagl_glVertexAttrib3dvARB;
extern PFNGLVERTEXATTRIB3DVNVPROC* divagl_glVertexAttrib3dvNV;
extern PFNGLVERTEXATTRIB3FPROC* divagl_glVertexAttrib3f;
extern PFNGLVERTEXATTRIB3FARBPROC* divagl_glVertexAttrib3fARB;
extern PFNGLVERTEXATTRIB3FNVPROC* divagl_glVertexAttrib3fNV;
extern PFNGLVERTEXATTRIB3FVPROC* divagl_glVertexAttrib3fv;
extern PFNGLVERTEXATTRIB3FVARBPROC* divagl_glVertexAttrib3fvARB;
extern PFNGLVERTEXATTRIB3FVNVPROC* divagl_glVertexAttrib3fvNV;
extern PFNGLVERTEXATTRIB3HNVPROC* divagl_glVertexAttrib3hNV;
extern PFNGLVERTEXATTRIB3HVNVPROC* divagl_glVertexAttrib3hvNV;
extern PFNGLVERTEXATTRIB3SPROC* divagl_glVertexAttrib3s;
extern PFNGLVERTEXATTRIB3SARBPROC* divagl_glVertexAttrib3sARB;
extern PFNGLVERTEXATTRIB3SNVPROC* divagl_glVertexAttrib3sNV;
extern PFNGLVERTEXATTRIB3SVPROC* divagl_glVertexAttrib3sv;
extern PFNGLVERTEXATTRIB3SVARBPROC* divagl_glVertexAttrib3svARB;
extern PFNGLVERTEXATTRIB3SVNVPROC* divagl_glVertexAttrib3svNV;
extern PFNGLVERTEXATTRIB4BVPROC* divagl_glVertexAttrib4bv;
extern PFNGLVERTEXATTRIB4BVARBPROC* divagl_glVertexAttrib4bvARB;
extern PFNGLVERTEXATTRIB4DPROC* divagl_glVertexAttrib4d;
extern PFNGLVERTEXATTRIB4DARBPROC* divagl_glVertexAttrib4dARB;
extern PFNGLVERTEXATTRIB4DNVPROC* divagl_glVertexAttrib4dNV;
extern PFNGLVERTEXATTRIB4DVPROC* divagl_glVertexAttrib4dv;
extern PFNGLVERTEXATTRIB4DVARBPROC* divagl_glVertexAttrib4dvARB;
extern PFNGLVERTEXATTRIB4DVNVPROC* divagl_glVertexAttrib4dvNV;
extern PFNGLVERTEXATTRIB4FPROC* divagl_glVertexAttrib4f;
extern PFNGLVERTEXATTRIB4FARBPROC* divagl_glVertexAttrib4fARB;
extern PFNGLVERTEXATTRIB4FNVPROC* divagl_glVertexAttrib4fNV;
extern PFNGLVERTEXATTRIB4FVPROC* divagl_glVertexAttrib4fv;
extern PFNGLVERTEXATTRIB4FVARBPROC* divagl_glVertexAttrib4fvARB;
extern PFNGLVERTEXATTRIB4FVNVPROC* divagl_glVertexAttrib4fvNV;
extern PFNGLVERTEXATTRIB4HNVPROC* divagl_glVertexAttrib4hNV;
extern PFNGLVERTEXATTRIB4HVNVPROC* divagl_glVertexAttrib4hvNV;
extern PFNGLVERTEXATTRIB4IVPROC* divagl_glVertexAttrib4iv;
extern PFNGLVERTEXATTRIB4IVARBPROC* divagl_glVertexAttrib4ivARB;
extern PFNGLVERTEXATTRIB4NBVPROC* divagl_glVertexAttrib4Nbv;
extern PFNGLVERTEXATTRIB4NBVARBPROC* divagl_glVertexAttrib4NbvARB;
extern PFNGLVERTEXATTRIB4NIVPROC* divagl_glVertexAttrib4Niv;
extern PFNGLVERTEXATTRIB4NIVARBPROC* divagl_glVertexAttrib4NivARB;
extern PFNGLVERTEXATTRIB4NSVPROC* divagl_glVertexAttrib4Nsv;
extern PFNGLVERTEXATTRIB4NSVARBPROC* divagl_glVertexAttrib4NsvARB;
extern PFNGLVERTEXATTRIB4NUBPROC* divagl_glVertexAttrib4Nub;
extern PFNGLVERTEXATTRIB4NUBARBPROC* divagl_glVertexAttrib4NubARB;
extern PFNGLVERTEXATTRIB4NUBVPROC* divagl_glVertexAttrib4Nubv;
extern PFNGLVERTEXATTRIB4NUBVARBPROC* divagl_glVertexAttrib4NubvARB;
extern PFNGLVERTEXATTRIB4NUIVPROC* divagl_glVertexAttrib4Nuiv;
extern PFNGLVERTEXATTRIB4NUIVARBPROC* divagl_glVertexAttrib4NuivARB;
extern PFNGLVERTEXATTRIB4NUSVPROC* divagl_glVertexAttrib4Nusv;
extern PFNGLVERTEXATTRIB4NUSVARBPROC* divagl_glVertexAttrib4NusvARB;
extern PFNGLVERTEXATTRIB4SPROC* divagl_glVertexAttrib4s;
extern PFNGLVERTEXATTRIB4SARBPROC* divagl_glVertexAttrib4sARB;
extern PFNGLVERTEXATTRIB4SNVPROC* divagl_glVertexAttrib4sNV;
extern PFNGLVERTEXATTRIB4SVPROC* divagl_glVertexAttrib4sv;
extern PFNGLVERTEXATTRIB4SVARBPROC* divagl_glVertexAttrib4svARB;
extern PFNGLVERTEXATTRIB4SVNVPROC* divagl_glVertexAttrib4svNV;
extern PFNGLVERTEXATTRIB4UBNVPROC* divagl_glVertexAttrib4ubNV;
extern PFNGLVERTEXATTRIB4UBVPROC* divagl_glVertexAttrib4ubv;
extern PFNGLVERTEXATTRIB4UBVARBPROC* divagl_glVertexAttrib4ubvARB;
extern PFNGLVERTEXATTRIB4UBVNVPROC* divagl_glVertexAttrib4ubvNV;
extern PFNGLVERTEXATTRIB4UIVPROC* divagl_glVertexAttrib4uiv;
extern PFNGLVERTEXATTRIB4UIVARBPROC* divagl_glVertexAttrib4uivARB;
extern PFNGLVERTEXATTRIB4USVPROC* divagl_glVertexAttrib4usv;
extern PFNGLVERTEXATTRIB4USVARBPROC* divagl_glVertexAttrib4usvARB;
extern PFNGLVERTEXATTRIBI1IPROC* divagl_glVertexAttribI1i;
extern PFNGLVERTEXATTRIBI1IEXTPROC* divagl_glVertexAttribI1iEXT;
extern PFNGLVERTEXATTRIBI1IVPROC* divagl_glVertexAttribI1iv;
extern PFNGLVERTEXATTRIBI1IVEXTPROC* divagl_glVertexAttribI1ivEXT;
extern PFNGLVERTEXATTRIBI1UIPROC* divagl_glVertexAttribI1ui;
extern PFNGLVERTEXATTRIBI1UIEXTPROC* divagl_glVertexAttribI1uiEXT;
extern PFNGLVERTEXATTRIBI1UIVPROC* divagl_glVertexAttribI1uiv;
extern PFNGLVERTEXATTRIBI1UIVEXTPROC* divagl_glVertexAttribI1uivEXT;
extern PFNGLVERTEXATTRIBI2IPROC* divagl_glVertexAttribI2i;
extern PFNGLVERTEXATTRIBI2IEXTPROC* divagl_glVertexAttribI2iEXT;
extern PFNGLVERTEXATTRIBI2IVPROC* divagl_glVertexAttribI2iv;
extern PFNGLVERTEXATTRIBI2IVEXTPROC* divagl_glVertexAttribI2ivEXT;
extern PFNGLVERTEXATTRIBI2UIPROC* divagl_glVertexAttribI2ui;
extern PFNGLVERTEXATTRIBI2UIEXTPROC* divagl_glVertexAttribI2uiEXT;
extern PFNGLVERTEXATTRIBI2UIVPROC* divagl_glVertexAttribI2uiv;
extern PFNGLVERTEXATTRIBI2UIVEXTPROC* divagl_glVertexAttribI2uivEXT;
extern PFNGLVERTEXATTRIBI3IPROC* divagl_glVertexAttribI3i;
extern PFNGLVERTEXATTRIBI3IEXTPROC* divagl_glVertexAttribI3iEXT;
extern PFNGLVERTEXATTRIBI3IVPROC* divagl_glVertexAttribI3iv;
extern PFNGLVERTEXATTRIBI3IVEXTPROC* divagl_glVertexAttribI3ivEXT;
extern PFNGLVERTEXATTRIBI3UIPROC* divagl_glVertexAttribI3ui;
extern PFNGLVERTEXATTRIBI3UIEXTPROC* divagl_glVertexAttribI3uiEXT;
extern PFNGLVERTEXATTRIBI3UIVPROC* divagl_glVertexAttribI3uiv;
extern PFNGLVERTEXATTRIBI3UIVEXTPROC* divagl_glVertexAttribI3uivEXT;
extern PFNGLVERTEXATTRIBI4BVPROC* divagl_glVertexAttribI4bv;
extern PFNGLVERTEXATTRIBI4BVEXTPROC* divagl_glVertexAttribI4bvEXT;
extern PFNGLVERTEXATTRIBI4IPROC* divagl_glVertexAttribI4i;
extern PFNGLVERTEXATTRIBI4IEXTPROC* divagl_glVertexAttribI4iEXT;
extern PFNGLVERTEXATTRIBI4IVPROC* divagl_glVertexAttribI4iv;
extern PFNGLVERTEXATTRIBI4IVEXTPROC* divagl_glVertexAttribI4ivEXT;
extern PFNGLVERTEXATTRIBI4SVPROC* divagl_glVertexAttribI4sv;
extern PFNGLVERTEXATTRIBI4SVEXTPROC* divagl_glVertexAttribI4svEXT;
extern PFNGLVERTEXATTRIBI4UBVPROC* divagl_glVertexAttribI4ubv;
extern PFNGLVERTEXATTRIBI4UBVEXTPROC* divagl_glVertexAttribI4ubvEXT;
extern PFNGLVERTEXATTRIBI4UIPROC* divagl_glVertexAttribI4ui;
extern PFNGLVERTEXATTRIBI4UIEXTPROC* divagl_glVertexAttribI4uiEXT;
extern PFNGLVERTEXATTRIBI4UIVPROC* divagl_glVertexAttribI4uiv;
extern PFNGLVERTEXATTRIBI4UIVEXTPROC* divagl_glVertexAttribI4uivEXT;
extern PFNGLVERTEXATTRIBI4USVPROC* divagl_glVertexAttribI4usv;
extern PFNGLVERTEXATTRIBI4USVEXTPROC* divagl_glVertexAttribI4usvEXT;
extern PFNGLVERTEXATTRIBIPOINTERPROC* divagl_glVertexAttribIPointer;
extern PFNGLVERTEXATTRIBIPOINTEREXTPROC* divagl_glVertexAttribIPointerEXT;
extern PFNGLVERTEXATTRIBPOINTERPROC* divagl_glVertexAttribPointer;
extern PFNGLVERTEXATTRIBPOINTERNVPROC* divagl_glVertexAttribPointerNV;
extern PFNGLVERTEXATTRIBS1DVNVPROC* divagl_glVertexAttribs1dvNV;
extern PFNGLVERTEXATTRIBS1FVNVPROC* divagl_glVertexAttribs1fvNV;
extern PFNGLVERTEXATTRIBS1HVNVPROC* divagl_glVertexAttribs1hvNV;
extern PFNGLVERTEXATTRIBS1SVNVPROC* divagl_glVertexAttribs1svNV;
extern PFNGLVERTEXATTRIBS2DVNVPROC* divagl_glVertexAttribs2dvNV;
extern PFNGLVERTEXATTRIBS2FVNVPROC* divagl_glVertexAttribs2fvNV;
extern PFNGLVERTEXATTRIBS2HVNVPROC* divagl_glVertexAttribs2hvNV;
extern PFNGLVERTEXATTRIBS2SVNVPROC* divagl_glVertexAttribs2svNV;
extern PFNGLVERTEXATTRIBS3DVNVPROC* divagl_glVertexAttribs3dvNV;
extern PFNGLVERTEXATTRIBS3FVNVPROC* divagl_glVertexAttribs3fvNV;
extern PFNGLVERTEXATTRIBS3HVNVPROC* divagl_glVertexAttribs3hvNV;
extern PFNGLVERTEXATTRIBS3SVNVPROC* divagl_glVertexAttribs3svNV;
extern PFNGLVERTEXATTRIBS4DVNVPROC* divagl_glVertexAttribs4dvNV;
extern PFNGLVERTEXATTRIBS4FVNVPROC* divagl_glVertexAttribs4fvNV;
extern PFNGLVERTEXATTRIBS4HVNVPROC* divagl_glVertexAttribs4hvNV;
extern PFNGLVERTEXATTRIBS4SVNVPROC* divagl_glVertexAttribs4svNV;
extern PFNGLVERTEXATTRIBS4UBVNVPROC* divagl_glVertexAttribs4ubvNV;
extern PFNGLVERTEXPOINTEREXTPROC* divagl_glVertexPointerEXT;
extern PFNGLWINDOWPOS2DPROC* divagl_glWindowPos2d;
extern PFNGLWINDOWPOS2DARBPROC* divagl_glWindowPos2dARB;
extern PFNGLWINDOWPOS2DVPROC* divagl_glWindowPos2dv;
extern PFNGLWINDOWPOS2DVARBPROC* divagl_glWindowPos2dvARB;
extern PFNGLWINDOWPOS2FPROC* divagl_glWindowPos2f;
extern PFNGLWINDOWPOS2FARBPROC* divagl_glWindowPos2fARB;
extern PFNGLWINDOWPOS2FVPROC* divagl_glWindowPos2fv;
extern PFNGLWINDOWPOS2FVARBPROC* divagl_glWindowPos2fvARB;
extern PFNGLWINDOWPOS2IPROC* divagl_glWindowPos2i;
extern PFNGLWINDOWPOS2IARBPROC* divagl_glWindowPos2iARB;
extern PFNGLWINDOWPOS2IVPROC* divagl_glWindowPos2iv;
extern PFNGLWINDOWPOS2IVARBPROC* divagl_glWindowPos2ivARB;
extern PFNGLWINDOWPOS2SPROC* divagl_glWindowPos2s;
extern PFNGLWINDOWPOS2SARBPROC* divagl_glWindowPos2sARB;
extern PFNGLWINDOWPOS2SVPROC* divagl_glWindowPos2sv;
extern PFNGLWINDOWPOS2SVARBPROC* divagl_glWindowPos2svARB;
extern PFNGLWINDOWPOS3DPROC* divagl_glWindowPos3d;
extern PFNGLWINDOWPOS3DARBPROC* divagl_glWindowPos3dARB;
extern PFNGLWINDOWPOS3DVPROC* divagl_glWindowPos3dv;
extern PFNGLWINDOWPOS3DVARBPROC* divagl_glWindowPos3dvARB;
extern PFNGLWINDOWPOS3FPROC* divagl_glWindowPos3f;
extern PFNGLWINDOWPOS3FARBPROC* divagl_glWindowPos3fARB;
extern PFNGLWINDOWPOS3FVPROC* divagl_glWindowPos3fv;
extern PFNGLWINDOWPOS3FVARBPROC* divagl_glWindowPos3fvARB;
extern PFNGLWINDOWPOS3IPROC* divagl_glWindowPos3i;
extern PFNGLWINDOWPOS3IARBPROC* divagl_glWindowPos3iARB;
extern PFNGLWINDOWPOS3IVPROC* divagl_glWindowPos3iv;
extern PFNGLWINDOWPOS3IVARBPROC* divagl_glWindowPos3ivARB;
extern PFNGLWINDOWPOS3SPROC* divagl_glWindowPos3s;
extern PFNGLWINDOWPOS3SARBPROC* divagl_glWindowPos3sARB;
extern PFNGLWINDOWPOS3SVPROC* divagl_glWindowPos3sv;
extern PFNGLWINDOWPOS3SVARBPROC* divagl_glWindowPos3svARB;
extern PFNWGLALLOCATEMEMORYNVPROC* divagl_wglAllocateMemoryNV;
extern PFNWGLBINDSWAPBARRIERNVPROC* divagl_wglBindSwapBarrierNV;
extern PFNWGLBINDTEXIMAGEARBPROC* divagl_wglBindTexImageARB;
extern PFNWGLBINDVIDEOIMAGENVPROC* divagl_wglBindVideoImageNV;
extern PFNWGLCHOOSEPIXELFORMATARBPROC* divagl_wglChoosePixelFormatARB;
extern PFNWGLCREATEBUFFERREGIONARBPROC* divagl_wglCreateBufferRegionARB;
extern PFNWGLCREATECONTEXTATTRIBSARBPROC* divagl_wglCreateContextAttribsARB;
extern PFNWGLCREATEPBUFFERARBPROC* divagl_wglCreatePbufferARB;
extern PFNWGLDELETEBUFFERREGIONARBPROC* divagl_wglDeleteBufferRegionARB;
extern PFNWGLDESTROYPBUFFERARBPROC* divagl_wglDestroyPbufferARB;
extern PFNWGLDXCLOSEDEVICENVPROC* divagl_wglDXCloseDeviceNV;
extern PFNWGLDXLOCKOBJECTSNVPROC* divagl_wglDXLockObjectsNV;
extern PFNWGLDXOPENDEVICENVPROC* divagl_wglDXOpenDeviceNV;
extern PFNWGLDXREGISTEROBJECTNVPROC* divagl_wglDXRegisterObjectNV;
extern PFNWGLDXSETRESOURCESHAREHANDLENVPROC* divagl_wglDXSetResourceShareHandleNV;
extern PFNWGLDXUNLOCKOBJECTSNVPROC* divagl_wglDXUnlockObjectsNV;
extern PFNWGLDXUNREGISTEROBJECTNVPROC* divagl_wglDXUnregisterObjectNV;
extern PFNWGLFREEMEMORYNVPROC* divagl_wglFreeMemoryNV;
extern PFNWGLGETCURRENTCONTEXTPROC* divagl_wglGetCurrentContext;
extern PFNWGLGETCURRENTREADDCARBPROC* divagl_wglGetCurrentReadDCARB;
extern PFNWGLGETEXTENSIONSSTRINGARBPROC* divagl_wglGetExtensionsStringARB;
extern PFNWGLGETEXTENSIONSSTRINGEXTPROC* divagl_wglGetExtensionsStringEXT;
extern PFNWGLGETPBUFFERDCARBPROC* divagl_wglGetPbufferDCARB;
extern PFNWGLGETPIXELFORMATATTRIBFVARBPROC* divagl_wglGetPixelFormatAttribfvARB;
extern PFNWGLGETPIXELFORMATATTRIBIVARBPROC* divagl_wglGetPixelFormatAttribivARB;
extern PFNWGLGETPROCADDRESSPROC* divagl_wglGetProcAddress;
extern PFNWGLGETSWAPINTERVALEXTPROC* divagl_wglGetSwapIntervalEXT;
extern PFNWGLGETVIDEODEVICENVPROC* divagl_wglGetVideoDeviceNV;
extern PFNWGLGETVIDEOINFONVPROC* divagl_wglGetVideoInfoNV;
extern PFNWGLJOINSWAPGROUPNVPROC* divagl_wglJoinSwapGroupNV;
extern PFNWGLMAKECONTEXTCURRENTARBPROC* divagl_wglMakeContextCurrentARB;
extern PFNWGLQUERYFRAMECOUNTNVPROC* divagl_wglQueryFrameCountNV;
extern PFNWGLQUERYMAXSWAPGROUPSNVPROC* divagl_wglQueryMaxSwapGroupsNV;
extern PFNWGLQUERYPBUFFERARBPROC* divagl_wglQueryPbufferARB;
extern PFNWGLQUERYSWAPGROUPNVPROC* divagl_wglQuerySwapGroupNV;
extern PFNWGLRELEASEPBUFFERDCARBPROC* divagl_wglReleasePbufferDCARB;
extern PFNWGLRELEASETEXIMAGEARBPROC* divagl_wglReleaseTexImageARB;
extern PFNWGLRELEASEVIDEODEVICENVPROC* divagl_wglReleaseVideoDeviceNV;
extern PFNWGLRELEASEVIDEOIMAGENVPROC* divagl_wglReleaseVideoImageNV;
extern PFNWGLRESETFRAMECOUNTNVPROC* divagl_wglResetFrameCountNV;
extern PFNWGLRESTOREBUFFERREGIONARBPROC* divagl_wglRestoreBufferRegionARB;
extern PFNWGLSAVEBUFFERREGIONARBPROC* divagl_wglSaveBufferRegionARB;
extern PFNWGLSENDPBUFFERTOVIDEONVPROC* divagl_wglSendPbufferToVideoNV;
extern PFNWGLSETPBUFFERATTRIBARBPROC* divagl_wglSetPbufferAttribARB;
extern PFNWGLSWAPINTERVALEXTPROC* divagl_wglSwapIntervalEXT;

extern PFNGLDRAWBUFFERGLUTPROC* divagl_glDrawBufferGLUT;
extern PFNGLENABLEGLUTPROC* divagl_glEnableGLUT;
extern PFNGLFINISHGLUTPROC* divagl_glFinishGLUT;
extern PFNGLGETERRORGLUTPROC* divagl_glGetErrorGLUT;
extern PFNGLGETINTEGERVGLUTPROC* divagl_glGetIntegervGLUT;
extern PFNGLGETSTRINGGLUTPROC* divagl_glGetStringGLUT;
extern PFNGLPIXELSTOREIGLUTPROC* divagl_glPixelStoreiGLUT;
extern PFNGLREADBUFFERGLUTPROC* divagl_glReadBufferGLUT;
extern PFNGLVIEWPORTGLUTPROC* divagl_glViewportGLUT;
extern PFNWGLCREATECONTEXTGLUTPROC* divagl_wglCreateContextGLUT;
extern PFNWGLDELETECONTEXTGLUTPROC* divagl_wglDeleteContextGLUT;
extern PFNWGLGETCURRENTCONTEXTGLUTPROC* divagl_wglGetCurrentContextGLUT;
extern PFNWGLGETCURRENTDCGLUTPROC* divagl_wglGetCurrentDCGLUT;
extern PFNWGLGETPROCADDRESSGLUTPROC* divagl_wglGetProcAddressGLUT;
extern PFNWGLMAKECURRENTGLUTPROC* divagl_wglMakeCurrentGLUT;

extern PFNGLTEXPARAMETERIVPROC divagl_glTexParameteriv;
extern PFNGLDRAWARRAYSINSTANCEDPROC divagl_glDrawArraysInstanced;
extern PFNGLPRIMITIVERESTARTINDEXPROC divagl_glPrimitiveRestartIndex;
extern PFNGLGETUNIFORMBLOCKINDEXPROC divagl_glGetUniformBlockIndex;
extern PFNGLUNIFORMBLOCKBINDINGPROC divagl_glUniformBlockBinding;
extern PFNGLGETINTEGER64I_VPROC divagl_glGetInteger64i_v;
extern PFNGLVERTEXATTRIBDIVISORPROC divagl_glVertexAttribDivisor;
extern PFNGLCLEARDEPTHFPROC divagl_glClearDepthf;
extern PFNGLGETPROGRAMBINARYPROC divagl_glGetProgramBinary;
extern PFNGLPROGRAMBINARYPROC divagl_glProgramBinary;
extern PFNGLPUSHDEBUGGROUPPROC divagl_glPushDebugGroup;
extern PFNGLPOPDEBUGGROUPPROC divagl_glPopDebugGroup;
extern PFNGLBUFFERSTORAGEPROC divagl_glBufferStorage;
extern PFNGLCREATEBUFFERSPROC divagl_glCreateBuffers;
extern PFNGLNAMEDBUFFERSTORAGEPROC divagl_glNamedBufferStorage;
extern PFNGLNAMEDBUFFERSUBDATAPROC divagl_glNamedBufferSubData;
extern PFNGLMAPNAMEDBUFFERPROC divagl_glMapNamedBuffer;
extern PFNGLMAPNAMEDBUFFERRANGEPROC divagl_glMapNamedBufferRange;
extern PFNGLUNMAPNAMEDBUFFERPROC divagl_glUnmapNamedBuffer;
extern PFNGLTEXTURESUBIMAGE2DPROC divagl_glTextureSubImage2D;

#define glBindTextureDLL (*divagl_glBindTextureDLL)
#define glBlendFuncDLL (*divagl_glBlendFuncDLL)
#define glClearDLL (*divagl_glClearDLL)
#define glClearColorDLL (*divagl_glClearColorDLL)
#define glClearDepthDLL (*divagl_glClearDepthDLL)
#define glClearStencilDLL (*divagl_glClearStencilDLL)
#define glColorMaskDLL (*divagl_glColorMaskDLL)
#define glCopyTexImage2DDLL (*divagl_glCopyTexImage2DDLL)
#define glCopyTexSubImage2DDLL (*divagl_glCopyTexSubImage2DDLL)
#define glCullFaceDLL (*divagl_glCullFaceDLL)
#define glDeleteTexturesDLL (*divagl_glDeleteTexturesDLL)
#define glDepthFuncDLL (*divagl_glDepthFuncDLL)
#define glDepthMaskDLL (*divagl_glDepthMaskDLL)
#define glDisableDLL (*divagl_glDisableDLL)
#define glDrawArraysDLL (*divagl_glDrawArraysDLL)
#define glDrawBufferDLL (*divagl_glDrawBufferDLL)
#define glDrawElementsDLL (*divagl_glDrawElementsDLL)
#define glEnableDLL (*divagl_glEnableDLL)
#define glFinishDLL (*divagl_glFinishDLL)
#define glFrontFaceDLL (*divagl_glFrontFaceDLL)
#define glGenTexturesDLL (*divagl_glGenTexturesDLL)
#define glGetBooleanvDLL (*divagl_glGetBooleanvDLL)
#define glGetErrorDLL (*divagl_glGetErrorDLL)
#define glGetFloatvDLL (*divagl_glGetFloatvDLL)
#define glGetIntegervDLL (*divagl_glGetIntegervDLL)
#define glGetTexImageDLL (*divagl_glGetTexImageDLL)
#define glIsEnabledDLL (*divagl_glIsEnabledDLL)
#define glPixelStoreiDLL (*divagl_glPixelStoreiDLL)
#define glPolygonModeDLL (*divagl_glPolygonModeDLL)
#define glReadBufferDLL (*divagl_glReadBufferDLL)
#define glReadPixelsDLL (*divagl_glReadPixelsDLL)
#define glScissorDLL (*divagl_glScissorDLL)
#define glTexImage1DDLL (*divagl_glTexImage1DDLL)
#define glTexImage2DDLL (*divagl_glTexImage2DDLL)
#define glTexParameterfDLL (*divagl_glTexParameterfDLL)
#define glTexParameterfvDLL (*divagl_glTexParameterfvDLL)
#define glTexParameteriDLL (*divagl_glTexParameteriDLL)
#define glTexSubImage2DDLL (*divagl_glTexSubImage2DDLL)
#define glViewportDLL (*divagl_glViewportDLL)
#define wglGetProcAddressDLL (*divagl_wglGetProcAddressDLL)

#define glActiveStencilFaceEXT (*divagl_glActiveStencilFaceEXT)
#define glActiveTexture (*divagl_glActiveTexture)
#define glActiveTextureARB (*divagl_glActiveTextureARB)
#define glActiveVaryingNV (*divagl_glActiveVaryingNV)
#define glAreProgramsResidentNV (*divagl_glAreProgramsResidentNV)
#define glAreTexturesResidentEXT (*divagl_glAreTexturesResidentEXT)
#define glArrayElementEXT (*divagl_glArrayElementEXT)
#define glAttachObjectARB (*divagl_glAttachObjectARB)
#define glAttachShader (*divagl_glAttachShader)
#define glBeginConditionalRender (*divagl_glBeginConditionalRender)
#define glBeginConditionalRenderNV (*divagl_glBeginConditionalRenderNV)
#define glBeginOcclusionQueryNV (*divagl_glBeginOcclusionQueryNV)
#define glBeginQuery (*divagl_glBeginQuery)
#define glBeginQueryARB (*divagl_glBeginQueryARB)
#define glBeginTransformFeedback (*divagl_glBeginTransformFeedback)
#define glBeginTransformFeedbackNV (*divagl_glBeginTransformFeedbackNV)
#define glBindAttribLocation (*divagl_glBindAttribLocation)
#define glBindAttribLocationARB (*divagl_glBindAttribLocationARB)
#define glBindBuffer (*divagl_glBindBuffer)
#define glBindBufferBase (*divagl_glBindBufferBase)
#define glBindBufferOffsetNV (*divagl_glBindBufferOffsetNV)
#define glBindBufferRange (*divagl_glBindBufferRange)
#define glBindBufferRangeNV (*divagl_glBindBufferRangeNV)
#define glBindFragDataLocation (*divagl_glBindFragDataLocation)
#define glBindFragDataLocationEXT (*divagl_glBindFragDataLocationEXT)
#define glBindFramebuffer (*divagl_glBindFramebuffer)
#define glBindProgramARB (*divagl_glBindProgramARB)
#define glBindProgramNV (*divagl_glBindProgramNV)
#define glBindRenderbuffer (*divagl_glBindRenderbuffer)
#define glBindSampler (*divagl_glBindSampler)
#define glBindTextureEXT (*divagl_glBindTextureEXT)
#define glBindVertexArray (*divagl_glBindVertexArray)
#define glBlendColor (*divagl_glBlendColor)
#define glBlendColorEXT (*divagl_glBlendColorEXT)
#define glBlendEquation (*divagl_glBlendEquation)
#define glBlendEquationEXT (*divagl_glBlendEquationEXT)
#define glBlendEquationSeparate (*divagl_glBlendEquationSeparate)
#define glBlendEquationSeparateEXT (*divagl_glBlendEquationSeparateEXT)
#define glBlendFuncSeparate (*divagl_glBlendFuncSeparate)
#define glBlendFuncSeparateEXT (*divagl_glBlendFuncSeparateEXT)
#define glBlitFramebuffer (*divagl_glBlitFramebuffer)
#define glBlitFramebufferEXT (*divagl_glBlitFramebufferEXT)
#define glBufferData (*divagl_glBufferData)
#define glBufferSubData (*divagl_glBufferSubData)
#define glBufferSubDataARB (*divagl_glBufferSubDataARB)
#define glCheckFramebufferStatus (*divagl_glCheckFramebufferStatus)
#define glCheckFramebufferStatusEXT (*divagl_glCheckFramebufferStatusEXT)
#define glCheckNamedFramebufferStatusEXT (*divagl_glCheckNamedFramebufferStatusEXT)
#define glClearBufferfi (*divagl_glClearBufferfi)
#define glClearBufferfv (*divagl_glClearBufferfv)
#define glClearBufferiv (*divagl_glClearBufferiv)
#define glClearBufferuiv (*divagl_glClearBufferuiv)
#define glClearColorIiEXT (*divagl_glClearColorIiEXT)
#define glClearColorIuiEXT (*divagl_glClearColorIuiEXT)
#define glClearDepthdNV (*divagl_glClearDepthdNV)
#define glClientActiveTextureARB (*divagl_glClientActiveTextureARB)
#define glClientAttribDefaultEXT (*divagl_glClientAttribDefaultEXT)
#define glColor3hNV (*divagl_glColor3hNV)
#define glColor3hvNV (*divagl_glColor3hvNV)
#define glColor4hNV (*divagl_glColor4hNV)
#define glColor4hvNV (*divagl_glColor4hvNV)
#define glColorMaski (*divagl_glColorMaski)
#define glColorMaskIndexedEXT (*divagl_glColorMaskIndexedEXT)
#define glColorPointerEXT (*divagl_glColorPointerEXT)
#define glColorSubTable (*divagl_glColorSubTable)
#define glColorSubTableEXT (*divagl_glColorSubTableEXT)
#define glColorTable (*divagl_glColorTable)
#define glColorTableEXT (*divagl_glColorTableEXT)
#define glColorTableParameterfv (*divagl_glColorTableParameterfv)
#define glColorTableParameteriv (*divagl_glColorTableParameteriv)
#define glCombinerInputNV (*divagl_glCombinerInputNV)
#define glCombinerOutputNV (*divagl_glCombinerOutputNV)
#define glCombinerParameterfNV (*divagl_glCombinerParameterfNV)
#define glCombinerParameterfvNV (*divagl_glCombinerParameterfvNV)
#define glCombinerParameteriNV (*divagl_glCombinerParameteriNV)
#define glCombinerParameterivNV (*divagl_glCombinerParameterivNV)
#define glCombinerStageParameterfvNV (*divagl_glCombinerStageParameterfvNV)
#define glCompileShader (*divagl_glCompileShader)
#define glCompileShaderARB (*divagl_glCompileShaderARB)
#define glCompressedMultiTexImage1DEXT (*divagl_glCompressedMultiTexImage1DEXT)
#define glCompressedMultiTexImage2DEXT (*divagl_glCompressedMultiTexImage2DEXT)
#define glCompressedMultiTexImage3DEXT (*divagl_glCompressedMultiTexImage3DEXT)
#define glCompressedMultiTexSubImage1DEXT (*divagl_glCompressedMultiTexSubImage1DEXT)
#define glCompressedMultiTexSubImage2DEXT (*divagl_glCompressedMultiTexSubImage2DEXT)
#define glCompressedMultiTexSubImage3DEXT (*divagl_glCompressedMultiTexSubImage3DEXT)
#define glCompressedTexImage1D (*divagl_glCompressedTexImage1D)
#define glCompressedTexImage1DARB (*divagl_glCompressedTexImage1DARB)
#define glCompressedTexImage2D (*divagl_glCompressedTexImage2D)
#define glCompressedTexImage2DARB (*divagl_glCompressedTexImage2DARB)
#define glCompressedTexImage3D (*divagl_glCompressedTexImage3D)
#define glCompressedTexImage3DARB (*divagl_glCompressedTexImage3DARB)
#define glCompressedTexSubImage1D (*divagl_glCompressedTexSubImage1D)
#define glCompressedTexSubImage1DARB (*divagl_glCompressedTexSubImage1DARB)
#define glCompressedTexSubImage2D (*divagl_glCompressedTexSubImage2D)
#define glCompressedTexSubImage2DARB (*divagl_glCompressedTexSubImage2DARB)
#define glCompressedTexSubImage3D (*divagl_glCompressedTexSubImage3D)
#define glCompressedTexSubImage3DARB (*divagl_glCompressedTexSubImage3DARB)
#define glCompressedTextureImage1DEXT (*divagl_glCompressedTextureImage1DEXT)
#define glCompressedTextureImage2DEXT (*divagl_glCompressedTextureImage2DEXT)
#define glCompressedTextureImage3DEXT (*divagl_glCompressedTextureImage3DEXT)
#define glCompressedTextureSubImage1DEXT (*divagl_glCompressedTextureSubImage1DEXT)
#define glCompressedTextureSubImage2DEXT (*divagl_glCompressedTextureSubImage2DEXT)
#define glCompressedTextureSubImage3DEXT (*divagl_glCompressedTextureSubImage3DEXT)
#define glConvolutionFilter1D (*divagl_glConvolutionFilter1D)
#define glConvolutionFilter2D (*divagl_glConvolutionFilter2D)
#define glConvolutionParameterf (*divagl_glConvolutionParameterf)
#define glConvolutionParameterfv (*divagl_glConvolutionParameterfv)
#define glConvolutionParameteri (*divagl_glConvolutionParameteri)
#define glConvolutionParameteriv (*divagl_glConvolutionParameteriv)
#define glCopyColorSubTable (*divagl_glCopyColorSubTable)
#define glCopyColorTable (*divagl_glCopyColorTable)
#define glCopyConvolutionFilter1D (*divagl_glCopyConvolutionFilter1D)
#define glCopyConvolutionFilter2D (*divagl_glCopyConvolutionFilter2D)
#define glCopyImageSubData (*divagl_glCopyImageSubData)
#define glCopyMultiTexImage1DEXT (*divagl_glCopyMultiTexImage1DEXT)
#define glCopyMultiTexImage2DEXT (*divagl_glCopyMultiTexImage2DEXT)
#define glCopyMultiTexSubImage1DEXT (*divagl_glCopyMultiTexSubImage1DEXT)
#define glCopyMultiTexSubImage3DEXT (*divagl_glCopyMultiTexSubImage3DEXT)
#define glCopyTexSubImage3D (*divagl_glCopyTexSubImage3D)
#define glCopyTexSubImage3DEXT (*divagl_glCopyTexSubImage3DEXT)
#define glCopyTextureImage1DEXT (*divagl_glCopyTextureImage1DEXT)
#define glCopyTextureImage2DEXT (*divagl_glCopyTextureImage2DEXT)
#define glCopyTextureSubImage1DEXT (*divagl_glCopyTextureSubImage1DEXT)
#define glCopyTextureSubImage2DEXT (*divagl_glCopyTextureSubImage2DEXT)
#define glCopyTextureSubImage3DEXT (*divagl_glCopyTextureSubImage3DEXT)
#define glCreateProgram (*divagl_glCreateProgram)
#define glCreateProgramObjectARB (*divagl_glCreateProgramObjectARB)
#define glCreateShader (*divagl_glCreateShader)
#define glCreateShaderObjectARB (*divagl_glCreateShaderObjectARB)
#define glDeleteBuffers (*divagl_glDeleteBuffers)
#define glDeleteFencesNV (*divagl_glDeleteFencesNV)
#define glDeleteFramebuffers (*divagl_glDeleteFramebuffers)
#define glDeleteObjectARB (*divagl_glDeleteObjectARB)
#define glDeleteOcclusionQueriesNV (*divagl_glDeleteOcclusionQueriesNV)
#define glDeleteProgram (*divagl_glDeleteProgram)
#define glDeleteProgramsARB (*divagl_glDeleteProgramsARB)
#define glDeleteProgramsNV (*divagl_glDeleteProgramsNV)
#define glDeleteQueries (*divagl_glDeleteQueries)
#define glDeleteQueriesARB (*divagl_glDeleteQueriesARB)
#define glDeleteRenderbuffers (*divagl_glDeleteRenderbuffers)
#define glDeleteSamplers (*divagl_glDeleteSamplers)
#define glDeleteShader (*divagl_glDeleteShader)
#define glDeleteTextures (*divagl_glDeleteTextures)
#define glDeleteTexturesEXT (*divagl_glDeleteTexturesEXT)
#define glDeleteVertexArrays (*divagl_glDeleteVertexArrays)
#define glDepthBoundsdNV (*divagl_glDepthBoundsdNV)
#define glDepthBoundsEXT (*divagl_glDepthBoundsEXT)
#define glDepthRangedNV (*divagl_glDepthRangedNV)
#define glDetachObjectARB (*divagl_glDetachObjectARB)
#define glDetachShader (*divagl_glDetachShader)
#define glDisableClientStateIndexedEXT (*divagl_glDisableClientStateIndexedEXT)
#define glDisablei (*divagl_glDisablei)
#define glDisableIndexedEXT (*divagl_glDisableIndexedEXT)
#define glDisableVertexAttribArray (*divagl_glDisableVertexAttribArray)
#define glDrawArraysEXT (*divagl_glDrawArraysEXT)
#define glDrawArraysInstancedARB (*divagl_glDrawArraysInstancedARB)
#define glDrawArraysInstancedEXT (*divagl_glDrawArraysInstancedEXT)
#define glDrawBuffers (*divagl_glDrawBuffers)
#define glDrawBuffersARB (*divagl_glDrawBuffersARB)
#define glDrawBuffersATI (*divagl_glDrawBuffersATI)
#define glDrawElementsInstancedARB (*divagl_glDrawElementsInstancedARB)
#define glDrawElementsInstancedEXT (*divagl_glDrawElementsInstancedEXT)
#define glDrawRangeElements (*divagl_glDrawRangeElements)
#define glDrawRangeElementsEXT (*divagl_glDrawRangeElementsEXT)
#define glEdgeFlagPointerEXT (*divagl_glEdgeFlagPointerEXT)
#define glEnableClientStateIndexedEXT (*divagl_glEnableClientStateIndexedEXT)
#define glEnablei (*divagl_glEnablei)
#define glEnableIndexedEXT (*divagl_glEnableIndexedEXT)
#define glEnableVertexAttribArray (*divagl_glEnableVertexAttribArray)
#define glEndConditionalRender (*divagl_glEndConditionalRender)
#define glEndConditionalRenderNV (*divagl_glEndConditionalRenderNV)
#define glEndOcclusionQueryNV (*divagl_glEndOcclusionQueryNV)
#define glEndQuery (*divagl_glEndQuery)
#define glEndQueryARB (*divagl_glEndQueryARB)
#define glEndTransformFeedback (*divagl_glEndTransformFeedback)
#define glEndTransformFeedbackNV (*divagl_glEndTransformFeedbackNV)
#define glExecuteProgramNV (*divagl_glExecuteProgramNV)
#define glFinalCombinerInputNV (*divagl_glFinalCombinerInputNV)
#define glFinishFenceNV (*divagl_glFinishFenceNV)
#define glFlushMappedBufferRange (*divagl_glFlushMappedBufferRange)
#define glFlushPixelDataRangeNV (*divagl_glFlushPixelDataRangeNV)
#define glFlushVertexArrayRangeNV (*divagl_glFlushVertexArrayRangeNV)
#define glFogCoordd (*divagl_glFogCoordd)
#define glFogCoorddEXT (*divagl_glFogCoorddEXT)
#define glFogCoorddv (*divagl_glFogCoorddv)
#define glFogCoorddvEXT (*divagl_glFogCoorddvEXT)
#define glFogCoordf (*divagl_glFogCoordf)
#define glFogCoordfEXT (*divagl_glFogCoordfEXT)
#define glFogCoordfv (*divagl_glFogCoordfv)
#define glFogCoordfvEXT (*divagl_glFogCoordfvEXT)
#define glFogCoordhNV (*divagl_glFogCoordhNV)
#define glFogCoordhvNV (*divagl_glFogCoordhvNV)
#define glFogCoordPointer (*divagl_glFogCoordPointer)
#define glFogCoordPointerEXT (*divagl_glFogCoordPointerEXT)
#define glFramebufferDrawBufferEXT (*divagl_glFramebufferDrawBufferEXT)
#define glFramebufferDrawBuffersEXT (*divagl_glFramebufferDrawBuffersEXT)
#define glFramebufferReadBufferEXT (*divagl_glFramebufferReadBufferEXT)
#define glFramebufferRenderbuffer (*divagl_glFramebufferRenderbuffer)
#define glFramebufferTexture (*divagl_glFramebufferTexture)
#define glFramebufferTexture1D (*divagl_glFramebufferTexture1D)
#define glFramebufferTexture1DEXT (*divagl_glFramebufferTexture1DEXT)
#define glFramebufferTexture2D (*divagl_glFramebufferTexture2D)
#define glFramebufferTexture3D (*divagl_glFramebufferTexture3D)
#define glFramebufferTexture3DEXT (*divagl_glFramebufferTexture3DEXT)
#define glFramebufferTextureARB (*divagl_glFramebufferTextureARB)
#define glFramebufferTextureEXT (*divagl_glFramebufferTextureEXT)
#define glFramebufferTextureFaceARB (*divagl_glFramebufferTextureFaceARB)
#define glFramebufferTextureFaceEXT (*divagl_glFramebufferTextureFaceEXT)
#define glFramebufferTextureLayer (*divagl_glFramebufferTextureLayer)
#define glFramebufferTextureLayerARB (*divagl_glFramebufferTextureLayerARB)
#define glFramebufferTextureLayerEXT (*divagl_glFramebufferTextureLayerEXT)
#define glGenBuffers (*divagl_glGenBuffers)
#define glGenBuffersARB (*divagl_glGenBuffersARB)
#define glGenerateMipmap (*divagl_glGenerateMipmap)
#define glGenerateMipmapEXT (*divagl_glGenerateMipmapEXT)
#define glGenerateMultiTexMipmapEXT (*divagl_glGenerateMultiTexMipmapEXT)
#define glGenerateTextureMipmapEXT (*divagl_glGenerateTextureMipmapEXT)
#define glGenFencesNV (*divagl_glGenFencesNV)
#define glGenFramebuffers (*divagl_glGenFramebuffers)
#define glGenOcclusionQueriesNV (*divagl_glGenOcclusionQueriesNV)
#define glGenProgramsARB (*divagl_glGenProgramsARB)
#define glGenProgramsNV (*divagl_glGenProgramsNV)
#define glGenQueries (*divagl_glGenQueries)
#define glGenQueriesARB (*divagl_glGenQueriesARB)
#define glGenRenderbuffers (*divagl_glGenRenderbuffers)
#define glGenSamplers (*divagl_glGenSamplers)
#define glGenTextures (*divagl_glGenTextures)
#define glGenTexturesEXT (*divagl_glGenTexturesEXT)
#define glGenVertexArrays (*divagl_glGenVertexArrays)
#define glGetActiveAttrib (*divagl_glGetActiveAttrib)
#define glGetActiveAttribARB (*divagl_glGetActiveAttribARB)
#define glGetActiveUniform (*divagl_glGetActiveUniform)
#define glGetActiveUniformARB (*divagl_glGetActiveUniformARB)
#define glGetActiveVaryingNV (*divagl_glGetActiveVaryingNV)
#define glGetAttachedObjectsARB (*divagl_glGetAttachedObjectsARB)
#define glGetAttachedShaders (*divagl_glGetAttachedShaders)
#define glGetAttribLocation (*divagl_glGetAttribLocation)
#define glGetAttribLocationARB (*divagl_glGetAttribLocationARB)
#define glGetBooleani_v (*divagl_glGetBooleani_v)
#define glGetBooleanIndexedvEXT (*divagl_glGetBooleanIndexedvEXT)
#define glGetBufferParameteriv (*divagl_glGetBufferParameteriv)
#define glGetBufferParameterivARB (*divagl_glGetBufferParameterivARB)
#define glGetBufferPointerv (*divagl_glGetBufferPointerv)
#define glGetBufferPointervARB (*divagl_glGetBufferPointervARB)
#define glGetBufferSubData (*divagl_glGetBufferSubData)
#define glGetBufferSubDataARB (*divagl_glGetBufferSubDataARB)
#define glGetColorTable (*divagl_glGetColorTable)
#define glGetColorTableEXT (*divagl_glGetColorTableEXT)
#define glGetColorTableParameterfv (*divagl_glGetColorTableParameterfv)
#define glGetColorTableParameterfvEXT (*divagl_glGetColorTableParameterfvEXT)
#define glGetColorTableParameteriv (*divagl_glGetColorTableParameteriv)
#define glGetColorTableParameterivEXT (*divagl_glGetColorTableParameterivEXT)
#define glGetCombinerInputParameterfvNV (*divagl_glGetCombinerInputParameterfvNV)
#define glGetCombinerInputParameterivNV (*divagl_glGetCombinerInputParameterivNV)
#define glGetCombinerOutputParameterfvNV (*divagl_glGetCombinerOutputParameterfvNV)
#define glGetCombinerOutputParameterivNV (*divagl_glGetCombinerOutputParameterivNV)
#define glGetCombinerStageParameterfvNV (*divagl_glGetCombinerStageParameterfvNV)
#define glGetCompressedMultiTexImageEXT (*divagl_glGetCompressedMultiTexImageEXT)
#define glGetCompressedTexImage (*divagl_glGetCompressedTexImage)
#define glGetCompressedTexImageARB (*divagl_glGetCompressedTexImageARB)
#define glGetCompressedTextureImageEXT (*divagl_glGetCompressedTextureImageEXT)
#define glGetConvolutionFilter (*divagl_glGetConvolutionFilter)
#define glGetConvolutionParameterfv (*divagl_glGetConvolutionParameterfv)
#define glGetConvolutionParameteriv (*divagl_glGetConvolutionParameteriv)
#define glGetDoubleIndexedvEXT (*divagl_glGetDoubleIndexedvEXT)
#define glGetFenceivNV (*divagl_glGetFenceivNV)
#define glGetFinalCombinerInputParameterfvNV (*divagl_glGetFinalCombinerInputParameterfvNV)
#define glGetFinalCombinerInputParameterivNV (*divagl_glGetFinalCombinerInputParameterivNV)
#define glGetFloatIndexedvEXT (*divagl_glGetFloatIndexedvEXT)
#define glGetFragDataLocation (*divagl_glGetFragDataLocation)
#define glGetFragDataLocationEXT (*divagl_glGetFragDataLocationEXT)
#define glGetFramebufferAttachmentParameteriv (*divagl_glGetFramebufferAttachmentParameteriv)
#define glGetFramebufferAttachmentParameterivEXT (*divagl_glGetFramebufferAttachmentParameterivEXT)
#define glGetFramebufferParameterivEXT (*divagl_glGetFramebufferParameterivEXT)
#define glGetHandleARB (*divagl_glGetHandleARB)
#define glGetHistogram (*divagl_glGetHistogram)
#define glGetHistogramParameterfv (*divagl_glGetHistogramParameterfv)
#define glGetHistogramParameteriv (*divagl_glGetHistogramParameteriv)
#define glGetInfoLogARB (*divagl_glGetInfoLogARB)
#define glGetIntegeri_v (*divagl_glGetIntegeri_v)
#define glGetIntegerIndexedvEXT (*divagl_glGetIntegerIndexedvEXT)
#define glGetMinmax (*divagl_glGetMinmax)
#define glGetMinmaxParameterfv (*divagl_glGetMinmaxParameterfv)
#define glGetMinmaxParameteriv (*divagl_glGetMinmaxParameteriv)
#define glGetMultisamplefvNV (*divagl_glGetMultisamplefvNV)
#define glGetMultiTexEnvfvEXT (*divagl_glGetMultiTexEnvfvEXT)
#define glGetMultiTexEnvivEXT (*divagl_glGetMultiTexEnvivEXT)
#define glGetMultiTexGendvEXT (*divagl_glGetMultiTexGendvEXT)
#define glGetMultiTexGenfvEXT (*divagl_glGetMultiTexGenfvEXT)
#define glGetMultiTexGenivEXT (*divagl_glGetMultiTexGenivEXT)
#define glGetMultiTexImageEXT (*divagl_glGetMultiTexImageEXT)
#define glGetMultiTexLevelParameterfvEXT (*divagl_glGetMultiTexLevelParameterfvEXT)
#define glGetMultiTexLevelParameterivEXT (*divagl_glGetMultiTexLevelParameterivEXT)
#define glGetMultiTexParameterfvEXT (*divagl_glGetMultiTexParameterfvEXT)
#define glGetMultiTexParameterIivEXT (*divagl_glGetMultiTexParameterIivEXT)
#define glGetMultiTexParameterIuivEXT (*divagl_glGetMultiTexParameterIuivEXT)
#define glGetMultiTexParameterivEXT (*divagl_glGetMultiTexParameterivEXT)
#define glGetNamedBufferParameterivEXT (*divagl_glGetNamedBufferParameterivEXT)
#define glGetNamedBufferPointervEXT (*divagl_glGetNamedBufferPointervEXT)
#define glGetNamedBufferSubDataEXT (*divagl_glGetNamedBufferSubDataEXT)
#define glGetNamedFramebufferAttachmentParameterivEXT (*divagl_glGetNamedFramebufferAttachmentParameterivEXT)
#define glGetNamedProgramivEXT (*divagl_glGetNamedProgramivEXT)
#define glGetNamedProgramLocalParameterdvEXT (*divagl_glGetNamedProgramLocalParameterdvEXT)
#define glGetNamedProgramLocalParameterfvEXT (*divagl_glGetNamedProgramLocalParameterfvEXT)
#define glGetNamedProgramLocalParameterIivEXT (*divagl_glGetNamedProgramLocalParameterIivEXT)
#define glGetNamedProgramLocalParameterIuivEXT (*divagl_glGetNamedProgramLocalParameterIuivEXT)
#define glGetNamedProgramStringEXT (*divagl_glGetNamedProgramStringEXT)
#define glGetNamedRenderbufferParameterivEXT (*divagl_glGetNamedRenderbufferParameterivEXT)
#define glGetObjectParameterfvARB (*divagl_glGetObjectParameterfvARB)
#define glGetObjectParameterivARB (*divagl_glGetObjectParameterivARB)
#define glGetOcclusionQueryivNV (*divagl_glGetOcclusionQueryivNV)
#define glGetOcclusionQueryuivNV (*divagl_glGetOcclusionQueryuivNV)
#define glGetPointerIndexedvEXT (*divagl_glGetPointerIndexedvEXT)
#define glGetPointervEXT (*divagl_glGetPointervEXT)
#define glGetProgramEnvParameterdvARB (*divagl_glGetProgramEnvParameterdvARB)
#define glGetProgramEnvParameterIivNV (*divagl_glGetProgramEnvParameterIivNV)
#define glGetProgramEnvParameterIuivNV (*divagl_glGetProgramEnvParameterIuivNV)
#define glGetProgramInfoLog (*divagl_glGetProgramInfoLog)
#define glGetProgramiv (*divagl_glGetProgramiv)
#define glGetProgramivNV (*divagl_glGetProgramivNV)
#define glGetProgramLocalParameterdvARB (*divagl_glGetProgramLocalParameterdvARB)
#define glGetProgramLocalParameterfvARB (*divagl_glGetProgramLocalParameterfvARB)
#define glGetProgramLocalParameterIivNV (*divagl_glGetProgramLocalParameterIivNV)
#define glGetProgramLocalParameterIuivNV (*divagl_glGetProgramLocalParameterIuivNV)
#define glGetProgramNamedParameterdvNV (*divagl_glGetProgramNamedParameterdvNV)
#define glGetProgramNamedParameterfvNV (*divagl_glGetProgramNamedParameterfvNV)
#define glGetProgramParameterdvNV (*divagl_glGetProgramParameterdvNV)
#define glGetProgramParameterfvNV (*divagl_glGetProgramParameterfvNV)
#define glGetProgramStringARB (*divagl_glGetProgramStringARB)
#define glGetProgramStringNV (*divagl_glGetProgramStringNV)
#define glGetQueryiv (*divagl_glGetQueryiv)
#define glGetQueryivARB (*divagl_glGetQueryivARB)
#define glGetQueryObjecti64vEXT (*divagl_glGetQueryObjecti64vEXT)
#define glGetQueryObjectiv (*divagl_glGetQueryObjectiv)
#define glGetQueryObjectivARB (*divagl_glGetQueryObjectivARB)
#define glGetQueryObjectui64v (*divagl_glGetQueryObjectui64v)
#define glGetQueryObjectui64vEXT (*divagl_glGetQueryObjectui64vEXT)
#define glGetQueryObjectuiv (*divagl_glGetQueryObjectuiv)
#define glGetQueryObjectuivARB (*divagl_glGetQueryObjectuivARB)
#define glGetRenderbufferParameteriv (*divagl_glGetRenderbufferParameteriv)
#define glGetRenderbufferParameterivEXT (*divagl_glGetRenderbufferParameterivEXT)
#define glGetSeparableFilter (*divagl_glGetSeparableFilter)
#define glGetShaderInfoLog (*divagl_glGetShaderInfoLog)
#define glGetShaderiv (*divagl_glGetShaderiv)
#define glGetShaderSource (*divagl_glGetShaderSource)
#define glGetShaderSourceARB (*divagl_glGetShaderSourceARB)
#define glGetStringi (*divagl_glGetStringi)
#define glGetTexParameterIiv (*divagl_glGetTexParameterIiv)
#define glGetTexParameterIivEXT (*divagl_glGetTexParameterIivEXT)
#define glGetTexParameterIuiv (*divagl_glGetTexParameterIuiv)
#define glGetTexParameterIuivEXT (*divagl_glGetTexParameterIuivEXT)
#define glGetTextureLevelParameterfvEXT (*divagl_glGetTextureLevelParameterfvEXT)
#define glGetTextureLevelParameterivEXT (*divagl_glGetTextureLevelParameterivEXT)
#define glGetTextureParameterfvEXT (*divagl_glGetTextureParameterfvEXT)
#define glGetTextureParameterIivEXT (*divagl_glGetTextureParameterIivEXT)
#define glGetTextureParameterIuivEXT (*divagl_glGetTextureParameterIuivEXT)
#define glGetTextureParameterivEXT (*divagl_glGetTextureParameterivEXT)
#define glGetTrackMatrixivNV (*divagl_glGetTrackMatrixivNV)
#define glGetTransformFeedbackVarying (*divagl_glGetTransformFeedbackVarying)
#define glGetTransformFeedbackVaryingNV (*divagl_glGetTransformFeedbackVaryingNV)
#define glGetUniformBufferSizeEXT (*divagl_glGetUniformBufferSizeEXT)
#define glGetUniformfv (*divagl_glGetUniformfv)
#define glGetUniformfvARB (*divagl_glGetUniformfvARB)
#define glGetUniformiv (*divagl_glGetUniformiv)
#define glGetUniformivARB (*divagl_glGetUniformivARB)
#define glGetUniformLocation (*divagl_glGetUniformLocation)
#define glGetUniformLocationARB (*divagl_glGetUniformLocationARB)
#define glGetUniformOffsetEXT (*divagl_glGetUniformOffsetEXT)
#define glGetUniformuiv (*divagl_glGetUniformuiv)
#define glGetUniformuivEXT (*divagl_glGetUniformuivEXT)
#define glGetVaryingLocationNV (*divagl_glGetVaryingLocationNV)
#define glGetVertexAttribdv (*divagl_glGetVertexAttribdv)
#define glGetVertexAttribdvARB (*divagl_glGetVertexAttribdvARB)
#define glGetVertexAttribdvNV (*divagl_glGetVertexAttribdvNV)
#define glGetVertexAttribfv (*divagl_glGetVertexAttribfv)
#define glGetVertexAttribfvARB (*divagl_glGetVertexAttribfvARB)
#define glGetVertexAttribfvNV (*divagl_glGetVertexAttribfvNV)
#define glGetVertexAttribIiv (*divagl_glGetVertexAttribIiv)
#define glGetVertexAttribIivEXT (*divagl_glGetVertexAttribIivEXT)
#define glGetVertexAttribIuiv (*divagl_glGetVertexAttribIuiv)
#define glGetVertexAttribIuivEXT (*divagl_glGetVertexAttribIuivEXT)
#define glGetVertexAttribiv (*divagl_glGetVertexAttribiv)
#define glGetVertexAttribivARB (*divagl_glGetVertexAttribivARB)
#define glGetVertexAttribivNV (*divagl_glGetVertexAttribivNV)
#define glGetVertexAttribPointerv (*divagl_glGetVertexAttribPointerv)
#define glGetVertexAttribPointervARB (*divagl_glGetVertexAttribPointervARB)
#define glGetVertexAttribPointervNV (*divagl_glGetVertexAttribPointervNV)
#define glGetVideoi64vNV (*divagl_glGetVideoi64vNV)
#define glGetVideoivNV (*divagl_glGetVideoivNV)
#define glGetVideoui64vNV (*divagl_glGetVideoui64vNV)
#define glGetVideouivNV (*divagl_glGetVideouivNV)
#define glHistogram (*divagl_glHistogram)
#define glIndexPointerEXT (*divagl_glIndexPointerEXT)
#define glIsBuffer (*divagl_glIsBuffer)
#define glIsEnabledi (*divagl_glIsEnabledi)
#define glIsEnabledIndexedEXT (*divagl_glIsEnabledIndexedEXT)
#define glIsFenceNV (*divagl_glIsFenceNV)
#define glIsFramebuffer (*divagl_glIsFramebuffer)
#define glIsFramebufferEXT (*divagl_glIsFramebufferEXT)
#define glIsOcclusionQueryNV (*divagl_glIsOcclusionQueryNV)
#define glIsProgram (*divagl_glIsProgram)
#define glIsProgramARB (*divagl_glIsProgramARB)
#define glIsProgramNV (*divagl_glIsProgramNV)
#define glIsQuery (*divagl_glIsQuery)
#define glIsQueryARB (*divagl_glIsQueryARB)
#define glIsRenderbuffer (*divagl_glIsRenderbuffer)
#define glIsRenderbufferEXT (*divagl_glIsRenderbufferEXT)
#define glIsShader (*divagl_glIsShader)
#define glIsTextureEXT (*divagl_glIsTextureEXT)
#define glIsVertexArray (*divagl_glIsVertexArray)
#define glLinkProgram (*divagl_glLinkProgram)
#define glLinkProgramARB (*divagl_glLinkProgramARB)
#define glLoadProgramNV (*divagl_glLoadProgramNV)
#define glLoadTransposeMatrixd (*divagl_glLoadTransposeMatrixd)
#define glLoadTransposeMatrixdARB (*divagl_glLoadTransposeMatrixdARB)
#define glLoadTransposeMatrixfARB (*divagl_glLoadTransposeMatrixfARB)
#define glLockArraysEXT (*divagl_glLockArraysEXT)
#define glMapBuffer (*divagl_glMapBuffer)
#define glMapBufferARB (*divagl_glMapBufferARB)
#define glMapBufferRange (*divagl_glMapBufferRange)
#define glMatrixFrustumEXT (*divagl_glMatrixFrustumEXT)
#define glMatrixLoaddEXT (*divagl_glMatrixLoaddEXT)
#define glMatrixLoadfEXT (*divagl_glMatrixLoadfEXT)
#define glMatrixLoadIdentityEXT (*divagl_glMatrixLoadIdentityEXT)
#define glMatrixLoadTransposedEXT (*divagl_glMatrixLoadTransposedEXT)
#define glMatrixLoadTransposefEXT (*divagl_glMatrixLoadTransposefEXT)
#define glMatrixMultdEXT (*divagl_glMatrixMultdEXT)
#define glMatrixMultfEXT (*divagl_glMatrixMultfEXT)
#define glMatrixMultTransposedEXT (*divagl_glMatrixMultTransposedEXT)
#define glMatrixMultTransposefEXT (*divagl_glMatrixMultTransposefEXT)
#define glMatrixOrthoEXT (*divagl_glMatrixOrthoEXT)
#define glMatrixPopEXT (*divagl_glMatrixPopEXT)
#define glMatrixPushEXT (*divagl_glMatrixPushEXT)
#define glMatrixRotatedEXT (*divagl_glMatrixRotatedEXT)
#define glMatrixRotatefEXT (*divagl_glMatrixRotatefEXT)
#define glMatrixScaledEXT (*divagl_glMatrixScaledEXT)
#define glMatrixScalefEXT (*divagl_glMatrixScalefEXT)
#define glMatrixTranslatedEXT (*divagl_glMatrixTranslatedEXT)
#define glMatrixTranslatefEXT (*divagl_glMatrixTranslatefEXT)
#define glMinmax (*divagl_glMinmax)
#define glMultiDrawArrays (*divagl_glMultiDrawArrays)
#define glMultiDrawArraysEXT (*divagl_glMultiDrawArraysEXT)
#define glMultiDrawElements (*divagl_glMultiDrawElements)
#define glMultiDrawElementsEXT (*divagl_glMultiDrawElementsEXT)
#define glMultiTexBufferEXT (*divagl_glMultiTexBufferEXT)
#define glMultiTexCoord1d (*divagl_glMultiTexCoord1d)
#define glMultiTexCoord1dARB (*divagl_glMultiTexCoord1dARB)
#define glMultiTexCoord1dv (*divagl_glMultiTexCoord1dv)
#define glMultiTexCoord1dvARB (*divagl_glMultiTexCoord1dvARB)
#define glMultiTexCoord1f (*divagl_glMultiTexCoord1f)
#define glMultiTexCoord1fARB (*divagl_glMultiTexCoord1fARB)
#define glMultiTexCoord1fv (*divagl_glMultiTexCoord1fv)
#define glMultiTexCoord1fvARB (*divagl_glMultiTexCoord1fvARB)
#define glMultiTexCoord1hNV (*divagl_glMultiTexCoord1hNV)
#define glMultiTexCoord1hvNV (*divagl_glMultiTexCoord1hvNV)
#define glMultiTexCoord1i (*divagl_glMultiTexCoord1i)
#define glMultiTexCoord1iARB (*divagl_glMultiTexCoord1iARB)
#define glMultiTexCoord1iv (*divagl_glMultiTexCoord1iv)
#define glMultiTexCoord1ivARB (*divagl_glMultiTexCoord1ivARB)
#define glMultiTexCoord1s (*divagl_glMultiTexCoord1s)
#define glMultiTexCoord1sARB (*divagl_glMultiTexCoord1sARB)
#define glMultiTexCoord1sv (*divagl_glMultiTexCoord1sv)
#define glMultiTexCoord1svARB (*divagl_glMultiTexCoord1svARB)
#define glMultiTexCoord2d (*divagl_glMultiTexCoord2d)
#define glMultiTexCoord2dARB (*divagl_glMultiTexCoord2dARB)
#define glMultiTexCoord2dv (*divagl_glMultiTexCoord2dv)
#define glMultiTexCoord2dvARB (*divagl_glMultiTexCoord2dvARB)
#define glMultiTexCoord2fARB (*divagl_glMultiTexCoord2fARB)
#define glMultiTexCoord2fvARB (*divagl_glMultiTexCoord2fvARB)
#define glMultiTexCoord2hNV (*divagl_glMultiTexCoord2hNV)
#define glMultiTexCoord2hvNV (*divagl_glMultiTexCoord2hvNV)
#define glMultiTexCoord2i (*divagl_glMultiTexCoord2i)
#define glMultiTexCoord2iARB (*divagl_glMultiTexCoord2iARB)
#define glMultiTexCoord2iv (*divagl_glMultiTexCoord2iv)
#define glMultiTexCoord2ivARB (*divagl_glMultiTexCoord2ivARB)
#define glMultiTexCoord2s (*divagl_glMultiTexCoord2s)
#define glMultiTexCoord2sARB (*divagl_glMultiTexCoord2sARB)
#define glMultiTexCoord2sv (*divagl_glMultiTexCoord2sv)
#define glMultiTexCoord2svARB (*divagl_glMultiTexCoord2svARB)
#define glMultiTexCoord3d (*divagl_glMultiTexCoord3d)
#define glMultiTexCoord3dARB (*divagl_glMultiTexCoord3dARB)
#define glMultiTexCoord3dv (*divagl_glMultiTexCoord3dv)
#define glMultiTexCoord3dvARB (*divagl_glMultiTexCoord3dvARB)
#define glMultiTexCoord3f (*divagl_glMultiTexCoord3f)
#define glMultiTexCoord3fARB (*divagl_glMultiTexCoord3fARB)
#define glMultiTexCoord3fv (*divagl_glMultiTexCoord3fv)
#define glMultiTexCoord3fvARB (*divagl_glMultiTexCoord3fvARB)
#define glMultiTexCoord3hNV (*divagl_glMultiTexCoord3hNV)
#define glMultiTexCoord3hvNV (*divagl_glMultiTexCoord3hvNV)
#define glMultiTexCoord3i (*divagl_glMultiTexCoord3i)
#define glMultiTexCoord3iARB (*divagl_glMultiTexCoord3iARB)
#define glMultiTexCoord3iv (*divagl_glMultiTexCoord3iv)
#define glMultiTexCoord3ivARB (*divagl_glMultiTexCoord3ivARB)
#define glMultiTexCoord3s (*divagl_glMultiTexCoord3s)
#define glMultiTexCoord3sARB (*divagl_glMultiTexCoord3sARB)
#define glMultiTexCoord3sv (*divagl_glMultiTexCoord3sv)
#define glMultiTexCoord3svARB (*divagl_glMultiTexCoord3svARB)
#define glMultiTexCoord4d (*divagl_glMultiTexCoord4d)
#define glMultiTexCoord4dARB (*divagl_glMultiTexCoord4dARB)
#define glMultiTexCoord4dv (*divagl_glMultiTexCoord4dv)
#define glMultiTexCoord4dvARB (*divagl_glMultiTexCoord4dvARB)
#define glMultiTexCoord4f (*divagl_glMultiTexCoord4f)
#define glMultiTexCoord4fARB (*divagl_glMultiTexCoord4fARB)
#define glMultiTexCoord4fv (*divagl_glMultiTexCoord4fv)
#define glMultiTexCoord4fvARB (*divagl_glMultiTexCoord4fvARB)
#define glMultiTexCoord4hNV (*divagl_glMultiTexCoord4hNV)
#define glMultiTexCoord4hvNV (*divagl_glMultiTexCoord4hvNV)
#define glMultiTexCoord4i (*divagl_glMultiTexCoord4i)
#define glMultiTexCoord4iARB (*divagl_glMultiTexCoord4iARB)
#define glMultiTexCoord4iv (*divagl_glMultiTexCoord4iv)
#define glMultiTexCoord4ivARB (*divagl_glMultiTexCoord4ivARB)
#define glMultiTexCoord4s (*divagl_glMultiTexCoord4s)
#define glMultiTexCoord4sARB (*divagl_glMultiTexCoord4sARB)
#define glMultiTexCoord4sv (*divagl_glMultiTexCoord4sv)
#define glMultiTexCoord4svARB (*divagl_glMultiTexCoord4svARB)
#define glMultiTexCoordPointerEXT (*divagl_glMultiTexCoordPointerEXT)
#define glMultiTexEnvfEXT (*divagl_glMultiTexEnvfEXT)
#define glMultiTexEnvfvEXT (*divagl_glMultiTexEnvfvEXT)
#define glMultiTexEnviEXT (*divagl_glMultiTexEnviEXT)
#define glMultiTexEnvivEXT (*divagl_glMultiTexEnvivEXT)
#define glMultiTexGendEXT (*divagl_glMultiTexGendEXT)
#define glMultiTexGendvEXT (*divagl_glMultiTexGendvEXT)
#define glMultiTexGenfEXT (*divagl_glMultiTexGenfEXT)
#define glMultiTexGenfvEXT (*divagl_glMultiTexGenfvEXT)
#define glMultiTexGeniEXT (*divagl_glMultiTexGeniEXT)
#define glMultiTexGenivEXT (*divagl_glMultiTexGenivEXT)
#define glMultiTexImage1DEXT (*divagl_glMultiTexImage1DEXT)
#define glMultiTexImage2DEXT (*divagl_glMultiTexImage2DEXT)
#define glMultiTexImage3DEXT (*divagl_glMultiTexImage3DEXT)
#define glMultiTexParameterfEXT (*divagl_glMultiTexParameterfEXT)
#define glMultiTexParameterfvEXT (*divagl_glMultiTexParameterfvEXT)
#define glMultiTexParameteriEXT (*divagl_glMultiTexParameteriEXT)
#define glMultiTexParameterIivEXT (*divagl_glMultiTexParameterIivEXT)
#define glMultiTexParameterIuivEXT (*divagl_glMultiTexParameterIuivEXT)
#define glMultiTexParameterivEXT (*divagl_glMultiTexParameterivEXT)
#define glMultiTexRenderbufferEXT (*divagl_glMultiTexRenderbufferEXT)
#define glMultiTexSubImage1DEXT (*divagl_glMultiTexSubImage1DEXT)
#define glMultiTexSubImage2DEXT (*divagl_glMultiTexSubImage2DEXT)
#define glMultiTexSubImage3DEXT (*divagl_glMultiTexSubImage3DEXT)
#define glMultTransposeMatrixd (*divagl_glMultTransposeMatrixd)
#define glMultTransposeMatrixdARB (*divagl_glMultTransposeMatrixdARB)
#define glMultTransposeMatrixfARB (*divagl_glMultTransposeMatrixfARB)
#define glNamedFramebufferRenderbufferEXT (*divagl_glNamedFramebufferRenderbufferEXT)
#define glNamedFramebufferTexture1DEXT (*divagl_glNamedFramebufferTexture1DEXT)
#define glNamedFramebufferTexture2DEXT (*divagl_glNamedFramebufferTexture2DEXT)
#define glNamedFramebufferTexture3DEXT (*divagl_glNamedFramebufferTexture3DEXT)
#define glNamedFramebufferTextureEXT (*divagl_glNamedFramebufferTextureEXT)
#define glNamedFramebufferTextureFaceEXT (*divagl_glNamedFramebufferTextureFaceEXT)
#define glNamedFramebufferTextureLayerEXT (*divagl_glNamedFramebufferTextureLayerEXT)
#define glNamedProgramLocalParameter4dEXT (*divagl_glNamedProgramLocalParameter4dEXT)
#define glNamedProgramLocalParameter4dvEXT (*divagl_glNamedProgramLocalParameter4dvEXT)
#define glNamedProgramLocalParameter4fEXT (*divagl_glNamedProgramLocalParameter4fEXT)
#define glNamedProgramLocalParameter4fvEXT (*divagl_glNamedProgramLocalParameter4fvEXT)
#define glNamedProgramLocalParameterI4iEXT (*divagl_glNamedProgramLocalParameterI4iEXT)
#define glNamedProgramLocalParameterI4ivEXT (*divagl_glNamedProgramLocalParameterI4ivEXT)
#define glNamedProgramLocalParameterI4uiEXT (*divagl_glNamedProgramLocalParameterI4uiEXT)
#define glNamedProgramLocalParameterI4uivEXT (*divagl_glNamedProgramLocalParameterI4uivEXT)
#define glNamedProgramLocalParameters4fvEXT (*divagl_glNamedProgramLocalParameters4fvEXT)
#define glNamedProgramLocalParametersI4ivEXT (*divagl_glNamedProgramLocalParametersI4ivEXT)
#define glNamedProgramLocalParametersI4uivEXT (*divagl_glNamedProgramLocalParametersI4uivEXT)
#define glNamedProgramStringEXT (*divagl_glNamedProgramStringEXT)
#define glNamedRenderbufferStorageEXT (*divagl_glNamedRenderbufferStorageEXT)
#define glNamedRenderbufferStorageMultisampleCoverageEXT (*divagl_glNamedRenderbufferStorageMultisampleCoverageEXT)
#define glNamedRenderbufferStorageMultisampleEXT (*divagl_glNamedRenderbufferStorageMultisampleEXT)
#define glNormal3hNV (*divagl_glNormal3hNV)
#define glNormal3hvNV (*divagl_glNormal3hvNV)
#define glNormalPointerEXT (*divagl_glNormalPointerEXT)
#define glPixelDataRangeNV (*divagl_glPixelDataRangeNV)
#define glPointParameterfARB (*divagl_glPointParameterfARB)
#define glPointParameterfEXT (*divagl_glPointParameterfEXT)
#define glPointParameterfvARB (*divagl_glPointParameterfvARB)
#define glPointParameterfvEXT (*divagl_glPointParameterfvEXT)
#define glPointParameteriNV (*divagl_glPointParameteriNV)
#define glPointParameteriv (*divagl_glPointParameteriv)
#define glPointParameterivNV (*divagl_glPointParameterivNV)
#define glPresentFrameDualFillNV (*divagl_glPresentFrameDualFillNV)
#define glPresentFrameKeyedNV (*divagl_glPresentFrameKeyedNV)
#define glPrimitiveRestartNV (*divagl_glPrimitiveRestartNV)
#define glPrioritizeTexturesEXT (*divagl_glPrioritizeTexturesEXT)
#define glProgramBufferParametersIivNV (*divagl_glProgramBufferParametersIivNV)
#define glProgramBufferParametersIuivNV (*divagl_glProgramBufferParametersIuivNV)
#define glProgramEnvParameter4dARB (*divagl_glProgramEnvParameter4dARB)
#define glProgramEnvParameter4dvARB (*divagl_glProgramEnvParameter4dvARB)
#define glProgramEnvParameterI4iNV (*divagl_glProgramEnvParameterI4iNV)
#define glProgramEnvParameterI4ivNV (*divagl_glProgramEnvParameterI4ivNV)
#define glProgramEnvParameterI4uiNV (*divagl_glProgramEnvParameterI4uiNV)
#define glProgramEnvParameterI4uivNV (*divagl_glProgramEnvParameterI4uivNV)
#define glProgramEnvParametersI4ivNV (*divagl_glProgramEnvParametersI4ivNV)
#define glProgramEnvParametersI4uivNV (*divagl_glProgramEnvParametersI4uivNV)
#define glProgramLocalParameter4dARB (*divagl_glProgramLocalParameter4dARB)
#define glProgramLocalParameter4dvARB (*divagl_glProgramLocalParameter4dvARB)
#define glProgramLocalParameterI4iNV (*divagl_glProgramLocalParameterI4iNV)
#define glProgramLocalParameterI4ivNV (*divagl_glProgramLocalParameterI4ivNV)
#define glProgramLocalParameterI4uiNV (*divagl_glProgramLocalParameterI4uiNV)
#define glProgramLocalParameterI4uivNV (*divagl_glProgramLocalParameterI4uivNV)
#define glProgramLocalParametersI4ivNV (*divagl_glProgramLocalParametersI4ivNV)
#define glProgramLocalParametersI4uivNV (*divagl_glProgramLocalParametersI4uivNV)
#define glProgramNamedParameter4dNV (*divagl_glProgramNamedParameter4dNV)
#define glProgramNamedParameter4dvNV (*divagl_glProgramNamedParameter4dvNV)
#define glProgramNamedParameter4fNV (*divagl_glProgramNamedParameter4fNV)
#define glProgramNamedParameter4fvNV (*divagl_glProgramNamedParameter4fvNV)
#define glProgramParameter4dNV (*divagl_glProgramParameter4dNV)
#define glProgramParameter4dvNV (*divagl_glProgramParameter4dvNV)
#define glProgramParameter4fNV (*divagl_glProgramParameter4fNV)
#define glProgramParameter4fvNV (*divagl_glProgramParameter4fvNV)
#define glProgramParameteriARB (*divagl_glProgramParameteriARB)
#define glProgramParameteriEXT (*divagl_glProgramParameteriEXT)
#define glProgramParameters4dvNV (*divagl_glProgramParameters4dvNV)
#define glProgramParameters4fvNV (*divagl_glProgramParameters4fvNV)
#define glProgramStringARB (*divagl_glProgramStringARB)
#define glProgramUniform1fEXT (*divagl_glProgramUniform1fEXT)
#define glProgramUniform1fvEXT (*divagl_glProgramUniform1fvEXT)
#define glProgramUniform1iEXT (*divagl_glProgramUniform1iEXT)
#define glProgramUniform1ivEXT (*divagl_glProgramUniform1ivEXT)
#define glProgramUniform1uiEXT (*divagl_glProgramUniform1uiEXT)
#define glProgramUniform1uivEXT (*divagl_glProgramUniform1uivEXT)
#define glProgramUniform2fEXT (*divagl_glProgramUniform2fEXT)
#define glProgramUniform2fvEXT (*divagl_glProgramUniform2fvEXT)
#define glProgramUniform2iEXT (*divagl_glProgramUniform2iEXT)
#define glProgramUniform2ivEXT (*divagl_glProgramUniform2ivEXT)
#define glProgramUniform2uiEXT (*divagl_glProgramUniform2uiEXT)
#define glProgramUniform2uivEXT (*divagl_glProgramUniform2uivEXT)
#define glProgramUniform3fEXT (*divagl_glProgramUniform3fEXT)
#define glProgramUniform3fvEXT (*divagl_glProgramUniform3fvEXT)
#define glProgramUniform3iEXT (*divagl_glProgramUniform3iEXT)
#define glProgramUniform3ivEXT (*divagl_glProgramUniform3ivEXT)
#define glProgramUniform3uiEXT (*divagl_glProgramUniform3uiEXT)
#define glProgramUniform3uivEXT (*divagl_glProgramUniform3uivEXT)
#define glProgramUniform4fEXT (*divagl_glProgramUniform4fEXT)
#define glProgramUniform4fvEXT (*divagl_glProgramUniform4fvEXT)
#define glProgramUniform4iEXT (*divagl_glProgramUniform4iEXT)
#define glProgramUniform4ivEXT (*divagl_glProgramUniform4ivEXT)
#define glProgramUniform4uiEXT (*divagl_glProgramUniform4uiEXT)
#define glProgramUniform4uivEXT (*divagl_glProgramUniform4uivEXT)
#define glProgramUniformMatrix2fvEXT (*divagl_glProgramUniformMatrix2fvEXT)
#define glProgramUniformMatrix2x3fvEXT (*divagl_glProgramUniformMatrix2x3fvEXT)
#define glProgramUniformMatrix2x4fvEXT (*divagl_glProgramUniformMatrix2x4fvEXT)
#define glProgramUniformMatrix3fvEXT (*divagl_glProgramUniformMatrix3fvEXT)
#define glProgramUniformMatrix3x2fvEXT (*divagl_glProgramUniformMatrix3x2fvEXT)
#define glProgramUniformMatrix3x4fvEXT (*divagl_glProgramUniformMatrix3x4fvEXT)
#define glProgramUniformMatrix4fvEXT (*divagl_glProgramUniformMatrix4fvEXT)
#define glProgramUniformMatrix4x2fvEXT (*divagl_glProgramUniformMatrix4x2fvEXT)
#define glProgramUniformMatrix4x3fvEXT (*divagl_glProgramUniformMatrix4x3fvEXT)
#define glProgramVertexLimitNV (*divagl_glProgramVertexLimitNV)
#define glPushClientAttribDefaultEXT (*divagl_glPushClientAttribDefaultEXT)
#define glQueryCounter (*divagl_glQueryCounter)
#define glRenderbufferStorage (*divagl_glRenderbufferStorage)
#define glRenderbufferStorageMultisample (*divagl_glRenderbufferStorageMultisample)
#define glRenderbufferStorageMultisampleEXT (*divagl_glRenderbufferStorageMultisampleEXT)
#define glRequestResidentProgramsNV (*divagl_glRequestResidentProgramsNV)
#define glResetHistogram (*divagl_glResetHistogram)
#define glResetMinmax (*divagl_glResetMinmax)
#define glSampleCoverage (*divagl_glSampleCoverage)
#define glSampleCoverageARB (*divagl_glSampleCoverageARB)
#define glSampleMaskIndexedNV (*divagl_glSampleMaskIndexedNV)
#define glSamplerParameterf (*divagl_glSamplerParameterf)
#define glSamplerParameterfv (*divagl_glSamplerParameterfv)
#define glSamplerParameteri (*divagl_glSamplerParameteri)
#define glSecondaryColor3b (*divagl_glSecondaryColor3b)
#define glSecondaryColor3bEXT (*divagl_glSecondaryColor3bEXT)
#define glSecondaryColor3bv (*divagl_glSecondaryColor3bv)
#define glSecondaryColor3bvEXT (*divagl_glSecondaryColor3bvEXT)
#define glSecondaryColor3d (*divagl_glSecondaryColor3d)
#define glSecondaryColor3dEXT (*divagl_glSecondaryColor3dEXT)
#define glSecondaryColor3dv (*divagl_glSecondaryColor3dv)
#define glSecondaryColor3dvEXT (*divagl_glSecondaryColor3dvEXT)
#define glSecondaryColor3f (*divagl_glSecondaryColor3f)
#define glSecondaryColor3fEXT (*divagl_glSecondaryColor3fEXT)
#define glSecondaryColor3fv (*divagl_glSecondaryColor3fv)
#define glSecondaryColor3fvEXT (*divagl_glSecondaryColor3fvEXT)
#define glSecondaryColor3hNV (*divagl_glSecondaryColor3hNV)
#define glSecondaryColor3hvNV (*divagl_glSecondaryColor3hvNV)
#define glSecondaryColor3i (*divagl_glSecondaryColor3i)
#define glSecondaryColor3iEXT (*divagl_glSecondaryColor3iEXT)
#define glSecondaryColor3iv (*divagl_glSecondaryColor3iv)
#define glSecondaryColor3ivEXT (*divagl_glSecondaryColor3ivEXT)
#define glSecondaryColor3s (*divagl_glSecondaryColor3s)
#define glSecondaryColor3sEXT (*divagl_glSecondaryColor3sEXT)
#define glSecondaryColor3sv (*divagl_glSecondaryColor3sv)
#define glSecondaryColor3svEXT (*divagl_glSecondaryColor3svEXT)
#define glSecondaryColor3ub (*divagl_glSecondaryColor3ub)
#define glSecondaryColor3ubEXT (*divagl_glSecondaryColor3ubEXT)
#define glSecondaryColor3ubv (*divagl_glSecondaryColor3ubv)
#define glSecondaryColor3ubvEXT (*divagl_glSecondaryColor3ubvEXT)
#define glSecondaryColor3ui (*divagl_glSecondaryColor3ui)
#define glSecondaryColor3uiEXT (*divagl_glSecondaryColor3uiEXT)
#define glSecondaryColor3uiv (*divagl_glSecondaryColor3uiv)
#define glSecondaryColor3uivEXT (*divagl_glSecondaryColor3uivEXT)
#define glSecondaryColor3us (*divagl_glSecondaryColor3us)
#define glSecondaryColor3usEXT (*divagl_glSecondaryColor3usEXT)
#define glSecondaryColor3usv (*divagl_glSecondaryColor3usv)
#define glSecondaryColor3usvEXT (*divagl_glSecondaryColor3usvEXT)
#define glSecondaryColorPointer (*divagl_glSecondaryColorPointer)
#define glSecondaryColorPointerEXT (*divagl_glSecondaryColorPointerEXT)
#define glSeparableFilter2D (*divagl_glSeparableFilter2D)
#define glSetFenceNV (*divagl_glSetFenceNV)
#define glShaderSource (*divagl_glShaderSource)
#define glShaderSourceARB (*divagl_glShaderSourceARB)
#define glStencilFuncSeparate (*divagl_glStencilFuncSeparate)
#define glStencilMaskSeparate (*divagl_glStencilMaskSeparate)
#define glStencilOpSeparate (*divagl_glStencilOpSeparate)
#define glTestFenceNV (*divagl_glTestFenceNV)
#define glTexBufferARB (*divagl_glTexBufferARB)
#define glTexBufferEXT (*divagl_glTexBufferEXT)
#define glTexCoord1hNV (*divagl_glTexCoord1hNV)
#define glTexCoord1hvNV (*divagl_glTexCoord1hvNV)
#define glTexCoord2hNV (*divagl_glTexCoord2hNV)
#define glTexCoord2hvNV (*divagl_glTexCoord2hvNV)
#define glTexCoord3hNV (*divagl_glTexCoord3hNV)
#define glTexCoord3hvNV (*divagl_glTexCoord3hvNV)
#define glTexCoord4hNV (*divagl_glTexCoord4hNV)
#define glTexCoord4hvNV (*divagl_glTexCoord4hvNV)
#define glTexCoordPointerEXT (*divagl_glTexCoordPointerEXT)
#define glTexImage3D (*divagl_glTexImage3D)
#define glTexImage3DEXT (*divagl_glTexImage3DEXT)
#define glTexParameterIiv (*divagl_glTexParameterIiv)
#define glTexParameterIivEXT (*divagl_glTexParameterIivEXT)
#define glTexParameterIuiv (*divagl_glTexParameterIuiv)
#define glTexParameterIuivEXT (*divagl_glTexParameterIuivEXT)
#define glTexRenderbufferNV (*divagl_glTexRenderbufferNV)
#define glTexStorage2D (*divagl_glTexStorage2D)
#define glTexSubImage3D (*divagl_glTexSubImage3D)
#define glTexSubImage3DEXT (*divagl_glTexSubImage3DEXT)
#define glTextureBarrierNV (*divagl_glTextureBarrierNV)
#define glTextureBufferEXT (*divagl_glTextureBufferEXT)
#define glTextureImage1DEXT (*divagl_glTextureImage1DEXT)
#define glTextureImage2DEXT (*divagl_glTextureImage2DEXT)
#define glTextureImage3DEXT (*divagl_glTextureImage3DEXT)
#define glTextureParameterfEXT (*divagl_glTextureParameterfEXT)
#define glTextureParameterfvEXT (*divagl_glTextureParameterfvEXT)
#define glTextureParameteriEXT (*divagl_glTextureParameteriEXT)
#define glTextureParameterIivEXT (*divagl_glTextureParameterIivEXT)
#define glTextureParameterIuivEXT (*divagl_glTextureParameterIuivEXT)
#define glTextureParameterivEXT (*divagl_glTextureParameterivEXT)
#define glTextureRenderbufferEXT (*divagl_glTextureRenderbufferEXT)
#define glTextureStorage2DEXT (*divagl_glTextureStorage2DEXT)
#define glTextureSubImage1DEXT (*divagl_glTextureSubImage1DEXT)
#define glTextureSubImage2DEXT (*divagl_glTextureSubImage2DEXT)
#define glTextureSubImage3DEXT (*divagl_glTextureSubImage3DEXT)
#define glTrackMatrixNV (*divagl_glTrackMatrixNV)
#define glTransformFeedbackAttribsNV (*divagl_glTransformFeedbackAttribsNV)
#define glTransformFeedbackVaryings (*divagl_glTransformFeedbackVaryings)
#define glTransformFeedbackVaryingsNV (*divagl_glTransformFeedbackVaryingsNV)
#define glUniform1f (*divagl_glUniform1f)
#define glUniform1fARB (*divagl_glUniform1fARB)
#define glUniform1fv (*divagl_glUniform1fv)
#define glUniform1fvARB (*divagl_glUniform1fvARB)
#define glUniform1i (*divagl_glUniform1i)
#define glUniform1iARB (*divagl_glUniform1iARB)
#define glUniform1iv (*divagl_glUniform1iv)
#define glUniform1ivARB (*divagl_glUniform1ivARB)
#define glUniform1ui (*divagl_glUniform1ui)
#define glUniform1uiEXT (*divagl_glUniform1uiEXT)
#define glUniform1uiv (*divagl_glUniform1uiv)
#define glUniform1uivEXT (*divagl_glUniform1uivEXT)
#define glUniform2f (*divagl_glUniform2f)
#define glUniform2fARB (*divagl_glUniform2fARB)
#define glUniform2fv (*divagl_glUniform2fv)
#define glUniform2fvARB (*divagl_glUniform2fvARB)
#define glUniform2i (*divagl_glUniform2i)
#define glUniform2iARB (*divagl_glUniform2iARB)
#define glUniform2iv (*divagl_glUniform2iv)
#define glUniform2ivARB (*divagl_glUniform2ivARB)
#define glUniform2ui (*divagl_glUniform2ui)
#define glUniform2uiEXT (*divagl_glUniform2uiEXT)
#define glUniform2uiv (*divagl_glUniform2uiv)
#define glUniform2uivEXT (*divagl_glUniform2uivEXT)
#define glUniform3f (*divagl_glUniform3f)
#define glUniform3fARB (*divagl_glUniform3fARB)
#define glUniform3fv (*divagl_glUniform3fv)
#define glUniform3fvARB (*divagl_glUniform3fvARB)
#define glUniform3i (*divagl_glUniform3i)
#define glUniform3iARB (*divagl_glUniform3iARB)
#define glUniform3iv (*divagl_glUniform3iv)
#define glUniform3ivARB (*divagl_glUniform3ivARB)
#define glUniform3ui (*divagl_glUniform3ui)
#define glUniform3uiEXT (*divagl_glUniform3uiEXT)
#define glUniform3uiv (*divagl_glUniform3uiv)
#define glUniform3uivEXT (*divagl_glUniform3uivEXT)
#define glUniform4f (*divagl_glUniform4f)
#define glUniform4fARB (*divagl_glUniform4fARB)
#define glUniform4fv (*divagl_glUniform4fv)
#define glUniform4fvARB (*divagl_glUniform4fvARB)
#define glUniform4i (*divagl_glUniform4i)
#define glUniform4iARB (*divagl_glUniform4iARB)
#define glUniform4iv (*divagl_glUniform4iv)
#define glUniform4ivARB (*divagl_glUniform4ivARB)
#define glUniform4ui (*divagl_glUniform4ui)
#define glUniform4uiEXT (*divagl_glUniform4uiEXT)
#define glUniform4uiv (*divagl_glUniform4uiv)
#define glUniform4uivEXT (*divagl_glUniform4uivEXT)
#define glUniformBufferEXT (*divagl_glUniformBufferEXT)
#define glUniformMatrix2fv (*divagl_glUniformMatrix2fv)
#define glUniformMatrix2fvARB (*divagl_glUniformMatrix2fvARB)
#define glUniformMatrix2x3fv (*divagl_glUniformMatrix2x3fv)
#define glUniformMatrix2x4fv (*divagl_glUniformMatrix2x4fv)
#define glUniformMatrix3fv (*divagl_glUniformMatrix3fv)
#define glUniformMatrix3fvARB (*divagl_glUniformMatrix3fvARB)
#define glUniformMatrix3x2fv (*divagl_glUniformMatrix3x2fv)
#define glUniformMatrix3x4fv (*divagl_glUniformMatrix3x4fv)
#define glUniformMatrix4fv (*divagl_glUniformMatrix4fv)
#define glUniformMatrix4fvARB (*divagl_glUniformMatrix4fvARB)
#define glUniformMatrix4x2fv (*divagl_glUniformMatrix4x2fv)
#define glUniformMatrix4x3fv (*divagl_glUniformMatrix4x3fv)
#define glUnlockArraysEXT (*divagl_glUnlockArraysEXT)
#define glUnmapBuffer (*divagl_glUnmapBuffer)
#define glUnmapBufferARB (*divagl_glUnmapBufferARB)
#define glUseProgram (*divagl_glUseProgram)
#define glUseProgramObjectARB (*divagl_glUseProgramObjectARB)
#define glValidateProgram (*divagl_glValidateProgram)
#define glValidateProgramARB (*divagl_glValidateProgramARB)
#define glVertex2hNV (*divagl_glVertex2hNV)
#define glVertex2hvNV (*divagl_glVertex2hvNV)
#define glVertex3hNV (*divagl_glVertex3hNV)
#define glVertex3hvNV (*divagl_glVertex3hvNV)
#define glVertex4hNV (*divagl_glVertex4hNV)
#define glVertex4hvNV (*divagl_glVertex4hvNV)
#define glVertexArrayRangeNV (*divagl_glVertexArrayRangeNV)
#define glVertexAttrib1d (*divagl_glVertexAttrib1d)
#define glVertexAttrib1dARB (*divagl_glVertexAttrib1dARB)
#define glVertexAttrib1dNV (*divagl_glVertexAttrib1dNV)
#define glVertexAttrib1dv (*divagl_glVertexAttrib1dv)
#define glVertexAttrib1dvARB (*divagl_glVertexAttrib1dvARB)
#define glVertexAttrib1dvNV (*divagl_glVertexAttrib1dvNV)
#define glVertexAttrib1f (*divagl_glVertexAttrib1f)
#define glVertexAttrib1fARB (*divagl_glVertexAttrib1fARB)
#define glVertexAttrib1fNV (*divagl_glVertexAttrib1fNV)
#define glVertexAttrib1fv (*divagl_glVertexAttrib1fv)
#define glVertexAttrib1fvARB (*divagl_glVertexAttrib1fvARB)
#define glVertexAttrib1fvNV (*divagl_glVertexAttrib1fvNV)
#define glVertexAttrib1hNV (*divagl_glVertexAttrib1hNV)
#define glVertexAttrib1hvNV (*divagl_glVertexAttrib1hvNV)
#define glVertexAttrib1s (*divagl_glVertexAttrib1s)
#define glVertexAttrib1sARB (*divagl_glVertexAttrib1sARB)
#define glVertexAttrib1sNV (*divagl_glVertexAttrib1sNV)
#define glVertexAttrib1sv (*divagl_glVertexAttrib1sv)
#define glVertexAttrib1svARB (*divagl_glVertexAttrib1svARB)
#define glVertexAttrib1svNV (*divagl_glVertexAttrib1svNV)
#define glVertexAttrib2d (*divagl_glVertexAttrib2d)
#define glVertexAttrib2dARB (*divagl_glVertexAttrib2dARB)
#define glVertexAttrib2dNV (*divagl_glVertexAttrib2dNV)
#define glVertexAttrib2dv (*divagl_glVertexAttrib2dv)
#define glVertexAttrib2dvARB (*divagl_glVertexAttrib2dvARB)
#define glVertexAttrib2dvNV (*divagl_glVertexAttrib2dvNV)
#define glVertexAttrib2f (*divagl_glVertexAttrib2f)
#define glVertexAttrib2fARB (*divagl_glVertexAttrib2fARB)
#define glVertexAttrib2fNV (*divagl_glVertexAttrib2fNV)
#define glVertexAttrib2fv (*divagl_glVertexAttrib2fv)
#define glVertexAttrib2fvARB (*divagl_glVertexAttrib2fvARB)
#define glVertexAttrib2fvNV (*divagl_glVertexAttrib2fvNV)
#define glVertexAttrib2hNV (*divagl_glVertexAttrib2hNV)
#define glVertexAttrib2hvNV (*divagl_glVertexAttrib2hvNV)
#define glVertexAttrib2s (*divagl_glVertexAttrib2s)
#define glVertexAttrib2sARB (*divagl_glVertexAttrib2sARB)
#define glVertexAttrib2sNV (*divagl_glVertexAttrib2sNV)
#define glVertexAttrib2sv (*divagl_glVertexAttrib2sv)
#define glVertexAttrib2svARB (*divagl_glVertexAttrib2svARB)
#define glVertexAttrib2svNV (*divagl_glVertexAttrib2svNV)
#define glVertexAttrib3d (*divagl_glVertexAttrib3d)
#define glVertexAttrib3dARB (*divagl_glVertexAttrib3dARB)
#define glVertexAttrib3dNV (*divagl_glVertexAttrib3dNV)
#define glVertexAttrib3dv (*divagl_glVertexAttrib3dv)
#define glVertexAttrib3dvARB (*divagl_glVertexAttrib3dvARB)
#define glVertexAttrib3dvNV (*divagl_glVertexAttrib3dvNV)
#define glVertexAttrib3f (*divagl_glVertexAttrib3f)
#define glVertexAttrib3fARB (*divagl_glVertexAttrib3fARB)
#define glVertexAttrib3fNV (*divagl_glVertexAttrib3fNV)
#define glVertexAttrib3fv (*divagl_glVertexAttrib3fv)
#define glVertexAttrib3fvARB (*divagl_glVertexAttrib3fvARB)
#define glVertexAttrib3fvNV (*divagl_glVertexAttrib3fvNV)
#define glVertexAttrib3hNV (*divagl_glVertexAttrib3hNV)
#define glVertexAttrib3hvNV (*divagl_glVertexAttrib3hvNV)
#define glVertexAttrib3s (*divagl_glVertexAttrib3s)
#define glVertexAttrib3sARB (*divagl_glVertexAttrib3sARB)
#define glVertexAttrib3sNV (*divagl_glVertexAttrib3sNV)
#define glVertexAttrib3sv (*divagl_glVertexAttrib3sv)
#define glVertexAttrib3svARB (*divagl_glVertexAttrib3svARB)
#define glVertexAttrib3svNV (*divagl_glVertexAttrib3svNV)
#define glVertexAttrib4bv (*divagl_glVertexAttrib4bv)
#define glVertexAttrib4bvARB (*divagl_glVertexAttrib4bvARB)
#define glVertexAttrib4d (*divagl_glVertexAttrib4d)
#define glVertexAttrib4dARB (*divagl_glVertexAttrib4dARB)
#define glVertexAttrib4dNV (*divagl_glVertexAttrib4dNV)
#define glVertexAttrib4dv (*divagl_glVertexAttrib4dv)
#define glVertexAttrib4dvARB (*divagl_glVertexAttrib4dvARB)
#define glVertexAttrib4dvNV (*divagl_glVertexAttrib4dvNV)
#define glVertexAttrib4f (*divagl_glVertexAttrib4f)
#define glVertexAttrib4fARB (*divagl_glVertexAttrib4fARB)
#define glVertexAttrib4fNV (*divagl_glVertexAttrib4fNV)
#define glVertexAttrib4fv (*divagl_glVertexAttrib4fv)
#define glVertexAttrib4fvARB (*divagl_glVertexAttrib4fvARB)
#define glVertexAttrib4fvNV (*divagl_glVertexAttrib4fvNV)
#define glVertexAttrib4hNV (*divagl_glVertexAttrib4hNV)
#define glVertexAttrib4hvNV (*divagl_glVertexAttrib4hvNV)
#define glVertexAttrib4iv (*divagl_glVertexAttrib4iv)
#define glVertexAttrib4ivARB (*divagl_glVertexAttrib4ivARB)
#define glVertexAttrib4Nbv (*divagl_glVertexAttrib4Nbv)
#define glVertexAttrib4NbvARB (*divagl_glVertexAttrib4NbvARB)
#define glVertexAttrib4Niv (*divagl_glVertexAttrib4Niv)
#define glVertexAttrib4NivARB (*divagl_glVertexAttrib4NivARB)
#define glVertexAttrib4Nsv (*divagl_glVertexAttrib4Nsv)
#define glVertexAttrib4NsvARB (*divagl_glVertexAttrib4NsvARB)
#define glVertexAttrib4Nub (*divagl_glVertexAttrib4Nub)
#define glVertexAttrib4NubARB (*divagl_glVertexAttrib4NubARB)
#define glVertexAttrib4Nubv (*divagl_glVertexAttrib4Nubv)
#define glVertexAttrib4NubvARB (*divagl_glVertexAttrib4NubvARB)
#define glVertexAttrib4Nuiv (*divagl_glVertexAttrib4Nuiv)
#define glVertexAttrib4NuivARB (*divagl_glVertexAttrib4NuivARB)
#define glVertexAttrib4Nusv (*divagl_glVertexAttrib4Nusv)
#define glVertexAttrib4NusvARB (*divagl_glVertexAttrib4NusvARB)
#define glVertexAttrib4s (*divagl_glVertexAttrib4s)
#define glVertexAttrib4sARB (*divagl_glVertexAttrib4sARB)
#define glVertexAttrib4sNV (*divagl_glVertexAttrib4sNV)
#define glVertexAttrib4sv (*divagl_glVertexAttrib4sv)
#define glVertexAttrib4svARB (*divagl_glVertexAttrib4svARB)
#define glVertexAttrib4svNV (*divagl_glVertexAttrib4svNV)
#define glVertexAttrib4ubNV (*divagl_glVertexAttrib4ubNV)
#define glVertexAttrib4ubv (*divagl_glVertexAttrib4ubv)
#define glVertexAttrib4ubvARB (*divagl_glVertexAttrib4ubvARB)
#define glVertexAttrib4ubvNV (*divagl_glVertexAttrib4ubvNV)
#define glVertexAttrib4uiv (*divagl_glVertexAttrib4uiv)
#define glVertexAttrib4uivARB (*divagl_glVertexAttrib4uivARB)
#define glVertexAttrib4usv (*divagl_glVertexAttrib4usv)
#define glVertexAttrib4usvARB (*divagl_glVertexAttrib4usvARB)
#define glVertexAttribI1i (*divagl_glVertexAttribI1i)
#define glVertexAttribI1iEXT (*divagl_glVertexAttribI1iEXT)
#define glVertexAttribI1iv (*divagl_glVertexAttribI1iv)
#define glVertexAttribI1ivEXT (*divagl_glVertexAttribI1ivEXT)
#define glVertexAttribI1ui (*divagl_glVertexAttribI1ui)
#define glVertexAttribI1uiEXT (*divagl_glVertexAttribI1uiEXT)
#define glVertexAttribI1uiv (*divagl_glVertexAttribI1uiv)
#define glVertexAttribI1uivEXT (*divagl_glVertexAttribI1uivEXT)
#define glVertexAttribI2i (*divagl_glVertexAttribI2i)
#define glVertexAttribI2iEXT (*divagl_glVertexAttribI2iEXT)
#define glVertexAttribI2iv (*divagl_glVertexAttribI2iv)
#define glVertexAttribI2ivEXT (*divagl_glVertexAttribI2ivEXT)
#define glVertexAttribI2ui (*divagl_glVertexAttribI2ui)
#define glVertexAttribI2uiEXT (*divagl_glVertexAttribI2uiEXT)
#define glVertexAttribI2uiv (*divagl_glVertexAttribI2uiv)
#define glVertexAttribI2uivEXT (*divagl_glVertexAttribI2uivEXT)
#define glVertexAttribI3i (*divagl_glVertexAttribI3i)
#define glVertexAttribI3iEXT (*divagl_glVertexAttribI3iEXT)
#define glVertexAttribI3iv (*divagl_glVertexAttribI3iv)
#define glVertexAttribI3ivEXT (*divagl_glVertexAttribI3ivEXT)
#define glVertexAttribI3ui (*divagl_glVertexAttribI3ui)
#define glVertexAttribI3uiEXT (*divagl_glVertexAttribI3uiEXT)
#define glVertexAttribI3uiv (*divagl_glVertexAttribI3uiv)
#define glVertexAttribI3uivEXT (*divagl_glVertexAttribI3uivEXT)
#define glVertexAttribI4bv (*divagl_glVertexAttribI4bv)
#define glVertexAttribI4bvEXT (*divagl_glVertexAttribI4bvEXT)
#define glVertexAttribI4i (*divagl_glVertexAttribI4i)
#define glVertexAttribI4iEXT (*divagl_glVertexAttribI4iEXT)
#define glVertexAttribI4iv (*divagl_glVertexAttribI4iv)
#define glVertexAttribI4ivEXT (*divagl_glVertexAttribI4ivEXT)
#define glVertexAttribI4sv (*divagl_glVertexAttribI4sv)
#define glVertexAttribI4svEXT (*divagl_glVertexAttribI4svEXT)
#define glVertexAttribI4ubv (*divagl_glVertexAttribI4ubv)
#define glVertexAttribI4ubvEXT (*divagl_glVertexAttribI4ubvEXT)
#define glVertexAttribI4ui (*divagl_glVertexAttribI4ui)
#define glVertexAttribI4uiEXT (*divagl_glVertexAttribI4uiEXT)
#define glVertexAttribI4uiv (*divagl_glVertexAttribI4uiv)
#define glVertexAttribI4uivEXT (*divagl_glVertexAttribI4uivEXT)
#define glVertexAttribI4usv (*divagl_glVertexAttribI4usv)
#define glVertexAttribI4usvEXT (*divagl_glVertexAttribI4usvEXT)
#define glVertexAttribIPointer (*divagl_glVertexAttribIPointer)
#define glVertexAttribIPointerEXT (*divagl_glVertexAttribIPointerEXT)
#define glVertexAttribPointer (*divagl_glVertexAttribPointer)
#define glVertexAttribPointerNV (*divagl_glVertexAttribPointerNV)
#define glVertexAttribs1dvNV (*divagl_glVertexAttribs1dvNV)
#define glVertexAttribs1fvNV (*divagl_glVertexAttribs1fvNV)
#define glVertexAttribs1hvNV (*divagl_glVertexAttribs1hvNV)
#define glVertexAttribs1svNV (*divagl_glVertexAttribs1svNV)
#define glVertexAttribs2dvNV (*divagl_glVertexAttribs2dvNV)
#define glVertexAttribs2fvNV (*divagl_glVertexAttribs2fvNV)
#define glVertexAttribs2hvNV (*divagl_glVertexAttribs2hvNV)
#define glVertexAttribs2svNV (*divagl_glVertexAttribs2svNV)
#define glVertexAttribs3dvNV (*divagl_glVertexAttribs3dvNV)
#define glVertexAttribs3fvNV (*divagl_glVertexAttribs3fvNV)
#define glVertexAttribs3hvNV (*divagl_glVertexAttribs3hvNV)
#define glVertexAttribs3svNV (*divagl_glVertexAttribs3svNV)
#define glVertexAttribs4dvNV (*divagl_glVertexAttribs4dvNV)
#define glVertexAttribs4fvNV (*divagl_glVertexAttribs4fvNV)
#define glVertexAttribs4hvNV (*divagl_glVertexAttribs4hvNV)
#define glVertexAttribs4svNV (*divagl_glVertexAttribs4svNV)
#define glVertexAttribs4ubvNV (*divagl_glVertexAttribs4ubvNV)
#define glVertexPointerEXT (*divagl_glVertexPointerEXT)
#define glWindowPos2d (*divagl_glWindowPos2d)
#define glWindowPos2dARB (*divagl_glWindowPos2dARB)
#define glWindowPos2dv (*divagl_glWindowPos2dv)
#define glWindowPos2dvARB (*divagl_glWindowPos2dvARB)
#define glWindowPos2f (*divagl_glWindowPos2f)
#define glWindowPos2fARB (*divagl_glWindowPos2fARB)
#define glWindowPos2fv (*divagl_glWindowPos2fv)
#define glWindowPos2fvARB (*divagl_glWindowPos2fvARB)
#define glWindowPos2i (*divagl_glWindowPos2i)
#define glWindowPos2iARB (*divagl_glWindowPos2iARB)
#define glWindowPos2iv (*divagl_glWindowPos2iv)
#define glWindowPos2ivARB (*divagl_glWindowPos2ivARB)
#define glWindowPos2s (*divagl_glWindowPos2s)
#define glWindowPos2sARB (*divagl_glWindowPos2sARB)
#define glWindowPos2sv (*divagl_glWindowPos2sv)
#define glWindowPos2svARB (*divagl_glWindowPos2svARB)
#define glWindowPos3d (*divagl_glWindowPos3d)
#define glWindowPos3dARB (*divagl_glWindowPos3dARB)
#define glWindowPos3dv (*divagl_glWindowPos3dv)
#define glWindowPos3dvARB (*divagl_glWindowPos3dvARB)
#define glWindowPos3f (*divagl_glWindowPos3f)
#define glWindowPos3fARB (*divagl_glWindowPos3fARB)
#define glWindowPos3fv (*divagl_glWindowPos3fv)
#define glWindowPos3fvARB (*divagl_glWindowPos3fvARB)
#define glWindowPos3i (*divagl_glWindowPos3i)
#define glWindowPos3iARB (*divagl_glWindowPos3iARB)
#define glWindowPos3iv (*divagl_glWindowPos3iv)
#define glWindowPos3ivARB (*divagl_glWindowPos3ivARB)
#define glWindowPos3s (*divagl_glWindowPos3s)
#define glWindowPos3sARB (*divagl_glWindowPos3sARB)
#define glWindowPos3sv (*divagl_glWindowPos3sv)
#define glWindowPos3svARB (*divagl_glWindowPos3svARB)
#define wglAllocateMemoryNV (*divagl_wglAllocateMemoryNV)
#define wglBindSwapBarrierNV (*divagl_wglBindSwapBarrierNV)
#define wglBindTexImageARB (*divagl_wglBindTexImageARB)
#define wglBindVideoImageNV (*divagl_wglBindVideoImageNV)
#define wglChoosePixelFormatARB (*divagl_wglChoosePixelFormatARB)
#define wglCreateBufferRegionARB (*divagl_wglCreateBufferRegionARB)
#define wglCreateContextAttribsARB (*divagl_wglCreateContextAttribsARB)
#define wglCreatePbufferARB (*divagl_wglCreatePbufferARB)
#define wglDeleteBufferRegionARB (*divagl_wglDeleteBufferRegionARB)
#define wglDestroyPbufferARB (*divagl_wglDestroyPbufferARB)
#define wglDXCloseDeviceNV (*divagl_wglDXCloseDeviceNV)
#define wglDXLockObjectsNV (*divagl_wglDXLockObjectsNV)
#define wglDXOpenDeviceNV (*divagl_wglDXOpenDeviceNV)
#define wglDXRegisterObjectNV (*divagl_wglDXRegisterObjectNV)
#define wglDXSetResourceShareHandleNV (*divagl_wglDXSetResourceShareHandleNV)
#define wglDXUnlockObjectsNV (*divagl_wglDXUnlockObjectsNV)
#define wglDXUnregisterObjectNV (*divagl_wglDXUnregisterObjectNV)
#define wglFreeMemoryNV (*divagl_wglFreeMemoryNV)
#define wglGetCurrentContext (*divagl_wglGetCurrentContext)
#define wglGetCurrentReadDCARB (*divagl_wglGetCurrentReadDCARB)
#define wglGetExtensionsStringARB (*divagl_wglGetExtensionsStringARB)
#define wglGetExtensionsStringEXT (*divagl_wglGetExtensionsStringEXT)
#define wglGetPbufferDCARB (*divagl_wglGetPbufferDCARB)
#define wglGetPixelFormatAttribfvARB (*divagl_wglGetPixelFormatAttribfvARB)
#define wglGetPixelFormatAttribivARB (*divagl_wglGetPixelFormatAttribivARB)
#define wglGetProcAddress (*divagl_wglGetProcAddress)
#define wglGetSwapIntervalEXT (*divagl_wglGetSwapIntervalEXT)
#define wglGetVideoDeviceNV (*divagl_wglGetVideoDeviceNV)
#define wglGetVideoInfoNV (*divagl_wglGetVideoInfoNV)
#define wglJoinSwapGroupNV (*divagl_wglJoinSwapGroupNV)
#define wglMakeContextCurrentARB (*divagl_wglMakeContextCurrentARB)
#define wglQueryFrameCountNV (*divagl_wglQueryFrameCountNV)
#define wglQueryMaxSwapGroupsNV (*divagl_wglQueryMaxSwapGroupsNV)
#define wglQueryPbufferARB (*divagl_wglQueryPbufferARB)
#define wglQuerySwapGroupNV (*divagl_wglQuerySwapGroupNV)
#define wglReleasePbufferDCARB (*divagl_wglReleasePbufferDCARB)
#define wglReleaseTexImageARB (*divagl_wglReleaseTexImageARB)
#define wglReleaseVideoDeviceNV (*divagl_wglReleaseVideoDeviceNV)
#define wglReleaseVideoImageNV (*divagl_wglReleaseVideoImageNV)
#define wglResetFrameCountNV (*divagl_wglResetFrameCountNV)
#define wglRestoreBufferRegionARB (*divagl_wglRestoreBufferRegionARB)
#define wglSaveBufferRegionARB (*divagl_wglSaveBufferRegionARB)
#define wglSendPbufferToVideoNV (*divagl_wglSendPbufferToVideoNV)
#define wglSetPbufferAttribARB (*divagl_wglSetPbufferAttribARB)
#define wglSwapIntervalEXT (*divagl_wglSwapIntervalEXT)

#define glDrawBufferGLUT (*divagl_glDrawBufferGLUT)
#define glEnableGLUT (*divagl_glEnableGLUT)
#define glFinishGLUT (*divagl_glFinishGLUT)
#define glGetErrorGLUT (*divagl_glGetErrorGLUT)
#define glGetIntegervGLUT (*divagl_glGetIntegervGLUT)
#define glGetStringGLUT (*divagl_glGetStringGLUT)
#define glPixelStoreiGLUT (*divagl_glPixelStoreiGLUT)
#define glReadBufferGLUT (*divagl_glReadBufferGLUT)
#define glViewportGLUT (*divagl_glViewportGLUT)
#define wglCreateContextGLUT (*divagl_wglCreateContextGLUT)
#define wglDeleteContextGLUT (*divagl_wglDeleteContextGLUT)
#define wglGetCurrentContextGLUT (*divagl_wglGetCurrentContextGLUT)
#define wglGetCurrentDCGLUT (*divagl_wglGetCurrentDCGLUT)
#define wglGetProcAddressGLUT (*divagl_wglGetProcAddressGLUT)
#define wglMakeCurrentGLUT (*divagl_wglMakeCurrentGLUT)

#define glTexParameteriv divagl_glTexParameteriv
#define glDrawArraysInstanced divagl_glDrawArraysInstanced
#define glPrimitiveRestartIndex divagl_glPrimitiveRestartIndex
#define glGetUniformBlockIndex divagl_glGetUniformBlockIndex
#define glUniformBlockBinding divagl_glUniformBlockBinding
#define glGetInteger64i_v divagl_glGetInteger64i_v
#define glVertexAttribDivisor divagl_glVertexAttribDivisor
#define glClearDepthf divagl_glClearDepthf
#define glGetProgramBinary divagl_glGetProgramBinary
#define glProgramBinary divagl_glProgramBinary
#define glPushDebugGroup divagl_glPushDebugGroup
#define glPopDebugGroup divagl_glPopDebugGroup
#define glBufferStorage divagl_glBufferStorage
#define glCreateBuffers divagl_glCreateBuffers
#define glNamedBufferStorage divagl_glNamedBufferStorage
#define glNamedBufferSubData divagl_glNamedBufferSubData
#define glMapNamedBuffer divagl_glMapNamedBuffer
#define glMapNamedBufferRange divagl_glMapNamedBufferRange
#define glUnmapNamedBuffer divagl_glUnmapNamedBuffer
#define glTextureSubImage2D divagl_glTextureSubImage2D

extern bool GL_VERSION_4_1;
extern bool GL_VERSION_4_2;
extern bool GL_VERSION_4_3;
extern bool GL_VERSION_4_4;
extern bool GL_VERSION_4_5;
extern bool GL_VERSION_4_6;

extern void wrap_addresses();
extern void wrap_patch();

extern void GLAPIENTRY glAlphaFuncDLL(GLenum func, GLfloat ref);
extern void GLAPIENTRY glBeginDLL(GLenum mode);
extern void GLAPIENTRY glColor3fDLL(GLfloat red, GLfloat green, GLfloat blue);
extern void GLAPIENTRY glColor4fDLL(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern void GLAPIENTRY glColor4ubDLL(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
extern void GLAPIENTRY glColor4ubvDLL(GLubyte const * v);
extern void GLAPIENTRY glColorPointerDLL(GLint size, GLenum type, GLsizei stride, const void * pointer);
extern void GLAPIENTRY glDisableClientStateDLL(GLenum array);
extern void GLAPIENTRY glEnableClientStateDLL(GLenum array);
extern void GLAPIENTRY glEndDLL();
extern void GLAPIENTRY glFogfDLL(GLenum pname, GLfloat param);
extern void GLAPIENTRY glFogfvDLL(GLenum pname, GLfloat const * params);
extern void GLAPIENTRY glFogiDLL(GLenum pname, GLint param);
extern void GLAPIENTRY glFrustumDLL(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
extern void GLAPIENTRY glGetMaterialfvDLL(GLenum face, GLenum pname, GLfloat * params);
extern void GLAPIENTRY glGetTexLevelParameterivDLL(GLenum target, GLint level, GLenum pname, GLint * params);
extern void GLAPIENTRY glGetTexParameterivDLL(GLenum target, GLenum pname, GLint * params);
extern void GLAPIENTRY glLightfvDLL(GLenum light, GLenum pname, GLfloat const * params);
extern void GLAPIENTRY glLightModelfvDLL(GLenum pname, GLfloat const * params);
extern void GLAPIENTRY glLineWidthDLL(GLfloat width);
extern void GLAPIENTRY glLoadIdentityDLL();
extern void GLAPIENTRY glLoadMatrixfDLL(GLfloat const * m);
extern void GLAPIENTRY glMaterialfDLL(GLenum face, GLenum pname, GLfloat param);
extern void GLAPIENTRY glMaterialfvDLL(GLenum face, GLenum pname, GLfloat const * params);
extern void GLAPIENTRY glMatrixModeDLL(GLenum mode);
extern void GLAPIENTRY glMultMatrixdDLL(GLdouble const * m);
extern void GLAPIENTRY glNormal3fDLL(GLfloat nx, GLfloat ny, GLfloat nz);
extern void GLAPIENTRY glNormalPointerDLL(GLenum type, GLsizei stride, const void * pointer);
extern void GLAPIENTRY glOrthoDLL(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
extern void GLAPIENTRY glPointSizeDLL(GLfloat size);
extern void GLAPIENTRY glPopAttribDLL();
extern void GLAPIENTRY glPopClientAttribDLL();
extern void GLAPIENTRY glPopMatrixDLL();
extern void GLAPIENTRY glPushAttribDLL(GLbitfield mask);
extern void GLAPIENTRY glPushClientAttribDLL(GLbitfield mask);
extern void GLAPIENTRY glPushMatrixDLL();
extern void GLAPIENTRY glRotatefDLL(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
extern void GLAPIENTRY glScalefDLL(GLfloat x, GLfloat y, GLfloat z);
extern void GLAPIENTRY glShadeModelDLL(GLenum mode);
extern void GLAPIENTRY glTexCoord2fDLL(GLfloat s, GLfloat t);
extern void GLAPIENTRY glTexCoordPointerDLL(GLint size, GLenum type, GLsizei stride, const void * pointer);
extern void GLAPIENTRY glTexEnvfDLL(GLenum target, GLenum pname, GLfloat param);
extern void GLAPIENTRY glTexEnviDLL(GLenum target, GLenum pname, GLint param);
extern void GLAPIENTRY glTranslatefDLL(GLfloat x, GLfloat y, GLfloat z);
extern void GLAPIENTRY glVertex3fDLL(GLfloat x, GLfloat y, GLfloat z);
extern void GLAPIENTRY glVertex3fvDLL(GLfloat const * v);
extern void GLAPIENTRY glVertexPointerDLL(GLint size, GLenum type, GLsizei stride, const void * pointer);

extern void GLAPIENTRY glBindBufferARB(GLenum target, GLuint buffer);
extern void GLAPIENTRY glBindBufferBaseNV(GLenum target, GLuint index, GLuint buffer);
extern void GLAPIENTRY glBindFramebufferEXT(GLenum target, GLuint framebuffer);
extern void GLAPIENTRY glBindMultiTextureEXT(GLenum texunit, GLenum target, GLuint texture);
extern void GLAPIENTRY glBindRenderbufferEXT(GLenum target, GLuint renderbuffer);
extern void GLAPIENTRY glBufferDataARB(GLenum target, GLsizeiptrARB size, const void * data, GLenum usage);
extern void GLAPIENTRY glClampColorARB(GLenum target, GLenum clamp);
extern void GLAPIENTRY glClientActiveTexture(GLenum texture);
extern void GLAPIENTRY glCopyMultiTexSubImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
extern void GLAPIENTRY glDeleteBuffersARB(GLsizei n, GLuint const * buffers);
extern void GLAPIENTRY glDeleteFramebuffersEXT(GLsizei n, GLuint const * framebuffers);
extern void GLAPIENTRY glDeleteRenderbuffersEXT(GLsizei n, GLuint const * renderbuffers);
extern void GLAPIENTRY glDisableVertexAttribArrayARB(GLuint index);
extern void GLAPIENTRY glEnableVertexAttribArrayARB(GLuint index);
extern void GLAPIENTRY glFramebufferRenderbufferEXT(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
extern void GLAPIENTRY glFramebufferTexture2DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
extern void GLAPIENTRY glGenFramebuffersEXT(GLsizei n, GLuint * framebuffers);
extern void GLAPIENTRY glGenRenderbuffersEXT(GLsizei n, GLuint * renderbuffers);
extern void GLAPIENTRY glGetProgramEnvParameterfvARB(GLenum target, GLuint index, GLfloat * params);
extern void GLAPIENTRY glGetProgramivARB(GLenum target, GLenum pname, GLint * params);
extern void GLAPIENTRY glGetTextureImageEXT(GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, void * pixels);
extern GLboolean GLAPIENTRY glIsBufferARB(GLuint buffer);
extern void GLAPIENTRY glLoadTransposeMatrixf(GLfloat const * m);
extern void * GLAPIENTRY glMapNamedBufferEXT(GLuint buffer, GLenum access);
extern void GLAPIENTRY glMultiTexCoord2f(GLenum target, GLfloat s, GLfloat t);
extern void GLAPIENTRY glMultiTexCoord2fv(GLenum target, GLfloat const * v);
extern void GLAPIENTRY glMultTransposeMatrixf(GLfloat const * m);
extern void GLAPIENTRY glNamedBufferDataEXT(GLuint buffer, GLsizeiptr size, const void * data, GLenum usage);
extern void GLAPIENTRY glNamedBufferSubDataEXT(GLuint buffer, GLintptr offset, GLsizeiptr size, const void * data);
extern void GLAPIENTRY glPointParameterf(GLenum pname, GLfloat param);
extern void GLAPIENTRY glPointParameterfv(GLenum pname, GLfloat const * params);
extern void GLAPIENTRY glPointParameteri(GLenum pname, GLint param);
extern void GLAPIENTRY glPrimitiveRestartIndexNV(GLuint index);
extern void GLAPIENTRY glProgramBufferParametersfvNV(GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, GLfloat const * params);
extern void GLAPIENTRY glProgramEnvParameter4fARB(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
extern void GLAPIENTRY glProgramEnvParameter4fvARB(GLenum target, GLuint index, GLfloat const * params);
extern void GLAPIENTRY glProgramEnvParameters4fvEXT(GLenum target, GLuint index, GLsizei count, GLfloat const * params);
extern void GLAPIENTRY glProgramLocalParameter4fARB(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
extern void GLAPIENTRY glProgramLocalParameter4fvARB(GLenum target, GLuint index, GLfloat const * params);
extern void GLAPIENTRY glProgramLocalParameters4fvEXT(GLenum target, GLuint index, GLsizei count, GLfloat const * params);
extern void GLAPIENTRY glRenderbufferStorageEXT(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
extern void GLAPIENTRY glRenderbufferStorageMultisampleCoverageNV(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height);
extern GLboolean GLAPIENTRY glUnmapNamedBufferEXT(GLuint buffer);
extern void GLAPIENTRY glVertexAttribPointerARB(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);

extern void GLAPIENTRY glBeginGLUT(GLenum mode);
extern void GLAPIENTRY glBitmapGLUT(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, GLubyte const * bitmap);
extern void GLAPIENTRY glEndGLUT();
extern void GLAPIENTRY glEvalMesh2GLUT(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
extern void GLAPIENTRY glMap2fGLUT(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, GLfloat const * points);
extern void GLAPIENTRY glMapGrid2fGLUT(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
extern void GLAPIENTRY glNormal3fGLUT(GLfloat nx, GLfloat ny, GLfloat nz);
extern void GLAPIENTRY glNormal3fvGLUT(GLfloat const * v);
extern void GLAPIENTRY glPolygonModeGLUT(GLenum face, GLenum mode);
extern void GLAPIENTRY glPopAttribGLUT();
extern void GLAPIENTRY glPopMatrixGLUT();
extern void GLAPIENTRY glPushAttribGLUT(GLbitfield mask);
extern void GLAPIENTRY glPushMatrixGLUT();
extern void GLAPIENTRY glRotatefGLUT(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
extern void GLAPIENTRY glScalefGLUT(GLfloat x, GLfloat y, GLfloat z);
extern void GLAPIENTRY glTranslatefGLUT(GLfloat x, GLfloat y, GLfloat z);
extern void GLAPIENTRY glVertex2fGLUT(GLfloat x, GLfloat y);
extern void GLAPIENTRY glVertex3fGLUT(GLfloat x, GLfloat y, GLfloat z);
extern void GLAPIENTRY glVertex3fvGLUT(GLfloat const * v);
