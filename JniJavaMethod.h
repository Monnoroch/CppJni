#pragma once
#ifndef JNI_JAVA_METHOD_H
#define JNI_JAVA_METHOD_H

#include <JniForwards.h>
#include <JniJavaEnv.h>
#include <JniJavaObject.h>
#include <JniJavaClass.h>
#include <JniJavaString.h>
#include <JniJavaArray.h>
#include <JniProxy.h>


namespace JNI {

template<typename R>
struct JavaMethodCaller {
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args);
};

template<>
struct JavaMethodCaller<void> {
	typedef void R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallVoidMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaMethodCaller<jboolean> {
	typedef jboolean R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallBooleanMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaMethodCaller<jchar> {
	typedef jchar R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallCharMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaMethodCaller<jbyte> {
	typedef jbyte R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallByteMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaMethodCaller<jshort> {
	typedef jshort R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallShortMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaMethodCaller<jint> {
	typedef jint R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallIntMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaMethodCaller<jlong> {
	typedef jlong R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallLongMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaMethodCaller<jfloat> {
	typedef jfloat R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallFloatMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaMethodCaller<jdouble> {
	typedef jdouble R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallDoubleMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaMethodCaller<JavaObject> {
	typedef JavaObject R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return JavaObject(env, env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...));
	}
};

template<>
struct JavaMethodCaller<JavaString> {
	typedef JavaString R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return JavaString(env, (jstring) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...));
	}
};

template<typename T>
struct JavaMethodCaller<JavaArray<T>> {
	typedef JavaArray<T> R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return JavaArray<T>(env, (jarray) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...));
	}
};

template<>
struct JavaMethodCaller<JavaArray<jboolean>> {
	typedef jboolean Elem;
	typedef jbooleanArray JArr;

	typedef JavaArray<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaMethodCaller<JavaArray<jchar>> {
	typedef jchar Elem;
	typedef jcharArray JArr;

	typedef JavaArray<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaMethodCaller<JavaArray<jbyte>> {
	typedef jbyte Elem;
	typedef jbyteArray JArr;

	typedef JavaArray<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaMethodCaller<JavaArray<jshort>> {
	typedef jshort Elem;
	typedef jshortArray JArr;

	typedef JavaArray<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaMethodCaller<JavaArray<jint>> {
	typedef jint Elem;
	typedef jintArray JArr;

	typedef JavaArray<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaMethodCaller<JavaArray<jlong>> {
	typedef jlong Elem;
	typedef jlongArray JArr;

	typedef JavaArray<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaMethodCaller<JavaArray<jfloat>> {
	typedef jfloat Elem;
	typedef jfloatArray JArr;

	typedef JavaArray<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaMethodCaller<JavaArray<jdouble>> {
	typedef jdouble Elem;
	typedef jdoubleArray JArr;

	typedef JavaArray<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaMethodCaller<const char*> {
	typedef const char* R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return JavaString(env, (jstring) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).Value();
	}
};

template<>
struct JavaMethodCaller<std::string> {
	typedef std::string R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return JavaString(env, (jstring) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).Value();
	}
};

template<typename T>
struct JavaMethodCaller<std::vector<T>> {
	typedef std::vector<T> R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return JavaArray<T>(env, (jarray) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaMethodCaller<std::vector<jboolean>> {
	typedef jboolean Elem;
	typedef jbooleanArray JArr;

	typedef std::vector<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaMethodCaller<std::vector<jchar>> {
	typedef jchar Elem;
	typedef jcharArray JArr;

	typedef std::vector<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaMethodCaller<std::vector<jbyte>> {
	typedef jbyte Elem;
	typedef jbyteArray JArr;

	typedef std::vector<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaMethodCaller<std::vector<jshort>> {
	typedef jshort Elem;
	typedef jshortArray JArr;

	typedef std::vector<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaMethodCaller<std::vector<jint>> {
	typedef jint Elem;
	typedef jintArray JArr;

	typedef std::vector<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaMethodCaller<std::vector<jlong>> {
	typedef jlong Elem;
	typedef jlongArray JArr;

	typedef std::vector<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaMethodCaller<std::vector<jfloat>> {
	typedef jfloat Elem;
	typedef jfloatArray JArr;

	typedef std::vector<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaMethodCaller<std::vector<jdouble>> {
	typedef jdouble Elem;
	typedef jdoubleArray JArr;

	typedef std::vector<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(env, args).Val()...)).ToVector();
	}
};


template<typename R, typename ... Args>
class JavaMethod<R(Args...)> {
public:
	JavaMethod() {}
	JavaMethod(const JavaObject& cls, jmethodID mid) : _obj(cls), val(mid) {}
	JavaMethod(const JavaMethod& m) : _obj(m._obj), val(m.val) {}
	JavaMethod(JavaMethod&& m) : _obj(m._obj), val(m.val) {
		m._obj = JavaObject();
		m.val = 0;
	}

	JavaMethod& operator=(const JavaMethod& m) {
		_obj = m._obj;
		val = m.val;
		return *this;
	}

	JavaMethod& operator=(JavaMethod&& m) {
		std::swap(_obj, m._obj);
		std::swap(val, m.val);
		return *this;
	}

	R operator()(Args&& ... args) const {
		return JavaMethodCaller<R>().Call(*this, std::forward<Args>(args)...);
	}

	jmethodID Val() const {
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
	jmethodID val;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename R>
struct JavaStaticMethodCaller {
	template<typename ... Args>
	R Call(JavaStaticMethod<R, Args...>& self, Args&& ... args);
};

template<>
struct JavaStaticMethodCaller<void> {
	typedef void R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallStaticVoidMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaStaticMethodCaller<jboolean> {
	typedef jboolean R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallStaticBooleanMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaStaticMethodCaller<jchar> {
	typedef jchar R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallStaticCharMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaStaticMethodCaller<jbyte> {
	typedef jbyte R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallStaticByteMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaStaticMethodCaller<jshort> {
	typedef jshort R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallStaticShortMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaStaticMethodCaller<jint> {
	typedef jint R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallStaticIntMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaStaticMethodCaller<jlong> {
	typedef jlong R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallStaticLongMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaStaticMethodCaller<jfloat> {
	typedef jfloat R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallStaticFloatMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaStaticMethodCaller<jdouble> {
	typedef jdouble R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallStaticDoubleMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaStaticMethodCaller<JavaObject> {
	typedef JavaObject R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return JavaObject(env, env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...));
	}
};

template<>
struct JavaStaticMethodCaller<JavaString> {
	typedef JavaString R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return JavaString(env, (jstring) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...));
	}
};

template<typename T>
struct JavaStaticMethodCaller<JavaArray<T>> {
	typedef JavaArray<T> R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return JavaArray<T>(env, (jarray) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...));
	}
};

template<>
struct JavaStaticMethodCaller<JavaArray<jboolean>> {
	typedef jboolean Elem;
	typedef jbooleanArray JArr;

	typedef JavaArray<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaStaticMethodCaller<JavaArray<jchar>> {
	typedef jchar Elem;
	typedef jcharArray JArr;

	typedef JavaArray<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaStaticMethodCaller<JavaArray<jbyte>> {
	typedef jbyte Elem;
	typedef jbyteArray JArr;

	typedef JavaArray<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaStaticMethodCaller<JavaArray<jshort>> {
	typedef jshort Elem;
	typedef jshortArray JArr;

	typedef JavaArray<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaStaticMethodCaller<JavaArray<jint>> {
	typedef jint Elem;
	typedef jintArray JArr;

	typedef JavaArray<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaStaticMethodCaller<JavaArray<jlong>> {
	typedef jlong Elem;
	typedef jlongArray JArr;

	typedef JavaArray<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaStaticMethodCaller<JavaArray<jfloat>> {
	typedef jfloat Elem;
	typedef jfloatArray JArr;

	typedef JavaArray<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaStaticMethodCaller<JavaArray<jdouble>> {
	typedef jdouble Elem;
	typedef jdoubleArray JArr;

	typedef JavaArray<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaStaticMethodCaller<const char*> {
	typedef const char* R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return JavaString(env, (jstring) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).Value();
	}
};

template<>
struct JavaStaticMethodCaller<std::string> {
	typedef std::string R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return JavaString(env, (jstring) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).Value();
	}
};

template<typename T>
struct JavaStaticMethodCaller<std::vector<T>> {
	typedef std::vector<T> R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return JavaArray<T>(env, (jarray) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaStaticMethodCaller<std::vector<jboolean>> {
	typedef jboolean Elem;
	typedef jbooleanArray JArr;

	typedef std::vector<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaStaticMethodCaller<std::vector<jchar>> {
	typedef jchar Elem;
	typedef jcharArray JArr;

	typedef std::vector<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaStaticMethodCaller<std::vector<jbyte>> {
	typedef jbyte Elem;
	typedef jbyteArray JArr;

	typedef std::vector<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaStaticMethodCaller<std::vector<jshort>> {
	typedef jshort Elem;
	typedef jshortArray JArr;

	typedef std::vector<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaStaticMethodCaller<std::vector<jint>> {
	typedef jint Elem;
	typedef jintArray JArr;

	typedef std::vector<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaStaticMethodCaller<std::vector<jlong>> {
	typedef jlong Elem;
	typedef jlongArray JArr;

	typedef std::vector<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaStaticMethodCaller<std::vector<jfloat>> {
	typedef jfloat Elem;
	typedef jfloatArray JArr;

	typedef std::vector<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<>
struct JavaStaticMethodCaller<std::vector<jdouble>> {
	typedef jdouble Elem;
	typedef jdoubleArray JArr;

	typedef std::vector<Elem> R;
	typedef JavaArray<Elem> Arr;
	
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return Arr(env, (JArr) env.Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).ToVector();
	}
};

template<typename R, typename ... Args>
class JavaStaticMethod<R(Args...)> {
public:
	JavaStaticMethod() {}
	JavaStaticMethod(const JavaClass& cls, jmethodID mid) : _cls(cls), val(mid) {}
	JavaStaticMethod(const JavaStaticMethod& m) : _cls(m._cls), val(m.val) {}
	JavaStaticMethod(JavaStaticMethod&& m) : _cls(m._cls), val(m.val) {
		m._cls = JavaClass();
		m.val = 0;
	}

	JavaStaticMethod& operator=(const JavaStaticMethod& m) {
		_cls = m._cls;
		val = m.val;
		return *this;
	}

	JavaStaticMethod& operator=(JavaStaticMethod&& m) {
		std::swap(_cls, m._cls);
		std::swap(val, m.val);
		return *this;
	}

	R operator()(Args&& ... args) {
		return JavaStaticMethodCaller<R>().Call(*this, std::forward<Args>(args)...);
	}

	jmethodID Val() const {
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
	jmethodID val;
};

}

#endif
