#pragma once
#ifndef JNI_JAVA_CLASS_H
#define JNI_JAVA_CLASS_H

#include <JniForwards.h>
#include <JniProxy.h>
#include <JniJavaObject.h>
#include <JniJavaException.h>
#include <JniSignatureBuilder.h>


namespace JNI {

class JavaClass : public JavaObject {
	template<typename R, typename ... Args>
	struct MethodGetter;
	template<typename R, typename ... Args>
	struct StaticMethodGetter;
	template<typename T>
	struct FieldGetter;
	template<typename T>
	struct StaticFieldGetter;

public:
	JavaClass() : JavaObject() {}
	JavaClass(JavaEnv env, jclass c) : JavaObject(env, c) {}
	JavaClass(JavaEnv env, const char * val) : JavaClass(env, GetClass(env, val)) {}
	JavaClass(JavaEnv env, const std::string& val) : JavaClass(env, GetClass(env, val.c_str())) {}
	JavaClass(const JavaClass& c) : JavaObject(c) {}
	JavaClass(JavaClass&& c) : JavaObject(c) {}

	static JavaClass New(JavaEnv env, const char * str);
	static JavaClass New(JavaEnv env, const std::string& str);


	JavaObject NewObject() const;

	template<typename R, typename ... Args>
	JavaObject NewObject(Args&& ... args) const {
		return FromJavaProxy<JavaObject>(_env, _env.Val()->NewObject(Val(), GetConstructor<R(Args...)>().Val(), ToJavaProxy(_env, std::forward<Args>(args)).Val()...)).Val();
	}

	virtual ~JavaClass() {}

	JavaClass& operator=(const JavaClass& cls) {
		JavaObject::operator=(cls);
		return *this;
	}

	JavaClass& operator=(JavaClass&& cls) {
		JavaObject::operator=(std::move(cls));
		return *this;
	}

	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaClass& cls) const {
		return JavaObject::operator==(cls);
	}

	bool operator!=(const JavaClass& cls) const {
		return JavaObject::operator!=(cls);
	}

	bool operator==(const std::string& str) const {
		return *this == _env.FindClass(str);
	}

	bool operator!=(const std::string& str) const {
		return !(*this == str);
	}

	friend bool operator==(const std::string& str, const JavaClass& self) {
		return self == str;
	}

	friend bool operator!=(const std::string& str, const JavaClass& self) {
		return self != str;
	}

	jclass Val() const { return (jclass) _obj; }

	JavaClass Superclass() const {
		return JavaClass(_env, _env.Val()->GetSuperclass(Val()));
	}

	jboolean IsAssignableFrom(const JavaClass& cls) const {
		return _env.Val()->IsAssignableFrom(Val(), cls.Val());
	}

	template<typename T>
	JavaMethod<T> GetMethod(const JavaObject& obj, const char * name) const {
		return JavaMethod<T>(obj, MethodGetter<T>().Get(*this, name));
	}

	template<typename T>
	JavaStaticMethod<T> GetStaticMethod(const char * name) const {
		return JavaStaticMethod<T>(*this, StaticMethodGetter<T>().Get(*this, name));
	}

	JavaStaticMethod<void()> GetDefaultConstructor() const;

	// почему-то, конструктор в JNI -- не статический метод класса О_о
	// я сделал статическим
	template<typename T>
	JavaStaticMethod<T> GetConstructor() const {
		return JavaStaticMethod<T>(*this, MethodGetter<T>().Get(*this, "<init>"));
	}

	template<typename T>
	JavaField<T> GetField(const JavaObject& obj, const char * name) const {
		return JavaField<T>(obj, FieldGetter<T>().Get(*this, name));
	}

	template<typename T>
	JavaStaticField<T> GetStaticField(const char * name) const {
		return JavaStaticField<T>(*this, StaticFieldGetter<T>().Get(*this, name));
	}

	template<typename T>
	T GetStaticFieldValue(const char * name) const {
		return GetStaticField<T>(name).Get();
	}

private:
	static jclass GetClass(JavaEnv env, const char * name);
};

////////////////////////////////////////////////////////////////////////////////////

template<typename R, typename ... Args>
struct JavaClass::MethodGetter<R(Args...)> {
	jmethodID Get(const JavaClass& self, const char * name) const {
		return self.Env().Val()->GetMethodID(self.Val(), name, JniSignatureBuilder<R(Args...)>::Signature().c_str());
	}
};

template<typename R, typename ... Args>
struct JavaClass::StaticMethodGetter<R(Args...)> {
	jmethodID Get(const JavaClass& self, const char * name) const {
		return self.Env().Val()->GetStaticMethodID(self.Val(), name, JniSignatureBuilder<R(Args...)>::Signature().c_str());
	}
};

template<typename T>
struct JavaClass::FieldGetter {
	jfieldID Get(const JavaClass& self, const char * name) const {
		return self.Env().Val()->GetFieldID(self.Val(), name, JniSignatureBuilder<T>::Signature().c_str());
	}
};

template<typename T>
struct JavaClass::StaticFieldGetter {
	jfieldID Get(const JavaClass& self, const char * name) const {
		return self.Env().Val()->GetStaticFieldID(self.Val(), name, JniSignatureBuilder<T>::Signature().c_str());
	}
};

/////////////////////////////////////////////////////////////////////////////////////

// Методы из JavaObject. Иначе никак нельзя: циклические зависимости в шаблонных методах.
template<typename T>
JavaMethod<T> JavaObject::GetMethod(const char * name) const {
	return GetClass().GetMethod<T>(*this, name);
}

template<typename T>
JavaField<T> JavaObject::GetField(const char * name) const {
	return GetClass().GetField<T>(*this, name);
}

template<typename R, typename ... Args>
JavaObject JavaObject::New(const JavaClass& cls, Args&& ... args) {
	return cls.NewObject<R, Args...>(std::forward<Args>(args)...);
}

template<typename R, typename ... Args>
JavaObject JavaObject::New(JavaEnv env, const std::string& cls, Args&& ... args) {
	return New(env.FindClass(cls), std::forward<Args>(args)...);
}

}

#endif
