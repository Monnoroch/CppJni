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
	static T Get(const JavaField<T>& self) {
		return FromJavaProxy<T>(self.Env(), self.Env().Val()->GetObjectField(self.GetObject().Val(), self.Val())).Val();
	}
	static void Set(const JavaField<T>& self, T&& val) {
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
		m.val = nullptr;
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
		return JavaFieldHelper<T>::Get(*this);
	}

	void Set(T&& v) {
		JavaFieldHelper<T>::Set(*this, std::forward<T>(v));
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
		return _obj.Valid() &&  val != nullptr;
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
	static T Get(const JavaField<T>& self);
	static void Set(const JavaField<T>& self, T&& val);
};

template<>
struct JavaFieldHelper<jchar> {
	typedef jchar T;
	static T Get(const JavaField<T>& self);
	static void Set(const JavaField<T>& self, T&& val);
};

template<>
struct JavaFieldHelper<jbyte> {
	typedef jbyte T;
	static T Get(const JavaField<T>& self);
	static void Set(const JavaField<T>& self, T&& val);
};

template<>
struct JavaFieldHelper<jshort> {
	typedef jshort T;
	static T Get(const JavaField<T>& self);
	static void Set(const JavaField<T>& self, T&& val);
};

template<>
struct JavaFieldHelper<jint> {
	typedef jint T;
	static T Get(const JavaField<T>& self);
	static void Set(const JavaField<T>& self, T&& val);
};

// template<>
// struct JavaFieldHelper<TestJniInt> {
// 	typedef TestJniInt T;
// 	static T Get(const JavaField<T>& self);
// 	static void Set(const JavaField<T>& self, T&& val);
// };

template<>
struct JavaFieldHelper<jlong> {
	typedef jlong T;
	static T Get(const JavaField<T>& self);
	static void Set(const JavaField<T>& self, T&& val);
};

template<>
struct JavaFieldHelper<jfloat> {
	typedef jfloat T;
	static T Get(const JavaField<T>& self);
	static void Set(const JavaField<T>& self, T&& val);
};

template<>
struct JavaFieldHelper<jdouble> {
	typedef jdouble T;
	static T Get(const JavaField<T>& self);
	static void Set(const JavaField<T>& self, T&& val);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
struct JavaStaticFieldHelper {
	static T Get(const JavaStaticField<T>& self) {
		return FromJavaProxy<T>(self.Env(), self.Env().Val()->GetStaticObjectField(self.GetClass().Val(), self.Val())).Val();
	}
	static void Set(const JavaStaticField<T>& self, T&& val) {
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
		m.val = nullptr;
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
		return JavaStaticFieldHelper<T>::Get(*this);
	}

	void Set(T&& v) {
		JavaStaticFieldHelper<T>::Set(*this, std::forward<T>(v));
	}

	operator T() const {
		return Get();
	}

	jfieldID Val() const {
		return val;
	}

	bool Valid() const {
		return _cls.Valid() &&  val != nullptr;
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
	static T Get(const JavaStaticField<T>& self);
	static void Set(const JavaStaticField<T>& self, T&& val);
};

template<>
struct JavaStaticFieldHelper<jchar> {
	typedef jchar T;
	static T Get(const JavaStaticField<T>& self);
	static void Set(const JavaStaticField<T>& self, T&& val);
};

template<>
struct JavaStaticFieldHelper<jbyte> {
	typedef jbyte T;
	static T Get(const JavaStaticField<T>& self);
	static void Set(const JavaStaticField<T>& self, T&& val);
};

template<>
struct JavaStaticFieldHelper<jshort> {
	typedef jshort T;
	static T Get(const JavaStaticField<T>& self);
	static void Set(const JavaStaticField<T>& self, T&& val);
};

template<>
struct JavaStaticFieldHelper<jint> {
	typedef jint T;
	static T Get(const JavaStaticField<T>& self);
	static void Set(const JavaStaticField<T>& self, T&& val);
};

// template<>
// struct JavaStaticFieldHelper<TestJniInt> {
// 	typedef TestJniInt T;
// 	static T Get(const JavaStaticField<T>& self);
// 	static void Set(const JavaStaticField<T>& self, T&& val);
// };

template<>
struct JavaStaticFieldHelper<jlong> {
	typedef jlong T;
	static T Get(const JavaStaticField<T>& self);
	static void Set(const JavaStaticField<T>& self, T&& val);
};

template<>
struct JavaStaticFieldHelper<jfloat> {
	typedef jfloat T;
	static T Get(const JavaStaticField<T>& self);
	static void Set(const JavaStaticField<T>& self, T&& val);
};

template<>
struct JavaStaticFieldHelper<jdouble> {
	typedef jdouble T;
	static T Get(const JavaStaticField<T>& self);
	static void Set(const JavaStaticField<T>& self, T&& val);
};

}

#endif
