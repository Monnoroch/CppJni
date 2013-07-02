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

Для возвращения из джавы любого типа T необходимо реализовать три структуры:

В JniJavaMethod.h:
JavaMethodCaller<T> и JavaStaticMethodCaller<T> с конвертацией в T из какого бы то ни было jtype.
В JniSignatureBuilder.h:
JniSignatureBuilder<T> для получения сигнатуры java-обьекта.

Для передачи типа T в джаву нужно реализовать метод MakeJniProxy(JavaEnv, T) в JniProxy.h,
который бы возвращал тип с методом T::Val(), который бы возвращал один из jtype.

Пример:
Задаем аналогию между c++ типом std::string и java-типом java.lang.String.

При возвращении std::string из java-методов (обычных и статических) мы конвертируем jstring в std::string:

template<>
struct JavaMethodCaller<std::string> {
	typedef std::string R;
	template<typename ... Args>
	R Call(const JavaMethod<R(Args...)>& self, Args&& ... args) {
		JavaEnv env = self.Env();
		return JavaString(env, (jstring) env.Val()->CallObjectMethod(self.GetObject().Val(), self.Val(), MakeJniProxy(self.Env(), std::forward<Args>(args)).Val()...)).Value();
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

Сигнатура java-аналога std::string: Ljava/lang/String;

template<>
struct JniSignatureBuilder<std::string> {
	static std::string Signature() {
		return "Ljava/lang/String;";
	}
};

Если мы хотим передать в джаву std::string мы передаем JavaString::Val(), то есть jstring.
То есть эта функция задает конвертацию std::string в jstring.

JavaString MakeJniProxy(JavaEnv env, const std::string& v) {
	return JavaString(env, v);
}


*/

namespace JNI {

class JniHelper;
class JniJavaVM;
class JavaEnv;
class JavaObject;
class JavaClass;
class JavaString;
template<typename T>
class JavaArray;
template<typename R, typename ... Args>
class JavaMethod;
template<typename R, typename ... Args>
class JavaStaticMethod;
template<typename R, typename ... Args>
struct JniSignatureBuilder;

}


#endif
