// This file implements the IObjectWithPropertyKey Interface and Gateway for Python.
// Generated by makegw.py

#include "PythonCOM.h"
#include "PythonCOMServer.h"
#include "propsys.h"
#include "PyIObjectWithPropertyKey.h"
#include "PyPROPVARIANT.h"

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyIObjectWithPropertyKey::PyIObjectWithPropertyKey(IUnknown *pdisp):
	PyIUnknown(pdisp)
{
	ob_type = &type;
}

PyIObjectWithPropertyKey::~PyIObjectWithPropertyKey()
{
}

/* static */ IObjectWithPropertyKey *PyIObjectWithPropertyKey::GetI(PyObject *self)
{
	return (IObjectWithPropertyKey *)PyIUnknown::GetI(self);
}

// @pymethod |PyIObjectWithPropertyKey|SetPropertyKey|Sets the property id
PyObject *PyIObjectWithPropertyKey::SetPropertyKey(PyObject *self, PyObject *args)
{
	IObjectWithPropertyKey *pIOWPK = GetI(self);
	if ( pIOWPK == NULL )
		return NULL;
	PROPERTYKEY key;
	// @pyparm <o PyPROPERTYKEY>|key||The identifier of the property
	if ( !PyArg_ParseTuple(args, "O&:SetPropertyKey",
		PyWinObject_AsPROPERTYKEY, &key))
		return NULL;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIOWPK->SetPropertyKey(key);
	PY_INTERFACE_POSTCALL;

	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, pIOWPK, IID_IObjectWithPropertyKey );
	Py_INCREF(Py_None);
	return Py_None;
}

// @pymethod <o PyPROPERTYKEY>|PyIObjectWithPropertyKey|GetPropertyKey|Returns the property id
PyObject *PyIObjectWithPropertyKey::GetPropertyKey(PyObject *self, PyObject *args)
{
	IObjectWithPropertyKey *pIOWPK = GetI(self);
	if ( pIOWPK == NULL )
		return NULL;
	PROPERTYKEY key;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIOWPK->GetPropertyKey(&key);
	PY_INTERFACE_POSTCALL;

	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, pIOWPK, IID_IObjectWithPropertyKey );
	return PyWinObject_FromPROPERTYKEY(key);
}

// @object PyIObjectWithPropertyKey|Interface implemented by objects that have an associated property id
static struct PyMethodDef PyIObjectWithPropertyKey_methods[] =
{
	{ "SetPropertyKey", PyIObjectWithPropertyKey::SetPropertyKey, 1 }, // @pymeth SetPropertyKey|Sets the property id
	{ "GetPropertyKey", PyIObjectWithPropertyKey::GetPropertyKey, METH_NOARGS }, // @pymeth GetPropertyKey|Returns the property id
	{ NULL }
};

PyComTypeObject PyIObjectWithPropertyKey::type("PyIObjectWithPropertyKey",
		&PyIUnknown::type,
		sizeof(PyIObjectWithPropertyKey),
		PyIObjectWithPropertyKey_methods,
		GET_PYCOM_CTOR(PyIObjectWithPropertyKey));