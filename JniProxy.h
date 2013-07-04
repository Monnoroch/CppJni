#pragma once
#ifndef JNI_PROXY_H
#define JNI_PROXY_H

#include <JniForwards.h>
#include <JniJavaEnv.h>
#include <JniJavaObject.h>
#include <JniJavaString.h>
#include <JniJavaArray.h>


namespace JNI {

template<typename T>
struct JniToJavaProxy {
	JniToJavaProxy(JavaEnv, T v) : val(v) {}
	T Val() const { return val; }
	T val;
};

template<>
struct JniToJavaProxy<JavaObject> {
	typedef JavaObject R;
	typedef jobject jtype;
	JniToJavaProxy(JavaEnv, const R& v) : val(v) {}
	jtype Val() const { return val.Val(); }
	const R& val;
};

template<>
struct JniToJavaProxy<JavaString> {
	typedef JavaString R;
	typedef jstring jtype;
	JniToJavaProxy(JavaEnv, const R& v) : val(v) {}
	jtype Val() const { return val.Val(); }
	const R& val;
};

template<>
struct JniToJavaProxy<JavaBoolean> {
	typedef JavaBoolean R;
	typedef jobject jtype;
	JniToJavaProxy(JavaEnv, const R& v) : val(v) {}
	jtype Val() const { return val.Val(); }
	const R& val;
};

template<typename T>
struct JniToJavaProxy<JavaArray<T>> {
	typedef JavaArray<T> R;
	typedef jarray jtype;
	JniToJavaProxy(JavaEnv, const R& v) : val(v) {}
	jtype Val() const { return val.Val(); }
	const R& val;
};

template<>
struct JniToJavaProxy<const char*> {
	typedef const char * R;
	typedef JavaString Proxy;
	typedef jstring jtype;
	JniToJavaProxy(JavaEnv env, R v) : val(env, v) {}
	jtype Val() const { return val.Val(); }
	Proxy val;
};

template<>
struct JniToJavaProxy<std::string> {
	typedef std::string R;
	typedef JavaString Proxy;
	typedef jstring jtype;
	JniToJavaProxy(JavaEnv env, const R& v) : val(env, v) {}
	jtype Val() const { return val.Val(); }
	Proxy val;
};

template<typename T>
struct JniToJavaProxy<std::vector<T>> {
	typedef std::vector<T> R;
	typedef JavaArray<T> Proxy;
	typedef jarray jtype;
	JniToJavaProxy(JavaEnv env, const R& v) : val(env, v) {}
	jtype Val() const { return val.Val(); }
	Proxy val;
};

// template<>
// struct JniToJavaProxy<TestJniInt> {
// 	typedef TestJniInt R;
// 	typedef jint jtype;
// 	JniToJavaProxy(JavaEnv, const R& v) : val(v) {}
// 	jtype Val() const { return val.Val(); }
// 	const R& val;
// };


template<typename T>
static inline JniToJavaProxy<T> ToJavaProxy(JavaEnv env, const T& v) {
	return JniToJavaProxy<T>(env, v);
}

/////////////////////////////////////////////

template<typename T>
struct JniFromJavaProxy;

template<>
struct JniFromJavaProxy<JavaObject> {
	typedef JavaObject R;
	typedef jobject jtype;
	JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj(obj) {}
	R Val() const { return R(_env, _obj); }
	JavaEnv _env;
	jtype _obj;
};

template<>
struct JniFromJavaProxy<JavaString> {
	typedef JavaString R;
	typedef jstring jtype;
	JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}
	R Val() const { return R(_env, _obj); }
	JavaEnv _env;
	jtype _obj;
};

template<>
struct JniFromJavaProxy<JavaBoolean> {
	typedef JavaBoolean R;
	typedef jobject jtype;
	JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}
	R Val() const { return R(_env, _obj); }
	JavaEnv _env;
	jtype _obj;
};

template<typename T>
struct JniFromJavaProxy<JavaArray<T>> {
	typedef JavaArray<T> R;
	typedef jarray jtype;
	JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}
	R Val() const { return R(_env, _obj); }
	JavaEnv _env;
	jtype _obj;
};

template<>
struct JniFromJavaProxy<JavaArray<jboolean>> {
	typedef JavaArray<jboolean> R;
	typedef jbooleanArray jtype;
	JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}
	R Val() const { return R(_env, _obj); }
	JavaEnv _env;
	jtype _obj;
};

template<>
struct JniFromJavaProxy<JavaArray<jchar>> {
	typedef JavaArray<jchar> R;
	typedef jcharArray jtype;
	JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}
	R Val() const { return R(_env, _obj); }
	JavaEnv _env;
	jtype _obj;
};

template<>
struct JniFromJavaProxy<JavaArray<jbyte>> {
	typedef JavaArray<jbyte> R;
	typedef jbyteArray jtype;
	JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}
	R Val() const { return R(_env, _obj); }
	JavaEnv _env;
	jtype _obj;
};

template<>
struct JniFromJavaProxy<JavaArray<jshort>> {
	typedef JavaArray<jshort> R;
	typedef jshortArray jtype;
	JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}
	R Val() const { return R(_env, _obj); }
	JavaEnv _env;
	jtype _obj;
};

template<>
struct JniFromJavaProxy<JavaArray<jint>> {
	typedef JavaArray<jint> R;
	typedef jintArray jtype;
	JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}
	R Val() const { return R(_env, _obj); }
	JavaEnv _env;
	jtype _obj;
};

template<>
struct JniFromJavaProxy<JavaArray<jlong>> {
	typedef JavaArray<jlong> R;
	typedef jlongArray jtype;
	JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}
	R Val() const { return R(_env, _obj); }
	JavaEnv _env;
	jtype _obj;
};

template<>
struct JniFromJavaProxy<JavaArray<jfloat>> {
	typedef JavaArray<jfloat> R;
	typedef jfloatArray jtype;
	JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}
	R Val() const { return R(_env, _obj); }
	JavaEnv _env;
	jtype _obj;
};

template<>
struct JniFromJavaProxy<JavaArray<jdouble>> {
	typedef JavaArray<jdouble> R;
	typedef jdoubleArray jtype;
	JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}
	R Val() const { return R(_env, _obj); }
	JavaEnv _env;
	jtype _obj;
};

template<>
struct JniFromJavaProxy<std::string> {
	typedef std::string R;
	typedef jstring jtype;
	JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}
	R Val() const { return JavaString(_env, _obj).Value(); }
	JavaEnv _env;
	jtype _obj;
};

template<typename T>
struct JniFromJavaProxy<std::vector<T>> {
	typedef std::vector<T> R;
	typedef jobject jtype;
	JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}
	R Val() const { return  JniFromJavaProxy<JavaArray<T>>(_env, _obj).Val().ToVector(); }
	JavaEnv _env;
	jtype _obj;
};

// template<>
// struct JniFromJavaProxy<TestJniInt> {
// 	typedef TestJniInt R;
// 	typedef jint jtype;
// 	JniFromJavaProxy(JavaEnv, jtype obj) : _obj(obj) {}
// 	R Val() const { return R(_obj); }
// 	jtype _obj;
// };

template<typename T, typename J>
static inline JniFromJavaProxy<T> FromJavaProxy(JavaEnv env, J v) {
	return JniFromJavaProxy<T>(env, v);
}

}

#endif
