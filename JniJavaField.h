#pragma once
#ifndef JNI_JAVA_FIELD_H
#define JNI_JAVA_FIELD_H

#include <JniForwards.h>
#include <JniJavaEnv.h>
#include <JniJavaObject.h>
#include <JniJavaClass.h>
#include <JniJavaString.h>
#include <JniJavaArray.h>
#include <JniProxy.h>


namespace JNI {

template<typename T>
struct JavaFieldHelper {
	T Get(const JavaField<T>& self) {
		return FromJavaProxy<T>(self.Env(), self.Env().Val()->GetObjectField(self.GetObject().Val(), self.Val())).Val();
	}
	void Set(const JavaField<T>& self, T&& val) {
		self.Env().Val()->SetObjectField(self.GetObject().Val(), self.Val(), ToJavaProxy<T>(self.Env(), std::forward<T>(val)).Val());
	}
};


template<typename T>
class JavaField {
public:
	JavaField() {}
	JavaField(const JavaObject& cls, jfieldID mid) : _obj(cls), val(mid) {}
	JavaField(const JavaField& m) : _obj(m._obj), val(m.val) {}
	JavaField(JavaField&& m) : _obj(m._obj), val(m.val) {
		m._obj = JavaObject();
		m.val = 0;
	}

	JavaField& operator=(const JavaField& m) {
		_obj = m._obj;
		val = m.val;
		return *this;
	}

	JavaField& operator=(JavaField&& m) {
		std::swap(_obj, m._obj);
		std::swap(val, m.val);
		return *this;
	}

	T Get() const {
		return JavaFieldHelper<T>().Get(*this);
	}

	void Set(T&& v) {
		JavaFieldHelper<T>().Set(*this, std::forward<T>(v));
	}

	operator T() const {
		return Get();
	}

	jfieldID Val() const {
		return val;
	}

	JavaEnv Env() const {
		return _obj.Env();
	}

	bool Valid() const {
		return _obj.Valid() &&  val != 0;
	}

	const JavaObject& GetObject() const {
		return _obj;
	}

