#pragma once
#ifndef JNI_PROXY_H
#define JNI_PROXY_H

#include <JniForwards.h>
#include <JniJavaEnv.h>


namespace JNI {

/*

Для возвращения из джавы любого типа T необходимо реализовать три структуры:
JavaMethodCaller<T> и JavaStaticMethodCaller<T> с конвертацией в T из какого бы то ни было jtype.
И еще JniSignatureBuilder<T> тоже нужно реализовать.

Пример: std::string.

*/


namespace _Helpers {
	template<typename T>
	struct JniCallProxy {
		JniCallProxy(T v) : val(v) {}
		T Val() const { return val; }
		T val;
	};
}

template<typename T>
static inline _Helpers::JniCallProxy<T> MakeJniProxy(JavaEnv, T v) {
	return _Helpers::JniCallProxy<T>(v);
}

JavaString MakeJniProxy(JavaEnv env, const char * v);
JavaString MakeJniProxy(JavaEnv env, const std::string& v);
const JavaString& MakeJniProxy(JavaEnv env, const JavaString& v);

}

#endif
