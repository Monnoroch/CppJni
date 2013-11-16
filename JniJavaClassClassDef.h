#pragma once
#ifndef JNI_JAVA_CLASS_CLASS_DEF_H
#define JNI_JAVA_CLASS_CLASS_DEF_H

#include <JniForwards.h>
#include <JniProxy.h>
#include <JniJavaObjectClassDef.h>


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
	JavaClass();
	JavaClass(JavaEnv env, jclass c);
	JavaClass(JavaEnv env, const char * val);
	JavaClass(JavaEnv env, const std::string& val);
	JavaClass(const JavaClass& c);
	JavaClass(JavaClass&& c);

	static JavaClass New(JavaEnv env, const char * str);
	static JavaClass New(JavaEnv env, const std::string& str);


	JavaObject NewObject() const;

	template<typename R, typename ... Args>
	JavaObject NewObject(Args&& ... args) const {
		return FromJavaProxy<JavaObject>(_env, _env.Val()->NewObject(Val(), GetConstructor<R(Args...)>().Val(), ToJavaProxy(_env, std::forward<Args>(args)).Val()...)).Val();
	}

	virtual ~JavaClass();

	JavaClass& operator=(const JavaClass& cls);
	JavaClass& operator=(JavaClass&& cls);

	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaClass& cls) const;
	bool operator!=(const JavaClass& cls) const;
	bool operator==(const std::string& str) const;
	bool operator!=(const std::string& str) const;

	friend bool operator==(const std::string& str, const JavaClass& self) {
		return self == str;
	}

	friend bool operator!=(const std::string& str, const JavaClass& self) {
		return self != str;
	}

	jclass Val() const;
	JavaClass Superclass() const;
	jboolean IsAssignableFrom(const JavaClass& cls) const;

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

}

#endif
