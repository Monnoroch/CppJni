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
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return FromJavaProxy<R>(self.Env(), self.Env().Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...)).Val();
	}
};

template<>
struct JavaMethodCaller<void> {
	typedef void R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		self.Env().Val()->CallVoidMethod(self.GetObject().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaMethodCaller<jboolean> {
	typedef jboolean R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallBooleanMethod(self.GetObject().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaMethodCaller<jchar> {
	typedef jchar R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallCharMethod(self.GetObject().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaMethodCaller<jbyte> {
	typedef jbyte R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallByteMethod(self.GetObject().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaMethodCaller<jshort> {
	typedef jshort R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallShortMethod(self.GetObject().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaMethodCaller<jint> {
	typedef jint R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallIntMethod(self.GetObject().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

// template<>
// struct JavaMethodCaller<TestJniInt> {
// 	typedef TestJniInt R;
// 	template<typename ... Args>
// 	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
// 		return FromJavaProxy<R>(self.Env(), self.Env().Val()->CallIntMethod(self.GetObject().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...)).Val();
// 	}
// };

template<>
struct JavaMethodCaller<jlong> {
	typedef jlong R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallLongMethod(self.GetObject().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaMethodCaller<jfloat> {
	typedef jfloat R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallFloatMethod(self.GetObject().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaMethodCaller<jdouble> {
	typedef jdouble R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallDoubleMethod(self.GetObject().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...);
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
		m.val = nullptr;
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
	jmethodID val;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename R>
struct JavaStaticMethodCaller {
	template<typename ... Args>
	R Call(JavaStaticMethod<R, Args...>& self, Args&& ... args) {
		return FromJavaProxy<R>(self.Env(), self.Env().Val()->CallStaticObjectMethod(self.GetClass().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...)).Val();
	}
};

template<>
struct JavaStaticMethodCaller<void> {
	typedef void R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		self.Env().Val()->CallStaticVoidMethod(self.GetClass().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaStaticMethodCaller<jboolean> {
	typedef jboolean R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallStaticBooleanMethod(self.GetClass().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaStaticMethodCaller<jchar> {
	typedef jchar R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallStaticCharMethod(self.GetClass().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaStaticMethodCaller<jbyte> {
	typedef jbyte R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallStaticByteMethod(self.GetClass().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaStaticMethodCaller<jshort> {
	typedef jshort R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallStaticShortMethod(self.GetClass().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaStaticMethodCaller<jint> {
	typedef jint R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallStaticIntMethod(self.GetClass().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

// template<>
// struct JavaStaticMethodCaller<TestJniInt> {
// 	typedef TestJniInt R;
// 	template<typename ... Args>
// 	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
// 		return FromJavaProxy<R>(self.Env(), self.Env().Val()->CallStaticIntMethod(self.GetObject().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...)).Val();
// 	}
// };

template<>
struct JavaStaticMethodCaller<jlong> {
	typedef jlong R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallStaticLongMethod(self.GetClass().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaStaticMethodCaller<jfloat> {
	typedef jfloat R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallStaticFloatMethod(self.GetClass().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...);
	}
};

template<>
struct JavaStaticMethodCaller<jdouble> {
	typedef jdouble R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		return self.Env().Val()->CallStaticDoubleMethod(self.GetClass().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...);
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
		m.val = nullptr;
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
	jmethodID val;
};

}

#endif
