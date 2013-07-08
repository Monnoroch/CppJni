#pragma once
#ifndef JNI_FORWARDS_H
#define JNI_FORWARDS_H

#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>


#include <jni.h>


/*

Инструкция по передаче user-defined типа T в и из java.

I. Связывание c++ класса T с java-классом (на примере связывания std::string и java.lang.String)

1) Для построения JNI сигнатуры в JniSignatureBuilder.h реализовать структуру JniSignatureBuilder<T>:

template<>
struct JniSignatureBuilder<std::string> {
	static std::string Signature() {
		return "Ljava/lang/String;";
	}
};

2) Для конвертации из T в joblect в JniProxy.h реализовать структуру JniToJavaProxy<T>:

// воспользуемся готовым классом JavaString, обертывающим java.lang.String напрямую через встроенные JNI функции.
template<>
struct JniToJavaProxy<std::string> {
	JniToJavaProxy(JavaEnv env, const std::string& v) : val(env, v) {}
	jstring Val() const { return val.Val(); }
	JavaString val;
};

3) Для конвертации jobject в T в JniProxy.h реализовать структуру JniFromJavaProxy<T>:

// воспользуемся готовым классом JavaString, обертывающим java.lang.String напрямую через встроенные JNI функции.
template<>
struct JniFromJavaProxy<std::string> {
	JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jstring) obj) {}
	std::string Val() const { return JavaString(_env, _obj).Value(); }
	JavaEnv _env;
	jstring _obj;
};


II. Связывание c++ класса T с примитивным java типом (на примере связывания класса TestJniInt с jint)

struct TestJniInt {
	TestJniInt(int val) : _val(val) {}
	int Val() const { return _val; }
	int _val;
};

1,2,3) Выполнить вышеописанные действия для связывания с классом.

template<>
struct JniSignatureBuilder<TestJniInt> {
	static std::string Signature() {
		return "I";
	}
};

template<>
struct JniToJavaProxy<TestJniInt> {
	JniToJavaProxy(JavaEnv, const TestJniInt& v) : val(v) {}
	jint Val() const { return val.Val(); }
	const TestJniInt& val;
};

template<>
struct JniFromJavaProxy<TestJniInt> {
	JniFromJavaProxy(JavaEnv, jint obj) : _obj(obj) {}
	TestJniInt Val() const { return TestJniInt(_obj); }
	jint _obj;
};

4) Для возвращения TestJniInt java методами, возвращающими jint необходимо в JniJavaMethod.h
реализовать структуры JavaMethodCaller<T> и JavaStaticMethodCaller<T>:

template<>
struct JavaMethodCaller<TestJniInt> {
	typedef TestJniInt R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		return FromJavaProxy<R>(self.Env(), self.Env().Val()->CallIntMethod(self.GetObject().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...)).Val();
	}
};

template<>
struct JavaStaticMethodCaller<TestJniInt> {
	typedef TestJniInt R;
	template<typename ... Args>
	R Call(const JavaStaticMethod<R(Args...)>& self, Args&& ... args) {
		return FromJavaProxy<R>(self.Env(), self.Env().Val()->CallStaticIntMethod(self.GetObject().Val(), self.Val(), ToJavaProxy(self.Env(), std::forward<Args>(args)).Val()...)).Val();
	}
};

5) Для получения и установки jint полей значением класса TestJniInt необходимо в JniJavaField.h
реализовать структуры JavaFieldHelper<T> и JavaStaticFieldHelper<T>:

template<>
struct JavaFieldHelper<TestJniInt> {
	typedef TestJniInt T;
	T Get(const JavaField<T>& self) {
		return FromJavaProxy<T>(self.Env(), self.Env().Val()->GetIntField(self.GetObject().Val(), self.Val())).Val();
	}
	void Set(const JavaField<T>& self, T&& val) {
		self.Env().Val()->SetIntField(self.GetObject().Val(), self.Val(), ToJavaProxy<T>(self.Env(), std::forward<T>(val)).Val());
	}
};

template<>
struct JavaStaticFieldHelper<TestJniInt> {
	typedef TestJniInt T;
	T Get(const JavaStaticField<T>& self) {
		return FromJavaProxy<T>(self.Env(), self.Env().Val()->GetStaticIntField(self.GetClass().Val(), self.Val())).Val();
	}
	void Set(const JavaStaticField<T>& self, T&& val) {
		self.Env().Val()->SetStaticIntField(self.GetClass().Val(), self.Val(), ToJavaProxy<T>(self.Env(), std::forward<T>(val)).Val());
	}
};

*/


namespace JNI {

class JniHelper;
class JniJavaVM;
class JavaEnv;
class JavaObject;
class JavaException;
class JavaClass;
class JavaString;
template<typename T>
class JavaArray;
template<typename R, typename ... Args>
class JavaMethod;
template<typename R, typename ... Args>
class JavaStaticMethod;
template<typename T>
class JavaField;
template<typename T>
class JavaStaticField;
template<typename R, typename ... Args>
struct JniSignatureBuilder;


template<typename T>
struct JniFromJavaProxy;

template<typename T, typename J>
static inline JniFromJavaProxy<T> FromJavaProxy(JavaEnv env, J v);

}

// namespace JNI {

// struct TestJniInt {
// 	TestJniInt(int val) : _val(val) {}
// 	int Val() const { return _val; }
// 	int _val;
// };

// }

#endif
