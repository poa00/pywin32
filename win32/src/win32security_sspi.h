// Definitions for the win32security sspi support, by Roger Upole
// $Id$

#define SECURITY_WIN32
#include "Security.h"


// SecBuffer objects for SSPI functionality
extern __declspec(dllexport) PyTypeObject PySecBufferType;
extern BOOL PyWinObject_AsSecBuffer(PyObject *, PSecBuffer *, BOOL);
extern PyObject *PyWinObject_FromSecBuffer(PSecBuffer);

extern __declspec(dllexport) PyTypeObject PySecBufferDescType;
extern BOOL PyWinObject_AsSecBufferDesc(PyObject *, PSecBufferDesc *, BOOL);
extern PyObject *PyWinObject_FromSecBufferDesc(PSecBufferDesc);

// PyCtxtHandle object for SSPI support
extern __declspec(dllexport) PyTypeObject PyCtxtHandleType;
extern BOOL PyWinObject_AsCtxtHandle(PyObject *, PCtxtHandle *, BOOL);
extern PyObject *PyWinObject_FromCtxtHandle(PCtxtHandle);

extern __declspec(dllexport) PyTypeObject PyCredHandleType;
extern BOOL PyWinObject_AsCredHandle(PyObject *, PCredHandle *, BOOL);
extern PyObject *PyWinObject_FromCredHandle(PCredHandle);

extern PyObject *PyWinObject_FromSecPkgInfo(PSecPkgInfoW psecpkginfo);
extern PyObject *PyWinObject_FromSecHandle(PSecHandle h);

extern PSecurityFunctionTableW psecurityfunctiontable;
#define CHECK_SECURITYFUNCTIONTABLE(fname)if (psecurityfunctiontable==NULL||psecurityfunctiontable->fname==NULL) return PyErr_Format(PyExc_NotImplementedError,"%s is not available on this platform", #fname);

class PySecBuffer : public PyObject
{
public:
#ifdef _MSC_VER
#pragma warning( disable : 4251 )
#endif // _MSC_VER
	static struct PyMemberDef members[];
	static struct PyMethodDef methods[];
#ifdef _MSC_VER
#pragma warning( default : 4251 )
#endif // _MSC_VER


	PySecBuffer(PSecBuffer psecbuffer);
	PySecBuffer(ULONG cbBuffer, ULONG BufferType);
	~PySecBuffer();
	static void deallocFunc(PyObject *ob);
	static PyObject *getattro(PyObject *self, PyObject *name);
	static int setattro(PyObject *self, PyObject *obname, PyObject *obvalue);
	static PyObject *tp_new(PyTypeObject *, PyObject *, PyObject *);
	static PyObject *Clear(PyObject *self, PyObject *args);

	PSecBuffer GetSecBuffer(void);
	PyObject *obdummy;
	// InitializeSecurityContext and AcceptSecurityContext change the cbBuffer in the structure to reflect
	// bytes used, keep our own allocated size
	unsigned long maxbufsize;
protected:
	SecBuffer secbuffer;
};

class PySecBufferDesc : public PyObject
{
public:
#ifdef _MSC_VER
#pragma warning( disable : 4251 )
#endif // _MSC_VER
	static struct PyMemberDef members[];
	static struct PyMethodDef methods[];
#ifdef _MSC_VER
#pragma warning( default : 4251 )
#endif // _MSC_VER
	// ??? might need this, some protocols will allocate output buffers for you if ISC_REQ_ALLOCATE_MEMORY is specified
	PySecBufferDesc(ULONG ulVersion);
	PySecBufferDesc(PSecBufferDesc psecbufferdesc);
	~PySecBufferDesc();
	static void deallocFunc(PyObject *ob);
	static PyObject *getattro(PyObject *self, PyObject *name);
	static int setattro(PyObject *self, PyObject *obname, PyObject *obvalue);
	static PyObject *tp_new(PyTypeObject *, PyObject *, PyObject *);
	static PySequenceMethods sequencemethods;
	PSecBufferDesc GetSecBufferDesc(void);
	PyObject **obBuffers;
	unsigned long max_buffers;
	static PyObject *append(PyObject *self, PyObject *args);
	void modify_in_place(void);
	
protected:
	SecBufferDesc secbufferdesc;
};


class PyCtxtHandle : public PyObject
{
public:
#ifdef _MSC_VER
#pragma warning( disable : 4251 )
#endif // _MSC_VER
	static struct PyMemberDef members[];
	static struct PyMethodDef methods[];
#ifdef _MSC_VER
#pragma warning( default : 4251 )
#endif // _MSC_VER

	PyCtxtHandle(PCtxtHandle pctxthandle);
	PyCtxtHandle(void);
	~PyCtxtHandle();
	static void deallocFunc(PyObject *ob);
	static PyObject *getattro(PyObject *self, PyObject *name);
	static int setattro(PyObject *self, PyObject *obname, PyObject *obvalue);
	static PyObject *tp_new(PyTypeObject *, PyObject *, PyObject *);
	static PyObject *MakeSignature(PyObject *self, PyObject *args);
	static PyObject *VerifySignature(PyObject *self, PyObject *args);
	static PyObject *EncryptMessage(PyObject *self, PyObject *args);
	static PyObject *DecryptMessage(PyObject *self, PyObject *args);
	static PyObject *Detach(PyObject *self, PyObject *args);
	static PyObject *DeleteSecurityContext(PyObject *self, PyObject *args);
	static PyObject *CompleteAuthToken(PyObject *self, PyObject *args);
	static PyObject *QueryContextAttributes(PyObject *self, PyObject *args);
	static PyObject *QuerySecurityContextToken(PyObject *self, PyObject *args);
	static PyObject *ImpersonateSecurityContext(PyObject *self, PyObject *args);
	static PyObject *RevertSecurityContext(PyObject *self, PyObject *args);
	PCtxtHandle GetCtxtHandle(void);
protected:
	CtxtHandle ctxthandle;
};

class PyCredHandle : public PyObject
{
public:
#ifdef _MSC_VER
#pragma warning( disable : 4251 )
#endif // _MSC_VER
	static struct PyMemberDef members[];
	static struct PyMethodDef methods[];
#ifdef _MSC_VER
#pragma warning( default : 4251 )
#endif // _MSC_VER

	PyCredHandle(PCredHandle);
	PyCredHandle(void);
	~PyCredHandle();
	static void deallocFunc(PyObject *ob);
	static PyObject *getattro(PyObject *self, PyObject *name);
	static int setattro(PyObject *self, PyObject *obname, PyObject *obvalue);
	static PyObject *tp_new(PyTypeObject *, PyObject *, PyObject *);
	static PyObject *Detach(PyObject *self, PyObject *args);
	static PyObject *FreeCredentialsHandle(PyObject *self, PyObject *args);
	static PyObject *QueryCredentialsAttributes(PyObject *self, PyObject *args);
	PCredHandle GetCredHandle(void);
protected:
	CredHandle credhandle;
};