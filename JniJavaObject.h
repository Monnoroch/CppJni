#pragma once
#ifndef JNI_JAVA_OBJECT_H
#define JNI_JAVA_OBJECT_H

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
	JavaObject() : JavaObject(JavaEnv(), 0) {}
	JavaObject(JavaEnv env, jobject o) : _env(env), _obj(o) {
#ifdef MSYM_DEBUG_JNI_REF_CNT
		if(Valid())            
			globalRefCnt++;
#endif
	}

	JavaObject(const JavaObjectIniter& o) : JavaObject(o.env, o.obj) {}
	JavaObject(const JavaObject& o) {
		Init(o);
	}
	JavaObject(JavaObject&& o) : _env(o._env), _obj(o._obj) {
		o._env = JavaEnv();
		o._obj = 0;
	}

	static JavaObject New(const JavaClass& cls);
	static JavaObject New(JavaEnv env, const std::string& cls);

	template<typename R, typename ... Args>
	static JavaObject New(const JavaClass& cls, Args&& ... args);

	template<typename T>
	static JavaObject New(JavaEnv env, const std::string& cls);

	JavaObject& operator=(const JavaObject& o) {
		Reset(o);
		return *this;
	}

	JavaObject& operator=(JavaObject&& o) {
		std::swap(_env, o._env);
		std::swap(_obj, o._obj);
		return *this;
	}

	virtual ~JavaObject() {
		Destroy();
	}

	bool operator==(const JavaObject& obj) const {
		return _env.Val()->IsSameObject(Val(), obj.Val());
	}

	bool operator!=(const JavaObject& obj) const {
		return !(*this == obj);
	}

	JavaClass GetClass() const;

	bool Valid() const { return _env.Valid() && _obj != 0; }
	JavaEnv Env() const { return _env; }

	/// Нужно имплементировать!
	jobject Val() const { return _obj; }

	jint MonitorEnter() const {
		return _env.Val()->MonitorEnter(Val());
	}

	jint MonitorExit() const {
		return _env.Val()->MonitorExit(Val());
	}

	template<typename T>
	JavaMethod<T> GetMethod(const char * name) const;

	template<typename T>
	JavaField<T> GetField(const char * name) const;

protected:
	void Reset(const JavaObject& o) {
		Destroy();
		Init(o);
	}

private:
	void Init(const JavaObject& o) {
		_env = o._env;
		if(o.Valid()) {
#ifdef MSYM_DEBUG_JNI_REF_CNT
		globalRefCnt++;
#endif
			_obj = _env.Val()->NewLocalRef(o._obj);
		}
	}

	void Destroy() {
		if(Valid()) {
#ifdef MSYM_DEBUG_JNI_REF_CNT
		globalRefCnt--;
#endif
			_env.Val()->DeleteLocalRef(_obj);
		}
	}

protected:
	JavaEnv _env;
	jobject _obj;
};


class JavaBoolean : public JavaObject {
public:
	JavaBoolean() : JavaObject() {}
	JavaBoolean(JavaEnv env, jobject obj) : JavaObject(env, obj) {}
	JavaBoolean(const JavaBoolean& str) : JavaObject(str) {}
	JavaBoolean(JavaBoolean&& str) : JavaObject(str) {}
};

}

#endif