	JavaClass GetClass() const {
		return GetObject().GetClass();
	}

private:
	JavaObject _obj;
	jfieldID val;
};

template<>
struct JavaFieldHelper<jboolean> {
	typedef jboolean T;
	T Get(const JavaField<T>& self) {
		return self.Env().Val()->GetBooleanField(self.GetObject().Val(), self.Val());
	}
	void Set(const JavaField<T>& self, T&& val) {
		self.Env().Val()->SetBooleanField(self.GetObject().Val(), self.Val(), std::forward<T>(val));
	}
};

template<>
struct JavaFieldHelper<jchar> {
	typedef jchar T;
	T Get(const JavaField<T>& self) {
		return self.Env().Val()->GetCharField(self.GetObject().Val(), self.Val());
	}
	void Set(const JavaField<T>& self, T&& val) {
		self.Env().Val()->SetCharField(self.GetObject().Val(), self.Val(), std::forward<T>(val));
	}
};

template<>
struct JavaFieldHelper<jbyte> {
	typedef jbyte T;
	T Get(const JavaField<T>& self) {
		return self.Env().Val()->GetByteField(self.GetObject().Val(), self.Val());
	}
	void Set(const JavaField<T>& self, T&& val) {
		self.Env().Val()->SetByteField(self.GetObject().Val(), self.Val(), std::forward<T>(val));
	}
};

template<>
struct JavaFieldHelper<jshort> {
	typedef jshort T;
	T Get(const JavaField<T>& self) {
		return self.Env().Val()->GetShortField(self.GetObject().Val(), self.Val());
	}
	void Set(const JavaField<T>& self, T&& val) {
		self.Env().Val()->SetShortField(self.GetObject().Val(), self.Val(), std::forward<T>(val));
	}
};

template<>
struct JavaFieldHelper<jint> {
	typedef jint T;
	T Get(const JavaField<T>& self) {
		return self.Env().Val()->GetIntField(self.GetObject().Val(), self.Val());
	}
	void Set(const JavaField<T>& self, T&& val) {
		self.Env().Val()->SetIntField(self.GetObject().Val(), self.Val(), std::forward<T>(val));
	}
};

// template<>
// struct JavaFieldHelper<TestJniInt> {
// 	typedef TestJniInt T;
// 	T Get(const JavaField<T>& self) {
// 		return FromJavaProxy<T>(self.Env(), self.Env().Val()->GetIntField(self.GetObject().Val(), self.Val())).Val();
// 	}
// 	void Set(const JavaField<T>& self, T&& val) {
// 		self.Env().Val()->SetIntField(self.GetObject().Val(), self.Val(), ToJavaProxy<T>(self.Env(), std::forward<T>(val)).Val());
// 	}
// };

template<>
struct JavaFieldHelper<jlong> {
	typedef jlong T;
	T Get(const JavaField<T>& self) {
		return self.Env().Val()->GetLongField(self.GetObject().Val(), self.Val());
	}
	void Set(const JavaField<T>& self, T&& val) {
		self.Env().Val()->SetLongField(self.GetObject().Val(), self.Val(), std::forward<T>(val));
	}
};

template<>
struct JavaFieldHelper<jfloat> {
	typedef jfloat T;
	T Get(const JavaField<T>& self) {
		return self.Env().Val()->GetFloatField(self.GetObject().Val(), self.Val());
	}
	void Set(const JavaField<T>& self, T&& val) {
		self.Env().Val()->SetFloatField(self.GetObject().Val(), self.Val(), std::forward<T>(val));
	}
};

template<>
struct JavaFieldHelper<jdouble> {
	typedef jdouble T;
	T Get(const JavaField<T>& self) {
		return self.Env().Val()->GetDoubleField(self.GetObject().Val(), self.Val());
	}
	void Set(const JavaField<T>& self, T&& val) {
		self.Env().Val()->SetDoubleField(self.GetObject().Val(), self.Val(), std::forward<T>(val));
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
struct JavaStaticFieldHelper {
	T Get(const JavaStaticField<T>& self) {
		return FromJavaProxy<T>(self.Env(), self.Env().Val()->GetStaticObjectField(self.GetClass().Val(), self.Val())).Val();
	}
	void Set(const JavaStaticField<T>& self, T&& val) {
		self.Env().Val()->SetStaticObjectField(self.GetClass().Val(), self.Val(), ToJavaProxy<T>(self.Env(), std::forward<T>(val)).Val());
	}
};


template<typename T>
class JavaStaticField {
public:
	JavaStaticField() {}
	JavaStaticField(const JavaClass& cls, jfieldID mid) : _cls(cls), val(mid) {}
	JavaStaticField(const JavaStaticField& m) : _cls(m._cls), val(m.val) {}
	JavaStaticField(JavaStaticField&& m) : _cls(m._cls), val(m.val) {
		m._cls = JavaClass();
		m.val = 0;
	}

	JavaStaticField& operator=(const JavaStaticField& m) {
		_cls = m._cls;
		val = m.val;
		return *this;
	}

	JavaStaticField& operator=(JavaStaticField&& m) {
		std::swap(_cls, m._cls);
		std::swap(val, m.val);
		return *this;
	}

	T Get() const {
		return JavaStaticFieldHelper<T>().Get(*this);
	}

	void Set(T&& v) {
		JavaStaticFieldHelper<T>().Set(*this, std::forward<T>(v));
	}

	operator T() const {
		return Get();
	}

	jfieldID Val() const {
		return val;
	}

	bool Valid() const {
		return _cls.Valid() &&  val != 0;
	}

	const JavaClass& GetClass() const {
		return _cls;
	}

	JavaEnv Env() const {
		return _cls.Env();
	}

private:
	JavaClass _cls;
	jfieldID val;
};

template<>
struct JavaStaticFieldHelper<jboolean> {
	typedef jboolean T;
	T Get(const JavaStaticField<T>& self) {
		return self.Env().Val()->GetStaticBooleanField(self.GetClass().Val(), self.Val());
	}
	void Set(const JavaStaticField<T>& self, T&& val) {
		self.Env().Val()->SetStaticBooleanField(self.GetClass().Val(), self.Val(), std::forward<T>(val));
	}
};

template<>
struct JavaStaticFieldHelper<jchar> {
	typedef jchar T;
	T Get(const JavaStaticField<T>& self) {
		return self.Env().Val()->GetStaticCharField(self.GetClass().Val(), self.Val());
	}
	void Set(const JavaStaticField<T>& self, T&& val) {
		self.Env().Val()->SetStaticCharField(self.GetClass().Val(), self.Val(), std::forward<T>(val));
	}
};

template<>
struct JavaStaticFieldHelper<jbyte> {
	typedef jbyte T;
	T Get(const JavaStaticField<T>& self) {
		return self.Env().Val()->GetStaticByteField(self.GetClass().Val(), self.Val());
	}
	void Set(const JavaStaticField<T>& self, T&& val) {
		self.Env().Val()->SetStaticByteField(self.GetClass().Val(), self.Val(), std::forward<T>(val));
	}
};

template<>
struct JavaStaticFieldHelper<jshort> {
	typedef jshort T;
	T Get(const JavaStaticField<T>& self) {
		return self.Env().Val()->GetStaticShortField(self.GetClass().Val(), self.Val());
	}
	void Set(const JavaStaticField<T>& self, T&& val) {
		self.Env().Val()->SetStaticShortField(self.GetClass().Val(), self.Val(), std::forward<T>(val));
	}
};

template<>
struct JavaStaticFieldHelper<jint> {
	typedef jint T;
	T Get(const JavaStaticField<T>& self) {
		return self.Env(), self.Env().Val()->GetStaticIntField(self.GetClass().Val(), self.Val());
	}
	void Set(const JavaStaticField<T>& self, T&& val) {
		self.Env().Val()->SetStaticIntField(self.GetClass().Val(), self.Val(), std::forward<T>(val));
	}
};

// template<>
// struct JavaStaticFieldHelper<TestJniInt> {
// 	typedef TestJniInt T;
// 	T Get(const JavaStaticField<T>& self) {
// 		return FromJavaProxy<T>(self.Env(), self.Env().Val()->GetStaticIntField(self.GetClass().Val(), self.Val())).Val();
// 	}
// 	void Set(const JavaStaticField<T>& self, T&& val) {
// 		self.Env().Val()->SetStaticIntField(self.GetClass().Val(), self.Val(), ToJavaProxy<T>(self.Env(), std::forward<T>(val)).Val());
// 	}
// };

template<>
struct JavaStaticFieldHelper<jlong> {
	typedef jlong T;
	T Get(const JavaStaticField<T>& self) {
		return self.Env().Val()->GetStaticLongField(self.GetClass().Val(), self.Val());
	}
	void Set(const JavaStaticField<T>& self, T&& val) {
		self.Env().Val()->SetStaticLongField(self.GetClass().Val(), self.Val(), std::forward<T>(val));
	}
};

template<>
struct JavaStaticFieldHelper<jfloat> {
	typedef jfloat T;
	T Get(const JavaStaticField<T>& self) {
		return self.Env().Val()->GetStaticFloatField(self.GetClass().Val(), self.Val());
	}
	void Set(const JavaStaticField<T>& self, T&& val) {
		self.Env().Val()->SetStaticFloatField(self.GetClass().Val(), self.Val(), std::forward<T>(val));
	}
};

template<>
struct JavaStaticFieldHelper<jdouble> {
	typedef jdouble T;
	T Get(const JavaStaticField<T>& self) {
		return self.Env().Val()->GetStaticDoubleField(self.GetClass().Val(), self.Val());
	}
	void Set(const JavaStaticField<T>& self, T&& val) {
		self.Env().Val()->SetStaticDoubleField(self.GetClass().Val(), self.Val(), std::forward<T>(val));
	}
};

}

#endif
