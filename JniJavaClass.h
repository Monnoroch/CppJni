#pragma once
#ifndef JNI_JAVA_CLASS_H
#define JNI_JAVA_CLASS_H

#include <JniForwards.h>
#include <JniProxy.h>
#include <JniJavaObject.h>
#include <JniSignatureBuilder.h>


namespace JNI {

class JavaClass : public JavaObject {
	template<typename R, typename ... Args>
	struct MethodGetter;

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
	JavaObject NewObject(Args&& ... args) {
		return JavaObject(_env, _env.Val()->NewObject(Val(), GetConstructor<R(Args...)>().Val(), MakeJniProxy(_env, std::forward<Args>(args)).Val()...));
	}

	virtual ~JavaClass() {}

	JavaClass& operator=(const JavaClass& cls) {
		JavaObject::operator=(cls);
		return *this;
	}

	JavaClass& operator=(JavaClass&& cls) {
		JavaObject::operator=(cls);
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
		return JavaStaticMethod<T>(*this, MethodGetter<T>().Get(*this, name));
	}

	JavaStaticMethod<void()> GetDefaultConstructor() const;

	template<typename T>
	JavaStaticMethod<T> GetConstructor() const {
		return GetStaticMethod<T>("<init>");
	}

	// template<typename T>
	// JavaField<T> GetField(const char * name, const char * sig) const
	// {
	// 	jfieldID id = mEnv->GetFieldID(Val(), name, sig);
	// 	if(id == 0)
	// 	{
	// 		LOGE("JavaClass::GetField: cannot find method %s.", name);
	// 		return JavaField<T>();
	// 	}
	// 	return JavaField<T>(mEnv, id);
	// }

	// template<typename T>
	// JavaStaticField<T> GetStaticField(const char * name, const char * sig) const
	// {
	// 	jfieldID id = mEnv->GetStaticFieldID(Val(), name, sig);
	// 	if(id == 0)
	// 	{
	// 		LOGE("JavaClass::GetField: cannot find method %s.", name);
	// 		return JavaStaticField<T>(*this);
	// 	}
	// 	return JavaStaticField<T>(*this, id);
	// }

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

/////////////////////////////////////////////////////////////////////////////////////

// Методы из JavaObject. Иначе никак нельзя: циклические зависимости в шаблонных методах.
template<typename T>
JavaMethod<T> JavaObject::GetMethod(const char * name) const {
	return GetClass().GetMethod<T>(*this, name);
}

template<typename R, typename ... Args>
JavaObject JavaObject::New(const JavaClass& cls, Args&& ... args) {
	return cls.NewObject<R, Args...>(std::forward<Args>(args)...);
}

template<typename T>
JavaObject JavaObject::New(JavaEnv env, const std::string& cls) {
	return New(env.FindClass(cls));
}

}

#endif
