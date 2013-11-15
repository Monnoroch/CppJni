#pragma once
#ifndef JNI_JAVA_OBJECT_CLASS_DEF_H
#define JNI_JAVA_OBJECT_CLASS_DEF_H

#include <JniForwards.h>
#include <JniJavaEnv.h>


namespace JNI {

#define MSYM_DEBUG_JNI_REF_CNT 1
 
#ifdef MSYM_DEBUG_JNI_REF_CNT
extern int globalRefCnt;
#endif


class JavaObject {
	struct JavaObjectIniter {
		JavaEnv env;
		jobject obj;
	};
public:
	JavaObject();
	JavaObject(JavaEnv env, jobject o);
	JavaObject(const JavaObjectIniter& o);
	JavaObject(const JavaObject& o);
	JavaObject(JavaObject&& o);

	static JavaObject New(const JavaClass& cls);
	static JavaObject New(JavaEnv env, const std::string& cls);

	template<typename R, typename ... Args>
	static JavaObject New(const JavaClass& cls, Args&& ... args);

	template<typename R, typename ... Args>
	static JavaObject New(JavaEnv env, const std::string& cls, Args&& ... args);

	JavaObject& operator=(const JavaObject& o);
	JavaObject& operator=(JavaObject&& o);

	virtual ~JavaObject();

	bool operator==(const JavaObject& obj) const;
	bool operator!=(const JavaObject& obj) const;

	JavaClass GetClass() const;

	bool Valid() const;
	JavaEnv Env() const;
	/// Нужно имплементировать!
	jobject Val() const;

	jint MonitorEnter() const;
	jint MonitorExit() const;

	template<typename T>
	JavaMethod<T> GetMethod(const char * name) const;

	template<typename T>
	JavaField<T> GetField(const char * name) const;

	template<typename T>
	T GetFieldValue(const char * name) const {
		return GetField<T>(name).Get();
	}

protected:
	void Reset(const JavaObject& o);

	JavaEnv _env;
	jobject _obj;

private:
	void Init(const JavaObject& o);
	void Destroy();
};

}

#endif
